# DebugEngine
 Classe permettant de démarrer le moteur de débogage. 

# Référence
## Méthode Initialize
*Paramètres*
* None.

*Retour*
* Bool : 

*Description*
*  Initialise le moteur de débogage.
```
Initialize();
```

## Méthode Terminate
*Paramètres*
* None.

*Retour*
* Bool : 

*Description*
*  Libère les objets debug.
```
Terminate();
```

## Méthode DvAlloc
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Allocate additional memory to the target process.
```
DvAlloc();
```

## Méthode DvFree
*Paramètres*
* Numeric : 
* Numeric : 

*Retour*
* Bool : 

*Description*
*  Frees a memory allocation owned by the target process.
```
DvFree();
```
