#pragma once

#include "tiffio.h"
#include "PartImage.h"

#include <filesystem>

namespace BIA::Management
{
   class Manager;
}

#ifdef _LOGGING_
namespace BIA::Logging
{
   class ILogger;
}
#endif

namespace BIA
{
   namespace Image
   {
      class ImageManager
      {
      public:
         ImageManager(Management::Manager*);
         ~ImageManager();

         void SplitMainImages();
      private:
         void ReadTagsFromImage(TIFF*);

         bool OpenParentTIFFImageForReading(TIFF**, std::filesystem::path);
         bool CloseParentTIFFImage(TIFF**);

         Management::Manager* _manager = nullptr;
         Logging::ILogger* _logger = nullptr;
      };
   }
}
