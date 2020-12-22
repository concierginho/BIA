#pragma once

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
      public:
         ExperimentManager(Logger::ILogger* logger);
         ~ExperimentManager();
      private:
         Logger::ILogger* _logger;
      };
   }
}
