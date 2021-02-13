#ifndef _STRUCTURAL_ELEMENT_
#define _STRUCTURAL_ELEMENT_

namespace BIA
{
   class StructuralElement
   {
   public:
      int _width;
      int _length;
      StructuralElement();
      StructuralElement(int width, int length);
   };
}

#endif
