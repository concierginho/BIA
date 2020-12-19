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

         std::string& _rootPath;
         std::vector<std::filesystem::path> _rootFiles;
         std::vector<std::filesystem::path> _rootDirectories;

         void CreateNewDirectory(std::filesystem::path&);
         void MoveItemsToNewDirectory(std::filesystem::path&, std::vector<std::filesystem::path>&);
         void ScanDirectory();
         void ScanSubDirectories();
         void InitializeComponents();

         Logger::ILogger* logger;
      public:
         std::string& GetRootPath() const;
         void SetRootPath(std::string& rootPath);

         FileManager(std::string&, Logger::ILogger*);
         ~FileManager();
      };
   }
}