#include "ExperimentManager.h"
#include "../Logger/ILogger.h"

namespace BIA
{
   namespace ExperimentManagement
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
