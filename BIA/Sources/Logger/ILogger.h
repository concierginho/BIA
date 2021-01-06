#pragma once

#include <string>

namespace Logger
{
   class ILogger
   {
   public:
      virtual void Log(const std::stringstream&) = 0;
   };
}
