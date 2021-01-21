#ifndef _ILOGGER_
#define _ILOGGER_

#include <sstream>

#include "ESource.h"

namespace BIA
{
   class ILogger
   {
   public:
      virtual void Log(ESource, std::stringstream&) = 0;
      virtual void Prepare() = 0;
      virtual ~ILogger() {};
   };
}

#endif
