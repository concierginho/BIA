#include "pch.h"
#include "BIAImageManager.h"
#include "TIFFSettingsManager.h"
#include "tiffio.h"

/// <summary>
/// Konstruktor uzywany gdy _LOGGING_ nie jest zdefiniowane.
/// </summary>
BIA::BIAImageManager::BIAImageManager(std::shared_ptr<BIAExperimentManager> experimentManager)
{
   _fileManager = _experimentManager->GetFileManager();
   _experimentManager = experimentManager;
}

#ifdef _LOGGING_
/// <summary>
/// Konstruktor uzywany gdy _LOGGING_ jest zdefiniowany.
/// </summary>
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
/// Funkcja dzielaca obrazy typu 'tif' na 40 mniejszych obrazow.
/// </summary>
void BIA::BIAImageManager::SplitImages()
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

         TIFF* parentImage = TIFFOpen(c_tiffPath, "r");
         TIFFSettingsManager settingsManager = TIFFSettingsManager();

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
            auto partImagePath = partExperiment.GetImagePath().string();
            auto c_partImagePath = partImagePath.c_str();

            if (c_partImagePath == nullptr)
               continue;

            TIFF* partImage = nullptr;

            partImage = TIFFOpen(c_partImagePath, "w");

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
   _loggingManager.get()->Message << "Splitting images   has ended and took: " << time << "ms.";
   _loggingManager->Log(ESource::BIA_EXPERIMENT_MANAGER);
#endif
}

