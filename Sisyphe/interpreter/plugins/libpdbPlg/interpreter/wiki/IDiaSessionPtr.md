# IDiaSessionPtr
 Classe permettant de fournir un contexte de requête pour des symboles de débogage.

# Référence
## Méthode Get_globalScope
*Paramètres*
* IDiaSymbolPtr : 

*Retour*
* Numeric : 

*Description*
*  Extrait une référence de la portée globale.
```
Get_globalScope();
```

## Méthode Put_loadAddress
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Définit l'adresse de charge du fichier exécutable qui correspond aux symboles dans ce magasin de symboles.
```
Put_loadAddress();
```

## Méthode FindLinesByRVA
*Paramètres*
* Numeric : 
* Numeric : 
* IDiaEnumLineNumbersPtr : 

*Retour*
* Numeric : 

*Description*
*  Récupère les lignes d'un module spécifié qui contient une adresse virtuelle relative spécifiée (RVA).
```
FindLinesByRVA();
```

## Méthode FindLinesByLinenum
*Paramètres*
* IDiaSymbolPtr : 
* IDiaSourceFilePtr : 
* Numeric : 
* Numeric : 
* IDiaEnumLineNumbersPtr : 

*Retour*
* Numeric : 

*Description*
*  Détermine les numéros de ligne du module (compiland) que le numéro de ligne spécifié dans un fichier source se trouve dans ou approche.
```
FindLinesByLinenum();
```

## Méthode FindLines
*Paramètres*
* IDiaSymbolPtr : 
* IDiaSourceFilePtr : 
* IDiaEnumLineNumbersPtr : 

*Retour*
* Numeric : 

*Description*
*  Récupère les numéros de ligne dans les ID spécifiés de module (compiland) et du fichier source.
```
FindLines();
```

## Méthode FindFile
*Paramètres*
* IDiaSymbolPtr : 
* String : 
* Numeric : 
* IDiaEnumSourceFilesPtr : 

*Retour*
* Numeric : 

*Description*
*  Récupère les fichiers sources par le module et le nom.
```
FindFile();
```

## Méthode FindFile
*Paramètres*
* IDiaSymbolPtr : 
* IDiaEnumSourceFilesPtr : 

*Retour*
* Numeric : 

*Description*
*  Récupère les fichiers sources par le module.
```
FindFile();
```

## Méthode FindFile
*Paramètres*
* String : 
* Numeric : 
* IDiaEnumSourceFilesPtr : 

*Retour*
* Numeric : 

*Description*
*  Récupère les fichiers sources par le nom.
```
FindFile();
```

## Méthode FindFile
*Paramètres*
* IDiaEnumSourceFilesPtr : 

*Retour*
* Numeric : 

*Description*
*  Récupère tous les fichiers sources.
```
FindFile();
```
