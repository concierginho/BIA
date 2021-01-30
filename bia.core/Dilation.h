#ifndef _DILATION_
#define _DILATION_

#include "IOperation.h"
#include "StructuralElement.h"

namespace BIA
{
   class Dilation : IOperation
   {
   private:
      StructuralElement _structuralElement;
   public:
      virtual std::string ToString() override;
      virtual std::string ArgumentsToString() override;
   };
}

#endif
