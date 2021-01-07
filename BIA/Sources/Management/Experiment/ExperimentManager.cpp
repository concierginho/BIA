#include <sstream>

#include "../Manager.h"

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
         std::stringstream msg;
         msg.str(std::string());
         msg << "Preparing experiments directories has been started.";
         _logger->Log(msg);
         auto start = std::chrono::steady_clock::now();
#endif
         auto& experimentDirectories = _manager->FileManager->GetExperimentDirectories();

         for (const auto& experiment : experimentDirectories)
         {
            _experiments.push_back(Models::ExperimentDirectory(experiment));
         }

#ifdef _LOGGING_
         msg.str(std::string());
         auto end = std::chrono::steady_clock::now();
         auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
         msg << "Preparing experiments directories has ended and took: " << time << "ms.";
         _logger->Log(msg);
#endif
      }

      void ExperimentManager::PopulateExperimentsContnent()
      {
         for (auto& experiment : _experiments)
         {
            auto horizontalDir = experiment.GetHorizontalDirectoryPath();
            auto verticalDir = experiment.GetVerticalDirectoryPath();

            for (auto const& horizontalContent : std::filesystem::directory_iterator(horizontalDir.string()))
            {
               std::filesystem::path contentPath = horizontalContent.path();
               experiment.AddHorizontalDirectoryContent(contentPath);
            }

            for (auto const& verticalContent : std::filesystem::directory_iterator(verticalDir.string()))
            {
               std::filesystem::path contentPath = verticalContent.path();
               experiment.AddVerticalDirectoryContent(contentPath);
            }
         }
      }
      
      std::vector<Models::ExperimentDirectory>& ExperimentManager::GetExperiments()
      {
         return _experiments;
      }
   }
}
