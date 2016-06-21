# DebugFileInfoAccess
Réprésente une classe d'accès pour les objets DebugFileInfo. Cette classe est utilisée pour gérer l'entité DebugFileInfo dans la base de données.

# Référence
## Constructeur DebugFileInfoAccess
*Paramètres*
* None.

*Description*
* Crée une instance de la classe DebugFileInfoAccess.
```
access = new DebugFileInfoAccess();
```

## Méthode GetAllDebugFileInfos
*Paramètres*
* None.

*Retour*
* Array[DebugFileInfo] : Tous les objets DebugFileInfo de la base de données.

*Description*
* Retourne toutes les objets DebugFileInfo de la base de données.
```
objects = access.GetAllDebugFileInfos();
```

## Méthode GetManyDebugFileInfos
*Paramètres*
* String : clause WHERE de la recherche SQL.

*Retour*
* Array[DebugFileInfo] : Les objets DebugFileInfo de la base de données correspondant à la requête SQL.

*Description*
* Retourne les objets DebugFileInfo de la base de données correspondant à la requête SQL.
```
objects = access.GetManyDebugFileInfos("compilandPath = " & value);
```

## Méthode GetOneDebugFileInfo
*Paramètres*
* Numeric : L'identifiant identifier de la table debugFileInfo.

*Retour*
* DebugFileInfo : L'objet DebugFileInfo de la base de données correspondant à l'identifiant.

*Description*
* Retourne l'objet DebugFileInfo de la base de données correspondant à l'identifiant.
```
object = access.GetOneDebugFileInfo(identifier);
```

## Méthode SelectOneDebugFileInfo
*Paramètres*
* Numeric : L'identifiant identifier de la table debugFileInfo.
* Bool : non utilisé.

*Retour*
* DebugFileInfo : L'objet DebugFileInfo de la base de données correspondant à l'identifiant, verrouillé pour modification.

*Description*
* Verrouille l'objet DebugFileInfo de la base de données correspondant à l'identifiant.
```
object = access.SelectOneDebugFileInfo(identifier, false);
```

## Méthode SelectManyDebugFileInfos
*Paramètres*
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* Array[DebugFileInfo] : Les objets DebugFileInfo de la base de données correspondant à la requête SQL, verrouillés pour modification.

*Description*
* Verrouille les objets DebugFileInfo de la base de données correspondant à la requête SQL.
```
objects = access.SelectManyDebugFileInfos("compilandPath = " & value, false);
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

## Méthode IsSelectedDebugFileInfo
*Paramètres*
* DebugFileInfo : L'objet à tester.

*Retour*
* Bool : True, si l'objet est verrouillé, False sinon.

*Description*
* Retourne True, si l'objet est verrouillé, False sinon.
```
var = access.IsSelectedDebugFileInfo(debugFileInfo);
```

## Méthode FillCppFile
*Paramètres*
* DebugFileInfo : L'objet à remplir.

*Retour*
* None.

*Description*
* Recupère la donnée cppFile dans la base de données.
```
access.FillCppFile(debugFileInfo);
```

## Méthode IsModifiedDebugFileInfo
*Paramètres*
* DebugFileInfo : L'objet à tester.

*Retour*
* Bool : True si l'objet est modifié, False sinon.

*Description*
* Retourne True si l'objet est modifié, False sinon.
```
var = access.IsModifiedDebugFileInfo(debugFileInfo);
```

## Méthode UpdateDebugFileInfo
*Paramètres*
* DebugFileInfo : L'objet à mettre à jour dans la base de données.

*Retour*
* None.

*Description*
* Met à jour la donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.UpdateDebugFileInfo(debugFileInfo);
```

## Méthode InsertDebugFileInfo
*Paramètres*
* DebugFileInfo : L'objet à ajouter dans la base de données.

*Retour*
* None.

*Description*
* Ajoute une donnée dans la base de données.
```
var = access.InsertDebugFileInfo(debugFileInfo);
```

## Méthode DeleteDebugFileInfo
*Paramètres*
* DebugFileInfo : L'objet à supprimer dans la base de données.

*Retour*
* None.

*Description*
* Supprime une donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.DeleteDebugFileInfo(debugFileInfo);
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
