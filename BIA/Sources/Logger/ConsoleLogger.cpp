#include "ConsoleLogger.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>

namespace Logger
{
   void ConsoleLogger::Log(std::string message)
   {
      auto in_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
      tm timeinfo;

      localtime_s(&timeinfo, &in_time_t);

      printf("%d.%d.%d -- %d.%d.%d: ", timeinfo.tm_mday, timeinfo.tm_mon + 1,
         1900 + timeinfo.tm_year, timeinfo.tm_hour, timeinfo.tm_min,
         timeinfo.tm_sec);
      std::cout << message << std::endl;
   }

   ConsoleLogger::ConsoleLogger()
   {
   }

   ConsoleLogger::~ConsoleLogger()
   {
   }
}
