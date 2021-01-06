#pragma once

#include <vector>

#include "ExperimentDirectory.h"
#include "../Logger/ILogger.h"
#include "../FileManagement/FileManager.h"

namespace BIA
{
   namespace ExperimentManagement
   {
      class ExperimentManager
      {
      private:
         std::vector<ExperimentDirectory> _experiments;

         Logger::ILogger* _logger;
         FileManagement::FileManager* _fileManager;
      public:
         ExperimentManager(Logger::ILogger*, FileManagement::FileManager*);
         ~ExperimentManager();

         void PrepareExperiments();
      };
   }
}
