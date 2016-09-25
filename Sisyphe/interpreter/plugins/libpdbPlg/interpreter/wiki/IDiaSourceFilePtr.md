# IDiaSourceFilePtr
 Représente un fichier source.

# Référence
## Méthode Get_checksum
*Paramètres*
* Numeric : 
* Numeric : 
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Récupère les octets de checksum.
```
Get_checksum();
```

## Méthode Get_fileName
*Paramètres*
* String : 

*Retour*
* Numeric : 

*Description*
*  Extrait le nom du fichier source.
```
Get_fileName();
```

## Méthode Get_compilands
*Paramètres*
* IDiaEnumSymbolsPtr : 

*Retour*
* Numeric : 

*Description*
*  Récupère un énumérateur des compilands qui ont des numéros de ligne référençant ce fichier.
```
Get_compilands();
```
