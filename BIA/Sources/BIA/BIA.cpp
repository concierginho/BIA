#include "../../Public/BIA.h"

#include "../Logging/ConsoleLogger.h"
#include "../Logging/FileLogger.h"

#define _FILE_LOGGING_

namespace BIA
{
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
      _manager->SetLogger(new Logging::FileLogger(_rootPath));
   #else
      _manager->SetLogger(new Logging::ConsoleLogger());
   #endif
#endif
      _manager->SetFileManager(new FileManagement::FileManager(_manager, _rootPath));
      _manager->SetExperimentManager(new ExperimentManagement::ExperimentManager(_manager));
      _manager->SetImageManager(new ImageManagement::ImageManager(_manager));
   }

   void BIA::PrepareProcess()
   {
      _manager->GetFileManager()->ScanDirectory();
      _manager->GetExperimentManager()->PrepareExperimentDirectories();
      _manager->GetImageManager()->ScanImages();
      _manager->GetImageManager()->PrepareImageDirectories();
   }

   std::string& BIA::GetRootPath() const
   {
      return _rootPath;
   }
}
