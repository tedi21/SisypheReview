# TextNoticeAccess
Réprésente une classe d'accès pour les objets TextNotice. Cette classe est utilisée pour gérer l'entité TextNotice dans la base de données.

# Référence
## Constructeur TextNoticeAccess
*Paramètres*
* None.

*Description*
* Crée une instance de la classe TextNoticeAccess.
```
access = new TextNoticeAccess();
```

## Méthode GetAllTextNotices
*Paramètres*
* None.

*Retour*
* Array[TextNotice] : Tous les objets TextNotice de la base de données.

*Description*
* Retourne toutes les objets TextNotice de la base de données.
```
objects = access.GetAllTextNotices();
```

## Méthode GetManyTextNotices
*Paramètres*
* String : clause WHERE de la recherche SQL.

*Retour*
* Array[TextNotice] : Les objets TextNotice de la base de données correspondant à la requête SQL.

*Description*
* Retourne les objets TextNotice de la base de données correspondant à la requête SQL.
```
objects = access.GetManyTextNotices("description = " & value);
```

## Méthode GetOneTextNotice
*Paramètres*
* Numeric : L'identifiant rowid de la table textNotice.

*Retour*
* TextNotice : L'objet TextNotice de la base de données correspondant à l'identifiant.

*Description*
* Retourne l'objet TextNotice de la base de données correspondant à l'identifiant.
```
object = access.GetOneTextNotice(rowid);
```

## Méthode SelectOneTextNotice
*Paramètres*
* Numeric : L'identifiant rowid de la table textNotice.
* Bool : non utilisé.

*Retour*
* TextNotice : L'objet TextNotice de la base de données correspondant à l'identifiant, verrouillé pour modification.

*Description*
* Verrouille l'objet TextNotice de la base de données correspondant à l'identifiant.
```
object = access.SelectOneTextNotice(rowid, false);
```

## Méthode SelectManyTextNotices
*Paramètres*
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* Array[TextNotice] : Les objets TextNotice de la base de données correspondant à la requête SQL, verrouillés pour modification.

*Description*
* Verrouille les objets TextNotice de la base de données correspondant à la requête SQL.
```
objects = access.SelectManyTextNotices("description = " & value, false);
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

## Méthode IsSelectedTextNotice
*Paramètres*
* TextNotice : L'objet à tester.

*Retour*
* Bool : True, si l'objet est verrouillé, False sinon.

*Description*
* Retourne True, si l'objet est verrouillé, False sinon.
```
var = access.IsSelectedTextNotice(textNotice);
```

## Méthode FillTextFile
*Paramètres*
* TextNotice : L'objet à remplir.

*Retour*
* None.

*Description*
* Recupère la donnée textFile dans la base de données.
```
access.FillTextFile(textNotice);
```

## Méthode IsModifiedTextNotice
*Paramètres*
* TextNotice : L'objet à tester.

*Retour*
* Bool : True si l'objet est modifié, False sinon.

*Description*
* Retourne True si l'objet est modifié, False sinon.
```
var = access.IsModifiedTextNotice(textNotice);
```

## Méthode UpdateTextNotice
*Paramètres*
* TextNotice : L'objet à mettre à jour dans la base de données.

*Retour*
* None.

*Description*
* Met à jour la donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.UpdateTextNotice(textNotice);
```

## Méthode InsertTextNotice
*Paramètres*
* TextNotice : L'objet à ajouter dans la base de données.

*Retour*
* None.

*Description*
* Ajoute une donnée dans la base de données.
```
var = access.InsertTextNotice(textNotice);
```

## Méthode DeleteTextNotice
*Paramètres*
* TextNotice : L'objet à supprimer dans la base de données.

*Retour*
* None.

*Description*
* Supprime une donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.DeleteTextNotice(textNotice);
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
