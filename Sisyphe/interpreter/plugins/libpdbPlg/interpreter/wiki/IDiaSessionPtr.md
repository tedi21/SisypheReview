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

## Méthode GetSymbolsByAddr
*Paramètres*
* IDiaEnumSymbolsByAddrPtr : 

*Retour*
* Numeric : 

*Description*
*  Extrait un énumérateur qui recherche des symboles dans l'ordre de leurs adresses.
```
GetSymbolsByAddr();
```

## Méthode GetEnumTables
*Paramètres*
* IDiaEnumTablesPtr : 

*Retour*
* Numeric : 

*Description*
*  Récupère un énumérateur pour tous les tables contenues dans le magasin de symboles.
```
GetEnumTables();
```

## Méthode FindSymbolByAddr
*Paramètres*
* Numeric : 
* Numeric : 
* SymTagEnumType : 
* IDiaSymbolPtr : 

*Retour*
* Numeric : 

*Description*
*  Récupère un type spécifié de symboles qui contient, ou est le plus proche de, une adresse spécifiée.
```
FindSymbolByAddr();
```

## Méthode FindSymbolByRVA
*Paramètres*
* Numeric : 
* SymTagEnumType : 
* IDiaSymbolPtr : 

*Retour*
* Numeric : 

*Description*
*  Récupère un type spécifié de symboles qui contient, ou est le plus proche de, une adresse virtuelle relative spécifiée (RVA).
```
FindSymbolByRVA();
```

## Méthode SymbolById
*Paramètres*
* Numeric : 
* IDiaSymbolPtr : 

*Retour*
* Numeric : 

*Description*
*  Récupère un symbole par son identificateur unique.
```
SymbolById();
```

## Méthode SymsAreEquiv
*Paramètres*
* IDiaSymbolPtr : 
* IDiaSymbolPtr : 

*Retour*
* Numeric : 

*Description*
*  Vérifie si deux symboles sont équivalents.
```
SymsAreEquiv();
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

## Méthode FindLinesByAddr
*Paramètres*
* Numeric : 
* Numeric : 
* Numeric : 
* IDiaEnumLineNumbersPtr : 

*Retour*
* Numeric : 

*Description*
*  Retrieves the lines in a specified compiland that contain a specified address.
```
FindLinesByAddr();
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

## Méthode FindChildren
*Paramètres*
* IDiaSymbolPtr : 
* SymTagEnumType : 
* String : 
* Numeric : 
* IDiaEnumSymbolsPtr : 

*Retour*
* Numeric : 

*Description*
*  Récupère tous les enfants d'un identificateur parent spécifié qui correspondent au nom et le type de symbole.
```
FindChildren();
```

## Méthode FindChildren
*Paramètres*
* IDiaSymbolPtr : 
* SymTagEnumType : 
* IDiaEnumSymbolsPtr : 

*Retour*
* Numeric : 

*Description*
*  Récupère tous les enfants d'un identificateur parent spécifié qui correspondent au nom et le type de symbole.
```
FindChildren();
```
