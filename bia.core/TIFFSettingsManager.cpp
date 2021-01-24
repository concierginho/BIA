#include "pch.h"
#include "TIFFSettingsManager.h"

void BIA::TIFFSettingsManager::Init()
{
}

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

   settings.ScanlineSize = TIFFScanlineSize(*tiff);

   return settings;
}

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

BIA::TIFFSettingsManager::TIFFSettingsManager()
{
}

BIA::TIFFSettingsManager::~TIFFSettingsManager()
{
}
