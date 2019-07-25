# String
Cet objet représente un texte. Il dispose diverses méthodes permettant de manipuler le texte.

# Référence
## Constante `CrLf`
*Description*
* Représente les caractères spéciaux `Carriage return` et `Line feed`.
```
str = "Hello World !!!" & CrLf;
```

## Constante `Cr`
*Description*
* Représente le caractère spécial `Carriage return`.
```
str = "Hello World !!!" & Cr;
```

## Constante `Lf`
*Description*
* Représente le caractère spécial `Line feed`.
```
str = "Hello World !!!" & Lf;
```

## Constante `Tab`
*Description*
* Représente le caractère spécial `Tabulation`.
```
str = Tab & "Hello World !!!";
```

## Constante `DblQuotes`
*Description*
* Représente le caractère spécial guillemet `"`.
```
str = DblQuotes & "Hello World !!!" & DblQuotes;
```

## Méthode concat `&`
*Paramètres*
* String : Texte à concatener.

*Retour*
* String : Les deux textes concaténés.

*Description*
* Concatène les deux textes.
```
str = "Hello " & "World !!!";
```

## Méthode inferior `<`
*Paramètres*
* String : texte à comparer.

*Retour*
* Bool : true si le texte est inférieur au texte passé en paramètre, false sinon.

*Description*
* Indique si un texte est inférieur à un autre texte.
```
if a < "toto" then
    print("a inférieur à toto");
endif
```

## Méthode inferiorOrEqual `<=`
*Paramètres*
* String : texte à comparer.

*Retour*
* Bool : true si le texte est inférieur ou égal au texte passé en paramètre, false sinon.

*Description*
* Indique si un texte est inférieur ou égal à un autre texte.
```
if a <= "toto" then
    print("a inférieur à toto");
endif
```

## Méthode superior `>`
*Paramètres*
* String : texte à comparer.

*Retour*
* Bool : true si le texte est supérieur au texte passé en paramètre, false sinon.

*Description*
* Indique si un texte est supérieur à un autre texte.
```
if a > "tata" then
    print("a supérieur à tata");
endif
```

## Méthode superiorOrEqual `>=`
*Paramètres*
* String : texte à comparer.

*Retour*
* Bool : true si le texte est supérieur ou égal au texte passé en paramètre, false sinon.

*Description*
* Indique si un texte est supérieur ou égal à un autre texte.
```
if a >= "tata" then
    print("a supérieur à tata");
endif
```

## Méthode equals `==`
*Paramètres*
* String : texte à comparer.

*Retour*
* Bool : true si le texte est égal au texte passé en paramètre, false sinon.

*Description*
* Indique si un texte est égal à un autre texte.
```
if a == "toto" then
    print("a égal à toto");
endif
```

## Méthode notEquals `!=`
*Paramètres*
* String : texte à comparer.

*Retour*
* Bool : true si le texte est différent du texte passé en paramètre, false sinon.

*Description*
* Indique si un texte est différent d'un autre texte.
```
if a != "toto" then
    print("a différent de toto");
endif
```

## Méthode iequals `=~`
*Paramètres*
* String : texte à comparer.

*Retour*
* Bool : true si le texte est égal au texte passé en paramètre en n'étant pas sensible à la casse, false sinon.

*Description*
* Indique si un texte est égal à un autre texte sans vérification de la casse.
```
if a =~ "ToTo" then
    print("a égal à toto");
endif
```

## Méthode notIEquals `!~`
*Paramètres*
* String : texte à comparer.

*Retour*
* Bool : true si le texte est différent du texte passé en paramètre en n'étant pas sensible à la casse, false sinon.

*Description*
* Indique si un texte est différent d'un autre texte sans vérification de la casse.
```
if a !~ "ToTo" then
    print("a différent de toto");
endif
```

## Méthode size `#`
*Paramètres*
* None.

*Retour*
* Numeric : le nombre de caractères du texte.

*Description*
* Retourne le nombre de caractères que constitue le texte.
```
a = "Hello world !!!";
n = #a;
/* n = 15 */
```

## Méthode insertValue `[]`
*Paramètres*
* Numeric : Position d'insertion du caractère.
* Object : Caractère à ajouter dans la chaîne de caractères

*Retour*
* None.

