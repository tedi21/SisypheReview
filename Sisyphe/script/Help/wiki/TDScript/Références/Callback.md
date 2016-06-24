# Fonction Callback
Une fonction peut-être utilisée comme un objet du langage. Par conséquent, une fonction peut être passée en paramètre d'une autre fonction. Considérons le code suivant :
```
function Max(value)
    if vMax < value then
        vMax = value;
    endif
endfunction

function Min(value)
    if vMin > value then
        vMin = value;
    endif
endfunction

function Enumerate(array, f)
    i = 0;
    while i < #array do
        params = new Array();
        params[0] = array[i];
        f.Call(params);
        i.Increment();
    endwhile
endfunction

a = new Array();
a[0] = 1;
a[1] = 5;
a[2] = 10;

fMax = function:Max;
fMax.Variables("vMax") = -1;
fMin = function:Min;
fMin.Variables("vMin") = 20;

Enumerate(a, fMax);
Enumerate(a, fMin);
print(fMax.Variables(0).Name & "=" & fMax.Variables(0).Value);
print(fMin.Variables(0).Name & "=" & fMin.Variables(0).Value);
```
Le code ci-dessus montre deux fonctions `Max` et `Min`. On utilise l'opérateur `function:` pour indiquer que l'on souhaite manipuler la fonction comme un objet. On peut ensuite appeler des méthodes sur cet objet. 

Dans l'exemple, on ajoute une nouvelle variable `vMax`et `vMin` aux fonctions callback `fMax` et `fMin` à l'aide de la méthode `Variables`.
La fonction `Enumerate` prend en second paramètre la fonction callback. La méthode `Call` est ensuite appelée pour réaliser l'execution de la fonction.

Enfin, on récupère la première variable de la fonction callback pour afficher son nom et sa valeur.
Le code ci-dessus produit donc l'affichage suivant `vMax=10 vMin=1`.

# Référence
## Méthode Call
*Paramètres*
* Array : Tableau des paramètres passé à la fonction callback.

*Retour*
* Object : Retour de la fonction callback.

*Description*
* Appel de la fonction callback.
```
/*Appel de la fonction callback avec les paramètres 10 et "Text"*/
params[0] = 10;
params[1] = "Text";
ret = fct.Call(params);
```

## Méthode FindVariable
*Paramètres*
* String : Nom de la variable à rechercher
* Object : Valeur de la variable si celle-ci est trouvée.

*Retour*
* Bool : true si la variable est trouvée, false sinon.

*Description*
* Recherche de la variable dans la fonction callback.
```
/*Recherche la variable var1*/
v = "";
found = fct.FindVariable("var1", v);
if found then
    print(v);
endif
```

## Méthode FunctionName
*Paramètres*
* None.

*Retour*
* String : Nom de la fonction callback.

*Description*
* Retourne le nom de la fonction.
```
/*Retourne le nom de la fonction*/
name = fct.FunctionName();
```

## Méthode Parameters
*Paramètres*
* None.

*Retour*
* Array of string : Tableaux des noms des paramètres.

*Description*
* Retourne les noms des paramètres de la fonction.
```
/*Retourne la liste des paramètres*/
parameters = fct.Parameters();
```

## Méthode Variables
*Paramètres*
* Numeric : Indice dans la liste des variables.

*Retour*
* Structure {Name,Value} : Structure composée de deux champs réprésentant le nom et la valeur de la variable.

*Description*
* Retourne le nom et la valeur d'une variable de la liste des variables.
```
/*Retourne le premier paramètre*/
parameter = fct.Variables(0);
print(parameter.Name);
print(parameter.Value);
```

## Méthode Variables
*Paramètres*
* String : Nom de la variable.

*Retour*
* None.

*Description*
* Insère ou supprime une variable.
```
/*Insère la variable var1 avec la valeur 100*/
fct.Variables("var1") = 100; 
/*Supprime la variable var1*/
fct.Variables("var1") = null; 
```

## Méthode VariablesCount
*Paramètres*
* None.

*Retour*
* Numeric : Le nombre de variables de la fonction callback.

*Description*
* Retourne le nombre de variables de la fonction callback.
```
/*Retourne le nombre de variables*/
n = fct.VariablesCount();
```
