#include "pch.h"
#include "BIAProcessManager.h"
#include "BIA.h"

void Routine(BIA::BIA* _bia)
{
   _bia->StartBIAProcess();
}

BIA::BIAProcessManager::BIAProcessManager(BIA* bia)
{
   _bia = bia;
   Cancelled = false;
}

BIA::BIAProcessManager::BIAProcessManager(BIA* bia, std::shared_ptr<BIALoggingManager> loggingManager)
{
   _bia = bia;
   _loggingManager = loggingManager;
   Cancelled = false;
}

BIA::BIAProcessManager::~BIAProcessManager()
{
   _bia = nullptr;
}

void BIA::BIAProcessManager::Start()
{
#ifdef _LOGGING_
   _loggingManager->Message << "Process started.";
   _loggingManager->Log(ESource::BIA_PROCESS_MANAGER);
#endif
   Cancelled = false;
   _task = std::async(std::launch::async, &Routine, _bia);
}

void BIA::BIAProcessManager::Stop()
{
   Cancelled = true;
   _task.get();
#ifdef _LOGGING_
   _loggingManager->Message << "Process has been cancelled.";
   _loggingManager->Log(ESource::BIA_PROCESS_MANAGER);
#endif
}

void BIA::BIAProcessManager::Init()
{
#ifdef _LOGGING_
   _loggingManager->Message << "Initializing BIAProcessManager...";
   _loggingManager->Log(ESource::BIA_PROCESS_MANAGER);
#endif
}
