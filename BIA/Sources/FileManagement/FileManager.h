#pragma once

#include <string>
#include <vector>
#include <filesystem>

namespace BIA
{
   namespace FileManagement
   {
      class FileManager
      {
      private:
         std::string& _rootPath;
         std::vector<std::filesystem::path> _rootFiles;
         std::vector<std::filesystem::path> _rootDirectories;

         void ScanDirectory();
         void ScanSubDirectories();
      public:
         std::string& GetRootPath() const;
         void SetRootPath(std::string& rootPath);

         FileManager(std::string& rootPath);
         ~FileManager();
      };
   }
}