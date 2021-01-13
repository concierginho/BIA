#pragma once

namespace BIA::File
{
   class FileManager;
}

namespace BIA::Experiment
{
   class ExperimentManager;
}

namespace BIA::Image
{
   class ImageManager;
}

#ifdef _LOGGING_
namespace BIA::Logging
{
   class ILogger;
}
#endif

namespace BIA::Management
{
   class Manager
   {
   public:
      File::FileManager* FileManager = nullptr;
      Experiment::ExperimentManager* ExperimentManager = nullptr;
      Image::ImageManager* ImageManager = nullptr;
#ifdef _LOGGING_
      Logging::ILogger* Logger = nullptr;
#endif

      Manager();
      ~Manager();
   };
}