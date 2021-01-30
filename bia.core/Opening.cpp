#include "pch.h"
#include "Opening.h"

BIA::Opening::Opening()
{
   _structuralElement = nullptr;
}

BIA::Opening::~Opening()
{
   if (_structuralElement != nullptr)
      delete _structuralElement;
   _structuralElement = nullptr;
}

void BIA::Opening::PerformOperation(Bitmap* bitmap)
{
}

std::string BIA::Opening::ToString()
{
   return "OPENING";
}

std::string BIA::Opening::ArgumentsToString()
{
   return std::string();
}
