#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <regex>

#include "../Logger/ILogger.h"

namespace BIA
{
   namespace Experiment
   {
      class ExperimentManager;
   }

   namespace FileManagement
   {
      class FileManager
      {
      private:
         std::regex _hasVerticalPattern;
         std::regex _hasHorizontalPattern;
         std::regex _verticalAssociation;
         std::regex _horizontalAssociation;

         std::string _rootPath;
         std::string _logPath;
         std::vector<std::filesystem::path> _rootFiles;
         std::vector<std::filesystem::path> _rootDirectories;

         void CreateNewDirectory(std::filesystem::path&);
         void MoveItemsToNewDirectory(std::filesystem::path&, std::vector<std::filesystem::path>&);
         void ScanSubDirectories();
         void InitializeComponents();
         void CreateLogDirectory();

         Logger::ILogger* _logger = nullptr;
         Experiment::ExperimentManager* _experimentManager = nullptr;
      public:
         void ScanDirectory();
 
         std::string GetRootPath() const;
         void SetRootPath(std::string rootPath);

         std::string GetLogPath() const;
         void SetLogPath(std::string logPath);

         Experiment::ExperimentManager* GetExperimentManager();

         FileManager(const std::string&, Logger::ILogger*);
         ~FileManager();
      };
   }
}
