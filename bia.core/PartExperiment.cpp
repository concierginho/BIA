#include "pch.h"
#include "PartExperiment.h"

#include <sstream>

BIA::PartExperiment::PartExperiment(fs::path path, std::string parentName)
{
   _path = path;
   ID = std::atoi(path.filename().string().c_str());
   _name = parentName + "_" + std::to_string(ID);
   SetImagePath(fs::path(_path.string() + "\\" + _name + "\.tif"));
   _tiffImage = new TIFFImage(_imagePath);
}

BIA::PartExperiment::~PartExperiment()
{
}

void BIA::PartExperiment::SetImagePath(fs::path imagePath)
{
   _imagePath = imagePath;
}

fs::path BIA::PartExperiment::GetResultsJsonPath() const
{
   std::stringstream ss;
   ss << _path.string() << "\\results.json";
   return fs::path(ss.str());
}

fs::path BIA::PartExperiment::GetInfoJsonPath() const
{
   std::stringstream ss;
   ss << _path.string() << "\\info.json";
   return fs::path(ss.str());
}

fs::path BIA::PartExperiment::GetRecipeJsonPath() const
{
   std::stringstream ss;
   ss << _path.string() << "\\recipe.json";
   return fs::path(ss.str());
}

fs::path BIA::PartExperiment::GetPreviewDirectory() const
{
   std::stringstream ss;
   ss << _path.string() << "\\preview";
   return fs::path(ss.str());
}

fs::path BIA::PartExperiment::GetImagePath() const
{
   return _imagePath;
}

BIA::TIFFImage* BIA::PartExperiment::GetTIFFImage()
{
   return _tiffImage;
}

void BIA::PartExperiment::SetTIFFImage(TIFFImage* tiffImage)
{
   _tiffImage = tiffImage;
}
