#pragma once
#define WIN32_LEAN_AND_MEAN

#include <string>

#include "../Sources/FileManagement/FileManager.h"
#include "../Sources/ExperimentManagement/ExperimentManager.h"
#include "../Sources/ImageManagement/ImageManager.h"

namespace BIA
{
   class BIA
   {
   private:
      std::string& _rootPath;
      Logging::ILogger* _logger;
      FileManagement::FileManager* _fileManager;
      ExperimentManagement::ExperimentManager* _experimentManager;
      ImageManagement::ImageManager* _imageManager;

      void InitializeComponents();
   public:
      void PrepareProcess();

      std::string& GetRootPath() const;
      FileManagement::FileManager* GetFileManager() const;
      ExperimentManagement::ExperimentManager* GetExperimentManager() const;
      ImageManagement::ImageManager* GetImageManager() const;

      BIA(std::string rootPath);
      ~BIA();
   };
}