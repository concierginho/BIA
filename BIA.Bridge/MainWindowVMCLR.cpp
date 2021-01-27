#include "pch.h"
#include "MainWindowVMCLR.h"

using namespace System;
using namespace BIA::UI::Common;

BIA::MainWindowVMCLR::MainWindowVMCLR()
{
   StartBIAProcessCommand = gcnew RelayCommand<Object^>(gcnew Action<Object^>(this, &MainWindowVMCLR::OnStartBIAProcess));
   StopBIAProcessCommand = gcnew RelayCommand<Object^>(gcnew Action<Object^>(this, &MainWindowVMCLR::OnStopBIAProcess));
   InitializeBIACommand = gcnew RelayCommand<Object^>(gcnew Action<Object^>(this, &MainWindowVMCLR::OnInitializeBIA));
}

BIA::MainWindowVMCLR::~MainWindowVMCLR()
{
}

BIA::MainWindowVMCLR::!MainWindowVMCLR()
{
   if (_bia != nullptr)
      delete _bia;
   _bia = nullptr;
}

void BIA::MainWindowVMCLR::OnInitializeBIA(Object^)
{
   char* rootPath = "D:\\env\\root";
   _bia = new BIA(rootPath);
   _bia->Init();
}

void BIA::MainWindowVMCLR::OnStartBIAProcess(Object^)
{
   if (_bia == nullptr)
      return;

   _bia->Start();
}

void BIA::MainWindowVMCLR::OnStopBIAProcess(Object^)
{
   if (_bia == nullptr)
      return;

   _bia->Stop();
}
