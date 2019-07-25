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
* String : La valeur de la colonne name.

*Description*
* Crée une instance de la classe DebugVariableInfo.
```
var = new DebugVariableInfo(category, name);
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

## Méthode DebugTypeInfo
*Paramètres*
* None.

*Retour*
* DebugTypeInfo : La colonne debugTypeInfo.

*Description*
* Retourne la colonne DebugTypeInfo.
```
debugTypeInfo = var.DebugTypeInfo;
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

## Méthode DebugTypeInfo
*Paramètres*
* DebugTypeInfo : La valeur de la colonne debugTypeInfo.

*Retour*
* None.

*Description*
* Définit la colonne debugTypeInfo.
```
var.DebugTypeInfo(debugTypeInfo);
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

## Méthode HasDebugTypeInfo
*Paramètres*
* None.

*Retour*
* Bool : Une valeur est définie pour la colonne debugTypeInfo.

*Description*
* Indique si la colonne DebugTypeInfo a une valeur définie.
```
val = var.HasDebugTypeInfo;
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

## Méthode removeDebugTypeInfo
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime la valeur définie pour la colonne debugTypeInfo.
```
var.DebugTypeInfo = null;
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

## Méthode removeDebugValueInfos
*Paramètres*
* Numeric : La position de l'élément à supprimer dans la liste.

*Retour*
* None.

*Description*
* Supprime l'élément à la position *n* dans la liste de DebugValueInfos.
```
var.DebugValueInfos(0) = null;
```

## Méthode DebugValueInfos
*Paramètres*
* Numeric : La position de l'élément à insérer dans la liste.
* DebugValueInfo : L'élément à insérer dans la liste.

*Retour*
* None.

*Description*
* Insère un élément à la position *n* dans la liste de DebugValueInfos.
```
var.DebugValueInfos(0) = debugValueInfo;
```

## Méthode DebugValueInfos
*Paramètres*
* Numeric : La position de l'élément dans la liste.

*Retour*
* DebugValueInfo : L'élément dans la liste.

*Description*
* Retourne l'élément à la position *n* dans la liste de DebugValueInfos.
```
val = var.DebugValueInfos(0);
```

## Méthode ClearDebugValueInfos
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime tous les éléments de liste.
```
var.ClearDebugValueInfos();
```

## Méthode HasDebugValueInfos
*Paramètres*
* None.

*Retour*
* Bool : True si la liste n'est pas vide, False sinon.

*Description*
* Indique si la liste n'est pas vide.
```
val = var.HasDebugValueInfos();
```

## Méthode DebugValueInfosCount
*Paramètres*
* None.

*Retour*
* Numeric : Le nombre d'éléments contenus dans la liste.

*Description*
* Retourne le nombre d'élément contenus dans la liste.
```
val = var.DebugValueInfosCount();
```
