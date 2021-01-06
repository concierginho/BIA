#pragma once

#include "../FileManagement/FileManager.h"
#include "../ExperimentManagement/ExperimentManager.h"
#include "../Logger/ILogger.h"

namespace BIA
{
   namespace ImageManagement
   {
      class ImageManager
      {
      public:
         ImageManager(FileManagement::FileManager*, ExperimentManagement::ExperimentManager*, Logging::ILogger*);
         ~ImageManager();

         void PrepareImageDirectories();
         void ScanImages();
      private:
         FileManagement::FileManager* _fileManager = nullptr;
         ExperimentManagement::ExperimentManager* _experimentManager = nullptr;
         Logging::ILogger* _logger = nullptr;
      };
   }
}

