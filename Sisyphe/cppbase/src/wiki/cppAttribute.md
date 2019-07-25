# CppAttribute
cppAttribute table represents an attribute.

# Référence
## Constructeur CppAttribute
*Paramètres*
* None.

*Description*
* Crée une instance de la classe CppAttribute.
```
var = new CppAttribute();
```

## Constructeur CppAttribute
*Paramètres*
* String : La valeur de la colonne attrType.
* String : La valeur de la colonne name.
* String : La valeur de la colonne accessSpecifier.
* Numeric : La valeur de la colonne isStatic.
* Numeric : La valeur de la colonne isConst.
* Numeric : La valeur de la colonne isConstexpr.
* String : La valeur de la colonne constValue.
* Numeric : La valeur de la colonne lineNumber.
* Numeric : La valeur de la colonne startBlock.
* Numeric : La valeur de la colonne lengthBlock.

*Description*
* Crée une instance de la classe CppAttribute.
```
var = new CppAttribute(attrType, name, accessSpecifier, isStatic, isConst, isConstexpr, constValue, lineNumber, startBlock, lengthBlock);
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

## Méthode AttrType
*Paramètres*
* None.

*Retour*
* String : La colonne attrType.

*Description*
* Retourne la colonne AttrType.
```
val = var.AttrType;
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

## Méthode AttrType
*Paramètres*
* String : La valeur de la colonne attrType.

*Retour*
* None.

*Description*
* Définit la colonne attrType.
```
var.AttrType(attrType);
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
