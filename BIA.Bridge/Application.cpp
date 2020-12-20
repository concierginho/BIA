#include "pch.h"
#include "Application.h"

namespace BIA::Bridge
{
   Application::Application()
   {
   }

   Application::~Application()
   {
   }

   Application::!Application()
   {
   }

   void Application::SetHinstance(HINSTANCE& instance)
   {
      _instance = instance;
   }

   HINSTANCE Application::GetHinstance()
   {
      return _instance;
   }

   void Application::SetShowStatus(int showStatus)
   {
      _showStatus = showStatus;
   }

   int Application::GetShowStatus()
   {
      return _showStatus;
   }

   void Application::SetArguments(System::String^ arguments)
   {
      _arguments = arguments;
   }

   System::String^ Application::GetArguments()
   {
      return _arguments;
   }
}
