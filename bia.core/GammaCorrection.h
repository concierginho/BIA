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
      void PerformOperation(Bitmap* bitmap, nlohmann::json& json);

      explicit GammaCorrection();
      ~GammaCorrection();
   };
}

#endif
