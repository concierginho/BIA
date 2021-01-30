#include "pch.h"
#include "PartExperiment.h"

#include <sstream>

/// <summary>
/// Domyslny konstruktor.
/// </summary>
BIA::PartExperiment::PartExperiment(fs::path path, std::string parentName)
{
    _path = path;
   _id = std::atoi(path.filename().string().c_str());
   _name = parentName + "_" + std::to_string(_id);

   _tiffImage = new TIFFImage();
   _tiffImage->SetImagePath(path.string() + "\\" + _name + ".tif");
   _tiffImage->SetPreviewImagePath(fs::path(path.string() + "\\preview.tif"));
}

/// <summary>
/// Destruktor.
/// </summary>
BIA::PartExperiment::~PartExperiment()
{
}

/// <summary>
/// Cel: Zwrocenie sciezki do pliku 'results.json'.
/// </summary>
fs::path BIA::PartExperiment::GetResultsJsonPath() const
{
   std::stringstream ss;
   ss << _path.string() << "\\results.json";
   return fs::path(ss.str());
}

/// <summary>
/// Cel: Zwrocenie sciezki do pliku 'recipe.json'.
/// </summary>
fs::path BIA::PartExperiment::GetRecipeJsonPath() const
{
   std::stringstream ss;
   ss << _path.string() << "\\recipe.json";
   return fs::path(ss.str());
}

/// <summary>
/// Cel: Zwrocenie sciezki do obrazu nalezacego do eksperymentu czesciowego.
/// </summary>
fs::path BIA::PartExperiment::GetImagePath() const
{
   return _tiffImage->GetImagePath();
}

/// <summary>
/// Cel: Zwrocenie sciezki do podgladu obrazu nalezacego do eksperymentu czesciowego.
/// </summary>
/// <returns></returns>
fs::path BIA::PartExperiment::GetPreviewImagePath() const
{
   return _tiffImage->GetPreviewImagePath();
}

/// <summary>
/// Cel: Zwrocenie obiektu typu TIFFImage*.
/// </summary>
BIA::TIFFImage* BIA::PartExperiment::GetTIFFImage()
{
   return _tiffImage;
}

/// <summary>
/// Cel: Zwrocenie id eksperymentu czesciowego.
/// </summary>
int BIA::PartExperiment::GetId()
{
   return _id;
}

/// <summary>
/// Cel: Ustawienie sciezki do obrazu czesciowego.
/// </summary>
/// <param name="imagePath"></param>
void BIA::PartExperiment::SetImagePath(fs::path imagePath)
{
   _tiffImage->SetImagePath(imagePath);
}

/// <summary>
/// Cel: Ustawienie obiektu typu 'TIFFImage*'.
/// </summary>
/// <param name="tiffImage"></param>
void BIA::PartExperiment::SetTIFFImage(TIFFImage* tiffImage)
{
   _tiffImage = tiffImage;
}
