#pragma once
#define WIN32_LEAN_AND_MEAN

#include <string>

#include "../Sources/Common/Manager.h"

namespace BIA
{
   class BIA
   {
   private:
      Management::Manager* _manager;
      std::string& _rootPath;

      void InitializeComponents();
   public:
      void PrepareProcess();

      std::string& GetRootPath() const;

      BIA(std::string rootPath);
      ~BIA();
   };
}