# CppFileAccess
Réprésente une classe d'accès pour les objets CppFile. Cette classe est utilisée pour gérer l'entité CppFile dans la base de données.

# Référence
## Constructeur CppFileAccess
*Paramètres*
* None.

*Description*
* Crée une instance de la classe CppFileAccess.
```
access = new CppFileAccess();
```

## Méthode GetAllCppFiles
*Paramètres*
* None.

*Retour*
* Array[CppFile] : Tous les objets CppFile de la base de données.

*Description*
* Retourne toutes les objets CppFile de la base de données.
```
objects = access.GetAllCppFiles();
```

## Méthode GetManyCppFiles
*Paramètres*
* String : clause WHERE de la recherche SQL.

*Retour*
* Array[CppFile] : Les objets CppFile de la base de données correspondant à la requête SQL.

*Description*
* Retourne les objets CppFile de la base de données correspondant à la requête SQL.
```
objects = access.GetManyCppFiles("path = " & value);
```

## Méthode GetOneCppFile
*Paramètres*
* Numeric : L'identifiant identifier de la table cppFile.

*Retour*
* CppFile : L'objet CppFile de la base de données correspondant à l'identifiant.

*Description*
* Retourne l'objet CppFile de la base de données correspondant à l'identifiant.
```
object = access.GetOneCppFile(identifier);
```

## Méthode SelectOneCppFile
*Paramètres*
* Numeric : L'identifiant identifier de la table cppFile.
* Bool : non utilisé.

*Retour*
* CppFile : L'objet CppFile de la base de données correspondant à l'identifiant, verrouillé pour modification.

*Description*
* Verrouille l'objet CppFile de la base de données correspondant à l'identifiant.
```
object = access.SelectOneCppFile(identifier, false);
```

## Méthode SelectManyCppFiles
*Paramètres*
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* Array[CppFile] : Les objets CppFile de la base de données correspondant à la requête SQL, verrouillés pour modification.

