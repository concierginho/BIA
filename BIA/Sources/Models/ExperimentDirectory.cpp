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
         Id = NextId;
         NextId++;

         _hasVerticalImage = false;
         _hasHorizontalImage = false;
         _hasVerticalSettingsJson = false;
         _hasHorizontalSettingsJson = false;
         _hasVerticalResultsJson = false;
         _hasHorizontalResultsJson = false;
      }

      ExperimentDirectory::~ExperimentDirectory()
      {
      }

      int ExperimentDirectory::GetId() const
      {
         return Id;
      }

      void ExperimentDirectory::AddVerticalDirectoryContent(std::filesystem::path& verticalDirectoryContent)
      {
         _verticalDirectoryFiles.push_back(verticalDirectoryContent);
      }

      void ExperimentDirectory::AddHorizontalDirectoryContent(std::filesystem::path& horizontalDirectoryContent)
      {
         _horizontalDirectoryFiles.push_back(horizontalDirectoryContent);
      }

      void ExperimentDirectory::SetVerticalImagePath(std::filesystem::path& verticalImagePath)
      {
         _verticalImagePath = verticalImagePath;
      }

      void ExperimentDirectory::SetHorizontalImagePath(std::filesystem::path& horizontalImagePath)
      {
         _horizontalImagePath = horizontalImagePath;
      }

      void ExperimentDirectory::SetHasVerticalImage(bool value)
      {
         _hasVerticalImage = value;
      }

      void ExperimentDirectory::SetHasHorizontalImage(bool value)
      {
         _hasHorizontalImage = value;
      }

      void ExperimentDirectory::SetHasVerticalSettingsJson(bool value)
      {
         _hasVerticalSettingsJson = value;
      }

      void ExperimentDirectory::SetHasHorizontalSettingsJson(bool value)
      {
         _hasHorizontalSettingsJson = value;
      }

      void ExperimentDirectory::SetHasVerticalResultsJson(bool value)
      {
         _hasVerticalResultsJson = value;
      }

      void ExperimentDirectory::SetHasHorizontalResultsJson(bool value)
      {
         _hasHorizontalResultsJson = value;
      }

      void ExperimentDirectory::SetExperimentName(std::string name)
      {
         _name = name;
      }

      std::string ExperimentDirectory::GetExperimentName() const
      {
         return _name;
      }

      std::filesystem::path ExperimentDirectory::GetPath() const
      {
         return _path;
      }

      std::filesystem::path ExperimentDirectory::GetVerticalDirectoryPath() const
      {
         std::stringstream verticalDirectory;
         verticalDirectory << _path.string() << "\\Vertical";
         return std::filesystem::path(verticalDirectory.str());
      }

      std::filesystem::path ExperimentDirectory::GetHorizontalDirectoryPath() const
      {
         std::stringstream horizontalDirectory;
         horizontalDirectory << _path.string() << "\\Horizontal";
         return std::filesystem::path(horizontalDirectory.str());
      }

      std::filesystem::path ExperimentDirectory::GetVerticalSettingsPath() const
      {
         std::stringstream verticalSettings;
         verticalSettings << GetVerticalDirectoryPath().string() << "\\settings.json";
         return std::filesystem::path(verticalSettings.str());
      }

      std::filesystem::path ExperimentDirectory::GetHorizontalSettingsPath() const
      {
         std::stringstream horizontalSettings;
         horizontalSettings << GetHorizontalDirectoryPath().string() << "\\settings.json";
         return std::filesystem::path(horizontalSettings.str());
      }

      std::filesystem::path ExperimentDirectory::GetHorizontalExperimentPathById(int id) const
      {
         std::stringstream horizontalExperiment;
         horizontalExperiment << GetHorizontalDirectoryPath().string() << "\\" << id;
         return std::filesystem::path(horizontalExperiment.str());
      }

      std::filesystem::path ExperimentDirectory::GetVerticalExperimentSettingsPathById(int id) const
      {
         std::stringstream settingsPath;
         settingsPath << GetVerticalExperimentPathById(id).string() << "\\settings.json";
         return std::filesystem::path(settingsPath.str());
      }

      std::filesystem::path ExperimentDirectory::GetHorizontalExperimentSettingsPathById(int id) const
      {
         std::stringstream settingsPath;
         settingsPath << GetHorizontalExperimentPathById(id).string() << "\\settings.json";
         return std::filesystem::path(settingsPath.str());
      }

      std::filesystem::path ExperimentDirectory::GetVerticalExperimentResultsPathById(int id) const
      {
         std::stringstream resultsPath;
         resultsPath << GetVerticalExperimentPathById(id).string() << "\\results.json";
         return std::filesystem::path(resultsPath.str());
      }

      std::filesystem::path ExperimentDirectory::GetHorizontalExperimentResultsPathById(int id) const
      {
         std::stringstream resultsPath;
         resultsPath << GetHorizontalExperimentPathById(id).string() << "\\resulsts.json";
         return std::filesystem::path(resultsPath.str());
      }

      std::filesystem::path ExperimentDirectory::GetVerticalResultsPath() const
      {
         std::stringstream resultsPath;
         resultsPath << GetVerticalDirectoryPath().string() << "\\results.json";
         return std::filesystem::path(resultsPath.str());
      }

      std::filesystem::path ExperimentDirectory::GetHorizontalResultsPath() const
      {
         std::stringstream resultsPath;
         resultsPath << GetHorizontalDirectoryPath().string() << "\\results.json";
         return std::filesystem::path(resultsPath.str());
      }

      std::filesystem::path ExperimentDirectory::GetVerticalExperimentPathById(int id) const
      {
         std::stringstream verticalExperiment;
         verticalExperiment << GetVerticalDirectoryPath().string() << "\\" << id;
         return std::filesystem::path(verticalExperiment.str());
      }

      std::filesystem::path ExperimentDirectory::GetVerticalImagePath() const
      {
         return _verticalImagePath;
      }

      std::filesystem::path ExperimentDirectory::GetHorizontalImagePath() const
      {
         return _horizontalImagePath;
      }

      bool ExperimentDirectory::HasVerticalImage() const
      {
         return _hasVerticalImage;
      }
      
      bool ExperimentDirectory::HasHorizontalImage() const
      {
         return _hasHorizontalImage;
      }

      bool ExperimentDirectory::HasVerticalSettingsJson() const
      {
         return _hasVerticalSettingsJson;
      }

      bool ExperimentDirectory::HasHorizontalSettingsJson() const
      {
         return _hasHorizontalSettingsJson;
      }

      bool ExperimentDirectory::HasVerticalResultsJson() const
      {
         return _hasVerticalResultsJson;
      }

      bool ExperimentDirectory::HasHorizontalResultsJson() const
      {
         return _hasHorizontalResultsJson;
      }
   }
}
