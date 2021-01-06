#pragma once

#include <vector>
#include <string>
#include <filesystem>

namespace BIA
{
   namespace ExperimentManagement
   {
      class ExperimentDirectory
      {
      private:
         std::filesystem::path _path;
      public:
         std::filesystem::path GetPath() const;
         std::filesystem::path GetVerticalDirectoryPath() const;
         std::filesystem::path GetHorizontalDirectoryPath() const;
         std::filesystem::path GetVerticalExperimentPathById(int) const;
         std::filesystem::path GetHorizontalExperimentPathById(int) const;

         explicit ExperimentDirectory(std::filesystem::path);
         ~ExperimentDirectory();
      };
   }
}
