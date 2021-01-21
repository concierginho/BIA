#include "pch.h"
#include "BIA.h"
#include "BIAManagerKeeper.h"

#ifdef _LOGGING_
#include "BIALoggingManager.h"
#endif
#include "EAlignment.h"


void BIA::BIA::Init()
{
   _keeper = new BIAManagerKeeper(_rootPath);

   _keeper->Init();
}

void BIA::BIA::StartProcess()
{
   auto biaFileManager = _keeper->GetFileManagerAsBIAFileManager();
   auto biaImageManager = _keeper->GetImageManagerAsBIAImageManager();
   auto biaExperimentManager = _keeper->GetExperimentManagerAsBIAExperimentManager();

   biaFileManager->ScanRootDirectory();
   biaExperimentManager->PrepareExperiments();
   biaImageManager->SplitImages();
}

void BIA::BIA::SetRootPath(char* rootPath)
{
   _rootPath = rootPath;
}

const char* BIA::BIA::GetRootPath() const
{
   return _rootPath;
}

BIA::BIA::BIA(char* rootPath)
{
   _rootPath = rootPath;
   _keeper = nullptr;
}

BIA::BIA::~BIA()
{
   if(!_rootPath)
      delete _rootPath;
   _rootPath = nullptr;

   if (!_keeper)
      delete _keeper;
   _keeper = nullptr;
}
