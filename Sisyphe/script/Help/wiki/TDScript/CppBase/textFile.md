# TextFile
Creation Virtual Table________________Table using FTS4 describes data type for source generation. These information are not used by sqlite.textFile table represents a text file

# Référence
## Constructeur TextFile
*Paramètres*
* None.

*Description*
* Crée une instance de la classe TextFile.
```
var = new TextFile();
```

## Constructeur TextFile
*Paramètres*
* String : La valeur de la colonne content.

*Description*
* Crée une instance de la classe TextFile.
```
var = new TextFile(content);
```

## Méthode Rowid
*Paramètres*
* None.

*Retour*
* Numeric : La colonne rowid.

*Description*
* Retourne la colonne Rowid.
```
val = var.Rowid;
```

## Méthode Content
*Paramètres*
* None.

*Retour*
* String : La colonne content.

*Description*
* Retourne la colonne Content.
```
val = var.Content;
```

## Méthode Content
*Paramètres*
* String : La valeur de la colonne content.

*Retour*
* None.

*Description*
* Définit la colonne content.
```
var.Content(content);
```

## Méthode removeCppFiles
*Paramètres*
* Numeric : La position de l'élément à supprimer dans la liste.

*Retour*
* None.

*Description*
* Supprime l'élément à la position *n* dans la liste de CppFiles.
```
var.CppFiles(0) = null;
```

## Méthode removeDebugFileInfos
*Paramètres*
* Numeric : La position de l'élément à supprimer dans la liste.

*Retour*
* None.

*Description*
* Supprime l'élément à la position *n* dans la liste de DebugFileInfos.
```
var.DebugFileInfos(0) = null;
```

## Méthode CppFiles
*Paramètres*
* Numeric : La position de l'élément à insérer dans la liste.
* CppFile : L'élément à insérer dans la liste.

*Retour*
* None.

*Description*
* Insère un élément à la position *n* dans la liste de CppFiles.
```
var.CppFiles(0) = cppFile;
```

## Méthode DebugFileInfos
*Paramètres*
* Numeric : La position de l'élément à insérer dans la liste.
* DebugFileInfo : L'élément à insérer dans la liste.

*Retour*
* None.

*Description*
* Insère un élément à la position *n* dans la liste de DebugFileInfos.
```
var.DebugFileInfos(0) = debugFileInfo;
```

## Méthode CppFiles
*Paramètres*
* Numeric : La position de l'élément dans la liste.

*Retour*
* CppFile : L'élément dans la liste.

*Description*
* Retourne l'élément à la position *n* dans la liste de CppFiles.
```
val = var.CppFiles(0);
```

## Méthode DebugFileInfos
*Paramètres*
* Numeric : La position de l'élément dans la liste.

*Retour*
* DebugFileInfo : L'élément dans la liste.

*Description*
* Retourne l'élément à la position *n* dans la liste de DebugFileInfos.
```
val = var.DebugFileInfos(0);
```

## Méthode ClearCppFiles
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime tous les éléments de liste.
```
var.ClearCppFiles();
```

## Méthode ClearDebugFileInfos
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime tous les éléments de liste.
```
var.ClearDebugFileInfos();
```

## Méthode HasCppFiles
*Paramètres*
* None.

*Retour*
* Bool : True si la liste n'est pas vide, False sinon.

*Description*
* Indique si la liste n'est pas vide.
```
val = var.HasCppFiles();
```

## Méthode HasDebugFileInfos
*Paramètres*
* None.

*Retour*
* Bool : True si la liste n'est pas vide, False sinon.

*Description*
* Indique si la liste n'est pas vide.
```
val = var.HasDebugFileInfos();
```

## Méthode CppFilesCount
*Paramètres*
* None.

*Retour*
* Numeric : Le nombre d'éléments contenus dans la liste.

*Description*
* Retourne le nombre d'élément contenus dans la liste.
```
val = var.CppFilesCount();
```

## Méthode DebugFileInfosCount
*Paramètres*
* None.

*Retour*
* Numeric : Le nombre d'éléments contenus dans la liste.

*Description*
* Retourne le nombre d'élément contenus dans la liste.
```
val = var.DebugFileInfosCount();
```
