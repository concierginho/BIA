#include "pch.h"
#include "BIA.h"
#include "BIAManagerKeeper.h"

#ifdef _LOGGING_
#include "BIALoggingManager.h"
#endif
#include "EAlignment.h"

/// <summary>
/// Funkcja inicjalizujace BIAManagerKeeper'a, ktory odpowiedzialny jest
/// za inicjalizacje glownych klas. Klasy te odpowiadaja za poszczegolne
/// funkcjonalnosci. Np. BIAImageManager, BIAFileManager.
/// </summary>
void BIA::BIA::Init()
{
   _keeper = new BIAManagerKeeper(_rootPath);

   _keeper->Init();
}

/// <summary>
/// Funkcja rozpoczynajaca caly proces.
/// 
/// 1. Skanowanie zawartosci folderu podanego podczas inicjalizacji obiektu typu BIA
/// 2. Przygotowanie eksperymentow (przez eksperyment nalezy rozumiec podkatalog
///    glownego katalogu).
/// 3. Podzielenie obrazow na 40 obrazow skladowych.
/// 4. Wygenerowanie zbinaryzowanych obrazow.
/// </summary>
void BIA::BIA::StartProcess()
{
   auto biaFileManager = _keeper->GetFileManagerAsBIAFileManager();
   auto biaImageManager = _keeper->GetImageManagerAsBIAImageManager();
   auto biaExperimentManager = _keeper->GetExperimentManagerAsBIAExperimentManager();

   biaFileManager->ScanRootDirectory();
   biaExperimentManager->PrepareExperiments();
   biaImageManager->SplitImages();
   biaImageManager->GeneratePreviews();
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
/// Glowny konstruktor klasy BIA.
/// </summary>
/// <param name="rootPath"></param>
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
