constant SYMBOL_TAG = new SymTagEnumType();
constant SYMBOL_SEARCH = new NameSearchOptions();
constant SYMBOL_DATA_KIND = new DataKind();
constant SYMBOL_BASIC_TYPE = new BasicType();

function CollectInfo(PdbPath)

  /* Ouverture du fichier PDB */
  pdbParser = new PdbParser();
  pdbParser.Initialize();

  pdbDataSource = pdbParser.DataSource;
  pdbDataSource.LoadDataFromPdb(PdbPath);

  session = new IDiaSessionPtr();
  global = new IDiaSymbolPtr();
  pdbDataSource.OpenSession(session);
  session.Get_globalScope(global);

  CollectFiles(session, global);
  CollectGlobalData(session, global);

  /* Arrêt */
  global = null;
  session = null;
  pdbDataSource = null;
  pdbParser.Terminate();
  pdbParser = null;
endfunction

function CollectGlobalData(session, global)

  dataSymbols = new IDiaEnumSymbolsPtr();
  global.FindChildren(constant:SYMBOL_TAG.SymTagData, dataSymbols);
  dataSymbolsSize = new Numeric();
  dataSymbols.Get_Count(dataSymbolsSize);
  iDataSymbol = 0;
  /* print("dataSymbolsSize : " & dataSymbolsSize); */
  while iDataSymbol < dataSymbolsSize do
    dataSymbol = new IDiaSymbolPtr();
    dataSymbols.Item(iDataSymbol, dataSymbol);

    name = "";
    dataSymbol.Get_name(name);
    /* print("  var : " & name); */
    if #name > 0 && name.SubString(0, 1) != "_"  then   
      category = "";
      kind = 0;
      dataSymbol.Get_dataKind(kind);
      if kind == 6 then
        category = "Global";

        typename = "";
        symbolType = new IDiaSymbolPtr();
        res = dataSymbol.Get_type(symbolType);
        if res == 0 then
          typeInfo = CollectType(symbolType);
          debugType = InsertDebugType(typeInfo);
        endif

        debugVariable = new DebugVariableInfo();
        debugVariable.Category = category;
        debugVariable.DebugTypeInfo = debugType;
        debugVariable.Name = name;
        constant:DB_ACCESS.debugVariableInfo.InsertDebugVariableInfo(debugVariable);
        /* print(debugVariable); */
      endif
    endif
    iDataSymbol.Increment();
  endwhile
endfunction

function CollectFiles(session, global)

  /* Analyse des fichiers */
  files   = constant:DB_ACCESS.cppFile.GetManyCppFiles("name LIKE '%.cpp' or name LIKE '%.c'");

  ifile   = 0;
  while ifile < #files do

    filenameExt = files[ifile].Name.Split("\.");
    filename = filenameExt[0];
    ext = filenameExt[1];
    
    symbols = new IDiaEnumSymbolsPtr();

    SearchOption = constant:SYMBOL_SEARCH.NsfFNameExt + constant:SYMBOL_SEARCH.NsfCaseInsensitive;
    res = global.FindChildren(constant:SYMBOL_TAG.SymTagCompiland, filename & ".obj", SearchOption, symbols);
    if res == 0 then
        
      count = 0;
      symbols.Get_Count(count);
      if count > 0 then
            
        fileSymbol = new IDiaSymbolPtr();
        symbols.Item(0, fileSymbol);
        symbolName = new String();
        fileSymbol.Get_name(symbolName);        
        arrayChecksum = CollectChecksum(session, fileSymbol, filename);

        debugFile = new DebugFileInfo();
        constant:DB_ACCESS.cppFile.FillTextFile(files[ifile]);
        debugFile.TextFile = files[ifile].TextFile;
        debugFile.Name = files[ifile].Name;
        debugFile.CompilandPath = symbolName;
        debugFile.Checksum = arrayChecksum;
        constant:DB_ACCESS.debugFileInfo.InsertDebugFileInfo(debugFile);
        /* print(debugFile); */

        CollectFunction(session, debugFile, fileSymbol);
      endif
          
    endif
    
    ifile.Increment();
  endwhile 
