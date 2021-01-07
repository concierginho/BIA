#pragma once

#include "File/FileManager.h"
#include "Experiment/ExperimentManager.h"
#include "Image/ImageManager.h"
#include "../Logging/ILogger.h"

namespace BIA
{
   namespace Management
   {
      class Manager
      {
      public:
         File::FileManager* FileManager;
         Experiment::ExperimentManager* ExperimentManager;
         Image::ImageManager* ImageManager;
         Logging::ILogger* Logger;

         Manager();
         ~Manager();
      };
   }
}