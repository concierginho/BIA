#include "pch.h"
#include "PartExperiment.h"

#include <sstream>

/// <summary>
/// Glowny konstruktor.
/// </summary>
BIA::PartExperiment::PartExperiment(fs::path path, std::string parentName)
{
    _path = path;
   _id = std::atoi(path.filename().string().c_str());
   _name = parentName + "_" + std::to_string(_id);

   _tiffImage = new TIFFImage();
   _tiffImage->SetImagePath(path.string() + "\\" + _name + "\.tif");
   _tiffImage->SetPreviewImagePath(fs::path(path.string() + "\\preview\\" + _name + "\.tif"));
}

/// <summary>
/// Destruktor
/// </summary>
BIA::PartExperiment::~PartExperiment()
{
}

/// <summary>
/// Funkcja zwraca sciezke do obrazu wewnatrz folderu 'prewiev',
/// ktory znajduje sie wewnatrz eksperymentu czesciowego.
/// </summary>
fs::path BIA::PartExperiment::GetPreviewPath() const
{
   return _tiffImage->GetPreviewImagePath();
}

/// <summary>
/// Funkcja zwraca sciezke do pliku 'result.json' wewnatrz eksperymentu czesciowego.
/// </summary>
fs::path BIA::PartExperiment::GetResultsJsonPath() const
{
   std::stringstream ss;
   ss << _path.string() << "\\results.json";
   return fs::path(ss.str());
}

/// <summary>
/// Funkcja zwraca sciezke do pliku 'info.json' wewnatrz eksperymentu czesciowego.
/// </summary>
fs::path BIA::PartExperiment::GetInfoJsonPath() const
{
   std::stringstream ss;
   ss << _path.string() << "\\info.json";
   return fs::path(ss.str());
}

/// <summary>
/// Funkcja zwraca sciezke do pliku 'recipe.json' wewnatrz eksperymentu czesciowego.
/// </summary>
fs::path BIA::PartExperiment::GetRecipeJsonPath() const
{
   std::stringstream ss;
   ss << _path.string() << "\\recipe.json";
   return fs::path(ss.str());
}

/// <summary>
/// Funkcja zwraca sciezke do folderu 'preview' wewnatrz eksperymentu czesciowego.
/// </summary>
fs::path BIA::PartExperiment::GetPreviewDirectory() const
{
   std::stringstream ss;
   ss << _path.string() << "\\preview";
   return fs::path(ss.str());
}

/// <summary>
/// Funkcja zwraca sciezke do obrazu wewnatrz eksperymentu czesciowego.
/// </summary>
fs::path BIA::PartExperiment::GetImagePath() const
{
   return _tiffImage->GetImagePath();
}

/// <summary>
/// Funckja zwraca obiekt typu TIFFImage*, ktory przechowuje
/// wszelkie informacje na temat danego obrazu typu 'tif'.
/// </summary>
BIA::TIFFImage* BIA::PartExperiment::GetTIFFImage()
{
   return _tiffImage;
}

/// <summary>
/// Funkcja zwraca id danego eksperymentu czesciowego
/// </summary>
int BIA::PartExperiment::GetId()
{
   return _id;
}

/// <summary>
/// Funkcja pozwalajaca ustawisc sciezke do obrazu.
/// </summary>
void BIA::PartExperiment::SetImagePath(fs::path imagePath)
{
   _tiffImage->SetImagePath(imagePath);
}

/// <summary>
/// Funkcja pozwalajaca ustawic obiekt typu TIFFImage*.
/// </summary>
void BIA::PartExperiment::SetTIFFImage(TIFFImage* tiffImage)
{
   _tiffImage = tiffImage;
}
