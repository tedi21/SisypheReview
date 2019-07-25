# DebugVariableInfoAccess
Réprésente une classe d'accès pour les objets DebugVariableInfo. Cette classe est utilisée pour gérer l'entité DebugVariableInfo dans la base de données.

# Référence
## Constructeur DebugVariableInfoAccess
*Paramètres*
* None.

*Description*
* Crée une instance de la classe DebugVariableInfoAccess.
```
access = new DebugVariableInfoAccess();
```

## Méthode GetAllDebugVariableInfos
*Paramètres*
* None.

*Retour*
* Array[DebugVariableInfo] : Tous les objets DebugVariableInfo de la base de données.

*Description*
* Retourne toutes les objets DebugVariableInfo de la base de données.
```
objects = access.GetAllDebugVariableInfos();
```

## Méthode GetManyDebugVariableInfos
*Paramètres*
* String : clause WHERE de la recherche SQL.

*Retour*
* Array[DebugVariableInfo] : Les objets DebugVariableInfo de la base de données correspondant à la requête SQL.

*Description*
* Retourne les objets DebugVariableInfo de la base de données correspondant à la requête SQL.
```
objects = access.GetManyDebugVariableInfos("category = " & value);
```

## Méthode GetOneDebugVariableInfo
*Paramètres*
* Numeric : L'identifiant identifier de la table debugVariableInfo.

*Retour*
* DebugVariableInfo : L'objet DebugVariableInfo de la base de données correspondant à l'identifiant.

*Description*
* Retourne l'objet DebugVariableInfo de la base de données correspondant à l'identifiant.
```
object = access.GetOneDebugVariableInfo(identifier);
```

## Méthode SelectOneDebugVariableInfo
*Paramètres*
* Numeric : L'identifiant identifier de la table debugVariableInfo.
* Bool : non utilisé.

*Retour*
* DebugVariableInfo : L'objet DebugVariableInfo de la base de données correspondant à l'identifiant, verrouillé pour modification.

*Description*
* Verrouille l'objet DebugVariableInfo de la base de données correspondant à l'identifiant.
```
object = access.SelectOneDebugVariableInfo(identifier, false);
```

## Méthode SelectManyDebugVariableInfos
*Paramètres*
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* Array[DebugVariableInfo] : Les objets DebugVariableInfo de la base de données correspondant à la requête SQL, verrouillés pour modification.

*Description*
* Verrouille les objets DebugVariableInfo de la base de données correspondant à la requête SQL.
```
objects = access.SelectManyDebugVariableInfos("category = " & value, false);
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

## Méthode IsSelectedDebugVariableInfo
*Paramètres*
* DebugVariableInfo : L'objet à tester.

*Retour*
* Bool : True, si l'objet est verrouillé, False sinon.

*Description*
* Retourne True, si l'objet est verrouillé, False sinon.
```
var = access.IsSelectedDebugVariableInfo(debugVariableInfo);
```

## Méthode FillDebugTypeInfo
*Paramètres*
* DebugVariableInfo : L'objet à remplir.

*Retour*
* None.

*Description*
* Recupère la donnée debugTypeInfo dans la base de données.
```
access.FillDebugTypeInfo(debugVariableInfo);
```

## Méthode FillDebugFunctionInfo
*Paramètres*
* DebugVariableInfo : L'objet à remplir.

*Retour*
* None.

*Description*
* Recupère la donnée debugFunctionInfo dans la base de données.
```
access.FillDebugFunctionInfo(debugVariableInfo);
```

## Méthode FillAllDebugValueInfos
*Paramètres*
* DebugVariableInfo : L'objet à remplir.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données DebugValueInfo dans la base de données.
```
access.FillAllDebugValueInfos(debugVariableInfo, false);
```

## Méthode FillOneDebugValueInfo
*Paramètres*
* DebugVariableInfo : L'objet à remplir.
* Numeric : L'identifiant identifier de la table debugValueInfo.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère la donnée DebugValueInfo dans la base de données.
```
access.FillOneDebugValueInfo(debugVariableInfo, identifier, false);
```

## Méthode FillManyDebugValueInfos
*Paramètres*
* DebugVariableInfo : L'objet à remplir.
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données DebugValueInfo dans la base de données.
```
access.FillManyDebugValueInfos(debugVariableInfo, "identifier = " & value, false);
```

## Méthode IsModifiedDebugVariableInfo
*Paramètres*
* DebugVariableInfo : L'objet à tester.

*Retour*
* Bool : True si l'objet est modifié, False sinon.

*Description*
* Retourne True si l'objet est modifié, False sinon.
```
var = access.IsModifiedDebugVariableInfo(debugVariableInfo);
```

## Méthode UpdateDebugVariableInfo
*Paramètres*
* DebugVariableInfo : L'objet à mettre à jour dans la base de données.

*Retour*
* None.

*Description*
* Met à jour la donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.UpdateDebugVariableInfo(debugVariableInfo);
```

## Méthode InsertDebugVariableInfo
*Paramètres*
* DebugVariableInfo : L'objet à ajouter dans la base de données.

*Retour*
* None.

*Description*
* Ajoute une donnée dans la base de données.
```
var = access.InsertDebugVariableInfo(debugVariableInfo);
```

## Méthode DeleteDebugVariableInfo
*Paramètres*
* DebugVariableInfo : L'objet à supprimer dans la base de données.

*Retour*
* None.

*Description*
* Supprime une donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.DeleteDebugVariableInfo(debugVariableInfo);
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
