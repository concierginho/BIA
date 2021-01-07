#include "../Manager.h"

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
      
      void ImageManager::PrepareImageDirectories()
      {
         auto& experiments = _manager->ExperimentManager->GetExperiments();


         for (const auto& experiment : experiments)
         {
            //for(int i = )
            experiment;
         }
      }

      void ImageManager::ScanImages()
      {      }
   }
}