#include "pch.h"
#include "BIAProcessManager.h"
#include "BIA.h"

/// <summary>
/// Cel: Wykonanie procesu 'BIA' w sposob asynchroniczny.
/// </summary>
/// <param name="_bia"></param>
void BIARoutine(BIA::BIA* bia)
{
   bia->PrepareRoutine();
}

/// <summary>
/// Cel: Wykonanie procesu 'Operations' w sposob asynchroniczny.
/// </summary>
/// <param name="bia"></param>
void OperationsRoutine(BIA::BIA* bia)
{
   bia->OperationRoutine();
}

/// <summary>
/// Domyslny konstruktor.
/// </summary>
/// <param name="bia"></param>
BIA::BIAProcessManager::BIAProcessManager(BIA* bia)
{
   _bia = bia;
   Cancelled = false;
   Stopped = false;
}

#ifdef _LOGGING_
/// <summary>
/// Konstruktor wykorzystywany jezeli _LOGGING_ zostalo wczesniej zdefiniowane.
/// </summary>
/// <param name="bia"></param>
/// <param name="loggingManager"></param>
BIA::BIAProcessManager::BIAProcessManager(BIA* bia, std::shared_ptr<BIALoggingManager> loggingManager)
{
   _bia = bia;
   _loggingManager = loggingManager;
   Cancelled = false;
   Stopped = false;
}

/// <summary>
/// Cel: Zwrocenie obecnego postepu operacji PreopareRoutine
/// </summary>
/// <returns></returns>
std::atomic<int>& BIA::BIAProcessManager::GetBiaProgress()
{
   return BiaProgress;
}

/// <summary>
/// Cel: Zwrocenie obecnego postepu operacji OperationRotuine.
/// </summary>
/// <returns></returns>
std::atomic<int>& BIA::BIAProcessManager::GetOperationProgress()
{
   return OperationProgress;
}

/// <summary>
/// Cel: Zwrocenie sumy operacji, ktore beda wykonywnae przez PrepareRotuine.
/// </summary>
/// <returns></returns>
int BIA::BIAProcessManager::GetBiaProgressCapacity()
{
   return BiaProgressCapacity;
}

/// <summary>
/// Cel: Zwrocenie sumy operacji, ktore beda wykonywane przez OperationRoutine.
/// </summary>
/// <returns></returns>
int BIA::BIAProcessManager::GetOperationProgressCapacity()
{
   return OperationProgressCapacity;
}
#endif

/// <summary>
/// Destruktor.
/// </summary>
BIA::BIAProcessManager::~BIAProcessManager()
{
   _bia = nullptr;
}

/// <summary>
/// Cel: Rozpoczecie funkcji 'BIARoutine()' lub 'OperationsRoutine()'
///      w zaleznosci od argumentu, w sposob asynchroniczny.
/// </summary>
void BIA::BIAProcessManager::Start(EProcess process)
{
#ifdef _LOGGING_
   _loggingManager->Message << "Process started:";
   _loggingManager->Log(ESource::BIA_PROCESS_MANAGER);
#endif

   Cancelled = false;
   BiaProgress = 0;
   OperationProgress = 0;

   switch (process)
   {
      case EProcess::BIAPROCESS:
#ifdef _LOGGING_
         _loggingManager->Message << " --  PREPARING PROCESS.";
         _loggingManager->Log(ESource::BIA_PROCESS_MANAGER);
#endif
         _task = std::async(std::launch::async, &BIARoutine, _bia);
         break;
      case EProcess::BIAOPERATIONS:
#ifdef _LOGGING_
         _loggingManager->Message << " -- PERFORMING OPERATIONS.";
         _loggingManager->Log(ESource::BIA_PROCESS_MANAGER);
#endif
         _task = std::async(std::launch::async, &OperationsRoutine, _bia);
         break;
   }
}

/// <summary>
/// Cel: Zatrzymanie funkcji 'BIARoutine()' lub 'OperationsRoutine()'
///      dzialajacej w sposob asynchroniczny.
/// </summary>
void BIA::BIAProcessManager::Stop()
{
   if (Stopped == false)
   {
      Cancelled = true;
      _task.get();
      Stopped = true;
      BiaProgress = 0;
      OperationProgress = 0;

#ifdef _LOGGING_
      _loggingManager->Message << "Process has been cancelled.";
      _loggingManager->Log(ESource::BIA_PROCESS_MANAGER);
#endif
   }
}

/// <summary>
/// Cel: Inicjalizacja.
/// </summary>
void BIA::BIAProcessManager::Init()
{
#ifdef _LOGGING_
   _loggingManager->Message << "Initializing BIAProcessManager...";
   _loggingManager->Log(ESource::BIA_PROCESS_MANAGER);
#endif
}
