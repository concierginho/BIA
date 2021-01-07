#pragma once

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

            void PrepareImageDirectories();
            void ScanImages();
         private:
            Management::Manager* _manager = nullptr;
            Logging::ILogger* _logger = nullptr;
         };
      }
   }
}

