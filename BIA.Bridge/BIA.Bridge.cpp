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

#ifndef _DEBUG
[STAThread]
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
   LPSTR lpCmd, int nCmd)
{
   hPrevInstance;

   auto bia = new BIA::BIA("D:\\university\\engineering thesis\\obrazy-komora-prom-przeplywu");
   bia->PrepareProcess();
   auto mainWindow = gcnew MainWindow();
   auto mainWindowVM = gcnew MainWindowVM();
   mainWindow->DataContext = mainWindowVM;
   auto application = gcnew BIA::Bridge::Application();
   
   application->SetHinstance(hInstance);
   application->SetArguments(gcnew String(lpCmd));
   application->SetShowStatus(nCmd);

   application->Run(mainWindow);
}
#endif

#ifdef _DEBUG
int main()
{
   auto bia = new BIA::BIA("D:\\university\\engineering thesis\\obrazy-komora-prom-przeplywu");
   bia->PrepareProcess();
   delete bia;
   return 0;
}
#endif