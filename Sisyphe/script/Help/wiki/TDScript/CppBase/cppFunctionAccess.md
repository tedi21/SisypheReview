# CppFunctionAccess
Réprésente une classe d'accès pour les objets CppFunction. Cette classe est utilisée pour gérer l'entité CppFunction dans la base de données.

# Référence
## Constructeur CppFunctionAccess
*Paramètres*
* None.

*Description*
* Crée une instance de la classe CppFunctionAccess.
```
access = new CppFunctionAccess();
```

## Méthode GetAllCppFunctions
*Paramètres*
* None.

*Retour*
* Array[CppFunction] : Tous les objets CppFunction de la base de données.

*Description*
* Retourne toutes les objets CppFunction de la base de données.
```
objects = access.GetAllCppFunctions();
```

## Méthode GetManyCppFunctions
*Paramètres*
* String : clause WHERE de la recherche SQL.

*Retour*
* Array[CppFunction] : Les objets CppFunction de la base de données correspondant à la requête SQL.

*Description*
* Retourne les objets CppFunction de la base de données correspondant à la requête SQL.
```
objects = access.GetManyCppFunctions("name = " & value);
```

## Méthode GetOneCppFunction
*Paramètres*
* Numeric : L'identifiant identifier de la table cppFunction.

*Retour*
* CppFunction : L'objet CppFunction de la base de données correspondant à l'identifiant.

*Description*
* Retourne l'objet CppFunction de la base de données correspondant à l'identifiant.
```
object = access.GetOneCppFunction(identifier);
```

## Méthode SelectOneCppFunction
*Paramètres*
* Numeric : L'identifiant identifier de la table cppFunction.
* Bool : non utilisé.

*Retour*
* CppFunction : L'objet CppFunction de la base de données correspondant à l'identifiant, verrouillé pour modification.

*Description*
* Verrouille l'objet CppFunction de la base de données correspondant à l'identifiant.
```
object = access.SelectOneCppFunction(identifier, false);
```

## Méthode SelectManyCppFunctions
*Paramètres*
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* Array[CppFunction] : Les objets CppFunction de la base de données correspondant à la requête SQL, verrouillés pour modification.

*Description*
* Verrouille les objets CppFunction de la base de données correspondant à la requête SQL.
```
objects = access.SelectManyCppFunctions("name = " & value, false);
```

## Méthode CancelSelection
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Déverrouille les objets et annule les modifications.
```
access.CancelSelection();
```

## Méthode IsSelectedCppFunction
*Paramètres*
* CppFunction : L'objet à tester.

*Retour*
* Bool : True, si l'objet est verrouillé, False sinon.

*Description*
* Retourne True, si l'objet est verrouillé, False sinon.
```
var = access.IsSelectedCppFunction(cppFunction);
```

## Méthode FillCppDeclarationFile
*Paramètres*
* CppFunction : L'objet à remplir.

*Retour*
* None.

*Description*
* Recupère la donnée cppDeclarationFile dans la base de données.
```
access.FillCppDeclarationFile(cppFunction);
```

## Méthode FillCppDefinitionFile
*Paramètres*
* CppFunction : L'objet à remplir.

*Retour*
* None.

*Description*
* Recupère la donnée cppDefinitionFile dans la base de données.
```
access.FillCppDefinitionFile(cppFunction);
```

## Méthode FillCppClass
*Paramètres*
* CppFunction : L'objet à remplir.

*Retour*
* None.

*Description*
* Recupère la donnée cppClass dans la base de données.
```
access.FillCppClass(cppFunction);
```

## Méthode FillAllCppParameters
*Paramètres*
* CppFunction : L'objet à remplir.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppParameter dans la base de données.
```
access.FillAllCppParameters(cppFunction, false);
```

## Méthode FillAllCppVariables
*Paramètres*
* CppFunction : L'objet à remplir.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppVariable dans la base de données.
```
access.FillAllCppVariables(cppFunction, false);
```

## Méthode FillAllDebugFunctionInfos
*Paramètres*
* CppFunction : L'objet à remplir.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données DebugFunctionInfo dans la base de données.
```
access.FillAllDebugFunctionInfos(cppFunction, false);
```

## Méthode FillOneCppParameter
*Paramètres*
* CppFunction : L'objet à remplir.
* Numeric : L'identifiant identifier de la table cppParameter.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère la donnée CppParameter dans la base de données.
```
access.FillOneCppParameter(cppFunction, identifier, false);
```

## Méthode FillOneCppVariable
*Paramètres*
* CppFunction : L'objet à remplir.
* Numeric : L'identifiant identifier de la table cppVariable.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère la donnée CppVariable dans la base de données.
```
access.FillOneCppVariable(cppFunction, identifier, false);
```

## Méthode FillOneDebugFunctionInfo
*Paramètres*
* CppFunction : L'objet à remplir.
* Numeric : L'identifiant identifier de la table debugFunctionInfo.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère la donnée DebugFunctionInfo dans la base de données.
```
access.FillOneDebugFunctionInfo(cppFunction, identifier, false);
```

## Méthode FillManyCppParameters
*Paramètres*
* CppFunction : L'objet à remplir.
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppParameter dans la base de données.
```
access.FillManyCppParameters(cppFunction, "identifier = " & value, false);
```

## Méthode FillManyCppVariables
*Paramètres*
* CppFunction : L'objet à remplir.
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppVariable dans la base de données.
```
access.FillManyCppVariables(cppFunction, "identifier = " & value, false);
```

## Méthode FillManyDebugFunctionInfos
*Paramètres*
* CppFunction : L'objet à remplir.
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données DebugFunctionInfo dans la base de données.
```
access.FillManyDebugFunctionInfos(cppFunction, "identifier = " & value, false);
```

## Méthode IsModifiedCppFunction
*Paramètres*
* CppFunction : L'objet à tester.

*Retour*
* Bool : True si l'objet est modifié, False sinon.

*Description*
* Retourne True si l'objet est modifié, False sinon.
```
var = access.IsModifiedCppFunction(cppFunction);
```

## Méthode UpdateCppFunction
*Paramètres*
* CppFunction : L'objet à mettre à jour dans la base de données.

*Retour*
* None.

*Description*
* Met à jour la donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.UpdateCppFunction(cppFunction);
```

## Méthode InsertCppFunction
*Paramètres*
* CppFunction : L'objet à ajouter dans la base de données.

*Retour*
* None.

*Description*
* Ajoute une donnée dans la base de données.
```
var = access.InsertCppFunction(cppFunction);
```

## Méthode DeleteCppFunction
*Paramètres*
* CppFunction : L'objet à supprimer dans la base de données.

*Retour*
* None.

*Description*
* Supprime une donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.DeleteCppFunction(cppFunction);
```

## Méthode GetError
*Paramètres*
* String : Le texte de l'erreur.

*Retour*
* Bool : True si une erreur est survenue, False sinon.

*Description*
* Retourne l'erreur remontée par la base de données.
```
var = access.GetError(textError);
```
