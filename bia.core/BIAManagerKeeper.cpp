#include "pch.h"
#include "BIAManagerKeeper.h"

#include "BIAFileManager.h"
#include "BIAExperimentManager.h"
#include "BIAImageManager.h"
#include "BIAProcessManager.h"
#include "BIALoggingManager.h"

/// <summary>
/// Cel: Zwrocenie FileManager'a.
/// </summary>
/// <returns></returns>
std::shared_ptr<BIA::IFileManager> BIA::BIAManagerKeeper::GetFileManager()
{
   return _fileManager;
}

/// <summary>
/// Cel: Zwrocenie Experiment Manager'a.
/// </summary>
/// <returns></returns>
std::shared_ptr<BIA::IExperimentManager> BIA::BIAManagerKeeper::GetExperimentManager()
{
    return _experimentManager;
}

/// <summary>
/// Cel: Zwrocenie ImageManager'a.
/// </summary>
/// <returns></returns>
std::shared_ptr<BIA::IImageManager> BIA::BIAManagerKeeper::GetImageManager()
{
    return _imageManager;
}

/// <summary>
/// Cel: Zwrocenie ProcessManager'a.
/// </summary>
/// <returns></returns>
std::shared_ptr<BIA::IProcessManager> BIA::BIAManagerKeeper::GetProcessManager()
{
    return _processManager;
}

/// <summary>
/// Cel: Zwrocenie LoggingManager'a.
/// </summary>
/// <returns></returns>
std::shared_ptr<BIA::ILoggingManager> BIA::BIAManagerKeeper::GetLoggingManager()
{
   return _loggingManager;
}

/// <summary>
/// Cel: Zwrocenie sciezki do katalogu glownego.
/// </summary>
/// <returns></returns>
std::string BIA::BIAManagerKeeper::GetRootPath()
{
   return _rootPath;
}

/// <summary>
/// Domyslny konstruktor.
/// </summary>
/// <param name="rootPath"></param>
/// <param name="bia"></param>
BIA::BIAManagerKeeper::BIAManagerKeeper(char* rootPath, BIA* bia)
{
   _rootPath = std::string(rootPath);
   _bia = bia;
}

/// <summary>
/// Destruktor.
/// </summary>
BIA::BIAManagerKeeper::~BIAManagerKeeper()
{
}

/// <summary>
/// Cel: Inicjalizacja wszystkich zaleznosci w zaleznosci od tego
///      czy _LOGGING_ zostalo zdefiniowane.
/// </summary>
void BIA::BIAManagerKeeper::Init()
{
   _fileManager = std::make_shared<BIAFileManager>(_rootPath);

#ifdef _LOGGING_
#ifdef _FILE_LOGGING_
   _loggingManager = std::make_shared<BIALoggingManager>(EType::FileLogger, _fileManager);
#else
   _loggingManager = std::make_shared<BIALoggingManager>(EType::ConsoleLogger, rootPath);
#endif

   auto loggingManager = std::dynamic_pointer_cast<BIALoggingManager>(_loggingManager);
   auto fileManager = std::dynamic_pointer_cast<BIAFileManager>(_fileManager);

   fileManager->SetLoggingManager(loggingManager);

   _experimentManager = std::make_shared <BIAExperimentManager>(fileManager, loggingManager);

   auto experimentManager = std::dynamic_pointer_cast<BIAExperimentManager>(_experimentManager);

   _imageManager = std::make_shared<BIAImageManager>(experimentManager, loggingManager);
   _processManager = std::make_shared<BIAProcessManager>(_bia, loggingManager);
#else
   auto fileManager = GetFileManagerAsBIAFileManager();

   _experimentManager = std::make_shared<BIAExperimentManager>(fileManager);
   
   auto experimentManager = GetExperimentManagerAsBIAExperimentManager();

   _imageManager = std::make_shared<BIAImageManager>(experimentManager, fileManager);
   _processManager = std::make_shared<BIAProcessManager>(_bia);
#endif

   _managers =
   {
#ifdef _LOGGING_
      _loggingManager,
#endif
      _fileManager,
      _experimentManager,
      _imageManager,
      _processManager
   };

   for (const auto& manager : _managers)
      manager->Init();
}
