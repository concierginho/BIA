#include "pch.h"
#include "BIAImageManager.h"
#include "TIFFSettingsManager.h"
#include "Operation.h"
#include "tiffio.h"
#include "Bitmap.h"

#include <nlohmann/json.hpp>
#include <fstream>

/// <summary>
/// Domyslny konstruktor.
/// </summary>
/// <param name="experimentManager"></param>
BIA::BIAImageManager::BIAImageManager(std::shared_ptr<BIAExperimentManager> experimentManager)
{
   _fileManager = _experimentManager->GetFileManager();
   _experimentManager = experimentManager;
}

#ifdef _LOGGING_
/// <summary>
/// Konstruktor uzywany gdy _LOGGING_ jest zdefiniowane.
/// </summary>
/// <param name="experimentManager"></param>
/// <param name="loggingManager"></param>
BIA::BIAImageManager::BIAImageManager(std::shared_ptr<BIAExperimentManager> experimentManager, std::shared_ptr<BIALoggingManager> loggingManager)
{
   _fileManager = experimentManager->GetFileManager();
   _experimentManager = experimentManager;
   _loggingManager = loggingManager;
}
#endif

/// <summary>
/// Destruktor
/// </summary>
BIA::BIAImageManager::~BIAImageManager()
{
}

/// <summary>
/// Cel: Podzielenie obrazow zrodlowych na 40 o wymiarach 1024 x 1024.
/// </summary>
/// <param name="cancelled"></param>
void BIA::BIAImageManager::SplitImages(std::atomic<bool>& cancelled)
{
#ifdef _LOGGING_
   _loggingManager.get()->Message << "Splitting images has been started.";
   _loggingManager->Log(ESource::BIA_IMAGE_MANAGER);
   auto start = std::chrono::steady_clock::now();
#endif

   for (int i = 0; i < 2; i++)
   {
      EFolder type = (EFolder)i;

      for (auto& experiment : _experimentManager->GetExperiments())
      {
         if (cancelled == true)
         {
#ifdef _LOGGING_
            _loggingManager->Message << "Requesting process cancellation.";
            _loggingManager->Log(ESource::BIA_IMAGE_MANAGER);
#endif
            return;
         }

         auto parentTIFFImage = experiment.GetTIFFImage(type);
         std::string tiffPathStr = parentTIFFImage->GetImagePath().string();
         auto c_tiffPath = tiffPathStr.c_str();

         if (c_tiffPath == nullptr)
         {
#ifdef _LOGGING_
            _loggingManager->Message << "Path to TIFF image was nullptr.";
            _loggingManager->Log(ESource::BIA_IMAGE_MANAGER);
#endif
            return;
         }

         TIFF* parentImage = TIFFOpen(c_tiffPath, READ);
         TIFFSettingsManager settingsManager = TIFFSettingsManager();

         _ASSERT(parentImage);
         if (!parentImage)
         {
#ifdef _LOGGING_
            _loggingManager->Message << "Unable to open TIFF image at path: " << c_tiffPath;
            _loggingManager->Log(ESource::BIA_IMAGE_MANAGER);
#endif
            return;
         }

         parentTIFFImage->GetImageSettings() = settingsManager.ReadSettings(&parentImage);

         for (auto& partExperiment : experiment.GetPartExperiments(type))
         {
            if (cancelled == true)
            {
#ifdef _LOGGING_
               _loggingManager->Message << "Requesting process cancellation.";
               _loggingManager->Log(ESource::BIA_IMAGE_MANAGER);
#endif
               return;
            }

            auto partImagePath = partExperiment.GetImagePath().string();
            auto c_partImagePath = partImagePath.c_str();

            if (c_partImagePath == nullptr)
               continue;

            TIFF* partImage = nullptr;

            partImage = TIFFOpen(c_partImagePath, WRITE);

            if (!partImage)
            {
#ifdef _LOGGING_
               _loggingManager->Message << "Unable to open TIFF file at path: " << partImagePath;
               _loggingManager->Log(ESource::BIA_EXPERIMENT_MANAGER);
#endif
               continue;
            }

            auto settings = settingsManager.GetPartImageSettings(parentTIFFImage->GetImageSettings());
            settingsManager.ApplySettings(&partImage, settings);
            partExperiment.GetTIFFImage()->GetImageSettings() = settings;

            switch (type)
            {
               case EFolder::HORIZONTAL:
                  CopyHorizontalPartImageToDestinationFile(&parentImage, parentTIFFImage, &partImage, partExperiment.GetTIFFImage(), partExperiment.GetId());
                  break;
               case EFolder::VERTICAL:
               default:
                  CopyVerticalPartImageToDestinationFile(&parentImage, parentTIFFImage, &partImage, partExperiment.GetTIFFImage(), partExperiment.GetId());
                  break;
            }
            TIFFClose(partImage);
         }
         TIFFClose(parentImage);
      }
   }

#ifdef _LOGGING_
   auto end = std::chrono::steady_clock::now();
   auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
   _loggingManager.get()->Message << "Splitting images has ended and took: " << time << "ms.";
   _loggingManager->Log(ESource::BIA_EXPERIMENT_MANAGER);
#endif
}

