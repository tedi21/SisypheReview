
function GetFileEncoding(file)
  encoding = "ISO-8859-15";
  f = new File(file, "NONE", "BASE64");
  if f.Open then
    binData = "";
    f >> binData;
    bom = 0;
    bom.ParseBase64(binData, 0, 24);
    if bom.ConvertHex() =~ "EFBBBF" then
      encoding = "UTF8";
    endif
    bom.ParseBase64(binData, 0, 16);
    if bom.ConvertHex() =~ "FFFE" then
      encoding = "UTF16-LE";
    endif
    if bom.ConvertHex() =~ "FEFF" then
      encoding = "UTF16-BE";
    endif
  endif
  /*return*/encoding;
endfunction

function GetFileContent(file)
    str = "";
    f = new File(file, "NONE", GetFileEncoding(file));
    if f.Open then
        f >> str;
    endif
    /*return*/str;
endfunction

function generateFilesList(jsonPath)
  /* Liste des identifiants */
  identifiers = new Array();
  
  /* Lecture de la base */
  columns = new Array();
  columns[0] = "identifier";
  columns[1] = "name";
  
  tables = new Array();
  tables[0] = "cppFile";
  
  connection = new Connection();
  statement = connection.Select(columns, tables, "");
 
  textError = "";
  if !connection.GetError(textError) then
  
    /* Création du fichier */
    print(jsonPath & "/files.json");
    outFiles = new File(jsonPath & "/files.json", "OVERWRITE", "UTF8");
    jsonArray = new JSONArrayFormatter();
    jsonStruct = new JSONStructureFormatter();
    while statement.ExecuteStep() do
    
      /* Write file */
      identifier = 0;
      name = "";
      if statement.GetInt( 0, identifier ) && statement.GetText( 1, name ) then
          jsonStruct.Clear();
          jsonStruct.Append("id", identifier);
          jsonStruct.Append("name", name);
          jsonArray.AppendAsText(jsonStruct.Text);
          identifiers[#identifiers] = identifier;
      endif
    endwhile
    outFiles << jsonArray.Text;
  else
     print("Error DB File : " & textError);
  endif 
  /*return*/ identifiers;
endfunction

function generateFileContent(jsonPath, identifier)

  /* Lecture de la base */
  columns = new Array();
  columns[0] = "c.identifier";
  columns[1] = "c.path";
  columns[2] = "c.idType";
  columns[3] = "c.linesCount";
  columns[4] = "errors";
  columns[5] = "classes";
  columns[6] = "enums";
  columns[7] = "methodsDec";
  columns[8] = "methodsDef";
  columns[9] = "attributes";
  columns[10] = "macros";
  columns[11] = "complexities";
  columns[12] = "t.content";
  
  tables = new Array();
  tables[0] = "(SELECT COUNT(n.identifier) as errors FROM cppNotice n, cppFile c WHERE c.identifier=" & identifier & " and n.idFile=" & identifier & ")";
  tables[1] = "(SELECT COUNT(cc.identifier) as classes FROM cppClass cc WHERE cc.idFile=" & identifier & " and cc.lengthBlock!=0)";
  tables[2] = "(SELECT COUNT(ce.identifier) as enums FROM cppEnum ce WHERE ce.idFile=" & identifier & " and ce.lengthBlock!=0)";
  tables[3] = "(SELECT COUNT(cf.identifier) as methodsDec FROM cppFunction cf WHERE cf.idDecFile=" & identifier & " and cf.lengthDecBlock!=0)";
  tables[4] = "(SELECT COUNT(cf.identifier) as methodsDef, AVG(complexity) as complexities FROM cppFunction cf WHERE cf.idDefFile=" & identifier & " and cf.lengthDefBlock!=0)";
  tables[5] = "(SELECT COUNT(ca.identifier) as attributes FROM cppAttribute ca, cppClass cc WHERE cc.idFile=" & identifier & " and cc.identifier=ca.idClass and ca.lengthBlock!=0)";
  tables[6] = "(SELECT COUNT(cm.identifier) as macros FROM cMacro cm WHERE cm.idFile=" & identifier & " and cm.lengthBlock!=0)";
  tables[7] = "cppFile c";
  tables[8] = "textFile t";
  
  where = "c.identifier=" & identifier & " and t.rowid=c.idText";
  
  connection = new Connection();
  statement = connection.Select(columns, tables, where);
 
  textError = "";
  if !connection.GetError(textError) then

    /* Création du fichier */
    print(jsonPath & "/file_" & identifier & ".json");
    outFiles = new File(jsonPath & "/file_" & identifier & ".json", "OVERWRITE", "UTF8");
    jsonStruct = new JSONStructureFormatter();
    
    while statement.ExecuteStep() do
    
      /* Write file */
      identifier = 0;
      path = "";
      content = "";
      type = 0;
      linesCount = 0;
      errorsCount = 0;
      classesCount = 0;
      enumsCount = 0;
      decMethodsCount = 0;
      defMethodsCount = 0;
      attributesCount = 0;
      macrosCount = 0;
      complexityAvg = 0;
      if  statement.GetInt( 0, identifier ) &&
          statement.GetText( 1, path ) &&
          statement.GetInt( 2, type ) &&
          statement.GetInt( 3, linesCount ) &&
          statement.GetInt( 4, errorsCount ) &&
          statement.GetInt( 5, classesCount ) &&
          statement.GetInt( 6, enumsCount ) &&
          statement.GetInt( 7, decMethodsCount ) &&
          statement.GetInt( 8, defMethodsCount ) &&
          statement.GetInt( 9, attributesCount ) &&
          statement.GetInt( 10, macrosCount ) &&
          statement.GetInt( 11, complexityAvg ) &&
          statement.GetText( 12, content ) then
          
          jsonStruct.Clear();
          jsonStruct.Append("id", identifier);
          jsonStruct.Append("path", path);
          jsonStruct.Append("path", path);
          if type == 2 then
            jsonStruct.Append("type", "source");
          else
            jsonStruct.Append("type", "header");
          endif
          jsonStruct.Append("linesCount", linesCount);
          jsonStruct.Append("errorsCount", errorsCount);
          jsonStruct.Append("classesCount", classesCount);
          jsonStruct.Append("enumsCount", enumsCount);
          jsonStruct.Append("decMethodsCount", decMethodsCount);
          jsonStruct.Append("defMethodsCount", defMethodsCount);
          jsonStruct.Append("attributesCount", attributesCount);
          jsonStruct.Append("macrosCount", macrosCount);
          jsonStruct.Append("complexityAvg", complexityAvg);
          if content == "file not available." then
            content = GetFileContent(path);
          endif
          HTMLPrinter = new HTMLFormatter();
          jsonStruct.Append("content", HTMLPrinter.PrettyPrint(content));
      endif
    endwhile
    outFiles << jsonStruct.Text;
  else
     print("Error DB File : " & textError);
  endif 
endfunction

function generateErrors(jsonPath, identifier)
 
  /* Lecture de la base */
  columns = new Array();
  columns[0] = "t.lineNumber";
  columns[1] = "t.startBlock";
  columns[2] = "t.lengthBlock";
  columns[3] = "t.category";
  columns[4] = "t.description";
  
  tables = new Array();
  tables[0] = "cppNotice t";
  tables[1] = "cppFile c";
  
  where = "c.identifier=" & identifier & " and t.idFile=" & identifier & " ORDER BY ABS(t.startBlock) ASC";
  
  connection = new Connection();
  statement = connection.Select(columns, tables, where);
 
  textError = "";
  if !connection.GetError(textError) then
  
    /* Création du fichier */
    print(jsonPath & "/errors_" & identifier & ".json");
    outFiles = new File(jsonPath & "/errors_" & identifier & ".json", "OVERWRITE", "UTF8");
    jsonStruct = new JSONStructureFormatter();
    jsonArray = new JSONArrayFormatter();
    jsonError = new JSONStructureFormatter();
    jsonStruct.Append("name", "Errors");
    while statement.ExecuteStep() do
    
      /* Write file */
      lineNumber = 0;
      start = 0;
      length = 0;
      category = "";
      description = "";
      if  statement.GetInt( 0, lineNumber ) &&
          statement.GetInt( 1, start ) &&
          statement.GetInt( 2, length ) &&
          statement.GetText( 3, category ) &&
          statement.GetText( 4, description ) then
        jsonError.Clear();
        jsonError.Append("lineNumber", lineNumber);
        jsonError.Append("start", start);
        jsonError.Append("length", length);
        jsonError.Append("category", category);
        jsonError.Append("description", description);
        jsonArray.AppendAsText(jsonError.Text);
      endif
    endwhile
    jsonStruct.AppendAsText("list", jsonArray.Text);
    outFiles << jsonStruct.Text;
  else
     print("Error DB File : " & textError);
  endif 
endfunction

function GenerateJsonFiles()
  jsonFolder = new Folder(constant:jsonPath);

  if jsonFolder.Exists then
    /* Génération de la liste des fichiers. */
    identifiers = generateFilesList(constant:jsonPath);

    iFile = 0;
    while iFile < #identifiers do
      identifier = identifiers[iFile];
      
      /* Génération des fichiers. */
      generateFileContent(constant:jsonPath, identifier);
      
      /* Génération des erreurs */
      generateErrors(constant:jsonPath, identifier);
      
      iFile.Increment();
    endwhile
  else
  
    print("Path is not found :" & CrLf & ">" & jsonFolder);
  endif
endfunction

GenerateJsonFiles();
