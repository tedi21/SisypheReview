# WordXMLNodeList
 Classe représentant une liste de noeuds XML du document Word.

# Référence
## Méthode Item
*Paramètres*
* Numeric : L'indice du noeud dans la liste.

*Retour*
* WordXMLNode : Le noeud dans la liste à la position *i*.

*Description*
*  Retourne le noeud à l'index *i*.
```
xpathNodeList = rootNode.Evaluate("//o:Author");
inode = 0;
if inode < xpathNodeList.Length then
    /* Récupération du noeud dans la liste. */
    xpathNode = xpathNodeList.Item(inode);
endif
```

## Méthode Length
*Paramètres*
* None.

*Retour*
* Numeric : La taille de la liste.

*Description*
*  Retourne la taille de la liste.
```
Voir l'exemple Item.
```
