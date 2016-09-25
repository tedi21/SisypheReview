# IDiaSymbolPtr
 Classe représentant un symbole.

# Référence
## Méthode FindChildren
*Paramètres*
* SymTagEnumType : 
* String : 
* Numeric : 
* IDiaEnumSymbolsPtr : 

*Retour*
* Numeric : 

*Description*
*  Récupère les enfants du symbole.
```
FindChildren();
```

## Méthode FindChildren
*Paramètres*
* SymTagEnumType : 
* IDiaEnumSymbolsPtr : 

*Retour*
* Numeric : 

*Description*
*  Récupère les enfants du symbole.
```
FindChildren();
```

## Méthode Get_name
*Paramètres*
* String : 

*Retour*
* Numeric : 

*Description*
*  Extrait le nom du symbole.
```
Get_name();
```

## Méthode Get_addressSection
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Extrait la partie de section d'un emplacement d'adresse.
```
Get_addressSection();
```

## Méthode Get_addressOffset
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Extrait la partie d'offset à un emplacement d'adresse.
```
Get_addressOffset();
```

## Méthode Get_relativeVirtualAddress
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Récupère l'adresse virtuelle relative (RVA) du symbole.
```
Get_relativeVirtualAddress();
```
