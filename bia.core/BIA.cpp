
#include "pch.h"
#include "BIA.h"
#include "BIAManagerKeeper.h"

#ifdef _LOGGING_
#include "BIALoggingManager.h"
#endif
#include "EAlignment.h"

#include <future>

/// <summary>
/// Funkcja inicjalizujace BIAManagerKeeper'a, ktory odpowiedzialny jest
/// za inicjalizacje glownych klas. Klasy te odpowiadaja za poszczegolne
/// funkcjonalnosci. Np. BIAImageManager, BIAFileManager.
/// 
/// 1. Skanowanie zawartosci folderu podanego podczas inicjalizacji obiektu typu BIA
/// 2. Przygotowanie eksperymentow (przez eksperyment nalezy rozumiec podkatalog
///    glownego katalogu).
/// 3. Podzielenie obrazow na 40 obrazow skladowych.
/// </summary>
void BIA::BIA::Init()
{
   _keeper = new BIAManagerKeeper(_rootPath, this);

   _keeper->Init();

   _keeper->GetFileManagerAsBIAFileManager()->ScanRootDirectory();
   _keeper->GetExperimentManagerAsBIAExperimentManager()->PrepareExperiments();
}

/// <summary>
/// Funkcja rozpoczynajaca caly proces.
/// 
/// 1. Binaryzacja obrazów na podstawie ustawien pobranych z pliku 'recipe.json'.
/// </summary>
void BIA::BIA::StartProcess()
{
   std::atomic<bool>& running = _keeper->GetProcessManagerAsBIAProcessManager()->Running;

   _keeper->GetImageManagerAsBIAImageManager()->SplitImages(running);

   if (running == false)
      return;

   _keeper->GetImageManagerAsBIAImageManager()->GeneratePreviews(running);

   if (running == false)
      return;
}

/// <summary>
/// 
/// </summary>
void BIA::BIA::StopProcess()
{
   _keeper->GetProcessManagerAsBIAProcessManager()->Stop();
}

/// <summary>
/// Funckja pozwalajaca na ustawienie sciezki katalogu glownego.
/// </summary>
void BIA::BIA::SetRootPath(char* rootPath)
{
   _rootPath = rootPath;
}

/// <summary>
/// Funkcja zwraca sciezke katalogu glownego.
/// </summary>
/// <returns></returns>
const char* BIA::BIA::GetRootPath() const
{
   return _rootPath;
}

/// <summary>
/// 
/// </summary>
BIA::BIAManagerKeeper* BIA::BIA::GetKeeper()
{
   return _keeper;
}

/// <summary>
/// 
/// </summary>
void BIA::BIA::SetKeeper(BIAManagerKeeper* keeper)
{
   _keeper = keeper;
}

/// <summary>
/// Glowny konstruktor klasy BIA.
/// </summary>
BIA::BIA::BIA(char* rootPath)
{
   _rootPath = rootPath;
   _keeper = nullptr;
}

/// <summary>
/// Destruktor
/// </summary>
BIA::BIA::~BIA()
{
   if(!_rootPath)
      delete _rootPath;
   _rootPath = nullptr;

   if (!_keeper)
      delete _keeper;
   _keeper = nullptr;
}

void BIA::BIA::Start()
{
   auto processManager = _keeper->GetProcessManagerAsBIAProcessManager();

   processManager->Start();
}

void BIA::BIA::Stop()
{
   auto processManager = _keeper->GetProcessManagerAsBIAProcessManager();

   processManager->Stop();
}
