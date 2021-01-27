
#include "pch.h"
#include "BIA.h"
#include "BIAManagerKeeper.h"

#ifdef _LOGGING_
#include "BIALoggingManager.h"
#endif
#include "EAlignment.h"

#include <future>


/// <summary>
/// Cel: Inicjalizacja BIAManagerKeeper'a, ktory odpowiada
///      za wszysktie zaleznosci w bibliotece.
///      
///      Nastepnie zostaja pobrane informacje na temat
///      katalogu glownego oraz przygotowane zostaja
///      eksperymenty (podkatalogi), znajdujace sie
///      w katalogu glownym.
/// </summary>
void BIA::BIA::Init()
{
   _keeper = new BIAManagerKeeper(_rootPath, this);

   _keeper->Init();

   _keeper->GetFileManagerAsBIAFileManager()->ScanRootDirectory();
   _keeper->GetExperimentManagerAsBIAExperimentManager()->PrepareExperiments();
}

/// <summary>
/// Cel: Rozpoczecie procesu BIA.
///      Proces uruchamiany jest w sposob asynchroniczny za pomoca BIAProcessManager'a.
///      Funkcja jest uruchamiana przez BIAProcessManager w sposob asynchroniczny.
/// </summary>
void BIA::BIA::StartBIAProcess()
{
   std::atomic<bool>& cancelled = _keeper->GetProcessManagerAsBIAProcessManager()->Cancelled;

   _keeper->GetImageManagerAsBIAImageManager()->SplitImages(cancelled);

   if (cancelled == false)
      return;

   _keeper->GetImageManagerAsBIAImageManager()->GeneratePreviews(cancelled);

   if (cancelled == false)
      return;
}

/// <summary>
/// Cel: Zatrzymanie procesu BIA.
/// </summary>
void BIA::BIA::StopBIAProcess()
{
   _keeper->GetProcessManagerAsBIAProcessManager()->Stop();
}

/// <summary>
/// Cel: Ustawienie sciezki do katalogu glownego.
/// </summary>
/// <param name="rootPath"></param>
void BIA::BIA::SetRootPath(char* rootPath)
{
   _rootPath = rootPath;
}

/// <summary>
/// Cel: Zwrocenie sciezki do katalogu glownego.
/// </summary>
/// <returns></returns>
const char* BIA::BIA::GetRootPath() const
{
   return _rootPath;
}

/// <summary>
/// Cel: Zwrocenie wskaznika do obiektu typu BIAManagerKeeper.
/// </summary>
/// <returns></returns>
BIA::BIAManagerKeeper* BIA::BIA::GetKeeper()
{
   return _keeper;
}

/// <summary>
/// Cel: Ustawienie wskaznika do obiektu typu BIAManagerKeeper.
/// </summary>
/// <param name="keeper"></param>
void BIA::BIA::SetKeeper(BIAManagerKeeper* keeper)
{
   _keeper = keeper;
}

/// <summary>
/// Domyslny konstruktor.
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

/// <summary>
/// Cel: Rozpoczecie procesu w sposob asynchroniczny.
/// </summary>
void BIA::BIA::Start()
{
   auto processManager = _keeper->GetProcessManagerAsBIAProcessManager();

   processManager->Start();
}

/// <summary>
/// Cel: Zatrzymanie asynchronicznego procesu.
/// </summary>
void BIA::BIA::Stop()
{
   auto processManager = _keeper->GetProcessManagerAsBIAProcessManager();

   processManager->Stop();
}
