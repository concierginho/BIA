#ifndef _GAMMA_CORRECTION_
#define _GAMMA_CORRECTION_

#include "IOperation.h"

namespace BIA
{
   class GammaCorrection : IOperation
   {
      virtual std::string ToString() override;
      virtual std::string ArgumentsToString() override;
   };
}

#endif
