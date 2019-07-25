# DebugTypeInfoAccess
Réprésente une classe d'accès pour les objets DebugTypeInfo. Cette classe est utilisée pour gérer l'entité DebugTypeInfo dans la base de données.

# Référence
## Constructeur DebugTypeInfoAccess
*Paramètres*
* None.

*Description*
* Crée une instance de la classe DebugTypeInfoAccess.
```
access = new DebugTypeInfoAccess();
```

## Méthode GetAllDebugTypeInfos
*Paramètres*
* None.

*Retour*
* Array[DebugTypeInfo] : Tous les objets DebugTypeInfo de la base de données.

*Description*
* Retourne toutes les objets DebugTypeInfo de la base de données.
```
objects = access.GetAllDebugTypeInfos();
```

## Méthode GetManyDebugTypeInfos
*Paramètres*
* String : clause WHERE de la recherche SQL.

*Retour*
* Array[DebugTypeInfo] : Les objets DebugTypeInfo de la base de données correspondant à la requête SQL.

*Description*
* Retourne les objets DebugTypeInfo de la base de données correspondant à la requête SQL.
```
objects = access.GetManyDebugTypeInfos("isChar = " & value);
```

## Méthode GetOneDebugTypeInfo
*Paramètres*
* Numeric : L'identifiant identifier de la table debugTypeInfo.

*Retour*
* DebugTypeInfo : L'objet DebugTypeInfo de la base de données correspondant à l'identifiant.

*Description*
* Retourne l'objet DebugTypeInfo de la base de données correspondant à l'identifiant.
```
object = access.GetOneDebugTypeInfo(identifier);
```

## Méthode SelectOneDebugTypeInfo
*Paramètres*
* Numeric : L'identifiant identifier de la table debugTypeInfo.
* Bool : non utilisé.

*Retour*
* DebugTypeInfo : L'objet DebugTypeInfo de la base de données correspondant à l'identifiant, verrouillé pour modification.

*Description*
* Verrouille l'objet DebugTypeInfo de la base de données correspondant à l'identifiant.
```
object = access.SelectOneDebugTypeInfo(identifier, false);
```

## Méthode SelectManyDebugTypeInfos
*Paramètres*
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* Array[DebugTypeInfo] : Les objets DebugTypeInfo de la base de données correspondant à la requête SQL, verrouillés pour modification.

*Description*
* Verrouille les objets DebugTypeInfo de la base de données correspondant à la requête SQL.
```
objects = access.SelectManyDebugTypeInfos("isChar = " & value, false);
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

## Méthode IsSelectedDebugTypeInfo
*Paramètres*
* DebugTypeInfo : L'objet à tester.

*Retour*
* Bool : True, si l'objet est verrouillé, False sinon.

*Description*
* Retourne True, si l'objet est verrouillé, False sinon.
```
var = access.IsSelectedDebugTypeInfo(debugTypeInfo);
```

## Méthode FillPrimitiveType
*Paramètres*
* DebugTypeInfo : L'objet à remplir.

*Retour*
* None.

*Description*
* Recupère la donnée primitiveType dans la base de données.
```
access.FillPrimitiveType(debugTypeInfo);
```

## Méthode FillAllRichTypes
*Paramètres*
* DebugTypeInfo : L'objet à remplir.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données RichType dans la base de données.
```
access.FillAllRichTypes(debugTypeInfo, false);
```

## Méthode FillAllDebugFunctionInfos
*Paramètres*
* DebugTypeInfo : L'objet à remplir.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données DebugFunctionInfo dans la base de données.
```
access.FillAllDebugFunctionInfos(debugTypeInfo, false);
```

## Méthode FillAllDebugVariableInfos
*Paramètres*
* DebugTypeInfo : L'objet à remplir.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données DebugVariableInfo dans la base de données.
```
access.FillAllDebugVariableInfos(debugTypeInfo, false);
```

## Méthode FillOneRichType
*Paramètres*
* DebugTypeInfo : L'objet à remplir.
* Numeric : L'identifiant identifier de la table debugTypeInfo.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère la donnée RichType dans la base de données.
```
access.FillOneRichType(debugTypeInfo, identifier, false);
```

## Méthode FillOneDebugFunctionInfo
*Paramètres*
* DebugTypeInfo : L'objet à remplir.
* Numeric : L'identifiant identifier de la table debugFunctionInfo.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère la donnée DebugFunctionInfo dans la base de données.
```
access.FillOneDebugFunctionInfo(debugTypeInfo, identifier, false);
```

## Méthode FillOneDebugVariableInfo
*Paramètres*
* DebugTypeInfo : L'objet à remplir.
* Numeric : L'identifiant identifier de la table debugVariableInfo.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère la donnée DebugVariableInfo dans la base de données.
```
access.FillOneDebugVariableInfo(debugTypeInfo, identifier, false);
```

## Méthode FillManyRichTypes
*Paramètres*
* DebugTypeInfo : L'objet à remplir.
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données RichType dans la base de données.
```
access.FillManyRichTypes(debugTypeInfo, "identifier = " & value, false);
```

## Méthode FillManyDebugFunctionInfos
*Paramètres*
* DebugTypeInfo : L'objet à remplir.
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données DebugFunctionInfo dans la base de données.
```
access.FillManyDebugFunctionInfos(debugTypeInfo, "identifier = " & value, false);
```

## Méthode FillManyDebugVariableInfos
*Paramètres*
* DebugTypeInfo : L'objet à remplir.
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données DebugVariableInfo dans la base de données.
```
access.FillManyDebugVariableInfos(debugTypeInfo, "identifier = " & value, false);
```

## Méthode IsModifiedDebugTypeInfo
*Paramètres*
* DebugTypeInfo : L'objet à tester.

*Retour*
* Bool : True si l'objet est modifié, False sinon.

*Description*
* Retourne True si l'objet est modifié, False sinon.
```
var = access.IsModifiedDebugTypeInfo(debugTypeInfo);
```

## Méthode UpdateDebugTypeInfo
*Paramètres*
* DebugTypeInfo : L'objet à mettre à jour dans la base de données.

*Retour*
* None.

*Description*
* Met à jour la donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.UpdateDebugTypeInfo(debugTypeInfo);
```

## Méthode InsertDebugTypeInfo
*Paramètres*
* DebugTypeInfo : L'objet à ajouter dans la base de données.

*Retour*
* None.

*Description*
* Ajoute une donnée dans la base de données.
```
var = access.InsertDebugTypeInfo(debugTypeInfo);
```

## Méthode DeleteDebugTypeInfo
*Paramètres*
* DebugTypeInfo : L'objet à supprimer dans la base de données.

*Retour*
* None.

*Description*
* Supprime une donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.DeleteDebugTypeInfo(debugTypeInfo);
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
