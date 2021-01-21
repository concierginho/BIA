#ifndef _IMANAGER_
#define _IMANAGER_

namespace BIA
{
   class IManager
   {
   public:
      virtual ~IManager() = 0 {};
      virtual void Init() = 0;
   };
}

#endif
