#include "pch.h"
#include "Erosion.h"
#include "Keys.h"

#include <sstream>

/// <summary>
/// Cel: Zwrocenie nazwy operacji jako lancuch znakow.
/// </summary>
/// <returns></returns>
std::string BIA::Erosion::ToString()
{
   return "EROSION";
}

/// <summary>
/// Cel: Wykonanie operacji na bitmapie
/// </summary>
/// <param name="bitmap"></param>
void BIA::Erosion::PerformOperation(Bitmap* bitmap, nlohmann::json& json)
{
   ReadArguments(json);

   int left_top_x = 0;
   int left_top_y = 0;
   int right_bot_x = bitmap->Width();
   int right_bot_y = bitmap->Length();

   unsigned char white = static_cast<unsigned char>(0);

   unsigned char* buffer = bitmap->GetBuffer();

   Bitmap* result = new Bitmap(bitmap);
   unsigned char* resultBuffer = result->GetBuffer();

   #pragma omp parallel for
   for (int i = left_top_x; i < right_bot_x - 1; i++)
   {
      for (int j = left_top_y; j < right_bot_y - 1; j++)
      {
         auto neighbours = GetNeighbours(i, j, right_bot_x, right_bot_y, bitmap);

         bool isAnyWhite = false;
         for (auto& neighbour : neighbours)
         {
            if (buffer[neighbour] == white)
            {
               isAnyWhite = true;
               break;
            }
         }

         if (isAnyWhite)
         {
            for (auto& neighbour : neighbours)
            {
               resultBuffer[neighbour] = white;
            }
         }
      }
   }

   delete[] buffer;

   bitmap->SetBuffer(result->GetBuffer());
}

std::vector<int> BIA::Erosion::GetNeighbours(int x, int y, int img_width, int img_length, Bitmap* bitmap)
{
   std::vector<int> neighbours;

   int half_width = static_cast<int>(_structuralElement->_width / 2);
   int half_length = static_cast<int>(_structuralElement->_length / 2);

   int left_top_x = x - half_width;
   int left_top_y = y - half_length;
   int right_bot_x = x + half_width;
   int right_bot_y = y + half_length;

   if (left_top_x < 0)
      left_top_x = 0;
   if (left_top_y < 0)
      left_top_y = 0;
   if (right_bot_x > img_width - 1)
      right_bot_x = img_width;
   if (right_bot_y > img_length - 1)
      right_bot_y = img_length;

   for (int i = left_top_x; i <= right_bot_x; i++)
   {
      for (int j = left_top_y; j <= right_bot_y; j++)
      {
         if (i < 0 || i > bitmap->Width() || j < 0 || j > bitmap->Length() || ((i == x) && (j == y)))
            continue;
         else
            neighbours.push_back(bitmap->Index(i, j));
      }
   }
   return neighbours;
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

/// <summary>
/// Cel: Odczytanie argumentow z obiektu json.
///      Stworzenie na podstawie argumentow obiektu typu StructuralElement.
/// </summary>
/// <param name="json"></param>
void BIA::Erosion::ReadArguments(nlohmann::json& json)
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
