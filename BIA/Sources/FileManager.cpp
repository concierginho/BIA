#include "FileManager.h"
#include <vector>
#include <iostream>

namespace BIA
{
   namespace FileManagement
   {
      FileManager::FileManager(std::string& rootPath) : _rootPath(rootPath)
      {
         ScanDirectory();
      }
      
      FileManager::~FileManager()
      {
      }

      void FileManager::ScanDirectory()
      {
         for (const auto& outer : std::filesystem::directory_iterator(_rootPath))
         {
            std::string filePath = outer.path().string();
            _rootFiles.push_back(filePath);
            std::cout << filePath << std::endl;

            if (outer.is_directory())
            {
               for (const auto& inner : std::filesystem::directory_iterator(filePath))
               {
                  std::cout << "   " + inner.path().string() << std::endl;
               }
            }
         }
      }
      
      std::string& FileManager::GetRootPath() const
      {
         return _rootPath;
      }
      
      void FileManager::SetRootPath(std::string& rootPath)
      {
         _rootPath = rootPath;
      }
   }
}