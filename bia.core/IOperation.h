#ifndef _IOPERATION_
#define _IOPERATION_

#include <string>
#include <nlohmann/json.hpp>
#include "Bitmap.h"

namespace BIA
{
   class IOperation
   {
   public:
      virtual std::string ToString() = 0;
      virtual void ReadArguments(nlohmann::json& json) = 0;
   };
}

#endif
