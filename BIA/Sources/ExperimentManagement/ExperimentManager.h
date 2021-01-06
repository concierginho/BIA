#pragma once

#include <vector>

#include "ExperimentDirectory.h"

namespace Logger
{
   class ILogger;
}

namespace BIA
{
   namespace ExperimentManagement
   {
      class ExperimentManager
      {
      private:
         std::vector<ExperimentDirectory> _experiments;

         Logger::ILogger* _logger;
      public:
         ExperimentManager(Logger::ILogger* logger);
         ~ExperimentManager();
      };
   }
}
