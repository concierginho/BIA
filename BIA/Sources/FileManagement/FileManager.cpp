#include <vector>
#include <iostream>
#include <chrono>
#include <regex>

#include "FileManager.h"

namespace BIA
{
   namespace FileManagement
   {
      FileManager::FileManager(const std::string& rootPath, Logger::ILogger* logger = nullptr)
      {
#ifndef _LOGGING_
         this->_logger = logger = nullptr;
#else
         this->_logger = logger;
#endif
         _rootPath = rootPath;
         InitializeComponents();
      }
      
      FileManager::~FileManager()
      {
         _logger = nullptr;
      }

      void FileManager::InitializeComponents()
      {
         _hasVerticalPattern = std::regex("(.*vertical$)", std::regex_constants::icase);
         _hasHorizontalPattern = std::regex("(.*horizontal$)", std::regex_constants::icase);
         _verticalAssociation = std::regex("(.*vertical.*)", std::regex_constants::icase);
         _horizontalAssociation = std::regex("(.*horizontal.*)", std::regex_constants::icase);
         _logPath = std::string(_rootPath + "\\" + "log");
      }

      void FileManager::CreateLogDirectory()
      {
         auto logPath = std::filesystem::path(_logPath);
         CreateNewDirectory(logPath);
      }

      /// <summary>
      /// Funkcja przechodzi przez kazdy plik/katalog w glowym folderze i wszystkie foldery kwalifikuje jako
      /// osobne eksperymenty (zrodla zdjec).
      /// </summary>
      void FileManager::ScanDirectory()
      {
#ifdef _LOGGING_
         std::string msg = "Scanning directory has been started.";
         _logger->Log(msg);
         auto start = std::chrono::steady_clock::now();
#endif
         for (const auto& rootItem : std::filesystem::directory_iterator(_rootPath))
         {
            if (rootItem.is_directory() && rootItem.path().filename() != "log")
               _experimentDirectories.push_back(rootItem.path());
            _rootFiles.push_back(rootItem.path());
         }

         if (_experimentDirectories.size() > 0)
            ScanSubDirectories();

         CreateLogDirectory();

#ifdef _LOGGING_
         auto end = std::chrono::steady_clock::now();
         auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
         msg = "Scanning directory has ended and took : " + std::to_string(time) + "ms.";
         _logger->Log(msg);
#endif
      }

      /// <summary>
      /// Funkcja sprawdza kazdy z folderow zlokalizowanych w glownym katalogu.
      /// Sprawdza czy folder o nazwie "Vertical" oraz "Horizontal" istnieja, a nastepnie szuka plikow ktore w swojej nazwie maja
      /// wlasnie te slowa. Na tej podstawie pliki przenoszone sa do odpowiednich folderow.
      /// </summary>
      void FileManager::ScanSubDirectories()
      {
         for (auto const& folder : _experimentDirectories)
         {
            bool hasVertical = false;
            bool hasHorizontal = false;
            std::vector<std::filesystem::path> verticalAssociatedItems;
            std::vector<std::filesystem::path> horizontalAssociatedItems;
            std::string subDirectoryPath = folder.string();

            for (auto const& subItem : std::filesystem::directory_iterator(folder.string()))
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

            std::filesystem::path verticalFolderPath(subDirectoryPath + "\\Vertical");
            std::filesystem::path horizontalFolderPath(subDirectoryPath + "\\Horizontal");

            if (!hasVertical)
            {
               CreateNewDirectory(verticalFolderPath);
            }
            if (!hasHorizontal)
            {
               CreateNewDirectory(horizontalFolderPath);
            }

            MoveItemsToNewDirectory(verticalFolderPath, verticalAssociatedItems);
            MoveItemsToNewDirectory(horizontalFolderPath, horizontalAssociatedItems);
         }
      }

      /// <summary>
      /// Funkcja odpowiedzialna jest za przeniesienie wszystkich elementow zawartych w wektorze "source" z ich starej lokalizacji
      /// Do folderu przekazanego w argumencie "newDirectory".
      /// </summary>
      void FileManager::MoveItemsToNewDirectory(std::filesystem::path& newDirectory, std::vector<std::filesystem::path>& source)
      {
         try
         {
            for (const auto& path : source)
            {
               std::filesystem::path oldPath = path;
               std::string filename = path.filename().string();
               std::filesystem::path newPath(newDirectory.string() + "\\" + filename);
               std::filesystem::rename(oldPath, newPath);
#ifdef _LOGGING_
               std::string msg = "Moved " + oldPath.string() + " to " + newPath.string() + ".";
               _logger->Log(msg);
#endif 
            }
         }
         catch (std::exception e)
         {
#ifdef _LOGGING_
            std::string msg0 = "Exception thrown: ";
            std::string msg1 = e.what();
            _logger->Log(msg0 + msg1);
#endif
         }
      }

      /// <summary>
      /// Funkcja tworzy nowy folder we wskazanej lokalizacji.
      /// </summary>
      void FileManager::CreateNewDirectory(std::filesystem::path& path)
      {
         if (std::filesystem::exists(path))
            return;

         try
         {
            std::filesystem::create_directories(path);
#ifdef _LOGGING_
            _logger->Log("Created new directory: " + path.string());
#endif 
         }
         catch (std::exception e)
         {
#ifdef _LOGGING_
            std::string msg0 = "Exception thrown: ";
            std::string msg1 = e.what();
            _logger->Log(msg0 + msg1);
#endif
         }
      }
      
      std::string FileManager::GetRootPath() const
      {
         return _rootPath;
      }
      
      void FileManager::SetRootPath(std::string rootPath)
      {
         _rootPath = rootPath;
      }

      std::string FileManager::GetLogPath() const
      {
         return _logPath;
      }

      void FileManager::SetLogPath(std::string logPath)
      {
         _logPath = logPath;
      }

      const std::vector<std::filesystem::path>& FileManager::GetExperimentDirectories() const
      {
         return _experimentDirectories;
      }

      const std::vector<std::filesystem::path>& FileManager::GetRootFiles() const
      {
         return _rootFiles;
      }
   }
}
