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
      virtual std::string ArgumentsToString() override;
      virtual void PerformOperation(Bitmap* bitmap) override;

      explicit Labeling();
      ~Labeling();
   };
}

#endif
