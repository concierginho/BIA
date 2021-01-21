#ifndef _TIFF_MANAGER_
#define _TIFF_MANAGER_

#include "IManager.h"
#include "EOperationType.h"
#include "TIFFImageSettings.h"
#include "tiffio.h"

#include <filesystem>

namespace fs = std::filesystem;

namespace BIA
{
   class TIFFSettingsManager : public IManager
   {
   private:
      TIFFImageSettings _settings;
      TIFFImageSettings _parentSettings;
   public:
      virtual void Init() override;

      TIFFImageSettings ReadSettings(TIFF**);
      TIFFImageSettings GetPartImageSettings(TIFFImageSettings parentSettings);

      void ApplySettings(TIFF**, TIFFImageSettings tiffImageSettings);

      TIFFSettingsManager();
      ~TIFFSettingsManager();
   };
}

#endif
