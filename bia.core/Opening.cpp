#include "pch.h"
#include "Opening.h"

/// <summary>
/// Cel: Zwrocenie nazwy operacji jako lancuch znakow.
/// </summary>
/// <returns></returns>
std::string BIA::Opening::ToString()
{
   return "OPENING";
}

/// <summary>
/// Cel: Zwrocenie argumentow operacji jako lancuch znakow.
/// </summary>
/// <returns></returns>
std::string BIA::Opening::ArgumentsToString()
{
   return std::string();
}

/// <summary>
/// Cel: Wykonanie operacji na bitmapie.
/// </summary>
/// <param name="bitmap"></param>
void BIA::Opening::PerformOperation(Bitmap* bitmap)
{
}

/// <summary>
/// Domyslny konstruktor.
/// </summary>
BIA::Opening::Opening()
{
   _structuralElement = nullptr;
}

/// <summary>
/// Destruktor.
/// </summary>
BIA::Opening::~Opening()
{
   if (_structuralElement != nullptr)
      delete _structuralElement;
   _structuralElement = nullptr;
}