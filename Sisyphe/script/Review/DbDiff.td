constant NEW_ERRORS = new Structure();
constant DIFF_TYPE = new DiffType();

function AddError(fileName, part) 
  rulesList = new Structure();
  if !constant:NEW_ERRORS.FindField(fileName, rulesList) then
    constant:NEW_ERRORS.Fields(fileName) = rulesList;
  endif
  
  errorList = new Array();
  if !rulesList.FindField(part.RuleNumber, errorList) then
    rulesList.Fields(part.RuleNumber) = errorList;
  endif
  errorList[#errorList] = part.Error;
  
  idList = new Array();
  field = "ids_r" & (part.RuleNumber);
  if !rulesList.FindField(field, idList) then
    rulesList.Fields(field) = idList;
  endif
  idList[#idList] = part.Identifier;
endfunction

function AddPart(fileParts, ruleNumber, startBlock, lengthBlock, lineNumber, category, description, id)
  error = new CppNotice();
  error.Category = category;
  error.Description = description;
  error.RuleNumber = ruleNumber;
  error.LineNumber = lineNumber;
  error.StartBlock = startBlock;
  error.LengthBlock = lengthBlock;
  part = new Structure();
  part.Identifier = id;
  part.RuleNumber = ruleNumber;
  part.Error = error;
  part.Key = "R" & ruleNumber & "L" & lengthBlock;
  fileParts[#fileParts] = part;
endfunction

function EqualPart(partA, partB)
  /*return*/ partA.Key == partB.Key;
endfunction

function EnumErrors(connection)
  files = new Structure();
  fileParts = new Array();
  /* Lecture de la base */
  columns = new Array();
  columns[0] = "c.name as fileName";
  columns[1] = "t.startblock";
  columns[2] = "t.lengthblock";
  columns[3] = "t.rulenumber";
  columns[4] = "t.lineNumber";
  columns[5] = "t.category";
  columns[6] = "t.description";
  columns[7] = "c.identifier as fileId";
  columns[8] = "t.identifier";
  
  tables = new Array();
  tables[0] = "cppNotice t";
  tables[1] = "cppFile c";
  
  where = "t.idFile=fileId order by fileName, t.startblock, t.rulenumber";
  
  statement = connection.Select(columns, tables, where);
 
  textError = "";
  if !connection.GetError(textError) then
  
    while statement.ExecuteStep() do

      fileName = "";
      startBlock = 0;
      lengthBlock = 0;
      ruleNumber = 0;
      lineNumber = 0;
      category = "";
      description = "";
      fileId = 0;
      identifier = 0;
      if statement.GetText( 0, fileName )   && 
         statement.GetInt( 1, startBlock )  && 
         statement.GetInt( 2, lengthBlock ) && 
         statement.GetInt( 3, ruleNumber )  && 
         statement.GetInt( 4, lineNumber )  && 
         statement.GetText( 5, category )   && 
         statement.GetText( 6, description ) &&
         statement.GetInt( 7, fileId )  &&
         statement.GetInt( 8, identifier ) then
      
        if EnabledRule(ruleNumber - 1) then
          fileInfo = new Structure();
          if !files.FindField(fileName, fileInfo) then
            fileParts = new Array();
            fileInfo.id = fileId;
            fileInfo.parts = fileParts;
            files.Fields(fileName) = fileInfo;
          endif
          AddPart(fileParts, ruleNumber, startBlock, lengthBlock, lineNumber, category, description, identifier);
        endif
      endif
    endwhile
  else
     print("Error DB File : " & textError);
  endif 
  /*return*/ files;
endfunction

function GetFileId(fileName)
  fileId = 0;
  connection = new Connection();
  /* Lecture de la base */
  columns = new Array();
  columns[0] = "c.identifier as fileId";
  tables = new Array();
  tables[0] = "cppFile c";
  where = "c.name='" & fileName & "'";
  
  statement = connection.Select(columns, tables, where);
 
  textError = "";
  if !connection.GetError(textError) then
  
    while statement.ExecuteStep() do
      statement.GetInt( 0, fileId );     
    endwhile
  else
     print("Error DB File : " & textError);
  endif 
  /*return*/ fileId;
endfunction

function EnumCurrentErrors()
  connection = new Connection();
  /*return*/ EnumErrors(connection);
endfunction

function EnumReferenceErrors(refDB)
  connection = new Connection();
  connection.OpenConnection(refDB);
  EnableRules(connection);
  errors = EnumErrors(connection);
  connection.CloseConnection(refDB);
  /*return*/ errors;
endfunction

function CompareErrors(refErrors, currentErrors)
  diffResults = new Structure();
  ifile = 0;
  while ifile < currentErrors.FieldsCount() do
    fileName = currentErrors.Fields(ifile).Name;
    parts = currentErrors.Fields(ifile).Value.parts;
    refinfo = new Structure();
    
    diffCount = new Structure();
    diffCount.Deletes = 0;
    diffCount.Adds = 0;
    diffCount.Modifies = 0;
    if !refErrors.FindField(fileName, refinfo) then
      /* Nouvelles erreurs dans le fichier */
      diffCount.Adds = #parts;
      ipart = 0;
      while ipart < #parts do 
        part = parts[ipart];
        AddError(fileName, part);
        ipart.Increment();
      endwhile
    else
      /* Compare les erreurs */ 
      diff = new Diff();
      diff.Compare(refinfo.parts, parts, function:EqualPart);
      diffCount.Deletes = diff.Deletes;
      diffCount.Adds = diff.Adds;
      diffCount.Modifies = diff.Modifies;
      i = 0;
      while i < #(diff.List) do
        d = diff.List[i];
        /* Remplacement d'erreurs */
        if d.Type == constant:DIFF_TYPE.MODIFY then
          if d.Item1.RuleNumber != d.Item2.RuleNumber then
            diffCount.Modifies = diffCount.Modifies - 1;
            diffCount.Adds = diffCount.Adds + 1;
            diffCount.Deletes = diffCount.Deletes + 1;
            AddError(fileName, d.Item2);
          endif
        endif
        /* Nouvelles erreurs */
        if d.Type == constant:DIFF_TYPE.ADD then
          AddError(fileName, d.Item2);
        endif
        i.Increment();
      endwhile 
    endif
    diffResults.Fields(fileName) = diffCount;
    ifile.Increment();
  endwhile
  /* Lecture des erreurs corrigées */
  ifile = 0;
  while ifile < refErrors.FieldsCount() do
    fileName = refErrors.Fields(ifile).Name;
    parts = refErrors.Fields(ifile).Value.parts;
    currinfo = new Structure();
    if !currentErrors.FindField(fileName, currinfo) then
      /* Correction erreurs dans le fichier */
      diffCount = new Structure();
      diffCount.Deletes = #parts;
      diffCount.Adds = 0;
      diffCount.Modifies = 0;
      diffResults.Fields(fileName) = diffCount;
    endif
    ifile.Increment();
  endwhile
  /*return*/ diffResults;
endfunction

function Rule(fileData, errorList)
  ruleErrors = new Structure();
  errors = new Array();
  if constant:NEW_ERRORS.FindField(fileData.Name, ruleErrors) then
    ruleErrors.FindField(ruleNumber, errors);
    errorList[#errorList _ -1] = errors;
  endif
  /*return*/ #errors == 0;
endfunction

function WriteReport(srcPath, modelPath, projectName, outputPath, diffResults, infoReview)
  rulesCollection = new Array();
  i = 0;
  while i < constant:RULES_COUNT do
    rulesCollection[i] = function:Rule;
    rulesCollection[i].Variables("ruleNumber") = (i + 1);
    i.Increment();
  endwhile
  resultWriters = new Array();
  resultWriters[0] = InitDoc(modelPath, projectName, outputPath, "PartialReport", infoReview);
  resultWriters[0].DiffResults = diffResults;
  CheckRules(srcPath, rulesCollection, function:AlwaysValidateRule, resultWriters);
  CloseDoc(resultWriters[0]);
endfunction

function XmlString(str)
  DblQuotes & str & DblQuotes;
endfunction

function XmlHeader(str)
  "<td value=" & XmlString(str) & " bgcolor=" & XmlString("grey") & " align=" & XmlString("center") & "/>" & CrLf;
endfunction

function XmlRow(str)
  "<td value=" & XmlString(str) & " bgcolor=" & XmlString("white") & " align=" &  XmlString("center") & "/>" & CrLf;
endfunction

function WriteSummary(srcPath, outputPath, filesErrors, filesDiff)
  /* Calcul des erreurs */
  totalErrors = 0;
  solvedErrors = 0;
  newErrors = 0;
  fileNames = ListFiles(srcPath, srcPath);
  ifile = 0;
  while ifile < #fileNames do
    fileName = fileNames[ifile];
    fileinfo = new Structure();
    if filesErrors.FindField(fileName, fileinfo) then  
      parts = fileinfo.parts;
      totalErrors = totalErrors + #parts;
    endif
    diffCount = new Structure();
    diffCount.Deletes = 0;
    diffCount.Adds = 0;
    if filesDiff.FindField(fileName, diffCount) then
      solvedErrors = solvedErrors + diffCount.Deletes;
      newErrors = newErrors + diffCount.Adds;
    endif
    ifile.Increment();
  endwhile
  /* Création du fichier */
  print(outputPath & "/summary.xml");
  outFiles = new File(outputPath & "/summary.xml", "OVERWRITE", "UTF8");
  outFiles << ("<section name=" &  XmlString("Sisyphe results") & ">" & CrLf);
  outFiles << ("<table>" & CrLf);
  outFiles << ("<tr>" & CrLf);
  outFiles << XmlHeader("Total Errors");
  outFiles << XmlHeader("Solved");
  outFiles << XmlHeader("New");
  outFiles << ("</tr>" & CrLf);
  outFiles << ("<tr>" & CrLf);
  outFiles << XmlRow(totalErrors);
  outFiles << XmlRow(solvedErrors);
  outFiles << XmlRow(newErrors);
  outFiles << ("</tr>" & CrLf);
  outFiles << ("</table>" & CrLf);
  outFiles << ("</section>" & CrLf);
endfunction

function StartBlockAscending(itemA, itemB)
  itemA.error.StartBlock < itemB.error.StartBlock;
endfunction

function WriteJsonDiff(srcPath, jsonPath, filesErrors, filesDiff) 
  /* Réinitialisation des diff dans la base de données*/
  constant:DB_ACCESS.connection.StartTransaction();
  column = new Array();
  column[0] = "isNew";
  statement = constant:DB_ACCESS.connection.Update("cppNotice", column, "");
  statement.SetInt64(1, constant:DB_FALSE);
  statement.ExecuteQuery();
  /* Ecriture des nouvelles erreurs */
  fileNames = ListFiles(srcPath, srcPath);
  ifile = 0;
  while ifile < #fileNames do
    fileName = fileNames[ifile];
    fileinfo = new Structure();
    totalErrors = 0;
    fileId = 0;
    if filesErrors.FindField(fileName, fileinfo) then  
      fileId = fileinfo.id;
      parts = fileinfo.parts;
      totalErrors = #parts;
    else
      fileId = GetFileId(fileName);
    endif
    diffCount = new Structure();
    solvedErrors = 0;
    newErrors = 0;
    if filesDiff.FindField(fileName, diffCount) then
      solvedErrors = diffCount.Deletes;
      newErrors = diffCount.Adds;
    endif
    /* Création du fichier */
    print(jsonPath & "/diff_" & fileId & ".json");
    outFiles = new File(jsonPath & "/diff_" & fileId & ".json", "OVERWRITE", "UTF8");
    jsonStruct = new JSONStructureFormatter();
    jsonArray = new JSONArrayFormatter();
    jsonError = new JSONStructureFormatter();
    jsonStruct.Append("name", "Diff");
    jsonStruct.Append("total", totalErrors);
    jsonStruct.Append("solved", solvedErrors);
    jsonStruct.Append("new", newErrors);
    sortedList = new Array();
    ilist = 0;
    rulesList = new Structure();
    if constant:NEW_ERRORS.FindField(fileName, rulesList) then
      irule = 1;
      while irule <= constant:RULES_COUNT do
        errorList = new Array();
        idList = new Array();
        b1 = rulesList.FindField(irule, errorList);
        b2 = rulesList.FindField("ids_r" & irule, idList);
        if b1 && b2 then
          ierror = 0;
          while ierror < #errorList do
            sortedList[ilist] = new Structure();
            sortedList[ilist].identifier = idList[ierror];
            sortedList[ilist].error = errorList[ierror];
            ilist.Increment();
            ierror.Increment();
          endwhile
        endif
        irule.Increment();
      endwhile
      sortedList.Sort(function:StartBlockAscending);
      ierror = 0;
      while ierror < #sortedList do
        /* Write error */
        id = sortedList[ierror].identifier;
        error = sortedList[ierror].error;
        statement = constant:DB_ACCESS.connection.Update("cppNotice", column, "identifier=" & id);
        statement.SetInt64(1, constant:DB_TRUE);
        statement.ExecuteQuery();
        jsonError.Clear();
        jsonError.Append("lineNumber", error.LineNumber);
        jsonError.Append("start", error.StartBlock);
        jsonError.Append("length", error.LengthBlock);
        jsonError.Append("category", error.Category);
        jsonError.Append("description", error.Description);
        jsonArray.AppendAsText(jsonError.Text);
        ierror.Increment();
      endwhile
    endif
    jsonStruct.AppendAsText("list", jsonArray.Text);
    outFiles << jsonStruct.Text;
    ifile.Increment();
  endwhile
  constant:DB_ACCESS.connection.Commit();
endfunction

function EnableRules(connection)
  i = 0;
  rulesInDB = IsDatabaseColumnExist(connection, "rule", "number");
  while i < constant:RULES_COUNT do
    if rulesInDB then
      /* Lecture de la base */
      columns = new Array();
      columns[0] = "COUNT(*)";
      tables = new Array();
      tables[0] = "rule";
      where = "number=" & i & " and enabled=1";
      statement = connection.Select(columns, tables, where);
      textError = "";
      if !connection.GetError(textError) then
        while statement.ExecuteStep() do
          count = 0;
          if statement.GetInt( 0, count ) then
            enabled = (count > 0);
          endif
        endwhile
      else
         print("Error DB File : " & textError);
      endif 
    else
      enabled = i < 57 && EnabledRule(i);
    endif
    constant:ENABLED_RULES.Fields("Rule" & (i+1)) = enabled;
    i.Increment();
  endwhile
endfunction

function WriteDatabaseRules()
  constant:DB_ACCESS.connection.StartTransaction();
 
  access = constant:DB_ACCESS.rule;
  rules = access.GetAllRules();
  irule = #rules;
  while irule > 0 do
    access.SelectOneRule(rules[irule-1].Identifier, false);
    access.DeleteRule(rules[irule-1]);
    irule.Decrement();
  endwhile
  
  i = 0;
  while i < constant:RULES_COUNT do
    rule = new Rule();
    rule.Number = i;
    description = constant:DESCRIPTION;
    rule.Description = description[i];
    if EnabledRule(i) then
      rule.Enabled = constant:DB_TRUE;
    else
      rule.Enabled = constant:DB_FALSE;
    endif
    access.InsertRule(rule);
    i.Increment();
  endwhile
 
  constant:DB_ACCESS.connection.Commit();
endfunction
 
function DiffBase(refDB, srcPath, modelPath, projectName, outputPath, jsonPath, infoReview)
  refErrors = EnumReferenceErrors(refDB);
  currentErrors = EnumCurrentErrors();
  diffResults = CompareErrors(refErrors, currentErrors);
  WriteReport(srcPath, modelPath, projectName, outputPath, diffResults, infoReview);
  WriteSummary(srcPath, outputPath, currentErrors, diffResults);
  WriteJsonDiff(srcPath, jsonPath, currentErrors, diffResults);
  WriteDatabaseRules();
endfunction
 
function SumBase(srcPath, outputPath)
  currentErrors = EnumCurrentErrors();
  diffResults = new Structure();
  WriteSummary(srcPath, outputPath, currentErrors, diffResults);
  WriteDatabaseRules();
endfunction

function MakeDiff()
  sourceFolder = new Folder(constant:sourcePath);
  docFolder = new Folder(constant:docPath);
  jsonFolder = new Folder(constant:jsonPath);

  if jsonFolder.Exists && sourceFolder.Exists && docFolder.Exists then
    dbFile = new File(constant:referenceDB, "NONE", "BASE64");
    exist = dbFile.Open;
    dbFile = null;
    if exist then
        DiffBase(constant:referenceDB, 
                 constant:sourcePath, 
                 "./CodingRules/CppCustom/Models/ModeleRevue_Custom.xml", 
                 constant:projectName, 
                 constant:docPath, 
                 constant:jsonPath,
                 constant:infoReview);
    else
        SumBase(constant:sourcePath, constant:docPath);
    endif

    /* copie de la base de données */
    dbSource = new File(constant:dbFile, "NONE", "BASE64");
    exist = dbSource.Open;
    if exist then
      bin = new String(524288);
      dbSource >> bin;
      dbDest = new File(constant:jsonPath & "/cppbase.db", "OVERWRITE", "BASE64");
      dbDest << bin;
      dbDest = null;
    endif
    dbSource = null;
  endif
endfunction

MakeDiff();
