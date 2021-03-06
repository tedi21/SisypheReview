constant FALSE_VALUE = 0;
constant TRUE_VALUE = 1;
constant INDETERMINATE_VALUE = 2;

function CreateFileData(fileName)
  cppFiles = FindCppFile(fileName, "");
  fileData = new Structure();
  if #cppFiles > 0 then
    /* Données de la base de données */
    fileData.Properties = cppFiles[0];
    /* Identifiant */
    fileData.Identifier = fileData.Properties.Identifier;
    /* Nom du fichier */
    fileData.Name = fileData.Properties.Name;
  endif
  /*Return*/ fileData;
endfunction

function LoadFileData(fileData)
  /* Parser */
  fileData.Parser = new CPPParser();
  /* Texte du fichier */
  constant:DB_ACCESS.cppFile.FillTextFile(fileData.Properties);
  if constant:DB_ACCESS.properties.TextFileEnabled then
    fileData.Text = fileData.Properties.TextFile.Content;
  else
    fileData.Text = fileData.Parser.FileContent(fileData.Properties.Path);
  endif
  fileData.Parser.Parse(fileData.Text);
  fileData.SourceCode = fileData.Parser.SourceCode;
  /* read git info */
  GitBlameFile(fileData);
endfunction

function UnLoadFileData(fileData)
  /* Parser */
  fileData.Parser = null;
  /* Texte du fichier */
  fileData.Text = null;
  fileData.SourceCode = null;
endfunction

function CreateFileDataList(files)
  fileDataList = new Array();
  ifiles = 0;
  while ifiles < #files do
      fileData = CreateFileData(files[ifiles]);
      if #fileData > 0 then
        fileDataList[ifiles] = fileData;
      endif
      ifiles.Increment();
  endwhile
  /*return*/ fileDataList;
endfunction

function GetLine(fileData, pos)
  iLine = 0;
  if pos.IsType("Numeric") then
    if pos > 0 then
      i = fileData.Parser.IndexOf(pos, fileData.Parser.Lines);
      if i != fileData.Parser.NoPos then
        iLine = i;
      endif
    endif
  endif
  /*Return*/ iLine;
endfunction

function GetTextLine(fileData, iLine)
  /*Return*/ fileData.Parser.Extract(iLine, fileData.Parser.Lines);
endfunction

function GetLinePos(fileData, iLine)
  /*Return*/ fileData.Parser.At(iLine, fileData.Parser.Lines);
endfunction

function GetCCommentCount(fileData)
  /*Return*/ fileData.Parser.Size(fileData.Parser.CComments);
endfunction

function GetCCommentLine(fileData, index)
  block = fileData.Parser.At(index, fileData.Parser.CComments);
  /*Return*/ fileData.Parser.IndexOf(block[0], fileData.Parser.Lines);
endfunction

function GetCCommentText(fileData, index)
  /*Return*/ fileData.Parser.Extract(index, fileData.Parser.CComments);
endfunction

function GetCCommentPos(fileData, index)
  block = fileData.Parser.At(index, fileData.Parser.CComments);
  /*Return*/ block[0];
endfunction

function GetCppCommentCount(fileData)
  /*Return*/ fileData.Parser.Size(fileData.Parser.CppComments);
endfunction

function GetCppCommentLine(fileData, index)
  block = fileData.Parser.At(index, fileData.Parser.CppComments);
  /*Return*/ fileData.Parser.IndexOf(block[0], fileData.Parser.Lines);
endfunction

