# IDiaDataSourcePtr
 Classe permettant d'accéder à une source de symboles de débogage. 

# Référence
## Méthode LoadDataFromPdb
*Paramètres*
* String : Le chemin du fichier PDB à ouvrir.

*Retour*
* Numeric : 0 si la lecture du fichier PDB est effectuée.

*Description*
*  Ouvre et prépare un fichier de base de données du programme (.pdb) comme source de données de débogage.
```
pdbParser = new PdbParser();
pdbParser.Initialize();
pdbDataSource = pdbParser.DataSource;
pdbDataSource.LoadDataFromPdb("projet.pdb");
```

## Méthode OpenSession
*Paramètres*
* IDiaSessionPtr : 

*Retour*
* Numeric : 

*Description*
*  Ouvre une session pour obtenir des symboles.
```
OpenSession();
```
