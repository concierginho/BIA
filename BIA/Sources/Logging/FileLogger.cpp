#include <chrono>
#include <sstream>

#include "FileLogger.h"

namespace BIA
{
   namespace Logging
   {
      std::stringstream FileLogger::Message;

      void FileLogger::Flush()
      {
         Message.str(std::string());
      }

      void FileLogger::Log(Source source)
      {
         auto in_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
         tm timeinfo;

         localtime_s(&timeinfo, &in_time_t);

         std::stringstream _msg;
         _msg << "\n";

         switch (source)
         {
            case Source::FILE_MANAGER:
               _msg << "File Manager / ";
               break;
            case Source::EXPERIMENT_MANAGER:
               _msg << "Experiment Manager / ";
               break;
            case Source::IMAGE_MANAGER:
               _msg << "Image Manager / ";
               break;
            case Source::MEMORY_MANAGEMENT:
               _msg << "Memory Management / ";
               break;
            case Source::TIME_MEASUREMENT:
               _msg << "Time Measurement / ";
               break;
         }

         _msg << std::setw(2) << std::setfill('0') << timeinfo.tm_mday << "."
            << std::setw(2) << std::setfill('0') << timeinfo.tm_mon + 1 << "."
            << 1900 + timeinfo.tm_year << " -- "
            << std::setw(2) << std::setfill('0') << timeinfo.tm_hour << ":"
            << std::setw(2) << std::setfill('0') << timeinfo.tm_min << ":"
            << std::setw(2) << std::setfill('0') << timeinfo.tm_sec << "\n"
            << Message.str();

         _logFile << _msg.str();
         Flush();
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

         Message.str(std::string());
      }

      FileLogger::~FileLogger()
      {
         _logFile.close();
      }
   }
}
