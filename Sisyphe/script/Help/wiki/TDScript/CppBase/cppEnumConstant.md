# CppEnumConstant
cppEnumConstant table represents a parameter.

# Référence
## Constructeur CppEnumConstant
*Paramètres*
* None.

*Description*
* Crée une instance de la classe CppEnumConstant.
```
var = new CppEnumConstant();
```

## Constructeur CppEnumConstant
*Paramètres*
* String : La valeur de la colonne name.
* Numeric : La valeur de la colonne defaultValue.
* Numeric : La valeur de la colonne startBlock.
* Numeric : La valeur de la colonne lengthBlock.

*Description*
* Crée une instance de la classe CppEnumConstant.
```
var = new CppEnumConstant(name, defaultValue, startBlock, lengthBlock);
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

## Méthode DefaultValue
*Paramètres*
* None.

*Retour*
* Numeric : La colonne defaultValue.

*Description*
* Retourne la colonne DefaultValue.
```
val = var.DefaultValue;
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

## Méthode CppEnum
*Paramètres*
* None.

*Retour*
* CppEnum : La colonne cppEnum.

*Description*
* Retourne la colonne CppEnum.
```
cppEnum = var.CppEnum;
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

## Méthode DefaultValue
*Paramètres*
* Numeric : La valeur de la colonne defaultValue.

*Retour*
* None.

*Description*
* Définit la colonne defaultValue.
```
var.DefaultValue(defaultValue);
```

## Méthode CppEnum
*Paramètres*
* CppEnum : La valeur de la colonne cppEnum.

*Retour*
* None.

*Description*
* Définit la colonne cppEnum.
```
var.CppEnum(cppEnum);
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

## Méthode HasCppEnum
*Paramètres*
* None.

*Retour*
* Bool : Une valeur est définie pour la colonne cppEnum.

*Description*
* Indique si la colonne CppEnum a une valeur définie.
```
val = var.HasCppEnum;
```

## Méthode removeCppEnum
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime la valeur définie pour la colonne cppEnum.
```
var.CppEnum = null;
```
