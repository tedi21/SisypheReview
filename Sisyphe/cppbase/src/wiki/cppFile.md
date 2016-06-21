# CppFile
cppFile table represents a file.

# Référence
## Constructeur CppFile
*Paramètres*
* None.

*Description*
* Crée une instance de la classe CppFile.
```
var = new CppFile();
```

## Constructeur CppFile
*Paramètres*
* TextFile : La valeur de la colonne textFile.
* String : La valeur de la colonne path.
* String : La valeur de la colonne name.
* Numeric : La valeur de la colonne linesCount.

*Description*
* Crée une instance de la classe CppFile.
```
var = new CppFile(textFile, path, name, linesCount);
```

## Méthode Path
*Paramètres*
* None.

*Retour*
* String : La colonne path.

*Description*
* Retourne la colonne Path.
```
val = var.Path;
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

## Méthode LinesCount
*Paramètres*
* None.

*Retour*
* Numeric : La colonne linesCount.

*Description*
* Retourne la colonne LinesCount.
```
val = var.LinesCount;
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

## Méthode CppFileType
*Paramètres*
* None.

*Retour*
* CppFileType : La colonne cppFileType.

*Description*
* Retourne la colonne CppFileType.
```
cppFileType = var.CppFileType;
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

## Méthode Path
*Paramètres*
* String : La valeur de la colonne path.

*Retour*
* None.

*Description*
* Définit la colonne path.
```
var.Path(path);
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

## Méthode CppFileType
*Paramètres*
* CppFileType : La valeur de la colonne cppFileType.

*Retour*
* None.

*Description*
* Définit la colonne cppFileType.
```
var.CppFileType(cppFileType);
```

## Méthode LinesCount
*Paramètres*
* Numeric : La valeur de la colonne linesCount.

*Retour*
* None.

*Description*
* Définit la colonne linesCount.
```
var.LinesCount(linesCount);
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

## Méthode HasCppFileType
*Paramètres*
* None.

*Retour*
* Bool : Une valeur est définie pour la colonne cppFileType.

*Description*
* Indique si la colonne CppFileType a une valeur définie.
```
val = var.HasCppFileType;
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

## Méthode removeCppFileType
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime la valeur définie pour la colonne cppFileType.
```
var.CppFileType = null;
```

## Méthode removeCppDeclarationFunctions
*Paramètres*
* Numeric : La position de l'élément à supprimer dans la liste.

*Retour*
* None.

*Description*
* Supprime l'élément à la position *n* dans la liste de CppDeclarationFunctions.
```
var.CppDeclarationFunctions(0) = null;
```

## Méthode removeCppDefinitionFunctions
*Paramètres*
* Numeric : La position de l'élément à supprimer dans la liste.

*Retour*
* None.

*Description*
* Supprime l'élément à la position *n* dans la liste de CppDefinitionFunctions.
```
var.CppDefinitionFunctions(0) = null;
```

## Méthode removeCppIncludes
*Paramètres*
* Numeric : La position de l'élément à supprimer dans la liste.

*Retour*
* None.

*Description*
* Supprime l'élément à la position *n* dans la liste de CppIncludes.
```
var.CppIncludes(0) = null;
```

## Méthode removeCppClasss
*Paramètres*
* Numeric : La position de l'élément à supprimer dans la liste.

*Retour*
* None.

*Description*
* Supprime l'élément à la position *n* dans la liste de CppClasss.
```
var.CppClasss(0) = null;
```

## Méthode removeCppEnums
*Paramètres*
* Numeric : La position de l'élément à supprimer dans la liste.

*Retour*
* None.

*Description*
* Supprime l'élément à la position *n* dans la liste de CppEnums.
```
var.CppEnums(0) = null;
```

## Méthode removeCMacros
*Paramètres*
* Numeric : La position de l'élément à supprimer dans la liste.

*Retour*
* None.

