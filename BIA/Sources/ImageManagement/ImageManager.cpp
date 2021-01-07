#include "../Common/Manager.h"

namespace BIA
{
   namespace ImageManagement
   {
      ImageManager::ImageManager(Management::Manager* manager)
      {
         _manager = manager;
         _logger = _manager->GetLogger();
      }

      ImageManager::~ImageManager()
      {
         _manager = nullptr;
         _logger = nullptr;
      }
      
      void ImageManager::PrepareImageDirectories()
      {
         auto experiments = _manager->GetExperimentManager()->GetExperiments();

         for (const auto& experiment : experiments)
         {
            //for(int i = )
            experiment;
         }
      }

      void ImageManager::ScanImages()
      {
      }
   }
}