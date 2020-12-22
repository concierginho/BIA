#include "ExperimentManager.h"
#include "../Logger/ILogger.h"

namespace BIA
{
   namespace Experiment
   {
      ExperimentManager::ExperimentManager(Logger::ILogger* logger)
      {
         _logger = logger;
      }

      ExperimentManager::~ExperimentManager()
      {
      }
   }
}