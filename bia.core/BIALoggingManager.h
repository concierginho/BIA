#ifndef _BIA_LOGGING_MANAGER_
#define _BIA_LOGGING_MANAGER_

#include "ILoggingManager.h"
#include "IFileManager.h"
#include "ILogger.h"
#include "EType.h"

namespace BIA
{
   class BIALoggingManager : public ILoggingManager
   {
   private:
      std::shared_ptr<ILogger> _logger;
      std::shared_ptr<IFileManager> _fileManager;

      std::string _rootPath;

      void Flush();
   public:
      static std::stringstream Message;

      BIALoggingManager(EType, std::shared_ptr<IFileManager>);
      ~BIALoggingManager();

      virtual void Init() override;
      virtual void Log(ESource) override;
   };
}

#endif
