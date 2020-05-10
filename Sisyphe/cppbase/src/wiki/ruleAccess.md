# RuleAccess
Réprésente une classe d'accès pour les objets Rule. Cette classe est utilisée pour gérer l'entité Rule dans la base de données.

# Référence
## Constructeur RuleAccess
*Paramètres*
* None.

*Description*
* Crée une instance de la classe RuleAccess.
```
access = new RuleAccess();
```

## Méthode GetAllRules
*Paramètres*
* None.

*Retour*
* Array[Rule] : Tous les objets Rule de la base de données.

*Description*
* Retourne toutes les objets Rule de la base de données.
```
objects = access.GetAllRules();
```

## Méthode GetManyRules
*Paramètres*
* String : clause WHERE de la recherche SQL.

*Retour*
* Array[Rule] : Les objets Rule de la base de données correspondant à la requête SQL.

*Description*
* Retourne les objets Rule de la base de données correspondant à la requête SQL.
```
objects = access.GetManyRules("number = " & value);
```

## Méthode GetOneRule
*Paramètres*
* Numeric : L'identifiant identifier de la table rule.

*Retour*
* Rule : L'objet Rule de la base de données correspondant à l'identifiant.

*Description*
* Retourne l'objet Rule de la base de données correspondant à l'identifiant.
```
object = access.GetOneRule(identifier);
```

## Méthode SelectOneRule
*Paramètres*
* Numeric : L'identifiant identifier de la table rule.
* Bool : non utilisé.

*Retour*
* Rule : L'objet Rule de la base de données correspondant à l'identifiant, verrouillé pour modification.

*Description*
* Verrouille l'objet Rule de la base de données correspondant à l'identifiant.
```
object = access.SelectOneRule(identifier, false);
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

## Méthode IsSelectedRule
*Paramètres*
* Rule : L'objet à tester.

*Retour*
* Bool : True, si l'objet est verrouillé, False sinon.

*Description*
* Retourne True, si l'objet est verrouillé, False sinon.
```
var = access.IsSelectedRule(rule);
```

## Méthode IsModifiedRule
*Paramètres*
* Rule : L'objet à tester.

*Retour*
* Bool : True si l'objet est modifié, False sinon.

*Description*
* Retourne True si l'objet est modifié, False sinon.
```
var = access.IsModifiedRule(rule);
```

## Méthode UpdateRule
*Paramètres*
* Rule : L'objet à mettre à jour dans la base de données.

*Retour*
* None.

*Description*
* Met à jour la donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.UpdateRule(rule);
```

## Méthode InsertRule
*Paramètres*
* Rule : L'objet à ajouter dans la base de données.

*Retour*
* None.

*Description*
* Ajoute une donnée dans la base de données.
```
var = access.InsertRule(rule);
```

## Méthode DeleteRule
*Paramètres*
* Rule : L'objet à supprimer dans la base de données.

*Retour*
* None.

*Description*
* Supprime une donnée dans la base de données. La donnée doit exister dans la base de données et être verrouillé pour modification.
```
var = access.DeleteRule(rule);
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
