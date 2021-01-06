#include "ImageManager.h"

namespace BIA
{
   namespace ImageManagement
   {
      ImageManager::ImageManager(Logging::ILogger* logger)
      {
         _logger = logger;
      }

      ImageManager::~ImageManager()
      {
         _logger = nullptr;
      }
   }
}