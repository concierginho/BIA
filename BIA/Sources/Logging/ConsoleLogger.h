#pragma once

#include "ILogger.h"

namespace BIA
{
   namespace Logging
   {
      class ConsoleLogger : public ILogger
      {
      public:
         void Log(const std::stringstream&) override;
         void Prepare() override;
         ConsoleLogger();
         virtual ~ConsoleLogger();
      };
   }
}
