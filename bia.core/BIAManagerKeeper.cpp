#include "pch.h"
#include "BIAManagerKeeper.h"

std::shared_ptr<BIA::BIAFileManager> BIA::BIAManagerKeeper::GetFileManagerAsBIAFileManager()
{
   return std::dynamic_pointer_cast<BIAFileManager>(_fileManager);
}

std::shared_ptr<BIA::BIAExperimentManager> BIA::BIAManagerKeeper::GetExperimentManagerAsBIAExperimentManager()
{
   return std::dynamic_pointer_cast<BIAExperimentManager>(_experimentManager);
}

std::shared_ptr<BIA::BIAImageManager> BIA::BIAManagerKeeper::GetImageManagerAsBIAImageManager()
{
   return std::dynamic_pointer_cast<BIAImageManager>(_imageManager);
}

#ifdef _LOGGING_
std::shared_ptr<BIA::BIALoggingManager> BIA::BIAManagerKeeper::GetLoggingManagerAsBIALoggingMenager()
{
   return std::dynamic_pointer_cast<BIALoggingManager>(_loggingManager);
}
#endif

std::string BIA::BIAManagerKeeper::GetRootPath()
{
   return _rootPath;
}

BIA::BIAManagerKeeper::BIAManagerKeeper(char* rootPath)
{
   _rootPath = std::string(rootPath);
}

BIA::BIAManagerKeeper::~BIAManagerKeeper()
{
}

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

#else
   _experimentManager = std::make_shared<BIAExperimentManager>(GetFileManagerAsBIAFileManager());
   _imageManager = std::make_shared<BIAImageManager>();
#endif

   _managers =
   {
#ifdef _LOGGING_
      _loggingManager,
#endif
      _fileManager,
      _experimentManager,
      _imageManager
   };

   for (const auto& manager : _managers)
      manager->Init();
}
