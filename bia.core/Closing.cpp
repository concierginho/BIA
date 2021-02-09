#include "pch.h"
#include "Closing.h"

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
/// Cel: Pobranie argumentow z obiektu typu json.
///      Stworzenie na podstawie argumentow obiektu typu StructuralElement.
/// </summary>
/// <param name="json"></param>
void BIA::Closing::ReadArguments(nlohmann::json& json)
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
void BIA::Closing::PerformOperation(Bitmap* bitmap, nlohmann::json& json)
{
   ReadArguments(json);
}
