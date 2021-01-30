#include "pch.h"
#include "GammaCorrection.h"

/// <summary>
/// Cel: Zwrocenie nazwy operacji jako lancuch znakow.
/// </summary>
/// <returns></returns>
std::string BIA::GammaCorrection::ToString()
{
   return "GAMMA_CORRECTION";
}

/// <summary>
/// Cel: Zwrocenie argumentow operacji jako lancuch znakow.
/// </summary>
/// <returns></returns>
std::string BIA::GammaCorrection::ArgumentsToString()
{
   return std::string();
}

/// <summary>
/// Domyslny konstruktor.
/// </summary>
BIA::GammaCorrection::GammaCorrection()
{
}

/// <summary>
/// Destruktor.
/// </summary>
BIA::GammaCorrection::~GammaCorrection()
{
}

/// <summary>
/// Cel: Wykonanie operacji na bitmapie.
/// </summary>
/// <param name="bitmap"></param>
void BIA::GammaCorrection::PerformOperation(Bitmap* bitmap)
{
}
