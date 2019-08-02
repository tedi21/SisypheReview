# IDiaEnumSourceFilesPtr
 Classe qui énumère les fichiers sources différents contenus dans la source de données..

# Référence
## Méthode Get_Count
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Récupère le nombre de fichiers sources.
```
Get_Count();
```

## Méthode Item
*Paramètres*
* Numeric : 
* IDiaSourceFilePtr : 

*Retour*
* Numeric : 

*Description*
*  Extrait un fichier source au moyen d'un index.
```
Item();
```

## Méthode Next
*Paramètres*
* Numeric : 
* IDiaSourceFilePtr : 
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Récupère un nombre spécifié de fichiers sources dans la séquence d'énumération.
```
Next();
```

## Méthode Skip
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Ignore un nombre spécifié de fichiers sources dans une séquence d'énumération.
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
