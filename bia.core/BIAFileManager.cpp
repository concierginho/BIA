#include "pch.h"

#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>

#include "BIAFileManager.h"

void BIA::BIAFileManager::LoadPatterns()
{
   _patternByType[EPattern::DIRECTORY_HORIZONTAL] = std::regex("(.*horizontal$)", std::regex_constants::icase);
   _patternByType[EPattern::DIRECTORY_VERTICAL] = std::regex("(.*vertical$)", std::regex_constants::icase);
   
   _patternByType[EPattern::CONTAINS_HORIZONTAL] = std::regex("(.*horizontal.*)", std::regex_constants::icase);
   _patternByType[EPattern::CONTAINS_VERTICAL] = std::regex("(.*vertical.*)", std::regex_constants::icase);
   
   _patternByType[EPattern::EXTENSION_TIF] = std::regex("(.*tif$)", std::regex_constants::icase);
}

std::string BIA::BIAFileManager::GetRootPath() const
{
   return _rootPath;
}

BIA::BIAFileManager::BIAFileManager(std::string rootPath)
{
   _rootPath = rootPath;
}

BIA::BIAFileManager::~BIAFileManager()
{
}

#ifdef _LOGGING_
void BIA::BIAFileManager::SetLoggingManager(std::shared_ptr<BIALoggingManager> loggingManager) 
{
   _loggingManager = loggingManager;
}
#endif

std::regex BIA::BIAFileManager::GetPattern(EPattern pattern)
{
   return _patternByType[pattern];
}

void BIA::BIAFileManager::Init()
{
   LoadPatterns();

#ifdef _LOGGING_
   _loggingManager->Message << "Initializing BIAFileManager.";
   _loggingManager->Log(ESource::BIA_FILE_MANAGER);
#endif
}

void BIA::BIAFileManager::ScanRootDirectory()
{
   for (const auto& obj : std::filesystem::directory_iterator(_rootPath))
   {
      if (obj.is_directory() && obj.path().filename() != "log")
         _rootDirectories.push_back(obj.path());
      _rootFiles.push_back(obj.path());
   }
}

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

bool BIA::BIAFileManager::ExistsAtPath(fs::path path)
{
   return fs::exists(path);
}

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

void BIA::BIAFileManager::ChangeFileLocation(fs::path& destDir, std::vector<fs::path> sourceFiles)
{
   for (auto& file : sourceFiles)
      ChangeFileLocation(destDir, file);
}

std::vector<fs::path>& BIA::BIAFileManager::GetRootDirectories()
{
   return _rootDirectories;
}

std::vector<fs::path>& BIA::BIAFileManager::GetRootFiles()
{
   return _rootFiles;
}
