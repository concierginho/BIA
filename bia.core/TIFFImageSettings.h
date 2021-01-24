#ifndef _TIFF_IMAGE_SETTINGS_
#define _TIFF_IMAGE_SETTINGS_

#include "tiffio.h"

namespace BIA
{
   struct TIFFImageSettings
   {
      uint32 ImageWidth;
      uint32 ImageLength;
      uint32 ScanlineSize;
      uint16 BitsPerSample;
      uint16 SamplesPerPixel;
      uint16 ResolutionUnit;
   };
}

#endif
