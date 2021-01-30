#include "pch.h"
#include "Closing.h"

std::string BIA::Closing::ToString()
{
   return "CLOSING";
}

std::string BIA::Closing::ArgumentsToString()
{
   return std::string();
}

BIA::Closing::Closing()
{
   _structuralElement = nullptr;
}

BIA::Closing::~Closing()
{
   if (_structuralElement != nullptr)
      delete _structuralElement;
   _structuralElement = nullptr;
}

void BIA::Closing::PerformOperation(Bitmap* bitmap)
{
}