void BIA::BIAImageManager::PerformOperations(std::atomic<bool>& cancelled)
{
   for (int i = 0; i < 2; i++)
   {
      EFolder folder = (EFolder)i;

      for (auto& experiment : _experimentManager->GetExperiments())
      {
         if (cancelled == true)
         {
#ifdef _LOGGING_
            _loggingManager->Message << "Requesting process cancellation.";
            _loggingManager->Log(ESource::BIA_IMAGE_MANAGER);
#endif
            return;
         }

         for (auto& partExperiment : experiment.GetPartExperiments(folder))
         {
            if (cancelled == true)
            {
#ifdef _LOGGING_
               _loggingManager->Message << "Requesting process cancellation.";
               _loggingManager->Log(ESource::BIA_IMAGE_MANAGER);
#endif
               return;
            }
         }
      }
   }
}

/// <summary>
/// Cel: Odczytanie ustawien zapisanych w obrazach.
/// </summary>
/// <param name="tiffPtr"></param>
/// <param name="tiffImage"></param>
void BIA::BIAImageManager::ReadImageSettings(TIFF* tiffPtr, TIFFImage* tiffImage)
{
   if (tiffPtr == nullptr)
      return;

   auto& settings = tiffImage->GetImageSettings();

   TIFFGetField(tiffPtr, TIFFTAG_IMAGEWIDTH, &settings.ImageWidth);
   TIFFGetField(tiffPtr, TIFFTAG_IMAGELENGTH, &settings.ImageLength);
   TIFFGetField(tiffPtr, TIFFTAG_BITSPERSAMPLE, &settings.BitsPerSample);
   TIFFGetField(tiffPtr, TIFFTAG_SAMPLESPERPIXEL, &settings.SamplesPerPixel);
   TIFFGetField(tiffPtr, TIFFTAG_RESOLUTIONUNIT, &settings.ResolutionUnit);

   uint32 scanlineSize = TIFFScanlineSize(tiffPtr);
   tiffImage->GetImageSettings().ScanlineSize = scanlineSize;
}