function GetCppCommentText(fileData, index)
  text = fileData.Parser.Extract(index, fileData.Parser.CppComments);
  pBlock = fileData.Parser.At(index, fileData.Parser.CppComments);
  continue = (#pBlock > 1);
  index.Increment();
  while continue do
    block = fileData.Parser.At(index, fileData.Parser.CppComments);
    continue = false;
    if #block > 1 then
      space = fileData.Text.SubString(pBlock[1], block[0] - pBlock[1]);
      if space.Match("\s*", new Match()) then
        text.Append(space);
        str = fileData.Parser.Extract(index, fileData.Parser.CppComments);
        text.Append(str);
        pBlock = block;
        continue = true;
        index.Increment();
      endif 
    endif
  endwhile
  index.Decrement();
  /*Return*/ text;
endfunction

function FindPreviousCppCommentText(fileData, pos)
  text = "";
  lineBlock = fileData.Parser.Range(pos, fileData.Parser.Lines);
  pos = lineBlock[0];
  index = fileData.Parser.Previous(pos, fileData.Parser.CppComments);
  continue = true;
  while continue do
    block = fileData.Parser.At(index, fileData.Parser.CppComments);
    continue = false;
    if #block > 1 then
      space = fileData.Text.SubString(block[1], pos - block[1]);
      if space.Match("\s*", new Match()) then
        str = fileData.Parser.Extract(index, fileData.Parser.CppComments);
        text.Insert(0, str);
        pos = block[0];
        continue = true;
        index.Decrement();
      endif 
    endif
  endwhile
  /*Return*/ text;
endfunction

function GetCppCommentPos(fileData, index)
  block = fileData.Parser.At(index, fileData.Parser.CppComments);
  /*Return*/ block[0];
endfunction

function IsPos(fileData, pos)
  valid = false;
  if pos.IsType("Numeric") then
    if pos > 0 then
      valid = !(fileData.Parser.InRange(pos, fileData.Parser.NoCode));
    endif
  endif
  /*return*/ valid;
endfunction

function FindCppClassInFile(fileData, filter)
	query = "idFile=" & fileData.Identifier & " and lengthBlock!=0";
	if "NONE" != filter then
		query = query & " and " & filter;
	endif
	/*return*/ constant:DB_ACCESS.cppClass.GetManyCppClasss(query);
endfunction

function FindCppDeclarationFunctionInFile(fileData, filter)
	query = "idDecFile=" & fileData.Identifier & " and lengthDecBlock!=0";
	if "NONE" != filter then
		query = query & " and " & filter;
	endif
	/*return*/ constant:DB_ACCESS.cppFunction.GetManyCppFunctions(query);
endfunction

function FindCppDefinitionFunctionInFile(fileData, filter)
	query = "idDefFile=" & fileData.Identifier & " and lengthDefBlock!=0";
	if "NONE" != filter then
		query = query & " and " & filter;
	endif
	/*return*/ constant:DB_ACCESS.cppFunction.GetManyCppFunctions(query);
endfunction

function FindCppDefinitionFunctionInSourceFile(fileData, filter)
	query = "idDefFile=" & fileData.Identifier & " and lengthDefBlock!=0 and (idDefFile!=idDecFile or startDefBlock!=startDecBlock)";
	if "NONE" != filter then
		query = query & " and " & filter;
	endif
	/*return*/ constant:DB_ACCESS.cppFunction.GetManyCppFunctions(query);
endfunction

function FindCppDefinitionFunctionInHeaderFile(fileData, filter)
	query = "idDefFile=" & fileData.Identifier & " and lengthDefBlock!=0 and (idDefFile=idDecFile and startDefBlock=startDecBlock)";
	if "NONE" != filter then
		query = query & " and " & filter;
	endif
	/*return*/ constant:DB_ACCESS.cppFunction.GetManyCppFunctions(query);
endfunction

function FindCppFunctionInFile(fileData, filter)
	query = "((idDefFile=" & fileData.Identifier & " and lengthDefBlock!=0) or (idDecFile=" & fileData.Identifier & " and lengthDecBlock!=0))";
	if "NONE" != filter then
		query = query & " and " & filter;
	endif
	/*return*/ constant:DB_ACCESS.cppFunction.GetManyCppFunctions(query);
endfunction

function FindCppEnumInFile(fileData, filter)
	query = "idFile=" & fileData.Identifier & " and lengthBlock!=0";
	if "NONE" != filter then
		query = query & " and " & filter;
	endif
	/*return*/ constant:DB_ACCESS.cppEnum.GetManyCppEnums(query);
endfunction

function FindCppAttributeInFile(fileData, filter)
	query = "idClass IN (SELECT identifier FROM cppClass WHERE idFile=" & fileData.Identifier & ") and lengthBlock!=0";
	if "NONE" != filter then
		query = query & " and " & filter;
	endif
	/*return*/ constant:DB_ACCESS.cppAttribute.GetManyCppAttributes(query);
endfunction

function FindCppClassAttributeInFile(fileData, filter)
	query = "idClass IN (SELECT identifier FROM cppClass WHERE isStruct=0 and idFile=" & fileData.Identifier & ") and lengthBlock!=0";
	if "NONE" != filter then
		query = query & " and " & filter;
	endif
	/*return*/ constant:DB_ACCESS.cppAttribute.GetManyCppAttributes(query);
endfunction

function FindCppStructAttributeInFile(fileData, filter)
	query = "idClass IN (SELECT identifier FROM cppClass WHERE isStruct=1 and idFile=" & fileData.Identifier & ") and lengthBlock!=0";
	if "NONE" != filter then
		query = query & " and " & filter;
	endif
	/*return*/ constant:DB_ACCESS.cppAttribute.GetManyCppAttributes(query);
endfunction

function FindCppVariableInFile(fileData, filter)
	query = "idFile=" & fileData.Identifier & " and lengthBlock!=0";
	if "NONE" != filter then
		query = query & " and " & filter;
	endif
	/*return*/ constant:DB_ACCESS.cppVariable.GetManyCppVariables(query);
endfunction

function FindCppDeclarationParameterInFile(fileData, filterOnFunction, filterOnParameter)
	query = "idFunction IN (SELECT identifier FROM cppFunction WHERE idDecFile=" & fileData.Identifier;
	if "NONE" != filterOnFunction then
		query = query & " and " & filterOnFunction;
	endif  
  query = query & ") and lengthDecBlock!=0";
	if "NONE" != filterOnParameter then
		query = query & " and " & filterOnParameter;
	endif
	/*return*/ constant:DB_ACCESS.cppParameter.GetManyCppParameters(query);
endfunction

function FindCppDefinitionParameterInFile(fileData, filter)
	query = "idFunction IN (SELECT identifier FROM cppFunction WHERE idDefFile=" & fileData.Identifier & ") and lengthDefBlock!=0";
	if "NONE" != filter then
		query = query & " and " & filter;
	endif
	/*return*/ constant:DB_ACCESS.cppParameter.GetManyCppParameters(query);
endfunction

function FindCppDefinitionParameterInSourceFile(fileData, filter)
	query = "idFunction IN (SELECT identifier FROM cppFunction WHERE idDefFile=" & fileData.Identifier & " and lengthDefBlock!=0 and (idDefFile!=idDecFile or startDefBlock!=startDecBlock))";
	if "NONE" != filter then
		query = query & " and " & filter;
	endif
	/*return*/ constant:DB_ACCESS.cppParameter.GetManyCppParameters(query);
endfunction

function FindCppDefinitionParameterInHeaderFile(fileData, filter)
	query = "idFunction IN (SELECT identifier FROM cppFunction WHERE idDefFile=" & fileData.Identifier & " and lengthDefBlock!=0 and (idDefFile=idDecFile and startDefBlock=startDecBlock))";
	if "NONE" != filter then
		query = query & " and " & filter;
	endif
	/*return*/ constant:DB_ACCESS.cppParameter.GetManyCppParameters(query);
endfunction

function FindCMacroInFile(fileData, filter)
	query = "idFile=" & fileData.Identifier & " and lengthBlock!=0";
	if "NONE" != filter then
		query = query & " and " & filter;
	endif
	/*return*/ constant:DB_ACCESS.cMacro.GetManyCMacros(query);
endfunction

function FindCppEnumConstantInFile(fileData, filter)
	query = "idEnum IN (SELECT identifier FROM cppEnum WHERE idFile=" & fileData.Identifier & ") and lengthBlock!=0";
	if "NONE" != filter then
		query = query & " and " & filter;
	endif
	/*return*/ constant:DB_ACCESS.cppEnumConstant.GetManyCppEnumConstants(query);
endfunction

function FindCppNoticeInFile(fileData, lineNumber, ruleNumber, filter)
	query = "idFile=" & fileData.Identifier & " and lineNumber=" & lineNumber & " and ruleNumber=" & ruleNumber;
	if "NONE" != filter then
		query = query & " and " & filter;
	endif
	/*return*/ constant:DB_ACCESS.cppNotice.GetManyCppNotices(query);
endfunction

function GetIndexClassMethod(minmax, fileId, classId, access, isConstructor, isDestructor, notFoundValue)
  /* Récupération de la méthode de la classe */
  query = "StartDecBlock = (SELECT " & minmax & "(StartDecBlock) FROM cppFunction where idClass = " & 
          classId & " and idDecFile=" & 
          fileId & " and accessSpecifier='" & 
          access & "' and isConstructor = " & 
          isConstructor & " and isDestructor = " &
          isDestructor & " and lengthDecBlock!=0) and idClass = " &
          classId & " and idDecFile=" & 
          fileId & " and accessSpecifier='" & 
          access & "' and isConstructor = " & 
          isConstructor & " and isDestructor = " & 
          isDestructor & " and lengthDecBlock!=0";
  methods = constant:DB_ACCESS.cppFunction.GetManyCppFunctions(query);
  indexMethod = notFoundValue;
  if #methods > 0 then
    indexMethod = methods[0].StartDecBlock;
  endif
  query = "StartDefBlock = (SELECT " & minmax & "(StartDefBlock) FROM cppFunction where idClass = " & 
          classId & " and idDefFile=" & 
          fileId & " and accessSpecifier='" & 
          access & "' and isConstructor = " & 
          isConstructor & " and isDestructor = " & 
          isDestructor & " and lengthDefBlock!=0) and idClass = " &
          classId & " and idDefFile=" & 
          fileId & " and accessSpecifier='" & 
          access & "' and isConstructor = " & 
          isConstructor & " and isDestructor = " & 
          isDestructor & " and lengthDefBlock!=0";
  methods = constant:DB_ACCESS.cppFunction.GetManyCppFunctions(query);
  if #methods > 0 then
    if minmax == "min" && methods[0].StartDefBlock < indexMethod then
      indexMethod = methods[0].StartDefBlock;
    endif
    if minmax == "max" && methods[0].StartDefBlock > indexMethod then
      indexMethod = methods[0].StartDefBlock;
    endif
  endif
  /*return*/ indexMethod;
endfunction

function GetIndexClassAttribute(minmax, classId, access, notFoundValue)
  /* Récupération de l'attribut de la classe */
  query = "StartBlock = (SELECT " & minmax & "(StartBlock) FROM cppAttribute where idClass = " & 
          classId & " and accessSpecifier='" & access & "') and idClass = " &
          classId & " and accessSpecifier='" & access & "'";
  attributes = constant:DB_ACCESS.cppAttribute.GetManyCppAttributes(query);
  indexAttribute = notFoundValue;
  if #attributes > 0 then
    indexAttribute = attributes[0].StartBlock;
  endif
  /*return*/ indexAttribute;
endfunction

function GetIndexEnumAttribute(minmax, fileId, classId, access, notFoundValue)
  /* Récupération de l'énumération de la classe */
  query = "StartBlock = (SELECT " & minmax & "(StartBlock) FROM cppEnum where idClass = " & 
          classId & " and idFile=" & 
          fileId & " and accessSpecifier='" & 
          access & "') and idClass = " &
          classId & " and idFile=" & 
          fileId & " and accessSpecifier='" & 
          access & "'";
  enums = constant:DB_ACCESS.cppEnum.GetManyCppEnums(query);
  indexEnum = notFoundValue;
  if #enums > 0 then
    indexEnum = enums[0].StartBlock;
  endif
  /*return*/ indexEnum;
endfunction

function GetInheritanceClasses(cppClass, partial)
  partial = false;
  classes = new Array();
  classes[0] = cppClass;
  iClass = 0;
  /* On limite la récursion à 20 éléments */
  while iClass < #classes && #classes < 20 do
    derivedClass = classes[iClass];
    constant:DB_ACCESS.cppClass.FillAllCppInheritances(derivedClass, false);
    iInheritance = 0;
    while iInheritance < derivedClass.CppInheritancesCount() do
      inheritance = derivedClass.CppInheritances(iInheritance);
      parentName = inheritance.BaseClassName;
      parentClass = constant:DB_ACCESS.cppClass.GetManyCppClasss("name='" & parentName & "'");
      if #parentClass == 0 then
        partial = true;
      else
        classes[#classes _ -1] = parentClass;
      endif
      iInheritance.Increment();
    endwhile
    iClass.Increment();
  endwhile
  classes[0] = null;
  classes.Sort(function:SortIdentifier);
  classes.Unique(function:EqualIdentifier);
  /*return*/ classes;
endfunction

function IsOverride(method)
  isOverride = constant:INDETERMINATE_VALUE;
  /* Récupération de l'identifiant de la classe */
  constant:DB_ACCESS.cppFunction.FillCppClass(method);
  if method.HasCppClass then
    /* Récupération des classes mères */
    partial = false;
    parentClasses = GetInheritanceClasses(method.CppClass, partial);
    iParent = 0;
    while (isOverride == constant:INDETERMINATE_VALUE) && (iParent < #parentClasses) do
      parentClass = parentClasses[iParent];
      /* Recherche de la méthode de base virtuelle*/
      baseSignature = parentClass.FullName & method.Signature.SubString(#(method.CppClass.FullName), -1);
      query = "idClass=" & parentClass.Identifier & " and isVirtual=1 and signature='" & baseSignature & "'";
      baseMethods = constant:DB_ACCESS.cppFunction.GetManyCppFunctions(query);
      if #baseMethods > 0 then
        isOverride = constant:TRUE_VALUE;
      endif
      iParent.Increment();
    endwhile
    /* Vérification que toutes les classes de bases ont été analysées */
    if !partial && (isOverride == constant:INDETERMINATE_VALUE) then
      isOverride = constant:FALSE_VALUE;
    endif
  endif
  /*return*/ isOverride;
endfunction

function CountColumn(content, pos)
  column = 0;
  found = false;
  j = 1;
  while pos-j >= 0 && !found do
      if content.SubString(pos-j, 1) != Lf then
          if content.SubString(pos-j, 1) == Tab then
              column = column + 4;
          else
              column = column + 1;
          endif
      else
          found = true;
      endif
      j.Increment();
  endwhile
  /* return */ column;
endfunction

function EqualString(a, b)
  /*return*/ a == b;
endfunction

function SortString(a, b)
  /*return*/ a < b;
endfunction

function EqualIdentifier(a, b)
  /*return*/ a.Identifier == b.Identifier;
endfunction

function SortIdentifier(a, b)
  /*return*/ a.Identifier < b.Identifier;
endfunction

function EqualName(a, b)
  /*return*/ a.Name == b.Name;
endfunction

function SortName(a, b)
  /*return*/ a.Name < b.Name;
endfunction

function IsInBlock(value)
  /*return*/ value[0] <= pos && pos < value[1];
endfunction

function IsBeforeBlock(value)
  /*return*/ pos < value[0];
endfunction

function InBlocks(array, pos)
  found = false;
  if pos.IsType("Numeric") then
    if pos > 0 then
      predValid = function:IsInBlock;
      predValid.Variables("pos") = pos;
      predInf = function:IsBeforeBlock;
      predInf.Variables("pos") = pos;
      i = array.Dichotomy(predValid, predInf);
      found = (i != #array);
    endif
  endif
  /*return*/ found;
endfunction

function IsVariableHiddenByLocals(fileData, varName, varPos, functionId)
  /* vérification des variables locales */
  locals = constant:DB_ACCESS.cppVariable.GetManyCppVariables("idFunction=" & functionId & " and name='" & varName & "' order by startblock");
  iLocal = 0;
  isInBlock = false;
  while iLocal < #locals && !isInBlock do
    localBlock = fileData.Parser.Range(locals[iLocal].StartBlock, fileData.Parser.CodeBlock);
    isInBlock = (localBlock[0] <= varPos && varPos < localBlock[1]);
    iLocal.Increment();
  endwhile
  /* vérification des paramètres */
  parameters = FindCppDefinitionParameterInFile(fileData, "idFunction=" & functionId & " and defName='" & varName & "'");
  /*return*/ isInBlock || (#parameters != 0);
endfunction

function IsVariableHiddenByAttributes(varName, function)
  hidden = false;
  constant:DB_ACCESS.cppFunction.FillCppClass(function);
  if function.HasCppClass then
    /* vérification des Attributs */
    attrs = constant:DB_ACCESS.cppAttribute.GetManyCppAttributes("idClass=" & (function.CppClass.Identifier) & " and name='" & varName & "'");
    hidden = (#attrs != 0);
    if !hidden then
      partial = false;
      parentClasses = GetInheritanceClasses(function.CppClass, partial);
      iParent = 0;
      while (!hidden) && (iParent < #parentClasses) do
        parentClass = parentClasses[iParent];
        attrs = constant:DB_ACCESS.cppAttribute.GetManyCppAttributes("idClass=" & (parentClass.Identifier) & " and name='" & varName & "'");
        hidden = (#attrs != 0);
        iParent.Increment();
      endwhile
    endif
  endif
  /*return*/ hidden;
endfunction

function HasEnumeration(text)
  end = #text;
  i = 0;
  brackets = 0;
  enumeration = false;
  while i < end && !enumeration && (brackets >= 0) do
    if text[i] == "(" then
      brackets.Increment();
    endif
    if text[i] == ")" then
      brackets.Decrement();
    endif
    enumeration = (text[i] == ",") && (brackets == 0);
    i.Increment();
  endwhile
  /*return*/ enumeration;
endfunction

function InLambda(fileData, blockId)
  parser = fileData.Parser;
  regex = "(^|\W)\s*\[[^\]]*\]";
  block = parser.At(blockId, parser.CodeBlock);
  statementId = parser.Previous(block[0], parser.Statement);
  txt = parser.Extract(statementId, parser.Statement);
  /*return*/txt.Search(0, #txt, regex, new Match(), 0);
endfunction

function EqualPos(value)
  /*return*/ value == pos;
endfunction

function IsBeforePos(value)
  /*return*/ pos < value;
endfunction

function BinarySearch(array, pos)
  found = false;
  if pos.IsType("Numeric") then
    if pos > 0 then
      predValid = function:EqualPos;
      predValid.Variables("pos") = pos;
      predInf = function:IsBeforePos;
      predInf.Variables("pos") = pos;
      i = array.Dichotomy(predValid, predInf);
      found = (i != #array);
    endif
  endif
  /*return*/ found;
endfunction

function GetMemberInitiliazerListBlock(parser, start, end, block)
  ret = false;
  initId = parser.Previous(start, parser.Statement) + 1;
  initBlock = parser.At(initId, parser.Statement);
  codeBlock = parser.Range(end - 1, parser.CodeBlock);
  if #initBlock > 1 && #codeBlock > 1 then
    if initBlock[0] <= codeBlock[0] then
      block = initBlock;
      ret = true;
    endif
  endif
  /*return*/ ret;
endfunction


function GetFunctionBlock(parser, start, end)
  block = new Array();
  block[0] := start;
  block[1] := end;
  initId = parser.Previous(start, parser.Statement) + 1;
  initBlock = parser.At(initId, parser.Statement);
  codeBlock = parser.Range(end - 1, parser.CodeBlock);
  if #codeBlock > 1 then
    block[0] = null;
    block[0] = null;
    block[0] = codeBlock[0];
    block[1] = codeBlock[1];
    if #initBlock > 1 then
      if initBlock[0] <= codeBlock[0] then
        block[0] = null;
        block[0] = initBlock[0];
      endif
    endif
  endif
  /*return*/ block;
endfunction

