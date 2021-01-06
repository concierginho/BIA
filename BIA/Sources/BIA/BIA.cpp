#include "../../Public/BIA.h"
#include "../ExperimentManagement/ExperimentManager.h"
#include "../FileManagement/FileManager.h"
#include "../Logger/ConsoleLogger.h"
#include "../Logger/FileLogger.h"

#define _FILE_LOGGING_

namespace BIA
{
   BIA::BIA(std::string rootPath) : _rootPath(rootPath)
   {
      InitializeComponents();
   }

   BIA::~BIA()
   {
      delete _logger;
      _logger = nullptr;

      delete _fileManager;
      _fileManager = nullptr;

      delete _experimentManager;
      _experimentManager = nullptr;

      delete _imageManager;
      _imageManager = nullptr;
   }

   void BIA::InitializeComponents()
   {
#ifdef _LOGGING_
   #ifdef _FILE_LOGGING_
      _logger = new Logging::FileLogger(_rootPath);
   #else
      _logger = new Logging::ConsoleLogger();
   #endif
#endif
      _fileManager = new FileManagement::FileManager(_rootPath, _logger);
      _experimentManager = new ExperimentManagement::ExperimentManager(_fileManager, _logger);
      _imageManager = new ImageManagement::ImageManager(_logger);
   }

   void BIA::PrepareProcess()
   {
      _fileManager->ScanDirectory();
      _experimentManager->PrepareExperiments();
   }

   std::string& BIA::GetRootPath() const
   {
      return _rootPath;
   }

   FileManagement::FileManager* BIA::GetFileManager() const
   {
      return _fileManager;
   }

   ExperimentManagement::ExperimentManager* BIA::GetExperimentManager() const
   {
      return _experimentManager;
   }

   ImageManagement::ImageManager* BIA::GetImageManager() const
   {
      return _imageManager;
   }
}
