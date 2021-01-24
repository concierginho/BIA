#ifndef _PART_EXPERIMENT_
#define _PART_EXPERIMENT_

#include "TIFFImage.h"

#include <filesystem>

namespace fs = std::filesystem;

namespace BIA
{
   class PartExperiment
   {
   private:
      int _id;

      fs::path _path;
      std::string _name;

      TIFFImage* _tiffImage = nullptr;
   public:
      int GetId();

      void SetImagePath(fs::path imagePath);
      void SetTIFFImage(TIFFImage* tiffImage);

      fs::path GetPreviewPath() const;
      fs::path GetResultsJsonPath() const;
      fs::path GetInfoJsonPath() const;
      fs::path GetRecipeJsonPath() const;
      fs::path GetPreviewDirectory() const;
      fs::path GetImagePath() const;

      TIFFImage* GetTIFFImage();

      explicit PartExperiment(fs::path path, std::string parentName);
      ~PartExperiment();
   };
}

#endif
