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

      void Init();
      void StartProcess();
      void SetRootPath(char*);
      const char* GetRootPath() const;
   private:
      BIAManagerKeeper* _keeper = nullptr;
      char* _rootPath = nullptr;
   };
}

#endif
