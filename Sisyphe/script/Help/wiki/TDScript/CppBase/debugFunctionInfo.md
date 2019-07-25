# DebugFunctionInfo
debugFunctionInfo table represents function information for debug.

# Référence
## Constructeur DebugFunctionInfo
*Paramètres*
* None.

*Description*
* Crée une instance de la classe DebugFunctionInfo.
```
var = new DebugFunctionInfo();
```

## Constructeur DebugFunctionInfo
*Paramètres*
* String : La valeur de la colonne name.
* Numeric : La valeur de la colonne firstLineNumber.
* Numeric : La valeur de la colonne lastLineNumber.
* Numeric : La valeur de la colonne address.

*Description*
* Crée une instance de la classe DebugFunctionInfo.
```
var = new DebugFunctionInfo(name, firstLineNumber, lastLineNumber, address);
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

## Méthode Name
*Paramètres*
* None.

*Retour*
* String : La colonne name.

*Description*
* Retourne la colonne Name.
```
val = var.Name;
```

## Méthode FirstLineNumber
*Paramètres*
* None.

*Retour*
* Numeric : La colonne firstLineNumber.

*Description*
* Retourne la colonne FirstLineNumber.
```
val = var.FirstLineNumber;
```

## Méthode LastLineNumber
*Paramètres*
* None.

*Retour*
* Numeric : La colonne lastLineNumber.

*Description*
* Retourne la colonne LastLineNumber.
```
val = var.LastLineNumber;
```

## Méthode Address
*Paramètres*
* None.

*Retour*
* Numeric : La colonne address.

*Description*
* Retourne la colonne Address.
```
val = var.Address;
```

## Méthode DebugTypeInfo
*Paramètres*
* None.

*Retour*
* DebugTypeInfo : La colonne debugTypeInfo.

*Description*
* Retourne la colonne DebugTypeInfo.
```
debugTypeInfo = var.DebugTypeInfo;
```

## Méthode DebugFileInfo
*Paramètres*
* None.

*Retour*
* DebugFileInfo : La colonne debugFileInfo.

*Description*
* Retourne la colonne DebugFileInfo.
```
debugFileInfo = var.DebugFileInfo;
```

## Méthode Name
*Paramètres*
* String : La valeur de la colonne name.

*Retour*
* None.

*Description*
* Définit la colonne name.
```
var.Name(name);
```

## Méthode FirstLineNumber
*Paramètres*
* Numeric : La valeur de la colonne firstLineNumber.

*Retour*
* None.

*Description*
* Définit la colonne firstLineNumber.
```
var.FirstLineNumber(firstLineNumber);
```

## Méthode LastLineNumber
*Paramètres*
* Numeric : La valeur de la colonne lastLineNumber.

*Retour*
* None.

*Description*
* Définit la colonne lastLineNumber.
```
var.LastLineNumber(lastLineNumber);
```

## Méthode Address
*Paramètres*
* Numeric : La valeur de la colonne address.

*Retour*
* None.

*Description*
* Définit la colonne address.
```
var.Address(address);
```

## Méthode DebugTypeInfo
*Paramètres*
* DebugTypeInfo : La valeur de la colonne debugTypeInfo.

*Retour*
* None.

*Description*
* Définit la colonne debugTypeInfo.
```
var.DebugTypeInfo(debugTypeInfo);
```

## Méthode DebugFileInfo
*Paramètres*
* DebugFileInfo : La valeur de la colonne debugFileInfo.

*Retour*
* None.

*Description*
* Définit la colonne debugFileInfo.
```
var.DebugFileInfo(debugFileInfo);
```

## Méthode HasDebugTypeInfo
*Paramètres*
* None.

*Retour*
* Bool : Une valeur est définie pour la colonne debugTypeInfo.

*Description*
* Indique si la colonne DebugTypeInfo a une valeur définie.
```
val = var.HasDebugTypeInfo;
```

## Méthode HasDebugFileInfo
*Paramètres*
* None.

*Retour*
* Bool : Une valeur est définie pour la colonne debugFileInfo.

*Description*
* Indique si la colonne DebugFileInfo a une valeur définie.
```
val = var.HasDebugFileInfo;
```

## Méthode removeDebugTypeInfo
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime la valeur définie pour la colonne debugTypeInfo.
```
var.DebugTypeInfo = null;
```

## Méthode removeDebugFileInfo
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime la valeur définie pour la colonne debugFileInfo.
```
var.DebugFileInfo = null;
```

## Méthode removeDebugVariableInfos
*Paramètres*
* Numeric : La position de l'élément à supprimer dans la liste.

*Retour*
* None.

*Description*
* Supprime l'élément à la position *n* dans la liste de DebugVariableInfos.
```
var.DebugVariableInfos(0) = null;
```

## Méthode DebugVariableInfos
*Paramètres*
* Numeric : La position de l'élément à insérer dans la liste.
* DebugVariableInfo : L'élément à insérer dans la liste.

*Retour*
* None.

*Description*
* Insère un élément à la position *n* dans la liste de DebugVariableInfos.
```
var.DebugVariableInfos(0) = debugVariableInfo;
```

## Méthode DebugVariableInfos
*Paramètres*
* Numeric : La position de l'élément dans la liste.

*Retour*
* DebugVariableInfo : L'élément dans la liste.

*Description*
* Retourne l'élément à la position *n* dans la liste de DebugVariableInfos.
```
val = var.DebugVariableInfos(0);
```

## Méthode ClearDebugVariableInfos
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime tous les éléments de liste.
```
var.ClearDebugVariableInfos();
```

## Méthode HasDebugVariableInfos
*Paramètres*
* None.

*Retour*
* Bool : True si la liste n'est pas vide, False sinon.

*Description*
* Indique si la liste n'est pas vide.
```
val = var.HasDebugVariableInfos();
```

## Méthode DebugVariableInfosCount
*Paramètres*
* None.

*Retour*
* Numeric : Le nombre d'éléments contenus dans la liste.

*Description*
* Retourne le nombre d'élément contenus dans la liste.
```
val = var.DebugVariableInfosCount();
```
