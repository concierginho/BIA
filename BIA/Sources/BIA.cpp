#include "../Public/BIA.h"
#include "Logging/FileLogger.h"
#include "Logging/ConsoleLogger.h"
#include "Management/Manager.h"

#define _FILE_LOGGING_

namespace BIA
{
   using namespace Management;

   BIA::BIA(std::string rootPath) : _rootPath(rootPath)
   {
      InitializeComponents();
   }

   BIA::~BIA()
   {
      if (_manager != nullptr)
         delete _manager;
      _manager = nullptr;
   }

   void BIA::InitializeComponents()
   {
      _manager = new Management::Manager();

#ifdef _LOGGING_
   #ifdef _FILE_LOGGING_
      _manager->Logger = new Logging::FileLogger(_rootPath);
   #else
      _manager->Logger = new Logging::ConsoleLogger();
   #endif
#endif
      _manager->FileManager = new File::FileManager(_manager, _rootPath);
      _manager->ExperimentManager = new Experiment::ExperimentManager(_manager);
      _manager->ImageManager = new Image::ImageManager(_manager);
   }

   void BIA::PrepareProcess()
   {
      if(_manager->Logger != nullptr)
         _manager->Logger->Prepare();
      _manager->FileManager->ScanDirectory();
      _manager->ExperimentManager->PrepareExperimentDirectories();
      _manager->FileManager->ScanExperimentDirectories();
      _manager->FileManager->ScanHorizontalAndVerticalDirectories();
      _manager->ImageManager->SplitMainImages();
   }

   std::string& BIA::GetRootPath() const
   {
      return _rootPath;
   }
}
