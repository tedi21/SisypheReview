# CppInheritanceAccess
Réprésente une classe d'accès pour les objets CppInheritance. Cette classe est utilisée pour gérer l'entité CppInheritance dans la base de données.

# Référence
## Constructeur CppInheritanceAccess
*Paramètres*
* None.

*Description*
* Crée une instance de la classe CppInheritanceAccess.
```
access = new CppInheritanceAccess();
```

## Méthode GetAllCppInheritances
*Paramètres*
* None.

*Retour*
* Array[CppInheritance] : Tous les objets CppInheritance de la base de données.

*Description*
* Retourne toutes les objets CppInheritance de la base de données.
```
objects = access.GetAllCppInheritances();
```

## Méthode GetManyCppInheritances
*Paramètres*
* String : clause WHERE de la recherche SQL.

*Retour*
* Array[CppInheritance] : Les objets CppInheritance de la base de données correspondant à la requête SQL.

*Description*
* Retourne les objets CppInheritance de la base de données correspondant à la requête SQL.
```
objects = access.GetManyCppInheritances("baseClassName = " & value);
```

## Méthode GetOneCppInheritance
*Paramètres*
* Numeric : L'identifiant identifier de la table cppInheritance.

*Retour*
* CppInheritance : L'objet CppInheritance de la base de données correspondant à l'identifiant.

*Description*
* Retourne l'objet CppInheritance de la base de données correspondant à l'identifiant.
```
object = access.GetOneCppInheritance(identifier);
```

## Méthode SelectOneCppInheritance
*Paramètres*
* Numeric : L'identifiant identifier de la table cppInheritance.
* Bool : non utilisé.

*Retour*
* CppInheritance : L'objet CppInheritance de la base de données correspondant à l'identifiant, verrouillé pour modification.

*Description*
* Verrouille l'objet CppInheritance de la base de données correspondant à l'identifiant.
```
object = access.SelectOneCppInheritance(identifier, false);
```

## Méthode SelectManyCppInheritances
*Paramètres*
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* Array[CppInheritance] : Les objets CppInheritance de la base de données correspondant à la requête SQL, verrouillés pour modification.

*Description*
* Verrouille les objets CppInheritance de la base de données correspondant à la requête SQL.
```
objects = access.SelectManyCppInheritances("baseClassName = " & value, false);
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

## Méthode IsSelectedCppInheritance
*Paramètres*
* CppInheritance : L'objet à tester.

*Retour*
* Bool : True, si l'objet est verrouillé, False sinon.

*Description*
* Retourne True, si l'objet est verrouillé, False sinon.
```
var = access.IsSelectedCppInheritance(cppInheritance);
```

## Méthode FillDerived
*Paramètres*
* CppInheritance : L'objet à remplir.

*Retour*
* None.

*Description*
* Recupère la donnée derived dans la base de données.
```
access.FillDerived(cppInheritance);
```

## Méthode IsModifiedCppInheritance
*Paramètres*
* CppInheritance : L'objet à tester.

*Retour*
* Bool : True si l'objet est modifié, False sinon.

*Description*
* Retourne True si l'objet est modifié, False sinon.
```
var = access.IsModifiedCppInheritance(cppInheritance);
```

## Méthode UpdateCppInheritance
*Paramètres*
* CppInheritance : L'objet à mettre à jour dans la base de données.

*Retour*
* None.

*Description*
* Met à jour la donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.UpdateCppInheritance(cppInheritance);
```

## Méthode InsertCppInheritance
*Paramètres*
* CppInheritance : L'objet à ajouter dans la base de données.

*Retour*
* None.

*Description*
* Ajoute une donnée dans la base de données.
```
var = access.InsertCppInheritance(cppInheritance);
```

## Méthode DeleteCppInheritance
*Paramètres*
* CppInheritance : L'objet à supprimer dans la base de données.

*Retour*
* None.

*Description*
* Supprime une donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.DeleteCppInheritance(cppInheritance);
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
