#include <chrono>
#include <sstream>

#include "FileLogger.h"

namespace BIA
{
   namespace Logging
   {
      void FileLogger::Log(const std::stringstream& message)
      {
         auto in_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
         tm timeinfo;

         localtime_s(&timeinfo, &in_time_t);

         std::stringstream _msg;

         _msg << std::setw(2) << std::setfill('0') << timeinfo.tm_mday << "."
            << std::setw(2) << std::setfill('0') << timeinfo.tm_mon + 1 << "."
            << 1900 + timeinfo.tm_year << " -- "
            << std::setw(2) << std::setfill('0') << timeinfo.tm_hour << ":"
            << std::setw(2) << std::setfill('0') << timeinfo.tm_min << ":"
            << std::setw(2) << std::setfill('0') << timeinfo.tm_sec << " -- "
            << message.str() << std::endl;

         _logFile << _msg.str();
      }

      void FileLogger::SetLogPath(const std::filesystem::path& logPath)
      {
         _logPath = logPath;

         CreateLogFile();
         _logFile.open(_logPath, std::ios::in);
      }

      void FileLogger::CreateLogFile()
      {
         auto in_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
         tm timeinfo;

         localtime_s(&timeinfo, &in_time_t);

         std::stringstream filename;

         filename << std::setw(2) << std::setfill('0') << timeinfo.tm_mday << "."
            << std::setw(2) << std::setfill('0') << timeinfo.tm_mon + 1 << "."
            << 1900 + timeinfo.tm_year << " at "
            << std::setw(2) << std::setfill('0') << timeinfo.tm_hour << "."
            << std::setw(2) << std::setfill('0') << timeinfo.tm_min << "."
            << std::setw(2) << std::setfill('0') << timeinfo.tm_sec;

         std::stringstream logFile;
         logFile << _logPath.string() << "\\log\\" << filename.str() << ".txt";

         _logPath = std::filesystem::path(logFile.str());

         if (std::filesystem::exists(_logPath))
            return;

         std::ofstream file{ _logPath.string() };
      }

      FileLogger::FileLogger(std::string rootPath)
      {
         SetLogPath(std::filesystem::path(rootPath));
      }

      FileLogger::~FileLogger()
      {
         _logFile.close();
      }
   }
}
//
//auto in_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
//tm timeinfo;
//
//localtime_s(&timeinfo, &in_time_t);
//
//std::stringstream _msg;
//
//_msg << std::setw(2) << std::setfill('0') << timeinfo.tm_mday << "."
//<< std::setw(2) << std::setfill('0') << timeinfo.tm_mon + 1 << "."
//<< 1900 + timeinfo.tm_year << " -- "
//<< std::setw(2) << std::setfill('0') << timeinfo.tm_hour << ":"
//<< std::setw(2) << std::setfill('0') << timeinfo.tm_min << ":"
//<< std::setw(2) << std::setfill('0') << timeinfo.tm_sec << " -- "
//<< message.str();
//
//std::cout << _msg.str() << std::endl;
