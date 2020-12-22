#pragma once

#include <string>
#include <vector>
#include <filesystem>

namespace Logger
{
   class ILogger;
}

namespace BIA
{
   namespace Experiment
   {
      class ExperimentDirectory
      {
      private:
         std::vector<std::filesystem::path> _verticalExperiments;
         std::vector<std::filesystem::path> _horizontalExperiments;

         std::filesystem::path _parent;
         std::filesystem::path _verticalDir;
         std::filesystem::path _horizontalDir;
         std::filesystem::path _settings;
         std::filesystem::path _result;
         std::filesystem::path _info;
         std::filesystem::path _horizontalImage;
         std::filesystem::path _verticalImage;

         Logger::ILogger* _logger;
      public:
         explicit ExperimentDirectory(Logger::ILogger* logger);
         ~ExperimentDirectory();

         void AddVerticalExperiment(std::filesystem::path&);
         void AddHorizontalExperiment(std::filesystem::path&);

         void SetParentPath(std::filesystem::path&);
         std::filesystem::path GetParentPath() const;

         void SetVerticalDirectoryPath(std::filesystem::path&);
         std::filesystem::path GetVerticalDirectoryPath() const;

         void SetHorizontalDirectoryPath(std::filesystem::path&);
         std::filesystem::path GetHorizontalDirectoryPath() const;

         void SetSettingsPath(std::filesystem::path&);
         std::filesystem::path GetSettingsPath() const;

         void SetResultPath(std::filesystem::path&);
         std::filesystem::path GetResultPath() const;

         void SetInformationPath(std::filesystem::path&);
         std::filesystem::path GetInformationPath() const;

         void SetHorizontalImagePath(std::filesystem::path&);
         std::filesystem::path GetHorizontalImagePath() const;

         void SetVerticalImagePath(std::filesystem::path&);
         std::filesystem::path GetVerticalImagePath() const;
      };
   }
}