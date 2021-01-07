#pragma once

#include <vector>

#include "ExperimentDirectory.h"

namespace BIA
{
   namespace Management
   {
      class Manager;
   }
   namespace ExperimentManagement
   {
      class ExperimentManager
      {
      private:
         std::vector<ExperimentDirectory> _experiments;

         Management::Manager* _manager = nullptr;
         Logging::ILogger* _logger = nullptr;
      public:
         void PrepareExperimentDirectories();
         void PopulateExperimentsContnent();
         const std::vector<ExperimentDirectory>& GetExperiments() const;

         ExperimentManager(Management::Manager*);
         ~ExperimentManager();
      };
   }
}