*Description*
* Supprime l'élément à la position *n* dans la liste de CMacros.
```
var.CMacros(0) = null;
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

## Méthode CppDeclarationFunctions
*Paramètres*
* Numeric : La position de l'élément à insérer dans la liste.
* CppFunction : L'élément à insérer dans la liste.

*Retour*
* None.

*Description*
* Insère un élément à la position *n* dans la liste de CppDeclarationFunctions.
```
var.CppDeclarationFunctions(0) = cppDeclarationFunction;
```

## Méthode CppDefinitionFunctions
*Paramètres*
* Numeric : La position de l'élément à insérer dans la liste.
* CppFunction : L'élément à insérer dans la liste.

*Retour*
* None.

*Description*
* Insère un élément à la position *n* dans la liste de CppDefinitionFunctions.
```
var.CppDefinitionFunctions(0) = cppDefinitionFunction;
```

## Méthode CppIncludes
*Paramètres*
* Numeric : La position de l'élément à insérer dans la liste.
* CppInclude : L'élément à insérer dans la liste.

*Retour*
* None.

*Description*
* Insère un élément à la position *n* dans la liste de CppIncludes.
```
var.CppIncludes(0) = cppInclude;
```

## Méthode CppClasss
*Paramètres*
* Numeric : La position de l'élément à insérer dans la liste.
* CppClass : L'élément à insérer dans la liste.

*Retour*
* None.

*Description*
* Insère un élément à la position *n* dans la liste de CppClasss.
```
var.CppClasss(0) = cppClass;
```

## Méthode CppEnums
*Paramètres*
* Numeric : La position de l'élément à insérer dans la liste.
* CppEnum : L'élément à insérer dans la liste.

*Retour*
* None.

*Description*
* Insère un élément à la position *n* dans la liste de CppEnums.
```
var.CppEnums(0) = cppEnum;
```

## Méthode CMacros
*Paramètres*
* Numeric : La position de l'élément à insérer dans la liste.
* CMacro : L'élément à insérer dans la liste.

*Retour*
* None.

*Description*
* Insère un élément à la position *n* dans la liste de CMacros.
```
var.CMacros(0) = cMacro;
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

## Méthode CppDeclarationFunctions
*Paramètres*
* Numeric : La position de l'élément dans la liste.

*Retour*
* CppFunction : L'élément dans la liste.

*Description*
* Retourne l'élément à la position *n* dans la liste de CppDeclarationFunctions.
```
val = var.CppDeclarationFunctions(0);
```

## Méthode CppDefinitionFunctions
*Paramètres*
* Numeric : La position de l'élément dans la liste.

*Retour*
* CppFunction : L'élément dans la liste.

*Description*
* Retourne l'élément à la position *n* dans la liste de CppDefinitionFunctions.
```
val = var.CppDefinitionFunctions(0);
```

## Méthode CppIncludes
*Paramètres*
* Numeric : La position de l'élément dans la liste.

*Retour*
* CppInclude : L'élément dans la liste.

*Description*
* Retourne l'élément à la position *n* dans la liste de CppIncludes.
```
val = var.CppIncludes(0);
```

## Méthode CppClasss
*Paramètres*
* Numeric : La position de l'élément dans la liste.

*Retour*
* CppClass : L'élément dans la liste.

*Description*
* Retourne l'élément à la position *n* dans la liste de CppClasss.
```
val = var.CppClasss(0);
```

## Méthode CppEnums
*Paramètres*
* Numeric : La position de l'élément dans la liste.

*Retour*
* CppEnum : L'élément dans la liste.

*Description*
* Retourne l'élément à la position *n* dans la liste de CppEnums.
```
val = var.CppEnums(0);
```

## Méthode CMacros
*Paramètres*
* Numeric : La position de l'élément dans la liste.

*Retour*
* CMacro : L'élément dans la liste.

