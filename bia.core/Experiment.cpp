#include "pch.h"
#include "Experiment.h"

#include <sstream>

/// <summary>
/// Zmienna statyczna wskazujaca nastepne id;
/// </summary>
int BIA::Experiment::nextId = 0;

/// <summary>
/// Funkcja pozwalajaca na inicjializacje
/// obiektu typu TIFFImage na podstawie
/// sciezki do obrazu oraz folderu, w ktorym
/// ma byc zlokalizowany (HORIZONTAL lub VERTICAL).
/// </summary>
void BIA::Experiment::IninitalizeTIFFImage(EFolder folder, fs::path path)
{
   switch (folder)
   {
      case EFolder::HORIZONTAL:
         _horTIFFImg = new TIFFImage();
         _horTIFFImg->SetImagePath(path);
         break;
      case EFolder::VERTICAL:
      default:
         _vertTIFFImg = new TIFFImage();
         _vertTIFFImg->SetImagePath(path);
         break;
   }
}

/// <summary>
/// Funkcja zwraca sciezke do obrazu na podstawie
/// folderu, w ktorym obraz jest zawarty (HORIZONTAL lub VERTICAL).
/// </summary>
fs::path BIA::Experiment::GetTIFFImagePath(EFolder folder)
{
   switch (folder)
   {
      case EFolder::HORIZONTAL:
         return _horTIFFImg->GetImagePath();
         break;
      case EFolder::VERTICAL:
      default:
         return _vertTIFFImg->GetImagePath();
         break;
   }
}

/// <summary>
/// Funkcja zwracajaca obiekt typu TIFFImage*
/// Na podstawie zmiennej folder, zwrocony
/// zostanie obraz zawarty w folderze Horizontal
/// lub Vertical.
/// </summary>
BIA::TIFFImage* BIA::Experiment::GetTIFFImage(EFolder folder)
{
   switch (folder)
   {
      case EFolder::HORIZONTAL:
         return _horTIFFImg;
         break;
      case EFolder::VERTICAL:
      default:
         return _vertTIFFImg;
         break;
   }

}

/// <summary>
/// Funkcja zwraca kolejne wolne id i ustawie zmienna statyczna
/// nextId na kolejne id w kolejnosci
/// </summary>
int BIA::Experiment::GetNextId()
{
   int i = nextId;
   nextId++;
   return i;
}

/// <summary>
/// Glowny konstruktor klasy Experiment.
/// </summary>
/// <param name="path"></param>
BIA::Experiment::Experiment(fs::path path)
{
   _path = path;
   _name = path.filename().string();
   _id = GetNextId();
}

/// <summary>
/// Destruktor
/// </summary>
BIA::Experiment::~Experiment()
{
}

/// <summary>
/// Funkcja zwracajaca sciezke do folderu tzw. eksperymentu.
/// </summary>
fs::path BIA::Experiment::GetPath()
{
   return _path;
}

/// <summary>
/// Funkcja zwraca sciezke do folderu zawartego wewnatrz eksperymentu
/// na podstawie argument typu EFolder sciezka prowadzi do folderu
/// Horizontal lub Vertical
/// </summary>
fs::path BIA::Experiment::GetPath(EFolder folder)
{
   fs::path parent = GetPath();

   std::stringstream ss;

   ss << parent.string() << "\\";

   switch (folder)
   {
      case EFolder::HORIZONTAL:
         ss << "horizontal";
         break;
      case EFolder::VERTICAL:
      default:
         ss << "vertical";
         break;
   }

   return fs::path(ss.str());
}

/// <summary>
/// Funkcja zwraca sciezke do eksperymentu czesciowego na podstawie id.
/// </summary>
fs::path BIA::Experiment::GetPartExperimentPathById(EFolder folder, int id)
{
   auto path = GetPath(folder);
   std::stringstream ss;

   ss << path.string() << "\\" << id;

   return fs::path(ss.str());
}

/// <summary>
/// Funkcja zwraca nazwe danego eksperymentu.
/// </summary>
std::string BIA::Experiment::GetName() const
{
   return _name;
}

/// <summary>
/// Funkcja zwraca wektor z obiektami typu PartExperiment.
/// </summary>
std::vector<BIA::PartExperiment>& BIA::Experiment::GetPartExperiments(EFolder alignment)
{
   switch (alignment)
   {
      case EFolder::HORIZONTAL:
         return _partExperimentsByAlignment[EFolder::HORIZONTAL];
         break;
      case EFolder::VERTICAL:
      default:
         return _partExperimentsByAlignment[EFolder::VERTICAL];
         break;
   }
}