endfunction

function CollectChecksum(session, fileSymbol, filename)

  SearchOption = constant:SYMBOL_SEARCH.NsfFNameExt + constant:SYMBOL_SEARCH.NsfCaseInsensitive;
  diaEnumSourceFiles = new IDiaEnumSourceFilesPtr();
  session.FindFile(fileSymbol, filename & ".cpp", SearchOption, diaEnumSourceFiles);
  
  sizeEnumSourceFiles = new Numeric();
  diaEnumSourceFiles.Get_Count(sizeEnumSourceFiles);
  
  sizeChecksum = new Numeric();
  arrayChecksum = new Array(); 
  if sizeEnumSourceFiles > 0 then
  
    diaSourceFile = new IDiaSourceFilePtr();
    diaEnumSourceFiles.Item(0, diaSourceFile);
    
    sizeChecksum = 0;
    diaSourceFile.Get_checksum(sizeChecksum, sizeChecksum, arrayChecksum);
    i = 0;
    while i < sizeChecksum do
      arrayChecksum[i] = 0;
      i.Increment();
    endwhile
    diaSourceFile.Get_checksum(sizeChecksum, sizeChecksum, arrayChecksum);
  endif

  /*return*/ arrayChecksum;
endfunction

function CollectFunction(session, debugFile, fileSymbol)

  functions = FindCppFunction("NONE", "NONE", "NONE", "NONE", debugFile.Name, "");
  ifunction = 0;
  while ifunction < #functions do
  
    function = functions[ifunction];
    constant:DB_ACCESS.cppFunction.FillCppClass(function);
    if function.HasCppClass then
      functionName = function.CppClass.Name & "::" & function.Name;
    else 
      functionName = function.Name;
    endif
    functionLine = function.DefLineNumber;
    /* print("searching " & functionName & "(" & functionLine & ")"); */
    functionSymbols = new IDiaEnumSymbolsPtr();
    hr = fileSymbol.FindChildren(constant:SYMBOL_TAG.SymTagFunction, functionName, constant:SYMBOL_SEARCH.NsNone, functionSymbols);       
    functionSymbolsSize = new Numeric();
    functionSymbols.Get_Count(functionSymbolsSize);
    ifunctionSymbol = 0;
    while ifunctionSymbol < functionSymbolsSize do

      functionSymbol = new IDiaSymbolPtr();
      functionSymbols.Item(ifunctionSymbol, functionSymbol);
      
      name = new String();
      res = functionSymbol.Get_undecoratedName(name);
      
      rva = new Numeric();
      res = functionSymbol.Get_relativeVirtualAddress(rva);
      /* print("  address : " & rva.ConvertHex()); */
      
      debugSymbols = new IDiaEnumSymbolsPtr();
      functionSymbol.FindChildren(constant:SYMBOL_TAG.SymTagFuncDebugEnd, debugSymbols);
      debugSymbolsSize = new Numeric();
      debugSymbols.Get_Count(debugSymbolsSize);
      if debugSymbolsSize > 0 then
        debugSymbol = new IDiaSymbolPtr();
        debugSymbols.Item(0, debugSymbol);
        debugEnd = new Numeric();
        res = debugSymbol.Get_relativeVirtualAddress(debugEnd);
        /* print("  end address : " & debugEnd.ConvertHex()); */
      endif
      
      functionSymbol.FindChildren(constant:SYMBOL_TAG.SymTagFuncDebugStart, debugSymbols);
      debugSymbols.Get_Count(debugSymbolsSize);
      if debugSymbolsSize > 0 then
        debugSymbol = new IDiaSymbolPtr();
        debugSymbols.Item(0, debugSymbol);
        debugStart = new Numeric();
        res = debugSymbol.Get_relativeVirtualAddress(debugStart);
        /* print("  start address : " & debugStart.ConvertHex()); */
      endif
      
      functionTypeSymbol = new IDiaSymbolPtr();
      functionSymbol.Get_type(functionTypeSymbol);      
      returnTypeSymbol = new IDiaSymbolPtr();
      functionTypeSymbol.Get_type(returnTypeSymbol);
      returnDebugType = CollectType(returnTypeSymbol);

      lineSymbols = new IDiaEnumLineNumbersPtr();
      session.FindLinesByRVA(rva, 1, lineSymbols);
      lineSymbolsSize  = new Numeric();
      lineSymbols.Get_Count(lineSymbolsSize);
      if lineSymbolsSize > 0 then 
        lineSymbol = new IDiaLineNumberPtr();
        lineSymbols.Item(0, lineSymbol);
        firstLineNumber = new Numeric();
        lineSymbol.Get_lineNumber(firstLineNumber);
        /* print("  first line : " & firstLineNumber); */
        
        session.FindLinesByRVA(debugEnd - 1, 2, lineSymbols);
        lineSymbols.Get_Count(lineSymbolsSize);
        if lineSymbolsSize > 0 then 
          lineSymbols.Item(lineSymbolsSize - 1, lineSymbol);
          lastLineNumber = new Numeric();
          lineSymbol.Get_lineNumber(lastLineNumber);
          /* print("  last line : " & lastLineNumber); */

          debugFunction = new DebugFunctionInfo();
          debugFunction.Name = name;
          debugFunction.Address = rva;
          debugFunction.FirstLineNumber = firstLineNumber;
          debugFunction.LastLineNumber = lastLineNumber;
          debugFunction.DebugTypeInfo = returnDebugType;
          debugFunction.DebugFileInfo = debugFile;
          constant:DB_ACCESS.debugFunctionInfo.InsertDebugFunctionInfo(debugFunction);
          /*print(debugFunction);*/
          CollectData(functionSymbol, debugFunction);
            
        endif
      endif
    
      ifunctionSymbol.Increment();
    endwhile  

    ifunction.Increment();
  endwhile
