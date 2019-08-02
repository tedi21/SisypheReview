# IDiaLineNumberPtr
 Accède aux informations qui décrivent le processus du mappage d'un bloc d'octets de texte image à un numéro de ligne du fichier source.

# Référence
## Méthode Get_lineNumber
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Récupère le numéro de ligne dans le fichier source.
```
Get_lineNumber();
```

## Méthode Get_lineNumberEnd
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Récupère le numéro de ligne source de base 1 où l'instruction ou l'expression se termine.
```
Get_lineNumberEnd();
```

## Méthode Get_columnNumber
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Récupère le numéro de colonne où l'expression ou l'instruction commence.
```
Get_columnNumber();
```

## Méthode Get_columnNumberEnd
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Récupère le numéro de colonne source de base 1 où l'expression ou l'instruction se termine.
```
Get_columnNumberEnd();
```

## Méthode Get_length
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  Récupère le nombre d'octets dans un bloc.
```
Get_length();
```

## Méthode Get_statement
*Paramètres*
* Numeric : 

*Retour*
* Numeric : 

*Description*
*  extrait une balise indiquant que ces informations de ligne décrivent le début d'une instruction, plutôt qu'une expression, dans la source de programme.
```
Get_statement();
```

## Méthode Get_sourceFile
*Paramètres*
* IDiaSourceFilePtr : 

*Retour*
* Numeric : 

*Description*
*  extrait une référence au fichier source.
```
Get_sourceFile();
```
