#include "pch.h"
#include "Closing.h"

/// <summary>
/// Cel: Zwrocenie nazwy operacji jako lancuch znakow.
/// </summary>
/// <returns></returns>
std::string BIA::Closing::ToString()
{
   return "CLOSING";
}

/// <summary>
/// Domyslny konstruktor.
/// </summary>
BIA::Closing::Closing()
{
   _structuralElement = nullptr;
}

/// <summary>
/// Destruktor.
/// </summary>
BIA::Closing::~Closing()
{
   if (_structuralElement != nullptr)
      delete _structuralElement;
   _structuralElement = nullptr;
}

/// <summary>
/// Cel: Wykonanie operacji na bitmapie.
/// </summary>
/// <param name="bitmap"></param>
void BIA::Closing::PerformOperation(Bitmap* bitmap, nlohmann::json& json)
{
}
