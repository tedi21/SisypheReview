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
* String : La valeur de la colonne path.
* String : La valeur de la colonne name.
* Numeric : La valeur de la colonne linesCount.
* Numeric : La valeur de la colonne hash.
* Numeric : La valeur de la colonne analyzed.

*Description*
* Crée une instance de la classe CppFile.
```
var = new CppFile(path, name, linesCount, hash, analyzed);
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

## Méthode Hash
*Paramètres*
* None.

*Retour*
* Numeric : La colonne hash.

*Description*
* Retourne la colonne Hash.
```
val = var.Hash;
```

## Méthode Analyzed
*Paramètres*
* None.

*Retour*
* Numeric : La colonne analyzed.

*Description*
* Retourne la colonne Analyzed.
```
val = var.Analyzed;
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

## Méthode Hash
*Paramètres*
* Numeric : La valeur de la colonne hash.

*Retour*
* None.

*Description*
* Définit la colonne hash.
```
var.Hash(hash);
```

## Méthode Analyzed
*Paramètres*
* Numeric : La valeur de la colonne analyzed.

*Retour*
* None.

*Description*
* Définit la colonne analyzed.
```
var.Analyzed(analyzed);
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

## Méthode removeCppVariables
*Paramètres*
* Numeric : La position de l'élément à supprimer dans la liste.

*Retour*
* None.

*Description*
* Supprime l'élément à la position *n* dans la liste de CppVariables.
```
var.CppVariables(0) = null;
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

## Méthode removeCppNotices
*Paramètres*
* Numeric : La position de l'élément à supprimer dans la liste.

*Retour*
* None.

*Description*
* Supprime l'élément à la position *n* dans la liste de CppNotices.
```
var.CppNotices(0) = null;
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

## Méthode CppVariables
*Paramètres*
* Numeric : La position de l'élément à insérer dans la liste.
* CppVariable : L'élément à insérer dans la liste.

*Retour*
* None.

*Description*
* Insère un élément à la position *n* dans la liste de CppVariables.
```
var.CppVariables(0) = cppVariable;
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

## Méthode CppNotices
*Paramètres*
* Numeric : La position de l'élément à insérer dans la liste.
* CppNotice : L'élément à insérer dans la liste.

*Retour*
* None.

*Description*
* Insère un élément à la position *n* dans la liste de CppNotices.
```
var.CppNotices(0) = cppNotice;
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

## Méthode CppVariables
*Paramètres*
* Numeric : La position de l'élément dans la liste.

*Retour*
* CppVariable : L'élément dans la liste.

*Description*
* Retourne l'élément à la position *n* dans la liste de CppVariables.
```
val = var.CppVariables(0);
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

## Méthode CppNotices
*Paramètres*
* Numeric : La position de l'élément dans la liste.

*Retour*
* CppNotice : L'élément dans la liste.

*Description*
* Retourne l'élément à la position *n* dans la liste de CppNotices.
```
val = var.CppNotices(0);
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

## Méthode ClearCppVariables
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime tous les éléments de liste.
```
var.ClearCppVariables();
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

## Méthode ClearCppNotices
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime tous les éléments de liste.
```
var.ClearCppNotices();
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

## Méthode HasCppVariables
*Paramètres*
* None.

*Retour*
* Bool : True si la liste n'est pas vide, False sinon.

*Description*
* Indique si la liste n'est pas vide.
```
val = var.HasCppVariables();
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

## Méthode HasCppNotices
*Paramètres*
* None.

*Retour*
* Bool : True si la liste n'est pas vide, False sinon.

*Description*
* Indique si la liste n'est pas vide.
```
val = var.HasCppNotices();
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

## Méthode CppVariablesCount
*Paramètres*
* None.

*Retour*
* Numeric : Le nombre d'éléments contenus dans la liste.

*Description*
* Retourne le nombre d'élément contenus dans la liste.
```
val = var.CppVariablesCount();
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

## Méthode CppNoticesCount
*Paramètres*
* None.

*Retour*
* Numeric : Le nombre d'éléments contenus dans la liste.

*Description*
* Retourne le nombre d'élément contenus dans la liste.
```
val = var.CppNoticesCount();
```
