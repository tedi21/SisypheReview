# Rule
Creation Table________________rule table represents a static analysis rule.

# Référence
## Constructeur Rule
*Paramètres*
* None.

*Description*
* Crée une instance de la classe Rule.
```
var = new Rule();
```

## Constructeur Rule
*Paramètres*
* Numeric : La valeur de la colonne number.
* String : La valeur de la colonne description.
* Numeric : La valeur de la colonne enabled.

*Description*
* Crée une instance de la classe Rule.
```
var = new Rule(number, description, enabled);
```

## Méthode Identifier
*Paramètres*
* None.

*Retour*
* Numeric : La colonne identifier.

*Description*
* Retourne la colonne Identifier.
```
val = var.Identifier;
```

## Méthode Number
*Paramètres*
* None.

*Retour*
* Numeric : La colonne number.

*Description*
* Retourne la colonne Number.
```
val = var.Number;
```

## Méthode Description
*Paramètres*
* None.

*Retour*
* String : La colonne description.

*Description*
* Retourne la colonne Description.
```
val = var.Description;
```

## Méthode Enabled
*Paramètres*
* None.

*Retour*
* Numeric : La colonne enabled.

*Description*
* Retourne la colonne Enabled.
```
val = var.Enabled;
```

## Méthode Number
*Paramètres*
* Numeric : La valeur de la colonne number.

*Retour*
* None.

*Description*
* Définit la colonne number.
```
var.Number(number);
```

## Méthode Description
*Paramètres*
* String : La valeur de la colonne description.

*Retour*
* None.

*Description*
* Définit la colonne description.
```
var.Description(description);
```

## Méthode Enabled
*Paramètres*
* Numeric : La valeur de la colonne enabled.

*Retour*
* None.

*Description*
* Définit la colonne enabled.
```
var.Enabled(enabled);
```
