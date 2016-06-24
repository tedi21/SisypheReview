# WordXMLNode
 Classe représentant un noeud XML du document Word.

# Référence
## Constante `DocumentTag`
*Description*
* Le nom du noeud *DOCUMENT*. 
```
xmlDocument = new WordXMLDocument();
xmlDocument.Parse("modelWord.xml");
rootNode = xmlDocument.DocumentNode;
print(rootNode.DocumentTag == rootNode.TagName);
```

## Constante `BodyTag`
*Description*
* Le nom du noeud *BODY*. 
```
xmlDocument = new WordXMLDocument();
xmlDocument.Parse("modelWord.xml");
rootNode = xmlDocument.DocumentNode;
bodyNode = rootNode.Nodes(rootNode.BodyTag).Item(0);
print(bodyNode.TagName);
```

## Constante `SectionTag`
*Description*
* Le nom du noeud *SECTION*. 
```
xmlDocument = new WordXMLDocument();
xmlDocument.Parse("modelWord.xml");
rootNode = xmlDocument.DocumentNode;
nodes = rootNode.Evaluate("//" & (rootNode.SectionTag));
if nodes.Length > 0 then
    print(nodes.Item(0).TagName);
endif
```

## Constante `SubSectionTag`
*Description*
* Le nom du noeud *SUBSECTION*. 
```
xmlDocument = new WordXMLDocument();
xmlDocument.Parse("modelWord.xml");
rootNode = xmlDocument.DocumentNode;
nodes = rootNode.Evaluate("//" & (rootNode.SubSectionTag));
if nodes.Length > 0 then
    print(nodes.Item(0).TagName);
endif
```

## Constante `TableTag`
*Description*
* Le nom du noeud *TABLE*. 
```
xmlDocument = new WordXMLDocument();
xmlDocument.Parse("modelWord.xml");
rootNode = xmlDocument.DocumentNode;
nodes = rootNode.Evaluate("//" & (rootNode.TableTag));
if nodes.Length > 0 then
    print(nodes.Item(0).TagName);
endif
```

## Constante `RowTag`
*Description*
* Le nom du noeud *ROW*. 
```
xmlDocument = new WordXMLDocument();
xmlDocument.Parse("modelWord.xml");
rootNode = xmlDocument.DocumentNode;
nodes = rootNode.Evaluate("//" & (rootNode.RowTag));
if nodes.Length > 0 then
    print(nodes.Item(0).TagName);
endif
```

## Constante `CellTag`
*Description*
* Le nom du noeud *CELL*. 
```
xmlDocument = new WordXMLDocument();
xmlDocument.Parse("modelWord.xml");
rootNode = xmlDocument.DocumentNode;
nodes = rootNode.Evaluate("//" & (rootNode.CellTag));
if nodes.Length > 0 then
    print(nodes.Item(0).TagName);
endif
```

## Constante `ParagraphTag`
*Description*
* Le nom du noeud *PARAGRAPH*. 
```
xmlDocument = new WordXMLDocument();
xmlDocument.Parse("modelWord.xml");
rootNode = xmlDocument.DocumentNode;
nodes = rootNode.Evaluate("//" & (rootNode.ParagraphTag));
if nodes.Length > 0 then
    print(nodes.Item(0).TagName);
endif
```

## Constante `RevisionTag`
*Description*
* Le nom du noeud *REVISION*. 
```
xmlDocument = new WordXMLDocument();
xmlDocument.Parse("modelWord.xml");
rootNode = xmlDocument.DocumentNode;
nodes = rootNode.Evaluate("//" & (rootNode.RevisionTag));
if nodes.Length > 0 then
    print(nodes.Item(0).TagName);
endif
```

## Constante `RunTag`
*Description*
* Le nom du noeud *RUN*. 
```
xmlDocument = new WordXMLDocument();
xmlDocument.Parse("modelWord.xml");
rootNode = xmlDocument.DocumentNode;
nodes = rootNode.Evaluate("//" & (rootNode.RunTag));
if nodes.Length > 0 then
    print(nodes.Item(0).TagName);
endif
```

## Constante `NoLength`
*Description*
* Valeur par défaut indiquant que le paramètre de la taille est à ignorer (cf. méthode *eraseString*). 
```
xmlDocument = new WordXMLDocument();
xmlDocument.Parse("modelWord.xml");
rootNode = xmlDocument.DocumentNode;
nodes = rootNode.Evaluate("//" & (rootNode.CellTag));
inode = 0;
while inode < nodes.Length do
    node = nodes.Item(inode);
    /* Supprime tous les textes contenus dans les cellules des tableaux. */
    node.EraseString(false, 0, rootNode.NoLength);
    /* Une cellule doit contenir au minimum un paragraphe. */
    node.AppendString(false, "");
    inode = inode + 1;
endwhile
```