/// <summary>
/// Funkcja pozwalajaca na odczytanie ustawien zapisanych w pliku typu 'tif'.
/// </summary>
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
/// Funkcja sluzaca do skopiowania i zapisania odpowiedniego fragmentu
/// obrazu zorientowanego horyzontalnie do mniejszego stanowiacego 
/// czterdziesta czesc powierzchni obrazu, z ktorego kopiowane sa dane.
/// Dobor danych do skopiowania odbywa sie na podstawie id.
/// </summary>
void BIA::BIAImageManager::CopyHorizontalPartImageToDestinationFile(TIFF** src, TIFFImage* parentImg, TIFF** tar, TIFFImage* childImg, int id)
{
   if (src == nullptr || parentImg == nullptr || tar == nullptr || childImg == nullptr)
   {
#ifdef _LOGGING_
      if (parentImg == nullptr)
      {
         _loggingManager->Message << "Parent Image was nullptr. ";
         _loggingManager->Log(ESource::BIA_IMAGE_MANAGER);
      }

      if (childImg == nullptr)
      {
         _loggingManager->Message << "Child Image was nullptr. ";
         _loggingManager->Log(ESource::BIA_IMAGE_MANAGER);
      }

      if (src == nullptr)
      {
         _loggingManager->Message << "TIFF parent image pointer was nullptr. ";
         _loggingManager->Log(ESource::BIA_IMAGE_MANAGER);
      }

      if (tar == nullptr)
      {
         _loggingManager->Message << "TIFF child image pointer was nullptr. ";
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
   _loggingManager->Message << "Released " << 2 * linebytes << " bytes.";
   _loggingManager->Log(ESource::MEMORY_MANAGEMENT);
#endif
}

/// <summary>
/// Funkcja sluzaca do skopiowania i zapisania odpowiedniego fragmentu
/// obrazu zorientowanego wertykalnie do mniejszego stanowiacego 
/// czterdziesta czesc powierzchni obrazu, z ktorego kopiowane sa dane.
/// Dobor danych do skopiowania odbywa sie na podstawie id.
/// </summary>
void BIA::BIAImageManager::CopyVerticalPartImageToDestinationFile(TIFF** src, TIFFImage* parentImg, TIFF** tar, TIFFImage* childImg, int id)
{
   if (parentImg == nullptr || childImg == nullptr || src == nullptr || tar == nullptr)
   {
#ifdef _LOGGING_
      _ASSERT(!parentImg);
      if (parentImg == nullptr)
      {
         _loggingManager->Message << "Parent Image was nullptr. ";
         _loggingManager->Log(ESource::BIA_IMAGE_MANAGER);
      }
      
      _ASSERT(!childImg);
      if (childImg == nullptr)
      {
         _loggingManager->Message << "Child Image was nullptr. ";
         _loggingManager->Log(ESource::BIA_IMAGE_MANAGER);
      }
      
      _ASSERT(!src);
      if (src == nullptr)
      {
         _loggingManager->Message << "TIFF parent image pointer was nullptr. ";
         _loggingManager->Log(ESource::BIA_IMAGE_MANAGER);
      }
      
      _ASSERT(!tar);
      if (tar == nullptr)
      {
         _loggingManager->Message << "TIFF child image pointer was nullptr. ";
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
/// Funkcja sluzaca do wygenerowania obrazow binarnych,
/// na podstawie zapisanej w pliku recipe.json wartosci
/// pola 'threshold'.
/// </summary>
void BIA::BIAImageManager::GeneratePreviews()
{
   auto& experiments = _experimentManager->GetExperiments();
   
   for (auto & experiment : experiments)
   {
      for (int i = 0; i < 2; i++)
      {
         EFolder type = (EFolder)i;
         auto& partExperiments = experiment.GetPartExperiments(type);

         for (auto& partExperiment : partExperiments)
         {
            std::string originalImagePath = partExperiment.GetImagePath().string();
            const char* c_originalImagePath = originalImagePath.c_str();

            std::string previewImagePath = partExperiment.GetPreviewPath().string();
            const char* c_previewImagePath = previewImagePath.c_str();
         
            TIFF* originalTIFFImage = TIFFOpen(c_originalImagePath, "r");
            TIFF* previewTIFFImage = TIFFOpen(c_previewImagePath, "w");

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

            for (uint32 i = 0; i < linebytes; i++)
            {
               TIFFReadScanline(originalTIFFImage, source_buffer, i);

               memcpy(destination_buffer, source_buffer, linebytes);

               BinarizeScanline(destination_buffer, linebytes, static_cast<unsigned char>(200));

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
/// Funkcja inicjalizujaca
/// </summary>
void BIA::BIAImageManager::Init()
{
#ifdef _LOGGING_
   _loggingManager->Message << "Initializing BIAImageManager.";
   _loggingManager->Log(ESource::BIA_IMAGE_MANAGER);
#endif
}

/// <summary>
/// Funkcja sluzaca do odpowiedniego 'wyprostowania' wartosic zapisanych w tablicach znakow.
/// Jezeli wartosc w tablicy jest ujemna to zostaje zamieninona na wartosc bezwzgledna z siebie samej.
/// Jezeli wartosc w tablicy jest dodatnia to wartosc ta zostaje odjeta od maksymalnej wartosic (255)
/// i nadpisana.
/// Pozwala to 'obrocic' kolory w obrazie.
/// </summary>
/// <param name="array"></param>
/// <param name="length"></param>
void BIA::BIAImageManager::AdjustScanline(unsigned char* array, int length)
{
   #pragma omp parallel for
   for (int i = 0; i < length; i++)
   {
      unsigned char value = array[i];
      if (value < 0)
         array[i] = static_cast<unsigned char>(-1 * std::abs(array[i]));
      else
         array[i] = static_cast<unsigned char>(255 - value);
   }
}

/// <summary>
/// Funkcja sluzaca do binaryzacji tablicy znakow, na podstawie
/// zmiennej 'threshold' ustawiona zostaje albo maksymalna lub minimalna
/// wartosc piksela
/// Wynikiem jest tablica skladajaca sie z dwoch kolorow (czarnego lub bialego).
/// </summary>
void BIA::BIAImageManager::BinarizeScanline(unsigned char* buffer, int length, unsigned char threshold)
{
   unsigned char black = static_cast<unsigned char>(255);
   unsigned char white = static_cast<unsigned char>(0);

   if (threshold < white || threshold > black)
   {
#ifdef _LOGGING_
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
