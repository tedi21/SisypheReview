
function ListFiles(srcPath, filePath)
    directory = new Folder(filePath);
    files = FilterSourceFiles(srcPath, filePath, directory.Files);
    folders = directory.Folders;
    iFolder = 0;
    while iFolder < #folders do
        predicate = function:IsExcludedName;
        predicate.Variables("name") = folders[iFolder];
        if constant:EXCLUDE_PATHS.Find(predicate) == #constant:EXCLUDE_PATHS then
            filesSize = #files;
            subFolder = new Folder(folders[iFolder]);
            subFolderPath = filePath & "/" & subFolder.Path;
            files[filesSize _ -1] = ListFiles(srcPath, subFolderPath);
        endif
        iFolder.Increment();
    endwhile
    /*return*/ files;
endfunction

function RemoveSpace(content, start, length, newStart, newLength)
  matches = new Match();
  newStart = start;
  newLength = 0;
  trimming = content.SubString(start, length).Match("^\s*(([^\s]|(\s(?!\s*$)))+)\s*$", matches);
  if trimming then
    newStart = start + matches.SubStringsPos[1];
    newLength = #(matches.SubStrings[1]);
  endif
endfunction

function AppendError(fileData, errorList, ruleNumber, category, description, lineNumber)
  iError = #errorList;
  errorList[iError] = new CppNotice();
  errorList[iError].Category = category;
  errorList[iError].Description = description;
  errorList[iError].RuleNumber = ruleNumber;
  errorList[iError].CppFile = fileData.Properties;
  errorList[iError].LineNumber = lineNumber;
  errorList[iError].IsNew = constant:DB_TRUE;
  FillBlameInfo(errorList[iError]);
  block = GetLinePos(fileData, lineNumber - 1);
  startBlock = 0;
  lengthBlock = 0;
  if #block > 1 then
    startBlock = block[0];
    lengthBlock = block[1] - block[0];
  endif
  RemoveSpace(fileData.Text, startBlock, lengthBlock, errorList[iError].StartBlock, errorList[iError].LengthBlock);
endfunction

function CompleteString(value, fillc, filln)
    str = "" & value;
    while #str < filln do
        str = fillc & str;
    endwhile
    /*return*/ str;
endfunction

function EnabledRule(number)
	value = true;
	constant:ENABLED_RULES.FindField("Rule" & (number+1), value);
	/*return*/ value;
endfunction

function EnabledDiagram(type)
	value = true;
	constant:ENABLED_DIAGRAMS.FindField(type, value);
	/*return*/ value;
endfunction

function FillCell(result, errorCount, xmlDocument, node)
    if !result then
        node.AppendString(false, "N" & errorCount);
        nodeProperties = node.PropertiesNode;
        shdNode = xmlDocument.CreateNode("w:shd");
        shdNode.Attributes("w:fill") = "FF0000";
        shdNode.Attributes("w:color") = "auto";
        shdNode.Attributes("w:val") = "clear";
        nodeProperties.Append(shdNode);
    else
        node.AppendString(false, "O");
    endif
endfunction

function InsertPicture(name, binData, xmlDocument, node)
	width = 0;
	width.ParseBase64(binData, 128, 32);
	height = 0;
	height.ParseBase64(binData, 160, 32);
	if width > 700 then
		ratio = 700 / width;
		width = width * ratio;
		height = height * ratio;
	endif
	
	pictNode = xmlDocument.CreateNode("w:pict");
	binDataNode = xmlDocument.CreateNode("w:binData");
	binDataNode.Content = binData;
	binDataNode.Attributes("w:name") = "wordml://" & name;
	shapeNode = xmlDocument.CreateNode("v:shape");
	shapeNode.Attributes("type") = "#_x0000_t75";
	shapeNode.Attributes("style") = "width:" & width & "px;height:" & height & "px";
	imageDataNode = xmlDocument.CreateNode("v:imagedata");
	imageDataNode.Attributes("src") = "wordml://" & name;
	imageDataNode.Attributes("o:title") = name;
	shapeNode.Append(imageDataNode);
	pictNode.Append(shapeNode);
	pictNode.Append(binDataNode);
	node.Append(pictNode);
endfunction

function FillComment(result, errorCount, filename, textError, node)
    if !result then
        nodes = node.AppendString(false, "[N" & errorCount & "] " & filename & " : " & CrLf & textError & CrLf);
        node = nodes.Item(nodes.Length()-1);
    endif
endfunction

function FormatError(errorList)
	i = 0;
	size = #errorList;
	textError = new String(size * 200);
	while i < size do
		if #textError > 0 then
			textError.Append(CrLf);
		endif
		lineError = "    Line " & errorList[i].LineNumber & " : " & errorList[i].Description;
		textError.Append(lineError);
		i.Increment();
	endwhile
	/*return*/ textError;
