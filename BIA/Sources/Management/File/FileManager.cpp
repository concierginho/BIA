#include <vector>
#include <iostream>
#include <chrono>
#include <regex>
#include <sstream>
#include <fstream>

#include "../Manager.h"

namespace BIA
{
   namespace Management::File
   {
      FileManager::FileManager(Management::Manager* manager, const std::string& rootPath)
      {
         _manager = manager;
         _rootPath = rootPath;
         _logger = _manager->Logger;

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
         _tif = std::regex("(.*tif$)");
         _settings = std::regex("(.*settings\\.json$)");
         _results = std::regex("(.*results\\.json$)");
      }

      /// <summary>
      /// Funkcja przechodzi przez kazdy plik/katalog w glowym folderze i wszystkie foldery kwalifikuje jako
      /// osobne eksperymenty (zrodla zdjec).
      /// </summary>
      void FileManager::ScanDirectory()
      {
#ifdef _LOGGING_
         std::stringstream msg;
         msg.str(std::string());
         msg << "Scanning directory has been started.";
         _logger->Log(msg);
         auto start = std::chrono::steady_clock::now();
#endif
         for (const auto& rootItem : std::filesystem::directory_iterator(_rootPath))
         {
            if (rootItem.is_directory() && rootItem.path().filename() != "log")
               _experimentDirectories.push_back(rootItem.path());
            _rootFiles.push_back(rootItem.path());
         }

#ifdef _LOGGING_
         msg.str(std::string());
         auto end = std::chrono::steady_clock::now();
         auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
         msg << "Scanning directory has ended and took: " << time << "ms.";
         _logger->Log(msg);
#endif
      }

