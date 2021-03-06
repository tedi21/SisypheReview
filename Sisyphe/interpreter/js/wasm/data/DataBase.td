constant DB_ACCESS = new Structure();
constant DB_TRUE = 1;
constant DB_FALSE = 0;

function CleanCppFile()
  access = constant:DB_ACCESS.cppFile;
  files  = access.GetAllCppFiles();
  ifile  = #files;
  while ifile > 0 do
    access.SelectOneCppFile(files[ifile-1].Identifier, false);
    access.DeleteCppFile(files[ifile-1]);
    ifile.Decrement();
  endwhile 
endfunction

function MoveCppDeclarationFunction(access, function)
  moved = false;
  access.FillCppDeclarationFile(function);
  if function.HasCppDeclarationFile then
    sqlquery = "idDecFile IS NULL AND idDefFile IS NOT NULL AND signature='" & (function.Signature) & "'";
    otherfunctions = access.SelectManyCppFunctions(sqlquery, false);
    moved = (#otherfunctions > 0);
    if moved then
      iother = #otherfunctions - 1;
      other := otherfunctions[iother];
      access.FillAllCppParameters(other, false);
      access.FillAllCppParameters(function, false);
      iParameter = 0;
      while iParameter < function.CppParametersCount() do
        parameter = function.CppParameters(iParameter);
        otherparam = other.CppParameters(iParameter);
        otherparam.ParamType = parameter.ParamType;
        otherparam.IsConst = parameter.IsConst;
        otherparam.DefaultValue = parameter.DefaultValue;
        otherparam.DecName = parameter.DecName;
        otherparam.DecLineNumber = parameter.DecLineNumber;
        otherparam.StartDecBlock = parameter.StartDecBlock;
        otherparam.LengthDecBlock = parameter.LengthDecBlock;
        iParameter.Increment();
      endwhile
      other.AccessSpecifier = function.AccessSpecifier;
      other.ReturnType = function.ReturnType;
      other.IsConst = function.IsConst;
      other.IsVirtual = function.IsVirtual;
      other.IsVirtualPure = function.IsVirtualPure;
      other.IsStatic = function.IsStatic;
      other.IsOperator = function.IsOperator;
      other.IsConstructor = function.IsConstructor;
      other.IsDestructor = function.IsDestructor;
      other.IsVariadic = function.IsVariadic;
      other.IsTemplate = function.IsTemplate;
      other.IsInline = function.IsInline;
      other.IsConstexpr = function.IsConstexpr;
      other.IsOverride = function.IsOverride;
      other.IsFinal = function.IsFinal;
      other.IsNoexcept = function.IsNoexcept;
      other.CppDeclarationFile = function.CppDeclarationFile;
      other.DecLineNumber = function.DecLineNumber;
      other.StartDecBlock = function.StartDecBlock;
      other.LengthDecBlock = function.LengthDecBlock;
      access.UpdateCppFunction(other);
    endif
  endif
  /*return*/ moved;
endfunction

function ResetCppDefinitionFunctions(idFile)
  access = constant:DB_ACCESS.cppFunction;
  functions = access.GetManyCppFunctions("idDefFile=" & idFile);
  iFunction = 0;
  while iFunction < #functions do
    function = functions[iFunction];
    decMoved = MoveCppDeclarationFunction(access, function);
    access.SelectOneCppFunction(function.Identifier, false);
    access.FillAllCppParameters(function, false);
    access.FillAllCppVariables(function, false);
    if decMoved then
      access.FillCppDeclarationFile(function);
      function.CppDeclarationFile = null;
    endif
    function.StartDefBlock = 0;
    function.LengthDefBlock = 0;
    function.DefLineNumber = 0;
    function.Complexity = 0;
    function.LinesCount = 0;
    function.ClearCppVariables();
    iParameter = 0;
    while iParameter < function.CppParametersCount() do
      parameter = function.CppParameters(iParameter);
      parameter.DefName = "";
      parameter.DefLineNumber = 0;
      parameter.StartDefBlock = 0;
      parameter.LengthDefBlock = 0;
      iParameter.Increment();
    endwhile
    access.UpdateCppFunction(function);
    iFunction.Increment();
  endwhile
endfunction

function ResetCppDeclarationFunctions(idFile)
  access = constant:DB_ACCESS.cppFunction;
  functions = access.SelectManyCppFunctions("idDecFile=" & idFile, false);
  iFunction = 0;
  while iFunction < #functions do
    function = functions[iFunction];
    access.FillAllCppParameters(function, false);
    function.StartDecBlock = 0;
    function.LengthDecBlock = 0;
    function.DecLineNumber = 0;
    iParameter = 0;
    while iParameter < function.CppParametersCount() do
      parameter = function.CppParameters(iParameter);
      parameter.DecName = "";
      parameter.DefaultValue = "";
      parameter.DecLineNumber = 0;
      parameter.StartDecBlock = 0;
      parameter.LengthDecBlock = 0;
      iParameter.Increment();
    endwhile
    access.UpdateCppFunction(function);
    iFunction.Increment();
  endwhile
endfunction

function PurgeCppFunctions()
  access = constant:DB_ACCESS.cppFunction;
  functions = access.SelectManyCppFunctions("idDecFile IS NULL and idDefFile IS NULL", false);
  iFunction = 0;
  while iFunction < #functions do
    function = functions[iFunction];
    access.DeleteCppFunction(function);
    iFunction.Increment();
  endwhile
endfunction

function DeleteCppFile(name)
  access = constant:DB_ACCESS.cppFile;
  files   = access.SelectManyCppFiles("name='" & name & "'", false);
  ifile   = #files;
  while ifile > 0 do
    file = files[ifile-1];
    ResetCppDefinitionFunctions(file.Identifier);
    ResetCppDeclarationFunctions(file.Identifier);
    constant:DB_ACCESS.cppFile.FillTextFile(file);
    DeleteTextFile(file.TextFile.Rowid);
    access.DeleteCppFile(file);
    ifile.Decrement();
  endwhile
  PurgeCppFunctions();
endfunction

function CleanCppClass()
  access = constant:DB_ACCESS.cppClass;
  classes = access.GetAllCppClasss();
  iclass  = #classes;
  while iclass > 0 do
    access.SelectOneCppClass(classes[iclass-1].Identifier, false);
    access.DeleteCppClass(classes[iclass-1]);
    iclass.Decrement();
  endwhile 
endfunction

function CleanCppFunction()
  access = constant:DB_ACCESS.cppFunction;
  functions = access.GetAllCppFunctions();
  ifunction = #functions;
  while ifunction > 0 do
    access.SelectOneCppFunction(functions[ifunction-1].Identifier, false);
    access.DeleteCppFunction(functions[ifunction-1]);
    ifunction.Decrement();
  endwhile 
endfunction

function CleanCppAttribute()
  access = constant:DB_ACCESS.cppAttribute;
  attributes = access.GetAllCppAttributes();
  iattribute = #attributes;
  while iattribute > 0 do
    access.SelectOneCppAttribute(attributes[iattribute-1].Identifier, false);
    access.DeleteCppAttribute(attributes[iattribute-1]);
    iattribute.Decrement();
  endwhile 
endfunction

function CleanCppVariable()
  access = constant:DB_ACCESS.cppVariable;
  variables = access.GetAllCppVariables();
  ivariable = #variables;
  while ivariable > 0 do
    access.SelectOneCppVariable(variables[ivariable-1].Identifier, false);
    access.DeleteCppVariable(variables[ivariable-1]);
    ivariable.Decrement();
  endwhile 
endfunction

function CleanCppEnum()
  access = constant:DB_ACCESS.cppEnum;
  enums = access.GetAllCppEnums();
  ienum  = #enums;
  while ienum > 0 do
    access.SelectOneCppEnum(enums[ienum-1].Identifier, false);
    access.DeleteCppEnum(enums[ienum-1]);
    ienum.Decrement();
  endwhile 
endfunction

function CleanCMacro()
  access = constant:DB_ACCESS.cMacro;
  macros = access.GetAllCMacros();
  imacro  = #macros;
  while imacro > 0 do
    access.SelectOneCMacro(macros[imacro-1].Identifier, false);
    access.DeleteCMacro(macros[imacro-1]);
    imacro.Decrement();
  endwhile 
endfunction

function CleanCppNotice()
  access = constant:DB_ACCESS.cppNotice;
  notices = access.GetAllCppNotices();
  inotices = #notices;
  while inotices > 0 do
    access.SelectOneCppNotice(notices[inotices-1].Identifier, false);
    access.DeleteCppNotice(notices[inotices-1]);
    inotices.Decrement();
  endwhile 
endfunction

function CleanTextFile()
  access = constant:DB_ACCESS.textFile;
  files = access.GetAllTextFiles();
  ifiles  = #files;
  while ifiles > 0 do
    access.SelectOneTextFile(files[ifiles-1].Rowid, false);
    access.DeleteTextFile(files[ifiles-1]);
    ifiles.Decrement();
  endwhile 
endfunction

function DeleteTextFile(fileId)
  access = constant:DB_ACCESS.textFile;
  file   = access.SelectOneTextFile(fileId, false);
  access.DeleteTextFile(file);
endfunction

function CleanDebugFile()
  access = constant:DB_ACCESS.debugFileInfo;
  debugs = access.GetAllDebugFileInfos();
  idebugs  = #debugs;
  while idebugs > 0 do
    access.SelectOneDebugFileInfo(debugs[idebugs-1].Identifier, false);
    access.DeleteDebugFileInfo(debugs[idebugs-1]);
    idebugs.Decrement();
  endwhile 
endfunction

function CleanDebugFunction()
  access = constant:DB_ACCESS.debugFunctionInfo;
  debugs = access.GetAllDebugFunctionInfos();
  idebugs  = #debugs;
  while idebugs > 0 do
    access.SelectOneDebugFunctionInfo(debugs[idebugs-1].Identifier, false);
    access.DeleteDebugFunctionInfo(debugs[idebugs-1]);
    idebugs.Decrement();
  endwhile 
endfunction

function CleanDebugVariable()
  access = constant:DB_ACCESS.debugVariableInfo;
  debugs = access.GetAllDebugVariableInfos();
  idebugs  = #debugs;
  while idebugs > 0 do
    access.SelectOneDebugVariableInfo(debugs[idebugs-1].Identifier, false);
    access.DeleteDebugVariableInfo(debugs[idebugs-1]);
    idebugs.Decrement();
  endwhile 
endfunction

function CleanCustomParamDebugVariable(idDebugFunction)
  access = constant:DB_ACCESS.debugVariableInfo;
  debugs = access.GetManyDebugVariableInfos("category='CustomParam' and idDebugFunction=" & idDebugFunction);
  idebugs  = #debugs;
  while idebugs > 0 do
    access.SelectOneDebugVariableInfo(debugs[idebugs-1].Identifier, false);
    access.DeleteDebugVariableInfo(debugs[idebugs-1]);
    idebugs.Decrement();
  endwhile 
endfunction

function CleanDebugType()
  access = constant:DB_ACCESS.debugTypeInfo;
  debugs = access.GetAllDebugTypeInfos();
  idebugs  = #debugs;
  while idebugs > 0 do
    access.SelectOneDebugTypeInfo(debugs[idebugs-1].Identifier, false);
    access.DeleteDebugTypeInfo(debugs[idebugs-1]);
    idebugs.Decrement();
  endwhile 
endfunction

function CleanDebugError()
  access = constant:DB_ACCESS.debugErrorInfo;
  debugs = access.GetAllDebugErrorInfos();
  idebugs  = #debugs;
  while idebugs > 0 do
    access.SelectOneDebugErrorInfo(debugs[idebugs-1].Identifier, false);
    access.DeleteDebugErrorInfo(debugs[idebugs-1]);
    idebugs.Decrement();
  endwhile 
endfunction

function CleanDebugStub()
  access = constant:DB_ACCESS.debugStubInfo;
  debugs = access.GetAllDebugStubInfos();
  idebugs  = #debugs;
  while idebugs > 0 do
    access.SelectOneDebugStubInfo(debugs[idebugs-1].Identifier, false);
    access.DeleteDebugStubInfo(debugs[idebugs-1]);
    idebugs.Decrement();
  endwhile 
endfunction

function CleanDebugValue()
  access = constant:DB_ACCESS.debugValueInfo;
  debugs = access.GetAllDebugValueInfos();
  idebugs  = #debugs;
  while idebugs > 0 do
    access.SelectOneDebugValueInfo(debugs[idebugs-1].Identifier, false);
    access.DeleteDebugValueInfo(debugs[idebugs-1]);
    idebugs.Decrement();
  endwhile 
endfunction

function CleanDebugValueByStub(stubId)
  access = constant:DB_ACCESS.debugValueInfo;
  debugs = access.GetManyDebugValueInfos("idDebugStub=" & stubId);
  idebugs  = #debugs;
  while idebugs > 0 do
    access.SelectOneDebugValueInfo(debugs[idebugs-1].Identifier, false);
    access.DeleteDebugValueInfo(debugs[idebugs-1]);
    idebugs.Decrement();
  endwhile 
endfunction

function CleanDebug()
  CleanDebugFile();
  CleanDebugFunction();
  CleanDebugVariable();
  CleanDebugType();
  CleanDebugError();
  CleanDebugStub();
  CleanDebugValue();
endfunction

function Clean()
  CleanTextFile();
  CleanCppFile();
  CleanCppClass();
  CleanCppFunction();
  CleanCppAttribute();
  CleanCppVariable();
  CleanCppEnum();
  CleanCMacro();
  CleanCppNotice();
  CleanDebug();
endfunction

function FindCppFile(name, filter)
  access = constant:DB_ACCESS.cppFile;
  sqlquery = filter;
  if "NONE" != name then
    if #sqlquery > 0 then
      sqlquery = sqlquery & " and ";
    endif
    sqlquery = sqlquery & "name='" & name & "'";
  endif
  /*return*/ access.GetManyCppFiles(sqlquery);
endfunction

function FindCppClass(fullName, fileName, filter)
  access = constant:DB_ACCESS.cppClass;
  sqlquery = filter;
  if "NONE" != fullName then
    if #sqlquery > 0 then
      sqlquery = sqlquery & " and ";
    endif
    sqlquery = sqlquery & "fullName='" & fullName & "'";
  endif
  if "NONE" != fileName then
    if #sqlquery > 0 then
      sqlquery = sqlquery & " and ";
    endif
    sqlquery = sqlquery & "idFile IN (SELECT identifier FROM cppFile WHERE name='" & fileName & "')";
  endif
  /*return*/ access.GetManyCppClasss(sqlquery);
endfunction

function FindCppFunction(signature, name, classFullName, decFileName, defFileName, filter)
  access = constant:DB_ACCESS.cppFunction;
  sqlquery = filter;
   if "NONE" != signature then
    if #sqlquery > 0 then
      sqlquery = sqlquery & " and ";
    endif
    sqlquery = sqlquery & "signature='" & signature & "'";
  endif
  if "NONE" != name then
    if #sqlquery > 0 then
      sqlquery = sqlquery & " and ";
    endif
    sqlquery = sqlquery & "name='" & name & "'";
  endif
  if "NONE" != classFullName then
    if #sqlquery > 0 then
      sqlquery = sqlquery & " and ";
    endif
    sqlquery = sqlquery & "idClass IN (SELECT identifier FROM cppClass WHERE fullName='" & classFullName & "')";
  endif
  if "NONE" != decFileName then
    if #sqlquery > 0 then
      sqlquery = sqlquery & " and ";
    endif
    sqlquery = sqlquery & "idDecFile IN (SELECT identifier FROM cppFile WHERE name='" & decFileName & "')";
  endif
  if "NONE" != defFileName then
    if #sqlquery > 0 then
      sqlquery = sqlquery & " and ";
    endif
    sqlquery = sqlquery & "idDefFile IN (SELECT identifier FROM cppFile WHERE name='" & defFileName & "')";
  endif
  /*return*/ access.GetManyCppFunctions(sqlquery);
endfunction

function FindCppParameter(functionId, order, filter)
  access = constant:DB_ACCESS.cppParameter;
  sqlquery = filter;
  if "NONE" != order then
    if #sqlquery > 0 then
      sqlquery = sqlquery & " and ";
    endif
    sqlquery = sqlquery & "paramOrder='" & order & "'";
  endif
  if "NONE" != functionId then
    if #sqlquery > 0 then
      sqlquery = sqlquery & " and ";
    endif
    sqlquery = sqlquery & "idFunction='" & functionId & "'";
  endif
  /*return*/ access.GetManyCppParameters(sqlquery);
endfunction

function FindCppAttribute(name, classFullName, filter)
  access = constant:DB_ACCESS.cppAttribute;
  sqlquery = filter;
  if "NONE" != name then
    if #sqlquery > 0 then
      sqlquery = sqlquery & " and ";
    endif
    sqlquery = sqlquery & "name='" & name & "'";
  endif
  if "NONE" != classFullName then
    if #sqlquery > 0 then
      sqlquery = sqlquery & " and ";
    endif
    sqlquery = sqlquery & "idClass IN (SELECT identifier FROM cppClass WHERE fullName='" & classFullName & "')";
  endif
  /*return*/ access.GetManyCppAttributes(sqlquery);
endfunction

function FindCppVariable(name, functionId, filter)
  access = constant:DB_ACCESS.cppVariable;
  sqlquery = filter;
  if "NONE" != name then
    if #sqlquery > 0 then
      sqlquery = sqlquery & " and ";
    endif
    sqlquery = sqlquery & "name='" & name & "'";
  endif
  if "NONE" != functionId then
    if #sqlquery > 0 then
      sqlquery = sqlquery & " and ";
    endif
    sqlquery = sqlquery & "idFunction='" & functionId & "'";
  endif
  /*return*/ access.GetManyCppVariables(sqlquery);
endfunction

function FindCppEnum(name, classFullName, fileName, filter)
  access = constant:DB_ACCESS.cppEnum;
  sqlquery = filter;
  if "NONE" != name then
    if #sqlquery > 0 then
      sqlquery = sqlquery & " and ";
    endif
    sqlquery = sqlquery & "name='" & name & "'";
  endif
  if "NONE" != classFullName then
    if #sqlquery > 0 then
      sqlquery = sqlquery & " and ";
    endif
    sqlquery = sqlquery & "idClass IN (SELECT identifier FROM cppClass WHERE fullName='" & classFullName & "')";
  endif
  if "NONE" != fileName then
    if #sqlquery > 0 then
      sqlquery = sqlquery & " and ";
    endif
    sqlquery = sqlquery & "idFile IN (SELECT identifier FROM cppFile WHERE name='" & fileName & "')";
  endif
  /*return*/ access.GetManyCppEnum(sqlquery);
endfunction

function FindCppEnumConstant(enumId, name, filter)
  access = constant:DB_ACCESS.cppEnumConstant;
  sqlquery = filter;
  if "NONE" != name then
    if #sqlquery > 0 then
      sqlquery = sqlquery & " and ";
    endif
    sqlquery = sqlquery & "name='" & name & "'";
  endif
  if "NONE" != functionId then
    if #sqlquery > 0 then
      sqlquery = sqlquery & " and ";
    endif
    sqlquery = sqlquery & "idEnum='" & enumId & "'";
  endif
  /*return*/ access.GetManyCppEnumConstant(sqlquery);
endfunction

function FindCMacro(name, fileName, filter)
  access = constant:DB_ACCESS.cMacro;
  sqlquery = filter;
  if "NONE" != name then
    if #sqlquery > 0 then
      sqlquery = sqlquery & " and ";
    endif
    sqlquery = sqlquery & "name='" & name & "'";
  endif
  if "NONE" != fileName then
    if #sqlquery > 0 then
      sqlquery = sqlquery & " and ";
    endif
    sqlquery = sqlquery & "idFile IN (SELECT identifier FROM cppFile WHERE name='" & fileName & "')";
  endif
  /*return*/ access.GetManyCMacro(sqlquery);
endfunction

function IsDatabaseColumnExist(connection, table, column)
  exist = false;
  /* Lecture de la base */
  columns = new Array();
  columns[0] = "COUNT(*) as cptColumn";
  tables = new Array();
  tables[0] = "pragma_table_info('" & table & "')";
  where = "name='" & column & "'";
  statement = connection.Select(columns, tables, where);
  textError = "";
  if !connection.GetError(textError) then
    while statement.ExecuteStep() do
      cptColumn = 0;
      if statement.GetInt( 0, cptColumn ) then
        exist = (cptColumn > 0);
      endif
    endwhile
  else
     print("Error DB File : " & textError);
  endif 
  /*return*/ exist;
endfunction

function IsError()
  error = false;
  textError = "";
  if constant:DB_ACCESS.cppFile.GetError(textError) then
     error = true;
     print("Error DB File : " & textError);
  endif
  if constant:DB_ACCESS.cppClass.GetError(textError) then
     error = true;
     print("Error DB Class : " & textError);
  endif
  if constant:DB_ACCESS.cppInheritance.GetError(textError) then
     error = true;
     print("Error DB Inheritance : " & textError);
  endif
  if constant:DB_ACCESS.cppFunction.GetError(textError) then
     error = true;
     print("Error DB Function : " & textError);
  endif
  if constant:DB_ACCESS.cppAttribute.GetError(textError) then
     error = true;
     print("Error DB Attribute : " & textError);
  endif
  if constant:DB_ACCESS.cppParameter.GetError(textError) then
     error = true;
     print("Error DB Parameter : " & textError);
  endif
  if constant:DB_ACCESS.cppFileType.GetError(textError) then
     error = true;
     print("Error DB FileType : " & textError);
  endif
  if constant:DB_ACCESS.cppInclude.GetError(textError) then
     error = true;
     print("Error DB Include : " & textError);
  endif
  if constant:DB_ACCESS.cppEnum.GetError(textError) then
     error = true;
     print("Error DB Enum : " & textError);
  endif
  if constant:DB_ACCESS.cppEnumConstant.GetError(textError) then
     error = true;
     print("Error DB EnumConstant : " & textError);
  endif
  if constant:DB_ACCESS.cMacro.GetError(textError) then
     error = true;
     print("Error DB Macro : " & textError);
  endif
  if constant:DB_ACCESS.textFile.GetError(textError) then
     error = true;
     print("Error DB TextFile : " & textError);
  endif
  if constant:DB_ACCESS.cppNotice.GetError(textError) then
     error = true;
     print("Error DB CppNotice : " & textError);
  endif
  if constant:DB_ACCESS.debugFileInfo.GetError(textError) then
     error = true;
     print("Error DB DebugFileInfo : " & textError);
  endif
  if constant:DB_ACCESS.debugFunctionInfo.GetError(textError) then
     error = true;
     print("Error DB DebugFunctionInfo : " & textError);
  endif
  if constant:DB_ACCESS.debugVariableInfo.GetError(textError) then
     error = true;
     print("Error DB DebugVariableInfo : " & textError);
  endif
  if constant:DB_ACCESS.debugTypeInfo.GetError(textError) then
     error = true;
     print("Error DB DebugTypeInfo : " & textError);
  endif
  if constant:DB_ACCESS.debugErrorInfo.GetError(textError) then
     error = true;
     print("Error DB DebugErrorInfo : " & textError);
  endif
  if constant:DB_ACCESS.debugStubInfo.GetError(textError) then
     error = true;
     print("Error DB DebugStubInfo : " & textError);
  endif
  if constant:DB_ACCESS.debugValueInfo.GetError(textError) then
     error = true;
     print("Error DB DebugValueInfo : " & textError);
  endif
  /*return*/ error;
endfunction

constant:DB_ACCESS.connection = new Connection();
constant:DB_ACCESS.connection.SetPragma("synchronous = OFF");
constant:DB_ACCESS.connection.SetPragma("journal_mode = MEMORY");
constant:DB_ACCESS.cppFile		= new CppFileAccess();
constant:DB_ACCESS.cppClass		= new CppClassAccess();
constant:DB_ACCESS.cppInheritance = new CppInheritanceAccess();
constant:DB_ACCESS.cppFunction	= new CppFunctionAccess();
constant:DB_ACCESS.cppParameter	= new CppParameterAccess();
constant:DB_ACCESS.cppAttribute	= new CppAttributeAccess();
constant:DB_ACCESS.cppVariable	= new CppVariableAccess();
constant:DB_ACCESS.cppFileType	= new CppFileTypeAccess();
constant:DB_ACCESS.cppInclude	= new CppIncludeAccess();
constant:DB_ACCESS.cppEnum		= new CppEnumAccess();
constant:DB_ACCESS.cppEnumConstant = new CppEnumConstantAccess();
constant:DB_ACCESS.cMacro 		= new CMacroAccess();
constant:DB_ACCESS.cppNotice	= new CppNoticeAccess();
constant:DB_ACCESS.textFile		= new TextFileAccess();
constant:DB_ACCESS.rule = new RuleAccess();
constant:DB_ACCESS.debugFileInfo= new DebugFileInfoAccess();
constant:DB_ACCESS.debugFunctionInfo= new DebugFunctionInfoAccess();
constant:DB_ACCESS.debugVariableInfo= new DebugVariableInfoAccess();
constant:DB_ACCESS.debugTypeInfo= new DebugTypeInfoAccess();
constant:DB_ACCESS.debugErrorInfo= new DebugErrorInfoAccess();
constant:DB_ACCESS.debugStubInfo= new DebugStubInfoAccess();
constant:DB_ACCESS.debugValueInfo= new DebugValueInfoAccess();
constant:DB_ACCESS.properties   = new Structure();
constant:DB_ACCESS.properties.TextFileEnabled = false;

/* Migrate old database */
if !IsDatabaseColumnExist(constant:DB_ACCESS.connection, "rule", "number") then
  constant:DB_ACCESS.connection.Exec("CREATE TABLE rule ( identifier INTEGER NOT NULL, number INTEGER NOT NULL, description VARCHAR(512) NOT NULL, enabled INTEGER NOT NULL, CONSTRAINT PK_RULE PRIMARY KEY(identifier))");
endif
if !IsDatabaseColumnExist(constant:DB_ACCESS.connection, "cppNotice", "isNew") then
  constant:DB_ACCESS.connection.Exec("ALTER TABLE cppNotice ADD COLUMN isNew INTEGER DEFAULT 0");
endif
if !IsDatabaseColumnExist(constant:DB_ACCESS.connection, "cppNotice", "commitHash") then
  constant:DB_ACCESS.connection.Exec("ALTER TABLE cppNotice ADD COLUMN commitHash TEXT DEFAULT ''");
endif
if !IsDatabaseColumnExist(constant:DB_ACCESS.connection, "cppNotice", "commitDate") then
  constant:DB_ACCESS.connection.Exec("ALTER TABLE cppNotice ADD COLUMN commitDate TEXT DEFAULT ''");
endif
if !IsDatabaseColumnExist(constant:DB_ACCESS.connection, "cppNotice", "commitAuthor") then
  constant:DB_ACCESS.connection.Exec("ALTER TABLE cppNotice ADD COLUMN commitAuthor TEXT DEFAULT ''");
endif
if !IsDatabaseColumnExist(constant:DB_ACCESS.connection, "cppNotice", "commitLine") then
  constant:DB_ACCESS.connection.Exec("ALTER TABLE cppNotice ADD COLUMN commitLine INTEGER DEFAULT 0");
endif
if !IsDatabaseColumnExist(constant:DB_ACCESS.connection, "cppFile", "isTracked") then
  constant:DB_ACCESS.connection.Exec("ALTER TABLE cppFile ADD COLUMN isTracked INTEGER DEFAULT 0");
endif
if !IsDatabaseColumnExist(constant:DB_ACCESS.connection, "cppNotice", "derogation") then
  constant:DB_ACCESS.connection.Exec("ALTER TABLE cppNotice ADD COLUMN derogation TEXT DEFAULT ''");
endif