#include "pch.h"
#include "TIFFImage.h"

/// <summary>
/// Cel: Ustawienie sciezki do obrazu.
/// </summary>
/// <param name="image_path"></param>
void BIA::TIFFImage::SetImagePath(fs::path image_path)
{
   _image_path = image_path;
}

/// <summary>
/// Cel: Zwrocenie sciezki do obrazu.
/// </summary>
/// <returns></returns>
fs::path BIA::TIFFImage::GetImagePath() const
{
   return _image_path;
}

/// <summary>
/// Cel: Ustawienie sciezki do podgladu obrazu.
/// </summary>
/// <param name="preview_path"></param>
void BIA::TIFFImage::SetPreviewImagePath(fs::path preview_path)
{
   _preview_path = preview_path;
}

/// <summary>
/// Cel: Zwrocenie sciezki do podgladu obrazu.
/// </summary>
/// <returns></returns>
fs::path BIA::TIFFImage::GetPreviewImagePath() const
{
   return _preview_path;
}

/// <summary>
/// Cel: Ustawienie sciezki do ustawien.
/// </summary>
/// <param name="settings"></param>
void BIA::TIFFImage::SetImageSettings(BIA::TIFFImageSettings settings)
{
   _settings = settings;
}

/// <summary>
/// Cel: Zwrocenie referencji do ustawien.
/// </summary>
/// <returns></returns>
BIA::TIFFImageSettings& BIA::TIFFImage::GetImageSettings()
{
   return _settings;
}

/// <summary>
/// Domyslny konstruktor.
/// </summary>
BIA::TIFFImage::TIFFImage()
{
   _settings = {
      0,0,0,0,0,0
   };
}

/// <summary>
/// Destruktor.
/// </summary>
BIA::TIFFImage::~TIFFImage()
{
}
