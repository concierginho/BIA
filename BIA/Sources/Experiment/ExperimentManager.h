#pragma once

#include "ExperimentDirectory.h"

#include <vector>

namespace Logger
{
   class ILogger;
}

namespace BIA
{
   namespace Experiment
   {
      class ExperimentManager
      {
      private:
         Logger::ILogger* _logger;
      public:
         std::vector<std::vector<ExperimentDirectory>> _experiments;

         void AddExperiment(std::vector<ExperimentDirectory>&);

         ExperimentManager(Logger::ILogger* logger);
         ~ExperimentManager();
      };
   }
}
