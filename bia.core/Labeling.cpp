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
   std::string arg = json.get<std::string>();

   ENeighbourhood type = ENeighbourhood::VONNEUMANN;

   if (arg == "MOORE")
      type = ENeighbourhood::MOORE;

   int length = bitmap->Length(), width = bitmap->Width();
   auto* buffer = bitmap->GetBuffer();

   int size = length * width;
   int* labels = new int[size];

   #pragma omp parallel for
   for (int i = 0; i < size; i++)
   {
      labels[i] = 0;
   }

   std::vector<int> indexes;
   std::vector<int> blackPixels;

   std::unordered_map<int, std::vector<int>> _indexesByLabel;

   for (int y = 0; y < length; y++)
   {
      for (int x = 0; x < width; x++)
      {
         indexes.push_back(bitmap->Index(x, y));
      }
   }

   int currentLabel = 1;

   while (!indexes.empty())
   {
      int index = indexes.back();
      if (buffer[index] == 255)
      {
         if (labels[index] == 0)
         {
            labels[index] = currentLabel;
            _indexesByLabel[currentLabel].push_back(index);
            blackPixels.push_back(index);

            while (!blackPixels.empty())
            {
               index = blackPixels.back();
               blackPixels.pop_back();

               auto neighbours = GetNeighbours(bitmap, type, index, labels);
               for (auto neighbour : neighbours)
               {
                  if (buffer[neighbour] == 255)
                  {
                     labels[neighbour] = currentLabel;
                     _indexesByLabel[currentLabel].push_back(neighbour);
                     blackPixels.push_back(neighbour);
                  }
               }
            }
            currentLabel++;
         }
      }
      indexes.pop_back();
   }
   delete [] labels;
}

/// <summary>
/// Cel: Zwrocenie wektora zwaierajacego indeksy sasiadow wskazanego pixela.
///      Kolejnosc sasiadow dla ENeighbourhood::MOORE:
///      [0] - lewy gorny
///      [1] - gorny
///      [2] - prawy gorny
///      [3] - lewy
///      [4] - prawy
///      [5] - lewy dolny
///      [6] - dolny
///      [7] - prawy dolny
///      Kolejnosc sasiadow dla ENeighbourhood::VONNEUMANN:
///      [0] - gorny
///      [1] - lewy
///      [2] - prawy
///      [3] - dolny
///      Zwracane sa tylko te indeksy, ktore maja sens w kontekscie algorytmu.
/// </summary>
/// <param name="neighbourhood"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
std::vector<int> BIA::Labeling::GetNeighbours(Bitmap* bitmap, ENeighbourhood neighbourhood, int index, int* labels)
{
   int tmp_x = 0, tmp_y = 0, tmp_idx = 0;

   int value = -1;
   int width = bitmap->Width(), length = bitmap->Length();
   int size = width * length;
   auto buffer = bitmap->GetBuffer();

   std::vector<int> neighbours;

   int new_index = 0;

   switch (neighbourhood)
   {
      case ENeighbourhood::MOORE:
         new_index = index - 1025;
         if (new_index < 0)
            new_index = -1;
         neighbours.push_back(new_index);
         new_index = index - 1024;
         if (new_index < 0)
            new_index = -1;
         neighbours.push_back(new_index);
         new_index = index - 1023;
         if (new_index < 0)
            new_index = -1;
         neighbours.push_back(new_index);
         new_index = index - 1;
         if (new_index < 0)
            new_index = -1;
         neighbours.push_back(new_index);
         new_index = index + 1;
         if (new_index < 0)
            new_index = -1;
         neighbours.push_back(new_index);
         new_index = index + 1023;
         if (new_index < 0)
            new_index = -1;
         neighbours.push_back(new_index);
         new_index = index + 1024;
         if (new_index < 0)
            new_index = -1;
         neighbours.push_back(new_index);
         new_index = index + 1025;
         if (new_index < 0)
            new_index = -1;
         neighbours.push_back(new_index);
         break;
      case ENeighbourhood::VONNEUMANN:
         new_index = index - 1024;
         if (new_index < 0 || new_index > size)
            new_index = -1;
         else if (labels[new_index] != 0)
            new_index = -1;
         neighbours.push_back(new_index);
         new_index = index - 1;
         if (new_index < 0 || new_index > size)
            new_index = -1;
         else if (labels[new_index] != 0)
            new_index = -1;
         neighbours.push_back(new_index);
         new_index = index + 1;
         if (new_index < 0 || new_index > size)
            new_index = -1;
         else if (labels[new_index] != 0)
            new_index = -1;
         neighbours.push_back(new_index);
         new_index = index + 1024;
         if (new_index < 0 || new_index > size)
            new_index = -1;
         else if (labels[new_index] != 0)
            new_index = -1;
         neighbours.push_back(new_index);
         break;
   }
   return neighbours;
}
