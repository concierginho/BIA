#include "pch.h"
#include "BIAManagerKeeper.h"

/// <summary>
/// Funkcja zwraca smart pointer do obiektu typu BIAFileManager
/// std::dynamic_pointer_cast zostaje wykorzystany, poniewaz
/// _fileManager jest przechowywany jako obiekt typu IFileManager
/// </summary>
std::shared_ptr<BIA::BIAFileManager> BIA::BIAManagerKeeper::GetFileManagerAsBIAFileManager()
{
   return std::dynamic_pointer_cast<BIAFileManager>(_fileManager);
}

/// <summary>
/// Funkcja zwraca smart pointer do obiektu typu BIAExperimentManager
/// std::dynamic_pointer_cast zostaje wykrzystany, poniewaz
/// _experimentManager jest przechowywany jako obiekt typu IExperimentManager
/// </summary>
std::shared_ptr<BIA::BIAExperimentManager> BIA::BIAManagerKeeper::GetExperimentManagerAsBIAExperimentManager()
{
   return std::dynamic_pointer_cast<BIAExperimentManager>(_experimentManager);
}

/// <summary>
/// Funkcja zwraca smart pointer do obiektu typu BIAImageManager
/// std::dynamic_pointer_cast zostaje wykorzystany, poniewaz
/// _imageManager jest przechowywany jako obiekt typu IImageManager
/// </summary>
std::shared_ptr<BIA::BIAImageManager> BIA::BIAManagerKeeper::GetImageManagerAsBIAImageManager()
{
   return std::dynamic_pointer_cast<BIAImageManager>(_imageManager);
}

#ifdef _LOGGING_
/// <summary>
/// Funkcja zwraca smart pointer do obiektu typu BIALoggingManager
/// std::dynamic_pointer_cast zostaje wykorzystany, poniewaz
/// _loggingManager jest przechowywany jako obiekt typu ILoggingManager
/// </summary>
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

/// <summary>
/// Funkcja inicjalizujace w odpowiedni sposob glowne klasy odpowiadajace
/// za poszczegolne funkcjonalnosci. W zaleznosci od tego czy _LOGGING_
/// zostal zdefiniowany, obiekty inicjalizowane sa w rozny sposob.
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
