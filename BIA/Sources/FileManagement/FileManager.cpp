#include "FileManager.h"
#include <vector>
#include <iostream>
#include <chrono>
#include <regex>

namespace BIA
{
   namespace FileManagement
   {
      FileManager::FileManager(std::string& rootPath) : _rootPath(rootPath)
      {
         InitializeComponents();
         ScanDirectory();
      }
      
      FileManager::~FileManager()
      {
      }

      void FileManager::InitializeComponents()
      {
         _hasVerticalPattern = std::regex("(.*vertical$)", std::regex_constants::icase);
         _hasHorizontalPattern = std::regex("(.*horizontal$)", std::regex_constants::icase);
         _verticalAssociation = std::regex("(.*vertical.*)", std::regex_constants::icase);
         _horizontalAssociation = std::regex("(.*horizontal.*)", std::regex_constants::icase);
      }

      void FileManager::ScanDirectory()
      {
#ifdef _TIME_MEASUREMENT_
         auto start = std::chrono::steady_clock::now();
#endif
         for (const auto& rootItem : std::filesystem::directory_iterator(_rootPath))
         {
            if (rootItem.is_directory())
               _rootDirectories.push_back(rootItem.path());
            _rootFiles.push_back(rootItem.path());
         }
         
         if (_rootDirectories.size() > 0)
            ScanSubDirectories();
#ifdef _TIME_MEASUREMENT_
         auto end = std::chrono::steady_clock::now();
         auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
         std::cout << "scanning root file: " << time << "ms" << std::endl;
#endif
      }

      void FileManager::ScanSubDirectories()
      {


         for (auto const& rootSubDir : _rootDirectories)
         {
            bool hasVertical = false;
            bool hasHorizontal = false;

            std::vector<std::filesystem::path> verticalAssociatedItems;
            std::vector<std::filesystem::path> horizontalAssociatedItems;

            std::string rootSubDirPath = rootSubDir.string();

            for (auto const& subItem : std::filesystem::directory_iterator(rootSubDir.string()))
            {
               std::string subItemPath = subItem.path().string();
               if (!subItem.is_directory())
               {
                  std::string fileName = subItem.path().filename().string();

                  if (std::regex_match(fileName, _horizontalAssociation))
                     horizontalAssociatedItems.push_back(subItemPath);
                  else if (std::regex_match(fileName, _verticalAssociation))
                     verticalAssociatedItems.push_back(subItemPath);
               }
               else
               {
                  if (std::regex_match(subItemPath, _hasHorizontalPattern))
                     hasHorizontal = true;
                  if (std::regex_match(subItemPath, _hasVerticalPattern))
                     hasVertical = true;
               }
            }
            
            std::filesystem::path verticalFolderPath(rootSubDirPath + "\\Vertical");
            std::filesystem::path horizontalFolderPath(rootSubDirPath + "\\Horizontal");
            
            try
            {
               if (!hasVertical)
                  std::filesystem::create_directories(verticalFolderPath);

               if (!hasHorizontal)
                  std::filesystem::create_directories(horizontalFolderPath);
            }
            catch (const std::exception& exception)
            {
               std::cout << exception.what() << std::endl;;
            }

            for (auto const& horizontalAssociatedItem : horizontalAssociatedItems)
            {
               try
               {
                  std::filesystem::path oldPath = horizontalAssociatedItem;
                  std::string filename = horizontalAssociatedItem.filename().string();
                  std::filesystem::path newPath(horizontalFolderPath.string() + "\\" + filename);
                  std::filesystem::rename(oldPath, newPath);
               }
               catch (const std::exception& exception)
               {
                  std::cout << exception.what() << std::endl;
               }
            }

            for (auto const& verticalAssociatedItem : verticalAssociatedItems)
            {
               try
               {
                  std::filesystem::path oldPath = verticalAssociatedItem;
                  std::string filename = verticalAssociatedItem.filename().string();
                  std::filesystem::path newPath(verticalFolderPath.string() + "\\" + filename);
                  std::filesystem::rename(oldPath, newPath);
               }
               catch (const std::exception& exception)
               {
                  std::cout << exception.what() << std::endl;
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
