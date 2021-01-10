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
         std::string _name;

         std::vector<std::filesystem::path> _horizontalDirectoryFiles;
         std::vector<std::filesystem::path> _verticalDirectoryFiles;
         
         std::filesystem::path _path;
         std::filesystem::path _horizontalImagePath;
         std::filesystem::path _verticalImagePath;

         bool _hasVerticalImage;
         bool _hasHorizontalImage;
         bool _hasVerticalSettingsJson;
         bool _hasHorizontalSettingsJson;
         bool _hasVerticalResultsJson;
         bool _hasHorizontalResultsJson;

         int Id;
      public:
         int GetId() const;

         void AddVerticalDirectoryContent(std::filesystem::path&);
         void AddHorizontalDirectoryContent(std::filesystem::path&);
         void SetVerticalImagePath(std::filesystem::path&);
         void SetHorizontalImagePath(std::filesystem::path&);
         void SetHasVerticalImage(bool);
         void SetHasHorizontalImage(bool);
         void SetHasVerticalSettingsJson(bool);
         void SetHasHorizontalSettingsJson(bool);
         void SetHasVerticalResultsJson(bool);
         void SetHasHorizontalResultsJson(bool);
         
         void SetExperimentName(std::string);
         std::string GetExperimentName() const;

         std::filesystem::path GetPath() const;
         std::filesystem::path GetVerticalDirectoryPath() const;
         std::filesystem::path GetHorizontalDirectoryPath() const;
         std::filesystem::path GetVerticalSettingsPath() const;
         std::filesystem::path GetHorizontalSettingsPath() const;
         std::filesystem::path GetVerticalExperimentPathById(int) const;
         std::filesystem::path GetHorizontalExperimentPathById(int) const;
         std::filesystem::path GetVerticalExperimentSettingsPathById(int) const;
         std::filesystem::path GetHorizontalExperimentSettingsPathById(int) const;
         std::filesystem::path GetVerticalExperimentResultsPathById(int) const;
         std::filesystem::path GetHorizontalExperimentResultsPathById(int) const;
         std::filesystem::path GetVerticalResultsPath() const;
         std::filesystem::path GetHorizontalResultsPath() const;
         std::filesystem::path GetVerticalImagePath() const;
         std::filesystem::path GetHorizontalImagePath() const;
         std::filesystem::path GetVerticalImagePathById(int) const;
         std::filesystem::path GetHorizontalImagePathById(int) const;

         bool HasVerticalImage() const;
         bool HasHorizontalImage() const;
         bool HasVerticalSettingsJson() const;
         bool HasHorizontalSettingsJson() const;
         bool HasVerticalResultsJson() const;
         bool HasHorizontalResultsJson() const;

         static int NextId;

         explicit ExperimentDirectory(std::filesystem::path);
         ~ExperimentDirectory();
      };
   }
}
