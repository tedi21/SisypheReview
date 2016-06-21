# TextFileAccess
Réprésente une classe d'accès pour les objets TextFile. Cette classe est utilisée pour gérer l'entité TextFile dans la base de données.

# Référence
## Constructeur TextFileAccess
*Paramètres*
* None.

*Description*
* Crée une instance de la classe TextFileAccess.
```
access = new TextFileAccess();
```

## Méthode GetAllTextFiles
*Paramètres*
* None.

*Retour*
* Array[TextFile] : Tous les objets TextFile de la base de données.

*Description*
* Retourne toutes les objets TextFile de la base de données.
```
objects = access.GetAllTextFiles();
```

## Méthode GetManyTextFiles
*Paramètres*
* String : clause WHERE de la recherche SQL.

*Retour*
* Array[TextFile] : Les objets TextFile de la base de données correspondant à la requête SQL.

*Description*
* Retourne les objets TextFile de la base de données correspondant à la requête SQL.
```
objects = access.GetManyTextFiles("content = " & value);
```

## Méthode GetOneTextFile
*Paramètres*
* Numeric : L'identifiant rowid de la table textFile.

*Retour*
* TextFile : L'objet TextFile de la base de données correspondant à l'identifiant.

*Description*
* Retourne l'objet TextFile de la base de données correspondant à l'identifiant.
```
object = access.GetOneTextFile(rowid);
```

## Méthode SelectOneTextFile
*Paramètres*
* Numeric : L'identifiant rowid de la table textFile.
* Bool : non utilisé.

*Retour*
* TextFile : L'objet TextFile de la base de données correspondant à l'identifiant, verrouillé pour modification.

*Description*
* Verrouille l'objet TextFile de la base de données correspondant à l'identifiant.
```
object = access.SelectOneTextFile(rowid, false);
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

## Méthode IsSelectedTextFile
*Paramètres*
* TextFile : L'objet à tester.

*Retour*
* Bool : True, si l'objet est verrouillé, False sinon.

*Description*
* Retourne True, si l'objet est verrouillé, False sinon.
```
var = access.IsSelectedTextFile(textFile);
```

## Méthode FillAllTextNotices
*Paramètres*
* TextFile : L'objet à remplir.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données TextNotice dans la base de données.
```
access.FillAllTextNotices(textFile, false);
```

## Méthode FillOneTextNotice
*Paramètres*
* TextFile : L'objet à remplir.
* Numeric : L'identifiant rowid de la table textNotice.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère la donnée TextNotice dans la base de données.
```
access.FillOneTextNotice(textFile, rowid, false);
```

## Méthode FillManyTextNotices
*Paramètres*
* TextFile : L'objet à remplir.
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données TextNotice dans la base de données.
```
access.FillManyTextNotices(textFile, "rowid = " & value, false);
```

## Méthode IsModifiedTextFile
*Paramètres*
* TextFile : L'objet à tester.

*Retour*
* Bool : True si l'objet est modifié, False sinon.

*Description*
* Retourne True si l'objet est modifié, False sinon.
```
var = access.IsModifiedTextFile(textFile);
```

## Méthode UpdateTextFile
*Paramètres*
* TextFile : L'objet à mettre à jour dans la base de données.

*Retour*
* None.

*Description*
* Met à jour la donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.UpdateTextFile(textFile);
```

## Méthode InsertTextFile
*Paramètres*
* TextFile : L'objet à ajouter dans la base de données.

*Retour*
* None.

*Description*
* Ajoute une donnée dans la base de données.
```
var = access.InsertTextFile(textFile);
```

## Méthode DeleteTextFile
*Paramètres*
* TextFile : L'objet à supprimer dans la base de données.

*Retour*
* None.

*Description*
* Supprime une donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.DeleteTextFile(textFile);
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
