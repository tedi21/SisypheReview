# CppEnum
cppEnum table represents an enumeration.

# Référence
## Constructeur CppEnum
*Paramètres*
* None.

*Description*
* Crée une instance de la classe CppEnum.
```
var = new CppEnum();
```

## Constructeur CppEnum
*Paramètres*
* String : La valeur de la colonne name.
* Numeric : La valeur de la colonne lineNumber.
* Numeric : La valeur de la colonne startBlock.
* Numeric : La valeur de la colonne lengthBlock.

*Description*
* Crée une instance de la classe CppEnum.
```
var = new CppEnum(name, lineNumber, startBlock, lengthBlock);
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

## Méthode StartBlock
*Paramètres*
* None.

*Retour*
* Numeric : La colonne startBlock.

*Description*
* Retourne la colonne StartBlock.
```
val = var.StartBlock;
```

## Méthode LengthBlock
*Paramètres*
* None.

*Retour*
* Numeric : La colonne lengthBlock.

*Description*
* Retourne la colonne LengthBlock.
```
val = var.LengthBlock;
```

## Méthode CppFile
*Paramètres*
* None.

*Retour*
* CppFile : La colonne cppFile.

*Description*
* Retourne la colonne CppFile.
```
cppFile = var.CppFile;
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

## Méthode CppFile
*Paramètres*
* CppFile : La valeur de la colonne cppFile.

*Retour*
* None.

*Description*
* Définit la colonne cppFile.
```
var.CppFile(cppFile);
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

## Méthode StartBlock
*Paramètres*
* Numeric : La valeur de la colonne startBlock.

*Retour*
* None.

*Description*
* Définit la colonne startBlock.
```
var.StartBlock(startBlock);
```

## Méthode LengthBlock
*Paramètres*
* Numeric : La valeur de la colonne lengthBlock.

*Retour*
* None.

*Description*
* Définit la colonne lengthBlock.
```
var.LengthBlock(lengthBlock);
```

## Méthode HasCppFile
*Paramètres*
* None.

*Retour*
* Bool : Une valeur est définie pour la colonne cppFile.

*Description*
* Indique si la colonne CppFile a une valeur définie.
```
val = var.HasCppFile;
```

## Méthode removeCppFile
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime la valeur définie pour la colonne cppFile.
```
var.CppFile = null;
```

## Méthode removeCppEnumConstants
*Paramètres*
* Numeric : La position de l'élément à supprimer dans la liste.

*Retour*
* None.

*Description*
* Supprime l'élément à la position *n* dans la liste de CppEnumConstants.
```
var.CppEnumConstants(0) = null;
```

## Méthode CppEnumConstants
*Paramètres*
* Numeric : La position de l'élément à insérer dans la liste.
* CppEnumConstant : L'élément à insérer dans la liste.

*Retour*
* None.

*Description*
* Insère un élément à la position *n* dans la liste de CppEnumConstants.
```
var.CppEnumConstants(0) = cppEnumConstant;
```

## Méthode CppEnumConstants
*Paramètres*
* Numeric : La position de l'élément dans la liste.

*Retour*
* CppEnumConstant : L'élément dans la liste.

*Description*
* Retourne l'élément à la position *n* dans la liste de CppEnumConstants.
```
val = var.CppEnumConstants(0);
```

## Méthode ClearCppEnumConstants
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime tous les éléments de liste.
```
var.ClearCppEnumConstants();
```

## Méthode HasCppEnumConstants
*Paramètres*
* None.

*Retour*
* Bool : True si la liste n'est pas vide, False sinon.

*Description*
* Indique si la liste n'est pas vide.
```
val = var.HasCppEnumConstants();
```

## Méthode CppEnumConstantsCount
*Paramètres*
* None.

*Retour*
* Numeric : Le nombre d'éléments contenus dans la liste.

*Description*
* Retourne le nombre d'élément contenus dans la liste.
```
val = var.CppEnumConstantsCount();
```
