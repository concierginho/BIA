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
         auto& experiments = _manager->ExperimentManager->GetExperiments();

         for (auto& experiment : experiments)
         {
            if (experiment.HasVerticalImage())
            {
               std::string verticalDirectoryPath = experiment.GetVerticalImagePath().string();
               const char* cpath = verticalDirectoryPath.c_str();
               TIFF* verticalTiffImage = TIFFOpen(cpath, "r");
               TIFFClose(verticalTiffImage);
            }

            if (experiment.HasHorizontalImage())
            {

            }
         }
      }
   }
}