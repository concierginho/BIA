#ifndef _CLOSING_
#define _CLOSING_

#include "IOperation.h"
#include "StructuralElement.h"
#include "Bitmap.h"

namespace BIA
{
   class Closing : public IOperation
   {
   private:
      StructuralElement* _structuralElement = nullptr;
   public:
      virtual std::string ToString() override;
      virtual std::string ArgumentsToString() override;
      virtual void PerformOperation(Bitmap* bitmap) override;

      explicit Closing();
      ~Closing();
   };
}

#endif
