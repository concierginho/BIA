#ifndef _EXPERIMENT_
#define _EXPERIMENT_

#include <vector>
#include <filesystem>
#include <unordered_map>

#include "PartExperiment.h"
#include "EAlignment.h"
#include "TIFFImage.h"

namespace fs = std::filesystem;

namespace BIA
{
   class Experiment
   {
   private:
      std::unordered_map<EFolder, std::vector<PartExperiment>> _partExperimentsByAlignment;

      std::string _name;

      fs::path _path;

      TIFFImage* _vertTIFFImg;
      TIFFImage* _horTIFFImg;

      int _id;
   public:
      void IninitalizeTIFFImage(EFolder folder, fs::path path);

      TIFFImage* GetTIFFImage(EFolder folder);

      static int nextId;

      int GetNextId();

      explicit Experiment(fs::path);
      ~Experiment();

      fs::path GetPath();
      fs::path GetPath(EFolder);
      fs::path GetTIFFImagePath(EFolder folder);
      fs::path GetPartExperimentPathById(EFolder, int);

      PartExperiment* GetPartExperimentById(EFolder, int);

      std::string GetName() const;

      std::vector<PartExperiment>& GetPartExperiments(EFolder);
   };
}

#endif
