#include "Experiment.h"

#include <sstream>

namespace BIA
{
   namespace Experiment
   {
      fs::path Experiment::VerticalDirectoryPathRecipe(fs::path experimentPath)
      {
         std::stringstream verticalDirPath;
         verticalDirPath << experimentPath.string() << "\\Vertical";
         return fs::path(verticalDirPath.str());
      }

      fs::path Experiment::HorizontalDirectoryPathRecipe(fs::path experimentPath)
      {
         std::stringstream horizontalDirPath;
         horizontalDirPath << experimentPath.string() << "\\Horizontal";
         return fs::path(horizontalDirPath.str());
      }

      std::string Experiment::GetName() const
      {
         return _name;
      }

      fs::path Experiment::GetPath() const
      {
         return _path;
      }

      fs::path Experiment::GetVerticalDirectoryPath() const
      {
         if (!GetPath().empty())
            return fs::path(VerticalDirectoryPathRecipe(GetPath()));
         return fs::path();
      }

      fs::path Experiment::GetHorizontalDirectoryPath() const
      {
         if(!GetPath().empty())
            return fs::path(HorizontalDirectoryPathRecipe(GetPath()));
         return fs::path();
      }

      Experiment::Experiment(fs::path& path, std::string& name)
      {
         _path = path;
         _name = name;
      }

      Experiment::~Experiment()
      {
      }
   }
}