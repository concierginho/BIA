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

         std::filesystem::path _horizontalImage;
         std::filesystem::path _verticalImage;

         int ID;
      public:
         void AddHorizontalDirectoryContent(std::filesystem::path&);
         void AddVerticalDirectoryContent(std::filesystem::path&);

         std::filesystem::path GetPath() const;
         std::filesystem::path GetVerticalDirectoryPath() const;
         std::filesystem::path GetHorizontalDirectoryPath() const;
         std::filesystem::path GetVerticalSettingsPath() const;
         std::filesystem::path GetHorizontalSettingsPath() const;
         std::filesystem::path GetVerticalExperimentPathById(int) const;
         std::filesystem::path GetHorizontalExperimentPathById(int) const;
         std::filesystem::path GetVerticalExperimentSettingsPathById(int) const;
         std::filesystem::path GetHorizontalExperimentSettingsPathById(int) const;

         static int NextId;

         explicit ExperimentDirectory(std::filesystem::path);
         ~ExperimentDirectory();
      };
   }
}