*Description*
* Insère un caractère à une position donnée.
```
/*Insère toujours au début*/
str = new String();
str[0] = "b";
str[0] = "a";
/*str = "ab"*/
```

## Méthode getValue `[]`
*Paramètres*
* Numeric : Position du caractère..

*Retour*
* Object : Caractère à la position donnée.

*Description*
* Retourne un caractère à une position donnée.
```
str = "ab";
print(str[0]);
```

## Méthode Append
*Paramètres*
* String : Texte à ajouter.

*Retour*
* None.

*Description*
* Ajoute un texte à la fin du texte courant.
```
content = "Hello world ";
content.Append("!!!");
/* content = "hello world !!!" */
```

## Méthode Insert
*Paramètres*
* Numeric : Position du texte à insérer.
* String : Texte à insérer.

*Retour*
* None.

*Description*
* Insère un texte à une position souhaitée.
```
content = "Hello !!!";
content.Insert(5, " world");
/* content = "hello world !!!" */
```

## Méthode Remove
*Paramètres*
* Numeric : Position du texte à supprimer.
* Numeric : Longueur du texte à supprimer.

*Retour*
* None.

*Description*
* Supprime une portion de texte à une position souhaitée.
```
content = "Hello world !!!";
content.Remove(5, 6);
/* content = "hello !!!" */
```

## Méthode SubString
*Paramètres*
* Numeric : Position du texte à extraire.
* Numeric : Longueur du texte à extraire.

*Retour*
* String : Le texte extrait.

*Description*
* Extrait une sous-chaîne dans le texte courant.
```
content = "Hello world !!!";
w = content.SubString(5, 6);
/* w = "world " */
```

## Méthode insertValue `[]`
*Paramètres*
* Numeric : Position d'insertion de la valeur dans la chaîne de caractères.
* String : Caractère à ajouter.

*Retour*
* None.

*Description*
* Insère une valeur à une position donnée.
```
/*Insère toujours au début*/
str = new String();
str[0] = "b";
str[0] = "a";
/*str = "ab"*/
```

## Méthode removeValue `[]`
*Paramètres*
* Numeric : Position de suppression dans la chaîne de caractères.

*Retour*
* None.

*Description*
* Suppression d'une valeur à une position donnée.
```
str = new String();
str[0] = "a";
str[1] = "b";
str[0] = null;
/*str = "b"*/
```

## Méthode getValue `[]`
*Paramètres*
* Numeric : Position de la valeur dans la chaîne de caractères.

*Retour*
* String : Le caractère à la position donnée.

*Description*
* Retourne un caractère à une position donnée.
```
str = new String();
str[0] = "a";
print(str[0]);
```

## Méthode Match
*Paramètres*
* String : Expression régulière.
* Match : Les valeurs capturées par l'expression régulière.

*Retour*
* Bool : true si le texte correspond à l'expression régulière, false sinon.

*Description*
* Indique si le texte correspond à une expression régulière.
```
m = new Match(); 
content = "Hello world !!!";
if content.Match("(\w+)\s+(\w+).*", m) then
    print(m.String);
endif
```

## Méthode Search
*Paramètres*
* Numeric : Position de début dans le texte où commencer la recherche.
* Numeric : Position de fin dans le texte où arrêter la recherche.
* String : Expression régulière.
* Match : Les valeurs capturées par l'expression régulière.
* Numeric : Position après le texte trouvé.

*Retour*
* Bool : true si l'expression régulière a été trouvé dans le texte, false sinon.

*Description*
* Recherche une expression régulière dans le texte.
```
m = new Match(); 
content = "Hello world !!!";
i = 0;
while content.Search(i, #content, "\w+", m, i) do
	print(m.String);
endwhile
/* sortie : hello 
            world */
```

## Méthode Split
*Paramètres*
* String : Expression régulière.

*Retour*
* Array of String : Les sous-chaînes découpées par l'expression régulière.

*Description*
* Découpe un texte à partir d'une expression régulière.
```
content = "Hello world !!!";
words = content.Split("\s+");
/* words = [hello,world,!!!] */
```

## Méthode ReplaceAll
*Paramètres*
* String : Chaîne de caractères à rechercher.
* String : Chaîne de caractères à remplacer.

*Retour*
* None.

*Description*
* Remplace toutes les occurences par une valeur de remplacement.
```
content = "Hello world !!!";
content.ReplaceAll("world", "everybody");
```