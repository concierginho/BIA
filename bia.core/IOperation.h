#ifndef _IOPERATION_
#define _IOPERATION_

#include <string>

namespace BIA
{
   class IOperation
   {
      std::string virtual ToString() = 0;
      std::string virtual ArgumentsToString() = 0;
   };
}

#endif
