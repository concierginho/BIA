#ifndef _OPENING_
#define _OPENING_

#include "IOperation.h"
#include "StructuralElement.h"
#include "Bitmap.h"

namespace BIA
{
   class Opening : public IOperation
   {
   private:
      StructuralElement* _structuralElement = nullptr;
   public:
      virtual std::string ToString() override;
      void PerformOperation(Bitmap* bitmap, nlohmann::json& json);

      explicit Opening();
      ~Opening();
   };
}

#endif
