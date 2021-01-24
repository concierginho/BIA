#ifndef _TIFF_IMAGE_
#define _TIFF_IMAGE_

#include "tiffio.h"
#include "TIFFImageSettings.h"

#include <filesystem>

namespace fs = std::filesystem;

namespace BIA
{
   class TIFFImage
   {
   private:
      TIFFImageSettings _settings;

      fs::path _image_path;
      fs::path _preview_path;
   public:
      void SetImagePath(fs::path image_path);
      fs::path GetImagePath() const;

      void SetPreviewImagePath(fs::path preview_path);
      fs::path GetPreviewImagePath() const;

      void SetImageSettings(TIFFImageSettings settings);
      TIFFImageSettings& GetImageSettings();

      TIFFImage();
      ~TIFFImage();
   };
}

#endif
