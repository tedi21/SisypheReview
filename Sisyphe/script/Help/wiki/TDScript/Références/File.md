# File
Cet objet représente un fichier. Il dispose diverses méthodes permettant de manipuler un fichier.

# Référence
## Constructeur File
*Paramètres*
* String ou Folder : Chemin du fichier.
* String : Mode d'ouverture parmi APPEND, OVERWRITE ou NONE.
    * NONE : Ouvre le fichier en lecture.
    * APPEND :  Crée ou ouvre le fichier en écriture avec positionnement en fin de fichier.
	* OVERWRITE : Crée ou ouvre le fichier en écriture avec suppression du contenu.
* String : Codage du fichier. (format texte : ANSI, UTF16-LE, UTF16-BE, UTF8, ISO-8859-15; format binaire : BASE64)
    * ANSI.
	* UTF16-LE.
	* UTF16-BE.
	* UTF8.
	* ISO-8859-15.
	* BASE64.

*Retour*
* None.

*Description*
* Construit un fichier.
```
f = new File("Fichier.txt", "OVERWRITE", "ISO-8859-15");
```

## Méthode Open
*Paramètres*
* None.

*Retour*
* Bool : true si le fichier est ouvert, false sinon.

*Description*
* Indique si le fichier est ouvert.
```
f = new File("Fichier.txt", "NONE", "ISO-8859-15");
b = f.Open;
print(b);
```

## Méthode load `>>`
*Paramètres*
* String : Texte chargé depuis le fichier.

*Retour*
* Bool : true si le texte est correctement chargé.

*Description*
* Charge le texte contenu dans le fichier.
```
f = new File("Fichier.txt", "NONE", "ISO-8859-15");
if f.Open then
    str = "";
	f >> str;
endif
```

## Méthode save `<<`
*Paramètres*
* String : Texte à écrire dans le fichier.

*Retour*
* Bool : true si le texte est correctement écris.

*Description*
* Ecris le texte dans le fichier.
```
f = new File("Fichier.txt", "OVERWRITE", "ISO-8859-15");
str = "Hello world !!!";
f << str;
```

## Méthode size `#`
*Paramètres*
* None.

*Retour*
* Numeric : La taille du fichier.

*Description*
* Retourne la taille du fichier.
```
f = new File("Fichier.txt", "NONE", "ISO-8859-15");
if f.Open then
    n = #f;
endif
```