#ifndef _BIA_EXPERIMENT_MANAGER_
#define _BIA_EXPERIMENT_MANAGER_

#include <memory>

#include "IExperimentManager.h"
#include "BIAFileManager.h"
#include "Experiment.h"

#ifdef _LOGGING_
#include "BIALoggingManager.h"
#endif

namespace BIA
{
   class BIAExperimentManager : public IExperimentManager
   {
   private:
#ifdef _LOGGING_
      std::shared_ptr<BIALoggingManager> _loggingManager;
#endif
      std::shared_ptr<BIAFileManager> _fileManager;

      std::vector<Experiment> _experiments;
   public:
#ifdef _LOGGING_
      BIAExperimentManager(std::shared_ptr<BIAFileManager>, std::shared_ptr<BIALoggingManager>);
#endif
      BIAExperimentManager(std::shared_ptr<BIAFileManager>);
      ~BIAExperimentManager();

      void PrepareExperiments();
      void LocalizeTIFFImages();
      void PreparePartExperiments();
      void MoveExistingFiles();
      void InitializePartExperiment(PartExperiment&);

      std::shared_ptr<BIAFileManager> GetFileManager();

      std::vector<Experiment>& GetExperiments();

      virtual void Init() override;
   };
}

#endif
