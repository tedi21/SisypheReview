# CppParameterAccess
Réprésente une classe d'accès pour les objets CppParameter. Cette classe est utilisée pour gérer l'entité CppParameter dans la base de données.

# Référence
## Constructeur CppParameterAccess
*Paramètres*
* None.

*Description*
* Crée une instance de la classe CppParameterAccess.
```
access = new CppParameterAccess();
```

## Méthode GetAllCppParameters
*Paramètres*
* None.

*Retour*
* Array[CppParameter] : Tous les objets CppParameter de la base de données.

*Description*
* Retourne toutes les objets CppParameter de la base de données.
```
objects = access.GetAllCppParameters();
```

## Méthode GetManyCppParameters
*Paramètres*
* String : clause WHERE de la recherche SQL.

*Retour*
* Array[CppParameter] : Les objets CppParameter de la base de données correspondant à la requête SQL.

*Description*
* Retourne les objets CppParameter de la base de données correspondant à la requête SQL.
```
objects = access.GetManyCppParameters("paramOrder = " & value);
```

## Méthode GetOneCppParameter
*Paramètres*
* Numeric : L'identifiant identifier de la table cppParameter.

*Retour*
* CppParameter : L'objet CppParameter de la base de données correspondant à l'identifiant.

*Description*
* Retourne l'objet CppParameter de la base de données correspondant à l'identifiant.
```
object = access.GetOneCppParameter(identifier);
```

## Méthode SelectOneCppParameter
*Paramètres*
* Numeric : L'identifiant identifier de la table cppParameter.
* Bool : non utilisé.

*Retour*
* CppParameter : L'objet CppParameter de la base de données correspondant à l'identifiant, verrouillé pour modification.

*Description*
* Verrouille l'objet CppParameter de la base de données correspondant à l'identifiant.
```
object = access.SelectOneCppParameter(identifier, false);
```

## Méthode SelectManyCppParameters
*Paramètres*
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* Array[CppParameter] : Les objets CppParameter de la base de données correspondant à la requête SQL, verrouillés pour modification.

*Description*
* Verrouille les objets CppParameter de la base de données correspondant à la requête SQL.
```
objects = access.SelectManyCppParameters("paramOrder = " & value, false);
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

## Méthode IsSelectedCppParameter
*Paramètres*
* CppParameter : L'objet à tester.

*Retour*
* Bool : True, si l'objet est verrouillé, False sinon.

*Description*
* Retourne True, si l'objet est verrouillé, False sinon.
```
var = access.IsSelectedCppParameter(cppParameter);
```

## Méthode FillCppFunction
*Paramètres*
* CppParameter : L'objet à remplir.

*Retour*
* None.

*Description*
* Recupère la donnée cppFunction dans la base de données.
```
access.FillCppFunction(cppParameter);
```

## Méthode IsModifiedCppParameter
*Paramètres*
* CppParameter : L'objet à tester.

*Retour*
* Bool : True si l'objet est modifié, False sinon.

*Description*
* Retourne True si l'objet est modifié, False sinon.
```
var = access.IsModifiedCppParameter(cppParameter);
```

## Méthode UpdateCppParameter
*Paramètres*
* CppParameter : L'objet à mettre à jour dans la base de données.

*Retour*
* None.

*Description*
* Met à jour la donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.UpdateCppParameter(cppParameter);
```

## Méthode InsertCppParameter
*Paramètres*
* CppParameter : L'objet à ajouter dans la base de données.

*Retour*
* None.

*Description*
* Ajoute une donnée dans la base de données.
```
var = access.InsertCppParameter(cppParameter);
```

## Méthode DeleteCppParameter
*Paramètres*
* CppParameter : L'objet à supprimer dans la base de données.

*Retour*
* None.

*Description*
* Supprime une donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.DeleteCppParameter(cppParameter);
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
