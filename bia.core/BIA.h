#ifndef _BIA_
#define _BIA_

#include "BIACoreExports.h"

namespace BIA
{
   class BIAManagerKeeper;

   class BIACORE_API BIA
   {
   public:
      explicit BIA(char*);
      ~BIA();

      bool IsRunning();

      void Start();
      void Stop();

      void Init();
      void StartProcess();
      void StopProcess();
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
