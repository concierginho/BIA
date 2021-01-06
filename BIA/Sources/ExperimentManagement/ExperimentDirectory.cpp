#include "ExperimentDirectory.h"

#include <sstream>

namespace BIA
{
   namespace ExperimentManagement
   {
      ExperimentDirectory::ExperimentDirectory(std::filesystem::path path)
      {
         _path = path;
      }

      ExperimentDirectory::~ExperimentDirectory()
      {
      }

      std::filesystem::path ExperimentDirectory::GetPath() const
      {
         return _path;
      }

      std::filesystem::path ExperimentDirectory::GetVerticalDirectoryPath() const
      {
         std::stringstream verticalDirectory;
         verticalDirectory << _path << "\\Horizontal";
         return std::filesystem::path(verticalDirectory.str());
      }

      std::filesystem::path ExperimentDirectory::GetHorizontalDirectoryPath() const
      {
         std::stringstream horizontalDirectory;
         horizontalDirectory << _path << "\\Vertical";
         return std::filesystem::path(horizontalDirectory.str());
      }

      std::filesystem::path ExperimentDirectory::GetHorizontalExperimentPathById(int id) const
      {
         std::stringstream horizontalExperiment;
         horizontalExperiment << GetHorizontalDirectoryPath() << "\\" << id;
         return std::filesystem::path(horizontalExperiment.str());
      }

      std::filesystem::path ExperimentDirectory::GetVerticalExperimentPathById(int id) const
      {
         std::stringstream verticalExperiment;
         verticalExperiment << GetVerticalDirectoryPath() << "\\" << id;
         return std::filesystem::path(verticalExperiment.str());
      }
   }
}
