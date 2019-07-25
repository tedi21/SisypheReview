# CppNoticeAccess
Réprésente une classe d'accès pour les objets CppNotice. Cette classe est utilisée pour gérer l'entité CppNotice dans la base de données.

# Référence
## Constructeur CppNoticeAccess
*Paramètres*
* None.

*Description*
* Crée une instance de la classe CppNoticeAccess.
```
access = new CppNoticeAccess();
```

## Méthode GetAllCppNotices
*Paramètres*
* None.

*Retour*
* Array[CppNotice] : Tous les objets CppNotice de la base de données.

*Description*
* Retourne toutes les objets CppNotice de la base de données.
```
objects = access.GetAllCppNotices();
```

## Méthode GetManyCppNotices
*Paramètres*
* String : clause WHERE de la recherche SQL.

*Retour*
* Array[CppNotice] : Les objets CppNotice de la base de données correspondant à la requête SQL.

*Description*
* Retourne les objets CppNotice de la base de données correspondant à la requête SQL.
```
objects = access.GetManyCppNotices("description = " & value);
```

## Méthode GetOneCppNotice
*Paramètres*
* Numeric : L'identifiant identifier de la table cppNotice.

*Retour*
* CppNotice : L'objet CppNotice de la base de données correspondant à l'identifiant.

*Description*
* Retourne l'objet CppNotice de la base de données correspondant à l'identifiant.
```
object = access.GetOneCppNotice(identifier);
```

## Méthode SelectOneCppNotice
*Paramètres*
* Numeric : L'identifiant identifier de la table cppNotice.
* Bool : non utilisé.

*Retour*
* CppNotice : L'objet CppNotice de la base de données correspondant à l'identifiant, verrouillé pour modification.

*Description*
* Verrouille l'objet CppNotice de la base de données correspondant à l'identifiant.
```
object = access.SelectOneCppNotice(identifier, false);
```

## Méthode SelectManyCppNotices
*Paramètres*
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* Array[CppNotice] : Les objets CppNotice de la base de données correspondant à la requête SQL, verrouillés pour modification.

*Description*
* Verrouille les objets CppNotice de la base de données correspondant à la requête SQL.
```
objects = access.SelectManyCppNotices("description = " & value, false);
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

## Méthode IsSelectedCppNotice
*Paramètres*
* CppNotice : L'objet à tester.

*Retour*
* Bool : True, si l'objet est verrouillé, False sinon.

*Description*
* Retourne True, si l'objet est verrouillé, False sinon.
```
var = access.IsSelectedCppNotice(cppNotice);
```

## Méthode FillCppFile
*Paramètres*
* CppNotice : L'objet à remplir.

*Retour*
* None.

*Description*
* Recupère la donnée cppFile dans la base de données.
```
access.FillCppFile(cppNotice);
```

## Méthode IsModifiedCppNotice
*Paramètres*
* CppNotice : L'objet à tester.

*Retour*
* Bool : True si l'objet est modifié, False sinon.

*Description*
* Retourne True si l'objet est modifié, False sinon.
```
var = access.IsModifiedCppNotice(cppNotice);
```

## Méthode UpdateCppNotice
*Paramètres*
* CppNotice : L'objet à mettre à jour dans la base de données.

*Retour*
* None.

*Description*
* Met à jour la donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.UpdateCppNotice(cppNotice);
```

## Méthode InsertCppNotice
*Paramètres*
* CppNotice : L'objet à ajouter dans la base de données.

*Retour*
* None.

*Description*
* Ajoute une donnée dans la base de données.
```
var = access.InsertCppNotice(cppNotice);
```

## Méthode DeleteCppNotice
*Paramètres*
* CppNotice : L'objet à supprimer dans la base de données.

*Retour*
* None.

*Description*
* Supprime une donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.DeleteCppNotice(cppNotice);
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
