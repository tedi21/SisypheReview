constant RULES_COUNT = 28;

function InitDoc(modelPath, projectName, outputPath, reportName)

  /* Check reportName.doc file existence */
  docFile = new File(outputPath & "/" & reportName & ".doc", "NONE", "ANSI");
  if docFile.Open then
    docFile = null;
    print("The file " & reportName & ".doc already exists. The file will be overwritten.");
  endif
  
  directory = new Folder(outputPath);
  directory.Remove(reportName & ".xml");
  
  /* Copy Model document */
  paths = modelPath.Split("[\\/]");
  modelName = paths[#paths - 1];
  modelPath = modelPath.SubString(0, #modelPath - #modelName);
  directory = new Folder(modelPath); 
  directory.CopyTo(modelName, outputPath & "/" & reportName & ".xml");

  /* Open Model document */
  print("Loading Model ...");
  xml = new WordXML();
  xml.Initialize();
  STATIC_NODE = new WordXMLNode();

  xmlDocument = new WordXMLDocument();
  xmlDocument.Parse(outputPath & "/" & reportName & ".xml");
  print("Model loaded.");
  rootNode = xmlDocument.DocumentNode;

  /* Get current date */
  now = new Date().CurrentDate;
  dateStr = CompleteString(now.Day, "0", 2) & "/" & CompleteString(now.Month, "0", 2) & "/" & now.Year;

  /* Update project name in document content */
  contentNode = rootNode.Nodes(STATIC_NODE.BodyTag).Item(0);

  /* Project name */
  projectNodes = contentNode.Evaluate("//w:t[text()="PROJECT_NAME"]");
  inode = 0;
  while inode < projectNodes.Length do

    node = projectNodes.Item(inode);
    node.AppendString(false, projectName);
    node.EraseString(false, 0, 12);
    inode.Increment();
  endwhile

  /* Project date */
  nodes = contentNode.Evaluate("//w:t[text()="DATE_ANALYSIS"]");
  inode = 0;
  while inode < nodes.Length do

    node = nodes.Item(inode);
    node.AppendString(false, dateStr);
    node.EraseString(false, 0, 13);
    inode.Increment();
  endwhile

  /* doc Writer */
  docWriter = new Structure();
  docWriter.reportName = reportName;
  docWriter.errorCount = 0;
  docWriter.outputPath = outputPath;
  docWriter.xml = xml;
  docWriter.STATIC_NODE = STATIC_NODE;
  docWriter.xmlDocument = xmlDocument;  
  docWriter.contentNode = contentNode;
  docWriter.nodes = contentNode.Evaluate("//w:t[text()="FilesEnums.h"]");

  inode = 0;
  if inode < docWriter.nodes.Length then

    node = docWriter.nodes.Item(inode);
    docWriter.tableNode = node.Parent(STATIC_NODE.TableTag);
    docWriter.rowNode = node.Parent(STATIC_NODE.RowTag);
    node.EraseString(false, 0, 12);
    docWriter.rowClonedNode = docWriter.rowNode.CloneNode(true);
    
    commentNodes = docWriter.contentNode.Evaluate("//w:t[text()="Detailed analysis"]");
    commentNode = commentNodes.Item(0);
    commentNodes = commentNode.AppendString(false, CrLf);
    docWriter.commentNode = commentNodes.Item(1);
  endif
  docWriter.Write = function:WriteDoc;
  
  /*return*/ docWriter;
endfunction

function WriteDoc(object, file, ifile, nfile, irule, nrule, success, errorList)

  if irule == 0 then 
    object.cellNodes = object.rowNode.Nodes(object.STATIC_NODE.CellTag);
    object.fileRuleCount = 0;
    object.fileErrorCount = 0;
    
    /* Write file name */
    cellNode = object.cellNodes.Item(0);
    cellNode.AppendString(false, file.Name);
  endif
  
  if !success then
    object.errorCount = object.errorCount + 1;
    object.fileErrorCount = object.fileErrorCount + #errorList;
    object.fileRuleCount = object.fileRuleCount + 1;
  endif
  
  textError = FormatError(errorList);
  FillComment(success, object.errorCount, file.Name, textError, object.commentNode);
            
  if irule == (nrule-1) then 
    /* Fill summary */    
    success = (object.fileErrorCount == 0);
    cellNode = object.cellNodes.Item(1);
    diffResults = new Structure();
    if object.FindField("DiffResults", diffResults) then
      diffCount = new Structure();
      diffCount.Deletes = 0;
      diffCount.Adds = 0;
      diffResults.FindField(file.Name, diffCount);
      FillCell(success, "", object.xmlDocument, cellNode);
      solved = diffCount.Deletes;
      new_errors = diffCount.Adds;
      text = CrLf & "Solved : " & solved &
             CrLf & "New : " & new_errors;
      cellNode.AppendString(false, text);
    else
      text = " (" & object.fileRuleCount & " violated rules, " & object.fileErrorCount & " errors)";
      FillCell(success, text, object.xmlDocument, cellNode);
    endif
    
    if ifile != (nfile-1) then
      /* Add new line */
      object.rowNode = object.rowClonedNode.CloneNode(true);
      object.tableNode.Append(object.rowNode);
    endif
  endif
endfunction

function CloseDoc(object)
  /* Save document*/
  object.xmlDocument.Save();
  object.xmlDocument = null;
  object.contentNode = null;
  object.nodes = null;
  object.xml.Terminate();
  object.xml = null;
  print("Document saved.");

  /* Convert document */
  print("Conversion in progress ...");
  outputDir = new Folder(object.outputPath);
  absolutePath = outputDir.AbsolutePath;
  word = new WordMacro();
  word.ConvertToDOC(absolutePath & "/" & object.reportName & ".xml", absolutePath & "/" & object.reportName & ".doc", false);
  word = null;
  print("Conversion finished.");
endfunction

function ReviewCode(srcPath, modelPath, projectName, outputPath)
  rulesCollection = new Array();
  rulesCollection[0] = function:Rule1;
  rulesCollection[1] = function:Rule2;
  rulesCollection[2] = function:Rule3;
  rulesCollection[3] = function:Rule4;
  rulesCollection[4] = function:Rule5;
  rulesCollection[5] = function:Rule6;
  rulesCollection[6] = function:Rule7;
  rulesCollection[7] = function:Rule8;
  rulesCollection[8] = function:Rule9;
  rulesCollection[9] = function:Rule10;
  rulesCollection[10] = function:Rule11;
  rulesCollection[11] = function:Rule12;
  rulesCollection[12] = function:Rule13;
  rulesCollection[13] = function:Rule14;
  rulesCollection[14] = function:Rule15;
  rulesCollection[15] = function:Rule16;
  rulesCollection[16] = function:Rule17;
  rulesCollection[17] = function:Rule18;
  rulesCollection[18] = function:Rule19;
  rulesCollection[19] = function:Rule20;
  rulesCollection[20] = function:Rule21;
  rulesCollection[21] = function:Rule22;
  rulesCollection[22] = function:Rule23;
  rulesCollection[23] = function:Rule24;
  rulesCollection[24] = function:Rule25;
  rulesCollection[25] = function:Rule26;
  rulesCollection[26] = function:Rule27;
  rulesCollection[27] = function:Rule28;
  
  resultWriters = new Array();
  resultWriters[0] = InitDB();
  resultWriters[1] = InitDoc(modelPath, projectName, outputPath, "Report");
  
  CheckRules(srcPath, rulesCollection, function:ValidateRuleDB, resultWriters);
  
  CloseDoc(resultWriters[1]);
  CloseDB();
endfunction

include("./CodingRules/CppCustom/Rules.td");
