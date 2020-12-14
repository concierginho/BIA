#include "../Public/BIA.h"
#include "FileManager.h"

namespace BIA
{
   BIA::BIA(std::string rootPath) : _rootPath(rootPath)
   {
      InitializeComponents();
   }

   BIA::~BIA()
   {
   }

   void BIA::InitializeComponents()
   {
      _fileManager = new FileManagement::FileManager(_rootPath);
   }

   std::string& BIA::GetRootPath() const
   {
      return _rootPath;
   }

   void BIA::SetRootPath(std::string& rootPath)
   {
      _rootPath = rootPath;
   }
   
   FileManagement::FileManager* BIA::GetFileManager() const
   {
      return nullptr;
   }
}