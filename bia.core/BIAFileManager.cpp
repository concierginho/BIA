#include "pch.h"

#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>

#include "BIAFileManager.h"

/// <summary>
/// Funckja wczytuje wszystkie wyrazenia regularne, ktore sa wykorzystywane
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
/// Funkcja zwraca sciezke do glownego katalogu jako typu std::string.
/// </summary>
std::string BIA::BIAFileManager::GetRootPath() const
{
   return _rootPath;
}

/// <summary>
/// Konstruktor domyslny
/// </summary>
BIA::BIAFileManager::BIAFileManager(std::string rootPath)
{
   _rootPath = rootPath;
}

/// <summary>
/// Destruktor
/// </summary>
BIA::BIAFileManager::~BIAFileManager()
{
}

#ifdef _LOGGING_
/// <summary>
/// Funkcja pozwala na ustawienie menadzera logowania.
/// Jest on ustawiany za pomoca tej funkcji, poniewaz
/// podczas inicjalizacji FileManager'a nie wiadomo
/// jeszcze o tym czy LoggingManager bedzie wykorzystany.
/// </summary>
/// <param name="loggingManager"></param>
void BIA::BIAFileManager::SetLoggingManager(std::shared_ptr<BIALoggingManager> loggingManager) 
{
   _loggingManager = loggingManager;
}
#endif

/// <summary>
/// Funckja zwraca odpowiednie wyrazenie regularne na podstawie okreslonego
/// argumentu typu EPattern.
/// </summary>
std::regex BIA::BIAFileManager::GetPattern(EPattern pattern)
{
   return _patternByType[pattern];
}

/// <summary>
/// Funkcja inicjalizujaca wszystkie potrzebne do dzialania obiekty.
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
/// Funckja odpowiada za skanowanie zawartosci glownego folderu.
/// Kazdy folder zawarty w katalogu glownym (oprocz folderu "log")
/// bedzie w pozniejszej fazie traktowany jako tzw. "ekseryment".
/// Przez eksperyment nalezy rozumiec katalog, ktorym bezposrednio
/// znajda sie conajmniej dwa obrazy pochodzace z mikroskopu
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
/// Funkcja sluzy do stworzenia pliku o wskazanej sciezce
/// Argument typu EFileType pozwala okreslic czy dana sciezka
/// prowadzi do folderu czy tez do pliku.
/// </summary>
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
/// Funckja sprawdza czy plik/folder o podanej sciezce istnieje.
/// </summary>
bool BIA::BIAFileManager::ExistsAtPath(fs::path path)
{
   return fs::exists(path);
}

/// <summary>
/// Funkcja sluzy do skanowania folderu.
/// Zwraca mape skladajaca sie z dwoch wektorw
/// 1. Wektor folderow
/// 2. Wektor plikow
/// znajdujacych sie we wskazanym folderze.
/// </summary>
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
/// Funkcja pozwala na przeniesienie pojedynczego pliku/folderu
/// do wskazanego w pierwszym argumencie miejsca docelowego.
/// </summary>
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
/// Funkcja pozwala na przeniesienie wektoru plikow/folderow 
/// do wskazanego w argumencie pierwszym folderu
/// </summary>
void BIA::BIAFileManager::ChangeFileLocation(fs::path& destDir, std::vector<fs::path> sourceFiles)
{
   for (auto& file : sourceFiles)
      ChangeFileLocation(destDir, file);
}

/// <summary>
/// Funkcja zwraca wektor folderow znajdujacych sie w glownym katalogu.
/// </summary>
std::vector<fs::path>& BIA::BIAFileManager::GetRootDirectories()
{
   return _rootDirectories;
}

/// <summary>
/// Funkcja zwraca wektor plikow znajdujach sie w glownym katalogu.
/// </summary>
std::vector<fs::path>& BIA::BIAFileManager::GetRootFiles()
{
   return _rootFiles;
}
