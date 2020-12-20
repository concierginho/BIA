#pragma once

#include <string>
#include <Windows.h>

namespace BIA::Bridge
{
   ref class Application : System::Windows::Application
   {
   public:
      Application();
      ~Application();
      !Application();

      void SetHinstance(HINSTANCE&);
      HINSTANCE GetHinstance();

      void SetShowStatus(int);
      int GetShowStatus();

      void SetArguments(System::String^);
      System::String^ GetArguments();
   private:
      HINSTANCE _instance;
      int _showStatus;
      System::String^ _arguments;
   };
}
