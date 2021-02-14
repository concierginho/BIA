#ifndef _IPROCESS_MANAGER_
#define _IPROCESS_MANAGER_

#include "IManager.h"

#include <atomic>

namespace BIA
{
   class IProcessManager : public IManager
   {
   public:
      virtual void Init() = 0;
      virtual ~IProcessManager() = 0 {};

      virtual std::atomic<int>& GetBiaProgress() = 0;
      virtual std::atomic<int>& GetOperationProgress() = 0;
      virtual int GetBiaProgressCapacity() = 0;
      virtual int GetOperationProgressCapacity() = 0;
   };
}

#endif
