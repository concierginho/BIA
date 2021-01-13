#pragma once

#include <filesystem>
#include <string>

#include "PartExperiment.h"

namespace fs = std::filesystem;

namespace BIA::Experiment
{
   class Experiment
   {
   private:
      std::string _name;
      fs::path _path;
   public:
      static fs::path VerticalDirectoryPathRecipe(fs::path);
      static fs::path HorizontalDirectoryPathRecipe(fs::path);

      std::string GetName() const;
      fs::path GetPath() const;

      fs::path GetVerticalDirectoryPath() const;
      fs::path GetHorizontalDirectoryPath() const;

      std::vector<PartExperiment> _partExperiments;

      Experiment(fs::path&, std::string&);
      ~Experiment();
   };
}
