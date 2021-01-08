#include <sstream>

#include "../Manager.h"
#include "tiffio.h"

namespace BIA
{
   namespace Management::Image
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

      void ImageManager::SplitMainImages()
      {
#ifdef _LOGGING_
         std::stringstream msg;
#endif
         auto& experiments = _manager->ExperimentManager->GetExperiments();

         for (auto& experiment : experiments)
         {
            if (experiment.HasVerticalImage())
            {
               std::string verticalDirectoryPath = experiment.GetVerticalImagePath().string();
               const char* cpath = verticalDirectoryPath.c_str();
#ifdef _LOGGING_
               msg.str(std::string());
               msg << "Experiment Id " << experiment.GetId() << " / Opening '*.tif' image with path " << verticalDirectoryPath << ".";
               _logger->Log(msg, Logging::Source::IMAGE_MANAGER);
#endif
               TIFF* verticalTiffImage = TIFFOpen(cpath, "r");
               if (verticalTiffImage != nullptr)
               {
#if _LOGGING_
                  msg.str(std::string());
                  msg << "Experiment Id " << experiment.GetId() << " / Successful file opening on path " << verticalDirectoryPath << ".";
                  _logger->Log(msg, Logging::Source::IMAGE_MANAGER);
#endif
                  uint32 width, height;
                  size_t npixels;
                  uint32* raster;

                  TIFFGetField(verticalTiffImage, TIFFTAG_IMAGEWIDTH, &width);
                  TIFFGetField(verticalTiffImage, TIFFTAG_IMAGELENGTH, &height);

#ifdef _LOGGING_
                  msg.str(std::string());
                  msg << "Experiment Id " << experiment.GetId() << " / Image information: width " << width << " px, height " << height << " px.";
                  _logger->Log(msg, Logging::Source::IMAGE_MANAGER);
#endif
                  npixels = width * height;
#ifdef _LOGGING_
                  msg.str(std::string());
                  msg << "Experiment Id " << experiment.GetId() << " / Allocationg memory for " << npixels << " fields of type 'uint32'.";
                  _logger->Log(msg, Logging::Source::MEMORY_MANAGEMENT);
#endif
                  raster = (uint32*)_TIFFmalloc(npixels * sizeof(uint32));

                  if (raster != nullptr)
                  {
                     if (TIFFReadRGBAImage(verticalTiffImage, width, height, raster, 0))
                     {
#ifdef _LOGGING_
                        msg.str(std::string());
                        msg << "Experiment Id " << experiment.GetId() << " / Successful reading file as RGBA Image.";
                        _logger->Log(msg, Logging::Source::IMAGE_MANAGER);
#endif
                        for (int i = 0; i < 40; i++)
                        {
                           std::filesystem::path directoryPath = experiment.GetVerticalExperimentPathById(i);
                           std::filesystem::path settingsPath = experiment.GetVerticalExperimentSettingsPathById(i);
                           std::filesystem::path resultsPath = experiment.GetVerticalExperimentResultsPathById(i);

                           if (!_manager->FileManager->Exists(directoryPath))
                           {
#ifdef _LOGGING_
                              msg.str(std::string());
                              msg << "Experiment Id " << experiment.GetId() << " / Missing directory " << directoryPath.string();
                              _logger->Log(msg, Logging::Source::IMAGE_MANAGER);
#endif
                              _manager->FileManager->CreateNewDirectory(directoryPath);
                           }

                           if (!_manager->FileManager->Exists(settingsPath))
                           {
#ifdef _LOGGING_
                              msg.str(std::string());
                              msg << "Experiment Id " << experiment.GetId() << " / Missing file " << settingsPath.string();
                              _logger->Log(msg, Logging::Source::IMAGE_MANAGER);
#endif
                              _manager->FileManager->CreateNewFile(settingsPath);
                           }

                           if (!_manager->FileManager->Exists(resultsPath))
                           {
#ifdef _LOGGING_
                              msg.str(std::string());
                              msg << "Experiment Id " << experiment.GetId() << " / Missing file " << resultsPath.string();
                              _logger->Log(msg, Logging::Source::IMAGE_MANAGER);
#endif
                              _manager->FileManager->CreateNewFile(resultsPath);
                           }


                        }
                     }
                     _TIFFfree(raster);
#ifdef _LOGGING_
                     msg.str(std::string());
                     msg << "Experiment Id " << experiment.GetId() << " / Releasing memory.";
                     _logger->Log(msg, Logging::Source::MEMORY_MANAGEMENT);
#endif
                  }
               }
               TIFFClose(verticalTiffImage);
#ifdef _LOGGING_
#endif
            }

            if (experiment.HasHorizontalImage())
            {

            }
         }
      }
   }
}