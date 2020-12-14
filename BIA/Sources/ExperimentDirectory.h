#pragma once

#include <string>

namespace BIA
{
   namespace FileManagement
   {
      class ExperimentDirectory
      {
      private:
         std::string _parentPath;
         std::string _horizontalPath;
         std::string _verticalPath;
         std::string _settingsPath;
         std::string _infoPath;
         std::string _horizontalImagePath;
         std::string _verticalImagePath;
         std::string _resultPath;
      public:
         std::string GetParentPath() const;
         std::string GetHorizontalPath() const;
         std::string GetVerticalPath() const;
         std::string GetSettingsPath() const;
         std::string GetInfoPath() const;
         std::string GetHorizontalImagePath() const;
         std::string GetVerticalImagePath() const;
         std::string GetResultPath() const;

         void SetParentPath(std::string&);
         void SetHorizontalPath(std::string&);
         void SetVerticalPath(std::string&);
         void SetSettingsPath(std::string&);
         void SetInfoPath(std::string&);
         void SetHorizontalImagePath(std::string&);
         void SetVerticalImagePath(std::string&);
         void SetResultPath(std::string&);

         explicit ExperimentDirectory();
         ~ExperimentDirectory();
      };
   }
}