#include "pch.h"
#include "JsonSettings.h"

/// <summary>
/// Cel: Ustawienia domyslne dla pliku 'recipe.json'
/// </summary>
nlohmann::json BIA::JsonSettings::DefaultRecipeJson =
R"({
   "threshold" : 200,
   "operations" : {
      "LABELING" : ""
   }
})"_json;

/// <summary>
/// Cel: Ustawienia domyslne dla pliku 'results.json'
/// </summary>
nlohmann::json BIA::JsonSettings::DefaultResultsJson =
R"({
   "results" : ""
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
