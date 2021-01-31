#ifndef _PIXEL_
#define _PIXEL_

namespace BIA
{
   class Pixel
   {
   public:
      int index;
      int x;
      int y;
      unsigned char value;
      bool is_labeled;

      Pixel();
      Pixel(int x, int y, unsigned char value);
   };
}

#endif