endfunction

function CollectData(functionSymbol, debugFunction)
  dataSymbols = new IDiaEnumSymbolsPtr();
  functionSymbol.FindChildren(constant:SYMBOL_TAG.SymTagData, dataSymbols);
  dataSymbolsSize = new Numeric();
  dataSymbols.Get_Count(dataSymbolsSize);
  iDataSymbol = 0;
  /* print("dataSymbolsSize : " & dataSymbolsSize); */
  while iDataSymbol < dataSymbolsSize do
    dataSymbol = new IDiaSymbolPtr();
    dataSymbols.Item(iDataSymbol, dataSymbol);
      
    name = "";
    dataSymbol.Get_name(name);
    /* print("  var : " & name); */
    if #name > 0 then
    
      category = "";
      kind = 0;
      dataSymbol.Get_dataKind(kind);
      if kind == 1 then
        category = "Local";
      endif
      if kind == 2 then
        category = "Static Local";
      endif
      if kind == 3 then
        category = "Param";
      endif
      if kind == 4 then
        category = "Object Ptr";
      endif
      if kind == 5 then
        category = "File Static";
      endif
      if kind == 6 then
        category = "Global";
      endif
      if kind == 7 then
        category = "Member";
      endif
      if kind == 8 then
        category = "Static Member";
      endif
      if kind == 9 then
        category = "Constant";
      endif
      
      typename = "";
      symbolType = new IDiaSymbolPtr();
      res = dataSymbol.Get_type(symbolType);
      if res == 0 then
        debugType = CollectType(symbolType);
      endif
    
      debugVariable = new DebugVariableInfo();
      debugVariable.Category = category;
      debugVariable.DebugTypeInfo = debugType;
      debugVariable.Name = name;
      debugVariable.DebugFunctionInfo = debugFunction;
      constant:DB_ACCESS.debugVariableInfo.InsertDebugVariableInfo(debugVariable);
      /* print(debugVariable); */
    endif
    iDataSymbol.Increment();
  endwhile
endfunction

