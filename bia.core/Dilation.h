#ifndef _DILATION_
#define _DILATION_

#include "IOperation.h"
#include "StructuralElement.h"
#include "Bitmap.h"

namespace BIA
{
   class Dilation : public IOperation
   {
   private:
      StructuralElement* _structuralElement = nullptr;
   public:
      virtual std::string ToString() override;
      virtual std::string ArgumentsToString() override;
      virtual void PerformOperation(Bitmap* bitmap) override;

      explicit Dilation();
      ~Dilation();
   };
}

#endif
