#pragma once

#include <string>

namespace BIA
{
   namespace Logging
   {
      class ILogger
      {
      public:
         virtual void Log(const std::stringstream&) = 0;
         virtual ~ILogger() {};
      };
   }
}