*Description*
* Verrouille les objets CppFile de la base de données correspondant à la requête SQL.
```
objects = access.SelectManyCppFiles("path = " & value, false);
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

## Méthode IsSelectedCppFile
*Paramètres*
* CppFile : L'objet à tester.

*Retour*
* Bool : True, si l'objet est verrouillé, False sinon.

*Description*
* Retourne True, si l'objet est verrouillé, False sinon.
```
var = access.IsSelectedCppFile(cppFile);
```

## Méthode FillTextFile
*Paramètres*
* CppFile : L'objet à remplir.

*Retour*
* None.

*Description*
* Recupère la donnée textFile dans la base de données.
```
access.FillTextFile(cppFile);
```

## Méthode FillCppFileType
*Paramètres*
* CppFile : L'objet à remplir.

*Retour*
* None.

*Description*
* Recupère la donnée cppFileType dans la base de données.
```
access.FillCppFileType(cppFile);
```

## Méthode FillAllCppDeclarationFunctions
*Paramètres*
* CppFile : L'objet à remplir.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppDeclarationFunction dans la base de données.
```
access.FillAllCppDeclarationFunctions(cppFile, false);
```

## Méthode FillAllCppDefinitionFunctions
*Paramètres*
* CppFile : L'objet à remplir.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppDefinitionFunction dans la base de données.
```
access.FillAllCppDefinitionFunctions(cppFile, false);
```

## Méthode FillAllCppClasss
*Paramètres*
* CppFile : L'objet à remplir.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppClass dans la base de données.
```
access.FillAllCppClasss(cppFile, false);
```

## Méthode FillAllCppIncludes
*Paramètres*
* CppFile : L'objet à remplir.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppInclude dans la base de données.
```
access.FillAllCppIncludes(cppFile, false);
```

## Méthode FillAllCppVariables
*Paramètres*
* CppFile : L'objet à remplir.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppVariable dans la base de données.
```
access.FillAllCppVariables(cppFile, false);
```

## Méthode FillAllCppEnums
*Paramètres*
* CppFile : L'objet à remplir.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppEnum dans la base de données.
```
access.FillAllCppEnums(cppFile, false);
```

## Méthode FillAllCMacros
*Paramètres*
* CppFile : L'objet à remplir.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CMacro dans la base de données.
```
access.FillAllCMacros(cppFile, false);
```

## Méthode FillAllCppNotices
*Paramètres*
* CppFile : L'objet à remplir.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppNotice dans la base de données.
```
access.FillAllCppNotices(cppFile, false);
```

## Méthode FillOneCppDeclarationFunction
*Paramètres*
* CppFile : L'objet à remplir.
* Numeric : L'identifiant identifier de la table cppFunction.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère la donnée CppDeclarationFunction dans la base de données.
```
access.FillOneCppDeclarationFunction(cppFile, identifier, false);
```

## Méthode FillOneCppDefinitionFunction
*Paramètres*
* CppFile : L'objet à remplir.
* Numeric : L'identifiant identifier de la table cppFunction.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère la donnée CppDefinitionFunction dans la base de données.
```
access.FillOneCppDefinitionFunction(cppFile, identifier, false);
```

## Méthode FillOneCppClass
*Paramètres*
* CppFile : L'objet à remplir.
* Numeric : L'identifiant identifier de la table cppClass.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère la donnée CppClass dans la base de données.
```
access.FillOneCppClass(cppFile, identifier, false);
```

## Méthode FillOneCppInclude
*Paramètres*
* CppFile : L'objet à remplir.
* Numeric : L'identifiant identifier de la table cppInclude.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère la donnée CppInclude dans la base de données.
```
access.FillOneCppInclude(cppFile, identifier, false);
```

## Méthode FillOneCppVariable
*Paramètres*
* CppFile : L'objet à remplir.
* Numeric : L'identifiant identifier de la table cppVariable.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère la donnée CppVariable dans la base de données.
```
access.FillOneCppVariable(cppFile, identifier, false);
```

## Méthode FillOneCppEnum
*Paramètres*
* CppFile : L'objet à remplir.
* Numeric : L'identifiant identifier de la table cppEnum.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère la donnée CppEnum dans la base de données.
```
access.FillOneCppEnum(cppFile, identifier, false);
```

## Méthode FillOneCMacro
*Paramètres*
* CppFile : L'objet à remplir.
* Numeric : L'identifiant identifier de la table cMacro.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère la donnée CMacro dans la base de données.
```
access.FillOneCMacro(cppFile, identifier, false);
```

## Méthode FillOneCppNotice
*Paramètres*
* CppFile : L'objet à remplir.
* Numeric : L'identifiant identifier de la table cppNotice.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère la donnée CppNotice dans la base de données.
```
access.FillOneCppNotice(cppFile, identifier, false);
```

## Méthode FillManyCppDeclarationFunctions
*Paramètres*
* CppFile : L'objet à remplir.
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppDeclarationFunction dans la base de données.
```
access.FillManyCppDeclarationFunctions(cppFile, "identifier = " & value, false);
```

## Méthode FillManyCppDefinitionFunctions
*Paramètres*
* CppFile : L'objet à remplir.
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppDefinitionFunction dans la base de données.
```
access.FillManyCppDefinitionFunctions(cppFile, "identifier = " & value, false);
```

## Méthode FillManyCppClasss
*Paramètres*
* CppFile : L'objet à remplir.
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppClass dans la base de données.
```
access.FillManyCppClasss(cppFile, "identifier = " & value, false);
```

## Méthode FillManyCppIncludes
*Paramètres*
* CppFile : L'objet à remplir.
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppInclude dans la base de données.
```
access.FillManyCppIncludes(cppFile, "identifier = " & value, false);
```

## Méthode FillManyCppVariables
*Paramètres*
* CppFile : L'objet à remplir.
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppVariable dans la base de données.
```
access.FillManyCppVariables(cppFile, "identifier = " & value, false);
```

## Méthode FillManyCppEnums
*Paramètres*
* CppFile : L'objet à remplir.
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppEnum dans la base de données.
```
access.FillManyCppEnums(cppFile, "identifier = " & value, false);
```

## Méthode FillManyCMacros
*Paramètres*
* CppFile : L'objet à remplir.
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CMacro dans la base de données.
```
access.FillManyCMacros(cppFile, "identifier = " & value, false);
```

## Méthode FillManyCppNotices
*Paramètres*
* CppFile : L'objet à remplir.
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppNotice dans la base de données.
```
access.FillManyCppNotices(cppFile, "identifier = " & value, false);
```

## Méthode IsModifiedCppFile
*Paramètres*
* CppFile : L'objet à tester.

*Retour*
* Bool : True si l'objet est modifié, False sinon.

*Description*
* Retourne True si l'objet est modifié, False sinon.
```
var = access.IsModifiedCppFile(cppFile);
```

## Méthode UpdateCppFile
*Paramètres*
* CppFile : L'objet à mettre à jour dans la base de données.

*Retour*
* None.

*Description*
* Met à jour la donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.UpdateCppFile(cppFile);
```

## Méthode InsertCppFile
*Paramètres*
* CppFile : L'objet à ajouter dans la base de données.

*Retour*
* None.

*Description*
* Ajoute une donnée dans la base de données.
```
var = access.InsertCppFile(cppFile);
```

## Méthode DeleteCppFile
*Paramètres*
* CppFile : L'objet à supprimer dans la base de données.

*Retour*
* None.

*Description*
* Supprime une donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.DeleteCppFile(cppFile);
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
