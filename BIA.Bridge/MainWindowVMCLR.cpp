#include "pch.h"
#include "MainWindowVMCLR.h"
#include "BIAManagerKeeper.h"
#include "Experiment.h"
#include "EOperation.h"
#include "BIAExperimentManager.h"
#include "IProcessManager.h"

#include <memory>
#include <vector>

#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace BIA::UI::Common;
using namespace BIA::UI::Models;
using namespace System::Timers;
using namespace System::Threading;

/// <summary>
/// 
/// </summary>
BIA::MainWindowVMCLR::MainWindowVMCLR()
{
   StartBIAProcessCommand = gcnew RelayCommand<Object^>(gcnew Action<Object^>(this, &MainWindowVMCLR::OnStartBIAProcess));
   StopBIAProcessCommand = gcnew RelayCommand<Object^>(gcnew Action<Object^>(this, &MainWindowVMCLR::OnStopProcess));
   InitializeBIACommand = gcnew RelayCommand<Object^>(gcnew Action<Object^>(this, &MainWindowVMCLR::OnInitializeBIA));
   StartOperationProcessCommand = gcnew RelayCommand<Object^>(gcnew Action<Object^>(this, &MainWindowVMCLR::OnStartOperationProcess));
   ShowImageCommand = gcnew RelayCommand<Object^>(gcnew Action<Object^>(this, &MainWindowVMCLR::OnShowImage));
   ShowBinaryImageCommand = gcnew RelayCommand<Object^>(gcnew Action<Object^>(this, &MainWindowVMCLR::OnShowBinaryImage));
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

   LoadData();
}

/// <summary>
/// 
/// </summary>
/// <param name=""></param>
void BIA::MainWindowVMCLR::OnStartBIAProcess(Object^)
{
   if (_bia == nullptr)
      return;

   BiaTimer->Interval = 100;
   BiaTimer->Start();

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

   OperationTimer->Interval = 100;
   OperationTimer->Start();

   _bia->Start(EProcess::BIAOPERATIONS);
   LoadData();
}

/// <summary>
/// 
/// </summary>
/// <param name="parameter"></param>
void BIA::MainWindowVMCLR::OnShowImage(Object^ parameter)
{
   auto partExperimentModel = dynamic_cast<PartExperimentModel^>(parameter);
   
   msclr::interop::marshal_context context;
   std::string name = context.marshal_as<std::string>(partExperimentModel->Name);
   const char* c_name = name.c_str();

   int id = partExperimentModel->Id;
   bool isHorizontal = true;

   if (partExperimentModel->Folder == "Vertical")
      isHorizontal = false;

   std::string path = _bia->GetExperimentManager()->GetPartExperimentImagePath(c_name, id, isHorizontal);
   const char* c_path = path.c_str();
   System::String^ stringPath = gcnew System::String(c_path);
   Image = gcnew System::Windows::Media::Imaging::BitmapImage(gcnew System::Uri(stringPath));
}

/// <summary>
/// 
/// </summary>
/// <param name="parameter"></param>
void BIA::MainWindowVMCLR::OnShowBinaryImage(Object^ parameter)
{
   auto partExperimentModel = dynamic_cast<PartExperimentModel^>(parameter);

   msclr::interop::marshal_context context;
   std::string name = context.marshal_as<std::string>(partExperimentModel->Name);
   const char* c_name = name.c_str();

   int id = partExperimentModel->Id;
   bool isHorizontal = true;

   if (partExperimentModel->Folder == "Vertical")
      isHorizontal = false;

   std::string path = _bia->GetExperimentManager()->GetPartExperimentPreviewImagePath(c_name, id, isHorizontal);
   const char* c_path = path.c_str();
   System::String^ stringPath = gcnew System::String(c_path);
   Image = gcnew System::Windows::Media::Imaging::BitmapImage(gcnew System::Uri(stringPath));
}

/// <summary>
/// 
/// </summary>
void BIA::MainWindowVMCLR::LoadData()
{
   auto experimentManager = dynamic_cast<BIAExperimentManager*>(_bia->GetExperimentManager());
   int experimentSize = experimentManager->GetExperimentsSize();

   BiaProgress = 0;
   BiaProgressCapacity = experimentSize * 80 * 2;
   OperationProgress = 0;
   OperationProgressCapacity = experimentSize * 80;
   
   ExperimentModels->Clear();

   for (int i = 0; i < experimentSize; i++)
   {
      System::String^ name = gcnew System::String(experimentManager->GetExperimentName(i).c_str());
      ExperimentModels->Add(gcnew ExperimentModel(name));

      auto& vertPartExps = experimentManager->GetPartExperiments(i, false);
      auto& horPartExps = experimentManager->GetPartExperiments(i, true);

      ExperimentModels[i]->VerticalPartExperimentModels->Clear();
      for (int ii = 0; ii < vertPartExps.size(); ii++)
      {
         ExperimentModels[i]->VerticalPartExperimentModels->Add(gcnew PartExperimentModel("Vertical", ii, name));
         ExperimentModels[i]->VerticalPartExperimentModels[ii]->ShowImageCommand = ShowImageCommand;
         ExperimentModels[i]->VerticalPartExperimentModels[ii]->ShowBinaryImageCommand = ShowBinaryImageCommand;
      }

      ExperimentModels[i]->HorizontalPartExperimentModels->Clear();
      for (int ii = 0; ii < vertPartExps.size(); ii++)
      {
         ExperimentModels[i]->HorizontalPartExperimentModels->Add(gcnew PartExperimentModel("Horizontal", ii, name));
         ExperimentModels[i]->HorizontalPartExperimentModels[ii]->ShowImageCommand = ShowImageCommand;
         ExperimentModels[i]->HorizontalPartExperimentModels[ii]->ShowBinaryImageCommand = ShowBinaryImageCommand;

      }
   }
}

/// <summary>
/// 
/// </summary>
/// <param name="source"></param>
/// <param name="args"></param>
void BIA::MainWindowVMCLR::OnBiaTick(Object^ source, ElapsedEventArgs^ args)
{
   auto processManager = _bia->GetProcessManager();

   BiaProgress = processManager->GetBiaProgress();

   if (OperationProgress >= OperationProgressCapacity)
      _bia->Stop();
}

/// <summary>
/// 
/// </summary>
/// <param name="source"></param>
/// <param name="args"></param>
void BIA::MainWindowVMCLR::OnOperationTick(Object^ source, ElapsedEventArgs^ args)
{
   auto processManager = _bia->GetProcessManager();

   OperationProgress = static_cast<int>(processManager->GetOperationProgress());

   if (BiaProgress >= BiaProgressCapacity)
      _bia->Stop();
}

/// <summary>
/// 
/// </summary>
/// <param name=""></param>
void BIA::MainWindowVMCLR::OnStopProcess(Object^)
{
   if (_bia == nullptr)
      return;

   if (BiaTimer->Enabled)
      BiaTimer->Stop();

   if (OperationTimer->Enabled)
      OperationTimer->Stop();

   _bia->Stop();
}
