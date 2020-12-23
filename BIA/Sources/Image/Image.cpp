#include "Image.h"

namespace BIA
{
   namespace Graphics
   {
      Image::Image(int width, int height)
      {
         _width = width;
         _height = height;
      }

      Image::Image()
      {
         _width = _height = 0;
      }

      Image::~Image()
      {
      }
   }
}
