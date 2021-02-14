#ifndef _IEXPERIMENT_MANAGER_
#define _IEXPERIMENT_MANAGER_

#include "IManager.h"
#include "EOperation.h"
#include "Experiment.h"
#include "PartExperiment.h"

namespace BIA
{
   class IExperimentManager : public IManager
   {
   public:
      virtual ~IExperimentManager() = 0 {};
      virtual void Init() = 0;
      virtual bool AddOperation(const char* name, int id, bool isHorizontal, EOperation operation, const char* args) = 0;
      virtual std::vector<Experiment>& GetExperiments() = 0;
      virtual std::string GetExperimentName(int idx) = 0;
      virtual std::vector<PartExperiment>& GetPartExperiments(int idx, bool isHorizontal) = 0;
      virtual std::string GetPartExperimentImagePath(const char* name, int id, bool isHorizontal) = 0;
      virtual std::string GetPartExperimentPreviewImagePath(const char* name, int id, bool isHorizontal) = 0;
      virtual int GetExperimentsSize() = 0;
   };
}

#endif
