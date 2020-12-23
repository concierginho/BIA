#pragma once

#include <vector>
#include <filesystem>

namespace BIA
{
   namespace FileManagement
   {
      class SubExperimentDirectory
      {
      private:
         std::filesystem::path _imagePath;
         std::filesystem::path _imagePreviewPath;
         std::filesystem::path _settingsPath;
      public:
         std::filesystem::path GetImagePath();
         std::filesystem::path GetImagePreviewPath();
         std::filesystem::path GetSettingsPath();

         explicit SubExperimentDirectory(const std::string&, const std::string&, const std::string&);
         SubExperimentDirectory();
         ~SubExperimentDirectory();
      };
   }
}
