#include <sstream>

#include "../Manager.h"

using namespace BIA::Logging;

namespace BIA
{
   namespace Management::Experiment
   {
      ExperimentManager::ExperimentManager(Management::Manager* manager)
      {
         _manager = manager;
         _logger = _manager->Logger;
      }

      ExperimentManager::~ExperimentManager()
      {
         _manager = nullptr;
         _logger = nullptr;
      }

      void ExperimentManager::PrepareExperimentDirectories()
      {
#ifdef _LOGGING_
         _logger->Message << "Preparing experiments directories has been started.";
         _logger->Log(Source::EXPERIMENT_MANAGER);
         auto start = std::chrono::steady_clock::now();
#endif
         auto& experimentDirectories = _manager->FileManager->GetExperimentDirectories();

         for (const auto& experiment : experimentDirectories)
         {
            Models::ExperimentDirectory experimentDirectory(experiment);
            experimentDirectory.SetExperimentName(experiment.filename().string());
            _experiments.push_back(experimentDirectory);
         }

#ifdef _LOGGING_
         auto end = std::chrono::steady_clock::now();
         auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
         _logger->Message << "Preparing experiments directories has ended and took: " << time << "ms.";
         _logger->Log(Source::EXPERIMENT_MANAGER);
#endif
      }

      std::vector<Models::ExperimentDirectory>& ExperimentManager::GetExperiments()
      {
         return _experiments;
      }
   }
}
