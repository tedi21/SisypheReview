# IDiaEnumTablesPtr
 Classe qui énumère les différents tables contenues dans la source de données.

# Référence
## Méthode Get_Count
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Récupère le nombre de tables.
```
Get_Count();
```

## Méthode Item
*Paramètres*
* Numeric : 
* IDiaTablePtr : 

*Retour*
* Numeric : 

*Description*
*  Récupère une table à l'aide d'un index ou d'une étiquette.
```
Item();
```

## Méthode Next
*Paramètres*
* Numeric : 
* IDiaTablePtr : 
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Récupère un nombre spécifié de tables dans la séquence d'énumération.
```
Next();
```

## Méthode Skip
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Ignore un nombre spécifié de tables dans une séquence d'énumération.
```
Skip();
```

## Méthode Reset
*Paramètres*
* None.

*Retour*
* Numeric : 

*Description*
*  Réinitialise une séquence d'énumération au début.
```
Reset();
```
