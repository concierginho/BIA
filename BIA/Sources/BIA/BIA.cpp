#include "../../Public/BIA.h"
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
      _fileManager = new FileManagement::FileManager(_rootPath, logger);
   }

   std::string& BIA::GetRootPath() const
   {
      return _rootPath;
   }

   void BIA::SetRootPath(std::string& rootPath)
   {
      _rootPath = rootPath;
   }
   
   FileManagement::FileManager* BIA::GetFileManager() const
   {
      return nullptr;
   }
}
