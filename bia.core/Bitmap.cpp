#include "pch.h"
#include "Bitmap.h"
#include "Operation.h"
#include "TIFFSettingsManager.h"

#include "tiffio.h"

/// <summary>
/// Domyslny konstruktor.
/// </summary>
/// <param name="width"></param>
/// <param name="length"></param>
BIA::Bitmap::Bitmap(int width, int length)
{
   _width = width;
   _length = length;
   _buffer = new unsigned char[(width * length)];
}

/// <summary>
/// Destruktor.
/// </summary>
BIA::Bitmap::~Bitmap()
{
   if (_buffer != nullptr)
      delete _buffer;
   _buffer = nullptr;
}

/// <summary>
/// Cel: Zaladowanie informacji z pliku do bitmapy.
/// </summary>
/// <param name="path"></param>
void BIA::Bitmap::LoadFromFile(fs::path& path)
{
   std::string pathStr = path.string();
   const char* c_pathStr = pathStr.c_str();

   TIFF* tiff = TIFFOpen(c_pathStr, READ);

   if (tiff != nullptr)
   {
      uint32 linebytes = (uint32)_width;
      unsigned char* buffer = (unsigned char*)_TIFFmalloc(linebytes);
#ifdef _LOGGING_
#endif

      for (uint32 row = 0; row < (uint32)_width; row++)
      {
         TIFFReadScanline(tiff, buffer, row);
         memcpy(&_buffer[row * linebytes], buffer, _width);
      }

      _TIFFfree(buffer);
      TIFFClose(tiff);
   }
}

/// <summary>
/// Cel: Zapisanie bitmapy do pliku.
/// </summary>
/// <param name="path"></param>
void BIA::Bitmap::SaveToFile(fs::path& path)
{
   std::string pathStr = path.string();
   const char* c_pathStr = pathStr.c_str();

   if (fs::remove(path) == false)
      return;

   TIFFSettingsManager settingsManager;
   auto settings = settingsManager.GetPreviewImageSettings();

   TIFF* tiff = TIFFOpen(c_pathStr, WRITE);

   settingsManager.ApplySettings(&tiff, settings);

   if (tiff != nullptr)
   {
      uint32 linebytes = (uint32)_width;
      unsigned char* buffer = (unsigned char*)_TIFFmalloc(linebytes);
#ifdef _LOGGING_
#endif

      for (uint32 row = 0; row < (uint32)_width; row++)
      {
         memcpy(buffer, &_buffer[row * linebytes], _width);
         if (TIFFWriteScanline(tiff, buffer, row) < 0)
            break;
      }

      _TIFFfree(buffer);
      TIFFClose(tiff);
   }
}

/// <summary>
/// Cel: Zwrocenie indeksu pixela o wskazanych wspolrzednych.
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
int BIA::Bitmap::Index(int x, int y)
{
   return x + _width * y;
}
