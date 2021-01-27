#ifndef _IPROCESS_MANAGER_
#define _IPROCESS_MANAGER_

#include "IManager.h"

namespace BIA
{
   class IProcessManager : public IManager
   {
   public:
      virtual void Init() = 0;
      virtual ~IProcessManager() = 0 {};
   };
}

#endif
