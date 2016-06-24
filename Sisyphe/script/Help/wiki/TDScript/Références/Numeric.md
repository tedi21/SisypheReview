# Numeric
Cet objet représente un numérique. Il dispose diverses méthodes permettant de manipuler le numérique.

# Référence
## Méthode minus `-`
*Paramètres*
* None.

*Retour*
* Numeric : La valeur numérique sur laquelle l'opérateur moins a été appliqué.

*Description*
* Applique l'opérateur moins.
```
b = 1;
a = -b;
/* a = -1 */
```

## Méthode minus `-`
*Paramètres*
* Numeric : Valeur à soustraire

*Retour*
* Numeric : La valeur résultat de la soustraction.

*Description*
* Applique une soustraction.
```
a = 5;
b = 3;
c = a - b;
/* c = 2 */
```

## Méthode plus `+`
*Paramètres*
* Numeric : Valeur à additionner

*Retour*
* Numeric : La valeur résultat de l'addition.

*Description*
* Applique une addition.
```
a = 5;
b = 3;
c = a + b;
/* c = 8 */
```

## Méthode multiply `*`
*Paramètres*
* Numeric : Valeur à multiplier

*Retour*
* Numeric : La valeur résultat de la multiplication.

*Description*
* Applique une multiplication.
```
a = 5;
b = 3;
c = a * b;
/* c = 15 */
```

## Méthode Divide `/`
*Paramètres*
* Numeric : Valeur à diviser

*Retour*
* Numeric : La valeur résultat de la division.

*Description*
* Applique une division.
```
a = 15;
b = 3;
c = a / b;
/* c = 5 */
```

## Méthode inferior `<`
*Paramètres*
* Numeric : Valeur à comparer.

*Retour*
* Bool : true si la valeur est inférieure au numérique passé en paramètre, false sinon.

*Description*
* Indique si la valeur est inférieure à une autre valeur.
```
if a < 5 then
    print("a inférieure à 5");
endif
```

## Méthode inferiorOrEqual `<=`
*Paramètres*
* Numeric : Valeur à comparer.

*Retour*
* Bool : true si la valeur est inférieure ou égale à la valeur passée en paramètre, false sinon.

*Description*
* Indique si la valeur est inférieure ou égale à une autre valeur.
```
if a <= 5 then
    print("a inférieure à 5");
endif
```

## Méthode superior `>`
*Paramètres*
* Numeric : valeur à comparer.

*Retour*
* Bool : true si la valeur est supérieure à la valeur passée en paramètre, false sinon.

*Description*
* Indique si la valeur est supérieure à une autre valeur.
```
if a > 5 then
    print("a supérieure à 5");
endif
```

## Méthode superiorOrEqual `>=`
*Paramètres*
* Numeric : valeur à comparer.

*Retour*
* Bool : true si la valeur est supérieure ou égale à la valeur passée en paramètre, false sinon.

*Description*
* Indique si la valeur est supérieure ou égale à une autre valeur.
```
if a >= 5 then
    print("a supérieure à 5");
endif
```

## Méthode equals `==`
*Paramètres*
* Numeric : valeur à comparer.

*Retour*
* Bool : true si la valeur est égale à la valeur passée en paramètre, false sinon.

*Description*
* Indique si la valeur est égale à une autre valeur.
```
if a == 5 then
    print("a égale à 5");
endif
```

## Méthode notEquals `!=`
*Paramètres*
* Numeric : valeur à comparer.

*Retour*
* Bool : true si la valeur est différente à la valeur passée en paramètre, false sinon.

*Description*
* Indique si une valeur est différente d'une autre valeur.
```
if a != 5 then
    print("a différente de 5");
endif
```

## Méthode Increment
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Incrémente une valeur.
```
a = 5;
a.Increment();
/* a = 6 */
```

## Méthode Decrement
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Décrémente une valeur.
```
a = 5;
a.Decrement();
/* a = 4 */
```

## Méthode Parse
*Paramètres*
* String : Texte réprésentant une valeur numérique.

*Retour*
* None.

*Description*
* Convertit un texte en valeur numérique.
```
a = "5";
b = 0;
b.Parse(a);
/* b = 5 */
```

## Méthode ParseBase64
*Paramètres*
* String : Texte réprésentant un buffer binaire encodé en BASE64.
* Numeric : Position en bit dans le buffer.  
* Numeric : Taille en bit à analyser.

*Retour*
* None.

*Description*
* Convertit une valeur binaire en valeur numérique.
```
a = "AqB";
b = 0;
b.ParseBase64(a, 6, 4);
/* b = 10 */
```