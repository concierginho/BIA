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
      std::string virtual ToString() = 0;
      void virtual PerformOperation(Bitmap* bitmap, nlohmann::json& json) = 0;
   };
}

#endif
