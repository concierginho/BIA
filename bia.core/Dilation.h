#ifndef _DILATION_
#define _DILATION_

#include "IOperation.h"
#include "StructuralElement.h"
#include "Bitmap.h"

namespace BIA
{
   class Dilation : public IOperation
   {
   private:
      StructuralElement* _structuralElement = nullptr;
   public:
      virtual std::string ToString() override;
      virtual void ReadArguments(nlohmann::json& json) override;

      void PerformOperation(Bitmap* bitmap, nlohmann::json& json);
      std::vector<int> GetNeighbours(int x, int y, int img_width, int img_length, Bitmap* bitmap);

      explicit Dilation();
      ~Dilation();
   };
}

#endif
