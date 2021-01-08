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

         _msg << "\n"
            << std::setw(2) << std::setfill('0') << timeinfo.tm_mday << "."
            << std::setw(2) << std::setfill('0') << timeinfo.tm_mon + 1 << "."
            << 1900 + timeinfo.tm_year << " -- "
            << std::setw(2) << std::setfill('0') << timeinfo.tm_hour << ":"
            << std::setw(2) << std::setfill('0') << timeinfo.tm_min << ":"
            << std::setw(2) << std::setfill('0') << timeinfo.tm_sec << "\n"
            << message.str();

         _logFile << _msg.str();
      }

      void FileLogger::Prepare()
      {
         CreateLogDirectory();
         CreateLogFile();

         _logFile.open(_logFilePath.string(), std::ios::in);
         std::stringstream msg;
         msg << "############################\n"
            << "### BLOOD IMAGE ANALYSER ###\n"
            << "###       AGH 2021       ###\n"
#ifdef _DEBUG
            << "###     DEBUG VERSION    ###\n"
#endif
#ifdef NDEBUG
            << "###    RELEASE VERSION   ###\n"
#endif
            << "############################\n";
            _logFile << msg.str();
      }

      void FileLogger::SetLogDirectoryPath(const std::filesystem::path& logDirectoryPath)
      {
         _logDirectoryPath = logDirectoryPath;
      }

      void FileLogger::CreateLogDirectory()
      {
         if(!std::filesystem::exists(_logDirectoryPath))
            std::filesystem::create_directory(_logDirectoryPath);
      }

      void FileLogger::CreateLogFile()
      {
         auto in_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
         tm timeinfo;

         localtime_s(&timeinfo, &in_time_t);

         std::stringstream logFilePath;
         std::stringstream logFilename;

#ifdef _DEBUG
         logFilename << "debug-";
#elif NDEBUG
         logFilename << "release-";
#endif

         logFilename << "on-"
            << std::setw(2) << std::setfill('0') << timeinfo.tm_mday << "-"
            << std::setw(2) << std::setfill('0') << timeinfo.tm_mon + 1 << "-"
            << 1900 + timeinfo.tm_year << "-at-"
            << std::setw(2) << std::setfill('0') << timeinfo.tm_hour << "-"
            << std::setw(2) << std::setfill('0') << timeinfo.tm_min << "-"
            << std::setw(2) << std::setfill('0') << timeinfo.tm_sec << ".txt";
         logFilePath << _logDirectoryPath.string() << "\\" << logFilename.str();

         _logFilePath = std::filesystem::path(logFilePath.str());
         std::ofstream logFile{ _logFilePath.string() };
      }

      FileLogger::FileLogger(std::string rootPath)
      {
         std::stringstream logDirectoryPath;
         logDirectoryPath << rootPath << "\\log";
         SetLogDirectoryPath(std::filesystem::path(logDirectoryPath.str()));
      }

      FileLogger::~FileLogger()
      {
         _logFile.close();
      }
   }
}