## Méthode TagName
*Paramètres*
* None.

*Retour*
* String : Le tag du noeud courant.

*Description*
*  Retourne le nom du noeud.
```
Voir l'exemple AppendString.
```

## Méthode Evaluate
*Paramètres*
* String : La requête XPath.

*Retour*
* WordXMLNodeList : La liste des noeuds résultat de la requête XPath.

*Description*
*  Execute une requête XPath.
```
Voir l'exemple AppendString.
```

## Méthode Nodes
*Paramètres*
* None.

*Retour*
* WordXMLNodeList : La liste des noeuds fils du noeud courant.

*Description*
*  Retourne les noeuds fils.
```
Voir l'exemple AppendString.
```

## Méthode Nodes
*Paramètres*
* String : Le tag des noeuds fils à considérer.

*Retour*
* WordXMLNodeList : La liste des noeuds fils avec le tag *tagName* du noeud courant.

*Description*
*  Retourne les noeuds fils avec le nom *tagName*.
```
Voir l'exemple AppendString.
```

## Méthode NextNode
*Paramètres*
* None.

*Retour*
* WordXMLNode : Le noeud suivant ou un noeud invalide si le noeud suivant n'existe pas.

*Description*
*  Retourne le noeud suivant.
```
xmlDocument = new WordXMLDocument();
xmlDocument.Parse("modelWord.xml");
rootNode = xmlDocument.DocumentNode;
node = rootNode.Nodes(rootNode.ParagraphTag).Item(0);
/* Liste les noeuds du même niveau suivant le noeud node */
while node.Validity do
    print(node.TagName);
    node = node.NextNode;
endwhile
```

## Méthode NextNode
*Paramètres*
* String : Le tag des noeuds suivant à considérer.

*Retour*
* WordXMLNode : Le noeud *tagName* suivant ou un noeud invalide si le noeud *tagName* suivant n'existe pas.

*Description*
*  Retourne le noeud suivant avec le nom *tagName*.
```
xmlDocument = new WordXMLDocument();
xmlDocument.Parse("modelWord.xml");
rootNode = xmlDocument.DocumentNode;
node = rootNode.Nodes(rootNode.ParagraphTag).Item(0);
/* Liste les noeuds Paragraph du même niveau suivant le noeud node */
while node.Validity do
    print(node.TagName);
    node = node.NextNode(rootNode.ParagraphTag);
endwhile
```

## Méthode PreviousNode
*Paramètres*
* None.

*Retour*
* WordXMLNode : Le noeud précédant ou un noeud invalide si le noeud précédant n'existe pas.

*Description*
*  Retourne le noeud précèdent.
```
xmlDocument = new WordXMLDocument();
xmlDocument.Parse("modelWord.xml");
rootNode = xmlDocument.DocumentNode;
nodeList = rootNode.Nodes(rootNode.ParagraphTag);
node = nodeList.Item(nodeList.Length - 1);
/* Liste les noeuds du même niveau précédant le noeud node. */
while node.Validity do
    print(node.TagName);
    node = node.PreviousNode;
endwhile
```

## Méthode PreviousNode
*Paramètres*
* String : Le tag des noeuds précèdant à considérer.

*Retour*
* WordXMLNode : Le noeud *tagName* précédant ou un noeud invalide si le noeud *tagName* précédant n'existe pas.

*Description*
*  Retourne le noeud précèdent avec le nom *tagName*.
```
xmlDocument = new WordXMLDocument();
xmlDocument.Parse("modelWord.xml");
rootNode = xmlDocument.DocumentNode;
nodeList = rootNode.Nodes(rootNode.ParagraphTag);
node = nodeList.Item(nodeList.Length - 1);
/* Liste les noeuds Paragraph du même niveau précédant le noeud node. */
while node.Validity do
    print(node.TagName);
    node = node.PreviousNode(rootNode.ParagraphTag);
endwhile
```

## Méthode Parent
*Paramètres*
* None.

*Retour*
* WordXMLNode : Le noeud Parent du noeud courant ou un noeud invalide si le noeud Parent n'existe pas.

