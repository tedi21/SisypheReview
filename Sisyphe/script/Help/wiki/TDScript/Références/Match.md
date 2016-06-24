# Match
Cet objet représente une capture réalisée par une expression régulière.

# Référence
## Méthode String
*Paramètres*
* None.

*Retour*
* String : Le texte capturé par l'expression régulière.

*Description*
* Retourne le texte capturé par l'expression régulière.
```
m = new Match(); 
content = "Hello world !!!";
if content.Match("(\w+)\s+(\w+).*", m) then
    print(m.String);
endif
/* sortie : Hello world !!! */
```

## Méthode SubStrings
*Paramètres*
* None.

*Retour*
* String : La sous-chaîne capturée par l'expression régulière.

*Description*
* Retourne la sous-chaîne capturé par l'expression régulière.
```
m = new Match(); 
content = "Hello world !!!";
if content.Match("(\w+)\s+(\w+).*", m) then
    print(m.SubStrings[1]);
endif
/* sortie : Hello*/
```

## Méthode Prefix
*Paramètres*
* None.

*Retour*
* String : Le texte précèdent la chaîne capturée par l'expression régulière.

*Description*
* Retourne le texte précèdent la chaîne capturée par l'expression régulière.
```
m = new Match(); 
content = "Hello world !!!";
i = 0;
if content.Search(i, #content, "w\w+", m, i) then
	print(m.Prefix);
endif
/* sortie : Hello */
```

## Méthode Suffix
*Paramètres*
* None.

*Retour*
* String : Le texte suivant la chaîne capturée par l'expression régulière.

*Description*
* Retourne le texte suivant la chaîne capturée par l'expression régulière.
```
m = new Match(); 
content = "Hello world !!!";
i = 0;
if content.Search(i, #content, "w\w+", m, i) then
	print(m.Suffix);
endif
/* sortie :  !!!*/
```

## Méthode StringPos
*Paramètres*
* None.

*Retour*
* Numeric : La position de la chaîne capturée par l'expression régulière dans le texte.

*Description*
* Retourne la position de la chaîne capturée par l'expression régulière dans le texte.
```
m = new Match(); 
content = "Hello world !!!";
i = 0;
if content.Search(i, #content, "w\w+", m, i) then
	print(m.StringPos);
endif
/* sortie :  6*/
```

## Méthode SubStringsPos
*Paramètres*
* None.

*Retour*
* Numeric : La position de la sous-chaîne capturée par l'expression régulière dans le texte.

*Description*
* Retourne la position de la sous-chaîne capturée par l'expression régulière dans le texte.
```
m = new Match(); 
content = "Hello world !!!";
i = 0;
if content.Search(i, #content, "Hello (\w+)", m, i) then
	print(m.SubStringsPos[1]);
endif
/* sortie :  6*/
```