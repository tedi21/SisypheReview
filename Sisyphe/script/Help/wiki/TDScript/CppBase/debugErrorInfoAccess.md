# DebugErrorInfoAccess
Réprésente une classe d'accès pour les objets DebugErrorInfo. Cette classe est utilisée pour gérer l'entité DebugErrorInfo dans la base de données.

# Référence
## Constructeur DebugErrorInfoAccess
*Paramètres*
* None.

*Description*
* Crée une instance de la classe DebugErrorInfoAccess.
```
access = new DebugErrorInfoAccess();
```

## Méthode GetAllDebugErrorInfos
*Paramètres*
* None.

*Retour*
* Array[DebugErrorInfo] : Tous les objets DebugErrorInfo de la base de données.

*Description*
* Retourne toutes les objets DebugErrorInfo de la base de données.
```
objects = access.GetAllDebugErrorInfos();
```

## Méthode GetManyDebugErrorInfos
*Paramètres*
* String : clause WHERE de la recherche SQL.

*Retour*
* Array[DebugErrorInfo] : Les objets DebugErrorInfo de la base de données correspondant à la requête SQL.

*Description*
* Retourne les objets DebugErrorInfo de la base de données correspondant à la requête SQL.
```
objects = access.GetManyDebugErrorInfos("callStack = " & value);
```

## Méthode GetOneDebugErrorInfo
*Paramètres*
* Numeric : L'identifiant identifier de la table debugErrorInfo.

*Retour*
* DebugErrorInfo : L'objet DebugErrorInfo de la base de données correspondant à l'identifiant.

*Description*
* Retourne l'objet DebugErrorInfo de la base de données correspondant à l'identifiant.
```
object = access.GetOneDebugErrorInfo(identifier);
```

## Méthode SelectOneDebugErrorInfo
*Paramètres*
* Numeric : L'identifiant identifier de la table debugErrorInfo.
* Bool : non utilisé.

*Retour*
* DebugErrorInfo : L'objet DebugErrorInfo de la base de données correspondant à l'identifiant, verrouillé pour modification.

*Description*
* Verrouille l'objet DebugErrorInfo de la base de données correspondant à l'identifiant.
```
object = access.SelectOneDebugErrorInfo(identifier, false);
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

## Méthode IsSelectedDebugErrorInfo
*Paramètres*
* DebugErrorInfo : L'objet à tester.

*Retour*
* Bool : True, si l'objet est verrouillé, False sinon.

*Description*
* Retourne True, si l'objet est verrouillé, False sinon.
```
var = access.IsSelectedDebugErrorInfo(debugErrorInfo);
```

## Méthode IsModifiedDebugErrorInfo
*Paramètres*
* DebugErrorInfo : L'objet à tester.

*Retour*
* Bool : True si l'objet est modifié, False sinon.

*Description*
* Retourne True si l'objet est modifié, False sinon.
```
var = access.IsModifiedDebugErrorInfo(debugErrorInfo);
```

## Méthode UpdateDebugErrorInfo
*Paramètres*
* DebugErrorInfo : L'objet à mettre à jour dans la base de données.

*Retour*
* None.

*Description*
* Met à jour la donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.UpdateDebugErrorInfo(debugErrorInfo);
```

## Méthode InsertDebugErrorInfo
*Paramètres*
* DebugErrorInfo : L'objet à ajouter dans la base de données.

*Retour*
* None.

*Description*
* Ajoute une donnée dans la base de données.
```
var = access.InsertDebugErrorInfo(debugErrorInfo);
```

## Méthode DeleteDebugErrorInfo
*Paramètres*
* DebugErrorInfo : L'objet à supprimer dans la base de données.

*Retour*
* None.

*Description*
* Supprime une donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.DeleteDebugErrorInfo(debugErrorInfo);
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
