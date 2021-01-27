#ifndef _TIFF_MANAGER_
#define _TIFF_MANAGER_

#include "IManager.h"
#include "TIFFImageSettings.h"
#include "tiffio.h"

#include <filesystem>

namespace fs = std::filesystem;

namespace BIA
{
   class TIFFSettingsManager : public IManager
   {
   public:
      virtual void Init() override;

      TIFFImageSettings ReadSettings(TIFF**);
      TIFFImageSettings GetPartImageSettings(TIFFImageSettings parentSettings);
      TIFFImageSettings GetPreviewImageSettings();

      void ApplySettings(TIFF**, TIFFImageSettings tiffImageSettings);

      TIFFSettingsManager();
      ~TIFFSettingsManager();
   };
}

#endif
