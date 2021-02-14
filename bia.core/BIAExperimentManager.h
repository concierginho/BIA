#ifndef _BIA_EXPERIMENT_MANAGER_
#define _BIA_EXPERIMENT_MANAGER_

#include <memory>

#include "IExperimentManager.h"
#include "BIAFileManager.h"
#include "Experiment.h"
#include "PartExperiment.h"
#include "EOperation.h"

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

      Experiment* GetExperiment(const char* name);

      PartExperiment* GetPartExperiment(const char* name, int id, bool isHorizontal);

      bool AddOperation(const char* name, int id, bool isHorizontal, EOperation operation, const char* args) override;

      void PrepareExperiments();
      void LocalizeTIFFImages();
      void PreparePartExperiments();
      void PrepareRecipeJson(PartExperiment&);
      void MoveExistingFiles();
      void InitializePartExperiment(PartExperiment&);

      std::shared_ptr<BIAFileManager> GetFileManager();

      virtual std::vector<Experiment>& GetExperiments() override;
      virtual std::vector<PartExperiment>& GetPartExperiments(int idx, bool isHorizontal) override;

      virtual std::string GetExperimentName(int idx) override;
      virtual std::string GetPartExperimentImagePath(const char* name, int id, bool isHorizontal) override;
      virtual std::string GetPartExperimentPreviewImagePath(const char* name, int id, bool isHorizontal) override;
      virtual int GetExperimentsSize() override;

      virtual void Init() override;

   };
}

#endif
