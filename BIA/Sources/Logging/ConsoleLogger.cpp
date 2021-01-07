#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>

#include "ConsoleLogger.h"

namespace BIA
{
   namespace Logging
   {
      void ConsoleLogger::Log(const std::stringstream& message)
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
            << message.str();

         std::cout << _msg.str() << std::endl;
      }

      ConsoleLogger::ConsoleLogger()
      {
      }

      ConsoleLogger::~ConsoleLogger()
      {
      }
   }

}