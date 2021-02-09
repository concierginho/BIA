#include "pch.h"
#include "Dilation.h"

#include <sstream>

/// <summary>
/// Cel: Zwrocenie nazwy operacji jako lancuch znakow.
/// </summary>
/// <returns></returns>
std::string BIA::Dilation::ToString()
{
   return "DILATION";
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
/// 
/// </summary>
/// <param name="json"></param>
void BIA::Dilation::ReadArguments(nlohmann::json& json)
{
   std::stringstream arguments;
   std::string tmp;
   std::vector<int> arg;

   arguments << json.get<std::string>();

   while (std::getline(arguments, tmp, ','))
   {
      try
      {
         arg.push_back(atoi(tmp.c_str()));
      }
      catch (std::exception e)
      {
         e;
      }
   }

   _structuralElement = new StructuralElement(arg[0], arg[1]);
}

/// <summary>
/// Cel: Wykonanie operacji na bitmapie.
/// </summary>
/// <param name="bitmap"></param>
void BIA::Dilation::PerformOperation(Bitmap* bitmap, nlohmann::json& json)
{
}
