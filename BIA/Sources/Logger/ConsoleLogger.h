#pragma once

#include "ILogger.h"

namespace Logger
{
   class ConsoleLogger : public ILogger
   {
   public:
       void Log(const std::stringstream&) override;
       ConsoleLogger();
       ~ConsoleLogger();
   };
}
