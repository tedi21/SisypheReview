# DebugFileInfo
debugFileInfo table represents file information for debug.

# Référence
## Constructeur DebugFileInfo
*Paramètres*
* None.

*Description*
* Crée une instance de la classe DebugFileInfo.
```
var = new DebugFileInfo();
```

## Constructeur DebugFileInfo
*Paramètres*
* String : La valeur de la colonne name.
* String : La valeur de la colonne compilandPath.
* Array[Numeric] : La valeur de la colonne checksum.

*Description*
* Crée une instance de la classe DebugFileInfo.
```
var = new DebugFileInfo(name, compilandPath, checksum);
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

## Méthode CompilandPath
*Paramètres*
* None.

*Retour*
* String : La colonne compilandPath.

*Description*
* Retourne la colonne CompilandPath.
```
val = var.CompilandPath;
```

## Méthode Checksum
*Paramètres*
* None.

*Retour*
* Array[Numeric] : La colonne checksum.

*Description*
* Retourne la colonne Checksum.
```
val = var.Checksum;
```

## Méthode TextFile
*Paramètres*
* None.

*Retour*
* TextFile : La colonne textFile.

*Description*
* Retourne la colonne TextFile.
```
textFile = var.TextFile;
```

## Méthode TextFile
*Paramètres*
* TextFile : La valeur de la colonne textFile.

*Retour*
* None.

*Description*
* Définit la colonne textFile.
```
var.TextFile(textFile);
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

## Méthode CompilandPath
*Paramètres*
* String : La valeur de la colonne compilandPath.

*Retour*
* None.

*Description*
* Définit la colonne compilandPath.
```
var.CompilandPath(compilandPath);
```

## Méthode Checksum
*Paramètres*
* Array[Numeric] : La valeur de la colonne checksum.

*Retour*
* None.

*Description*
* Définit la colonne checksum.
```
var.Checksum(checksum);
```

## Méthode HasTextFile
*Paramètres*
* None.

*Retour*
* Bool : Une valeur est définie pour la colonne textFile.

*Description*
* Indique si la colonne TextFile a une valeur définie.
```
val = var.HasTextFile;
```

## Méthode removeTextFile
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime la valeur définie pour la colonne textFile.
```
var.TextFile = null;
```

## Méthode removeDebugFunctionInfos
*Paramètres*
* Numeric : La position de l'élément à supprimer dans la liste.

*Retour*
* None.

*Description*
* Supprime l'élément à la position *n* dans la liste de DebugFunctionInfos.
```
var.DebugFunctionInfos(0) = null;
```

## Méthode removeDebugStubInfos
*Paramètres*
* Numeric : La position de l'élément à supprimer dans la liste.

*Retour*
* None.

*Description*
* Supprime l'élément à la position *n* dans la liste de DebugStubInfos.
```
var.DebugStubInfos(0) = null;
```

## Méthode DebugFunctionInfos
*Paramètres*
* Numeric : La position de l'élément à insérer dans la liste.
* DebugFunctionInfo : L'élément à insérer dans la liste.

*Retour*
* None.

*Description*
* Insère un élément à la position *n* dans la liste de DebugFunctionInfos.
```
var.DebugFunctionInfos(0) = debugFunctionInfo;
```

## Méthode DebugStubInfos
*Paramètres*
* Numeric : La position de l'élément à insérer dans la liste.
* DebugStubInfo : L'élément à insérer dans la liste.

*Retour*
* None.

*Description*
* Insère un élément à la position *n* dans la liste de DebugStubInfos.
```
var.DebugStubInfos(0) = debugStubInfo;
```

## Méthode DebugFunctionInfos
*Paramètres*
* Numeric : La position de l'élément dans la liste.

*Retour*
* DebugFunctionInfo : L'élément dans la liste.

*Description*
* Retourne l'élément à la position *n* dans la liste de DebugFunctionInfos.
```
val = var.DebugFunctionInfos(0);
```

## Méthode DebugStubInfos
*Paramètres*
* Numeric : La position de l'élément dans la liste.

*Retour*
* DebugStubInfo : L'élément dans la liste.

*Description*
* Retourne l'élément à la position *n* dans la liste de DebugStubInfos.
```
val = var.DebugStubInfos(0);
```

## Méthode ClearDebugFunctionInfos
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime tous les éléments de liste.
```
var.ClearDebugFunctionInfos();
```

## Méthode ClearDebugStubInfos
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime tous les éléments de liste.
```
var.ClearDebugStubInfos();
```

## Méthode HasDebugFunctionInfos
*Paramètres*
* None.

*Retour*
* Bool : True si la liste n'est pas vide, False sinon.

*Description*
* Indique si la liste n'est pas vide.
```
val = var.HasDebugFunctionInfos();
```

## Méthode HasDebugStubInfos
*Paramètres*
* None.

*Retour*
* Bool : True si la liste n'est pas vide, False sinon.

*Description*
* Indique si la liste n'est pas vide.
```
val = var.HasDebugStubInfos();
```

## Méthode DebugFunctionInfosCount
*Paramètres*
* None.

*Retour*
* Numeric : Le nombre d'éléments contenus dans la liste.

*Description*
* Retourne le nombre d'élément contenus dans la liste.
```
val = var.DebugFunctionInfosCount();
```

## Méthode DebugStubInfosCount
*Paramètres*
* None.

*Retour*
* Numeric : Le nombre d'éléments contenus dans la liste.

*Description*
* Retourne le nombre d'élément contenus dans la liste.
```
val = var.DebugStubInfosCount();
```
