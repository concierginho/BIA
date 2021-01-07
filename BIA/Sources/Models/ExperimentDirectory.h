#pragma once

#include <vector>
#include <string>
#include <filesystem>

namespace BIA
{
   namespace Models
   {
      class ExperimentDirectory
      {
      private:
         std::filesystem::path _path;
         std::vector<std::filesystem::path> _horizontalDirectoryFiles;
         std::vector<std::filesystem::path> _verticalDirectoryFiles;

         std::filesystem::path _horizontalImagePath;
         std::filesystem::path _verticalImagePath;

         int Id;
      public:
         int GetId() const;

         void AddVerticalDirectoryContent(std::filesystem::path&);
         void AddHorizontalDirectoryContent(std::filesystem::path&);
         void SetVerticalImagePath(std::filesystem::path&);
         void SetHorizontalImagePath(std::filesystem::path&);

         std::filesystem::path GetPath() const;
         std::filesystem::path GetVerticalDirectoryPath() const;
         std::filesystem::path GetHorizontalDirectoryPath() const;
         std::filesystem::path GetVerticalSettingsPath() const;
         std::filesystem::path GetHorizontalSettingsPath() const;
         std::filesystem::path GetVerticalExperimentPathById(int) const;
         std::filesystem::path GetHorizontalExperimentPathById(int) const;
         std::filesystem::path GetVerticalExperimentSettingsPathById(int) const;
         std::filesystem::path GetHorizontalExperimentSettingsPathById(int) const;
         std::filesystem::path GetVerticalResultsPath() const;
         std::filesystem::path GetHorizontalResultsPath() const;
         std::filesystem::path GetVerticalImagePath() const;
         std::filesystem::path GetHorizontalImagePath() const;

         static int NextId;

         explicit ExperimentDirectory(std::filesystem::path);
         ~ExperimentDirectory();
      };
   }
}
