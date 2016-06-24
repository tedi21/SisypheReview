# CMacro
cMacro table represents a macro.

# Référence
## Constructeur CMacro
*Paramètres*
* None.

*Description*
* Crée une instance de la classe CMacro.
```
var = new CMacro();
```

## Constructeur CMacro
*Paramètres*
* String : La valeur de la colonne name.
* Numeric : La valeur de la colonne isConst.
* String : La valeur de la colonne constValue.
* Numeric : La valeur de la colonne lineNumber.
* Numeric : La valeur de la colonne startBlock.
* Numeric : La valeur de la colonne lengthBlock.

*Description*
* Crée une instance de la classe CMacro.
```
var = new CMacro(name, isConst, constValue, lineNumber, startBlock, lengthBlock);
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

## Méthode ConstValue
*Paramètres*
* None.

*Retour*
* String : La colonne constValue.

*Description*
* Retourne la colonne ConstValue.
```
val = var.ConstValue;
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

## Méthode ConstValue
*Paramètres*
* String : La valeur de la colonne constValue.

*Retour*
* None.

*Description*
* Définit la colonne constValue.
```
var.ConstValue(constValue);
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
