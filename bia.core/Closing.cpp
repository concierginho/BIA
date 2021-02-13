#include "pch.h"
#include "Closing.h"
#include "Keys.h"
#include "Erosion.h"
#include "Dilation.h"

#include <sstream>

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
}

/// <summary>
/// Destruktor.
/// </summary>
BIA::Closing::~Closing()
{
}

/// <summary>
/// Cel: Pobranie argumentow z obiektu typu json.
///      Stworzenie na podstawie argumentow obiektu typu StructuralElement.
/// </summary>
/// <param name="json"></param>
void BIA::Closing::ReadArguments(nlohmann::json& json)
{
}

/// <summary>
/// Cel: Wykonanie operacji na bitmapie.
/// </summary>
/// <param name="bitmap"></param>
void BIA::Closing::PerformOperation(Bitmap* bitmap, nlohmann::json& json)
{
   Dilation* dilation = new Dilation();
   Erosion* erosion = new Erosion();

   dilation->PerformOperation(bitmap, json);
   erosion->PerformOperation(bitmap, json);
}
