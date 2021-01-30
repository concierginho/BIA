#include "pch.h"
#include "Erosion.h"

std::string BIA::Erosion::ToString()
{
   return "EROSION";
}

std::string BIA::Erosion::ArgumentsToString()
{
    return std::string();
}

void BIA::Erosion::PerformOperation(Bitmap* bitmap)
{
}

BIA::Erosion::Erosion()
{
   _structuralElement = nullptr;
}

BIA::Erosion::~Erosion()
{
   if (_structuralElement != nullptr)
      delete _structuralElement;
   _structuralElement = nullptr;
}
