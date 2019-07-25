# DebugErrorInfo
debugErrorInfo table represents error information for debug.

# Référence
## Constructeur DebugErrorInfo
*Paramètres*
* None.

*Description*
* Crée une instance de la classe DebugErrorInfo.
```
var = new DebugErrorInfo();
```

## Constructeur DebugErrorInfo
*Paramètres*
* String : La valeur de la colonne callStack.

*Description*
* Crée une instance de la classe DebugErrorInfo.
```
var = new DebugErrorInfo(callStack);
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

## Méthode CallStack
*Paramètres*
* None.

*Retour*
* String : La colonne callStack.

*Description*
* Retourne la colonne CallStack.
```
val = var.CallStack;
```

## Méthode CallStack
*Paramètres*
* String : La valeur de la colonne callStack.

*Retour*
* None.

*Description*
* Définit la colonne callStack.
```
var.CallStack(callStack);
```
