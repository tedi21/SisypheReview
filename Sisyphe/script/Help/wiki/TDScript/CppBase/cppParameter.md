# CppParameter
cppParameter table represents a parameter.

# Référence
## Constructeur CppParameter
*Paramètres*
* None.

*Description*
* Crée une instance de la classe CppParameter.
```
var = new CppParameter();
```

## Constructeur CppParameter
*Paramètres*
* Numeric : La valeur de la colonne paramOrder.
* String : La valeur de la colonne paramType.
* Numeric : La valeur de la colonne isConst.
* String : La valeur de la colonne defaultValue.
* String : La valeur de la colonne decName.
* Numeric : La valeur de la colonne decLineNumber.
* Numeric : La valeur de la colonne startDecBlock.
* Numeric : La valeur de la colonne lengthDecBlock.
* String : La valeur de la colonne defName.
* Numeric : La valeur de la colonne defLineNumber.
* Numeric : La valeur de la colonne startDefBlock.
* Numeric : La valeur de la colonne lengthDefBlock.

*Description*
* Crée une instance de la classe CppParameter.
```
var = new CppParameter(paramOrder, paramType, isConst, defaultValue, decName, decLineNumber, startDecBlock, lengthDecBlock, defName, defLineNumber, startDefBlock, lengthDefBlock);
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

## Méthode ParamOrder
*Paramètres*
* None.

*Retour*
* Numeric : La colonne paramOrder.

*Description*
* Retourne la colonne ParamOrder.
```
val = var.ParamOrder;
```

## Méthode ParamType
*Paramètres*
* None.

*Retour*
* String : La colonne paramType.

*Description*
* Retourne la colonne ParamType.
```
val = var.ParamType;
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

## Méthode DefaultValue
*Paramètres*
* None.

*Retour*
* String : La colonne defaultValue.

*Description*
* Retourne la colonne DefaultValue.
```
val = var.DefaultValue;
```

## Méthode DecName
*Paramètres*
* None.

*Retour*
* String : La colonne decName.

*Description*
* Retourne la colonne DecName.
```
val = var.DecName;
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

## Méthode DefName
*Paramètres*
* None.

*Retour*
* String : La colonne defName.

*Description*
* Retourne la colonne DefName.
```
val = var.DefName;
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

## Méthode ParamOrder
*Paramètres*
* Numeric : La valeur de la colonne paramOrder.

*Retour*
* None.

*Description*
* Définit la colonne paramOrder.
```
var.ParamOrder(paramOrder);
```

## Méthode ParamType
*Paramètres*
* String : La valeur de la colonne paramType.

*Retour*
* None.

*Description*
* Définit la colonne paramType.
```
var.ParamType(paramType);
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

## Méthode DefaultValue
*Paramètres*
* String : La valeur de la colonne defaultValue.

*Retour*
* None.

*Description*
* Définit la colonne defaultValue.
```
var.DefaultValue(defaultValue);
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

## Méthode DecName
*Paramètres*
* String : La valeur de la colonne decName.

*Retour*
* None.

*Description*
* Définit la colonne decName.
```
var.DecName(decName);
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

## Méthode DefName
*Paramètres*
* String : La valeur de la colonne defName.

*Retour*
* None.

*Description*
* Définit la colonne defName.
```
var.DefName(defName);
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