*Description*
* Retourne l'élément à la position *n* dans la liste de CMacros.
```
val = var.CMacros(0);
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

## Méthode ClearCppDeclarationFunctions
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime tous les éléments de liste.
```
var.ClearCppDeclarationFunctions();
```

## Méthode ClearCppDefinitionFunctions
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime tous les éléments de liste.
```
var.ClearCppDefinitionFunctions();
```

## Méthode ClearCppIncludes
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime tous les éléments de liste.
```
var.ClearCppIncludes();
```

## Méthode ClearCppClasss
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime tous les éléments de liste.
```
var.ClearCppClasss();
```

## Méthode ClearCppEnums
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime tous les éléments de liste.
```
var.ClearCppEnums();
```

## Méthode ClearCMacros
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime tous les éléments de liste.
```
var.ClearCMacros();
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

## Méthode HasCppDeclarationFunctions
*Paramètres*
* None.

*Retour*
* Bool : True si la liste n'est pas vide, False sinon.

*Description*
* Indique si la liste n'est pas vide.
```
val = var.HasCppDeclarationFunctions();
```

## Méthode HasCppDefinitionFunctions
*Paramètres*
* None.

*Retour*
* Bool : True si la liste n'est pas vide, False sinon.

*Description*
* Indique si la liste n'est pas vide.
```
val = var.HasCppDefinitionFunctions();
```

## Méthode HasCppIncludes
*Paramètres*
* None.

*Retour*
* Bool : True si la liste n'est pas vide, False sinon.

*Description*
* Indique si la liste n'est pas vide.
```
val = var.HasCppIncludes();
```

## Méthode HasCppClasss
*Paramètres*
* None.

*Retour*
* Bool : True si la liste n'est pas vide, False sinon.

*Description*
* Indique si la liste n'est pas vide.
```
val = var.HasCppClasss();
```

## Méthode HasCppEnums
*Paramètres*
* None.

*Retour*
* Bool : True si la liste n'est pas vide, False sinon.

*Description*
* Indique si la liste n'est pas vide.
```
val = var.HasCppEnums();
```

## Méthode HasCMacros
*Paramètres*
* None.

*Retour*
* Bool : True si la liste n'est pas vide, False sinon.

*Description*
* Indique si la liste n'est pas vide.
```
val = var.HasCMacros();
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

## Méthode CppDeclarationFunctionsCount
*Paramètres*
* None.

*Retour*
* Numeric : Le nombre d'éléments contenus dans la liste.

*Description*
* Retourne le nombre d'élément contenus dans la liste.
```
val = var.CppDeclarationFunctionsCount();
```

## Méthode CppDefinitionFunctionsCount
*Paramètres*
* None.

*Retour*
* Numeric : Le nombre d'éléments contenus dans la liste.

*Description*
* Retourne le nombre d'élément contenus dans la liste.
```
val = var.CppDefinitionFunctionsCount();
```

## Méthode CppIncludesCount
*Paramètres*
* None.

*Retour*
* Numeric : Le nombre d'éléments contenus dans la liste.

*Description*
* Retourne le nombre d'élément contenus dans la liste.
```
val = var.CppIncludesCount();
```

## Méthode CppClasssCount
*Paramètres*
* None.

*Retour*
* Numeric : Le nombre d'éléments contenus dans la liste.

*Description*
* Retourne le nombre d'élément contenus dans la liste.
```
val = var.CppClasssCount();
```

## Méthode CppEnumsCount
*Paramètres*
* None.

*Retour*
* Numeric : Le nombre d'éléments contenus dans la liste.

*Description*
* Retourne le nombre d'élément contenus dans la liste.
```
val = var.CppEnumsCount();
```

## Méthode CMacrosCount
*Paramètres*
* None.

*Retour*
* Numeric : Le nombre d'éléments contenus dans la liste.

*Description*
* Retourne le nombre d'élément contenus dans la liste.
```
val = var.CMacrosCount();
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
