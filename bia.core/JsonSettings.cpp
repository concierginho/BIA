#include "pch.h"
#include "JsonSettings.h"

nlohmann::json BIA::JsonSettings::DefaultRecipeJson =
R"({
   "threshold" : 200,
   "operations" : {
      "LABELING" : ""
   }
})"_json;

nlohmann::json BIA::JsonSettings::DefaultResultsJson =
R"({
   "results" : ""
})"_json;

/// <summary>
/// 
/// </summary>
/// <returns></returns>
nlohmann::json BIA::JsonSettings::GetDefaultRecipeJson()
{
   return DefaultRecipeJson;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
nlohmann::json BIA::JsonSettings::GetDefaultResultsJson()
{
   return DefaultResultsJson;
}
