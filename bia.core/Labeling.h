#ifndef _LABELING_
#define _LABELING_

#include "IOperation.h"
#include "Bitmap.h"

namespace BIA
{
   class Labeling : public IOperation
   {
   public:
      virtual std::string ToString() override;
      virtual void PerformOperation(Bitmap* bitmap, nlohmann::json& json) override;

      static std::vector<int> GetNeighbours(Bitmap* bitmap, ENeighbourhood neighbourhood, int index, int* labels);

      explicit Labeling();
      ~Labeling();
   };
}

#endif
