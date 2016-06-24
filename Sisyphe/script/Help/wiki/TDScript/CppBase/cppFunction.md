# CppFunction
cppFunction table represents a function.

# Référence
## Constructeur CppFunction
*Paramètres*
* None.

*Description*
* Crée une instance de la classe CppFunction.
```
var = new CppFunction();
```

## Constructeur CppFunction
*Paramètres*
* String : La valeur de la colonne name.
* String : La valeur de la colonne accessSpecifier.
* String : La valeur de la colonne returnType.
* Numeric : La valeur de la colonne isConst.
* Numeric : La valeur de la colonne isVirtual.
* Numeric : La valeur de la colonne isVirtualPure.
* Numeric : La valeur de la colonne isStatic.
* Numeric : La valeur de la colonne isOperator.
* Numeric : La valeur de la colonne isDestructor.
* Numeric : La valeur de la colonne isConstructor.
* Numeric : La valeur de la colonne isVariadic.
* String : La valeur de la colonne signature.
* Numeric : La valeur de la colonne startDecBlock.
* Numeric : La valeur de la colonne lengthDecBlock.
* Numeric : La valeur de la colonne decLineNumber.
* Numeric : La valeur de la colonne linesCount.
* Numeric : La valeur de la colonne complexity.
* Numeric : La valeur de la colonne defLineNumber.
* Numeric : La valeur de la colonne startDefBlock.
* Numeric : La valeur de la colonne lengthDefBlock.

*Description*
* Crée une instance de la classe CppFunction.
```
var = new CppFunction(name, accessSpecifier, returnType, isConst, isVirtual, isVirtualPure, isStatic, isOperator, isDestructor, isConstructor, isVariadic, signature, startDecBlock, lengthDecBlock, decLineNumber, linesCount, complexity, defLineNumber, startDefBlock, lengthDefBlock);
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

## Méthode ReturnType
*Paramètres*
* None.

*Retour*
* String : La colonne returnType.

*Description*
* Retourne la colonne ReturnType.
```
val = var.ReturnType;
```

## Méthode IsConst
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isConst.

*Description*
* Retourne la colonne IsConst.
```
val = var.IsConst;
```

## Méthode IsVirtual
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isVirtual.

*Description*
* Retourne la colonne IsVirtual.
```
val = var.IsVirtual;
```

## Méthode IsVirtualPure
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isVirtualPure.

*Description*
* Retourne la colonne IsVirtualPure.
```
val = var.IsVirtualPure;
```

## Méthode IsStatic
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isStatic.

*Description*
* Retourne la colonne IsStatic.
```
val = var.IsStatic;
```

## Méthode IsOperator
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isOperator.

*Description*
* Retourne la colonne IsOperator.
```
val = var.IsOperator;
```

## Méthode IsDestructor
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isDestructor.

*Description*
* Retourne la colonne IsDestructor.
```
val = var.IsDestructor;
```

## Méthode IsConstructor
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isConstructor.

*Description*
* Retourne la colonne IsConstructor.
```
val = var.IsConstructor;
```

## Méthode IsVariadic
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isVariadic.

*Description*
* Retourne la colonne IsVariadic.
```
val = var.IsVariadic;
```

## Méthode Signature
*Paramètres*
* None.

*Retour*
* String : La colonne signature.

*Description*
* Retourne la colonne Signature.
```
val = var.Signature;
```

## Méthode StartDecBlock
*Paramètres*
* None.

*Retour*
* Numeric : La colonne startDecBlock.

*Description*
* Retourne la colonne StartDecBlock.
```
val = var.StartDecBlock;
```

## Méthode LengthDecBlock
*Paramètres*
* None.

*Retour*
* Numeric : La colonne lengthDecBlock.

*Description*
* Retourne la colonne LengthDecBlock.
```
val = var.LengthDecBlock;
```

## Méthode DecLineNumber
*Paramètres*
* None.

*Retour*
* Numeric : La colonne decLineNumber.

*Description*
* Retourne la colonne DecLineNumber.
```
val = var.DecLineNumber;
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

## Méthode Complexity
*Paramètres*
* None.

*Retour*
* Numeric : La colonne complexity.

*Description*
* Retourne la colonne Complexity.
```
val = var.Complexity;
```

## Méthode DefLineNumber
*Paramètres*
* None.

*Retour*
* Numeric : La colonne defLineNumber.

