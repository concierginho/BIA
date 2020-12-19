#pragma once

#include "ILogger.h"

namespace Logger
{
   class FileLogger : public ILogger
   {
   public:
      void Log(const std::string&) override;
      FileLogger();
      ~FileLogger();
   };
}
