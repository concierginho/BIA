#include "ImageManager.h"

namespace BIA
{
   namespace ImageManagement
   {
      ImageManager::ImageManager(FileManagement::FileManager* fileManager, ExperimentManagement::ExperimentManager* experimentManager, Logging::ILogger* logger)
      {
         _fileManager = fileManager;
         _experimentManager = experimentManager;
         _logger = logger;
      }

      ImageManager::~ImageManager()
      {
         _fileManager = nullptr;
         _experimentManager = nullptr;
         _logger = nullptr;
      }
      
      void ImageManager::PrepareImageDirectories()
      {
         auto experiments = _experimentManager->GetExperiments();

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