*Description*
* Retourne la colonne DefLineNumber.
```
val = var.DefLineNumber;
```

## Méthode StartDefBlock
*Paramètres*
* None.

*Retour*
* Numeric : La colonne startDefBlock.

*Description*
* Retourne la colonne StartDefBlock.
```
val = var.StartDefBlock;
```

## Méthode LengthDefBlock
*Paramètres*
* None.

*Retour*
* Numeric : La colonne lengthDefBlock.

*Description*
* Retourne la colonne LengthDefBlock.
```
val = var.LengthDefBlock;
```

## Méthode CppDeclarationFile
*Paramètres*
* None.

*Retour*
* CppFile : La colonne cppDeclarationFile.

*Description*
* Retourne la colonne CppDeclarationFile.
```
cppDeclarationFile = var.CppDeclarationFile;
```

## Méthode CppDefinitionFile
*Paramètres*
* None.

*Retour*
* CppFile : La colonne cppDefinitionFile.

*Description*
* Retourne la colonne CppDefinitionFile.
```
cppDefinitionFile = var.CppDefinitionFile;
```

## Méthode CppClass
*Paramètres*
* None.

*Retour*
* CppClass : La colonne cppClass.

*Description*
* Retourne la colonne CppClass.
```
cppClass = var.CppClass;
```

## Méthode CppDeclarationFile
*Paramètres*
* CppFile : La valeur de la colonne cppDeclarationFile.

*Retour*
* None.

*Description*
* Définit la colonne cppDeclarationFile.
```
var.CppDeclarationFile(cppDeclarationFile);
```

## Méthode CppDefinitionFile
*Paramètres*
* CppFile : La valeur de la colonne cppDefinitionFile.

*Retour*
* None.

*Description*
* Définit la colonne cppDefinitionFile.
```
var.CppDefinitionFile(cppDefinitionFile);
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

## Méthode CppClass
*Paramètres*
* CppClass : La valeur de la colonne cppClass.

*Retour*
* None.

*Description*
* Définit la colonne cppClass.
```
var.CppClass(cppClass);
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

## Méthode ReturnType
*Paramètres*
* String : La valeur de la colonne returnType.

*Retour*
* None.

*Description*
* Définit la colonne returnType.
```
var.ReturnType(returnType);
```

## Méthode IsConst
*Paramètres*
* Numeric : La valeur de la colonne isConst.

*Retour*
* None.

*Description*
* Définit la colonne isConst.
```
var.IsConst(isConst);
```

## Méthode IsVirtual
*Paramètres*
* Numeric : La valeur de la colonne isVirtual.

*Retour*
* None.

*Description*
* Définit la colonne isVirtual.
```
var.IsVirtual(isVirtual);
```

## Méthode IsVirtualPure
*Paramètres*
* Numeric : La valeur de la colonne isVirtualPure.

*Retour*
* None.

*Description*
* Définit la colonne isVirtualPure.
```
var.IsVirtualPure(isVirtualPure);
```

## Méthode IsStatic
*Paramètres*
* Numeric : La valeur de la colonne isStatic.

*Retour*
* None.

*Description*
* Définit la colonne isStatic.
```
var.IsStatic(isStatic);
```

## Méthode IsOperator
*Paramètres*
* Numeric : La valeur de la colonne isOperator.

*Retour*
* None.

*Description*
* Définit la colonne isOperator.
```
var.IsOperator(isOperator);
```

## Méthode IsDestructor
*Paramètres*
* Numeric : La valeur de la colonne isDestructor.

*Retour*
* None.

*Description*
* Définit la colonne isDestructor.
```
var.IsDestructor(isDestructor);
```

## Méthode IsConstructor
*Paramètres*
* Numeric : La valeur de la colonne isConstructor.

*Retour*
* None.

*Description*
* Définit la colonne isConstructor.
```
var.IsConstructor(isConstructor);
```

## Méthode IsVariadic
*Paramètres*
* Numeric : La valeur de la colonne isVariadic.

*Retour*
* None.

*Description*
* Définit la colonne isVariadic.
```
var.IsVariadic(isVariadic);
```

## Méthode Signature
*Paramètres*
* String : La valeur de la colonne signature.

*Retour*
* None.

*Description*
* Définit la colonne signature.
```
var.Signature(signature);
```

## Méthode StartDecBlock
*Paramètres*
* Numeric : La valeur de la colonne startDecBlock.

