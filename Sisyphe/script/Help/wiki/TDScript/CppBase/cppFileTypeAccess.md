# CppFileTypeAccess
Réprésente une classe d'accès pour les objets CppFileType. Cette classe est utilisée pour gérer l'entité CppFileType dans la base de données.

# Référence
## Constructeur CppFileTypeAccess
*Paramètres*
* None.

*Description*
* Crée une instance de la classe CppFileTypeAccess.
```
access = new CppFileTypeAccess();
```

## Méthode GetAllCppFileTypes
*Paramètres*
* None.

*Retour*
* Array[CppFileType] : Tous les objets CppFileType de la base de données.

*Description*
* Retourne toutes les objets CppFileType de la base de données.
```
objects = access.GetAllCppFileTypes();
```

## Méthode GetManyCppFileTypes
*Paramètres*
* String : clause WHERE de la recherche SQL.

*Retour*
* Array[CppFileType] : Les objets CppFileType de la base de données correspondant à la requête SQL.

*Description*
* Retourne les objets CppFileType de la base de données correspondant à la requête SQL.
```
objects = access.GetManyCppFileTypes("string = " & value);
```

## Méthode GetOneCppFileType
*Paramètres*
* Numeric : L'identifiant identifier de la table cppFileType.

*Retour*
* CppFileType : L'objet CppFileType de la base de données correspondant à l'identifiant.

*Description*
* Retourne l'objet CppFileType de la base de données correspondant à l'identifiant.
```
object = access.GetOneCppFileType(identifier);
```

## Méthode SelectOneCppFileType
*Paramètres*
* Numeric : L'identifiant identifier de la table cppFileType.
* Bool : non utilisé.

*Retour*
* CppFileType : L'objet CppFileType de la base de données correspondant à l'identifiant, verrouillé pour modification.

*Description*
* Verrouille l'objet CppFileType de la base de données correspondant à l'identifiant.
```
object = access.SelectOneCppFileType(identifier, false);
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

## Méthode IsSelectedCppFileType
*Paramètres*
* CppFileType : L'objet à tester.

*Retour*
* Bool : True, si l'objet est verrouillé, False sinon.

*Description*
* Retourne True, si l'objet est verrouillé, False sinon.
```
var = access.IsSelectedCppFileType(cppFileType);
```

## Méthode FillAllCppFiles
*Paramètres*
* CppFileType : L'objet à remplir.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppFile dans la base de données.
```
access.FillAllCppFiles(cppFileType, false);
```

## Méthode FillOneCppFile
*Paramètres*
* CppFileType : L'objet à remplir.
* Numeric : L'identifiant identifier de la table cppFile.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère la donnée CppFile dans la base de données.
```
access.FillOneCppFile(cppFileType, identifier, false);
```

## Méthode FillManyCppFiles
*Paramètres*
* CppFileType : L'objet à remplir.
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppFile dans la base de données.
```
access.FillManyCppFiles(cppFileType, "identifier = " & value, false);
```

## Méthode IsModifiedCppFileType
*Paramètres*
* CppFileType : L'objet à tester.

*Retour*
* Bool : True si l'objet est modifié, False sinon.

*Description*
* Retourne True si l'objet est modifié, False sinon.
```
var = access.IsModifiedCppFileType(cppFileType);
```

## Méthode UpdateCppFileType
*Paramètres*
* CppFileType : L'objet à mettre à jour dans la base de données.

*Retour*
* None.

*Description*
* Met à jour la donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.UpdateCppFileType(cppFileType);
```

## Méthode InsertCppFileType
*Paramètres*
* CppFileType : L'objet à ajouter dans la base de données.

*Retour*
* None.

*Description*
* Ajoute une donnée dans la base de données.
```
var = access.InsertCppFileType(cppFileType);
```

## Méthode DeleteCppFileType
*Paramètres*
* CppFileType : L'objet à supprimer dans la base de données.

*Retour*
* None.

*Description*
* Supprime une donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.DeleteCppFileType(cppFileType);
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
