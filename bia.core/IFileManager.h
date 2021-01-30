#ifndef _IFILE_MANAGER_
#define _IFILE_MANAGER_

#include <filesystem>
#include <unordered_map>
#include <nlohmann/json.hpp>

#include "IManager.h"
#include "EFileType.h"

namespace fs = std::filesystem;

namespace BIA
{
   class IFileManager : public IManager
   {
   public:
      virtual ~IFileManager() = 0 {};
      
      virtual void Init() = 0;
      virtual void ScanRootDirectory() = 0;
      virtual void CreateAtPath(fs::path, EFileType) = 0;
      virtual void ChangeFileLocation(fs::path&, fs::path&) = 0;
      virtual void ChangeFileLocation(fs::path&, std::vector<fs::path>) = 0;
      virtual void WriteToJson(fs::path&, nlohmann::json&) = 0;
      virtual nlohmann::json ReadFromJson(fs::path&) = 0;
      virtual bool ExistsAtPath(fs::path) = 0;

      virtual std::unordered_map<EFileType, std::vector<fs::path>> GetDirectoryContent(fs::path) = 0;
   };
}

#endif
