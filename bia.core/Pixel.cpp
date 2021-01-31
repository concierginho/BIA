#include "pch.h"
#include "Pixel.h"

BIA::Pixel::Pixel()
{
   x = 0;
   y = 0;
   value = 0;
   index = 0;
   is_labeled = false;
}

BIA::Pixel::Pixel(int x, int y, unsigned char value)
{
   this->x = x;
   this->y = y;
   this->value = value;
   this->index = 0;
   this->is_labeled = false;
}
