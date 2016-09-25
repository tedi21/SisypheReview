# WordXMLDocument
 Classe représentant un document XML.

# Référence
## Méthode CreateNode
*Paramètres*
* String : Le nom du noeud.

*Retour*
* WordXMLNode : Le noeud créé.

*Description*
*  Crée un nouveau noeud.
```
xml = new WordXML();
xml.Initialize();
xmlDocument = new WordXMLDocument();
xmlDocument.Parse("modelWord.xml");
rootNode = xmlDocument.DocumentNode;
contentNode = rootNode.Nodes(rootNode.BodyTag).Item(0);
/* Note : Pour insérer ou ajouter du texte, 
   utiliser les fonctions InsertString ou AppendString 
   de WordXMLNode qui gèrent plus efficacement 
   l'insertion des noeuds Paragraph, Run et Text. */
/* Insertion d'un nouveau paragraphe */
paragraphNode = xmlDocument.CreateNode(rootNode.ParagraphTag);
contentNode.Append(paragraphNode);
/* Insertion d'un nouveau run */
runNode = xmlDocument.CreateNode(rootNode.RunTag);
paragraphNode.Append(runNode);
/* Insertion d'un texte */
node = xmlDocument.CreateTextNode("Hello world !!!");
runNode.Append(node);
xmlDocument.Save();
xmlDocument = null;
xml.Terminate();
xml = null;
```

## Méthode CreateTextNode
*Paramètres*
* String : Le nom du noeud *Text*.

*Retour*
* WordXMLNode : Le noeud *Text* créé.

*Description*
*  Crée un noeud texte.
```
Voir l'exemple CreateNode.
```

## Méthode DocumentNode
*Paramètres*
* None.

*Retour*
* WordXMLNode : Le noeud racine du document XML.

*Description*
*  Retourne le noeud racine du document.
```
xml = new WordXML();
xml.Initialize();
xmlDocument = new WordXMLDocument();
xmlDocument.Parse("modelWord.xml");
rootNode = xmlDocument.DocumentNode;
nodes = rootNode.Evaluate("//o:Author");
inode = 0;
while inode < nodes.Length do
    node = nodes.Item(inode);
    print(node.Content);
    inode.Increment();
endwhile
nodes = null;
xmlDocument = null;
xml.Terminate();
xml = null;
```

## Méthode Parse
*Paramètres*
* String : Le nom du document Word.

*Retour*
* None.

*Description*
*  Ouvre un fichier Word XML.
```
Voir l'exemple DocumentNode.
```

## Méthode Save
*Paramètres*
* None.

*Retour*
* None.

*Description*
*  Enregistre le document.
```
Voir l'exemple CreateNode.
```
