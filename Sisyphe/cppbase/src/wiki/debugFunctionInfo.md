# DebugFunctionInfo
debugFunctionInfo table represents function information for debug.

# Référence
## Constructeur DebugFunctionInfo
*Paramètres*
* None.

*Description*
* Crée une instance de la classe DebugFunctionInfo.
```
var = new DebugFunctionInfo();
```

## Constructeur DebugFunctionInfo
*Paramètres*
* Numeric : La valeur de la colonne lineNumber.
* Numeric : La valeur de la colonne address.
* Numeric : La valeur de la colonne debugStart.
* Numeric : La valeur de la colonne debugEnd.
* String : La valeur de la colonne debugReturnType.

*Description*
* Crée une instance de la classe DebugFunctionInfo.
```
var = new DebugFunctionInfo(lineNumber, address, debugStart, debugEnd, debugReturnType);
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

## Méthode Address
*Paramètres*
* None.

*Retour*
* Numeric : La colonne address.

*Description*
* Retourne la colonne Address.
```
val = var.Address;
```

## Méthode DebugStart
*Paramètres*
* None.

*Retour*
* Numeric : La colonne debugStart.

*Description*
* Retourne la colonne DebugStart.
```
val = var.DebugStart;
```

## Méthode DebugEnd
*Paramètres*
* None.

*Retour*
* Numeric : La colonne debugEnd.

*Description*
* Retourne la colonne DebugEnd.
```
val = var.DebugEnd;
```

## Méthode DebugReturnType
*Paramètres*
* None.

*Retour*
* String : La colonne debugReturnType.

*Description*
* Retourne la colonne DebugReturnType.
```
val = var.DebugReturnType;
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

## Méthode Address
*Paramètres*
* Numeric : La valeur de la colonne address.

*Retour*
* None.

*Description*
* Définit la colonne address.
```
var.Address(address);
```

## Méthode DebugStart
*Paramètres*
* Numeric : La valeur de la colonne debugStart.

*Retour*
* None.

*Description*
* Définit la colonne debugStart.
```
var.DebugStart(debugStart);
```

## Méthode DebugEnd
*Paramètres*
* Numeric : La valeur de la colonne debugEnd.

*Retour*
* None.

*Description*
* Définit la colonne debugEnd.
```
var.DebugEnd(debugEnd);
```

## Méthode DebugReturnType
*Paramètres*
* String : La valeur de la colonne debugReturnType.

*Retour*
* None.

*Description*
* Définit la colonne debugReturnType.
```
var.DebugReturnType(debugReturnType);
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

## Méthode removeDebugVariableInfos
*Paramètres*
* Numeric : La position de l'élément à supprimer dans la liste.

*Retour*
* None.

*Description*
* Supprime l'élément à la position *n* dans la liste de DebugVariableInfos.
```
var.DebugVariableInfos(0) = null;
```

## Méthode DebugVariableInfos
*Paramètres*
* Numeric : La position de l'élément à insérer dans la liste.
* DebugVariableInfo : L'élément à insérer dans la liste.

*Retour*
* None.

*Description*
* Insère un élément à la position *n* dans la liste de DebugVariableInfos.
```
var.DebugVariableInfos(0) = debugVariableInfo;
```

## Méthode DebugVariableInfos
*Paramètres*
* Numeric : La position de l'élément dans la liste.

*Retour*
* DebugVariableInfo : L'élément dans la liste.

*Description*
* Retourne l'élément à la position *n* dans la liste de DebugVariableInfos.
```
val = var.DebugVariableInfos(0);
```

## Méthode ClearDebugVariableInfos
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime tous les éléments de liste.
```
var.ClearDebugVariableInfos();
```

## Méthode HasDebugVariableInfos
*Paramètres*
* None.

*Retour*
* Bool : True si la liste n'est pas vide, False sinon.

*Description*
* Indique si la liste n'est pas vide.
```
val = var.HasDebugVariableInfos();
```

## Méthode DebugVariableInfosCount
*Paramètres*
* None.

*Retour*
* Numeric : Le nombre d'éléments contenus dans la liste.

*Description*
* Retourne le nombre d'élément contenus dans la liste.
```
val = var.DebugVariableInfosCount();
```
