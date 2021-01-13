#include "PartImage.h"

namespace BIA::Image
{
   uint32 PartImage::ParentImageWidth = 0;
   uint32 PartImage::ParentImageLength = 0;
   uint32 PartImage::ScanlineSize = 0;
   uint16 PartImage::BitsPerSample = 0;
   uint16 PartImage::SamplesPerPixel = 0;
   int PartImage::ID = 0;

   PartImage::PartImage(std::string& name, std::filesystem::path& path)
   {
      _id = ID;
      _name = name;
      _path = path;

      ID++;
   }

   PartImage::~PartImage()
   {
   }

   void PartImage::SetCoordinatesInParentImage(uint32 begCol, uint32 begRow, uint32 endCol, uint32 endRow)
   {
      _begCol = begCol;
      _begRow = begRow;
      _endCol = endCol;
      _endRow = endRow;
   }

   std::string PartImage::GetName()
   {
      return _name;
   }

   std::filesystem::path PartImage::GetPath()
   {
      return _path;
   }
}
