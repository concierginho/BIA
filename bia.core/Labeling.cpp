#include "pch.h"
#include "Labeling.h"

/// <summary>
/// Cel: Zwrocenie nazwy operacji jako lancuch znakow.
/// </summary>
/// <returns></returns>
std::string BIA::Labeling::ToString()
{
   return "LABELING";
}

/// <summary>
/// Domyslny konstruktor.
/// </summary>
BIA::Labeling::Labeling()
{
}

/// <summary>
/// Destruktor.
/// </summary>
BIA::Labeling::~Labeling()
{
}

/// <summary>
/// Cel: Wykonanie operacji na bitmapie.
/// </summary>
/// <param name="bitmap"></param>
void BIA::Labeling::PerformOperation(Bitmap* bitmap, nlohmann::json& json)
{
}
