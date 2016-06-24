# DebugFileInfo
debugFileInfo table represents file information for debug.

# Référence
## Constructeur DebugFileInfo
*Paramètres*
* None.

*Description*
* Crée une instance de la classe DebugFileInfo.
```
var = new DebugFileInfo();
```

## Constructeur DebugFileInfo
*Paramètres*
* String : La valeur de la colonne compilandPath.
* Array[Numeric] : La valeur de la colonne checksum.

*Description*
* Crée une instance de la classe DebugFileInfo.
```
var = new DebugFileInfo(compilandPath, checksum);
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

## Méthode CompilandPath
*Paramètres*
* None.

*Retour*
* String : La colonne compilandPath.

*Description*
* Retourne la colonne CompilandPath.
```
val = var.CompilandPath;
```

## Méthode Checksum
*Paramètres*
* None.

*Retour*
* Array[Numeric] : La colonne checksum.

*Description*
* Retourne la colonne Checksum.
```
val = var.Checksum;
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

## Méthode CompilandPath
*Paramètres*
* String : La valeur de la colonne compilandPath.

*Retour*
* None.

*Description*
* Définit la colonne compilandPath.
```
var.CompilandPath(compilandPath);
```

## Méthode Checksum
*Paramètres*
* Array[Numeric] : La valeur de la colonne checksum.

*Retour*
* None.

*Description*
* Définit la colonne checksum.
```
var.Checksum(checksum);
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
