#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>

#include "ILogger.h"

namespace BIA
{
   namespace Management
   {
      class Manager;
   }

   namespace Logging
   {
      class FileLogger : public ILogger
      {
      private:
         std::filesystem::path _rootDirectoryPath;
         std::filesystem::path _logDirectoryPath;
         std::filesystem::path _logFilePath;
         std::ofstream _logFile;
      public:
         void Flush() override;

         void Log(Source) override;
         void Prepare() override;
         void SetLogDirectoryPath(const std::filesystem::path&);
         void CreateLogDirectory();
         void CreateLogFile();

         FileLogger(std::string);
         virtual ~FileLogger();
      };
   }
}
