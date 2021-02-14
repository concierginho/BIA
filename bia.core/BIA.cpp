#include "pch.h"
#include "BIA.h"
#include "BIAManagerKeeper.h"
#include "BIAExperimentManager.h"
#include "BIAProcessManager.h"
#include "BIAImageManager.h"

#ifdef _LOGGING_
#include "BIALoggingManager.h"
#endif
#include "EAlignment.h"

#include <future>
#include <memory>

/// <summary>
/// Cel: Inicjalizacja BIAManagerKeeper'a, ktory odpowiada
///      za wszysktie zaleznosci w bibliotece.
///      Nastepnie zostaja pobrane informacje na temat
///      katalogu glownego, a pozniej przygotowywane sa
///      eksperymenty (podkatalogi), znajdujace sie
///      w katalogu glownym.
/// </summary>
void BIA::BIA::Init()
{
   _keeper = new BIAManagerKeeper(_rootPath, this);

   _keeper->Init();

   std::dynamic_pointer_cast<BIAFileManager>(_keeper->GetFileManager())->ScanRootDirectory();
   std::dynamic_pointer_cast<BIAExperimentManager>(_keeper->GetExperimentManager())->PrepareExperiments();
}

/// <summary>
/// Cel: Rozpoczecie procesu BIA.
///      Proces uruchamiany jest w sposob asynchroniczny za pomoca BIAProcessManager'a.
///      Funkcja jest uruchamiana przez BIAProcessManager w sposob asynchroniczny.
/// </summary>
void BIA::BIA::PrepareRoutine()
{
   auto biaProcessManager = std::dynamic_pointer_cast<BIAProcessManager>(_keeper->GetProcessManager());

   std::atomic<bool>& cancelled = biaProcessManager->Cancelled;
   std::atomic<int>& biaProgress = biaProcessManager->BiaProgress;

   biaProgress = 0;
   biaProcessManager->BiaProgressCapacity = GetExperimentManager()->GetExperiments().size() * 80 * 2;

   auto biaImageManager = std::dynamic_pointer_cast<BIAImageManager>(_keeper->GetImageManager());

   biaImageManager->SplitImages(cancelled, biaProgress);

   if (cancelled == true)
      return;

   biaImageManager->GeneratePreviews(cancelled, biaProgress);

   if (cancelled == true)
      return;

#ifdef _LOGGING_
   auto biaLoggingManager = std::dynamic_pointer_cast<BIALoggingManager>(_keeper->GetLoggingManager());
   biaLoggingManager->Message << "Process has finished.";
   biaLoggingManager->Log(ESource::BIA_EXPERIMENT_MANAGER);
#endif
   biaProgress = 100000;
}

/// <summary>
/// Cel: Uruchomienie algorytmow, ktore beda dzialac na poszczegolnych obrazach.
/// </summary>
void BIA::BIA::OperationRoutine()
{
   auto biaProcessManager = std::dynamic_pointer_cast<BIAProcessManager>(_keeper->GetProcessManager());
   auto biaImageManager = std::dynamic_pointer_cast<BIAImageManager>(_keeper->GetImageManager());

   std::atomic<bool>& cancelled = biaProcessManager->Cancelled;
   std::atomic<int>& operationProgress = biaProcessManager->OperationProgress;

   biaProcessManager->OperationProgressCapacity = GetExperimentManager()->GetExperiments().size() * 80;

   biaImageManager->PerformOperations(cancelled, operationProgress);

   if (cancelled == true)
      return;

#ifdef _LOGGING_
   auto biaLoggingManager = std::dynamic_pointer_cast<BIALoggingManager>(_keeper->GetLoggingManager());
   biaLoggingManager->Message << "Process has finished.";
   biaLoggingManager->Log(ESource::BIA_EXPERIMENT_MANAGER);
#endif
   operationProgress = 100000;
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
/// 
/// </summary>
/// <returns></returns>
BIA::IExperimentManager* BIA::BIA::GetExperimentManager()
{
   return _keeper->GetExperimentManager().get();
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
BIA::IProcessManager* BIA::BIA::GetProcessManager()
{
   return _keeper->GetProcessManager().get();
}

/// <summary>
/// Cel: Zwrocenie wskaznika do obiektu typu Experiment na podstawie jego nazwy.
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
BIA::Experiment* BIA::BIA::GetExperiment(const char* name)
{
   return std::dynamic_pointer_cast<BIAExperimentManager>(_keeper->GetExperimentManager())->GetExperiment(name);
}

/// <summary>
/// Cel: Zwrocenie wskaznika do obiektu typu PartExperiment na podstawie nazwy eksperymentu,
///      id eksperymentu czesciowego, oraz tego czy chcemy go pobrac z folderu vertical czy
///      horizontal. 
///   isHorizontal = true - oznacza wykorzystanie folderu horizontal.
///   isHorizontal = false - oznacza wykorzystnaie folderu vertical.
/// </summary>
/// <param name="name"></param>
/// <param name="id"></param>
/// <param name="isHorizontal"></param>
/// <returns></returns>
BIA::PartExperiment* BIA::BIA::GetPartExperiment(const char* name, int id, bool isHorizontal)
{
   EFolder type = EFolder::HORIZONTAL;
   if (isHorizontal)
      type = EFolder::VERTICAL;

   auto biaExperimentManager = std::dynamic_pointer_cast<BIAExperimentManager>(_keeper->GetExperimentManager());
   return biaExperimentManager->GetExperiment(name)->GetPartExperimentById(type, id);
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
/// Destruktor.
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
void BIA::BIA::Start(EProcess eprocess)
{
   auto processManager = std::dynamic_pointer_cast<BIAProcessManager>(_keeper->GetProcessManager());

   processManager->Start(eprocess);
}

/// <summary>
/// Cel: Zatrzymanie asynchronicznego procesu.
/// </summary>
void BIA::BIA::Stop()
{
   auto processManager = std::dynamic_pointer_cast<BIAProcessManager>(_keeper->GetProcessManager());

   processManager->Stop();
}