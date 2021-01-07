#pragma once
#define WIN32_LEAN_AND_MEAN

#include <string>

namespace BIA
{
   namespace Management
   {
      class Manager;
   }

   class BIA
   {
   private:
      std::string& _rootPath;
      Management::Manager* _manager;

      void InitializeComponents();
   public:
      void PrepareProcess();
      std::string& GetRootPath() const;\

      BIA(std::string rootPath);
      ~BIA();
   };
}