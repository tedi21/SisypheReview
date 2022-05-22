
sourceFolder = new Folder(constant:sourcePath);
docFolder = new Folder(constant:docPath);

if sourceFolder.Exists && docFolder.Exists then

  /* Nettoyage de l'analyse précèdente */
  if constant:forceClean then
    Clean();
  endif

  /* Initialise Git */
  InitGit(constant:sourcePath);

  /* Structure permettant de desactiver une règle (toutes les règles sont activées par défaut). */
  /*
  constant:ENABLED_RULES.Rule1  = false;
  constant:ENABLED_RULES.Rule28 = false;
  */
  constant:SETTINGS.IgnoreErrorKeyword = "DEROGATION";
  constant:SETTINGS.IgnorePreprocessorList = "".Split(";");
  
  /* Analyse les fichiers sources dans le repértoire passé en paramètre. */
  Parse(constant:sourcePath);

  /* Structure permettant de desactiver la génération des diagrammes (Activée par défaut). 
  Nécessite l'installation de GraphViz + 
  l'ajout de la variable d'environnement $PATH += /chemin/GraphViz/bin. */
  constant:ENABLED_DIAGRAMS.ClassDiagram = true;

  /* Applique les règles de codage pour les fichiers présents dans le répertoire passé comme premier paramètre. 
  Le second paramètre est le nom du projet affiché dans le rapport.
  Le troisième paramètre est le répertoire de sortie du rapport. */
  ReviewCode(constant:sourcePath, "./CodingRules/CppCustom/Models/ModeleRevue_Custom.xml", constant:projectName, constant:docPath, constant:infoReview);
  
  /* Libère Git */
  ReleaseGit();

else
  
  print("Paths are not found :" & CrLf & ">" & sourceFolder & CrLf & ">" & docFolder);
endif
