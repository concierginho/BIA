#ifndef _BIA_IMAGE_MANAGER_
#define _BIA_IMAGE_MANAGER_

#include "IImageManager.h"
#include "BIAExperimentManager.h"
#include "BIALoggingManager.h"
#include "tiffio.h"
#include "EOperation.h"
#include "IOperation.h"

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
#ifdef _LOGGING_
      BIAImageManager(std::shared_ptr<BIAExperimentManager> experimentManager, std::shared_ptr<BIALoggingManager> loggingManager);
#endif
      BIAImageManager(std::shared_ptr<BIAExperimentManager> experimentManager, std::shared_ptr<BIAFileManager> fileManager);
      ~BIAImageManager();

      void ReadImageSettings(TIFF*, TIFFImage*);
      void CopyHorizontalPartImageToDestinationFile(TIFF** src, TIFFImage* parentImg, TIFF** tar, TIFFImage* childImg, int id);
      void CopyVerticalPartImageToDestinationFile(TIFF** src, TIFFImage* parentImg, TIFF** tar, TIFFImage* childImg, int id);
      void SaveResultsToFile(PartExperiment& partExperiment, std::unordered_map<int, std::vector<int>> map);

      void GeneratePreviews(std::atomic<bool>& cancelled, std::atomic<int>& biaProgress);
      void SplitImages(std::atomic<bool>& cancelled, std::atomic<int>& biaProgress);
      void PerformOperations(std::atomic<bool>& cancelled, std::atomic<int>& operationProgress);

      virtual void Init() override;

      void AdjustScanline(unsigned char* array, int length);
      void BinarizeScanline(unsigned char* destination, int length, unsigned char threshold);
   };
}

#endif