function InsertDebugType(typeInfo)
  types = constant:DB_ACCESS.debugTypeInfo.GetManyDebugTypeInfos("name='" & (typeInfo.Name) & "'");
  if #types == 0 then
    constant:DB_ACCESS.debugTypeInfo.InsertDebugTypeInfo(typeInfo);
  else
    typeInfo = types[0];
  endif
  /*return*/ typeInfo;
endfunction

function CollectType(symbolType)
  /* TypeInfo structure */
  typeInfo = new DebugTypeInfo();
  
  /* Get infos */
  tag = new Numeric();
  symbolType.Get_symTag(tag);
  
  /* Get size of type */
  len = new Numeric();
  symbolType.Get_length(len);
  typeInfo.SizeOf = len;
  typeInfo.ArrayDim = 0;

  if tag != constant:SYMBOL_TAG.SymTagPointerType then
    bSet = new Numeric();
    symbolType.Get_constType(bSet);
    if bSet != 0 then
      typeInfo.Name = typeInfo.Name & "const ";
      typeInfo.IsConst = constant:DB_TRUE;
    endif
    
    symbolType.Get_volatileType(bSet);
    if bSet != 0 then
      typeInfo.Name = typeInfo.Name & "volatile ";
      typeInfo.IsVolatile = constant:DB_TRUE;
    endif
  endif
 
  if tag == constant:SYMBOL_TAG.SymTagUDT then
    udt = new Numeric();
    symbolType.Get_udtKind(udt);
    if udt == 0 then
      typeInfo.Name = typeInfo.Name & "struct ";
      typeInfo.IsStruct = constant:DB_TRUE;
    else
      if udt == 1 then
        typeInfo.Name = typeInfo.Name & "class ";
        typeInfo.IsClass = constant:DB_TRUE;
      else
        if udt == 2 then
          typeInfo.Name = typeInfo.Name & "union ";
          typeInfo.IsUnion = constant:DB_TRUE;
        else 
          if udt == 3 then
            typeInfo.Name = typeInfo.Name & "interface ";
            typeInfo.IsInterface = constant:DB_TRUE;
          endif
        endif
      endif
    endif 
    name = new String();
    symbolType.Get_name(name);
    typeInfo.BaseName = name;
    typeInfo.Name = typeInfo.Name & name;    
  endif
  
  if tag == constant:SYMBOL_TAG.SymTagEnum then
    typeInfo.Name = typeInfo.Name & "enum ";
    name = new String();
    symbolType.Get_name(name);
    typeInfo.BaseName = name;
    typeInfo.Name = typeInfo.Name & name;
    typeInfo.IsEnum = constant:DB_TRUE;
  endif
  
  if tag == constant:SYMBOL_TAG.SymTagFunctionType then
    typeInfo.Name = typeInfo.Name & "function ";
    typeInfo.IsFunction = constant:DB_TRUE;
  endif
  
  if tag == constant:SYMBOL_TAG.SymTagPointerType || tag == constant:SYMBOL_TAG.SymTagArrayType then
      symbolBaseType = new IDiaSymbolPtr();
      res = symbolType.Get_type(symbolBaseType);
      if res == 0 then
        subTypeInfo = CollectType(symbolBaseType);
        typeInfo.Name = typeInfo.Name & subTypeInfo.Name;
        typeInfo.ArrayDim = 1;
        typeInfo.BaseName = subTypeInfo.BaseName;
        typeInfo.PrimitiveType = subTypeInfo;

        bSet = new Numeric();
        symbolType.Get_reference(bSet);
        if bSet != 0 then
          typeInfo.Name = typeInfo.Name & " &";
          typeInfo.IsReference = constant:DB_TRUE;
        else
          typeInfo.BaseName = typeInfo.BaseName & " *";
          if tag == constant:SYMBOL_TAG.SymTagArrayType then
            dim = new Numeric();
            symbolType.Get_count(dim);
            typeInfo.ArrayDim = dim;
            typeInfo.Name = typeInfo.Name & " [" & dim & "]";
            if subTypeInfo.IsChar == constant:DB_TRUE then
              typeInfo.IsString = constant:DB_TRUE;
              typeInfo.IsWide = subTypeInfo.IsWide;
            else
              typeInfo.IsArray = constant:DB_TRUE;
            endif
          else 
            typeInfo.Name = typeInfo.Name & " *";
            if subTypeInfo.IsChar == constant:DB_TRUE then
              typeInfo.IsString = constant:DB_TRUE;
              typeInfo.IsWide = subTypeInfo.IsWide;
            else
              typeInfo.IsPointer = constant:DB_TRUE;
            endif
          endif
          /* 32 bit pointer */
          typeInfo.TypeId = 3;
          if len == 8 then
            /* 64 bit pointer */
            typeInfo.TypeId = 4;
          endif      
        endif    
        
        symbolType.Get_constType(bSet);
        if bSet != 0 then
          typeInfo.Name = typeInfo.Name & " const";
        endif
        
        symbolType.Get_volatileType(bSet);
        if bSet != 0 then
          typeInfo.Name = typeInfo.Name & " volatile";
        endif
      endif
  endif
  
  if tag == constant:SYMBOL_TAG.SymTagBaseType then
    info = new Numeric();
    res = symbolType.Get_baseType(info);
    if res == 0 then
      typeInfo.IsSigned = constant:DB_TRUE;
      
      if info == constant:SYMBOL_BASIC_TYPE.BtUInt then
        typeInfo.BaseName = "unsigned ";
        typeInfo.IsSigned = constant:DB_FALSE;
      endif
      
      if info == constant:SYMBOL_BASIC_TYPE.BtInt || info == constant:SYMBOL_BASIC_TYPE.BtUInt then
        if len == 1 then
          typeInfo.BaseName = typeInfo.BaseName & "char";
          typeInfo.TypeId = 1;
        endif
        if len == 2 then
          typeInfo.BaseName = typeInfo.BaseName & "short";
          typeInfo.TypeId = 2;
        endif
        if len == 4 then
          typeInfo.BaseName = typeInfo.BaseName & "int";
          typeInfo.TypeId = 3;
        endif
        if len == 8 then
          typeInfo.BaseName = typeInfo.BaseName & "__int64";
          typeInfo.TypeId = 4;
        endif
      endif
      
      if info == constant:SYMBOL_BASIC_TYPE.BtChar then
        typeInfo.BaseName = "char";
        typeInfo.TypeId = 1;
        typeInfo.IsChar = constant:DB_TRUE;
        typeInfo.IsSigned = constant:DB_FALSE;
      endif
      
      if info == constant:SYMBOL_BASIC_TYPE.BtWChar then
        typeInfo.BaseName = "wchar_t";
        typeInfo.TypeId = 2;
        typeInfo.IsChar = constant:DB_TRUE;
        typeInfo.IsWide = constant:DB_TRUE;
        typeInfo.IsSigned = constant:DB_FALSE;
      endif
      
      if info == constant:SYMBOL_BASIC_TYPE.BtBool then
        typeInfo.BaseName = "bool";
        typeInfo.TypeId = 1;
        typeInfo.IsBool = constant:DB_TRUE;
        typeInfo.IsSigned = constant:DB_FALSE;
      endif
      
      if info == constant:SYMBOL_BASIC_TYPE.BtLong then
        typeInfo.BaseName = "long";
        typeInfo.TypeId = 3;
      endif
      
      if info == constant:SYMBOL_BASIC_TYPE.BtULong then
        typeInfo.BaseName = "unsigned long";
        typeInfo.TypeId = 3;
        typeInfo.IsSigned = constant:DB_FALSE;
      endif
    
      if info == constant:SYMBOL_BASIC_TYPE.BtFloat then
        if len == 4 then
          typeInfo.BaseName = "float";
          typeInfo.TypeId = 5;
        endif
        if len == 8 then
          typeInfo.BaseName = "double";
          typeInfo.TypeId = 6;
        endif
        typeInfo.IsFloat = constant:DB_TRUE;
      endif
      
      typeInfo.Name = typeInfo.Name & typeInfo.BaseName;
    endif
  endif 
  debugType = InsertDebugType(typeInfo);
  /*return*/ debugType;
