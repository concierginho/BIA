#include "ExperimentDirectory.h"
#include "../Logger/ILogger.h"

namespace BIA
{
   namespace Experiment
   {
      ExperimentDirectory::ExperimentDirectory(Logger::ILogger* logger)
      {
         _logger = logger;
      }

      ExperimentDirectory::~ExperimentDirectory()
      {
         _logger = nullptr;
      }

      void ExperimentDirectory::AddVerticalExperiment(std::filesystem::path& path)
      {
         _verticalExperiments.push_back(path);
      }

      void ExperimentDirectory::AddHorizontalExperiment(std::filesystem::path& path)
      {
         _horizontalExperiments.push_back(path);
      }

      void ExperimentDirectory::SetParentPath(std::filesystem::path& path)
      {
         _parent = path;
      }

      std::filesystem::path ExperimentDirectory::GetParentPath() const
      {
         return _parent;
      }

      void ExperimentDirectory::SetVerticalDirectoryPath(std::filesystem::path& path)
      {
         _verticalDir = path;
      }

      std::filesystem::path ExperimentDirectory::GetVerticalDirectoryPath() const
      {
         return _verticalDir;
      }

      void ExperimentDirectory::SetHorizontalDirectoryPath(std::filesystem::path& path)
      {
         _horizontalDir = path;
      }

      std::filesystem::path ExperimentDirectory::GetHorizontalDirectoryPath() const
      {
         return _horizontalDir;
      }

      void ExperimentDirectory::SetSettingsPath(std::filesystem::path& path)
      {
         _settings = path;
      }

      std::filesystem::path ExperimentDirectory::GetSettingsPath() const
      {
         return _settings;
      }

      void ExperimentDirectory::SetResultPath(std::filesystem::path& path)
      {
         _result = path;
      }

      std::filesystem::path ExperimentDirectory::GetResultPath() const
      {
         return _result;
      }

      void ExperimentDirectory::SetInformationPath(std::filesystem::path& path)
      {
         _info = path;
      }

      std::filesystem::path ExperimentDirectory::GetInformationPath() const
      {
         return _info;
      }

      void ExperimentDirectory::SetHorizontalImagePath(std::filesystem::path& path)
      {
         _horizontalImage = path;
      }

      std::filesystem::path ExperimentDirectory::GetHorizontalImagePath() const
      {
         return _horizontalImage;
      }

      void ExperimentDirectory::SetVerticalImagePath(std::filesystem::path& path)
      {
         _verticalImage = path;
      }

      std::filesystem::path ExperimentDirectory::GetVerticalImagePath() const
      {
         return _verticalImage;
      }
   }
}
