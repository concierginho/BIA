#pragma once

#include "ILogger.h"

namespace Logger
{
   class FileLogger : public ILogger
   {
      void Log(std::string) override;
   };
}
