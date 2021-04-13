#include "pch.h"
#include "TIFFSettingsManager.h"

/// <summary>
/// Cel: Inicjalizacja.
/// </summary>
void BIA::TIFFSettingsManager::Init()
{
}

/// <summary>
/// Cel: Odczytanie ustawien zapisancyh w (otwartym wczesniej) obrazie.
/// </summary>
/// <param name="tiff"></param>
/// <returns></returns>
BIA::TIFFImageSettings BIA::TIFFSettingsManager::ReadSettings(TIFF** tiff)
{
   TIFFImageSettings settings = { };

   if (*tiff == nullptr)
      return settings;

   TIFFGetField(*tiff, TIFFTAG_IMAGEWIDTH, &settings.ImageWidth);
   TIFFGetField(*tiff, TIFFTAG_IMAGELENGTH, &settings.ImageLength);
   TIFFGetField(*tiff, TIFFTAG_BITSPERSAMPLE, &settings.BitsPerSample);
   TIFFGetField(*tiff, TIFFTAG_SAMPLESPERPIXEL, &settings.SamplesPerPixel);
   TIFFGetField(*tiff, TIFFTAG_RESOLUTIONUNIT, &settings.ResolutionUnit);

   settings.ScanlineSize = static_cast<uint32>(TIFFScanlineSize(*tiff));

   return settings;
}

/// <summary>
/// Cel: Zwrocenie ustawien dla czesciowego obrazu na podstawie ustawien
///      z obrazu zrodlowego.
/// </summary>
/// <param name="parentSettings"></param>
/// <returns></returns>
BIA::TIFFImageSettings BIA::TIFFSettingsManager::GetPartImageSettings(TIFFImageSettings parentSettings)
{
   return
   {
      1024,
      1024,
      (uint32)1024 * parentSettings.SamplesPerPixel,
      parentSettings.BitsPerSample,
      parentSettings.SamplesPerPixel,
      parentSettings.ResolutionUnit
   };
}

/// <summary>
/// Cel: Zwrocenie ustawien dla podgladu.
/// </summary>
/// <returns></returns>
BIA::TIFFImageSettings BIA::TIFFSettingsManager::GetPreviewImageSettings()
{
   return
   {
      1024,
      1024,
      (uint32)1024,
      8,
      1,
      2
   };
}

/// <summary>
/// Cel: Zapisanie ustawien w (otwartym wczesniej) obrazie.
/// </summary>
/// <param name="tiff"></param>
/// <param name="tiffImageSettings"></param>
void BIA::TIFFSettingsManager::ApplySettings(TIFF** tiff, TIFFImageSettings tiffImageSettings)
{
   TIFFSetField(*tiff, TIFFTAG_IMAGEWIDTH, tiffImageSettings.ImageWidth);
   TIFFSetField(*tiff, TIFFTAG_IMAGELENGTH, tiffImageSettings.ImageLength);
   TIFFSetField(*tiff, TIFFTAG_RESOLUTIONUNIT, tiffImageSettings.ResolutionUnit);
   TIFFSetField(*tiff, TIFFTAG_SAMPLESPERPIXEL, tiffImageSettings.SamplesPerPixel);
   TIFFSetField(*tiff, TIFFTAG_BITSPERSAMPLE, tiffImageSettings.BitsPerSample);
   TIFFSetField(*tiff, TIFFTAG_ROWSPERSTRIP, TIFFDefaultStripSize(*tiff, tiffImageSettings.ImageWidth * tiffImageSettings.SamplesPerPixel));
   TIFFSetField(*tiff, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
   TIFFSetField(*tiff, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
   TIFFSetField(*tiff, TIFFTAG_COMPRESSION, COMPRESSION_NONE);
}

/// <summary>
/// Domyslny konstruktor.
/// </summary>
BIA::TIFFSettingsManager::TIFFSettingsManager()
{
}

/// <summary>
/// Destruktor.
/// </summary>
BIA::TIFFSettingsManager::~TIFFSettingsManager()
{
}
