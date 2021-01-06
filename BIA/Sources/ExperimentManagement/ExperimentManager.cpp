#include "ExperimentManager.h"

#include <sstream>

namespace BIA
{
   namespace ExperimentManagement
   {
      ExperimentManager::ExperimentManager(Logger::ILogger* logger, FileManagement::FileManager* fileManager)
      {
         _logger = logger;
         _fileManager = fileManager;
      }

      ExperimentManager::~ExperimentManager()
      {
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

#ifdef _LOGGING_
         msg.clear();
         auto end = std::chrono::steady_clock::now();
         auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
         msg << "Preparing experiments has ended and took : " << time << "ms.";
         _logger->Log(msg);
#endif
      }
   }
}

//
//#ifdef _LOGGING_
//#ifdef _LOGGING_
//std::string msg = "Scanning directory has been started.";
//_logger->Log(msg);
//auto start = std::chrono::steady_clock::now();
//#endif
//auto end = std::chrono::steady_clock::now();
//auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//msg = "Scanning directory has ended and took : " + std::to_string(time) + "ms.";
//_logger->Log(msg);
//#endif