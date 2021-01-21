#include "pch.h"
#include "BIALoggingManager.h"
#include "BIAFileManager.h"
#include "ConsoleLogger.h"
#include "FileLogger.h"

std::stringstream BIA::BIALoggingManager::Message;

void BIA::BIALoggingManager::Flush()
{
   Message.str(std::string());
}

BIA::BIALoggingManager::BIALoggingManager(EType type, std::shared_ptr<BIA::IFileManager> fileManager)
{
   _fileManager = fileManager;

   auto tmp = std::dynamic_pointer_cast<BIAFileManager>(fileManager);

   _rootPath = tmp->GetRootPath();

   switch (type)
   {
      case EType::ConsoleLogger:
         _logger = std::make_shared<ConsoleLogger>();
         break;
      case EType::FileLogger:
         _logger = std::make_shared<FileLogger>(_rootPath, _fileManager);
         break;
   }
}

BIA::BIALoggingManager::~BIALoggingManager()
{
}

void BIA::BIALoggingManager::Log(ESource source)
{
   _logger->Log(source, Message);
   Flush();
}

void BIA::BIALoggingManager::Init()
{
   _logger->Prepare();
   Flush();
}
