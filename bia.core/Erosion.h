#ifndef _EROSION_
#define _EROSION_

#include "IOperation.h"
#include "StructuralElement.h"
#include "Bitmap.h"

namespace BIA
{
   class Erosion : public IOperation
   {
   private:
      StructuralElement* _structuralElement = nullptr;
   public:
      virtual std::string ToString() override;
      virtual void PerformOperation(Bitmap* bitmap, nlohmann::json& json) override;

      explicit Erosion();
      ~Erosion();
   };
}

#endif
