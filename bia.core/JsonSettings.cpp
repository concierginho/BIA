#include "pch.h"
#include "JsonSettings.h"

nlohmann::json BIA::JsonSettings::DefaultRecipeJson =
R"({
   "threshold" : 200,
   "operations" : 
   {
   }
})"_json;

nlohmann::json BIA::JsonSettings::DefaultResultsJson
{
};

nlohmann::json BIA::JsonSettings::DefaultInfoJson
{
};

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
nlohmann::json BIA::JsonSettings::GetDefaultInfoJson()
{
   return DefaultInfoJson;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
nlohmann::json BIA::JsonSettings::GetDefaultResultsJson()
{
   return DefaultResultsJson;
}
