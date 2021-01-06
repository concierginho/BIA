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

         Logging::ILogger* _logger = nullptr;
         FileManagement::FileManager* _fileManager = nullptr;
      public:
         ExperimentManager(FileManagement::FileManager*, Logging::ILogger*);
         ~ExperimentManager();

         void PrepareExperiments();
      };
   }
}
