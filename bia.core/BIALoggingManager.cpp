#include "pch.h"
#include "BIALoggingManager.h"
#include "BIAFileManager.h"
#include "FileLogger.h"

std::stringstream BIA::BIALoggingManager::Message;

/// <summary>
/// Cel: Ustawienie wartosci zmiennej 'Message' na pusty lancuch znakow.
/// </summary>
void BIA::BIALoggingManager::Flush()
{
   Message.str(std::string());
}

/// <summary>
/// Domyslny konstruktor.
/// </summary>
/// <param name="type"></param>
/// <param name="fileManager"></param>
BIA::BIALoggingManager::BIALoggingManager(EType type, std::shared_ptr<BIA::IFileManager> fileManager)
{
   _fileManager = fileManager;

   auto tmp = std::dynamic_pointer_cast<BIAFileManager>(fileManager);

   _rootPath = tmp->GetRootPath();

   switch (type)
   {
      case EType::FileLogger:
         _logger = std::make_shared<FileLogger>(_rootPath, _fileManager);
         break;
   }
}

/// <summary>
/// Destruktor.
/// </summary>
BIA::BIALoggingManager::~BIALoggingManager()
{
}

/// <summary>
/// Cel: Wypisanie wartosci zapisanej w zmiennej 'Message'
///      do miejsca docelowego.
/// </summary>
/// <param name="source"></param>
void BIA::BIALoggingManager::Log(ESource source)
{
   _logger->Log(source, Message);
   Flush();
}

/// <summary>
/// Cel: Inicjalizacja.
/// </summary>
void BIA::BIALoggingManager::Init()
{
   _logger->Prepare();
   Flush();
}
