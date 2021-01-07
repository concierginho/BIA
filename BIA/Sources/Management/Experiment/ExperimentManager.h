#pragma once

#include <vector>

#include "../../Models/ExperimentDirectory.h"

namespace BIA
{
   namespace Management
   {
      class Manager;
      namespace Experiment
      {
         class ExperimentManager
         {
         private:
            std::vector<Models::ExperimentDirectory> _experiments;

            Management::Manager* _manager = nullptr;
            Logging::ILogger* _logger = nullptr;
         public:
            void PrepareExperimentDirectories();
            void PopulateExperimentsContnent();
            std::vector<Models::ExperimentDirectory>& GetExperiments();

            ExperimentManager(Management::Manager*);
            ~ExperimentManager();
         };
      }
   }
}
