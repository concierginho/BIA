#include "pch.h"

#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>

#include "BIAFileManager.h"
#include <nlohmann/json.hpp>

/// <summary>
/// Cel: Stworzenie wyrazen regularnych na uzytek BIAFileManager'a.
/// podczas skanowania folderow.
/// </summary>
void BIA::BIAFileManager::LoadPatterns()
{
   _patternByType[EPattern::DIRECTORY_HORIZONTAL] = std::regex("(.*horizontal$)", std::regex_constants::icase);
   _patternByType[EPattern::DIRECTORY_VERTICAL] = std::regex("(.*vertical$)", std::regex_constants::icase);
   
   _patternByType[EPattern::CONTAINS_HORIZONTAL] = std::regex("(.*horizontal.*)", std::regex_constants::icase);
   _patternByType[EPattern::CONTAINS_VERTICAL] = std::regex("(.*vertical.*)", std::regex_constants::icase);
   
   _patternByType[EPattern::EXTENSION_TIF] = std::regex("(.*tif$)", std::regex_constants::icase);
}

/// <summary>
/// Cel: Zwrocenie sciezki do katalogu glownego.
/// </summary>
/// <returns></returns>
std::string BIA::BIAFileManager::GetRootPath() const
{
   return _rootPath;
}

/// <summary>
/// Domyslny konstruktor.
/// </summary>
/// <param name="rootPath"></param>
BIA::BIAFileManager::BIAFileManager(std::string rootPath)
{
   _rootPath = rootPath;
}

/// <summary>
/// Destruktor.
/// </summary>
BIA::BIAFileManager::~BIAFileManager()
{
}

#ifdef _LOGGING_
/// <summary>
/// Konstruktor uzywany gdy _LOGGING_ jest zdefiniowane.
/// </summary>
/// <param name="loggingManager"></param>
void BIA::BIAFileManager::SetLoggingManager(std::shared_ptr<BIALoggingManager> loggingManager) 
{
   _loggingManager = loggingManager;
}
#endif

/// <summary>
/// Cel: Zwrocenie wyrazenia regularnego na podstawie wybranego wzoru.
/// </summary>
/// <param name="pattern"></param>
/// <returns></returns>
std::regex BIA::BIAFileManager::GetPattern(EPattern pattern)
{
   return _patternByType[pattern];
}

/// <summary>
/// Cel: Inicjalizacja.
/// </summary>
void BIA::BIAFileManager::Init()
{
   LoadPatterns();

#ifdef _LOGGING_
   _loggingManager->Message << "Initializing BIAFileManager...";
   _loggingManager->Log(ESource::BIA_FILE_MANAGER);
#endif
}

/// <summary>
/// Cel: Skanowanie glowengo katalogu.
///      W kolejnej fazie kazdy folder zwarty wewnatrz
///      katalogu glownego bedzie traktowany jako zrodlo
///      obrazow.
/// </summary>
void BIA::BIAFileManager::ScanRootDirectory()
{
   for (const auto& obj : std::filesystem::directory_iterator(_rootPath))
   {
      if (obj.is_directory() && obj.path().filename() != "log")
         _rootDirectories.push_back(obj.path());
      _rootFiles.push_back(obj.path());
   }
}

/// <summary>
/// Cel: Stworzenie pliku/folderu o wskazanej sciezce.
///      Argument typu EFileType pozwala okreslic czy dana sciezka
///      prowadzi do folderu czy do pliku.
/// </summary>
/// <param name="path"></param>
/// <param name="fileType"></param>
void BIA::BIAFileManager::CreateAtPath(fs::path path, EFileType fileType)
{
   if (ExistsAtPath(path))
      return;

   switch (fileType)
   {
      case EFileType::DIRECTORY:
         try
         {
            std::filesystem::create_directory(path);

#ifdef _LOGGING_
            _loggingManager->Message << "Created new directory: " << path.string();
            _loggingManager->Log(ESource::BIA_FILE_MANAGER);
#endif
         }
         catch (std::exception e)
         {
            e;

#ifdef _LOGGING_
            _loggingManager->Message << "Exception thrown: " << e.what();
            _loggingManager->Log(ESource::BIA_FILE_MANAGER);
#endif
         }
         break;
      case EFileType::NON_DIRECTORY:
         try
         {
            std::ofstream file{ path.string() };

#ifdef _LOGGING_
            _loggingManager->Message << "Created new file: " << path.string();
            _loggingManager->Log(ESource::BIA_FILE_MANAGER);
#endif
         }
         catch (std::exception e)
         {
            e;

#ifdef _LOGGING_
            _loggingManager->Message << "Exception thrown: " << e.what();
            _loggingManager->Log(ESource::BIA_FILE_MANAGER);
#endif
         }
         break;
   }
}

