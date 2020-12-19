#pragma once

#include "ILogger.h"

namespace Logger
{
   class ConsoleLogger : public ILogger
   {
   public:
       void Log(const std::string&) override;
       ConsoleLogger();
       ~ConsoleLogger();
   };
}