*Description*
*  Retourne le noeud parent.
```
Voir l'exemple AppendString.
```

## Méthode Parent
*Paramètres*
* String : 

*Retour*
* WordXMLNode : Le noeud Parent avec le tag *tagName* du noeud courant ou un noeud invalide si le noeud Parent avec le tag *tagName* n'existe pas.

*Description*
*  Retourne le noeud parent avec le nom *tagName*.
```
Voir l'exemple AppendString.
```

## Méthode Content
*Paramètres*
* None.

*Retour*
* String : Le contenu d'un noeud XML.

*Description*
*  Retourne le contenu d'un noeud.
```
Voir l'exemple AppendString.
```

## Méthode HasAttribute
*Paramètres*
* String : Le nom de l'attribut.

*Retour*
* Bool : True, si l'attribut existe, False sinon.

*Description*
*  Indique si le noeud à un attribut *attrName*.
```
print(node.HasAttribute("w:val"));
```

## Méthode Attributes
*Paramètres*
* String : Le tag de l'attribut à rechercher.

*Retour*
* String : La valeur de l'attribut.

*Description*
*  Retourne la valeur de l'attribut *attrName*.
```
Voir l'exemple AppendString.
```

## Méthode AttributesNames
*Paramètres*
* None.

*Retour*
* StringList : La liste des attributs du noeud courant.

*Description*
*  Retourne les noms des attributs du noeud.
```
xmlDocument = new WordXMLDocument();
xmlDocument.Parse("modelWord.xml");
rootNode = xmlDocument.DocumentNode;
nameList = rootNode.AttributesNames;
it = nameList.Begin;
while it != nameList.End do
    print(it.Current);
    it.Increment();
endwhile
```

## Méthode GetString
*Paramètres*
* None.

*Retour*
* String : Le texte concaténé contenu dans les noeuds fils du noeud courant.

*Description*
*  Retourne le texte brut du noeud.
```
xmlDocument = new WordXMLDocument();
xmlDocument.Parse("modelWord.xml");
rootNode = xmlDocument.DocumentNode;
print(rootNode.GetString());
```

## Méthode Document
*Paramètres*
* None.

*Retour*
* WordXMLDocument : Une référence vers l'objet *Document* contenant le noeud.

*Description*
*  Retourne le document.
```
xmlDocumentPtr = node.Document;
rootNode = xmlDocumentPtr.DocumentNode;
```

## Méthode Validity
*Paramètres*
* None.

*Retour*
* Bool : Indique si le noeud est un noeud XML valide du document.

*Description*
*  Indique si le noeud est valide.
```
print(node.Validity);
```

## Méthode Content
*Paramètres*
* String : Le contenu du noeud.

*Retour*
* None.

*Description*
*  Définit le contenu.
```
Voir l'exemple AppendString.
```

## Méthode Attributes
*Paramètres*
* String : Le nom de l'attribut.
* String : La valeur de l'attribut.

*Retour*
* None.

*Description*
*  Définit un attribut.
```
Voir l'exemple AppendString.
```

## Méthode removeAttributes
*Paramètres*
* String : La nom de l'attribut.

*Retour*
* None.

*Description*
*  Supprime un attribut.
```
node.Attributes("w:val") = null;
```

## Méthode PropertiesNode
*Paramètres*
* None.

*Retour*
* WordXMLNode : Le noeud propriétés pour le noeud courant.

*Description*
*  Retourne le noeud Propriétés correspondant au noeud conteneur en cours ou crée le noeud si celui-ci n'existe pas.
```
Voir l'exemple AppendString.
```

## Méthode PropertiesNode
*Paramètres*
* WordXMLNode : Le noeud propriétés pour le noeud courant.

*Retour*
* None.

*Description*
*  Définit le noeud *Propriétés*.
```
Voir l'exemple AppendString.
```

## Méthode removePropertiesNode
*Paramètres*
* None.

*Retour*
* None.

*Description*
*  Supprime le noeud *Propriétés*.
```
node.PropertiesNode = null;
```

## Méthode Append
*Paramètres*
* WordXMLNode : Le nouveau noeud à ajouter.

*Retour*
* None.

*Description*
*  Ajoute un nouveau noeud.
```
Voir l'exemple AppendString.
```

## Méthode Erase
*Paramètres*
* None.

*Retour*
* None.

*Description*
*  Supprime le noeud.
```
Voir l'exemple AppendString.
```

