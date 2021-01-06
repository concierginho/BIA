#include "../../Public/BIA.h"
#include "../ExperimentManagement/ExperimentManager.h"
#include "../FileManagement/FileManager.h"
#include "../Logger/ConsoleLogger.h"
#include "../Logger/FileLogger.h"

namespace BIA
{
   BIA::BIA(std::string rootPath) : _rootPath(rootPath)
   {
      InitializeComponents();
   }

   BIA::~BIA()
   {
   }

   void BIA::InitializeComponents()
   {
      Logger::ILogger* logger = nullptr;
#ifdef _LOGGING_
   #ifdef _FILE_LOGGING_
      logger = new Logger::FileLogger();
   #else
      logger = new Logger::ConsoleLogger();
   #endif
#endif
      _experimentManager = new ExperimentManagement::ExperimentManager(logger);
      _fileManager = new FileManagement::FileManager(_rootPath, logger);
   }

   void BIA::PrepareProcess()
   {
      _fileManager->ScanDirectory();
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
}
