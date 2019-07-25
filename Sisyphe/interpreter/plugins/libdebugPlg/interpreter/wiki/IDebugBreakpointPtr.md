# IDebugBreakpointPtr
 Classe permettant d'accéder aux informations d'un breakpoint.

# Référence
## Méthode SetOffset
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Sets the location that triggers a breakpoint.
```
SetOffset();
```

## Méthode SetOffsetExpression
*Paramètres*
* String : 

*Retour*
* Numeric : 

*Description*
*  The SetOffsetExpression methods set an expression string that evaluates to the location that triggers a breakpoint.
```
SetOffsetExpression();
```

## Méthode SetFlags
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Sets the flags for a breakpoint.
```
SetFlags();
```

## Méthode SetPassCount
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  The SetPassCount method sets the number of times that the target must reach the breakpoint location before the breakpoint is triggered.
```
SetPassCount();
```

## Méthode GetPassCount
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  The GetPassCount method returns the number of times that the target was originally required to reach the breakpoint location before the breakpoint is triggered.
```
GetPassCount();
```

## Méthode GetCurrentPassCount
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  The GetCurrentPassCount method returns the remaining number of times that the target must reach the breakpoint location before the breakpoint is triggered.
```
GetCurrentPassCount();
```

## Méthode GetId
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  The GetId method returns a breakpoint ID, which is the engine's unique identifier for a breakpoint.
```
GetId();
```

## Méthode GetOffset
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  The GetOffset method returns the location that triggers a breakpoint.
```
GetOffset();
```