## Méthode Replace
*Paramètres*
* WordXMLNode : Le nouveau noeud.
* WordXMLNode : L'ancien noeud.

*Retour*
* None.

*Description*
*  Remplace un noeud.
```
node.Replace(newChild, oldChild);
```

## Méthode InsertBefore
*Paramètres*
* WordXMLNode : Le nouveau noeud à insérer.
* WordXMLNode : Le noeud suivant le noeud à insérer. Détermine la position du noeud à insérer dans la liste.

*Retour*
* None.

*Description*
*  Insère un nouveau noeud.
```
node.InsertBefore(newChild, refChild);
```

## Méthode CloneNode
*Paramètres*
* Bool : Indique si la copie se fait en profondeur ou non. Si la copie se fait en profondeur, les noeuds fils sont aussi copiés. Dans le cas contraire, seulement le noeud est copié.

*Retour*
* WordXMLNode : Le noeud copié.

*Description*
*  Clone le noeud.
```
node.CloneNode(true);
```

## Méthode AppendString
*Paramètres*
* Bool : True, active le suivi de modification. False, le texte ajouté n'est pas en suivi de modification.
* String : Le texte à ajouter.

*Retour*
* WordXMLNodeList : La liste des noeuds *run <w:r>* créés lors de l'ajout du texte.

*Description*
*  Ajoute du texte.
```
xml = new WordXML();
xml.Initialize();
xmlDocument = new WordXMLDocument();
xmlDocument.Parse("modelWord.xml");
rootNode = xmlDocument.DocumentNode;
/* Mise à jour de l'auteur. */
/* Recherche des noeuds o:Author et o:Revision. */
xpathNodeList = rootNode.Evaluate("//o:Author | //o:Revision");
inode = 0;
while inode < xpathNodeList.Length do
    /* Récupération du noeud dans la liste. */
    xpathNode = xpathNodeList.Item(inode);
    /* Suppression du contenu précèdent : suppression du noeud fils. */
    xpathNode.Nodes.Item(0).Erase();
    if xpathNode.TagName == "o:Author" then
        /* Ajout d'un nouveau contenu pour l'auteur. */
        xpathNode.Content = "WordXML";
    else
        /* Ajout d'un nouveau contenu pour la révision. */
        xpathNode.Content = "1";
    endif
    inode.Increment();
endwhile
xpathNodeList = null;
/* Ajout d'un texte dans le document */
bodyNode = rootNode.Nodes(rootNode.BodyTag).Item(0);
nodeList = bodyNode.AppendString(false, 
"Title" & CrLf & 
"All that we see or seem is but a dream within a dream." & CrLf & 
"Edgar Allan Poe");
/* Ajout du Style */
/* en gras pour le titre */
nodeTitleProperties = nodeList.Item(0).PropertiesNode;
boldNode = xmlDocument.CreateNode("w:b");
nodeTitleProperties.Append(boldNode);
/* en italique pour l'auteur */
nodeAuthorProperties = nodeList.Item(2).PropertiesNode;
italicNode = xmlDocument.CreateNode("w:i");
nodeAuthorProperties.Append(italicNode );
/* Paragraphe de l'auteur avec un alignement centré */
nodeParagraphProperties = nodeList.Item(2)
                        .Parent(rootNode.ParagraphTag).PropertiesNode;
alignNode = xmlDocument.CreateNode("w:jc");
alignNode.Attributes("w:val") = "center";
nodeParagraphProperties.Append(alignNode);
/* Suppression du mot Title */
bodyNode.EraseString(true, 0, 5);
/* Insertion du mot Quote */
bodyNode.InsertString(true, 0, "Quote");
xmlDocument.Save();
xmlDocument = null;
xml.Terminate();
xml = null;
```

## Méthode EraseString
*Paramètres*
* Bool : True, active le suivi de modification. False, le texte supprimé n'est pas en suivi de modification.
* Numeric : La position de départ du texte à supprimer.
* Numeric : La longueur du texte à supprimer.

*Retour*
* None.

*Description*
*  Supprime du texte.
```
Voir l'exemple AppendString.
```

## Méthode InsertString
*Paramètres*
* Bool : True, active le suivi de modification. False, le texte inséré n'est pas en suivi de modification.
* Numeric : La position de départ du texte à insérer.
* String : Le texte à insérer.

*Retour*
* WordXMLNodeList : La liste des noeuds *run <w:r>* créés lors de l'insertion du texte.

*Description*
*  Insère du texte.
```
Voir l'exemple AppendString.
```
