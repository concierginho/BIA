#pragma once

#include "../Logger/ILogger.h"

namespace BIA
{
   namespace ImageManagement
   {
      class ImageManager
      {
      public:
         ImageManager(Logging::ILogger*);
         ~ImageManager();
      private:
         Logging::ILogger* _logger = nullptr;
      };
   }
}

