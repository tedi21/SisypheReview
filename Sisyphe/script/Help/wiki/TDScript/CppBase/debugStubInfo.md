# DebugStubInfo
debugStubInfo table represents stub information for debug.

# Référence
## Constructeur DebugStubInfo
*Paramètres*
* None.

*Description*
* Crée une instance de la classe DebugStubInfo.
```
var = new DebugStubInfo();
```

## Constructeur DebugStubInfo
*Paramètres*
* Numeric : La valeur de la colonne lineNumber.
* Numeric : La valeur de la colonne isLineSkipped.

*Description*
* Crée une instance de la classe DebugStubInfo.
```
var = new DebugStubInfo(lineNumber, isLineSkipped);
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

## Méthode LineNumber
*Paramètres*
* None.

*Retour*
* Numeric : La colonne lineNumber.

*Description*
* Retourne la colonne LineNumber.
```
val = var.LineNumber;
```

## Méthode IsLineSkipped
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isLineSkipped.

*Description*
* Retourne la colonne IsLineSkipped.
```
val = var.IsLineSkipped;
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

## Méthode LineNumber
*Paramètres*
* Numeric : La valeur de la colonne lineNumber.

*Retour*
* None.

*Description*
* Définit la colonne lineNumber.
```
var.LineNumber(lineNumber);
```

## Méthode IsLineSkipped
*Paramètres*
* Numeric : La valeur de la colonne isLineSkipped.

*Retour*
* None.

*Description*
* Définit la colonne isLineSkipped.
```
var.IsLineSkipped(isLineSkipped);
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

## Méthode removeDebugValueInfos
*Paramètres*
* Numeric : La position de l'élément à supprimer dans la liste.

*Retour*
* None.

*Description*
* Supprime l'élément à la position *n* dans la liste de DebugValueInfos.
```
var.DebugValueInfos(0) = null;
```

## Méthode DebugValueInfos
*Paramètres*
* Numeric : La position de l'élément à insérer dans la liste.
* DebugValueInfo : L'élément à insérer dans la liste.

*Retour*
* None.

*Description*
* Insère un élément à la position *n* dans la liste de DebugValueInfos.
```
var.DebugValueInfos(0) = debugValueInfo;
```

## Méthode DebugValueInfos
*Paramètres*
* Numeric : La position de l'élément dans la liste.

*Retour*
* DebugValueInfo : L'élément dans la liste.

*Description*
* Retourne l'élément à la position *n* dans la liste de DebugValueInfos.
```
val = var.DebugValueInfos(0);
```

## Méthode ClearDebugValueInfos
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime tous les éléments de liste.
```
var.ClearDebugValueInfos();
```

## Méthode HasDebugValueInfos
*Paramètres*
* None.

*Retour*
* Bool : True si la liste n'est pas vide, False sinon.

*Description*
* Indique si la liste n'est pas vide.
```
val = var.HasDebugValueInfos();
```

## Méthode DebugValueInfosCount
*Paramètres*
* None.

*Retour*
* Numeric : Le nombre d'éléments contenus dans la liste.

*Description*
* Retourne le nombre d'élément contenus dans la liste.
```
val = var.DebugValueInfosCount();
```
