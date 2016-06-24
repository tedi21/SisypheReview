# Bool
Cet objet représente un booléen. Il dispose diverses méthodes permettant de manipuler le booléen.

# Référence
## Méthode not_ `!`
*Paramètres*
* None.

*Retour*
* Bool : La valeur booléenne sur laquelle l'opérateur de négation a été appliqué.

*Description*
* Applique l'opérateur de négation.
```
b = false;
a = !b;
/* a = true */
```

## Méthode and_ `&&`
*Paramètres*
* Bool : Valeur booléenne à appliquer.

*Retour*
* Bool : La valeur booléenne sur laquelle l'opérateur ET a été appliqué.

*Description*
* Applique l'opérateur ET booléen.
```
b = false;
a = true;
c = a && b;
/* c = false */
```

## Méthode or_ `||`
*Paramètres*
* Bool : Valeur booléenne à appliquer.

*Retour*
* Bool : La valeur booléenne sur laquelle l'opérateur OU a été appliqué.

*Description*
* Applique l'opérateur OU booléen.
```
b = false;
a = true;
c = a || b;
/* c = true */
```