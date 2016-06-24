# CMacroAccess
Réprésente une classe d'accès pour les objets CMacro. Cette classe est utilisée pour gérer l'entité CMacro dans la base de données.

# Référence
## Constructeur CMacroAccess
*Paramètres*
* None.

*Description*
* Crée une instance de la classe CMacroAccess.
```
access = new CMacroAccess();
```

## Méthode GetAllCMacros
*Paramètres*
* None.

*Retour*
* Array[CMacro] : Tous les objets CMacro de la base de données.

*Description*
* Retourne toutes les objets CMacro de la base de données.
```
objects = access.GetAllCMacros();
```

## Méthode GetManyCMacros
*Paramètres*
* String : clause WHERE de la recherche SQL.

*Retour*
* Array[CMacro] : Les objets CMacro de la base de données correspondant à la requête SQL.

*Description*
* Retourne les objets CMacro de la base de données correspondant à la requête SQL.
```
objects = access.GetManyCMacros("name = " & value);
```

## Méthode GetOneCMacro
*Paramètres*
* Numeric : L'identifiant identifier de la table cMacro.

*Retour*
* CMacro : L'objet CMacro de la base de données correspondant à l'identifiant.

*Description*
* Retourne l'objet CMacro de la base de données correspondant à l'identifiant.
```
object = access.GetOneCMacro(identifier);
```

## Méthode SelectOneCMacro
*Paramètres*
* Numeric : L'identifiant identifier de la table cMacro.
* Bool : non utilisé.

*Retour*
* CMacro : L'objet CMacro de la base de données correspondant à l'identifiant, verrouillé pour modification.

*Description*
* Verrouille l'objet CMacro de la base de données correspondant à l'identifiant.
```
object = access.SelectOneCMacro(identifier, false);
```

## Méthode SelectManyCMacros
*Paramètres*
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* Array[CMacro] : Les objets CMacro de la base de données correspondant à la requête SQL, verrouillés pour modification.

*Description*
* Verrouille les objets CMacro de la base de données correspondant à la requête SQL.
```
objects = access.SelectManyCMacros("name = " & value, false);
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

## Méthode IsSelectedCMacro
*Paramètres*
* CMacro : L'objet à tester.

*Retour*
* Bool : True, si l'objet est verrouillé, False sinon.

*Description*
* Retourne True, si l'objet est verrouillé, False sinon.
```
var = access.IsSelectedCMacro(cMacro);
```

## Méthode FillCppFile
*Paramètres*
* CMacro : L'objet à remplir.

*Retour*
* None.

*Description*
* Recupère la donnée cppFile dans la base de données.
```
access.FillCppFile(cMacro);
```

## Méthode IsModifiedCMacro
*Paramètres*
* CMacro : L'objet à tester.

*Retour*
* Bool : True si l'objet est modifié, False sinon.

*Description*
* Retourne True si l'objet est modifié, False sinon.
```
var = access.IsModifiedCMacro(cMacro);
```

## Méthode UpdateCMacro
*Paramètres*
* CMacro : L'objet à mettre à jour dans la base de données.

*Retour*
* None.

*Description*
* Met à jour la donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.UpdateCMacro(cMacro);
```

## Méthode InsertCMacro
*Paramètres*
* CMacro : L'objet à ajouter dans la base de données.

*Retour*
* None.

*Description*
* Ajoute une donnée dans la base de données.
```
var = access.InsertCMacro(cMacro);
```

## Méthode DeleteCMacro
*Paramètres*
* CMacro : L'objet à supprimer dans la base de données.

*Retour*
* None.

*Description*
* Supprime une donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.DeleteCMacro(cMacro);
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
