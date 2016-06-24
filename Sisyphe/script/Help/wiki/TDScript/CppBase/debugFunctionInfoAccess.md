# DebugFunctionInfoAccess
Réprésente une classe d'accès pour les objets DebugFunctionInfo. Cette classe est utilisée pour gérer l'entité DebugFunctionInfo dans la base de données.

# Référence
## Constructeur DebugFunctionInfoAccess
*Paramètres*
* None.

*Description*
* Crée une instance de la classe DebugFunctionInfoAccess.
```
access = new DebugFunctionInfoAccess();
```

## Méthode GetAllDebugFunctionInfos
*Paramètres*
* None.

*Retour*
* Array[DebugFunctionInfo] : Tous les objets DebugFunctionInfo de la base de données.

*Description*
* Retourne toutes les objets DebugFunctionInfo de la base de données.
```
objects = access.GetAllDebugFunctionInfos();
```

## Méthode GetManyDebugFunctionInfos
*Paramètres*
* String : clause WHERE de la recherche SQL.

*Retour*
* Array[DebugFunctionInfo] : Les objets DebugFunctionInfo de la base de données correspondant à la requête SQL.

*Description*
* Retourne les objets DebugFunctionInfo de la base de données correspondant à la requête SQL.
```
objects = access.GetManyDebugFunctionInfos("lineNumber = " & value);
```

## Méthode GetOneDebugFunctionInfo
*Paramètres*
* Numeric : L'identifiant identifier de la table debugFunctionInfo.

*Retour*
* DebugFunctionInfo : L'objet DebugFunctionInfo de la base de données correspondant à l'identifiant.

*Description*
* Retourne l'objet DebugFunctionInfo de la base de données correspondant à l'identifiant.
```
object = access.GetOneDebugFunctionInfo(identifier);
```

## Méthode SelectOneDebugFunctionInfo
*Paramètres*
* Numeric : L'identifiant identifier de la table debugFunctionInfo.
* Bool : non utilisé.

*Retour*
* DebugFunctionInfo : L'objet DebugFunctionInfo de la base de données correspondant à l'identifiant, verrouillé pour modification.

*Description*
* Verrouille l'objet DebugFunctionInfo de la base de données correspondant à l'identifiant.
```
object = access.SelectOneDebugFunctionInfo(identifier, false);
```

## Méthode SelectManyDebugFunctionInfos
*Paramètres*
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* Array[DebugFunctionInfo] : Les objets DebugFunctionInfo de la base de données correspondant à la requête SQL, verrouillés pour modification.

*Description*
* Verrouille les objets DebugFunctionInfo de la base de données correspondant à la requête SQL.
```
objects = access.SelectManyDebugFunctionInfos("lineNumber = " & value, false);
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

## Méthode IsSelectedDebugFunctionInfo
*Paramètres*
* DebugFunctionInfo : L'objet à tester.

*Retour*
* Bool : True, si l'objet est verrouillé, False sinon.

*Description*
* Retourne True, si l'objet est verrouillé, False sinon.
```
var = access.IsSelectedDebugFunctionInfo(debugFunctionInfo);
```

## Méthode FillCppFunction
*Paramètres*
* DebugFunctionInfo : L'objet à remplir.

*Retour*
* None.

*Description*
* Recupère la donnée cppFunction dans la base de données.
```
access.FillCppFunction(debugFunctionInfo);
```

## Méthode FillAllDebugVariableInfos
*Paramètres*
* DebugFunctionInfo : L'objet à remplir.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données DebugVariableInfo dans la base de données.
```
access.FillAllDebugVariableInfos(debugFunctionInfo, false);
```

## Méthode FillOneDebugVariableInfo
*Paramètres*
* DebugFunctionInfo : L'objet à remplir.
* Numeric : L'identifiant identifier de la table debugVariableInfo.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère la donnée DebugVariableInfo dans la base de données.
```
access.FillOneDebugVariableInfo(debugFunctionInfo, identifier, false);
```

## Méthode FillManyDebugVariableInfos
*Paramètres*
* DebugFunctionInfo : L'objet à remplir.
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données DebugVariableInfo dans la base de données.
```
access.FillManyDebugVariableInfos(debugFunctionInfo, "identifier = " & value, false);
```

## Méthode IsModifiedDebugFunctionInfo
*Paramètres*
* DebugFunctionInfo : L'objet à tester.

*Retour*
* Bool : True si l'objet est modifié, False sinon.

*Description*
* Retourne True si l'objet est modifié, False sinon.
```
var = access.IsModifiedDebugFunctionInfo(debugFunctionInfo);
```

## Méthode UpdateDebugFunctionInfo
*Paramètres*
* DebugFunctionInfo : L'objet à mettre à jour dans la base de données.

*Retour*
* None.

*Description*
* Met à jour la donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.UpdateDebugFunctionInfo(debugFunctionInfo);
```

## Méthode InsertDebugFunctionInfo
*Paramètres*
* DebugFunctionInfo : L'objet à ajouter dans la base de données.

*Retour*
* None.

*Description*
* Ajoute une donnée dans la base de données.
```
var = access.InsertDebugFunctionInfo(debugFunctionInfo);
```

## Méthode DeleteDebugFunctionInfo
*Paramètres*
* DebugFunctionInfo : L'objet à supprimer dans la base de données.

*Retour*
* None.

*Description*
* Supprime une donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.DeleteDebugFunctionInfo(debugFunctionInfo);
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
