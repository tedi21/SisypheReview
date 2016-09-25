# IDiaEnumSymbolsPtr
 Classe qui énumère les différents symboles contenus dans la source de données.

# Référence
## Méthode Get_Count
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Récupère le nombre de symboles.
```
Get_Count();
```

## Méthode Item
*Paramètres*
* Numeric : 
* IDiaSymbolPtr : 

*Retour*
* Numeric : 

*Description*
*  Récupère un symbole au moyen d'un index.
```
Item();
```

## Méthode Next
*Paramètres*
* Numeric : 
* IDiaSymbolPtr : 
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Récupère un nombre spécifié de symboles dans la séquence d'énumération.
```
Next();
```

## Méthode Skip
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Ignore un nombre spécifié de symboles dans une séquence d'énumération.
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