/// <summary>
/// Cel: Skopiowanie wartosci pixeli z obrazu zrodlowego 
///      zorientowanego horyzontalnie na podstawie id linii
///      do kopii o rozmiarach 1024 x 1024.
/// </summary>
/// <param name="src"></param>
/// <param name="parentImg"></param>
/// <param name="tar"></param>
/// <param name="childImg"></param>
/// <param name="id"></param>
void BIA::BIAImageManager::CopyHorizontalPartImageToDestinationFile(TIFF** src, TIFFImage* parentImg, TIFF** tar, TIFFImage* childImg, int id)
{
   if (src == nullptr || parentImg == nullptr || tar == nullptr || childImg == nullptr)
   {
#ifdef _LOGGING_
      _ASSERT(!parentImg);
      if (parentImg == nullptr)
      {
         _loggingManager->Message << "Parent Image was nullptr.";
         _loggingManager->Log(ESource::BIA_IMAGE_MANAGER);
      }

      _ASSERT(!childImg);
      if (childImg == nullptr)
      {
         _loggingManager->Message << "Child Image was nullptr.";
         _loggingManager->Log(ESource::BIA_IMAGE_MANAGER);
      }

      _ASSERT(!src);
      if (src == nullptr)
      {
         _loggingManager->Message << "TIFF parent image pointer was nullptr.";
         _loggingManager->Log(ESource::BIA_IMAGE_MANAGER);
      }

      _ASSERT(!tar);
      if (tar == nullptr)
      {
         _loggingManager->Message << "TIFF child image pointer was nullptr.";
         _loggingManager->Log(ESource::BIA_IMAGE_MANAGER);
      }
#endif
      return;
   }

   const auto& parentTIFFImageSetings = parentImg->GetImageSettings();
   const auto& childTIFFImageSettings = childImg->GetImageSettings();

   unsigned char* destinationBuffer = nullptr;
   unsigned char* sourceBuffer = nullptr;

   uint32 linebytes = childTIFFImageSettings.ScanlineSize;
   uint32 parentlinebytes = 40 * linebytes;

   destinationBuffer = (unsigned char*)_TIFFmalloc(linebytes);
   sourceBuffer = (unsigned char*)_TIFFmalloc(parentlinebytes);

#ifdef _LOGGING_
   _loggingManager->Message << "Allocation " << 41 * linebytes << " bytes for image copying [HORIZONTAL] operation.";
   _loggingManager->Log(ESource::MEMORY_MANAGEMENT);
#endif

   uint32 fristColumnInParentImage = id * 1024;

   uint32 firstRowInChildImage = 0;
   uint32 lastRowInChildImage = 1023;
   uint32 childCurrentRow = firstRowInChildImage;

   for (; childCurrentRow <= lastRowInChildImage; childCurrentRow++)
   {
      TIFFReadScanline(*src, sourceBuffer, childCurrentRow);
      AdjustScanline(sourceBuffer, static_cast<int>(parentlinebytes));

      memcpy(destinationBuffer, sourceBuffer + fristColumnInParentImage, linebytes);
      if (TIFFWriteScanline(*tar, destinationBuffer, childCurrentRow) < 0)
         break;
   }

   _TIFFfree(destinationBuffer);
   _TIFFfree(sourceBuffer);

#ifdef _LOGGING_
   _loggingManager->Message << "Released " << 41 * linebytes << " bytes.";
   _loggingManager->Log(ESource::MEMORY_MANAGEMENT);
#endif
}

