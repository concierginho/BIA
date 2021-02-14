#include "pch.h"
#include "BIAExperimentManager.h"
#include "Experiment.h"
#include "JsonSettings.h"
#include "Keys.h"

#include <regex>

#ifdef _LOGGING_
/// <summary>
/// Konstruktor uzywany gdy _LOGGING_ jest zdefiniowany.
/// </summary>
BIA::BIAExperimentManager::BIAExperimentManager(std::shared_ptr<BIAFileManager> fileManager, std::shared_ptr<BIALoggingManager> loggingManager)
{
   _fileManager = fileManager;
   _loggingManager = loggingManager;
}
#endif

/// <summary>
/// Domyslny konstruktor.
/// </summary>
/// <param name="fileManager"></param>
BIA::BIAExperimentManager::BIAExperimentManager(std::shared_ptr<BIAFileManager> fileManager)
{
   _fileManager = fileManager;
}

/// <summary>
/// Destruktor.
/// </summary>
BIA::BIAExperimentManager::~BIAExperimentManager()
{
}

/// <summary>
/// 
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
BIA::Experiment* BIA::BIAExperimentManager::GetExperiment(const char* name)
{
   std::string strName = name;
   for (auto& experiment : _experiments)
   {
      if (experiment.GetName() == strName)
         return &experiment;
   }
   return nullptr;
}

/// <summary>
/// 
/// </summary>
/// <param name="name"></param>
/// <param name="id"></param>
/// <param name="isHorizontal"></param>
/// <returns></returns>
BIA::PartExperiment* BIA::BIAExperimentManager::GetPartExperiment(const char* name, int id, bool isHorizontal)
{
   EFolder type = EFolder::VERTICAL;
   if (isHorizontal)
      type = EFolder::HORIZONTAL;

   return GetExperiment(name)->GetPartExperimentById(type, id);
}

/// <summary>
/// 
/// </summary>
/// <param name="name"></param>
/// <param name="id"></param>
/// <param name="isHorizontal"></param>
/// <param name="operation"></param>
/// <param name="args"></param>
/// <returns></returns>
bool BIA::BIAExperimentManager::AddOperation(const char* name, int id, bool isHorizontal, EOperation operation, const char* args)
{
   auto partExperiment = GetPartExperiment(name, id, isHorizontal);
   auto recipePath = partExperiment->GetRecipeJsonPath();

   auto json = _fileManager->ReadFromJson(recipePath);
   nlohmann::json insertOperationJson;
   nlohmann::json operationJson;

   std::string strName;
   switch (operation)
   {
      case EOperation::CLOSING:
         strName = key::closing;
         break;
      case EOperation::DILATION:
         strName = key::dilation;
         break;
      case EOperation::EROSION:
         strName = key::erosion;
         break;
      case EOperation::GAMMA_CORRECTION:
         strName = key::gamma_correction;
         break;
      case EOperation::LABELING:
         strName = key::labeling;
         break;
      case EOperation::OPENING:
         strName = key::opening;
         break;
   }

   operationJson[key::name] = strName;
   operationJson[key::args] = args;
   insertOperationJson[key::operation] = operationJson;
   json[key::operations].insert(json[key::operations].end(), insertOperationJson);

   _fileManager->WriteToJson(recipePath, json);
   
   return false;
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
      bool isHorizontal = true;
      if (folder == EFolder::VERTICAL)
         isHorizontal = false;

      for (auto& experiment : _experiments)
      {
         auto path = experiment.GetPath(folder);
         auto directoryName = path.filename().string();

         for (int i = 0; i < 40; i++)
         {
            fs::path partExpPath = experiment.GetPartExperimentPathById(folder, i);

            if (!_fileManager->ExistsAtPath(partExpPath))
               _fileManager->CreateAtPath(partExpPath, EFileType::DIRECTORY);

            PartExperiment partExperiment(partExpPath, directoryName, isHorizontal);

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
/// Cel: Przygotowanie pliku 'recipe.json'.
///      Jezeli plik nie istnieje - zostaje wypelniony wartosciami domyslnymi.
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
/// 
/// </summary>
/// <param name="idx"></param>
/// <param name="isHorizontal"></param>
/// <returns></returns>
std::vector<BIA::PartExperiment>& BIA::BIAExperimentManager::GetPartExperiments(int idx, bool isHorizontal)
{
   std::vector<PartExperiment> partExperiments;

   if (idx >= 0 && idx < _experiments.size())
   {
      if (isHorizontal)
         return _experiments[idx].GetPartExperiments(EFolder::HORIZONTAL);
      else
         return _experiments[idx].GetPartExperiments(EFolder::VERTICAL);
   }
   return partExperiments;
}

/// <summary>
/// Cel: Zwrocenie nazwy eksperymentu o podanym indexie.
/// </summary>
/// <param name="idx"></param>
/// <returns></returns>
std::string BIA::BIAExperimentManager::GetExperimentName(int idx)
{
   return _experiments[idx].GetName().c_str();
}

/// <summary>
/// Cel: Zwrocenie rozmiaru wektora eksperymentow.
/// </summary>
/// <returns></returns>
int BIA::BIAExperimentManager::GetExperimentsSize()
{
   return _experiments.size();
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

std::string BIA::BIAExperimentManager::GetPartExperimentPreviewImagePath(const char* name, int id, bool isHorizontal)
{
   auto experiment = GetExperiment(name);

   if (experiment != nullptr)
   {
      EFolder type = EFolder::VERTICAL;
      if (isHorizontal)
         type = EFolder::HORIZONTAL;

      auto partExperiment = experiment->GetPartExperimentById(type, id);
      auto imagePath = partExperiment->GetPreviewImagePath();
      return imagePath.string();
   }

   return std::string();
}

/// <summary>
/// 
/// </summary>
/// <param name="name"></param>
/// <param name="id"></param>
/// <param name="isHorizontal"></param>
/// <returns></returns>
std::string BIA::BIAExperimentManager::GetPartExperimentImagePath(const char* name, int id, bool isHorizontal)
{
   auto experiment = GetExperiment(name);

   if (experiment != nullptr)
   {
      EFolder type = EFolder::VERTICAL;
      if (isHorizontal)
         type = EFolder::HORIZONTAL;

      auto partExperiment = experiment->GetPartExperimentById(type, id);
      auto imagePath = partExperiment->GetImagePath();
      return imagePath.string();
   }

   return std::string();
}
