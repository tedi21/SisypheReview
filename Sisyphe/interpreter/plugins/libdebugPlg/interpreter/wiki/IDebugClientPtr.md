# IDebugClientPtr
 Classe permettant d'accéder à un client de débogage. 

# Référence
## Méthode CreateProcess
*Paramètres*
* String : 
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  La méthode CreateProcess crée un processus à partir de la ligne de commande en paramètre.
```
CreateProcess();
```

## Méthode GetRunningProcessSystemIds
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  The GetRunningProcessSystemIds method returns the process ID.
```
GetRunningProcessSystemIds();
```

## Méthode GetRunningProcessDescription
*Paramètres*
* Numeric : 
* Numeric : 
* String : 
* String : 

*Retour*
* Numeric : 

*Description*
*  The GetRunningProcessDescription method returns a description of the process that includes the executable image name, the service names, the MTS package names, and the command line.
```
GetRunningProcessDescription();
```
