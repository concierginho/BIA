#include "pch.h"
#include "BIAExperimentManager.h"
#include "Experiment.h"

#include <regex>

#ifdef _LOGGING_
/// <summary>
/// Konstruktor uzywany gdy _LOGGING_ jest zdefiniowany
/// </summary>
BIA::BIAExperimentManager::BIAExperimentManager(std::shared_ptr<BIAFileManager> fileManager, std::shared_ptr<BIALoggingManager> loggingManager)
{
   _fileManager = fileManager;
   _loggingManager = loggingManager;
}
#endif

/// <summary>
/// Konstruktor uzywany gdy _LOGGING_ nie jest zdefiniowany
/// </summary>
/// <param name="fileManager"></param>
BIA::BIAExperimentManager::BIAExperimentManager(std::shared_ptr<BIAFileManager> fileManager)
{
   _fileManager = fileManager;
}

/// <summary>
/// Destruktor
/// </summary>
BIA::BIAExperimentManager::~BIAExperimentManager()
{
}

/// <summary>
/// Funkcja sluzaca do inicjalizacji wszystkich obiektow typu
/// Experiment. Obiekty te przechowywane sa nastepnie w odpowiednim
/// wektorze. Wszelkie potrzebne foldery zostaja stworzone.
/// Nastepnie istniejace pliki zostaja przeniesione do odpowiednich
/// folderow na podstawie swojej nazwy - pliki ze slowem "Horizontal"
/// w nazwie zostaja przeniesione do folderu o nazwie "Horizontal",
/// Pliki ze slowem "Vertical" do folderu o nazwie "Vertical".
/// Nastepnie przygotowane zostaja tzw. PartExperiment'y.
/// PartExperiment to skladowa calego eksperymentu.
/// Kazdy eksperyment sklada sie z 40 takich obiektow.
/// W kolejnym kroku nastepuje zlokalizowanie plikow typu 'tif'.
/// </summary>
void BIA::BIAExperimentManager::PrepareExperiments()
{
#ifdef _LOGGING_
   _loggingManager.get()->Message << "Preparing experiments directories has been started.";
   _loggingManager->Log(ESource::BIA_EXPERIMENT_MANAGER);
   auto start = std::chrono::steady_clock::now();
#endif

   auto& experimentDirectories = _fileManager->GetRootDirectories();

   for (const auto& experiment : experimentDirectories)
      _experiments.push_back(Experiment(experiment));

   for(int i = 0; i < 2; i++)
      for (auto& experiment : _experiments)
      {
         if (!_fileManager->ExistsAtPath(experiment.GetPath((EFolder)i)))
            _fileManager->CreateAtPath(experiment.GetPath((EFolder)i), EFileType::DIRECTORY);
      }

   MoveExistingFiles();
   PreparePartExperiments();
   LocalizeTIFFImages();

#ifdef _LOGGING_
   auto end = std::chrono::steady_clock::now();
   auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
   _loggingManager.get()->Message << "Preparing experiments directories has ended and took: " << time << "ms.";
   _loggingManager->Log(ESource::BIA_EXPERIMENT_MANAGER);
#endif
}

/// <summary>
/// Funkcja przeszukujaca wszystkie eksperymenty
/// w poszukiwaniu obrazow typu 'tif'.
/// Gdy takowy znajdzie - sciezka do niego 
/// zostaje ustawiona w odpowiednim obiekcie typu PartExperiment.
/// </summary>
void BIA::BIAExperimentManager::LocalizeTIFFImages()
{
   for (int i = 0; i < 2; i++)
      for (auto& experiment : _experiments)
      {
         EFolder type = (EFolder)i;

         for (const auto item : fs::directory_iterator(experiment.GetPath((EFolder)i)))
         {
            if (!fs::is_directory(item))
               if (std::regex_match(item.path().string(), _fileManager->GetPattern(EPattern::EXTENSION_TIF)))
               {
                  experiment.IninitalizeTIFFImage(type, item.path());

#ifdef _LOGGING_
                  _loggingManager->Message << "Found TIFF image at path: " << item.path().string();
                  _loggingManager->Log(ESource::BIA_EXPERIMENT_MANAGER);
#endif
               }
         }
      }
}

