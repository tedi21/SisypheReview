# DebugStubInfoAccess
Réprésente une classe d'accès pour les objets DebugStubInfo. Cette classe est utilisée pour gérer l'entité DebugStubInfo dans la base de données.

# Référence
## Constructeur DebugStubInfoAccess
*Paramètres*
* None.

*Description*
* Crée une instance de la classe DebugStubInfoAccess.
```
access = new DebugStubInfoAccess();
```

## Méthode GetAllDebugStubInfos
*Paramètres*
* None.

*Retour*
* Array[DebugStubInfo] : Tous les objets DebugStubInfo de la base de données.

*Description*
* Retourne toutes les objets DebugStubInfo de la base de données.
```
objects = access.GetAllDebugStubInfos();
```

## Méthode GetManyDebugStubInfos
*Paramètres*
* String : clause WHERE de la recherche SQL.

*Retour*
* Array[DebugStubInfo] : Les objets DebugStubInfo de la base de données correspondant à la requête SQL.

*Description*
* Retourne les objets DebugStubInfo de la base de données correspondant à la requête SQL.
```
objects = access.GetManyDebugStubInfos("lineNumber = " & value);
```

## Méthode GetOneDebugStubInfo
*Paramètres*
* Numeric : L'identifiant identifier de la table debugStubInfo.

*Retour*
* DebugStubInfo : L'objet DebugStubInfo de la base de données correspondant à l'identifiant.

*Description*
* Retourne l'objet DebugStubInfo de la base de données correspondant à l'identifiant.
```
object = access.GetOneDebugStubInfo(identifier);
```

## Méthode SelectOneDebugStubInfo
*Paramètres*
* Numeric : L'identifiant identifier de la table debugStubInfo.
* Bool : non utilisé.

*Retour*
* DebugStubInfo : L'objet DebugStubInfo de la base de données correspondant à l'identifiant, verrouillé pour modification.

*Description*
* Verrouille l'objet DebugStubInfo de la base de données correspondant à l'identifiant.
```
object = access.SelectOneDebugStubInfo(identifier, false);
```

## Méthode SelectManyDebugStubInfos
*Paramètres*
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* Array[DebugStubInfo] : Les objets DebugStubInfo de la base de données correspondant à la requête SQL, verrouillés pour modification.

*Description*
* Verrouille les objets DebugStubInfo de la base de données correspondant à la requête SQL.
```
objects = access.SelectManyDebugStubInfos("lineNumber = " & value, false);
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

## Méthode IsSelectedDebugStubInfo
*Paramètres*
* DebugStubInfo : L'objet à tester.

*Retour*
* Bool : True, si l'objet est verrouillé, False sinon.

*Description*
* Retourne True, si l'objet est verrouillé, False sinon.
```
var = access.IsSelectedDebugStubInfo(debugStubInfo);
```

## Méthode FillDebugFileInfo
*Paramètres*
* DebugStubInfo : L'objet à remplir.

*Retour*
* None.

*Description*
* Recupère la donnée debugFileInfo dans la base de données.
```
access.FillDebugFileInfo(debugStubInfo);
```

## Méthode FillAllDebugValueInfos
*Paramètres*
* DebugStubInfo : L'objet à remplir.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données DebugValueInfo dans la base de données.
```
access.FillAllDebugValueInfos(debugStubInfo, false);
```

## Méthode FillOneDebugValueInfo
*Paramètres*
* DebugStubInfo : L'objet à remplir.
* Numeric : L'identifiant identifier de la table debugValueInfo.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère la donnée DebugValueInfo dans la base de données.
```
access.FillOneDebugValueInfo(debugStubInfo, identifier, false);
```

## Méthode FillManyDebugValueInfos
*Paramètres*
* DebugStubInfo : L'objet à remplir.
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données DebugValueInfo dans la base de données.
```
access.FillManyDebugValueInfos(debugStubInfo, "identifier = " & value, false);
```

## Méthode IsModifiedDebugStubInfo
*Paramètres*
* DebugStubInfo : L'objet à tester.

*Retour*
* Bool : True si l'objet est modifié, False sinon.

*Description*
* Retourne True si l'objet est modifié, False sinon.
```
var = access.IsModifiedDebugStubInfo(debugStubInfo);
```

## Méthode UpdateDebugStubInfo
*Paramètres*
* DebugStubInfo : L'objet à mettre à jour dans la base de données.

*Retour*
* None.

*Description*
* Met à jour la donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.UpdateDebugStubInfo(debugStubInfo);
```

## Méthode InsertDebugStubInfo
*Paramètres*
* DebugStubInfo : L'objet à ajouter dans la base de données.

*Retour*
* None.

*Description*
* Ajoute une donnée dans la base de données.
```
var = access.InsertDebugStubInfo(debugStubInfo);
```

## Méthode DeleteDebugStubInfo
*Paramètres*
* DebugStubInfo : L'objet à supprimer dans la base de données.

*Retour*
* None.

*Description*
* Supprime une donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.DeleteDebugStubInfo(debugStubInfo);
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
