#pragma once

#include <vector>

#include "SubExperimentDirectory.h"

namespace BIA
{
   namespace FileManagement
   {
      class ExperimentDirectory
      {
      private:
         std::vector<SubExperimentDirectory> _horizontalSubExperiments;
         std::vector<SubExperimentDirectory> _verticalSubExperiments;

         std::filesystem::path _experimentSettingsPath;
      public:
         SubExperimentDirectory GetHorizontalSubExperiment(int index) const;
         SubExperimentDirectory GetVerticalSubExperiment(int index) const;

         void SetExperimentSettingsPath(std::filesystem::path& experimentGlobalSettingsPath);
         std::filesystem::path GetExperimentSettingsPath() const;

         void SetHorizontalSubExperiments(std::vector<SubExperimentDirectory>& horizontalSubExperiments);
         std::vector<SubExperimentDirectory>& GetHorizontalSubExperiments();

         void SetVerticalSubExperiments(std::vector<SubExperimentDirectory>& verticalSubExperiments);
         std::vector<SubExperimentDirectory>& GetVerticalSubExperiments();

         ExperimentDirectory();
         ~ExperimentDirectory();
      };
   }

}