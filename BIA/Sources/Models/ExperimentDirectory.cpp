#include "ExperimentDirectory.h"

#include <sstream>

namespace BIA
{
   namespace Models
   {
      int ExperimentDirectory::NextId = 0;

      ExperimentDirectory::ExperimentDirectory(std::filesystem::path path)
      {
         _path = path;
         ID = NextId;
         NextId++;
      }

      ExperimentDirectory::~ExperimentDirectory()
      {
      }

      void ExperimentDirectory::AddHorizontalDirectoryContent(std::filesystem::path& horizontalDirectoryContent)
      {
         _horizontalDirectoryFiles.push_back(horizontalDirectoryContent);
      }

      void ExperimentDirectory::AddVerticalDirectoryContent(std::filesystem::path& verticalDirectoryContent)
      {
         _verticalDirectoryFiles.push_back(verticalDirectoryContent);
      }

      std::filesystem::path ExperimentDirectory::GetPath() const
      {
         return _path;
      }

      std::filesystem::path ExperimentDirectory::GetVerticalDirectoryPath() const
      {
         std::stringstream verticalDirectory;
         verticalDirectory << _path.string() << "\\Horizontal";
         return std::filesystem::path(verticalDirectory.str());
      }

      std::filesystem::path ExperimentDirectory::GetHorizontalDirectoryPath() const
      {
         std::stringstream horizontalDirectory;
         horizontalDirectory << _path.string() << "\\Vertical";
         return std::filesystem::path(horizontalDirectory.str());
      }

      std::filesystem::path ExperimentDirectory::GetVerticalSettingsPath() const
      {
         std::stringstream verticalSettings;
         verticalSettings << GetVerticalDirectoryPath() << "\\settings.json";
         return std::filesystem::path(verticalSettings.str());
      }

      std::filesystem::path ExperimentDirectory::GetHorizontalSettingsPath() const
      {
         std::stringstream horizontalSettings;
         horizontalSettings << GetHorizontalDirectoryPath() << "\\settings.json";
         return std::filesystem::path(horizontalSettings.str());
      }

      std::filesystem::path ExperimentDirectory::GetHorizontalExperimentPathById(int id) const
      {
         std::stringstream horizontalExperiment;
         horizontalExperiment << GetHorizontalDirectoryPath() << "\\" << id;
         return std::filesystem::path(horizontalExperiment.str());
      }

      std::filesystem::path ExperimentDirectory::GetVerticalExperimentSettingsPathById(int id) const
      {
         std::stringstream settingsPath;
         settingsPath << GetVerticalExperimentPathById(id) << "\\settings.json";
         return std::filesystem::path(settingsPath.str());
      }

      std::filesystem::path ExperimentDirectory::GetHorizontalExperimentSettingsPathById(int id) const
      {
         std::stringstream settingsPath;
         settingsPath << GetHorizontalExperimentPathById(id) << "\\settings.json";
         return std::filesystem::path(settingsPath.str());
      }

      std::filesystem::path ExperimentDirectory::GetVerticalExperimentPathById(int id) const
      {
         std::stringstream verticalExperiment;
         verticalExperiment << GetVerticalDirectoryPath() << "\\" << id;
         return std::filesystem::path(verticalExperiment.str());
      }
   }
}
