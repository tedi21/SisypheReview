# DebugVariableInfo
debugVariableInfo table represents variable information for debug.

# Référence
## Constructeur DebugVariableInfo
*Paramètres*
* None.

*Description*
* Crée une instance de la classe DebugVariableInfo.
```
var = new DebugVariableInfo();
```

## Constructeur DebugVariableInfo
*Paramètres*
* String : La valeur de la colonne category.
* String : La valeur de la colonne type.
* String : La valeur de la colonne name.
* String : La valeur de la colonne textValue.

*Description*
* Crée une instance de la classe DebugVariableInfo.
```
var = new DebugVariableInfo(category, type, name, textValue);
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

## Méthode Type
*Paramètres*
* None.

*Retour*
* String : La colonne type.

*Description*
* Retourne la colonne Type.
```
val = var.Type;
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

## Méthode TextValue
*Paramètres*
* None.

*Retour*
* String : La colonne textValue.

*Description*
* Retourne la colonne TextValue.
```
val = var.TextValue;
```

## Méthode DebugFunctionInfo
*Paramètres*
* None.

*Retour*
* DebugFunctionInfo : La colonne debugFunctionInfo.

*Description*
* Retourne la colonne DebugFunctionInfo.
```
debugFunctionInfo = var.DebugFunctionInfo;
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

## Méthode Type
*Paramètres*
* String : La valeur de la colonne type.

*Retour*
* None.

*Description*
* Définit la colonne type.
```
var.Type(type);
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

## Méthode TextValue
*Paramètres*
* String : La valeur de la colonne textValue.

*Retour*
* None.

*Description*
* Définit la colonne textValue.
```
var.TextValue(textValue);
```

## Méthode DebugFunctionInfo
*Paramètres*
* DebugFunctionInfo : La valeur de la colonne debugFunctionInfo.

*Retour*
* None.

*Description*
* Définit la colonne debugFunctionInfo.
```
var.DebugFunctionInfo(debugFunctionInfo);
```

## Méthode HasDebugFunctionInfo
*Paramètres*
* None.

*Retour*
* Bool : Une valeur est définie pour la colonne debugFunctionInfo.

*Description*
* Indique si la colonne DebugFunctionInfo a une valeur définie.
```
val = var.HasDebugFunctionInfo;
```

## Méthode removeDebugFunctionInfo
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime la valeur définie pour la colonne debugFunctionInfo.
```
var.DebugFunctionInfo = null;
```