endfunction

function AddStub(debugInfo)
  access = constant:DB_ACCESS.debugStubInfo;
  stub = new DebugStubInfo();
  if debugInfo.stubId != -1 then
    CleanDebugValueByStub(debugInfo.stubId);
    stub = access.SelectOneDebugStubInfo(debugInfo.stubId, false);
    access.FillAllDebugValueInfos(stub, false);
    stub.ClearDebugValueInfos();
  endif
  stub.LineNumber = debugInfo.lineNumber;
  if debugInfo.isLineSkipped then
    stub.IsLineSkipped = constant:DB_TRUE;
  else 
    stub.IsLineSkipped = constant:DB_FALSE;
  endif
  stub.DebugFileInfo = constant:DB_ACCESS.debugFileInfo.GetOneDebugFileInfo(debugInfo.fileId);
  i = 0;
  while i < #debugInfo.variables do
    var = new DebugValueInfo();
    var.TextValue = debugInfo.variables[i].textValue;
    var.DebugVariableInfo = constant:DB_ACCESS.debugVariableInfo.GetOneDebugVariableInfo(debugInfo.variables[i].variableId);
    stub.DebugValueInfos(i) = var;
    i.Increment();
  endwhile
  if debugInfo.stubId == -1 then
    access.InsertDebugStubInfo(stub);
  else
    access.UpdateDebugStubInfo(stub);
  endif
