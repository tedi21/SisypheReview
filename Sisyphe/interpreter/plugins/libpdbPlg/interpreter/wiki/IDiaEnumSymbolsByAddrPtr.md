# IDiaEnumSymbolsByAddrPtr
 Classe qui énumère par l'adresse que différents symboles auront contenue dans la source de données.

# Référence
## Méthode SymbolByAddr
*Paramètres*
* Numeric : 
* Numeric : 
* IDiaSymbolPtr : 

*Retour*
* Numeric : 

*Description*
*  Positionne l'énumérateur en effectuant une recherche par le nombre de sections et l'offset d'image.
```
SymbolByAddr();
```

## Méthode SymbolByRVA
*Paramètres*
* Numeric : 
* IDiaSymbolPtr : 

*Retour*
* Numeric : 

*Description*
*  Positionne l'énumérateur en effectuant une recherche par l'adresse virtuelle associée (RVA).
```
SymbolByRVA();
```

## Méthode Next
*Paramètres*
* Numeric : 
* IDiaSymbolPtrIDiaSymbolPtr : 
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Récupère les symboles précédents dans l'ordre par l'adresse.
```
Next();
```

## Méthode Next
*Paramètres*
* Numeric : 
* IDiaSymbolPtrIDiaSymbolPtr : 
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Récupère les symboles précédents dans l'ordre par l'adresse.
```
Next();
```
