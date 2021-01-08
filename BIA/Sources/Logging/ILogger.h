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
         virtual void Log(const std::stringstream&, Source) = 0;
         virtual void Prepare() = 0;
         virtual ~ILogger() {};
      };
   }
}
