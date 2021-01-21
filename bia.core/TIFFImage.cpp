#include "pch.h"
#include "TIFFImage.h"

BIA::TIFFImage::TIFFImage(fs::path path)
{
   _path = path;
}

BIA::TIFFImage::~TIFFImage()
{
}

fs::path BIA::TIFFImage::GetPath()
{
   return _path;
}