/// <summary>
/// Cel: Skopiowanie wartosci pixeli z obrazu zrodlowego 
///      zorientowanego wertykalnie na podstawie id linii
///      do kopii o rozmiarach 1024 x 1024.
/// </summary>
/// <param name="src"></param>
/// <param name="parentImg"></param>
/// <param name="tar"></param>
/// <param name="childImg"></param>
/// <param name="id"></param>
void BIA::BIAImageManager::CopyVerticalPartImageToDestinationFile(TIFF** src, TIFFImage* parentImg, TIFF** tar, TIFFImage* childImg, int id)
{
   if (parentImg == nullptr || childImg == nullptr || src == nullptr || tar == nullptr)
   {
#ifdef _LOGGING_
      _ASSERT(!parentImg);
      if (parentImg == nullptr)
      {
         _loggingManager->Message << "Parent Image was nullptr.";
         _loggingManager->Log(ESource::BIA_IMAGE_MANAGER);
      }
      
      _ASSERT(!childImg);
      if (childImg == nullptr)
      {
         _loggingManager->Message << "Child Image was nullptr.";
         _loggingManager->Log(ESource::BIA_IMAGE_MANAGER);
      }
      
      _ASSERT(!src);
      if (src == nullptr)
      {
         _loggingManager->Message << "TIFF parent image pointer was nullptr.";
         _loggingManager->Log(ESource::BIA_IMAGE_MANAGER);
      }
      
      _ASSERT(!tar);
      if (tar == nullptr)
      {
         _loggingManager->Message << "TIFF child image pointer was nullptr.";
         _loggingManager->Log(ESource::BIA_IMAGE_MANAGER);
      }
#endif
      return;
   }

   auto& parentTIFFImageSettings = parentImg->GetImageSettings();
   auto& childTIFFImageSettings = childImg->GetImageSettings();

   unsigned char* destinationBuffer = nullptr;
   unsigned char* sourceBuffer = nullptr;

   uint32 linebytes = childTIFFImageSettings.ScanlineSize;

   destinationBuffer = (unsigned char*)_TIFFmalloc(linebytes);
   sourceBuffer = (unsigned char*)_TIFFmalloc(linebytes);

#ifdef _LOGGING_
   _loggingManager->Message << "Allocation " << 2 * linebytes << " bytes for image copying [VERTICAL] operation.";
   _loggingManager->Log(ESource::MEMORY_MANAGEMENT);
#endif

   uint32 firstRowInParentImage = id * 1024;
   uint32 lastRowInParentImage = firstRowInParentImage + 1023;
   uint32 parentCurrentRow = firstRowInParentImage;

   uint32 firstRowInChildImage = 0;
   uint32 lastRowInChildImage = 1023;
   uint32 childCurrentRow = firstRowInChildImage;

   for (; childCurrentRow <= lastRowInChildImage; childCurrentRow++, parentCurrentRow++)
   {
      TIFFReadScanline(*src, sourceBuffer, parentCurrentRow);
      AdjustScanline(sourceBuffer, static_cast<int>(linebytes));

      memcpy(destinationBuffer, sourceBuffer, linebytes);
      if (TIFFWriteScanline(*tar, destinationBuffer, childCurrentRow, 0) < 0)
         break;
   }

   _TIFFfree(destinationBuffer);
   _TIFFfree(sourceBuffer);

#ifdef _LOGGING_
   _loggingManager->Message << "Released " << 2 * linebytes << " bytes.";
   _loggingManager->Log(ESource::MEMORY_MANAGEMENT);
#endif
}

