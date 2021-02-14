#ifndef _BIA_
#define _BIA_

#include "BIACoreExports.h"
#include "EProcess.h"
#include "EOperation.h"

namespace BIA
{
   class BIAManagerKeeper;
   class Experiment;
   class PartExperiment;
   class IProcessManager;
   class IExperimentManager;

   class BIACORE_API BIA
   {
   public:
      explicit BIA(char*);
      ~BIA();

      void Start(EProcess);
      void Stop();
      void Init();
      void PrepareRoutine();
      void OperationRoutine();
      void SetKeeper(BIAManagerKeeper*);

      const char* GetRootPath() const;
      void SetRootPath(char*);

      BIAManagerKeeper* GetKeeper();
      IExperimentManager* GetExperimentManager();
      IProcessManager* GetProcessManager();

      Experiment* GetExperiment(const char* name);
      PartExperiment* GetPartExperiment(const char* name, int id, bool isHorizontal);
   private:
      BIAManagerKeeper* _keeper = nullptr;
      char* _rootPath = nullptr;
   };
}

#endif
