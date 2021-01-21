#ifndef _IIMAGE_MANAGER_
#define _IIMAGE_MANAGER_

#include "IManager.h"

namespace BIA
{
   class IImageManager : public IManager
   {
   public:
      virtual ~IImageManager() = 0 {};
      virtual void Init() = 0;
   };
}

#endif
