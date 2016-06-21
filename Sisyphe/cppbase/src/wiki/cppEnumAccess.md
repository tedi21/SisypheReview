# CppEnumAccess
Réprésente une classe d'accès pour les objets CppEnum. Cette classe est utilisée pour gérer l'entité CppEnum dans la base de données.

# Référence
## Constructeur CppEnumAccess
*Paramètres*
* None.

*Description*
* Crée une instance de la classe CppEnumAccess.
```
access = new CppEnumAccess();
```

## Méthode GetAllCppEnums
*Paramètres*
* None.

*Retour*
* Array[CppEnum] : Tous les objets CppEnum de la base de données.

*Description*
* Retourne toutes les objets CppEnum de la base de données.
```
objects = access.GetAllCppEnums();
```

## Méthode GetManyCppEnums
*Paramètres*
* String : clause WHERE de la recherche SQL.

*Retour*
* Array[CppEnum] : Les objets CppEnum de la base de données correspondant à la requête SQL.

*Description*
* Retourne les objets CppEnum de la base de données correspondant à la requête SQL.
```
objects = access.GetManyCppEnums("name = " & value);
```

## Méthode GetOneCppEnum
*Paramètres*
* Numeric : L'identifiant identifier de la table cppEnum.

*Retour*
* CppEnum : L'objet CppEnum de la base de données correspondant à l'identifiant.

*Description*
* Retourne l'objet CppEnum de la base de données correspondant à l'identifiant.
```
object = access.GetOneCppEnum(identifier);
```

## Méthode SelectOneCppEnum
*Paramètres*
* Numeric : L'identifiant identifier de la table cppEnum.
* Bool : non utilisé.

*Retour*
* CppEnum : L'objet CppEnum de la base de données correspondant à l'identifiant, verrouillé pour modification.

*Description*
* Verrouille l'objet CppEnum de la base de données correspondant à l'identifiant.
```
object = access.SelectOneCppEnum(identifier, false);
```

## Méthode SelectManyCppEnums
*Paramètres*
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* Array[CppEnum] : Les objets CppEnum de la base de données correspondant à la requête SQL, verrouillés pour modification.

*Description*
* Verrouille les objets CppEnum de la base de données correspondant à la requête SQL.
```
objects = access.SelectManyCppEnums("name = " & value, false);
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

## Méthode IsSelectedCppEnum
*Paramètres*
* CppEnum : L'objet à tester.

*Retour*
* Bool : True, si l'objet est verrouillé, False sinon.

*Description*
* Retourne True, si l'objet est verrouillé, False sinon.
```
var = access.IsSelectedCppEnum(cppEnum);
```

## Méthode FillCppFile
*Paramètres*
* CppEnum : L'objet à remplir.

*Retour*
* None.

*Description*
* Recupère la donnée cppFile dans la base de données.
```
access.FillCppFile(cppEnum);
```

## Méthode FillAllCppEnumConstants
*Paramètres*
* CppEnum : L'objet à remplir.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppEnumConstant dans la base de données.
```
access.FillAllCppEnumConstants(cppEnum, false);
```

## Méthode FillOneCppEnumConstant
*Paramètres*
* CppEnum : L'objet à remplir.
* Numeric : L'identifiant identifier de la table cppEnumConstant.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère la donnée CppEnumConstant dans la base de données.
```
access.FillOneCppEnumConstant(cppEnum, identifier, false);
```

## Méthode FillManyCppEnumConstants
*Paramètres*
* CppEnum : L'objet à remplir.
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppEnumConstant dans la base de données.
```
access.FillManyCppEnumConstants(cppEnum, "identifier = " & value, false);
```

## Méthode IsModifiedCppEnum
*Paramètres*
* CppEnum : L'objet à tester.

*Retour*
* Bool : True si l'objet est modifié, False sinon.

*Description*
* Retourne True si l'objet est modifié, False sinon.
```
var = access.IsModifiedCppEnum(cppEnum);
```

## Méthode UpdateCppEnum
*Paramètres*
* CppEnum : L'objet à mettre à jour dans la base de données.

*Retour*
* None.

*Description*
* Met à jour la donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.UpdateCppEnum(cppEnum);
```

## Méthode InsertCppEnum
*Paramètres*
* CppEnum : L'objet à ajouter dans la base de données.

*Retour*
* None.

*Description*
* Ajoute une donnée dans la base de données.
```
var = access.InsertCppEnum(cppEnum);
```

## Méthode DeleteCppEnum
*Paramètres*
* CppEnum : L'objet à supprimer dans la base de données.

*Retour*
* None.

*Description*
* Supprime une donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.DeleteCppEnum(cppEnum);
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
