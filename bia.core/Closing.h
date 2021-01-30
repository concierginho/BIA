#ifndef _CLOSING_
#define _CLOSING_

#include "IOperation.h"
#include "StructuralElement.h"

namespace BIA
{
   class Closing : IOperation
   {
   private:
      StructuralElement _structuralElement;
   public:
      virtual std::string ToString() override;
      virtual std::string ArgumentsToString() override;
   };
}

#endif
