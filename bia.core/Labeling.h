#ifndef _LABELING_
#define _LABELING_

#include "IOperation.h"

namespace BIA
{
   class Labeling : IOperation
   {
      virtual std::string ToString() override;
      virtual std::string ArgumentsToString() override;
   };
}

#endif
