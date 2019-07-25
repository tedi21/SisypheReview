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

## Méthode CreateProcess2
*Paramètres*
* String : 
* Numeric : 
* String : 

*Retour*
* Numeric : 

*Description*
*  La méthode CreateProcess2 crée un processus à partir de la ligne de commande en paramètre et d'un répertoire courant spécifique.
```
CreateProcess2();
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
