#include "pch.h"
#include "TIFFImage.h"

/// <summary>
/// Funckja pozwalajaca ustawic sciezke do obrazu typu 'tif'.
/// </summary>
void BIA::TIFFImage::SetImagePath(fs::path image_path)
{
   _image_path = image_path;
}

/// <summary>
/// Funckja zwracajaca sciezke do obrazu typu 'tif'.
/// </summary>
fs::path BIA::TIFFImage::GetImagePath() const
{
   return _image_path;
}

/// <summary>
/// Funkcja pozwalajaca ustawic sciezke do obrazu typu 'tif'
/// znajdujacego sie wewnatrz katalogu 'preview'.
/// </summary>
void BIA::TIFFImage::SetPreviewImagePath(fs::path preview_path)
{
   _preview_path = preview_path;
}

/// <summary>
/// Funkcja zwracajaca sciezke do obrazu typu 'tif'
/// znajdujacego sie wewnatrz katalogu 'preview'.
/// </summary>
fs::path BIA::TIFFImage::GetPreviewImagePath() const
{
   return _preview_path;
}

/// <summary>
/// Funkcja pozwalajaca ustawic ustawienia dla danego brazu typu 'tif'.
/// </summary>
void BIA::TIFFImage::SetImageSettings(BIA::TIFFImageSettings settings)
{
   _settings = settings;
}

/// <summary>
/// Funkcja zwracajaca ustawienia dla danego brazu typu 'tif'.
/// </summary>
BIA::TIFFImageSettings& BIA::TIFFImage::GetImageSettings()
{
   return _settings;
}

/// <summary>
/// Glowny konstruktor
/// </summary>
BIA::TIFFImage::TIFFImage()
{
   _settings = {
      0,0,0,0,0,0
   };
}

/// <summary>
/// Destruktor
/// </summary>
BIA::TIFFImage::~TIFFImage()
{
}
