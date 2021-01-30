#include "pch.h"
#include "BIAExperimentManager.h"
#include "Experiment.h"
#include "JsonSettings.h"

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
/// Cel: Inicjalizacja obiektow typu "Experiment".
///      Obiekty tego typu przechowywane sa w wektorze.
///      Wszystkie potrzebne katalogi zostaja stworzone
///      wedle schematu:
///      \root
///         \Experiment0
///            \Horizontal
///               \Horizontal.tif
///               \PartExperiment0
///                  \PartExperiment0.tif
///                  \results.json
///                  \recipe.json
///                  \preview.tif
///               \PartExperiment1
///               .
///               .
///               .
///               \PartExperiment39
///            \Vertical
///               \Vertical.tif
///               \PartExperiment0
///               \PartExperiment1
///               .
///               .
///               .
///               \PartExperiment39
///         \Experiment1
///         .
///         .
///         .
///         \Experiment39
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
/// Cel: Lokalizacja obrazow typu 'tif'.
///      Funkcja przechodzi przez wszystkie katalogi oraz pliki
///      i przypisuje odpowiednie wartosci sciezek do odpowiednich
///      eksperymentow.
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
/// Cel: Przygotowanie obiektow typu "PartExperiment".
///      Wywolywana przez funckje "PrepareExperiments()"
///      Stanowi jej integralna czesc.
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
            InitializePartExperiment(partExperiment);
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
/// 
/// </summary>
/// <param name="path"></param>
void BIA::BIAExperimentManager::PrepareRecipeJson(PartExperiment& partExperiment)
{
   fs::path recipeJsonPath = partExperiment.GetRecipeJsonPath();

   if (!_fileManager->ExistsAtPath(recipeJsonPath))
   {
      _fileManager->CreateAtPath(recipeJsonPath, EFileType::NON_DIRECTORY);

      auto defaultRecipeJson = JsonSettings::GetDefaultRecipeJson();

      _fileManager->WriteToJson(recipeJsonPath, defaultRecipeJson);
   }
}

/// <summary>
/// 
/// </summary>
/// <param name=""></param>
void BIA::BIAExperimentManager::PrepareResultsJson(PartExperiment& partExperiment)
{
   fs::path resultsJson = partExperiment.GetResultsJsonPath();

   if (!_fileManager->ExistsAtPath(resultsJson))
   {
      _fileManager->CreateAtPath(resultsJson, EFileType::NON_DIRECTORY);
   }
}

/// <summary>
/// Cel: Przenosi pliki na podstawie ich nazwy do odpowiednich lokalizacji.
///      Przyklad: Horizontal 4.5min.tif zostanie przeniesiony do folderu
///                o nazwie "Horizontal" wewnatrz eksperymentu gdzie zostal
///                zlokalizowany.
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
/// Cel: Inicjalizacja czesciowego eksperymentu wskazanego
///      w parametrze "partExperiment" oraz stworzenie
///      odpowiednich pliku wewnatrz katalogu czesciowego eksperymentu.
/// </summary>
/// <param name="partExperiment"></param>
void BIA::BIAExperimentManager::InitializePartExperiment(PartExperiment& partExperiment)
{
   PrepareRecipeJson(partExperiment);
   PrepareResultsJson(partExperiment);
}

/// <summary>
/// Cel: Zwrocenie obiektu typu std::shared_ptr<BIA::BIAFileManager>.
/// </summary>
/// <returns></returns>
std::shared_ptr<BIA::BIAFileManager> BIA::BIAExperimentManager::GetFileManager()
{
   return _fileManager;
}

/// <summary>
/// Cel: Zwrocenie referencji do wektora, w ktorym zapisane sa eksperymenty.
/// </summary>
/// <returns></returns>
std::vector<BIA::Experiment>& BIA::BIAExperimentManager::GetExperiments()
{
   return _experiments;
}

/// <summary>
/// Cel: Inicjalizacja.
/// </summary>
void BIA::BIAExperimentManager::Init()
{
#ifdef _LOGGING_
   _loggingManager->Message << "Initializing BIAExperimentManager...";
   _loggingManager->Log(ESource::BIA_EXPERIMENT_MANAGER);
#endif
}
