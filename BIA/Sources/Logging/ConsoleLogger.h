#pragma once

#include "ILogger.h"

namespace BIA
{
   namespace Logging
   {
      class ConsoleLogger : public ILogger
      {
      public:
         void Log(Source) override;
         void Prepare() override;
         ConsoleLogger();
         virtual ~ConsoleLogger();
         virtual void Flush() override;
      };
   }
}
