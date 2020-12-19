#pragma once

#include "ILogger.h"

namespace Logger
{
   class ConsoleLogger : public ILogger
   {
   public:
       void Log(std::string) override;
       ConsoleLogger();
       ~ConsoleLogger();
   };
}
