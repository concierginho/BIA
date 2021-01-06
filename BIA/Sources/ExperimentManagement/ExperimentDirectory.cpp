#include "ExperimentDirectory.h"

namespace BIA
{
   namespace ExperimentManagement
   {
      ExperimentDirectory::ExperimentDirectory()
      {
      }

      ExperimentDirectory::~ExperimentDirectory()
      {
      }

      void ExperimentDirectory::SetVerticalDirectoryPath(std::string verticalDirectoryPath)
      {
         _verticalDirectoryPath = verticalDirectoryPath;
      }

      std::string ExperimentDirectory::GetVerticalDirectoryPath() const
      {
         return _verticalDirectoryPath;
      }

      void ExperimentDirectory::SetHorizontalDirectoryPath(std::string horizontalDirectoryPath)
      {
         _horizontalDirectoryPath = horizontalDirectoryPath;
      }

      std::string ExperimentDirectory::GetHorizontalExperimentById(int id) const
      {
         std::string experimentPath = _horizontalDirectoryPath;
         experimentPath += "\\" + id;
         return experimentPath;
      }

      std::string ExperimentDirectory::GetVerticalExperimentById(int id) const
      {
         std::string experimentPath = _verticalDirectoryPath;
         experimentPath += "\\" + id;
         return experimentPath;
      }
   }
}
