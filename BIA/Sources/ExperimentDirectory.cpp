#include "ExperimentDirectory.h"

namespace BIA
{
   namespace FileManagement
   {
      ExperimentDirectory::ExperimentDirectory()
      {
         _parentPath = "";
         _horizontalPath = "";
         _verticalPath = "";
         _settingsPath = "";
         _infoPath = "";
         _horizontalImagePath = "";
         _verticalImagePath = "";
      }

      ExperimentDirectory::~ExperimentDirectory()
      {
      }

      std::string ExperimentDirectory::GetParentPath() const
      {
         return _parentPath;
      }

      std::string ExperimentDirectory::GetHorizontalPath() const
      {
         return _horizontalPath;
      }

      std::string ExperimentDirectory::GetVerticalPath() const
      {
         return _verticalPath;
      }

      std::string ExperimentDirectory::GetSettingsPath() const
      {
         return _settingsPath;
      }

      std::string ExperimentDirectory::GetInfoPath() const
      {
         return _infoPath;
      }

      std::string ExperimentDirectory::GetHorizontalImagePath() const
      {
         return _horizontalImagePath;
      }

      std::string ExperimentDirectory::GetVerticalImagePath() const
      {
         return _verticalImagePath;
      }

      std::string ExperimentDirectory::GetResultPath() const
      {
         return _resultPath;
      }

      void ExperimentDirectory::SetParentPath(std::string& parentPath)
      {
         _parentPath = parentPath;
      }

      void ExperimentDirectory::SetHorizontalPath(std::string& horizontalPath)
      {
         _horizontalPath = horizontalPath;
      }

      void ExperimentDirectory::SetVerticalPath(std::string& verticalPath)
      {
         _verticalPath = verticalPath;
      }

      void ExperimentDirectory::SetSettingsPath(std::string& settingsPath)
      {
         _settingsPath = settingsPath;
      }

      void ExperimentDirectory::SetInfoPath(std::string& infoPath)
      {
         _infoPath = infoPath;
      }

      void ExperimentDirectory::SetHorizontalImagePath(std::string& horizontalImagePath)
      {
         _horizontalImagePath = horizontalImagePath;
      }

      void ExperimentDirectory::SetVerticalImagePath(std::string& verticalImagePath)
      {
         _verticalImagePath = verticalImagePath;
      }

      void ExperimentDirectory::SetResultPath(std::string& resultPath)
      {
         _resultPath = resultPath;
      }
   }
}