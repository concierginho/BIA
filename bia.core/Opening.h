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
   public:
      virtual std::string ToString() override;
      virtual void ReadArguments(nlohmann::json& json) override;

      void PerformOperation(Bitmap* bitmap, nlohmann::json& json);

      explicit Opening();
      ~Opening();
   };
}

#endif
