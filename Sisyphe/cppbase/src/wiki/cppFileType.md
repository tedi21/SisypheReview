# CppFileType
cppFileType table represents a type of file : header or source.

# Référence
## Constructeur CppFileType
*Paramètres*
* None.

*Description*
* Crée une instance de la classe CppFileType.
```
var = new CppFileType();
```

## Constructeur CppFileType
*Paramètres*
* String : La valeur de la colonne string.

*Description*
* Crée une instance de la classe CppFileType.
```
var = new CppFileType(string);
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

## Méthode String
*Paramètres*
* None.

*Retour*
* String : La colonne string.

*Description*
* Retourne la colonne String.
```
val = var.String;
```

## Méthode String
*Paramètres*
* String : La valeur de la colonne string.

*Retour*
* None.

*Description*
* Définit la colonne string.
```
var.String(string);
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
