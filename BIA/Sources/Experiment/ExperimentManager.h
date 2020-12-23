#pragma once

#include <vector>

#include "../FileManagement/ExperimentDirectory.h"

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
         std::vector<FileManagement::ExperimentDirectory> _experiments;

         Logger::ILogger* _logger;
      public:
         ExperimentManager(Logger::ILogger* logger);
         ~ExperimentManager();
      };
   }
}
