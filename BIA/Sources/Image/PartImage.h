#pragma once

#include "tiffio.h"

#include <filesystem>
#include <string>

namespace BIA::Image
{
   class PartImage
   {
   public:
      static uint32 ParentImageWidth;
      static uint32 ParentImageLength;
      static uint32 ScanlineSize;
      static uint16 BitsPerSample;
      static uint16 SamplesPerPixel;
      static int ID;

      void SetCoordinatesInParentImage(uint32, uint32, uint32, uint32);

      std::string GetName();

      std::filesystem::path GetPath();

      explicit PartImage(std::string&, std::filesystem::path&);
      ~PartImage();
   private:
      int _id;

      std::string _name;

      uint32 _begCol;
      uint32 _endCol;
      uint32 _begRow;
      uint32 _endRow;

      std::filesystem::path _path;
   };
}

