#ifndef _BIA_IMAGE_MANAGER_
#define _BIA_IMAGE_MANAGER_

#include "IImageManager.h"
#include "BIAExperimentManager.h"
#include "BIALoggingManager.h"
#include "tiffio.h"

namespace BIA
{
   class BIAImageManager : public IImageManager
   {
   private:
      std::shared_ptr<BIAExperimentManager> _experimentManager;
      std::shared_ptr<BIAFileManager> _fileManager;
#ifdef _LOGGING_
      std::shared_ptr<BIALoggingManager> _loggingManager;
#endif
   public:
      BIAImageManager(std::shared_ptr<BIAExperimentManager> experimentManager);
#ifdef _LOGGING_
      BIAImageManager(std::shared_ptr<BIAExperimentManager> experimentManager, std::shared_ptr<BIALoggingManager> loggingManager);
#endif
      ~BIAImageManager();

      void SplitImages();
      void ReadImageSettings(TIFF*, TIFFImage*);
      void CopyHorizontalPartImageToDestinationFile(TIFF** src, TIFFImage* parentImg, TIFF** tar, TIFFImage* childImg, int id);
      void CopyVerticalPartImageToDestinationFile(TIFF** src, TIFFImage* parentImg, TIFF** tar, TIFFImage* childImg, int id);

      virtual void Init() override;
   };
}

#endif