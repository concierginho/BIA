#include "pch.h"
#include "MainWindowVMCLR.h"
#include "BIAManagerKeeper.h"
#include "Experiment.h"
#include "PartExperiment.h"
#include "EOperation.h"

#include <memory>

using namespace System;
using namespace BIA::UI::Common;

/// <summary>
/// 
/// </summary>
BIA::MainWindowVMCLR::MainWindowVMCLR()
{
   StartBIAProcessCommand = gcnew RelayCommand<Object^>(gcnew Action<Object^>(this, &MainWindowVMCLR::OnStartBIAProcess));
   StopBIAProcessCommand = gcnew RelayCommand<Object^>(gcnew Action<Object^>(this, &MainWindowVMCLR::OnStopProcess));
   InitializeBIACommand = gcnew RelayCommand<Object^>(gcnew Action<Object^>(this, &MainWindowVMCLR::OnInitializeBIA));
   StartOperationProcessCommand = gcnew RelayCommand<Object^>(gcnew Action<Object^>(this, &MainWindowVMCLR::OnStartOperationProcess));
}

/// <summary>
/// 
/// </summary>
BIA::MainWindowVMCLR::~MainWindowVMCLR()
{
}

/// <summary>
/// 
/// </summary>
BIA::MainWindowVMCLR::!MainWindowVMCLR()
{
   if (_bia != nullptr)
      delete _bia;
   _bia = nullptr;
}

/// <summary>
/// 
/// </summary>
/// <param name=""></param>
void BIA::MainWindowVMCLR::OnInitializeBIA(Object^)
{
   char* rootPath = "D:\\env\\root";
   _bia = new BIA(rootPath);
   _bia->Init();
}

/// <summary>
/// 
/// </summary>
/// <param name=""></param>
void BIA::MainWindowVMCLR::OnStartBIAProcess(Object^)
{
   if (_bia == nullptr)
      return;

   _bia->Start(EProcess::BIAPROCESS);
}

/// <summary>
/// 
/// </summary>
/// <param name=""></param>
void BIA::MainWindowVMCLR::OnStartOperationProcess(Object^)
{
   if (_bia == nullptr)
      return;

   _bia->Start(EProcess::BIAOPERATIONS);
}

/// <summary>
/// 
/// </summary>
/// <param name=""></param>
void BIA::MainWindowVMCLR::OnStopProcess(Object^)
{
   if (_bia == nullptr)
      return;

   _bia->Stop();
}
