#pragma once

#include <string>

namespace Logger
{
   class ILogger
   {
   public:
      virtual void Log(std::string) = 0;
   };
}