#include "pch.h"
#include "GammaCorrection.h"

#include <nlohmann/json.hpp>

/// <summary>
/// Cel: Zwrocenie nazwy operacji jako lancuch znakow.
/// </summary>
/// <returns></returns>
std::string BIA::GammaCorrection::ToString()
{
   return "GAMMA_CORRECTION";
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
/// 
void BIA::GammaCorrection::PerformOperation(Bitmap* bitmap, nlohmann::json& json)
{
   std::string strArgs = json.get<std::string>();
   double arg = atof(strArgs.c_str());

   int length = bitmap->Length();
   int width = bitmap->Width();
   auto* buffer = bitmap->GetBuffer();

   for (int i = 0; i < width; i++)
   {
      for (int j = 0; j < length; j++)
      {
         int index = bitmap->Index(i, j);
         int new_value = std::pow(buffer[index], arg);
         if (new_value > 255)
            new_value = 255;
         buffer[index] = static_cast<unsigned char>(new_value);
      }
   }
}
