#include "ExperimentManager.h"
#include "../Logger/ILogger.h"

namespace BIA
{
   namespace Experiment
   {
      void ExperimentManager::AddExperiment(std::vector<ExperimentDirectory>& experiments)
      {
         _experiments.push_back(experiments);
      }
      
      ExperimentManager::ExperimentManager(Logger::ILogger* logger)
      {
         _logger = logger;
      }

      ExperimentManager::~ExperimentManager()
      {
      }
   }
}