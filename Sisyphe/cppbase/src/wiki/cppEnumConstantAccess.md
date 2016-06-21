# CppEnumConstantAccess
Réprésente une classe d'accès pour les objets CppEnumConstant. Cette classe est utilisée pour gérer l'entité CppEnumConstant dans la base de données.

# Référence
## Constructeur CppEnumConstantAccess
*Paramètres*
* None.

*Description*
* Crée une instance de la classe CppEnumConstantAccess.
```
access = new CppEnumConstantAccess();
```

## Méthode GetAllCppEnumConstants
*Paramètres*
* None.

*Retour*
* Array[CppEnumConstant] : Tous les objets CppEnumConstant de la base de données.

*Description*
* Retourne toutes les objets CppEnumConstant de la base de données.
```
objects = access.GetAllCppEnumConstants();
```

## Méthode GetManyCppEnumConstants
*Paramètres*
* String : clause WHERE de la recherche SQL.

*Retour*
* Array[CppEnumConstant] : Les objets CppEnumConstant de la base de données correspondant à la requête SQL.

*Description*
* Retourne les objets CppEnumConstant de la base de données correspondant à la requête SQL.
```
objects = access.GetManyCppEnumConstants("name = " & value);
```

## Méthode GetOneCppEnumConstant
*Paramètres*
* Numeric : L'identifiant identifier de la table cppEnumConstant.

*Retour*
* CppEnumConstant : L'objet CppEnumConstant de la base de données correspondant à l'identifiant.

*Description*
* Retourne l'objet CppEnumConstant de la base de données correspondant à l'identifiant.
```
object = access.GetOneCppEnumConstant(identifier);
```

## Méthode SelectOneCppEnumConstant
*Paramètres*
* Numeric : L'identifiant identifier de la table cppEnumConstant.
* Bool : non utilisé.

*Retour*
* CppEnumConstant : L'objet CppEnumConstant de la base de données correspondant à l'identifiant, verrouillé pour modification.

*Description*
* Verrouille l'objet CppEnumConstant de la base de données correspondant à l'identifiant.
```
object = access.SelectOneCppEnumConstant(identifier, false);
```

## Méthode SelectManyCppEnumConstants
*Paramètres*
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* Array[CppEnumConstant] : Les objets CppEnumConstant de la base de données correspondant à la requête SQL, verrouillés pour modification.

*Description*
* Verrouille les objets CppEnumConstant de la base de données correspondant à la requête SQL.
```
objects = access.SelectManyCppEnumConstants("name = " & value, false);
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

## Méthode IsSelectedCppEnumConstant
*Paramètres*
* CppEnumConstant : L'objet à tester.

*Retour*
* Bool : True, si l'objet est verrouillé, False sinon.

*Description*
* Retourne True, si l'objet est verrouillé, False sinon.
```
var = access.IsSelectedCppEnumConstant(cppEnumConstant);
```

## Méthode FillCppEnum
*Paramètres*
* CppEnumConstant : L'objet à remplir.

*Retour*
* None.

*Description*
* Recupère la donnée cppEnum dans la base de données.
```
access.FillCppEnum(cppEnumConstant);
```

## Méthode IsModifiedCppEnumConstant
*Paramètres*
* CppEnumConstant : L'objet à tester.

*Retour*
* Bool : True si l'objet est modifié, False sinon.

*Description*
* Retourne True si l'objet est modifié, False sinon.
```
var = access.IsModifiedCppEnumConstant(cppEnumConstant);
```

## Méthode UpdateCppEnumConstant
*Paramètres*
* CppEnumConstant : L'objet à mettre à jour dans la base de données.

*Retour*
* None.

*Description*
* Met à jour la donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.UpdateCppEnumConstant(cppEnumConstant);
```

## Méthode InsertCppEnumConstant
*Paramètres*
* CppEnumConstant : L'objet à ajouter dans la base de données.

*Retour*
* None.

*Description*
* Ajoute une donnée dans la base de données.
```
var = access.InsertCppEnumConstant(cppEnumConstant);
```

## Méthode DeleteCppEnumConstant
*Paramètres*
* CppEnumConstant : L'objet à supprimer dans la base de données.

*Retour*
* None.

*Description*
* Supprime une donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.DeleteCppEnumConstant(cppEnumConstant);
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
