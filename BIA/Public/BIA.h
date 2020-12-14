#pragma once
#define WIN32_LEAN_AND_MEAN

#include <string>

namespace BIA
{
   namespace FileManagement
   {
      class FileManager;
   }

   class BIA
   {
   private:
      std::string& _rootPath;
      FileManagement::FileManager* _fileManager;

      void InitializeComponents();
   public:
      std::string& GetRootPath() const;
      void SetRootPath(std::string& rootPath);
      FileManagement::FileManager* GetFileManager() const;

      BIA(std::string rootPath);
      ~BIA();
   };
}