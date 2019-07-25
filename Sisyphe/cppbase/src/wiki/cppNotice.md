# CppNotice
cppNotice table represents an error.

# Référence
## Constructeur CppNotice
*Paramètres*
* None.

*Description*
* Crée une instance de la classe CppNotice.
```
var = new CppNotice();
```

## Constructeur CppNotice
*Paramètres*
* String : La valeur de la colonne description.
* String : La valeur de la colonne category.
* Numeric : La valeur de la colonne ruleNumber.
* Numeric : La valeur de la colonne lineNumber.
* Numeric : La valeur de la colonne startBlock.
* Numeric : La valeur de la colonne lengthBlock.

*Description*
* Crée une instance de la classe CppNotice.
```
var = new CppNotice(description, category, ruleNumber, lineNumber, startBlock, lengthBlock);
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

## Méthode Description
*Paramètres*
* None.

*Retour*
* String : La colonne description.

*Description*
* Retourne la colonne Description.
```
val = var.Description;
```

## Méthode Category
*Paramètres*
* None.

*Retour*
* String : La colonne category.

*Description*
* Retourne la colonne Category.
```
val = var.Category;
```

## Méthode RuleNumber
*Paramètres*
* None.

*Retour*
* Numeric : La colonne ruleNumber.

*Description*
* Retourne la colonne RuleNumber.
```
val = var.RuleNumber;
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

## Méthode Description
*Paramètres*
* String : La valeur de la colonne description.

*Retour*
* None.

*Description*
* Définit la colonne description.
```
var.Description(description);
```

## Méthode Category
*Paramètres*
* String : La valeur de la colonne category.

*Retour*
* None.

*Description*
* Définit la colonne category.
```
var.Category(category);
```

## Méthode RuleNumber
*Paramètres*
* Numeric : La valeur de la colonne ruleNumber.

*Retour*
* None.

*Description*
* Définit la colonne ruleNumber.
```
var.RuleNumber(ruleNumber);
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
