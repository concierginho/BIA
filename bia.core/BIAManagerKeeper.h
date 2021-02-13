#ifndef _BIA_MANAGER_KEEPER_
#define _BIA_MANAGER_KEEPER_

#include <memory>

#include "BIA.h"

#include "IFileManager.h"
#include "IExperimentManager.h"
#include "IImageManager.h"
#include "ILoggingManager.h"
#include "IProcessManager.h"

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

      std::shared_ptr<IFileManager> GetFileManager();
      std::shared_ptr<IExperimentManager> GetExperimentManager();
      std::shared_ptr<IImageManager> GetImageManager();
      std::shared_ptr<IProcessManager> GetProcessManager();
#ifdef _LOGGING_
      std::shared_ptr<ILoggingManager> GetLoggingManager();
#endif
   public:
      std::string GetRootPath();

      BIAManagerKeeper(char*, BIA*);
      ~BIAManagerKeeper();

      virtual void Init() override;
   };
}

#endif
