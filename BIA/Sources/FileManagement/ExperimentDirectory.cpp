#include "ExperimentDirectory.h"

namespace BIA
{
   namespace FileManagement
   {
      SubExperimentDirectory FileManagement::ExperimentDirectory::GetHorizontalSubExperiment(int index) const
      {
         return _horizontalSubExperiments[index];
      }

      SubExperimentDirectory FileManagement::ExperimentDirectory::GetVerticalSubExperiment(int index) const
      {
         return _verticalSubExperiments[index];
      }

      void ExperimentDirectory::SetHorizontalSubExperiments(std::vector<SubExperimentDirectory>& horizontalSubExperiments)
      {
         _horizontalSubExperiments = horizontalSubExperiments;
      }

      std::vector<SubExperimentDirectory>& ExperimentDirectory::GetHorizontalSubExperiments()
      {
         return _horizontalSubExperiments;
      }

      void ExperimentDirectory::SetVerticalSubExperiments(std::vector<SubExperimentDirectory>& verticalSubExperiments)
      {
         _verticalSubExperiments = verticalSubExperiments;
      }

      std::vector<SubExperimentDirectory>& ExperimentDirectory::GetVerticalSubExperiments()
      {
         return _verticalSubExperiments;
      }

      void ExperimentDirectory::SetExperimentSettingsPath(std::filesystem::path& experimentGlobalSettingsPath)
      {
         _experimentSettingsPath = experimentGlobalSettingsPath;
      }

      std::filesystem::path ExperimentDirectory::GetExperimentSettingsPath() const
      {
         return _experimentSettingsPath;
      }

      ExperimentDirectory::ExperimentDirectory() {}

      ExperimentDirectory::~ExperimentDirectory() {}
   }

}