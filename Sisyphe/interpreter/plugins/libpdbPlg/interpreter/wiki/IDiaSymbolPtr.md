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

## Méthode Get_undecoratedName
*Paramètres*
* String : 

*Retour*
* Numeric : 

*Description*
*  Extrait le 'undecorated' nom 
```
Get_undecoratedName();
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

## Méthode Get_locationType
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Retrieves the location type of a data symbol.
```
Get_locationType();
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

## Méthode Get_type
*Paramètres*
* IDiaSymbolPtr : 

*Retour*
* Numeric : 

*Description*
*  Récupère le symbole qui représente le type pour ce symbole.
```
Get_type();
```

## Méthode Get_constType
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Extrait une balise qui indique si le type de données défini par l'utilisateur est constante.
```
Get_constType();
```

## Méthode Get_dataKind
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  extrait la classification variable d'un symbole de données.
```
Get_dataKind();
```

## Méthode Get_constructor
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Extrait une balise qui indique si le type de données défini par l'utilisateur possède un constructeur ou un destructeur.
```
Get_constructor();
```

## Méthode Get_baseType
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Récupère le type de base pour ce symbole.
```
Get_baseType();
```

## Méthode Get_volatileType
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Extrait une balise qui indique si le type de données défini par (UDT) l'utilisateur est volatile.
```
Get_volatileType();
```

## Méthode Get_virtual
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  extrait une balise qui spécifie si la fonction est virtuelle.
```
Get_virtual();
```

## Méthode Get_isStatic
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Extrait une balise qui spécifie si la fonction ou la couche de conversion de code a été marquée comme static.
```
Get_isStatic();
```

## Méthode Get_isReturnValue
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Spécifie si la variable distribue une valeur de retour.
```
Get_isReturnValue();
```

## Méthode Get_symTag
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Récupère le classifieur de type de symbole.
```
Get_symTag();
```

## Méthode Get_length
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Récupère le nombre de bits ou d'octets de mémoire utilisés par l'objet représenté par ce symbole.
```
Get_length();
```

## Méthode Get_reference
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  extrait une balise qui spécifie si un type pointeur est une référence.
```
Get_reference();
```

## Méthode Get_rank
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Récupère le rang (nombre de dimensions) d'un tableau multidimensionnel FORTRAN.
```
Get_rank();
```

## Méthode Get_lowerBound
*Paramètres*
* IDiaSymbolPtr : 

*Retour*
* Numeric : 

*Description*
*  Extrait la limite inférieure d'une dimension de tableau FORTRAN.
```
Get_lowerBound();
```

## Méthode Get_upperBound
*Paramètres*
* IDiaSymbolPtr : 

*Retour*
* Numeric : 

*Description*
*  Récupère un symbole représentant la limite supérieure d'une dimension de tableau FORTRAN.
```
Get_upperBound();
```

## Méthode Get_oemId
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Récupère la valeur du fabricant d'ordinateurs (OEM) OEM du symbole.
```
Get_oemId();
```

## Méthode Get_oemSymbolId
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Récupère la valeur (OEM) du symbole de fabricant d'ordinateurs OEM.
```
Get_oemSymbolId();
```

## Méthode Get_types
*Paramètres*
* IDiaSymbolPtr : 

*Retour*
* Numeric : 

*Description*
*  Récupère un tableau de types de compilateur-détail pour ce symbole.
```
Get_types();
```

## Méthode Get_dataBytes
*Paramètres*
* Numeric : 
* Numeric : 
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Récupère les octets de données d'un symbole OEM.
```
Get_dataBytes();
```

## Méthode Get_udtKind
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Extrait le dossier fichiers divers un type défini par l' (UDT)utilisateur.
```
Get_udtKind();
```

## Méthode Get_noReturn
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Retrieves a flag that specifies whether the function has been marked as never returning with the noreturn attribute.
```
Get_noReturn();
```

## Méthode Get_offset
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Retrieves the offset of the symbol location. Use when the LocationType is LocIsRegRel or LocIsBitField.
```
Get_offset();
```

## Méthode Get_lexicalParent
*Paramètres*
* IDiaSymbolPtr : 

*Retour*
* Numeric : 

*Description*
*  Extrait une référence au parent lexicale du symbole.
```
Get_lexicalParent();
```

## Méthode Get_classParent
*Paramètres*
* IDiaSymbolPtr : 

*Retour*
* Numeric : 

*Description*
*  Extrait une référence au parent de classe du symbole.
```
Get_classParent();
```
