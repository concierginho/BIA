#ifndef _PART_EXPERIMENT_
#define _PART_EXPERIMENT_

#include "TIFFImage.h"

#include <filesystem>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

namespace BIA
{
   class PartExperiment
   {
   private:
      int _id;
      bool _isHorizontal;

      fs::path _path;
      fs::path _common;
      std::string _name;

      TIFFImage* _tiffImage = nullptr;
   public:
      int GetId();

      void SetImagePath(fs::path imagePath);
      void SetTIFFImage(TIFFImage* tiffImage);

      fs::path GetResultsJsonPath() const;
      fs::path GetRecipeJsonPath() const;
      fs::path GetImagePath() const;
      fs::path GetPreviewImagePath() const;
      fs::path GetResultsCommon() const;

      TIFFImage* GetTIFFImage();

      explicit PartExperiment(fs::path path, std::string parentName, bool isHorizontal, fs::path common);
   };
}

#endif
