# Array
Cet objet représente un tableau d'objets. 
```
/* Initialisation */
collection = new Array();
collection[0] = "un";
collection[1] = "deux";
collection[2] = "trois";

/* Lecture */
print(collection[0]);
```
Il dispose également de méthodes permettant de modifier/rechercher une valeur dans le tableau.

# Référence
## Méthode insertValue `[]`
*Paramètres*
* Numeric : Position d'insertion de la valeur dans le tableau.
* Object : Valeur à ajouter dans le tableau.

*Retour*
* None.

*Description*
* Insère une valeur à une position donnée.
```
/*Insère toujours au début*/
collection = new Array();
collection[0] = "b";
collection[0] = "a";
/*collection = [a,b]*/
```

## Méthode insertList `[*]`
*Paramètres*
* Numeric : Position d'insertion de la valeur dans le tableau.
* Object : Liste à ajouter dans le tableau.

*Retour*
* None.

*Description*
* Insère une valeur à une position donnée.
```
/*Insère toujours au début*/
collection = new Array();
collection[0] = "b";
collection[1] = "a";
collection2 = new Array();
collection2[0*] = collection;
collection2[2] = "c";
/*collection2 = [a,b,c]*/
```

## Méthode removeValue `[]`
*Paramètres*
* Numeric : Position de suppression dans le tableau.

*Retour*
* None.

*Description*
* Suppression d'une valeur à une position donnée.
```
collection = new Array();
collection[0] = "a";
collection[1] = "b";
collection[0] = null;
/*collection = [b]*/
```

## Méthode getValue `[]`
*Paramètres*
* Numeric : Position de la valeur dans le tableau.

*Retour*
* Object : La valeur à la position donnée.

*Description*
* Retourne une valeur à une position donnée.
```
collection = new Array();
collection[0] = "a";
print(collection[0]);
```

## Méthode getList `[*]`
*Paramètres*
* Numeric : Position de la valeur dans le tableau.

*Retour*
* Object : La liste restante à la position donnée.

*Description*
* Retourne une valeur à une position donnée.
```
collection = new Array();
collection[0] = "a";
collection[1] = "b";
collection[2] = "c";
print(collection[1*]);
/*collection[1*] = [b,c]*/
```

## Méthode size `#`
*Paramètres*
* None.

*Retour*
* Numeric : La taille du tableau.

*Description*
* Retourne la taille du tableau.
```
collection = new Array();
collection[0] = "a";
collection[1] = "b";
print(#collection);
/*sortie : 2*/
```

## Méthode Sort
*Paramètres*
* Callback : Fonction de trie.

*Retour*
* None.

*Description*
* Trie un tableau.
```
function Alphabetical(value1, value2)
    (value1 < value2);
endfunction
collection = new Array();
collection[0] = "b";
collection[1] = "c";
collection[2] = "a";
collection.Sort(function:Alphabetical);
/*collection = [a,b,c]*/
```

## Méthode Find
*Paramètres*
* Callback : Fonction de recherche.

*Retour*
* None.

*Description*
* Recherche un élément dans un tableau.
```
function EqualA(value)
    (value =~ "a");
endfunction
collection = new Array();
collection[0] = "b";
collection[1] = "a";
collection[2] = "c";
pos = collection.Find(function:EqualA);
```