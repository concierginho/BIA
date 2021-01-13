#include <sstream>

#include "ImageManager.h"
#include "../File/FileManager.h"
#include "../Experiment/ExperimentManager.h"
#include "../Management/Manager.h"

#ifdef _LOGGING_
#include "../Logging/ILogger.h"
using namespace BIA::Logging;
#endif


namespace BIA::Image
{
   ImageManager::ImageManager(Management::Manager* manager)
   {
      _manager = manager;
      _logger = _manager->Logger;
   }

   ImageManager::~ImageManager()
   {
      _manager = nullptr;
      _logger = nullptr;
   }

   void ImageManager::ReadTagsFromImage(TIFF* image)
   {
      TIFFGetField(image, TIFFTAG_IMAGEWIDTH, &PartImage::ParentImageWidth);
      TIFFGetField(image, TIFFTAG_IMAGELENGTH, &PartImage::ParentImageLength);
      TIFFGetField(image, TIFFTAG_BITSPERSAMPLE, &PartImage::BitsPerSample);
      TIFFGetField(image, TIFFTAG_SAMPLESPERPIXEL, &PartImage::SamplesPerPixel);
      PartImage::ScanlineSize = TIFFScanlineSize(image);
      //todo:
      //#ifdef _LOGGING_
      //         _logger->Message /*"Experiment Id " << experiment.GetId() << " /*/ << " Image information: width " <<  << " px, height " << imagelength
      //            << " px, bits per sample " << bitspersample << ", samples per pixel " << samplesperpixel << ", scanline size " << scanlinesize;
      //         _logger->Log(Logging::Source::IMAGE_MANAGER);
      //#endif
   }

   bool ImageManager::OpenParentTIFFImageForReading(TIFF** tiff, std::filesystem::path path)
   {
      std::string pathStr = path.string();
      const char* c_path = pathStr.c_str();
#ifdef _LOGGING_
      _logger->Message << " Opening '*.tif' image with path " << path.string() << ".";
      _logger->Log(Logging::Source::IMAGE_MANAGER);
#endif
      * tiff = TIFFOpen(c_path, "r");

      if (*tiff != nullptr)
      {
#if _LOGGING_
         _logger->Message << " Successful file opening on path " << path.string() << ".";
         _logger->Log(Logging::Source::IMAGE_MANAGER);
#endif
         return true;
      }
      return false;
   }

   bool ImageManager::CloseParentTIFFImage(TIFF** tiff)
   {
#if _LOGGING_
      _logger->Message << " Closing TIFF image";
      _logger->Log(Logging::Source::IMAGE_MANAGER);
#endif
      TIFFClose(*tiff);
      return true;
   }

   void ImageManager::SplitMainImages()
   {
      auto& experiments = _manager->ExperimentManager->GetExperiments();

      for (auto& experiment : experiments)
      {
         if (experiment.HasVerticalImage())
         {
            TIFF* verticalTIFFParentImage = nullptr;

            if (OpenParentTIFFImageForReading(&verticalTIFFParentImage, experiment.GetVerticalImagePath()))
            {
               ReadTagsFromImage(verticalTIFFParentImage);

               for (int i = 0; i < 40; i++)
               {
                  std::filesystem::path directoryPath = experiment.GetVerticalExperimentPathById(i);
                  std::filesystem::path settingsPath = experiment.GetVerticalExperimentSettingsPathById(i);
                  std::filesystem::path resultsPath = experiment.GetVerticalExperimentResultsPathById(i);

                  if (!_manager->FileManager->Exists(directoryPath))
                  {
#ifdef _LOGGING_

                     _logger->Message << "Experiment Id " << experiment.GetId() << " / Missing directory " << directoryPath.string();
                     _logger->Log(Logging::Source::IMAGE_MANAGER);
#endif
                     _manager->FileManager->CreateNewDirectory(directoryPath);
                  }

                  if (!_manager->FileManager->Exists(settingsPath))
                  {
#ifdef _LOGGING_

                     _logger->Message << "Experiment Id " << experiment.GetId() << " / Missing file " << settingsPath.string();
                     _logger->Log(Logging::Source::IMAGE_MANAGER);
#endif
                     _manager->FileManager->CreateNewFile(settingsPath);
                  }

                  if (!_manager->FileManager->Exists(resultsPath))
                  {
#ifdef _LOGGING_

                     _logger->Message << "Experiment Id " << experiment.GetId() << " / Missing file " << resultsPath.string();
                     _logger->Log(Logging::Source::IMAGE_MANAGER);
#endif
                     _manager->FileManager->CreateNewFile(resultsPath);
                  }

                  std::string verticalPartImagePath = experiment.GetVerticalImagePathById(i).string();
                  const char* c_verticalPathImagePath = verticalPartImagePath.c_str();

                  TIFF* verticalTIFFPartImage = TIFFOpen(c_verticalPathImagePath, "w");

                  TIFFSetField(verticalTIFFPartImage, TIFFTAG_IMAGEWIDTH, 1024);
                  TIFFSetField(verticalTIFFPartImage, TIFFTAG_IMAGELENGTH, 1024);
                  TIFFSetField(verticalTIFFPartImage, TIFFTAG_RESOLUTIONUNIT, 2);
                  TIFFSetField(verticalTIFFPartImage, TIFFTAG_SAMPLESPERPIXEL, 1);
                  TIFFSetField(verticalTIFFPartImage, TIFFTAG_BITSPERSAMPLE, 16);
                  TIFFSetField(verticalTIFFPartImage, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
                  TIFFSetField(verticalTIFFPartImage, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
                  TIFFSetField(verticalTIFFPartImage, TIFFTAG_COMPRESSION, COMPRESSION_NONE);

                  unsigned char* destinationbuffer = nullptr;
                  unsigned char* sourcebuffer = nullptr;

                  uint32 linebytes = PartImage::ScanlineSize;

                  destinationbuffer = (unsigned char*)_TIFFmalloc(linebytes);
                  sourcebuffer = (unsigned char*)_TIFFmalloc(linebytes);
#ifdef _LOGGING_

                  _logger->Message << "Allocating " << 2 * linebytes << " bytes for image copying operation.";
                  _logger->Log(Logging::Source::MEMORY_MANAGEMENT);
#endif
                  TIFFSetField(verticalTIFFPartImage, TIFFTAG_ROWSPERSTRIP, TIFFDefaultStripSize(verticalTIFFPartImage, linebytes));

                  uint32 row;

                  for (row = 0; row < PartImage::ParentImageLength; row++)
                  {
                     TIFFReadScanline(verticalTIFFParentImage, sourcebuffer, row);
                     memcpy(destinationbuffer, sourcebuffer, linebytes);
                     if (TIFFWriteScanline(verticalTIFFPartImage, destinationbuffer, row, 0) < 0)
                        break;

                     if (row == 1023)
                        break;
                  }

                  CloseParentTIFFImage(&verticalTIFFPartImage);

                  _TIFFfree(destinationbuffer);
                  _TIFFfree(sourcebuffer);

                  break;
               }
            }
#ifdef _LOGGING_

            _logger->Message << "Experiment Id " << experiment.GetId() << " / Releasing memory.";
            _logger->Log(Logging::Source::MEMORY_MANAGEMENT);
#endif
            TIFFClose(verticalTIFFParentImage);
#ifdef _LOGGING_
#endif
         }

         if (experiment.HasHorizontalImage())
         {

         }
      }
   }

}