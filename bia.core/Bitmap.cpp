#include "pch.h"
#include "Bitmap.h"
#include "Operation.h"

#include "tiffio.h"

BIA::Bitmap::Bitmap(int width, int length)
{
   _width = width;
   _length = length;
   _buffer = new unsigned char[width * length];
}

BIA::Bitmap::~Bitmap()
{
   if (_buffer != nullptr)
      delete _buffer;
   _buffer = nullptr;
}

void BIA::Bitmap::LoadFromFile(fs::path& path)
{
   std::string pathStr = path.string();
   const char* c_pathStr = pathStr.c_str();

   TIFF* tiff = TIFFOpen(c_pathStr, READ);

   if (tiff != nullptr)
   {
      uint32 linebytes = (uint32)_width;
      unsigned char* buffer = (unsigned char*)_TIFFmalloc(linebytes);
#ifdef _LOGGING_
#endif

      for (uint32 row = 0; row < (uint32)_width; row++)
      {
         TIFFReadScanline(tiff, buffer, row);
         memcpy(&_buffer[row * linebytes], buffer, _width);
      }

      _TIFFfree(buffer);
      TIFFClose(tiff);
   }
}

int BIA::Bitmap::Index(int x, int y)
{
   return x + _width * y;
}
