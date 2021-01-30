#ifndef _JSON_SETTINGS_
#define _JSON_SETTINGS_

#include <nlohmann/json.hpp>

namespace BIA
{
   class JsonSettings
   {
   private:
      static nlohmann::json DefaultRecipeJson;
      static nlohmann::json DefaultInfoJson;
      static nlohmann::json DefaultResultsJson;
   public:
      static nlohmann::json GetDefaultRecipeJson();
      static nlohmann::json GetDefaultInfoJson();
      static nlohmann::json GetDefaultResultsJson();
   };
}

#endif
