#include "pch.h"
#include "Experiment.h"

#include <sstream>

/// <summary>
/// Cel: Zmienna statyczna wskazujaca nastepne id;
/// </summary>
int BIA::Experiment::nextId = 0;

/// <summary>
/// Cel: Inicjalizacja obiektu TIFFImage na podstawie sciezki
///      do obrazu.
/// </summary>
/// <param name="folder"></param>
/// <param name="path"></param>
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
/// Cel: Zwrocenie sciezki do obrazu na podstawie folderu,
///      w ktorym obraz jest zawarty (HORIZONTAL lub VERTICAL).
/// </summary>
/// <param name="folder"></param>
/// <returns></returns>
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
/// Cel: Zwrocenie obiektu typu TIFFImage na podstawie folderu,
///      w ktorym sie znajduje (HORIZONTAL lub VERTICAL).
/// </summary>
/// <param name="folder"></param>
/// <returns></returns>
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
/// Cel: Zwrocenie kolejnego id oraz inkrementacja licznika.
/// </summary>
int BIA::Experiment::GetNextId()
{
   int i = nextId;
   nextId++;
   return i;
}

/// <summary>
/// Domyslny konstruktor.
/// </summary>
/// <param name="path"></param>
BIA::Experiment::Experiment(fs::path path)
{
   _path = path;
   _name = path.filename().string();
   _id = GetNextId();
}

/// <summary>
/// Destruktor.
/// </summary>
BIA::Experiment::~Experiment()
{
}

/// <summary>
/// Cel: Zwrocenie sciezki do folderu (eksperymentu).
/// </summary>
fs::path BIA::Experiment::GetPath()
{
   return _path;
}

/// <summary>
/// Cel: Zwrocenie sciezki do folderu VERTICAL lub HORIZONTAL
///      znajdujacego sie wewnatrz eksperymentu.
/// </summary>
/// <param name="folder"></param>
/// <returns></returns>
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
/// Cel: Zwrocenie sciezki do eksperymentu na podstawie id.
/// </summary>
/// <param name="folder"></param>
/// <param name="id"></param>
/// <returns></returns>
fs::path BIA::Experiment::GetPartExperimentPathById(EFolder folder, int id)
{
   auto path = GetPath(folder);
   std::stringstream ss;

   ss << path.string() << "\\" << id;

   return fs::path(ss.str());
}

BIA::PartExperiment* BIA::Experiment::GetPartExperimentById(EFolder folder, int id)
{
   return &_partExperimentsByAlignment[folder][id];
}

/// <summary>
/// Cel: Zwrocenie nazwy eksperymentu.
/// </summary>
/// <returns></returns>
std::string BIA::Experiment::GetName() const
{
   return _name;
}

/// <summary>
/// Cel: Zwrocenie eksperymentow czesciowych na podstawie wartosci
///      argumentu VERTICAL lub HORIZONTAL.
/// </summary>
/// <param name="alignment"></param>
/// <returns></returns>
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
