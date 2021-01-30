#include "pch.h"
#include "Erosion.h"

/// <summary>
/// Cel: Zwrocenie nazwy operacji jako lancuch znakow.
/// </summary>
/// <returns></returns>
std::string BIA::Erosion::ToString()
{
   return "EROSION";
}

/// <summary>
/// Cel: Zwrocenie argumentow operacji jako lancuch znakow.
/// </summary>
/// <returns></returns>
std::string BIA::Erosion::ArgumentsToString()
{
    return std::string();
}

/// <summary>
/// Cel: Wykonanie operacji na bitmapie
/// </summary>
/// <param name="bitmap"></param>
void BIA::Erosion::PerformOperation(Bitmap* bitmap)
{
}

/// <summary>
/// Domyslny konstruktor.
/// </summary>
BIA::Erosion::Erosion()
{
   _structuralElement = nullptr;
}

/// <summary>
/// Destruktor.
/// </summary>
BIA::Erosion::~Erosion()
{
   if (_structuralElement != nullptr)
      delete _structuralElement;
   _structuralElement = nullptr;
}
