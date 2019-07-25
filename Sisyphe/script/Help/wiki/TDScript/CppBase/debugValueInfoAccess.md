# DebugValueInfoAccess
Réprésente une classe d'accès pour les objets DebugValueInfo. Cette classe est utilisée pour gérer l'entité DebugValueInfo dans la base de données.

# Référence
## Constructeur DebugValueInfoAccess
*Paramètres*
* None.

*Description*
* Crée une instance de la classe DebugValueInfoAccess.
```
access = new DebugValueInfoAccess();
```

## Méthode GetAllDebugValueInfos
*Paramètres*
* None.

*Retour*
* Array[DebugValueInfo] : Tous les objets DebugValueInfo de la base de données.

*Description*
* Retourne toutes les objets DebugValueInfo de la base de données.
```
objects = access.GetAllDebugValueInfos();
```

## Méthode GetManyDebugValueInfos
*Paramètres*
* String : clause WHERE de la recherche SQL.

*Retour*
* Array[DebugValueInfo] : Les objets DebugValueInfo de la base de données correspondant à la requête SQL.

*Description*
* Retourne les objets DebugValueInfo de la base de données correspondant à la requête SQL.
```
objects = access.GetManyDebugValueInfos("textValue = " & value);
```

## Méthode GetOneDebugValueInfo
*Paramètres*
* Numeric : L'identifiant identifier de la table debugValueInfo.

*Retour*
* DebugValueInfo : L'objet DebugValueInfo de la base de données correspondant à l'identifiant.

*Description*
* Retourne l'objet DebugValueInfo de la base de données correspondant à l'identifiant.
```
object = access.GetOneDebugValueInfo(identifier);
```

## Méthode SelectOneDebugValueInfo
*Paramètres*
* Numeric : L'identifiant identifier de la table debugValueInfo.
* Bool : non utilisé.

*Retour*
* DebugValueInfo : L'objet DebugValueInfo de la base de données correspondant à l'identifiant, verrouillé pour modification.

*Description*
* Verrouille l'objet DebugValueInfo de la base de données correspondant à l'identifiant.
```
object = access.SelectOneDebugValueInfo(identifier, false);
```

## Méthode SelectManyDebugValueInfos
*Paramètres*
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* Array[DebugValueInfo] : Les objets DebugValueInfo de la base de données correspondant à la requête SQL, verrouillés pour modification.

*Description*
* Verrouille les objets DebugValueInfo de la base de données correspondant à la requête SQL.
```
objects = access.SelectManyDebugValueInfos("textValue = " & value, false);
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

## Méthode IsSelectedDebugValueInfo
*Paramètres*
* DebugValueInfo : L'objet à tester.

*Retour*
* Bool : True, si l'objet est verrouillé, False sinon.

*Description*
* Retourne True, si l'objet est verrouillé, False sinon.
```
var = access.IsSelectedDebugValueInfo(debugValueInfo);
```

## Méthode FillDebugVariableInfo
*Paramètres*
* DebugValueInfo : L'objet à remplir.

*Retour*
* None.

*Description*
* Recupère la donnée debugVariableInfo dans la base de données.
```
access.FillDebugVariableInfo(debugValueInfo);
```

## Méthode FillDebugStubInfo
*Paramètres*
* DebugValueInfo : L'objet à remplir.

*Retour*
* None.

*Description*
* Recupère la donnée debugStubInfo dans la base de données.
```
access.FillDebugStubInfo(debugValueInfo);
```

## Méthode IsModifiedDebugValueInfo
*Paramètres*
* DebugValueInfo : L'objet à tester.

*Retour*
* Bool : True si l'objet est modifié, False sinon.

*Description*
* Retourne True si l'objet est modifié, False sinon.
```
var = access.IsModifiedDebugValueInfo(debugValueInfo);
```

## Méthode UpdateDebugValueInfo
*Paramètres*
* DebugValueInfo : L'objet à mettre à jour dans la base de données.

*Retour*
* None.

*Description*
* Met à jour la donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.UpdateDebugValueInfo(debugValueInfo);
```

## Méthode InsertDebugValueInfo
*Paramètres*
* DebugValueInfo : L'objet à ajouter dans la base de données.

*Retour*
* None.

*Description*
* Ajoute une donnée dans la base de données.
```
var = access.InsertDebugValueInfo(debugValueInfo);
```

## Méthode DeleteDebugValueInfo
*Paramètres*
* DebugValueInfo : L'objet à supprimer dans la base de données.

*Retour*
* None.

*Description*
* Supprime une donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.DeleteDebugValueInfo(debugValueInfo);
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
