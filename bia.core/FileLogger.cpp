#include "pch.h"

#include <chrono>
#include <sstream>

#include "FileLogger.h"
#include "IFileManager.h"

/// <summary>
/// Konstruktor klasy FileLogger.
/// </summary>
/// <param name="rootPath"></param>
/// <param name="fileManager"></param>
BIA::FileLogger::FileLogger(std::string rootPath, std::shared_ptr<IFileManager>& fileManager)
{
   _fileManager = fileManager;

   std::stringstream logDirPath;
   logDirPath << rootPath << "\\log";
   _logDirPath = fs::path(logDirPath.str());
}

/// <summary>
/// Destruktor klasy FileLogger.
/// </summary>
BIA::FileLogger::~FileLogger()
{

   _fileManager = nullptr;
}

/// <summary>
/// Cel: zapisanie zawartosci parametru message w pliku.
/// </summary>
/// <param name="source"></param>
/// <param name="message"></param>
void BIA::FileLogger::Log(ESource source, std::stringstream& message)
{
   _logFileObj.open(_logFilePath, std::ios::app);

   if (!_logFileObj.is_open())
      return;

   auto in_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
   tm timeinfo;

   localtime_s(&timeinfo, &in_time_t);

   std::stringstream _msg;
   _msg << "\n";

   switch (source)
   {
      case ESource::BIA:
         _msg << "BIA / ";
      case ESource::BIA_FILE_MANAGER:
         _msg << "BIA File Manager / ";
         break;
      case ESource::BIA_EXPERIMENT_MANAGER:
         _msg << "BIA Experiment Manager / ";
         break;
      case ESource::BIA_IMAGE_MANAGER:
         _msg << "BIA Image Manager / ";
         break;
      case ESource::BIA_PROCESS_MANAGER:
         _msg << "BIA Process Manager / ";
         break;
      case ESource::MEMORY_MANAGEMENT:
         _msg << "Memory Management / ";
         break;
      case ESource::TIME_MEASUREMENT:
         _msg << "Time Measurement / ";
         break;
   }

   _msg << std::setw(2) << std::setfill('0') << timeinfo.tm_mday << "."
      << std::setw(2) << std::setfill('0') << timeinfo.tm_mon + 1 << "."
      << 1900 + timeinfo.tm_year << " -- "
      << std::setw(2) << std::setfill('0') << timeinfo.tm_hour << ":"
      << std::setw(2) << std::setfill('0') << timeinfo.tm_min << ":"
      << std::setw(2) << std::setfill('0') << timeinfo.tm_sec << "\n"
      << message.str();

   _logFileObj << _msg.str();
   _logFileObj.close();
}

/// <summary>
/// Cel: Przygotowanie folderu "log" oraz pliku tekstowego, do ktorego beda trafiac logi.
/// </summary>
void BIA::FileLogger::Prepare()
{
   CreateLogDirectory();
   CreateLogFile();

   _logFileObj.open(_logFilePath.string(), std::ios::in);

   if (!_logFileObj.is_open())
      return;

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
   _logFileObj << msg.str();

   _logFileObj.close();
}

/// <summary>
/// Cel: Stworzenie folderu "log" wewnatrz glownego katalogu.
/// </summary>
void BIA::FileLogger::CreateLogDirectory()
{
   if (!_fileManager->ExistsAtPath(_logDirPath))
      _fileManager->CreateAtPath(_logDirPath, EFileType::DIRECTORY);
}

/// <summary>
/// Cel: Stworzenie pliku, do ktorego trafialy beda logi.
///      Jego nazwa wybierana jest na podstawie daty oraz czasu.
/// </summary>
void BIA::FileLogger::CreateLogFile()
{
   try
   {
      if (!_fileManager->ExistsAtPath(_logFilePath))
      {
         auto in_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
         tm timeinfo;

         localtime_s(&timeinfo, &in_time_t);

         std::stringstream logFilePath;
         std::stringstream logFilename;

#ifdef _DEBUG
         logFilename << "DEBUG.";
#elif NDEBUG
         logFilename << "RELEASE.";
#endif

         logFilename << "ON."
            << std::setw(2) << std::setfill('0') << timeinfo.tm_mday << "-"
            << std::setw(2) << std::setfill('0') << timeinfo.tm_mon + 1 << "-"
            << 1900 + timeinfo.tm_year << ".AT."
            << std::setw(2) << std::setfill('0') << timeinfo.tm_hour << "-"
            << std::setw(2) << std::setfill('0') << timeinfo.tm_min << "-"
            << std::setw(2) << std::setfill('0') << timeinfo.tm_sec << ".txt";
         logFilePath << _logDirPath.string() << "\\" << logFilename.str();

         _logFilePath = std::filesystem::path(logFilePath.str());
         std::ofstream logFile{ _logFilePath.string() };
      }
   }
   catch (std::exception e)
   {
      e;
   }
}
