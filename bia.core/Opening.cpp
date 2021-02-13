#include "pch.h"
#include "Opening.h"
#include "Keys.h"
#include "Erosion.h"
#include "Dilation.h"

#include <sstream>

/// <summary>
/// Cel: Zwrocenie nazwy operacji jako lancuch znakow.
/// </summary>
/// <returns></returns>
std::string BIA::Opening::ToString()
{
   return "OPENING";
}

/// <summary>
/// Cel: Wykonanie operacji na bitmapie.
/// </summary>
/// <param name="bitmap"></param>
void BIA::Opening::PerformOperation(Bitmap* bitmap, nlohmann::json& json)
{
   Erosion* erosion = new Erosion();
   Dilation* dilation = new Dilation();

   erosion->PerformOperation(bitmap, json);
   dilation->PerformOperation(bitmap, json);
}

/// <summary>
/// Domyslny konstruktor.
/// </summary>
BIA::Opening::Opening()
{
}

/// <summary>
/// Destruktor.
/// </summary>
BIA::Opening::~Opening()
{
}

/// <summary>
/// Cel: Odczytanie argumentow z obiektu json.
///      Stworzenie na podstawie argumentow obiektu typu StructuralElement.
/// </summary>
/// <param name="json"></param>
void BIA::Opening::ReadArguments(nlohmann::json& json)
{
}
