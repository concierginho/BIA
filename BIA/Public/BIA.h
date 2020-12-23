#pragma once
#define WIN32_LEAN_AND_MEAN

#include <string>

namespace BIA
{
   namespace FileManagement
   {
      class FileManager;
   }
   
   namespace Experiment
   {
      class ExperimentManager;
   }

   class BIA
   {
   private:
      std::string& _rootPath;
      FileManagement::FileManager* _fileManager;
      Experiment::ExperimentManager* _experimentManager;

      void InitializeComponents();
   public:
      void PrepareProcess();

      std::string& GetRootPath() const;
      FileManagement::FileManager* GetFileManager() const;
      Experiment::ExperimentManager* GetExperimentManager() const;

      BIA(std::string rootPath);
      ~BIA();
   };
}