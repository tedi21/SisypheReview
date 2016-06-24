# CppInclude
cppInclude table represents an include in cpp file.

# Référence
## Constructeur CppInclude
*Paramètres*
* None.

*Description*
* Crée une instance de la classe CppInclude.
```
var = new CppInclude();
```

## Constructeur CppInclude
*Paramètres*
* String : La valeur de la colonne fileName.

*Description*
* Crée une instance de la classe CppInclude.
```
var = new CppInclude(fileName);
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

## Méthode FileName
*Paramètres*
* None.

*Retour*
* String : La colonne fileName.

*Description*
* Retourne la colonne FileName.
```
val = var.FileName;
```

## Méthode CppFile
*Paramètres*
* None.

*Retour*
* CppFile : La colonne cppFile.

*Description*
* Retourne la colonne CppFile.
```
cppFile = var.CppFile;
```

## Méthode FileName
*Paramètres*
* String : La valeur de la colonne fileName.

*Retour*
* None.

*Description*
* Définit la colonne fileName.
```
var.FileName(fileName);
```

## Méthode CppFile
*Paramètres*
* CppFile : La valeur de la colonne cppFile.

*Retour*
* None.

*Description*
* Définit la colonne cppFile.
```
var.CppFile(cppFile);
```

## Méthode HasCppFile
*Paramètres*
* None.

*Retour*
* Bool : Une valeur est définie pour la colonne cppFile.

*Description*
* Indique si la colonne CppFile a une valeur définie.
```
val = var.HasCppFile;
```

## Méthode removeCppFile
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime la valeur définie pour la colonne cppFile.
```
var.CppFile = null;
```
