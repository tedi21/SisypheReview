# CppAttributeAccess
Réprésente une classe d'accès pour les objets CppAttribute. Cette classe est utilisée pour gérer l'entité CppAttribute dans la base de données.

# Référence
## Constructeur CppAttributeAccess
*Paramètres*
* None.

*Description*
* Crée une instance de la classe CppAttributeAccess.
```
access = new CppAttributeAccess();
```

## Méthode GetAllCppAttributes
*Paramètres*
* None.

*Retour*
* Array[CppAttribute] : Tous les objets CppAttribute de la base de données.

*Description*
* Retourne toutes les objets CppAttribute de la base de données.
```
objects = access.GetAllCppAttributes();
```

## Méthode GetManyCppAttributes
*Paramètres*
* String : clause WHERE de la recherche SQL.

*Retour*
* Array[CppAttribute] : Les objets CppAttribute de la base de données correspondant à la requête SQL.

*Description*
* Retourne les objets CppAttribute de la base de données correspondant à la requête SQL.
```
objects = access.GetManyCppAttributes("attrType = " & value);
```

## Méthode GetOneCppAttribute
*Paramètres*
* Numeric : L'identifiant identifier de la table cppAttribute.

*Retour*
* CppAttribute : L'objet CppAttribute de la base de données correspondant à l'identifiant.

*Description*
* Retourne l'objet CppAttribute de la base de données correspondant à l'identifiant.
```
object = access.GetOneCppAttribute(identifier);
```

## Méthode SelectOneCppAttribute
*Paramètres*
* Numeric : L'identifiant identifier de la table cppAttribute.
* Bool : non utilisé.

*Retour*
* CppAttribute : L'objet CppAttribute de la base de données correspondant à l'identifiant, verrouillé pour modification.

*Description*
* Verrouille l'objet CppAttribute de la base de données correspondant à l'identifiant.
```
object = access.SelectOneCppAttribute(identifier, false);
```

## Méthode SelectManyCppAttributes
*Paramètres*
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* Array[CppAttribute] : Les objets CppAttribute de la base de données correspondant à la requête SQL, verrouillés pour modification.

*Description*
* Verrouille les objets CppAttribute de la base de données correspondant à la requête SQL.
```
objects = access.SelectManyCppAttributes("attrType = " & value, false);
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

## Méthode IsSelectedCppAttribute
*Paramètres*
* CppAttribute : L'objet à tester.

*Retour*
* Bool : True, si l'objet est verrouillé, False sinon.

*Description*
* Retourne True, si l'objet est verrouillé, False sinon.
```
var = access.IsSelectedCppAttribute(cppAttribute);
```

## Méthode FillCppClass
*Paramètres*
* CppAttribute : L'objet à remplir.

*Retour*
* None.

*Description*
* Recupère la donnée cppClass dans la base de données.
```
access.FillCppClass(cppAttribute);
```

## Méthode IsModifiedCppAttribute
*Paramètres*
* CppAttribute : L'objet à tester.

*Retour*
* Bool : True si l'objet est modifié, False sinon.

*Description*
* Retourne True si l'objet est modifié, False sinon.
```
var = access.IsModifiedCppAttribute(cppAttribute);
```

## Méthode UpdateCppAttribute
*Paramètres*
* CppAttribute : L'objet à mettre à jour dans la base de données.

*Retour*
* None.

*Description*
* Met à jour la donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.UpdateCppAttribute(cppAttribute);
```

## Méthode InsertCppAttribute
*Paramètres*
* CppAttribute : L'objet à ajouter dans la base de données.

*Retour*
* None.

*Description*
* Ajoute une donnée dans la base de données.
```
var = access.InsertCppAttribute(cppAttribute);
```

## Méthode DeleteCppAttribute
*Paramètres*
* CppAttribute : L'objet à supprimer dans la base de données.

*Retour*
* None.

*Description*
* Supprime une donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.DeleteCppAttribute(cppAttribute);
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
