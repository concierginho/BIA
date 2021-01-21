#ifndef _ILOGGING_MANAGER_
#define _ILOGGING_MANAGER_

#include <memory>

#include "IManager.h"
#include "ESource.h"

namespace BIA
{
   class ILoggingManager : public IManager
   {
   private:
   public:
      virtual ~ILoggingManager() = 0 {};
      virtual void Init() = 0;
      virtual void Log(ESource) = 0;
   };
}

#endif
