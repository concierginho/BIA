#ifndef _BITMAP_
#define _BITMAP_

#include <filesystem>

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

      unsigned char* GetBuffer();

      int Index(int x, int y);
      int Length();
      int Width();

      Bitmap(int width, int length);
      ~Bitmap();
   };
}

#endif
