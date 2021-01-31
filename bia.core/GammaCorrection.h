#ifndef _GAMMA_CORRECTION_
#define _GAMMA_CORRECTION_

#include "IOperation.h"
#include "Bitmap.h"

namespace BIA
{
   class GammaCorrection : public IOperation
   {
   public:
      virtual std::string ToString() override;
      virtual void PerformOperation(Bitmap* bitmap, nlohmann::json& json) override;

      explicit GammaCorrection();
      ~GammaCorrection();
   };
}

#endif
