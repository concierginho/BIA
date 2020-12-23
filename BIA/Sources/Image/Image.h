#pragma once
namespace BIA
{
   namespace Graphics
   {
      class Image
      {
      private:
         int _width;
         int _height;
      public:
         explicit Image(int, int);
         Image();
         ~Image();
      };
   }
}
