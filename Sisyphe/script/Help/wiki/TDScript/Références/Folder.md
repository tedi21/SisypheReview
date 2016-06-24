# Folder
Cet objet représente un dossier. Il dispose diverses méthodes permettant de manipuler un dossier.

# Référence
## Constructeur Folder
*Paramètres*
* String : Chemin du dossier.

*Retour*
* None.

*Description*
* Construit un dossier.
```
f = new Folder("C:\folder");
```

## Méthode Path
*Paramètres*
* None.

*Retour*
* String : Le chemin du dossier.

*Description*
* Retourne le chemin du dossier.
```
f = new Folder(".\folder");
print(f.Path); 
/* sortie : .\folder */
```

## Méthode AbsolutePath
*Paramètres*
* None.

*Retour*
* String : Le chemin complet du dossier.

*Description*
* Retourne le chemin du dossier.
```
f = new Folder(".\folder");
print(f.AbsolutePath); 
/* sortie : c:\Program files\scripts\folder */
```

## Méthode Files
*Paramètres*
* None.

*Retour*
* Array of String : La liste des fichiers contenus dans le dossier.

*Description*
* Retourne la liste des fichiers contenus dans le dossier.
```
f = new Folder(".\folder");
f.Files;
```

## Méthode Folders
*Paramètres*
* None.

*Retour*
* Array of String : La liste des dossiers contenus dans le dossier.

*Description*
* Retourne la liste des dossiers contenus dans le dossier.
```
f = new Folder(".\folder");
f.Folders;
```

## Méthode CreateFolder
*Paramètres*
* String : le nom du dossier.

*Retour*
* Bool : true si la création du dossier a réussit, false sinon.

*Description*
* Crée un sous-dossier.
```
f = new Folder(".\folder");
f.CreateFolder("subfolder");
```

## Méthode CopyTo
*Paramètres*
* String ou Folder ou File : Nom du fichier ou du dossier à copier.
* String ou Folder : Chemin du dossier de destination.

*Retour*
* None.

*Description*
* Copie un fichier ou un dossier.
```
f = new Folder(".\folder");
f.CopyTo("myFile", "c:\save");
```

## Méthode Remove
*Paramètres*
* String ou Folder ou File : Nom du fichier ou du dossier à supprimer.

*Retour*
* Numeric : Nombre de fichiers supprimés.

*Description*
* Supprime un fichier ou un dossier.
```
f = new Folder(".\folder");
f.Remove("myFile");
```

## Méthode Rename
*Paramètres*
* String ou Folder ou File : Nom du fichier ou du dossier à renommer.
* String ou Folder ou File : Nouveau nom du fichier ou du dossier.

*Retour*
* None.

*Description*
* Renomme un fichier ou un dossier.
```
f = new Folder(".\folder");
f.Rename("oldName", "newName");
```

## Méthode ModificationDate
*Paramètres*
* None.

*Retour*
* String : La date de modification.

*Description*
* Retourne la date de modification.
```
f = new Folder(".\folder\myFile");
print(f.ModificationDate());
```