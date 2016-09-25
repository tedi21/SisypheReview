# IDebugSystemObjectsPtr
 Classe permettant d'accéder aux informations du processus en cours de débogage.

# Référence
## Méthode GetCurrentProcessId
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Returns the engine process ID for the current process.
```
GetCurrentProcessId();
```

## Méthode GetCurrentProcessDataOffset
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Returns the location of the system data structure describing the current process.
```
GetCurrentProcessDataOffset();
```

## Méthode GetCurrentProcessExecutableName
*Paramètres*
* String : 

*Retour*
* Numeric : 

*Description*
*  Returns the name of executable file loaded in the current process.
```
GetCurrentProcessExecutableName();
```
