#pragma once

#include <string>

namespace BIA
{
   namespace Logging
   {
      enum class Source
      {
         FILE_MANAGER,
         EXPERIMENT_MANAGER,
         IMAGE_MANAGER,
         TIME_MEASUREMENT,
         MEMORY_MANAGEMENT
      };

      class ILogger
      {
      public:
         static std::stringstream Message;

         virtual void Log(Source) = 0;
         virtual void Flush() = 0;
         virtual void Prepare() = 0;
         virtual ~ILogger() {};
      };
   }
}
