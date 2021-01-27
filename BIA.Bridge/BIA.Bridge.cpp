#include "pch.h"
#include "BIA.h"
#include "Application.h"
#include "MainWindowVMCLR.h"

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

   auto mainWindow = gcnew MainWindow();
   auto mainWindowVM = gcnew BIA::MainWindowVMCLR();
   mainWindow->DataContext = mainWindowVM;

   //System::Threading::Thread::Sleep(5000);

   //bia.Stop();

   auto application = gcnew BIA::Bridge::Application();
   
   application->SetHinstance(hInstance);
   application->SetArguments(gcnew String(lpCmd));
   application->SetShowStatus(nCmd);

   application->Run(mainWindow);
}
