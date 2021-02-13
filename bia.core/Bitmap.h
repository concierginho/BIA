#ifndef _BITMAP_
#define _BITMAP_

#include <filesystem>

#include "ENeighbourhood.h"

namespace fs = std::filesystem;

namespace BIA
{
   class Bitmap
   {
   private:
      int _width;
      int _length;

      unsigned char* _buffer;
   public:
      void LoadFromFile(fs::path&);
      void SaveToFile(fs::path&);
      
      void SetBuffer(unsigned char* buffer);
      unsigned char* GetBuffer();

      int Index(int x, int y);
      int Length();
      int Width();

      Bitmap(int width, int length);
      Bitmap(const Bitmap* bitmap);
      ~Bitmap();
   };
}

#endif
