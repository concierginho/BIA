#pragma once

#include "tiffio.h"
#include "PartImage.h"

#include <filesystem>

namespace BIA
{
   namespace Management
   {
      class Manager;
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

            Management::Manager* _manager = nullptr;
            Logging::ILogger* _logger = nullptr;
         };
      }
   }
}

