#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>

#include "ILogger.h"
#include "../FileManagement/FileManager.h"

namespace BIA
{
   namespace Logging
   {
      class FileLogger : public ILogger
      {
      private:
         std::string _rootPath;
         std::filesystem::path _logPath;
         std::ofstream _logFile;
      public:
         void Log(const std::stringstream&) override;
         void SetLogPath(const std::filesystem::path&);
         void CreateLogFile();

         FileLogger(std::string);
         virtual ~FileLogger();
      };
   }
}
