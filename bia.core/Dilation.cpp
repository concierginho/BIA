#include "pch.h"
#include "Dilation.h"

std::string BIA::Dilation::ToString()
{
   return "DILATION";
}

std::string BIA::Dilation::ArgumentsToString()
{
   return std::string();
}

BIA::Dilation::Dilation()
{
   _structuralElement = nullptr;
}

BIA::Dilation::~Dilation()
{
   if (_structuralElement != nullptr)
      delete _structuralElement;
   _structuralElement = nullptr;
}

void BIA::Dilation::PerformOperation(Bitmap* bitmap)
{
}
