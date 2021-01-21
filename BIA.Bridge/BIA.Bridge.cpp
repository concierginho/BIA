#include "pch.h"
#include "BIA.h"
#include "Application.h"

#include <Windows.h>
#include <iostream>

using namespace System;
using namespace System::Threading;
using namespace System::Windows;
using namespace BIA::UI::Windows;
using namespace BIA::UI::ViewModels;

[STAThread]
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
   LPSTR lpCmd, int nCmd)
{
   hPrevInstance;

   char* path = "D:\\env\\root";
   BIA::BIA bia(path);
   bia.Init();
   bia.StartProcess();

   auto mainWindow = gcnew MainWindow();
   auto mainWindowVM = gcnew MainWindowVM();
   mainWindow->DataContext = mainWindowVM;
   auto application = gcnew BIA::Bridge::Application();
   
   application->SetHinstance(hInstance);
   application->SetArguments(gcnew String(lpCmd));
   application->SetShowStatus(nCmd);

   application->Run(mainWindow);
}