/// <summary>
/// Cel: Wygenerowanie zbinaryzowanych obrazow stanowiacych
///      podglad wykonanych na obrazie operacji.
/// </summary>
/// <param name="cancelled"></param>
void BIA::BIAImageManager::GeneratePreviews(std::atomic<bool>& cancelled)
{
   auto& experiments = _experimentManager->GetExperiments();
   
   for (int i = 0; i < 2; i++)
   {
      EFolder type = (EFolder)i;

      for (auto& experiment : experiments)
      {
         auto& partExperiments = experiment.GetPartExperiments(type);

         for (auto& partExperiment : partExperiments)
         {
            if (cancelled == true)
            {
#ifdef _LOGGING_
               _loggingManager->Message << "Requesting process cancellation.";
               _loggingManager->Log(ESource::BIA_IMAGE_MANAGER);
#endif
               return;
            }

            //Bitmap* bitmapix = new Bitmap(1024, 1024);
            //auto path = partExperiment.GetPreviewImagePath();
            //bitmapix->LoadFromFile(path); 

            std::string originalImagePath = partExperiment.GetImagePath().string();
            const char* c_originalImagePath = originalImagePath.c_str();

            std::string previewImagePath = partExperiment.GetPreviewImagePath().string();
            const char* c_previewImagePath = previewImagePath.c_str();

            TIFF* originalTIFFImage = TIFFOpen(c_originalImagePath, READ);
            TIFF* previewTIFFImage = TIFFOpen(c_previewImagePath, WRITE);

            if (originalTIFFImage == nullptr || previewTIFFImage == nullptr)
            {
               _ASSERT(!originalTIFFImage);
               _ASSERT(!previewTIFFImage);
               continue;
            }

            TIFFSettingsManager settingsManager;
            const auto& previewImageSettings = settingsManager.GetPreviewImageSettings();
            settingsManager.ApplySettings(&previewTIFFImage, previewImageSettings);

            uint32 linebytes = previewImageSettings.ScanlineSize;

            unsigned char* source_buffer = (unsigned char*)_TIFFmalloc(linebytes);
            unsigned char* destination_buffer = (unsigned char*)_TIFFmalloc(linebytes);

            fs::path recipeJsonPath = partExperiment.GetRecipeJsonPath();
            auto jsonRecipe = _fileManager->ReadFromJson(recipeJsonPath);
            if (!jsonRecipe.contains("threshold"))
            {
#ifdef _LOGGING_
#endif
               continue;
            }


            unsigned char threshold = static_cast<unsigned char>(jsonRecipe["threshold"]);

            for (uint32 i = 0; i < linebytes; i++)
            {
               TIFFReadScanline(originalTIFFImage, source_buffer, i);

               memcpy(destination_buffer, source_buffer, linebytes);

               BinarizeScanline(destination_buffer, linebytes, threshold);

               if (TIFFWriteScanline(previewTIFFImage, destination_buffer, i) < 0)
                  break;
            }

            _TIFFfree(source_buffer);
            _TIFFfree(destination_buffer);

            TIFFClose(originalTIFFImage);
            TIFFClose(previewTIFFImage);
         }
      }
   }
}

/// <summary>
/// Cel: Inicjalizacja.
/// </summary>
void BIA::BIAImageManager::Init()
{
#ifdef _LOGGING_
   _loggingManager->Message << "Initializing BIAImageManager...";
   _loggingManager->Log(ESource::BIA_IMAGE_MANAGER);
#endif
}

/// <summary>
/// Cel: Normalizacja wartosci pixeli.
///      Jezeli wartosc pixela jest ujemna - zostaje zastapiona wartoscia bezwzgledna z tej wartosci.
/// </summary>
/// <param name="array"></param>
/// <param name="length"></param>
void BIA::BIAImageManager::AdjustScanline(unsigned char* array, int length)
{
   if (array == nullptr)
      return;

   if (array[0] < 0)
   {
      #pragma omp parallel for
      for (int i = 0; i < length; i++)
      {
         array[i] = static_cast<unsigned char>(std::abs(array[i]));
      }
   }
   else
   {
      #pragma omp parallel for
      for (int i = 0; i < length; i++)
      {
         array[i] = static_cast<unsigned char>(255 - array[i]);
      }
   }
}

/// <summary>
/// Cel: Binaryzacja obrazu na podstawie wartosic parametru "threshold".
/// </summary>
void BIA::BIAImageManager::BinarizeScanline(unsigned char* buffer, int length, unsigned char threshold)
{
   unsigned char black = static_cast<unsigned char>(255);
   unsigned char white = static_cast<unsigned char>(0);

   if (threshold < white || threshold > black)
   {
#ifdef _LOGGING_
      _loggingManager->Message << "Threshold value was incorrect - it should be set between 0 and 255.";
      _loggingManager->Log(ESource::BIA_IMAGE_MANAGER);
#endif
      return;
   }

   #pragma omp parallel for
   for (int i = 0; i < length; i++)
   {
      if (buffer[i] >= threshold)
         buffer[i] = black;
     else
         buffer[i] = white;
   }
}
