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
* IDiaSymbolPtr : 
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Récupère les symboles ci-dessous dans l'ordre par l'adresse.
```
Next();
```

## Méthode Prev
*Paramètres*
* Numeric : 
* IDiaSymbolPtr : 
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Récupère les symboles précédents dans l'ordre par l'adresse.
```
Prev();
```