/// <summary>
/// Funkcja przygotowujaca obiekty typu PartExperiment.
/// Tworzy wszystkie potrzebne foldery i pliki.
/// </summary>
void BIA::BIAExperimentManager::PreparePartExperiments()
{
#ifdef _LOGGING_
   _loggingManager.get()->Message << "Starting operation 'Preparing part experiments'.";
   _loggingManager.get()->Log(ESource::BIA_EXPERIMENT_MANAGER);
   auto start = std::chrono::steady_clock::now();
#endif

   for (int type = (int)EFolder::HORIZONTAL; type <= (int)EFolder::VERTICAL; type++)
   {
      auto folder = (EFolder)type;

      for (auto& experiment : _experiments)
      {
         auto path = experiment.GetPath(folder);
         auto directoryName = path.filename().string();

         for (int i = 0; i < 40; i++)
         {
            fs::path partExpPath = experiment.GetPartExperimentPathById(folder, i);

            if (!_fileManager->ExistsAtPath(partExpPath))
               _fileManager->CreateAtPath(partExpPath, EFileType::DIRECTORY);

            PartExperiment partExperiment(partExpPath, directoryName);

            experiment.GetPartExperiments(folder).push_back(partExperiment);
            Initialize(partExperiment);
         }
      }
   }

#ifdef _LOGGING_
   auto end = std::chrono::steady_clock::now();
   auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
   _loggingManager.get()->Message << "Ending operation 'Preparing part experiments', it took: " << time << "ms.";
   _loggingManager->Log(ESource::BIA_EXPERIMENT_MANAGER);
#endif

}

/// <summary>
/// Funkcja, ktora pozwala na klasyfikacje zawartosci poszczegolnych eksperymentow.
/// Szuka plikow nazwanych w okreslony sposob, a nastepnie przenosi odpowiednie
/// pliki w odpowiednie miejsca.
/// </summary>
void BIA::BIAExperimentManager::MoveExistingFiles()
{
   if (_experiments.size() == 0)
   {

#ifdef _LOGGING_
      _loggingManager->Message << "Experiments count = 0, proces terminated.";
      _loggingManager->Log(ESource::BIA_EXPERIMENT_MANAGER);
#endif

      return;
   }

   for (auto experiment : _experiments)
   {
      std::vector<fs::path> verticalItems;
      std::vector<fs::path> horizontalItems;

      for (auto const& item : fs::directory_iterator(experiment.GetPath()))
      {
         if (!item.is_directory())
         {
            std::string filename = item.path().filename().string();

            if (std::regex_match(filename, _fileManager->GetPattern(EPattern::CONTAINS_HORIZONTAL)))
               horizontalItems.push_back(item);
            else if (std::regex_match(filename, _fileManager->GetPattern(EPattern::CONTAINS_VERTICAL)))
               verticalItems.push_back(item);
         }
      }

      fs::path targetDir;

      targetDir = experiment.GetPath(EFolder::HORIZONTAL);
      _fileManager->ChangeFileLocation(targetDir, horizontalItems);

      targetDir = experiment.GetPath(EFolder::VERTICAL);
      _fileManager->ChangeFileLocation(targetDir, verticalItems);
   }
}

/// <summary>
/// Funkcja tworzaca wszystkie potrzebne do prawidlowego dzialania programu pliki
/// </summary>
void BIA::BIAExperimentManager::Initialize(PartExperiment& partExperiment)
{
   std::vector<fs::path> files;

   files.push_back(partExperiment.GetInfoJsonPath());
   files.push_back(partExperiment.GetResultsJsonPath());
   files.push_back(partExperiment.GetRecipeJsonPath());

   for (auto file : files)
      if (!_fileManager->ExistsAtPath(file))
         _fileManager->CreateAtPath(file, EFileType::NON_DIRECTORY);

   if (!_fileManager->ExistsAtPath(partExperiment.GetPreviewDirectory()))
      _fileManager->CreateAtPath(partExperiment.GetPreviewDirectory(), EFileType::DIRECTORY);
}

/// <summary>
/// Funkcja zwraca smart pointer do obiektu typu BIAFileManager.
/// </summary>
/// <returns></returns>
std::shared_ptr<BIA::BIAFileManager> BIA::BIAExperimentManager::GetFileManager()
{
   return _fileManager;
}

/// <summary>
/// Funkcja zwraca wektor z obiektami typu Experiment
/// </summary>
std::vector<BIA::Experiment>& BIA::BIAExperimentManager::GetExperiments()
{
   return _experiments;
}

/// <summary>
/// Funkcja inicjalizujaca
/// </summary>
void BIA::BIAExperimentManager::Init()
{
#ifdef _LOGGING_
   _loggingManager->Message << "Initializing BIAExperimentManager...";
   _loggingManager->Log(ESource::BIA_EXPERIMENT_MANAGER);
#endif
}
