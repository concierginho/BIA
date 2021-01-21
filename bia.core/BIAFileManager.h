#ifndef _BIA_FILE_MANAGER_
#define _BIA_FILE_MANAGER_

#include <unordered_map>
#include <regex>

#include "IFileManager.h"
#include "EPattern.h"
#include "EFileType.h"

#ifdef _LOGGING_
#include "BIALoggingManager.h"
#endif

namespace BIA
{
   class BIAFileManager : public IFileManager
   {
   private:
      std::vector<fs::path> _rootDirectories;
      std::vector<fs::path> _rootFiles;

      std::unordered_map<EPattern, std::regex> _patternByType;

#ifdef _LOGGING_
      std::shared_ptr<BIALoggingManager> _loggingManager;
#endif

      std::string _rootPath;

      void LoadPatterns();
   public:
      std::string GetRootPath() const;

      std::vector<fs::path>& GetRootDirectories();
      std::vector<fs::path>& GetRootFiles();

      BIAFileManager(std::string);
      ~BIAFileManager();

#ifdef _LOGGING_
      void SetLoggingManager(std::shared_ptr<BIALoggingManager>);
#endif

      std::regex GetPattern(EPattern);

      virtual void Init() override;
      virtual void ScanRootDirectory() override;
      virtual void CreateAtPath(fs::path, EFileType) override;
      virtual void ChangeFileLocation(fs::path&, fs::path&) override;
      virtual void ChangeFileLocation(fs::path&, std::vector<fs::path>) override;

      virtual bool ExistsAtPath(fs::path) override;

      virtual std::unordered_map<EFileType, std::vector<fs::path>> GetDirectoryContent(fs::path) override;
   };
}

#endif
