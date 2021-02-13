#ifndef _IEXPERIMENT_MANAGER_
#define _IEXPERIMENT_MANAGER_

#include "IManager.h"
#include "EOperation.h"

namespace BIA
{
   class IExperimentManager : public IManager
   {
   public:
      virtual ~IExperimentManager() = 0 {};
      virtual void Init() = 0;
      virtual bool AddOperation(const char* name, int id, bool isHorizontal, EOperation operation, const char* args) = 0;
   };
}

#endif
