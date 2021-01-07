#pragma once

#include "../Logging/ILogger.h"
#include "../FileManagement/FileManager.h"
#include "../ExperimentManagement/ExperimentManager.h"
#include "../ImageManagement/ImageManager.h"

namespace BIA
{
   namespace Management
   {
      class Manager
      {
      private:
         ExperimentManagement::ExperimentManager* _experimentManager;
         FileManagement::FileManager* _fileManager;
         ImageManagement::ImageManager* _imageManager;
         Logging::ILogger* _logger;
      public:
         ExperimentManagement::ExperimentManager* GetExperimentManager() const;
         FileManagement::FileManager* GetFileManager() const;
         ImageManagement::ImageManager* GetImageManager() const;
         Logging::ILogger* GetLogger() const;

         void SetFileManager(FileManagement::FileManager*);
         void SetExperimentManager(ExperimentManagement::ExperimentManager*);
         void SetImageManager(ImageManagement::ImageManager*);
         void SetLogger(Logging::ILogger*);

         Manager();
         ~Manager();
      };
   }
}