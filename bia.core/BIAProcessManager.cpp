#include "pch.h"
#include "BIAProcessManager.h"
#include "BIA.h"

/// <summary>
/// Cel: Wykonanie procesu BIA w sposob asynchroniczny.
/// </summary>
/// <param name="_bia"></param>
void Routine(BIA::BIA* _bia)
{
   _bia->StartBIAProcess();
}

/// <summary>
/// Domyslny konstruktor.
/// </summary>
/// <param name="bia"></param>
BIA::BIAProcessManager::BIAProcessManager(BIA* bia)
{
   _bia = bia;
   Cancelled = false;
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
/// Cel: Rozpoczecie funkcji "Routine()" w sposob asynchroniczny.
/// </summary>
void BIA::BIAProcessManager::Start()
{
#ifdef _LOGGING_
   _loggingManager->Message << "Process started.";
   _loggingManager->Log(ESource::BIA_PROCESS_MANAGER);
#endif
   Cancelled = false;
   _task = std::async(std::launch::async, &Routine, _bia);
}

/// <summary>
/// Cel: Zatrzymanie funkcji "Routine()" dzialajacej w sposob asynchroniczny.
/// </summary>
void BIA::BIAProcessManager::Stop()
{
   Cancelled = true;
   _task.get();
#ifdef _LOGGING_
   _loggingManager->Message << "Process has been cancelled.";
   _loggingManager->Log(ESource::BIA_PROCESS_MANAGER);
#endif
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
