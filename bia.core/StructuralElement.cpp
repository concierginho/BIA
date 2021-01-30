#include "pch.h"
#include "StructuralElement.h"

/// <summary>
/// Domyslny konstruktor.
/// </summary>
BIA::StructuralElement::StructuralElement()
{
   _width = 0;
   _length = 0;
}

/// <summary>
/// Konstruktor pozwalajacy ustawic rozmiary bitmapy.
/// </summary>
/// <param name="width"></param>
/// <param name="length"></param>
BIA::StructuralElement::StructuralElement(int width, int length)
{
   _width = width;
   _length = length;
}
