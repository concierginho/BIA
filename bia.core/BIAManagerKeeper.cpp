#include "pch.h"
#include "BIAManagerKeeper.h"

/// <summary>
/// Cel: Dynamiczne rzutowanie obiektu typu std::shared_ptr<IFileManager>
///      do typu std::shared_ptr<BIAFileManager>.
/// </summary>
/// <returns></returns>
std::shared_ptr<BIA::BIAFileManager> BIA::BIAManagerKeeper::GetFileManagerAsBIAFileManager()
{
   return std::dynamic_pointer_cast<BIAFileManager>(_fileManager);
}

/// <summary>
/// Cel: Dynamiczne rzutowanie obiektu typu std::shared_ptr<IExperimentManager>
///      do typu std::shared_ptr<BIAExperimentManager>.
/// </summary>
/// <returns></returns>
std::shared_ptr<BIA::BIAExperimentManager> BIA::BIAManagerKeeper::GetExperimentManagerAsBIAExperimentManager()
{
   return std::dynamic_pointer_cast<BIAExperimentManager>(_experimentManager);
}

/// <summary>
/// Cel: Dynamiczne rzutowanie obiektu typu std::shared_ptr<IImageManager>
///      do typu std::shared_ptr<BIAImageManager>.
/// </summary>
/// <returns></returns>
std::shared_ptr<BIA::BIAImageManager> BIA::BIAManagerKeeper::GetImageManagerAsBIAImageManager()
{
   return std::dynamic_pointer_cast<BIAImageManager>(_imageManager);
}

/// <summary>
/// Cel: Dynamiczne rzutowanie obiektu typu std::shared_ptr<IProcessManager>
///      do typu std::shared_ptr<BIAProcessManager>.
/// </summary>
/// <returns></returns>
std::shared_ptr<BIA::BIAProcessManager> BIA::BIAManagerKeeper::GetProcessManagerAsBIAProcessManager()
{
   return std::dynamic_pointer_cast<BIAProcessManager>(_processManager);
}

#ifdef _LOGGING_
/// <summary>
/// Cel: Dynamiczne rzutowanie obiektu typu std::shared_ptr<ILoggingManager>
///      do typu std::shared_ptr<BIALoggingManager>.
/// </summary>
/// <returns></returns>
std::shared_ptr<BIA::BIALoggingManager> BIA::BIAManagerKeeper::GetLoggingManagerAsBIALoggingMenager()
{
   return std::dynamic_pointer_cast<BIALoggingManager>(_loggingManager);
}
#endif

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

   auto loggingManager = GetLoggingManagerAsBIALoggingMenager();
   auto fileManager = GetFileManagerAsBIAFileManager();

   fileManager->SetLoggingManager(loggingManager);

   _experimentManager = std::make_shared <BIAExperimentManager>(fileManager, loggingManager);

   auto experimentManager = GetExperimentManagerAsBIAExperimentManager();

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
