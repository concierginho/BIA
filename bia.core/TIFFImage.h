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
      fs::path _path;
   public:
      TIFFImage(fs::path);
      ~TIFFImage();

      TIFFImageSettings Settings;

      fs::path GetPath();
   };
}

#endif
