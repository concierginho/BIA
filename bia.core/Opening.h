#ifndef _OPENING_
#define _OPENING_

#include "IOperation.h"
#include "StructuralElement.h"

namespace BIA
{
   class Opening : IOperation
   {
   private:
      StructuralElement _structuralElement;
   public:
      virtual std::string ToString() override;
      virtual std::string ArgumentsToString() override;
   };
}

#endif
