# CppVariable
cppVariable table represents a variable.

# Référence
## Constructeur CppVariable
*Paramètres*
* None.

*Description*
* Crée une instance de la classe CppVariable.
```
var = new CppVariable();
```

## Constructeur CppVariable
*Paramètres*
* String : La valeur de la colonne varType.
* String : La valeur de la colonne name.
* Numeric : La valeur de la colonne isStatic.
* Numeric : La valeur de la colonne isConst.
* Numeric : La valeur de la colonne isConstexpr.
* Numeric : La valeur de la colonne lineNumber.
* Numeric : La valeur de la colonne startBlock.
* Numeric : La valeur de la colonne lengthBlock.

*Description*
* Crée une instance de la classe CppVariable.
```
var = new CppVariable(varType, name, isStatic, isConst, isConstexpr, lineNumber, startBlock, lengthBlock);
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

## Méthode VarType
*Paramètres*
* None.

*Retour*
* String : La colonne varType.

*Description*
* Retourne la colonne VarType.
```
val = var.VarType;
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

## Méthode IsConstexpr
*Paramètres*
* None.

*Retour*
* Numeric : La colonne isConstexpr.

*Description*
* Retourne la colonne IsConstexpr.
```
val = var.IsConstexpr;
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

## Méthode CppFunction
*Paramètres*
* None.

*Retour*
* CppFunction : La colonne cppFunction.

*Description*
* Retourne la colonne CppFunction.
```
cppFunction = var.CppFunction;
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

## Méthode VarType
*Paramètres*
* String : La valeur de la colonne varType.

*Retour*
* None.

*Description*
* Définit la colonne varType.
```
var.VarType(varType);
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

## Méthode IsConstexpr
*Paramètres*
* Numeric : La valeur de la colonne isConstexpr.

*Retour*
* None.

*Description*
* Définit la colonne isConstexpr.
```
var.IsConstexpr(isConstexpr);
```

## Méthode CppFunction
*Paramètres*
* CppFunction : La valeur de la colonne cppFunction.

*Retour*
* None.

*Description*
* Définit la colonne cppFunction.
```
var.CppFunction(cppFunction);
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

## Méthode HasCppFunction
*Paramètres*
* None.

*Retour*
* Bool : Une valeur est définie pour la colonne cppFunction.

*Description*
* Indique si la colonne CppFunction a une valeur définie.
```
val = var.HasCppFunction;
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

## Méthode removeCppFunction
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime la valeur définie pour la colonne cppFunction.
```
var.CppFunction = null;
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
