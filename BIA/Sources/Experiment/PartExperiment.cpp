#include "PartExperiment.h"

namespace BIA::Experiment
{
   int PartExperiment::ID = 0;

   bool PartExperiment::HaveTIFFImage() const
   {
      if (_TIFF.empty())
         return false;
      return true;
   }

   bool PartExperiment::HaveResultsFile() const
   {
      if (_results.empty())
         return false;
      return true;
   }

   bool PartExperiment::HaveSettingsFile() const
   {
      if (_settings.empty())
         return false;
      return true;
   }

   int PartExperiment::GetNextId() const
   {
      ID++;
      return ID - 1;
   }

   PartExperiment::PartExperiment(fs::path path)
   {
      _id = GetNextId();
      _path = path;

      _haveTIFFImage = false;
      _haveResultsFile = false;
      _haveSettingsFile = false;
   }

   PartExperiment::~PartExperiment()
   {
   }
}
