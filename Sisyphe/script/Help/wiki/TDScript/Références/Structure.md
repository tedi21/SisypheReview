# Structure
Cet objet représente une composition de sous-objets. Il permet de créer une hierarchie d'objets.
```
/* Initialisation */
personne = new Structure();
personne.Nom = "Dupont";
personne.Prenom = "Henri";
personne.Age = 30;
personne.Film = new Array();
personne.Film[0] = "Interstellar";

/* Lecture */
print(personne.Prenom & " " & personne.Nom);
```
Il dispose également de méthodes permettant de modifier/rechercher un champ composant la structure.

# Référence
## Méthode Fields
*Paramètres*
* Numeric : Indice dans la liste des champs.

*Retour*
* Structure {Name,Value} : Structure composée de deux champs réprésentant le nom et la valeur du champ.

*Description*
* Retourne le nom et la valeur du champ de la liste des champs.
```
/*Retourne le premier champ*/
f = personne.Fields(0);
print(f.Name);
print(f.Value);
/* sortie : Age 
            30 */
```

## Méthode Fields
*Paramètres*
* String : Nom du champ.

*Retour*
* None.

*Description*
* Insère ou supprime un champ.
```
/*Insère un champ Pseudonyme avec la valeur "Riton"*/
personne.Fields("Pseudonyme") = "Riton"; 
/*Supprime le champ Pseudonyme*/
personne.Fields("Pseudonyme") = null; 
```

## Méthode FieldsCount
*Paramètres*
* None.

*Retour*
* Numeric : Le nombre de champs.

*Description*
* Retourne le nombre de champs.
```
/*Retourne le nombre de champs*/
n = personne.FieldsCount();
```

## Méthode FindField
*Paramètres*
* String : Nom du champ à rechercher
* Object : Valeur du champ si celui-ci est trouvé.

*Retour*
* Bool : true si le champ est trouvé, false sinon.

*Description*
* Recherche du champ.
```
/*Recherche le champ Pseudonyme*/
v = "";
found = personne.FindField("Pseudonyme", v);
if found then
    print(v);
endif
```