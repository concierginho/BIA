#include "pch.h"
#include "BIAImageManager.h"
#include "TIFFSettingsManager.h"
#include "tiffio.h"

BIA::BIAImageManager::BIAImageManager(std::shared_ptr<BIAExperimentManager> experimentManager)
{
   _fileManager = _experimentManager->GetFileManager();
   _experimentManager = experimentManager;
}

#ifdef _LOGGING_
BIA::BIAImageManager::BIAImageManager(std::shared_ptr<BIAExperimentManager> experimentManager, std::shared_ptr<BIALoggingManager> loggingManager)
{
   _fileManager = experimentManager->GetFileManager();
   _experimentManager = experimentManager;
   _loggingManager = loggingManager;
}
#endif

BIA::BIAImageManager::~BIAImageManager()
{
}

void BIA::BIAImageManager::SplitImages()
{
   for (int i = 0; i < 2; i++)
   {
      EFolder type = (EFolder)i;

      for (auto& experiment : _experimentManager->GetExperiments())
      {
         auto parentTIFFImage = experiment.GetTIFFImage(type);
         std::string tiffPathStr = parentTIFFImage->GetPath().string();
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

         parentTIFFImage->Settings = settingsManager.ReadSettings(&parentImage);

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

            auto settings = settingsManager.GetPartImageSettings(parentTIFFImage->Settings);
            settingsManager.ApplySettings(&partImage, settings);
            partExperiment.GetTIFFImage()->Settings = settings;

            switch (type)
            {
               case EFolder::HORIZONTAL:
                  CopyHorizontalPartImageToDestinationFile(&parentImage, parentTIFFImage, &partImage, partExperiment.GetTIFFImage(), partExperiment.ID);
                  break;
               case EFolder::VERTICAL:
               default:
                  CopyVerticalPartImageToDestinationFile(&parentImage, parentTIFFImage, &partImage, partExperiment.GetTIFFImage(), partExperiment.ID);
                  break;
            }

            TIFFClose(partImage);
         }

         TIFFClose(parentImage);
      }
   }
}

void BIA::BIAImageManager::ReadImageSettings(TIFF* tiffPtr, TIFFImage* tiffImage)
{
   if (tiffPtr == nullptr)
      return;

   TIFFGetField(tiffPtr, TIFFTAG_IMAGEWIDTH, &tiffImage->Settings.ImageWidth);
   TIFFGetField(tiffPtr, TIFFTAG_IMAGELENGTH, &tiffImage->Settings.ImageLength);
   TIFFGetField(tiffPtr, TIFFTAG_BITSPERSAMPLE, &tiffImage->Settings.BitsPerSample);
   TIFFGetField(tiffPtr, TIFFTAG_SAMPLESPERPIXEL, &tiffImage->Settings.SamplesPerPixel);
   TIFFGetField(tiffPtr, TIFFTAG_RESOLUTIONUNIT, &tiffImage->Settings.ResolutionUnit);

   uint32 scanlineSize = TIFFScanlineSize(tiffPtr);
   tiffImage->Settings.ScanlineSize = scanlineSize;
}

void BIA::BIAImageManager::CopyHorizontalPartImageToDestinationFile(TIFF** src, TIFFImage* parentImg, TIFF** tar, TIFFImage* childImg, int id)
{
   if (src == nullptr || parentImg == nullptr || tar == nullptr || childImg == nullptr)
   {
#ifdef _LOGGING_

#endif
      return;
   }

   auto parentTIFFImageSetings = parentImg->Settings;
   auto childTIFFImageSettings = childImg->Settings;

   unsigned char* destinationBuffer = nullptr;
   unsigned char* sourceBuffer = nullptr;

   uint32 linebytes = childTIFFImageSettings.ScanlineSize;
   uint32 linebytesx40 = 40 * linebytes;

   destinationBuffer = (unsigned char*)_TIFFmalloc(linebytes);
   sourceBuffer = (unsigned char*)_TIFFmalloc(linebytesx40);

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
      memcpy(destinationBuffer, sourceBuffer + fristColumnInParentImage, linebytes);
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

void BIA::BIAImageManager::CopyVerticalPartImageToDestinationFile(TIFF** src, TIFFImage* parentImg, TIFF** tar, TIFFImage* childImg, int id)
{
   if (parentImg == nullptr || childImg == nullptr || src == nullptr || tar == nullptr)
   {
#ifdef _LOGGING_
#endif
      return;
   }

   auto parentTIFFImageSettings = parentImg->Settings;
   auto childTIFFImageSettings = childImg->Settings;

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

void BIA::BIAImageManager::Init()
{
#ifdef _LOGGING_
   _loggingManager->Message << "Initializing BIAImageManager.";
   _loggingManager->Log(ESource::BIA_IMAGE_MANAGER);
#endif
}
