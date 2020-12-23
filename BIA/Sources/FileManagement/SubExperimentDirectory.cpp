#include "SubExperimentDirectory.h"

namespace BIA
{
   namespace FileManagement
   {
      SubExperimentDirectory::SubExperimentDirectory(const std::string& imagePath, const std::string& imagePreviewPath, const std::string& settingsPath)
      {
         _imagePath = std::filesystem::path(imagePath);
         _imagePreviewPath = std::filesystem::path(imagePreviewPath);
         _settingsPath = std::filesystem::path(settingsPath);
      }

      SubExperimentDirectory::SubExperimentDirectory()
      {
      }

      SubExperimentDirectory::~SubExperimentDirectory()
      {
      }

      std::filesystem::path SubExperimentDirectory::GetImagePath()
      {
         return _imagePath;
      }

      std::filesystem::path SubExperimentDirectory::GetImagePreviewPath()
      {
         return _imagePreviewPath;
      }

      std::filesystem::path SubExperimentDirectory::GetSettingsPath()
      {
         return _settingsPath;
      }
   }
}