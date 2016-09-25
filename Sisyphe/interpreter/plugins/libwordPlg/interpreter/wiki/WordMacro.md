# WordMacro
 Classe permettant d'executer des macros Word. 

# Référence
## Méthode ConvertToXML
*Paramètres*
* String : Le nom du document Word.
* String : Le nom du document Word XML.
* Bool : True, le suivi de modification est accepté. False, le document d'origine est convertie tel quel.

*Retour*
* Bool : True, le document est convertie. False, le document n'est pas convertie.

*Description*
*  Convertie un fichier en xml.
```
word = new WordMacro();
docDir = new Folder(docPath);
tempDir = new Folder(tempPath);
word.ConvertToXML(docDir.AbsolutePath, tempDir.AbsolutePath & "\xmldoc.xml", false);
```

## Méthode ConvertToDOC
*Paramètres*
* String : Le nom du document Word XML.
* String : Le nom du document Word.
* Bool : True, le suivi de modification est accepté. False, le document d'origine est convertie tel quel.

*Retour*
* Bool : True, le document est convertie. False, le document n'est pas convertie.

*Description*
*  Convertie un fichier en doc.
```
word = new WordMacro();
fileDir = new Folder(filePath);
tempDir = new Folder(tempPath);
word.convertToDOC(fileDir.AbsolutePath, tempDir.AbsolutePath & "\filedoc.doc", false);
```

## Méthode ConvertToPDF
*Paramètres*
* String : Le nom du document Word.
* String : Le nom du document PDF.
* Bool : True, le suivi de modification est accepté. False, le document d'origine est convertie tel quel.

*Retour*
* Bool : True, le document est convertie. False, le document n'est pas convertie.

*Description*
*  Convertie un fichier en pdf.
```
word = new WordMacro();
fileDir = new Folder(filePath);
tempDir = new Folder(tempPath);
word.convertToPDF(fileDir.AbsolutePath, tempDir.AbsolutePath & "\filepdf.pdf", false);
```

## Méthode ConvertToXDOC
*Paramètres*
* String : Le nom du document Word.
* String : Le nom du document XDOC.
* Bool : True, le suivi de modification est accepté. False, le document d'origine est convertie tel quel.

*Retour*
* Bool : True, le document est convertie. False, le document n'est pas convertie.

*Description*
*  Convertie un fichier en xdoc.
```
word = new WordMacro();
fileDir = new Folder(filePath);
tempDir = new Folder(tempPath);
word.convertToXDOC(fileDir.AbsolutePath, tempDir.AbsolutePath & "\filedoc.xdoc", false);
```
