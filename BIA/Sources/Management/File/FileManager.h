#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <regex>

namespace BIA
{
   namespace Logging
   {
      class ILogger;
   }

   namespace Management
   {
      class Manager;
      namespace File
      {
         class FileManager
         {
         private:
            std::regex _hasVerticalPattern;
            std::regex _hasHorizontalPattern;
            std::regex _verticalAssociation;
            std::regex _horizontalAssociation;
            std::regex _tif;
            std::regex _settings;
            std::regex _results;

            std::string _rootPath;
            std::vector<std::filesystem::path> _rootFiles;
            std::vector<std::filesystem::path> _experimentDirectories;

            void CreateNewDirectory(std::filesystem::path&);
            void CreateNewFile(std::filesystem::path&);
            void MoveItemsToNewDirectory(std::filesystem::path&, std::vector<std::filesystem::path>&);
            void InitializeComponents();

            Management::Manager* _manager = nullptr;
            Logging::ILogger* _logger = nullptr;
         public:
            void ScanDirectory();
            void ScanExperimentDirectories();
            void ScanHorizontalAndVerticalDirectories();

            std::string GetRootPath() const;
            void SetRootPath(std::string);

            const std::vector<std::filesystem::path>& GetExperimentDirectories() const;
            const std::vector<std::filesystem::path>& GetRootFiles() const;

            FileManager(Management::Manager*, const std::string&);
            ~FileManager();
         };
      }
   }
}
