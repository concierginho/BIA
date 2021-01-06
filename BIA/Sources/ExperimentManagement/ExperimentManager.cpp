#include "ExperimentManager.h"

#include <sstream>

namespace BIA
{
   namespace ExperimentManagement
   {
      ExperimentManager::ExperimentManager(FileManagement::FileManager* fileManager, Logging::ILogger* logger)
      {
         _logger = logger;
         _fileManager = fileManager;
      }

      ExperimentManager::~ExperimentManager()
      {
         _logger = nullptr;
         _fileManager = nullptr;
      }

      void ExperimentManager::PrepareExperiments()
      {
#ifdef _LOGGING_
         std::stringstream msg;
         msg << "Preparing experiments has been started.";
         _logger->Log(msg);
         auto start = std::chrono::steady_clock::now();
#endif
         auto experimentDirectories = _fileManager->GetExperimentDirectories();

         for (const auto& experiment : experimentDirectories)
         {
            _experiments.push_back(ExperimentDirectory(experiment));
         }

         PopulateExperimentsContnent();

#ifdef _LOGGING_
         msg.clear();
         auto end = std::chrono::steady_clock::now();
         auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
         msg << "Preparing experiments has ended and took : " << time << "ms.";
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
      
      const std::vector<ExperimentDirectory>& ExperimentManager::GetExperiments() const
      {
         return _experiments;
      }
   }
}
