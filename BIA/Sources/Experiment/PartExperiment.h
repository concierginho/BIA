#pragma once

#include <filesystem>

namespace fs = std::filesystem;

namespace BIA::Experiment
{
   class PartExperiment
   {
   public:
      static int ID;

      bool HaveTIFFImage() const;
      bool HaveResultsFile() const;
      bool HaveSettingsFile() const;

      explicit PartExperiment(fs::path);
      ~PartExperiment();
   private:
      fs::path _path;
      fs::path _TIFF;
      fs::path _results;
      fs::path _settings;

      int _id;

      int GetNextId() const;

      bool _haveTIFFImage;
      bool _haveResultsFile;
      bool _haveSettingsFile;
   };
}

