#ifndef _BIA_
#define _BIA_

#include "BIACoreExports.h"
#include "EProcess.h"

namespace BIA
{
   class BIAManagerKeeper;

   class BIACORE_API BIA
   {
   public:
      explicit BIA(char*);
      ~BIA();

      void Start(EProcess);
      void Stop();

      void Init();

      void PrepareBIARoutine();
      void OperationRoutine();

      void SetRootPath(char*);
      const char* GetRootPath() const;

      BIAManagerKeeper* GetKeeper();
      void SetKeeper(BIAManagerKeeper*);
   private:
      BIAManagerKeeper* _keeper = nullptr;
      char* _rootPath = nullptr;
   };
}

#endif
