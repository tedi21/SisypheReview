# Script
Le langage TDScript est un langage de script. La ligne de commande pour executer un script est la suivante :
```
tdscript.exe <file> -v <log level> [-module <moduleName> <moduleParameters>]

<file>       : UTF-16LE input file
<log level>  : log level
<moduleName> : module name
<moduleParameters> : module parameters
```
L'option `-module <moduleName> <moduleParameters>` est optionnelle.

# Commentaire
Le langage donne la possibilité de réaliser des commentaires à l'aide des balises `/* */`. 
```
/* ceci est un commentaire */
```

# Variable
Le langage ne possède pas de déclaration de variable au sens strict car l'initialisation d'une variable vaut déclaration.

Pour créer une variable, il suffit donc d'indiquer sa valeur.

* Pour une string : `str = "Un texte";`
* Pour un numérique : `num = 12.34;`
* Pour un booléen : `b = true;`
* Pour un objet : `obj = new Array();`

Les variables sont automatiquement supprimées à la fin de la portée (c'est à dire à la fin de la fonction). Il est possible de supprimer explicitement une variable en l'affectant à `null` : 
```
val = null;
```

Les objets possèdent tous une conversion vers le type `String`. Toutes les opérations possibles sur le type `String` sont donc possibles sur tous les objets.
```
a = new Array();
a[0] = true; 
a[1] = 1 & 2;
a[2] = new Folder(".\");
print(a);
/* conversion du tableau et de son contenu en String */
/* sortie : [true,12,.\] */
```

# Affectation
L'affectation d'une variable ne réalise pas une copie de la variable mais ajoute une référence à la variable. Par exemple dans le code suivant, la variables `a` et `b` pointent vers la même valeur `6`.
```
a = 5;
b = a;
b.Increment();
```

Il est parfois nécessaire de réaliser une copie de la variable. C'est pour cela que le langage dispose d'un opérateur `:=`. Dans le code suivant, la variable `a` vaut `5` et la variable `b` vaut `6`.
```
a = 5;
b := a;
b.Increment();
```

# Condition
Les mots clés du langage permettant de faire un branchement conditionnel sont les suivants.
```
if i == 0 then
    print("i égale à 0");
else
    print("i différent de 0");
endif
```
Le branchement `else` est optionnel.

# Boucle
Le langage offre la possibilité de faire une boucle. Le code suivant permet par exemple d'afficher l'ensemble des valeurs d'un tableau.
```
i = 0;
while i < #list do
    print(list[i]);
    i.Increment();
endwhile
```

# Fonction
Le langage permet de réaliser des fonctions. La dernière instruction est considérée comme la valeur de retour.
Les paramètres des fonctions sont passés par référence. 
Les déclarations doivent être obligatoirement faites en **début de fichier après la déclaration des constantes et avant la première instruction**.
Etudions le code suivant :
```
function AddAndSubstract(a, b, c)
    d = a + b;
    c = b - a;
    /*return*/ d;
endfunction

v1 = 5;
v2 = 6;
v3 = 0;
v4 = AddAndSubstract(v1, v2, v3);
print(v1 & " " & v2 & " " & v3 & " " & v4);
```
La dernière instruction est `d;`, la fonction retourne donc la valeur de `d` c'est à dire `11`. Les paramètres `a` et `b` n'ont pas été modifiés, les valeurs de `v1` et `v2` sont respectivement `5` et `6`. le paramètre `c` a été modifié, la valeur de `v3` est `1`.
Le code ci-dessus produit donc comme affichage `5 6 1 11`.

# Globale
Le langage donne la possibilité de spécifier qu'une variable soit accessible dans n'importe quel portion de code sans distinction de portée à l'aide du mot-clé `constant`.
```
constant MAX_VALUE = 3;
constant ARRAY_TEST = new Array();
```
Cette variable ne peut pas être réaffectée à une autre valeur. Les déclarations doivent être obligatoirement faites en **début de fichier**. Pour faire appel à cette variable, le mot-clé `constant:` doit précèder le nom.
```
i = 0;
while i < constant:MAX_VALUE do
    constant:ARRAY_TEST[i] = i;
    i.Increment();
endwhile
```

