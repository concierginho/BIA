#ifndef _BIA_PROCESS_MANAGER_
#define _BIA_PROCESS_MANAGER_

#include "IProcessManager.h"
#include "BIALoggingManager.h"
#include "EProcess.h"
#include <future>

namespace BIA
{
   class BIA;
   class BIAProcessManager : public IProcessManager
   {
   private:
#ifdef _LOGGING_
      std::shared_ptr<BIALoggingManager> _loggingManager;
#endif
      BIA* _bia;
      std::future<void> _task;
   public:
      std::atomic<bool> Cancelled;
      std::atomic<bool> Stopped;

      void Start(EProcess);
      void Stop();

      virtual void Init() override;

      BIAProcessManager(BIA* bia);
      ~BIAProcessManager();
#ifdef _LOGGING_
      BIAProcessManager(BIA* bia, std::shared_ptr<BIALoggingManager> loggingManager);
#endif
   };
}

#endif
