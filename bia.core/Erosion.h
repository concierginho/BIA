#ifndef _EROSION_
#define _EROSION_

#include "IOperation.h"
#include "StructuralElement.h"

namespace BIA
{
   class Erosion : IOperation
   {
   private:
      StructuralElement _structuralElement;
   public:
      virtual std::string ToString() override;
      virtual std::string ArgumentsToString() override;
   };
}

#endif
