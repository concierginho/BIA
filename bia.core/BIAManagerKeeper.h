#ifndef _HOLDER_
#define _HOLDER_

#include <memory>

#include "BIAFileManager.h"
#include "BIAExperimentManager.h"
#include "BIAImageManager.h"
#include "BIALoggingManager.h"
#include "BIAProcessManager.h"
#include "BIA.h"

namespace BIA
{
   class BIAManagerKeeper : public IManager
   {
   private:
      BIA* _bia;
   public:
      std::shared_ptr<IFileManager> _fileManager;
      std::shared_ptr<IExperimentManager> _experimentManager;
      std::shared_ptr<IImageManager> _imageManager;
      std::shared_ptr<IProcessManager> _processManager;
#ifdef _LOGGING_
      std::shared_ptr<ILoggingManager> _loggingManager;
#endif
      std::vector<std::shared_ptr<IManager>> _managers;

      std::string _rootPath;

      std::shared_ptr<BIAFileManager> GetFileManagerAsBIAFileManager();
      std::shared_ptr<BIAExperimentManager> GetExperimentManagerAsBIAExperimentManager();
      std::shared_ptr<BIAImageManager> GetImageManagerAsBIAImageManager();
      std::shared_ptr<BIAProcessManager> GetProcessManagerAsBIAProcessManager();
#ifdef _LOGGING_
      std::shared_ptr<BIALoggingManager> GetLoggingManagerAsBIALoggingMenager();
#endif
   public:
      std::string GetRootPath();

      BIAManagerKeeper(char*, BIA*);
      ~BIAManagerKeeper();

      virtual void Init() override;
   };
}

#endif
