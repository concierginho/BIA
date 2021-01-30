#include "pch.h"
#include "Dilation.h"

/// <summary>
/// Cel: Zwrocenie nazwy operacji jako lancuch znakow.
/// </summary>
/// <returns></returns>
std::string BIA::Dilation::ToString()
{
   return "DILATION";
}

/// <summary>
/// Cel: Zwrocenie argumentow operacji jako lancuch znakow.
/// </summary>
/// <returns></returns>
std::string BIA::Dilation::ArgumentsToString()
{
   return std::string();
}

/// <summary>
/// Domyslny konstruktor.
/// </summary>
BIA::Dilation::Dilation()
{
   _structuralElement = nullptr;
}

/// <summary>
/// Destruktor.
/// </summary>
BIA::Dilation::~Dilation()
{
   if (_structuralElement != nullptr)
      delete _structuralElement;
   _structuralElement = nullptr;
}

/// <summary>
/// Cel: Wykonanie operacji na bitmapie.
/// </summary>
/// <param name="bitmap"></param>
void BIA::Dilation::PerformOperation(Bitmap* bitmap)
{
}
