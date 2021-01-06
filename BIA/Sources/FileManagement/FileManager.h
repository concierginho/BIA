#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <regex>

#include "../Logger/ILogger.h"

namespace BIA
{
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
         std::vector<std::filesystem::path> _experimentDirectories;

         void CreateNewDirectory(std::filesystem::path&);
         void MoveItemsToNewDirectory(std::filesystem::path&, std::vector<std::filesystem::path>&);
         void ScanSubDirectories();
         void InitializeComponents();
         void CreateLogDirectory();

         Logger::ILogger* _logger = nullptr;
      public:
         void ScanDirectory();
 
         std::string GetRootPath() const;
         void SetRootPath(std::string);

         std::string GetLogPath() const;
         void SetLogPath(std::string);

         const std::vector<std::filesystem::path>& GetExperimentDirectories() const;
         const std::vector<std::filesystem::path>& GetRootFiles() const;

         FileManager(const std::string&, Logger::ILogger*);
         ~FileManager();
      };
   }
}
