#pragma once

#include <vector>

#include "Experiment.h"
#include "ExperimentDirectory.h"

namespace BIA::Management
{
   class Manager;
}

#ifdef _LOGGING_
namespace BIA::Logging
{
   class ILogger;
}
#endif

namespace BIA::Experiment
{
   class ExperimentManager
   {
   private:
      std::vector<ExperimentDirectory> _experiments;

      Management::Manager* _manager = nullptr;
      Logging::ILogger* _logger = nullptr;
   public:
      void PrepareExperimentDirectories();
      std::vector<ExperimentDirectory>& GetExperiments();

      ExperimentManager(Management::Manager*);
      ~ExperimentManager();
   };
}