*Retour*
* None.

*Description*
* Définit la colonne startDecBlock.
```
var.StartDecBlock(startDecBlock);
```

## Méthode LengthDecBlock
*Paramètres*
* Numeric : La valeur de la colonne lengthDecBlock.

*Retour*
* None.

*Description*
* Définit la colonne lengthDecBlock.
```
var.LengthDecBlock(lengthDecBlock);
```

## Méthode DecLineNumber
*Paramètres*
* Numeric : La valeur de la colonne decLineNumber.

*Retour*
* None.

*Description*
* Définit la colonne decLineNumber.
```
var.DecLineNumber(decLineNumber);
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

## Méthode Complexity
*Paramètres*
* Numeric : La valeur de la colonne complexity.

*Retour*
* None.

*Description*
* Définit la colonne complexity.
```
var.Complexity(complexity);
```

## Méthode DefLineNumber
*Paramètres*
* Numeric : La valeur de la colonne defLineNumber.

*Retour*
* None.

*Description*
* Définit la colonne defLineNumber.
```
var.DefLineNumber(defLineNumber);
```

## Méthode StartDefBlock
*Paramètres*
* Numeric : La valeur de la colonne startDefBlock.

*Retour*
* None.

*Description*
* Définit la colonne startDefBlock.
```
var.StartDefBlock(startDefBlock);
```

## Méthode LengthDefBlock
*Paramètres*
* Numeric : La valeur de la colonne lengthDefBlock.

*Retour*
* None.

*Description*
* Définit la colonne lengthDefBlock.
```
var.LengthDefBlock(lengthDefBlock);
```

## Méthode HasCppDeclarationFile
*Paramètres*
* None.

*Retour*
* Bool : Une valeur est définie pour la colonne cppDeclarationFile.

*Description*
* Indique si la colonne CppDeclarationFile a une valeur définie.
```
val = var.HasCppDeclarationFile;
```

## Méthode HasCppDefinitionFile
*Paramètres*
* None.

*Retour*
* Bool : Une valeur est définie pour la colonne cppDefinitionFile.

*Description*
* Indique si la colonne CppDefinitionFile a une valeur définie.
```
val = var.HasCppDefinitionFile;
```

## Méthode HasCppClass
*Paramètres*
* None.

*Retour*
* Bool : Une valeur est définie pour la colonne cppClass.

*Description*
* Indique si la colonne CppClass a une valeur définie.
```
val = var.HasCppClass;
```

## Méthode removeCppDeclarationFile
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime la valeur définie pour la colonne cppDeclarationFile.
```
var.CppDeclarationFile = null;
```

## Méthode removeCppDefinitionFile
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime la valeur définie pour la colonne cppDefinitionFile.
```
var.CppDefinitionFile = null;
```

## Méthode removeCppClass
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime la valeur définie pour la colonne cppClass.
```
var.CppClass = null;
```

## Méthode removeCppParameters
*Paramètres*
* Numeric : La position de l'élément à supprimer dans la liste.

*Retour*
* None.

*Description*
* Supprime l'élément à la position *n* dans la liste de CppParameters.
```
var.CppParameters(0) = null;
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

## Méthode CppParameters
*Paramètres*
* Numeric : La position de l'élément à insérer dans la liste.
* CppParameter : L'élément à insérer dans la liste.

*Retour*
* None.

*Description*
* Insère un élément à la position *n* dans la liste de CppParameters.
```
var.CppParameters(0) = cppParameter;
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

## Méthode CppParameters
*Paramètres*
* Numeric : La position de l'élément dans la liste.

*Retour*
* CppParameter : L'élément dans la liste.

*Description*
* Retourne l'élément à la position *n* dans la liste de CppParameters.
```
val = var.CppParameters(0);
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

## Méthode ClearCppParameters
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime tous les éléments de liste.
```
var.ClearCppParameters();
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

## Méthode HasCppParameters
*Paramètres*
* None.

*Retour*
* Bool : True si la liste n'est pas vide, False sinon.

*Description*
* Indique si la liste n'est pas vide.
```
val = var.HasCppParameters();
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

## Méthode CppParametersCount
*Paramètres*
* None.

*Retour*
* Numeric : Le nombre d'éléments contenus dans la liste.

*Description*
* Retourne le nombre d'élément contenus dans la liste.
```
val = var.CppParametersCount();
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
