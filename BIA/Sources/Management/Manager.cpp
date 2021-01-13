#include "Manager.h"

#include "../File/FileManager.h"
#include "../Experiment/ExperimentManager.h"
#include "../Image/ImageManager.h"
#include "../Logging/ILogger.h"

namespace BIA
{
   namespace Management
   {
      Manager::Manager()
      {
         FileManager = nullptr;
         ExperimentManager = nullptr;
         ImageManager = nullptr;
         Logger = nullptr;
      }

      Manager::~Manager()
      {
         if (FileManager != nullptr)
            delete FileManager;

         if (ExperimentManager != nullptr)
            delete ExperimentManager;

         if (ImageManager != nullptr)
            delete ImageManager;

         if (Logger != nullptr)
            delete Logger;

         FileManager = nullptr;
         ExperimentManager = nullptr;
         ImageManager = nullptr;
         Logger = nullptr;
      }
   }
}