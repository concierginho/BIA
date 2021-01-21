#include "pch.h"
#include "Experiment.h"

#include <sstream>

int BIA::Experiment::nextId = 0;

void BIA::Experiment::IninitalizeTIFFImage(EFolder folder, fs::path path)
{
   switch (folder)
   {
      case EFolder::HORIZONTAL:
         _horTIFFImg = new TIFFImage(path);
         break;
      case EFolder::VERTICAL:
      default:
         _vertTIFFImg = new TIFFImage(path);
         break;
   }
}

fs::path BIA::Experiment::GetTIFFImagePath(EFolder folder)
{
   switch (folder)
   {
      case EFolder::HORIZONTAL:
         return _horTIFFImg->GetPath();
         break;
      case EFolder::VERTICAL:
      default:
         return _vertTIFFImg->GetPath();
         break;
   }
}

BIA::TIFFImage* BIA::Experiment::GetTIFFImage(EFolder folder)
{
   switch (folder)
   {
      case EFolder::HORIZONTAL:
         return _horTIFFImg;
         break;
      case EFolder::VERTICAL:
      default:
         return _vertTIFFImg;
         break;
   }

}

int BIA::Experiment::GetNextId()
{
   int i = nextId;
   nextId++;
   return i;
}

BIA::Experiment::Experiment(fs::path path)
{
   _path = path;
   _name = path.filename().string();
   _id = GetNextId();
}

BIA::Experiment::~Experiment()
{
}

fs::path BIA::Experiment::GetPath()
{
   return _path;
}

fs::path BIA::Experiment::GetPath(EFolder alignment)
{
   fs::path parent = GetPath();

   std::stringstream ss;

   ss << parent.string() << "\\";

   switch (alignment)
   {
      case EFolder::HORIZONTAL:
         ss << "horizontal";
         break;
      case EFolder::VERTICAL:
      default:
         ss << "vertical";
         break;
   }

   return fs::path(ss.str());
}

fs::path BIA::Experiment::GetPartExperimentPathById(EFolder folder, int id)
{
   auto path = GetPath(folder);
   std::stringstream ss;

   ss << path.string() << "\\" << id;

   return fs::path(ss.str());
}

std::string BIA::Experiment::GetName() const
{
   return _name;
}

std::vector<BIA::PartExperiment>& BIA::Experiment::GetPartExperiments(EFolder alignment)
{
   switch (alignment)
   {
      case EFolder::HORIZONTAL:
         return _partExperimentsByAlignment[EFolder::HORIZONTAL];
         break;
      case EFolder::VERTICAL:
      default:
         return _partExperimentsByAlignment[EFolder::VERTICAL];
         break;
   }
}
