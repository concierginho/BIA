#include "pch.h"
#include "StructuralElement.h"

BIA::StructuralElement::StructuralElement()
{
   _width = 0;
   _length = 0;
}

BIA::StructuralElement::StructuralElement(int width, int length)
{
   _width = width;
   _length = length;
}
