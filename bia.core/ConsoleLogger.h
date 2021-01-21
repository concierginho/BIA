#ifndef _CONSOLE_LOGGER_
#define _CONSOLE_LOGGER_

#include "ILogger.h"

namespace BIA
{
   class ConsoleLogger : public ILogger
   {
   public:
      ConsoleLogger();
      ~ConsoleLogger();

      virtual void Log(ESource, std::stringstream&) override;
      virtual void Prepare() override;
   };
}

#endif
