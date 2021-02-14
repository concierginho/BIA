#include "pch.h"
#include "JsonSettings.h"

/// <summary>
/// Cel: Ustawienia domyslne dla pliku 'recipe.json'
/// </summary>
nlohmann::json BIA::JsonSettings::DefaultRecipeJson =
R"({
   "THRESHOLD" : 200,
   "OPERATIONS" : [
   {
      "OPERATION" : {
         "NAME" : "LABELING",
            "ARGS" : "VONNEUMANN"
      }
   }
   ]
})"_json;

/// <summary>
/// Cel: Ustawienia domyslne dla pliku 'results.json'
/// </summary>
nlohmann::json BIA::JsonSettings::DefaultResultsJson =
R"({
   "RESULTS" : ""
})"_json;

/// <summary>
/// Cel: Zwrocenie domyslnych wartosci, ktore trafia do pliku 'recipe.json'.
/// </summary>
/// <returns></returns>
nlohmann::json BIA::JsonSettings::GetDefaultRecipeJson()
{
   return DefaultRecipeJson;
}

/// <summary>
/// Cel: Zwrocenie domyslnych wartosci, ktore trafia do pliku 'results.json'.
/// </summary>
/// <returns></returns>
nlohmann::json BIA::JsonSettings::GetDefaultResultsJson()
{
   return DefaultResultsJson;
}
