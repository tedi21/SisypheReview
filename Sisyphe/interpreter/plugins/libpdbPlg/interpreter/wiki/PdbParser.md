# PdbParser
 Classe permettant de parser des fichiers PDB. 

# Référence
## Méthode Initialize
*Paramètres*
* None.

*Retour*
* Bool : True si l'initialisation est effectuée.

*Description*
*  Initialise le parseur PDB.
```
pdbParser = new PdbParser();
pdbParser.Initialize();
pdbDataSource = pdbParser.DataSource;
```

## Méthode Terminate
*Paramètres*
* None.

*Retour*
* Bool : True si la destruction est effectuée.

*Description*
*  Libère les objets PDB.
```
pdbParser.Terminate();
pdbParser = null;
```
