# CppInheritance
cppInheritance table represents an inheritance.

# Référence
## Constructeur CppInheritance
*Paramètres*
* None.

*Description*
* Crée une instance de la classe CppInheritance.
```
var = new CppInheritance();
```

## Constructeur CppInheritance
*Paramètres*
* String : La valeur de la colonne baseClassName.
* String : La valeur de la colonne baseAccess.

*Description*
* Crée une instance de la classe CppInheritance.
```
var = new CppInheritance(baseClassName, baseAccess);
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

## Méthode BaseClassName
*Paramètres*
* None.

*Retour*
* String : La colonne baseClassName.

*Description*
* Retourne la colonne BaseClassName.
```
val = var.BaseClassName;
```

## Méthode BaseAccess
*Paramètres*
* None.

*Retour*
* String : La colonne baseAccess.

*Description*
* Retourne la colonne BaseAccess.
```
val = var.BaseAccess;
```

## Méthode Derived
*Paramètres*
* None.

*Retour*
* CppClass : La colonne derived.

*Description*
* Retourne la colonne Derived.
```
derived = var.Derived;
```

## Méthode Derived
*Paramètres*
* CppClass : La valeur de la colonne derived.

*Retour*
* None.

*Description*
* Définit la colonne derived.
```
var.Derived(derived);
```

## Méthode BaseClassName
*Paramètres*
* String : La valeur de la colonne baseClassName.

*Retour*
* None.

*Description*
* Définit la colonne baseClassName.
```
var.BaseClassName(baseClassName);
```

## Méthode BaseAccess
*Paramètres*
* String : La valeur de la colonne baseAccess.

*Retour*
* None.

*Description*
* Définit la colonne baseAccess.
```
var.BaseAccess(baseAccess);
```

## Méthode HasDerived
*Paramètres*
* None.

*Retour*
* Bool : Une valeur est définie pour la colonne derived.

*Description*
* Indique si la colonne Derived a une valeur définie.
```
val = var.HasDerived;
```

## Méthode removeDerived
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime la valeur définie pour la colonne derived.
```
var.Derived = null;
```
