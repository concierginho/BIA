#ifndef _FILE_LOGGER_
#define _FILE_LOGGER_

#include <filesystem>
#include <iostream>
#include <fstream>

#include "ILogger.h"
#include "IFileManager.h"

namespace BIA
{
   class FileLogger : public ILogger
   {
   private:
      fs::path _logDirPath;
      fs::path _logFilePath;

      std::ofstream _logFileObj;

      std::shared_ptr<IFileManager> _fileManager;
   public:
      FileLogger(std::string, std::shared_ptr<IFileManager>&);
      ~FileLogger();

      virtual void Log(ESource, std::stringstream&) override;
      virtual void Prepare() override;

      void CreateLogDirectory();
      void CreateLogFile();
   };
}

#endif
