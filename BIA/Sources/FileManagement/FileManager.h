#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <regex>

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

         void ScanDirectory();
         void ScanSubDirectories();
         void InitializeComponents();
      public:
         std::string& GetRootPath() const;
         void SetRootPath(std::string& rootPath);

         FileManager(std::string& rootPath);
         ~FileManager();
      };
   }
}