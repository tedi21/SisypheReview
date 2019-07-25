# CppVariableAccess
Réprésente une classe d'accès pour les objets CppVariable. Cette classe est utilisée pour gérer l'entité CppVariable dans la base de données.

# Référence
## Constructeur CppVariableAccess
*Paramètres*
* None.

*Description*
* Crée une instance de la classe CppVariableAccess.
```
access = new CppVariableAccess();
```

## Méthode GetAllCppVariables
*Paramètres*
* None.

*Retour*
* Array[CppVariable] : Tous les objets CppVariable de la base de données.

*Description*
* Retourne toutes les objets CppVariable de la base de données.
```
objects = access.GetAllCppVariables();
```

## Méthode GetManyCppVariables
*Paramètres*
* String : clause WHERE de la recherche SQL.

*Retour*
* Array[CppVariable] : Les objets CppVariable de la base de données correspondant à la requête SQL.

*Description*
* Retourne les objets CppVariable de la base de données correspondant à la requête SQL.
```
objects = access.GetManyCppVariables("varType = " & value);
```

## Méthode GetOneCppVariable
*Paramètres*
* Numeric : L'identifiant identifier de la table cppVariable.

*Retour*
* CppVariable : L'objet CppVariable de la base de données correspondant à l'identifiant.

*Description*
* Retourne l'objet CppVariable de la base de données correspondant à l'identifiant.
```
object = access.GetOneCppVariable(identifier);
```

## Méthode SelectOneCppVariable
*Paramètres*
* Numeric : L'identifiant identifier de la table cppVariable.
* Bool : non utilisé.

*Retour*
* CppVariable : L'objet CppVariable de la base de données correspondant à l'identifiant, verrouillé pour modification.

*Description*
* Verrouille l'objet CppVariable de la base de données correspondant à l'identifiant.
```
object = access.SelectOneCppVariable(identifier, false);
```

## Méthode SelectManyCppVariables
*Paramètres*
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* Array[CppVariable] : Les objets CppVariable de la base de données correspondant à la requête SQL, verrouillés pour modification.

*Description*
* Verrouille les objets CppVariable de la base de données correspondant à la requête SQL.
```
objects = access.SelectManyCppVariables("varType = " & value, false);
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

## Méthode IsSelectedCppVariable
*Paramètres*
* CppVariable : L'objet à tester.

*Retour*
* Bool : True, si l'objet est verrouillé, False sinon.

*Description*
* Retourne True, si l'objet est verrouillé, False sinon.
```
var = access.IsSelectedCppVariable(cppVariable);
```

## Méthode FillCppFunction
*Paramètres*
* CppVariable : L'objet à remplir.

*Retour*
* None.

*Description*
* Recupère la donnée cppFunction dans la base de données.
```
access.FillCppFunction(cppVariable);
```

## Méthode FillCppFile
*Paramètres*
* CppVariable : L'objet à remplir.

*Retour*
* None.

*Description*
* Recupère la donnée cppFile dans la base de données.
```
access.FillCppFile(cppVariable);
```

## Méthode IsModifiedCppVariable
*Paramètres*
* CppVariable : L'objet à tester.

*Retour*
* Bool : True si l'objet est modifié, False sinon.

*Description*
* Retourne True si l'objet est modifié, False sinon.
```
var = access.IsModifiedCppVariable(cppVariable);
```

## Méthode UpdateCppVariable
*Paramètres*
* CppVariable : L'objet à mettre à jour dans la base de données.

*Retour*
* None.

*Description*
* Met à jour la donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.UpdateCppVariable(cppVariable);
```

## Méthode InsertCppVariable
*Paramètres*
* CppVariable : L'objet à ajouter dans la base de données.

*Retour*
* None.

*Description*
* Ajoute une donnée dans la base de données.
```
var = access.InsertCppVariable(cppVariable);
```

## Méthode DeleteCppVariable
*Paramètres*
* CppVariable : L'objet à supprimer dans la base de données.

*Retour*
* None.

*Description*
* Supprime une donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.DeleteCppVariable(cppVariable);
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