/// <summary>
/// Cel: Sprawdzenie czy istnieje folder/plik o podanej sciezce.
/// </summary>
/// <param name="path"></param>
/// <returns></returns>
bool BIA::BIAFileManager::ExistsAtPath(fs::path path)
{
   return fs::exists(path);
}

/// <summary>
/// Cel: Zwrocenie zawartosci folderu wskazanego za pomoca argument "path":
///      1. Wektor folderow,
///      2. Wektor plikow.
/// </summary>
/// <param name="path"></param>
/// <returns></returns>
std::unordered_map<BIA::EFileType, std::vector<fs::path>> BIA::BIAFileManager::GetDirectoryContent(fs::path path)
{
   std::vector<fs::path> directories;
   std::vector<fs::path> files;

   for (const auto& item : fs::directory_iterator(path))
   {
      if (item.is_directory())
         directories.push_back(item);
      else
         files.push_back(item);
   }

   return std::unordered_map<BIA::EFileType, std::vector<fs::path>>
   {
      { EFileType::DIRECTORY, directories },
      { EFileType::NON_DIRECTORY, files }
   };
}

/// <summary>
/// Cel: Odczytanie informacji z pliku typu '.json'.
/// </summary>
/// <param name="path"></param>
/// <returns></returns>
nlohmann::json BIA::BIAFileManager::ReadFromJson(fs::path& path)
{
   nlohmann::json json;
   std::ifstream i(path.string());
   i >> json;

   return json;
}

/// <summary>
/// Cel: Zapisanie informacji zawartych w drugiej zmiennej
///      do pliku typu '.json' wskazanego na podstawie sciezki (argument pierwszy).
/// </summary>
/// <param name="path"></param>
/// <param name="json"></param>
void BIA::BIAFileManager::WriteToJson(fs::path& path, nlohmann::json& json)
{
   if (!ExistsAtPath(path))
   {
      CreateAtPath(path, EFileType::NON_DIRECTORY);
   }

   if (ExistsAtPath(path) && json.empty() == false)
   {
      std::ofstream o;
      try
      {
         o.open(path.string(), std::ios_base::app);
         o << std::setw(4) << json << std::endl;
         o.close();
      }
      catch (std::exception ex)
      {
         ex;
#ifdef _LOGGING_
#endif
      }
   }
}

/// <summary>
/// Cel: Zmiana lokalizacji pliku wskazanego za pomoca argumentu
///      "sourceFile" do katalogu docelowego wskazanego za pomoca
///      parametru "destDir".
/// </summary>
/// <param name="destDir"></param>
/// <param name="sourceFile"></param>
void BIA::BIAFileManager::ChangeFileLocation(fs::path& destDir, fs::path& sourceFile)
{
   try
   {
      std::stringstream s;
      s << destDir.string() << "\\" <<  sourceFile.filename().string();
      fs::rename(sourceFile, fs::path(s.str()));
#ifdef _LOGGING_
      _loggingManager->Message << "Moving file: " << sourceFile << "\n" << "To: " << s.str();
      _loggingManager->Log(ESource::BIA_FILE_MANAGER);
#endif
   }
   catch (std::exception e)
   {
#ifdef _LOGGING_
      _loggingManager->Message << "Exception thrown: " << e.what();
      _loggingManager->Log(ESource::BIA_FILE_MANAGER);
#endif
   }
}

/// <summary>
/// Cel: Przeniesienie wektoru plikow zapisanych w parametrze "sourceFiles"
///      do katalogu wskazanego w parametrze "destDir".
/// </summary>
/// <param name="destDir"></param>
/// <param name="sourceFiles"></param>
void BIA::BIAFileManager::ChangeFileLocation(fs::path& destDir, std::vector<fs::path> sourceFiles)
{
   for (auto& file : sourceFiles)
      ChangeFileLocation(destDir, file);
}

/// <summary>
/// Cel: Zwrocenie katalogow zawartych w katalogu glownym.
/// </summary>
std::vector<fs::path>& BIA::BIAFileManager::GetRootDirectories()
{
   return _rootDirectories;
}

/// <summary>
/// Cel: Zwrocenie plikow zawartych w katalogu glownym.
/// </summary>
std::vector<fs::path>& BIA::BIAFileManager::GetRootFiles()
{
   return _rootFiles;
}
