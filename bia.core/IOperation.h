#ifndef _IOPERATION_
#define _IOPERATION_

#include <string>
#include "Bitmap.h"

namespace BIA
{
   class IOperation
   {
   public:
      std::string virtual ToString() = 0;
      std::string virtual ArgumentsToString() = 0;
      void virtual PerformOperation(Bitmap* bitmap) = 0;
   };
}

#endif
