# Fonctions préprogrammées
Le langage propose trois fonctions préprogrammées : include, print et system.

# Référence
## Méthode include
*Paramètres*
* String : Chemin du fichier de script à interpreter.

*Retour*
* Bool : true si le fichier a été interpreté, false sinon.

*Description*
* Permet d'interpreter un fichier de script. Les fonctions définies dans le fichier sont rajoutées au contexte courant.
```
include(".\mesFonctions.td");
UneFonctionDefinieDansMesFonctions();
```

## Méthode print
*Paramètres*
* String : Texte à afficher.

*Retour*
* None.

*Description*
* Affiche le texte passé en paramètre dans la console.
```
print("Hello world !!!");
```

## Méthode system
*Paramètres*
* String : Commande à executer.

*Retour*
* None.

*Description*
* Execute une commande dans la console.
```
system("command.exe");
```