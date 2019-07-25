# DebugValueInfo
debugValueInfo table represents value information for debug.

# Référence
## Constructeur DebugValueInfo
*Paramètres*
* None.

*Description*
* Crée une instance de la classe DebugValueInfo.
```
var = new DebugValueInfo();
```

## Constructeur DebugValueInfo
*Paramètres*
* String : La valeur de la colonne textValue.

*Description*
* Crée une instance de la classe DebugValueInfo.
```
var = new DebugValueInfo(textValue);
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

## Méthode DebugVariableInfo
*Paramètres*
* None.

*Retour*
* DebugVariableInfo : La colonne debugVariableInfo.

*Description*
* Retourne la colonne DebugVariableInfo.
```
debugVariableInfo = var.DebugVariableInfo;
```

## Méthode DebugStubInfo
*Paramètres*
* None.

*Retour*
* DebugStubInfo : La colonne debugStubInfo.

*Description*
* Retourne la colonne DebugStubInfo.
```
debugStubInfo = var.DebugStubInfo;
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

## Méthode DebugVariableInfo
*Paramètres*
* DebugVariableInfo : La valeur de la colonne debugVariableInfo.

*Retour*
* None.

*Description*
* Définit la colonne debugVariableInfo.
```
var.DebugVariableInfo(debugVariableInfo);
```

## Méthode DebugStubInfo
*Paramètres*
* DebugStubInfo : La valeur de la colonne debugStubInfo.

*Retour*
* None.

*Description*
* Définit la colonne debugStubInfo.
```
var.DebugStubInfo(debugStubInfo);
```

## Méthode HasDebugVariableInfo
*Paramètres*
* None.

*Retour*
* Bool : Une valeur est définie pour la colonne debugVariableInfo.

*Description*
* Indique si la colonne DebugVariableInfo a une valeur définie.
```
val = var.HasDebugVariableInfo;
```

## Méthode HasDebugStubInfo
*Paramètres*
* None.

*Retour*
* Bool : Une valeur est définie pour la colonne debugStubInfo.

*Description*
* Indique si la colonne DebugStubInfo a une valeur définie.
```
val = var.HasDebugStubInfo;
```

## Méthode removeDebugVariableInfo
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime la valeur définie pour la colonne debugVariableInfo.
```
var.DebugVariableInfo = null;
```

## Méthode removeDebugStubInfo
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime la valeur définie pour la colonne debugStubInfo.
```
var.DebugStubInfo = null;
```
