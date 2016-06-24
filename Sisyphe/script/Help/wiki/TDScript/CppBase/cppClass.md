# CppClass
cppClass table represents a class.

# Référence
## Constructeur CppClass
*Paramètres*
* None.

*Description*
* Crée une instance de la classe CppClass.
```
var = new CppClass();
```

## Constructeur CppClass
*Paramètres*
* String : La valeur de la colonne name.
* Numeric : La valeur de la colonne isStruct.
* Numeric : La valeur de la colonne isInterface.
* Numeric : La valeur de la colonne isAbstract.
* Numeric : La valeur de la colonne linesCount.
* Numeric : La valeur de la colonne lineNumber.
* Numeric : La valeur de la colonne startBlock.
* Numeric : La valeur de la colonne lengthBlock.

*Description*
* Crée une instance de la classe CppClass.
```
var = new CppClass(name, isStruct, isInterface, isAbstract, linesCount, lineNumber, startBlock, lengthBlock);
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

## Méthode IsStruct
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isStruct.

*Description*
* Retourne la colonne IsStruct.
```
val = var.IsStruct;
```

## Méthode IsInterface
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isInterface.

*Description*
* Retourne la colonne IsInterface.
```
val = var.IsInterface;
```

## Méthode IsAbstract
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isAbstract.

*Description*
* Retourne la colonne IsAbstract.
```
val = var.IsAbstract;
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

## Méthode IsStruct
*Paramètres*
* Numeric : La valeur de la colonne isStruct.

*Retour*
* None.

*Description*
* Définit la colonne isStruct.
```
var.IsStruct(isStruct);
```

## Méthode IsInterface
*Paramètres*
* Numeric : La valeur de la colonne isInterface.

*Retour*
* None.

*Description*
* Définit la colonne isInterface.
```
var.IsInterface(isInterface);
```

## Méthode IsAbstract
*Paramètres*
* Numeric : La valeur de la colonne isAbstract.

*Retour*
* None.

*Description*
* Définit la colonne isAbstract.
```
var.IsAbstract(isAbstract);
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

## Méthode removeCppInheritances
*Paramètres*
* Numeric : La position de l'élément à supprimer dans la liste.

*Retour*
* None.

*Description*
* Supprime l'élément à la position *n* dans la liste de CppInheritances.
```
var.CppInheritances(0) = null;
```

## Méthode removeCppFunctions
*Paramètres*
* Numeric : La position de l'élément à supprimer dans la liste.

*Retour*
* None.

*Description*
* Supprime l'élément à la position *n* dans la liste de CppFunctions.
```
var.CppFunctions(0) = null;
```

## Méthode removeCppAttributes
*Paramètres*
* Numeric : La position de l'élément à supprimer dans la liste.

*Retour*
* None.

*Description*
* Supprime l'élément à la position *n* dans la liste de CppAttributes.
```
var.CppAttributes(0) = null;
```

## Méthode CppInheritances
*Paramètres*
* Numeric : La position de l'élément à insérer dans la liste.
* CppInheritance : L'élément à insérer dans la liste.

*Retour*
* None.

*Description*
* Insère un élément à la position *n* dans la liste de CppInheritances.
```
var.CppInheritances(0) = cppInheritance;
```

## Méthode CppFunctions
*Paramètres*
* Numeric : La position de l'élément à insérer dans la liste.
* CppFunction : L'élément à insérer dans la liste.

*Retour*
* None.

*Description*
* Insère un élément à la position *n* dans la liste de CppFunctions.
```
var.CppFunctions(0) = cppFunction;
```

## Méthode CppAttributes
*Paramètres*
* Numeric : La position de l'élément à insérer dans la liste.
* CppAttribute : L'élément à insérer dans la liste.

*Retour*
* None.

*Description*
* Insère un élément à la position *n* dans la liste de CppAttributes.
```
var.CppAttributes(0) = cppAttribute;
```

## Méthode CppInheritances
*Paramètres*
* Numeric : La position de l'élément dans la liste.

*Retour*
* CppInheritance : L'élément dans la liste.

*Description*
* Retourne l'élément à la position *n* dans la liste de CppInheritances.
```
val = var.CppInheritances(0);
```

## Méthode CppFunctions
*Paramètres*
* Numeric : La position de l'élément dans la liste.

*Retour*
* CppFunction : L'élément dans la liste.

*Description*
* Retourne l'élément à la position *n* dans la liste de CppFunctions.
```
val = var.CppFunctions(0);
```

## Méthode CppAttributes
*Paramètres*
* Numeric : La position de l'élément dans la liste.

*Retour*
* CppAttribute : L'élément dans la liste.

*Description*
* Retourne l'élément à la position *n* dans la liste de CppAttributes.
```
val = var.CppAttributes(0);
```

## Méthode ClearCppInheritances
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime tous les éléments de liste.
```
var.ClearCppInheritances();
```

## Méthode ClearCppFunctions
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime tous les éléments de liste.
```
var.ClearCppFunctions();
```

## Méthode ClearCppAttributes
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime tous les éléments de liste.
```
var.ClearCppAttributes();
```

## Méthode HasCppInheritances
*Paramètres*
* None.

*Retour*
* Bool : True si la liste n'est pas vide, False sinon.

*Description*
* Indique si la liste n'est pas vide.
```
val = var.HasCppInheritances();
```

## Méthode HasCppFunctions
*Paramètres*
* None.

*Retour*
* Bool : True si la liste n'est pas vide, False sinon.

*Description*
* Indique si la liste n'est pas vide.
```
val = var.HasCppFunctions();
```

## Méthode HasCppAttributes
*Paramètres*
* None.

*Retour*
* Bool : True si la liste n'est pas vide, False sinon.

*Description*
* Indique si la liste n'est pas vide.
```
val = var.HasCppAttributes();
```

## Méthode CppInheritancesCount
*Paramètres*
* None.

*Retour*
* Numeric : Le nombre d'éléments contenus dans la liste.

*Description*
* Retourne le nombre d'élément contenus dans la liste.
```
val = var.CppInheritancesCount();
```

## Méthode CppFunctionsCount
*Paramètres*
* None.

*Retour*
* Numeric : Le nombre d'éléments contenus dans la liste.

*Description*
* Retourne le nombre d'élément contenus dans la liste.
```
val = var.CppFunctionsCount();
```

## Méthode CppAttributesCount
*Paramètres*
* None.

*Retour*
* Numeric : Le nombre d'éléments contenus dans la liste.

*Description*
* Retourne le nombre d'élément contenus dans la liste.
```
val = var.CppAttributesCount();
```
