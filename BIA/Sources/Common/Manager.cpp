#include "Manager.h"

namespace BIA
{
   namespace Management
   {
      Manager::Manager()
      {
         _fileManager = nullptr;
         _experimentManager = nullptr;
         _imageManager = nullptr;
         _logger = nullptr;
      }

      Manager::~Manager()
      {
         if(_fileManager != nullptr)
            delete _fileManager;
         _fileManager = nullptr;

         if(_experimentManager != nullptr)
            delete _experimentManager;
         _experimentManager = nullptr;

         if(_imageManager != nullptr)
            delete _imageManager;
         _imageManager = nullptr;

         if (_logger != nullptr)
            delete _logger;
         _logger = nullptr;
      }

      ExperimentManagement::ExperimentManager* Manager::GetExperimentManager() const
      {
         return _experimentManager;
      }

      FileManagement::FileManager* Manager::GetFileManager() const
      {
         return _fileManager;
      }

      ImageManagement::ImageManager* Manager::GetImageManager() const
      {
         return _imageManager;
      }
      
      Logging::ILogger* Manager::GetLogger() const
      {
         return _logger;
      }

      void Manager::SetExperimentManager(ExperimentManagement::ExperimentManager* experimentManager)
      {
         _experimentManager = experimentManager;
      }

      void Manager::SetFileManager(FileManagement::FileManager* fileManager)
      {
         _fileManager = fileManager;
      }
      
      void Manager::SetImageManager(ImageManagement::ImageManager* imageManager)
      {
         _imageManager = imageManager;
      }

      void Manager::SetLogger(Logging::ILogger* logger)
      {
         _logger = logger;
      }
   }
}