      /// <summary>
      /// Funkcja sprawdza kazdy z folderow zlokalizowanych w glownym katalogu.
      /// Sprawdza czy folder o nazwie "Vertical" oraz "Horizontal" istnieja, 
      /// a nastepnie szuka plikow ktore w swojej nazwie maja
      /// wlasnie te slowa. Jezli takie pliki nie sa odnalezione - zostaja stworzone.
      /// Na podstawie tego, czy dana nazwa pliku zawiera w sobie slowa 'Vertical' 
      /// lub 'Horizontal' pliki przenoszone sa do odpowiedniej lokalizacji.
      /// </summary>
      void FileManager::ScanExperimentDirectories()
      {
#ifdef _LOGGING_
         std::stringstream msg;
#endif
         if (_experimentDirectories.size() == 0)
            return;

         auto& _experiments = _manager->ExperimentManager->GetExperiments();

         for (auto const& experiment : _experiments)
         {
            bool hasVertical = false;
            bool hasHorizontal = false;
            std::vector<std::filesystem::path> verticalAssociatedItems;
            std::vector<std::filesystem::path> horizontalAssociatedItems;
            std::string subDirectoryPath = experiment.GetPath().string();

            for (auto const& subItem : std::filesystem::directory_iterator(experiment.GetPath().string()))
            {
               std::string subItemPath = subItem.path().string();
               if (!subItem.is_directory())
               {
                  std::string filename = subItem.path().filename().string();

                  if (std::regex_match(filename, _horizontalAssociation))
                     horizontalAssociatedItems.push_back(subItemPath);
                  else if (std::regex_match(filename, _verticalAssociation))
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
#ifdef _LOGGING_
               msg.str(std::string());
               msg << "Experiment Id " << experiment.GetId() << " / Missing 'Vertical' directory.";
               _logger->Log(msg);
#endif
               CreateNewDirectory(verticalFolderPath);
            }
            if (!hasHorizontal)
            {
#ifdef _LOGGING_
               msg.str(std::string());
               msg << "'Horizontal' folder is missing.";
               _logger->Log(msg);
#endif
               CreateNewDirectory(horizontalFolderPath);
            }

            MoveItemsToNewDirectory(verticalFolderPath, verticalAssociatedItems);
            MoveItemsToNewDirectory(horizontalFolderPath, horizontalAssociatedItems);
         }
      }

      /// <summary>
      /// Funckja odpowiedzialna jest za skanowanie plikow zawartych w folderach horizontal oraz vertical.
      /// Skanowanie tych plikow odbywa sie po przeniesieniu i uporzadkowaniu plikow przez funkcje 
      /// PrepareExperimentDirectories() nalezacej do klasy ExperimentManager.
      /// </summary>
      void FileManager::ScanHorizontalAndVerticalDirectories()
      {
#ifdef _LOGGING_
         std::stringstream msg;
         msg.str(std::string());
         msg << "Scanning horizontal and vertical directories has been started.";
         _logger->Log(msg);
         auto start = std::chrono::steady_clock::now();
#endif
         auto& experiments = _manager->ExperimentManager->GetExperiments();

         for (auto& experiment : experiments)
         {
            for (auto const& item : std::filesystem::directory_iterator(experiment.GetHorizontalDirectoryPath().string()))
            {
               if (item.is_directory())
                  continue;

               std::string filename = item.path().filename().string();
               std::string fileExt = item.path().extension().string();
               if (std::regex_match(filename, _settings))
                  experiment.SetHasHorizontalSettingsJson(true);
               else if (std::regex_match(filename, _results))
                  experiment.SetHasHorizontalResultsJson(true);
               else if (std::regex_match(fileExt, _tif))
               {
                  std::filesystem::path itemPath = item.path();
                  experiment.SetHorizontalImagePath(itemPath);
                  experiment.SetHasHorizontalImage(true);
               }
            }

            if (experiment.HasHorizontalSettingsJson() == false)
            {
#ifdef _LOGGING_
               msg.str(std::string());
               msg << "Horizontal directory / Experiment Id " << experiment.GetId() << " / Missing 'settings.json' file.";
               _logger->Log(msg);
#endif
               auto path = experiment.GetHorizontalSettingsPath();
               CreateNewFile(path);
            }

            if (experiment.HasHorizontalResultsJson() == false)
            {
#ifdef _LOGGING_
               msg.str(std::string());
               msg << "Horizontal directory / Experiment Id " << experiment.GetId() << " / Missing 'results.json' file.";
               _logger->Log(msg);
#endif
               auto path = experiment.GetHorizontalResultsPath();
               CreateNewFile(path);
            }

            for (auto const& item : std::filesystem::directory_iterator(experiment.GetVerticalDirectoryPath().string()))
            {
               std::string filename = item.path().filename().string();
               std::string fileExt = item.path().extension().string();
               if (std::regex_match(filename, _settings))
                  experiment.SetHasVerticalSettingsJson(true);
               else if (std::regex_match(filename, _results))
                  experiment.SetHasVerticalResultsJson(true);
               else if (std::regex_match(fileExt, _tif))
               {
                  std::filesystem::path itemPath = item.path();
                  experiment.SetVerticalImagePath(itemPath);
                  experiment.SetHasVerticalImage(true);
               }
            }

            if (experiment.HasVerticalSettingsJson() == false)
            {
#ifdef _LOGGING_
               msg.str(std::string());
               msg << "Vertical directory / Experiment Id " << experiment.GetId() << " / Missing 'settings.json' file.";
               _logger->Log(msg);
#endif
               auto path = experiment.GetHorizontalSettingsPath();
               CreateNewFile(path);
            }

            if (experiment.HasVerticalResultsJson() == false)
            {
#ifdef _LOGGING_
               msg.str(std::string());
               msg << "Vertical directory / Experiment Id " << experiment.GetId() << " / Missing 'results.json' file.";
               _logger->Log(msg);
#endif
               auto path = experiment.GetHorizontalResultsPath();
               CreateNewFile(path);
            }

            if (experiment.GetHorizontalImagePath().empty())
            {
#ifdef _LOGGING_
               msg.str(std::string());
               msg << "Horizontal directory / Experiment Id " << experiment.GetId() << " / Missing image file with extension '*.tif'";
               _logger->Log(msg);
#endif
            }

            if (experiment.GetVerticalImagePath().empty())
            {
#ifdef _LOGGING_
               msg.str(std::string());
               msg << "Vertical directory / Experiment Id " << experiment.GetId() << " / Missing image file with extension '*.tif'";
               _logger->Log(msg);
#endif
            }
         }
#ifdef _LOGGING_
         msg.str(std::string());
         auto end = std::chrono::steady_clock::now();
         auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
         msg << "Scanning horizontal and vertical directories has ended and took: " << time << "ms.";
         _logger->Log(msg);
#endif
      }

      /// <summary>
      /// Funkcja odpowiedzialna jest za przeniesienie wszystkich elementow zawartych w wektorze "source" z ich starej lokalizacji
      /// Do folderu przekazanego w argumencie "newDirectory".
      /// </summary>
      void FileManager::MoveItemsToNewDirectory(std::filesystem::path& newDirectory, std::vector<std::filesystem::path>& source)
      {
#ifdef _LOGGING_
         std::stringstream msg;
#endif
         try
         {
            for (const auto& path : source)
            {
               std::filesystem::path oldPath = path;
               std::string filename = path.filename().string();
               std::filesystem::path newPath(newDirectory.string() + "\\" + filename);
               std::filesystem::rename(oldPath, newPath);
#ifdef _LOGGING_
               msg.str(std::string());
               msg << "Moved: " << oldPath.string() << "\nTo: " << newPath.string() << ".";
               _logger->Log(msg);
#endif 
            }
         }
         catch (std::exception e)
         {
#ifdef _LOGGING_
            msg.str(std::string());
            msg << "Exception thrown: " << e.what();
            _logger->Log(msg);
#endif
         }
      }

      /// <summary>
      /// Funkcja tworzy nowy folder we wskazanej lokalizacji.
      /// </summary>
      void FileManager::CreateNewDirectory(std::filesystem::path& path)
      {
#ifdef _LOGGING_
         std::stringstream msg;
#endif
         if (std::filesystem::exists(path))
            return;

         try
         {
            std::filesystem::create_directories(path);
#ifdef _LOGGING_
            msg.str(std::string());
            msg << "Created new directory: " << path.string();
            _logger->Log(msg);
#endif 
         }
         catch (std::exception e)
         {
#ifdef _LOGGING_
            msg.str(std::string());
            msg << "Exception thrown: " << e.what();
            _logger->Log(msg);
#endif
         }
      }

      void FileManager::CreateNewFile(std::filesystem::path& path)
      {
#ifdef _LOGGING_
         std::stringstream msg;
#endif
         if (std::filesystem::exists(path))
            return;

         try
         {
            std::ofstream file{ path.string() };
#ifdef _LOGGING_
            msg.str(std::string());
            msg << "Created new file: " << path.string();
            _logger->Log(msg);
#endif 
         }
         catch (std::exception e)
         {
#ifdef _LOGGING_
            msg.str(std::string());
            msg << "Exception thrown: " << e.what();
            _logger->Log(msg);
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