endfunction

function SaveErrors(errorList)
	i = 0;
	size = #errorList;
	while i < size do
		constant:DB_ACCESS.cppNotice.InsertCppNotice(errorList[i]);
		i.Increment();
	endwhile
endfunction

function InitDB()
  constant:DB_ACCESS.connection.StartTransaction();
  /* db writer */
  dbWriter = new Structure();
  dbWriter.Write = function:WriteDB;
  /*return*/ dbWriter;
endfunction

function CloseDB()
  constant:DB_ACCESS.connection.Commit();
endfunction

function WriteDB(object, file, ifile, nfile, irule, nrule, success, errorList)
  if file.Properties.Analyzed == constant:DB_FALSE then
    if !success then
        /* Add Errors */
        SaveErrors(errorList);
    endif
    
    if irule == (nrule-1) then
    
      /* Mise à jour de l'analyse du fichier */
      sourceFile = file.Properties;
      sourceFile.Analyzed = constant:DB_TRUE;
      constant:DB_ACCESS.cppFile.SelectOneCppFile(sourceFile.Identifier, false);
      constant:DB_ACCESS.cppFile.UpdateCppFile(sourceFile);
    endif
  endif
endfunction

function ReadDB(fileData, ruleNumber, errorList)
  /* Lecture de la base */
  columns = new Array();
  columns[0] = "t.category";
  columns[1] = "t.description";
  columns[2] = "t.ruleNumber";
  columns[3] = "t.lineNumber";
  columns[4] = "c.identifier as fileId";
  
  tables = new Array();
  tables[0] = "cppNotice t";
  tables[1] = "cppFile c";
  
  where = "fileId=" & fileData.Identifier & " and t.idFile=" & fileData.Identifier & " and t.rulenumber=" & ruleNumber;
  
  statement = constant:DB_ACCESS.connection.Select(columns, tables, where);
  textError = "";
  if !constant:DB_ACCESS.connection.GetError(textError) then 
    while statement.ExecuteStep() do
      category = "";
      description = "";
      ruleNumber = 0;
      lineNumber = 0;
      if statement.GetText( 0, category )     && 
         statement.GetText( 1, description )  && 
         statement.GetInt( 2, ruleNumber )    && 
         statement.GetInt( 3, lineNumber ) then

          AppendError(fileData, errorList, ruleNumber, category, description, lineNumber);
      endif
    endwhile
  else
     print("Error DB File : " & textError);
  endif
endfunction

function ValidateRuleDB(fileData, ruleNumber, errorList)
  validation = fileData.Properties.Analyzed == constant:DB_FALSE;
  if !validation then
    print("RULE " & ruleNumber+1 & " is already verified.");
    ReadDB(fileData, ruleNumber + 1, errorList);
  endif
  /*return*/ validation;
endfunction

function AlwaysValidateRule(fileData, ruleNumber, errorList)
  /*return*/ true;
endfunction

function CheckRules(srcPath, rulesCollection, rulesValidator, resultWriters)

  /* Read files to analyze */
  fileNames = ListFiles(srcPath, srcPath);
  files = CreateFileDataList(fileNames);

  ifiles = 0;
  while ifiles < #files do

    print(CrLf & "ANALYZE " & files[ifiles].Name);
    dataLoaded = false;
    irule = 0;
    /* Check each rule */
    while irule < #rulesCollection do
    
      /* Chargement des données */
      if !dataLoaded then
        LoadFileData(files[ifiles]);
        dataLoaded = true;
      endif
    
      errorList = new Array();
      success = true;

      /* Appel de la vérification de la règle */
      if EnabledRule(irule) then
        validParams = new Array();
        validParams[0] = files[ifiles];
        validParams[1] = irule;
        validParams[2] = errorList;
        if rulesValidator.Call(validParams) then
          
          print("RULE " & irule+1);
          params = new Array();
          params[0] = files[ifiles];
          params[1] = errorList;
          success = rulesCollection[irule].Call(params);
        else
          success = #errorList == 0;
        endif
        print("  ==> " & success);
      endif

      /* Ecriture du fichier */
      iwriter = 0;
      while iwriter < #resultWriters do
        
        writer = resultWriters[iwriter];
        writerParams = new Array();
        writerParams[0] = writer;
        writerParams[1] = files[ifiles];
        writerParams[2] = ifiles;
        writerParams[3] = #files;
        writerParams[4] = irule;
        writerParams[5] = #rulesCollection;
        writerParams[6] = success;
        writerParams[7] = errorList;
        writer.Write.Call(writerParams);
        iwriter.Increment();
      endwhile
      irule.Increment();
    endwhile

    UnLoadFileData(files[ifiles]);
    ifiles.Increment();
  endwhile
endfunction
