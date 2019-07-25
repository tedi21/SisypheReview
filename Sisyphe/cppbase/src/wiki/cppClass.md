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
* String : La valeur de la colonne fullName.
* String : La valeur de la colonne accessSpecifier.
* Numeric : La valeur de la colonne isStruct.
* Numeric : La valeur de la colonne isInterface.
* Numeric : La valeur de la colonne isAbstract.
* Numeric : La valeur de la colonne isTemplate.
* Numeric : La valeur de la colonne linesCount.
* Numeric : La valeur de la colonne lineNumber.
* Numeric : La valeur de la colonne startBlock.
* Numeric : La valeur de la colonne lengthBlock.

*Description*
* Crée une instance de la classe CppClass.
```
var = new CppClass(name, fullName, accessSpecifier, isStruct, isInterface, isAbstract, isTemplate, linesCount, lineNumber, startBlock, lengthBlock);
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

## Méthode FullName
*Paramètres*
* None.

*Retour*
* String : La colonne fullName.

*Description*
* Retourne la colonne FullName.
```
val = var.FullName;
```

## Méthode AccessSpecifier
*Paramètres*
* None.

*Retour*
* String : La colonne accessSpecifier.

*Description*
* Retourne la colonne AccessSpecifier.
```
val = var.AccessSpecifier;
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

## Méthode IsTemplate
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isTemplate.

*Description*
* Retourne la colonne IsTemplate.
```
val = var.IsTemplate;
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

## Méthode EncapsulationClass
*Paramètres*
* None.

*Retour*
* CppClass : La colonne encapsulationClass.

*Description*
* Retourne la colonne EncapsulationClass.
```
encapsulationClass = var.EncapsulationClass;
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

## Méthode EncapsulationClass
*Paramètres*
* CppClass : La valeur de la colonne encapsulationClass.

*Retour*
* None.

*Description*
* Définit la colonne encapsulationClass.
```
var.EncapsulationClass(encapsulationClass);
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

## Méthode FullName
*Paramètres*
* String : La valeur de la colonne fullName.

*Retour*
* None.

*Description*
* Définit la colonne fullName.
```
var.FullName(fullName);
```

## Méthode AccessSpecifier
*Paramètres*
* String : La valeur de la colonne accessSpecifier.

*Retour*
* None.

*Description*
* Définit la colonne accessSpecifier.
```
var.AccessSpecifier(accessSpecifier);
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

## Méthode IsTemplate
*Paramètres*
* Numeric : La valeur de la colonne isTemplate.

*Retour*
* None.

*Description*
* Définit la colonne isTemplate.
```
var.IsTemplate(isTemplate);
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

## Méthode HasEncapsulationClass
*Paramètres*
* None.

*Retour*
* Bool : Une valeur est définie pour la colonne encapsulationClass.

*Description*
* Indique si la colonne EncapsulationClass a une valeur définie.
```
val = var.HasEncapsulationClass;
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

## Méthode removeEncapsulationClass
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime la valeur définie pour la colonne encapsulationClass.
```
var.EncapsulationClass = null;
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

## Méthode removeInternClasses
*Paramètres*
* Numeric : La position de l'élément à supprimer dans la liste.

*Retour*
* None.

*Description*
* Supprime l'élément à la position *n* dans la liste de InternClasses.
```
var.InternClasses(0) = null;
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

## Méthode InternClasses
*Paramètres*
* Numeric : La position de l'élément à insérer dans la liste.
* CppClass : L'élément à insérer dans la liste.

*Retour*
* None.

*Description*
* Insère un élément à la position *n* dans la liste de InternClasses.
```
var.InternClasses(0) = internClasse;
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

## Méthode InternClasses
*Paramètres*
* Numeric : La position de l'élément dans la liste.

*Retour*
* CppClass : L'élément dans la liste.

*Description*
* Retourne l'élément à la position *n* dans la liste de InternClasses.
```
val = var.InternClasses(0);
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

## Méthode ClearInternClasses
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime tous les éléments de liste.
```
var.ClearInternClasses();
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

## Méthode HasInternClasses
*Paramètres*
* None.

*Retour*
* Bool : True si la liste n'est pas vide, False sinon.

*Description*
* Indique si la liste n'est pas vide.
```
val = var.HasInternClasses();
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

## Méthode InternClassesCount
*Paramètres*
* None.

*Retour*
* Numeric : Le nombre d'éléments contenus dans la liste.

*Description*
* Retourne le nombre d'élément contenus dans la liste.
```
val = var.InternClassesCount();
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