endfunction

function RemoveStub(stubId)
  access = constant:DB_ACCESS.debugStubInfo;
  CleanDebugValueByStub(stubId);
  if stubId != -1 then
    stub = access.SelectOneDebugStubInfo(stubId, false);
    access.DeleteDebugStubInfo(stub);
  endif
endfunction

function GetProcessMemoryOffset(dbgSystemObjects, dbgSymbols)
    baseOffset = 0;
    exeName = "";
    res = dbgSystemObjects.GetCurrentProcessExecutableName(exeName);
    exeName.Remove(#exeName - 4, 4);
    res = dbgSymbols.GetSymbolModule(exeName & "!", baseOffset);
    /*return*/ baseOffset;
endfunction

function RunDebug(commandLine, debugInfo)
  CREATE_FLAGS = new CreateFlags();
  WAIT_FLAGS = new WaitFlags();
  TIME_OUT = new TimeOut();
  DEBUG_STATUS = new DebugStatus();

  /* Lancement du debuggeur */
  debugEngine = new DebugEngine();
  debugEngine.Initialize();
  dbgClient = debugEngine.DebugClient;
  dbgControl = debugEngine.DebugControl;
  dbgSymbols = debugEngine.DebugSymbols; 
  dbgSystemObjects = debugEngine.DebugSystemObjects;  
  
  commandFolder = new Folder(commandLine);
  currentDirectory = commandFolder.ParentPath;
  
  /* Lancement du processus à debugger */
  print(commandLine);
  dbgClient.CreateProcess(commandLine, CREATE_FLAGS.DEBUG_ONLY_THIS_PROCESS, currentDirectory);
  
  dbgControl.WaitForEvent(WAIT_FLAGS.DEBUG_WAIT_DEFAULT, TIME_OUT.INFINITE);
  status = DEBUG_STATUS.DEBUG_STATUS_NO_DEBUGGEE;
  dbgControl.GetExecutionStatus(status);

  if status != DEBUG_STATUS.DEBUG_STATUS_NO_DEBUGGEE then
  
    res = dbgSymbols.AppendSymbolPath(debugInfo.PdbPath);

    /* Récupération de l'offset mémoire du processus */
    baseOffset = GetProcessMemoryOffset(dbgSystemObjects, dbgSymbols);
    print(baseOffset.ConvertHex());
    /* Allocation d'une plage d'adresses et écriture de l'appel de la fonction */
    
  else
    print("Error : cannot run debugger");
  endif
  
endfunction
