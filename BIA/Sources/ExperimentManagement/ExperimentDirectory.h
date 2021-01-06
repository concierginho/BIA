#pragma once

#include <vector>
#include <string>

namespace BIA
{
   namespace ExperimentManagement
   {
      class ExperimentDirectory
      {
      private:
         std::string _verticalDirectoryPath;
         std::string _horizontalDirectoryPath;
      public:
         void SetVerticalDirectoryPath(std::string);
         std::string GetVerticalDirectoryPath() const;

         void SetHorizontalDirectoryPath(std::string);
         std::string GetHorizontalDirectoryPath() const;

         std::string GetVerticalExperimentById(int) const;
         std::string GetHorizontalExperimentById(int) const;

         ExperimentDirectory();
         ~ExperimentDirectory();
      };
   }
}
