#ifndef _IEXPERIMENT_MANAGER_
#define _IEXPERIMENT_MANAGER_

#include "IManager.h"

namespace BIA
{
   class IExperimentManager : public IManager
   {
   public:
      virtual ~IExperimentManager() = 0 {};
      virtual void Init() = 0;
   };
}

#endif
