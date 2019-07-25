# CppClassAccess
Réprésente une classe d'accès pour les objets CppClass. Cette classe est utilisée pour gérer l'entité CppClass dans la base de données.

# Référence
## Constructeur CppClassAccess
*Paramètres*
* None.

*Description*
* Crée une instance de la classe CppClassAccess.
```
access = new CppClassAccess();
```

## Méthode GetAllCppClasss
*Paramètres*
* None.

*Retour*
* Array[CppClass] : Tous les objets CppClass de la base de données.

*Description*
* Retourne toutes les objets CppClass de la base de données.
```
objects = access.GetAllCppClasss();
```

## Méthode GetManyCppClasss
*Paramètres*
* String : clause WHERE de la recherche SQL.

*Retour*
* Array[CppClass] : Les objets CppClass de la base de données correspondant à la requête SQL.

*Description*
* Retourne les objets CppClass de la base de données correspondant à la requête SQL.
```
objects = access.GetManyCppClasss("name = " & value);
```

## Méthode GetOneCppClass
*Paramètres*
* Numeric : L'identifiant identifier de la table cppClass.

*Retour*
* CppClass : L'objet CppClass de la base de données correspondant à l'identifiant.

*Description*
* Retourne l'objet CppClass de la base de données correspondant à l'identifiant.
```
object = access.GetOneCppClass(identifier);
```

## Méthode SelectOneCppClass
*Paramètres*
* Numeric : L'identifiant identifier de la table cppClass.
* Bool : non utilisé.

*Retour*
* CppClass : L'objet CppClass de la base de données correspondant à l'identifiant, verrouillé pour modification.

*Description*
* Verrouille l'objet CppClass de la base de données correspondant à l'identifiant.
```
object = access.SelectOneCppClass(identifier, false);
```

## Méthode SelectManyCppClasss
*Paramètres*
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* Array[CppClass] : Les objets CppClass de la base de données correspondant à la requête SQL, verrouillés pour modification.

*Description*
* Verrouille les objets CppClass de la base de données correspondant à la requête SQL.
```
objects = access.SelectManyCppClasss("name = " & value, false);
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

## Méthode IsSelectedCppClass
*Paramètres*
* CppClass : L'objet à tester.

*Retour*
* Bool : True, si l'objet est verrouillé, False sinon.

*Description*
* Retourne True, si l'objet est verrouillé, False sinon.
```
var = access.IsSelectedCppClass(cppClass);
```

## Méthode FillEncapsulationClass
*Paramètres*
* CppClass : L'objet à remplir.

*Retour*
* None.

*Description*
* Recupère la donnée encapsulationClass dans la base de données.
```
access.FillEncapsulationClass(cppClass);
```

## Méthode FillCppFile
*Paramètres*
* CppClass : L'objet à remplir.

*Retour*
* None.

*Description*
* Recupère la donnée cppFile dans la base de données.
```
access.FillCppFile(cppClass);
```

## Méthode FillAllCppInheritances
*Paramètres*
* CppClass : L'objet à remplir.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppInheritance dans la base de données.
```
access.FillAllCppInheritances(cppClass, false);
```

## Méthode FillAllCppFunctions
*Paramètres*
* CppClass : L'objet à remplir.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppFunction dans la base de données.
```
access.FillAllCppFunctions(cppClass, false);
```

## Méthode FillAllInternClasses
*Paramètres*
* CppClass : L'objet à remplir.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données InternClasse dans la base de données.
```
access.FillAllInternClasses(cppClass, false);
```

## Méthode FillAllCppAttributes
*Paramètres*
* CppClass : L'objet à remplir.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppAttribute dans la base de données.
```
access.FillAllCppAttributes(cppClass, false);
```

## Méthode FillAllCppEnums
*Paramètres*
* CppClass : L'objet à remplir.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppEnum dans la base de données.
```
access.FillAllCppEnums(cppClass, false);
```

## Méthode FillOneCppInheritance
*Paramètres*
* CppClass : L'objet à remplir.
* Numeric : L'identifiant identifier de la table cppInheritance.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère la donnée CppInheritance dans la base de données.
```
access.FillOneCppInheritance(cppClass, identifier, false);
```

## Méthode FillOneCppFunction
*Paramètres*
* CppClass : L'objet à remplir.
* Numeric : L'identifiant identifier de la table cppFunction.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère la donnée CppFunction dans la base de données.
```
access.FillOneCppFunction(cppClass, identifier, false);
```

## Méthode FillOneInternClasse
*Paramètres*
* CppClass : L'objet à remplir.
* Numeric : L'identifiant identifier de la table cppClass.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère la donnée InternClasse dans la base de données.
```
access.FillOneInternClasse(cppClass, identifier, false);
```

## Méthode FillOneCppAttribute
*Paramètres*
* CppClass : L'objet à remplir.
* Numeric : L'identifiant identifier de la table cppAttribute.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère la donnée CppAttribute dans la base de données.
```
access.FillOneCppAttribute(cppClass, identifier, false);
```

## Méthode FillOneCppEnum
*Paramètres*
* CppClass : L'objet à remplir.
* Numeric : L'identifiant identifier de la table cppEnum.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère la donnée CppEnum dans la base de données.
```
access.FillOneCppEnum(cppClass, identifier, false);
```

## Méthode FillManyCppInheritances
*Paramètres*
* CppClass : L'objet à remplir.
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppInheritance dans la base de données.
```
access.FillManyCppInheritances(cppClass, "identifier = " & value, false);
```

## Méthode FillManyCppFunctions
*Paramètres*
* CppClass : L'objet à remplir.
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppFunction dans la base de données.
```
access.FillManyCppFunctions(cppClass, "identifier = " & value, false);
```

## Méthode FillManyInternClasses
*Paramètres*
* CppClass : L'objet à remplir.
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données InternClasse dans la base de données.
```
access.FillManyInternClasses(cppClass, "identifier = " & value, false);
```

## Méthode FillManyCppAttributes
*Paramètres*
* CppClass : L'objet à remplir.
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppAttribute dans la base de données.
```
access.FillManyCppAttributes(cppClass, "identifier = " & value, false);
```

## Méthode FillManyCppEnums
*Paramètres*
* CppClass : L'objet à remplir.
* String : clause WHERE de la recherche SQL.
* Bool : non utilisé.

*Retour*
* None.

*Description*
* Recupère les données CppEnum dans la base de données.
```
access.FillManyCppEnums(cppClass, "identifier = " & value, false);
```

## Méthode IsModifiedCppClass
*Paramètres*
* CppClass : L'objet à tester.

*Retour*
* Bool : True si l'objet est modifié, False sinon.

*Description*
* Retourne True si l'objet est modifié, False sinon.
```
var = access.IsModifiedCppClass(cppClass);
```

## Méthode UpdateCppClass
*Paramètres*
* CppClass : L'objet à mettre à jour dans la base de données.

*Retour*
* None.

*Description*
* Met à jour la donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.UpdateCppClass(cppClass);
```

## Méthode InsertCppClass
*Paramètres*
* CppClass : L'objet à ajouter dans la base de données.

*Retour*
* None.

*Description*
* Ajoute une donnée dans la base de données.
```
var = access.InsertCppClass(cppClass);
```

## Méthode DeleteCppClass
*Paramètres*
* CppClass : L'objet à supprimer dans la base de données.

*Retour*
* None.

*Description*
* Supprime une donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.DeleteCppClass(cppClass);
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
