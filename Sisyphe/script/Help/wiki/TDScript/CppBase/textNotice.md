# TextNotice


# Référence
## Constructeur TextNotice
*Paramètres*
* None.

*Description*
* Crée une instance de la classe TextNotice.
```
var = new TextNotice();
```

## Constructeur TextNotice
*Paramètres*
* String : La valeur de la colonne description.
* String : La valeur de la colonne category.
* Numeric : La valeur de la colonne lineNumber.
* Numeric : La valeur de la colonne startBlock.
* Numeric : La valeur de la colonne lengthBlock.

*Description*
* Crée une instance de la classe TextNotice.
```
var = new TextNotice(description, category, lineNumber, startBlock, lengthBlock);
```

## Méthode Rowid
*Paramètres*
* None.

*Retour*
* Numeric : La colonne rowid.

*Description*
* Retourne la colonne Rowid.
```
val = var.Rowid;
```

## Méthode Description
*Paramètres*
* None.

*Retour*
* String : La colonne description.

*Description*
* Retourne la colonne Description.
```
val = var.Description;
```

## Méthode Category
*Paramètres*
* None.

*Retour*
* String : La colonne category.

*Description*
* Retourne la colonne Category.
```
val = var.Category;
```

## Méthode LineNumber
*Paramètres*
* None.

*Retour*
* Numeric : La colonne lineNumber.

*Description*
* Retourne la colonne LineNumber.
```
val = var.LineNumber;
```

## Méthode StartBlock
*Paramètres*
* None.

*Retour*
* Numeric : La colonne startBlock.

*Description*
* Retourne la colonne StartBlock.
```
val = var.StartBlock;
```

## Méthode LengthBlock
*Paramètres*
* None.

*Retour*
* Numeric : La colonne lengthBlock.

*Description*
* Retourne la colonne LengthBlock.
```
val = var.LengthBlock;
```

## Méthode TextFile
*Paramètres*
* None.

*Retour*
* TextFile : La colonne textFile.

*Description*
* Retourne la colonne TextFile.
```
textFile = var.TextFile;
```

## Méthode Description
*Paramètres*
* String : La valeur de la colonne description.

*Retour*
* None.

*Description*
* Définit la colonne description.
```
var.Description(description);
```

## Méthode Category
*Paramètres*
* String : La valeur de la colonne category.

*Retour*
* None.

*Description*
* Définit la colonne category.
```
var.Category(category);
```

## Méthode LineNumber
*Paramètres*
* Numeric : La valeur de la colonne lineNumber.

*Retour*
* None.

*Description*
* Définit la colonne lineNumber.
```
var.LineNumber(lineNumber);
```

## Méthode TextFile
*Paramètres*
* TextFile : La valeur de la colonne textFile.

*Retour*
* None.

*Description*
* Définit la colonne textFile.
```
var.TextFile(textFile);
```

## Méthode StartBlock
*Paramètres*
* Numeric : La valeur de la colonne startBlock.

*Retour*
* None.

*Description*
* Définit la colonne startBlock.
```
var.StartBlock(startBlock);
```

## Méthode LengthBlock
*Paramètres*
* Numeric : La valeur de la colonne lengthBlock.

*Retour*
* None.

*Description*
* Définit la colonne lengthBlock.
```
var.LengthBlock(lengthBlock);
```

## Méthode HasTextFile
*Paramètres*
* None.

*Retour*
* Bool : Une valeur est définie pour la colonne textFile.

*Description*
* Indique si la colonne TextFile a une valeur définie.
```
val = var.HasTextFile;
```

## Méthode removeTextFile
*Paramètres*
* None.

*Retour*
* None.

*Description*
* Supprime la valeur définie pour la colonne textFile.
```
var.TextFile = null;
```
