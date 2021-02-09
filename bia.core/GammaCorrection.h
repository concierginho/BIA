#ifndef _GAMMA_CORRECTION_
#define _GAMMA_CORRECTION_

#include "IOperation.h"
#include "Bitmap.h"

namespace BIA
{
   class GammaCorrection : public IOperation
   {
   private:
      double _arg;
   public:
      virtual std::string ToString() override;
      virtual void ReadArguments(nlohmann::json& json) override;

      void PerformOperation(Bitmap* bitmap, nlohmann::json& json);

      explicit GammaCorrection();
      ~GammaCorrection();
   };
}

#endif
