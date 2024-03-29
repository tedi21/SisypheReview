/* Type names start with a capital letter and have a capital letter for each new word, with no underscore. */
function Rule1_1(fileData, errorList)
  print("  Type names start with a capital letter and have a capital letter for each new word, with no underscore.");
  success = true;
  classes = FindCppClassInFile(fileData, "NONE");
  iClass = 0;
  while iClass < #classes do
    /* Error formatting */
    if !(classes[iClass].Name.Match("[A-Z][a-zA-Z0-9]*", new Match())) then
      success = false;
      line = classes[iClass].LineNumber;
      description = "Type names should start with a capital letter and have a capital letter for each new word, with no underscore.";
      AppendError(fileData, errorList, 1, "Naming [R1]", description, line);
    endif
    iClass.Increment();
    endwhile
    /*return*/ success;
endfunction

/* Type names start with a capital letter and have a capital letter for each new word, with no underscore. */
function Rule1_2(fileData, errorList)
  success = true;
  enums = FindCppEnumInFile(fileData, "NONE");
  iEnum = 0;
  while iEnum < #enums do
    /* Error formatting */
    if !(enums[iEnum].Name.Match("[A-Z][a-zA-Z0-9]*", new Match())) then
      success = false;
      line = enums[iEnum].LineNumber;
      description = "Type names should start with a capital letter and have a capital letter for each new word, with no underscore.";
      AppendError(fileData, errorList, 1, "Naming [R1]", description, line);
    endif
    iEnum.Increment();
    endwhile
    /*return*/ success;
endfunction

function Rule1(fileData, errorList)
    /*return*/ Rule1_1(fileData, errorList) &&
               Rule1_2(fileData, errorList);
endfunction

/* The names of variables are all lowercase, with underscores between words. */
function Rule2(fileData, errorList)
  print("  The names of variables are all lowercase, with underscores between words.");
  success = true;
  variables = FindCppVariableInFile(fileData, "(isStatic!=1 or isConst!=1)");
  iVariable = 0;
  while iVariable < #variables do
  
    /* Error formatting */
    if !(variables[iVariable].Name.Match("[a-z_0-9]+", new Match())) then
      success = false;
      line = variables[iVariable].LineNumber;
      description = "The names of variables are all lowercase, with underscores between words.";
      AppendError(fileData, errorList, 2, "Naming [R2]", description, line);
    endif
    iVariable.Increment();
  endwhile
  /*return*/ success;
endfunction

/* The names of data members are all lowercase, with underscores between words. Data members of classes (but not structs) additionally have trailing underscores. */
function Rule3_1(fileData, errorList)
  print("  The names of data members are all lowercase, with underscores between words. Data members of classes (but not structs) additionally have trailing underscores.");
  success = true;
  attributes = FindCppClassAttributeInFile(fileData, "(isConst=0 or isStatic=0)");
  iAttribute = 0;
  while iAttribute < #attributes do
  
    /* Error formatting */
    if !(attributes[iAttribute].Name.Match("[a-z_0-9]+_", new Match())) then
      success = false;
      line = attributes[iAttribute].LineNumber;
      description = "The names of data members are all lowercase, with underscores between words. Data members of classes (but not structs) additionally have trailing underscores.";
      AppendError(fileData, errorList, 3, "Naming [R3]", description, line);
    endif
    iAttribute.Increment();
    endwhile
    /*return*/ success;
endfunction

function Rule3_2(fileData, errorList)
  success = true;
  attributes = FindCppStructAttributeInFile(fileData, "(isConst=0 or isStatic=0)");
  iAttribute = 0;
  while iAttribute < #attributes do
  
    /* Error formatting */
    if !(attributes[iAttribute].Name.Match("[a-z_0-9]+", new Match())) then
      success = false;
      line = attributes[iAttribute].LineNumber;
      description = "The names of data members are all lowercase, with underscores between words. Data members of classes (but not structs) additionally have trailing underscores.";
      AppendError(fileData, errorList, 3, "Naming [R3]", description, line);
    endif
    iAttribute.Increment();
    endwhile
    /*return*/ success;
endfunction

function Rule3(fileData, errorList)
    /*return*/ Rule3_1(fileData, errorList) &&
               Rule3_2(fileData, errorList);
endfunction

/* Variables declared const, and whose value is fixed for the duration of the program, are named with a leading "k" followed by mixed case. */
function Rule4_1(fileData, errorList)
  print("  Variables declared const, and whose value is fixed for the duration of the program, are named with a leading "k" followed by mixed case.");
  success = true;
  attributes = FindCppAttributeInFile(fileData, "isConst=1 and isStatic=1");
  iAttribute = 0;
  while iAttribute < #attributes do
  
    /* Error formatting */
    if !(attributes[iAttribute].Name.Match("k[a-zA-Z0-9]+", new Match())) then
      success = false;
      line = attributes[iAttribute].LineNumber;
      description = "Variables declared const, and whose value is fixed for the duration of the program, are named with a leading "k" followed by mixed case.";
      AppendError(fileData, errorList, 4, "Naming [R4]", description, line);
    endif
    iAttribute.Increment();
    endwhile
    /*return*/ success;
endfunction

function Rule4_2(fileData, errorList)
  success = true;
  variables = FindCppVariableInFile(fileData, "(isStatic=1 and isConst=1)");
  iVariable = 0;
  while iVariable < #variables do
  
    /* Error formatting */
    if !(variables[iVariable].Name.Match("k[a-zA-Z0-9]+", new Match())) then
      success = false;
      line = variables[iVariable].LineNumber;
      description = "Variables declared const, and whose value is fixed for the duration of the program, are named with a leading "k" followed by mixed case.";
      AppendError(fileData, errorList, 4, "Naming [R4]", description, line);
    endif
    iVariable.Increment();
  endwhile
  /*return*/ success;
endfunction

function Rule4(fileData, errorList)
    /*return*/ Rule4_1(fileData, errorList) &&
               Rule4_2(fileData, errorList);
endfunction

/* Regular functions have mixed case; "cheap" functions may use lower case with underscores. */
function Rule5_1(fileData, errorList)
  print("  Regular functions have mixed case; 'cheap' functions may use lower case with underscores.");
  success = true;
  methods = FindCppDeclarationFunctionInFile(fileData, "isOperator=0 and isDestructor=0 and isConstructor=0");
  iMethod = 0;
  while iMethod < #methods do
  
    /* Error formatting */
    if !(methods[iMethod].Name.Match("[A-Z][a-zA-Z0-9]*", new Match()) ||
         methods[iMethod].Name.Match("[a-z_0-9]+", new Match())) then
      success = false;
      line = methods[iMethod].DecLineNumber;
      description = "Regular functions have mixed case; "cheap" functions may use lower case with underscores.";
      AppendError(fileData, errorList, 5, "Naming [R5]", description, line);
    endif
    iMethod.Increment();
    endwhile
    /*return*/ success;
endfunction

function Rule5_2(fileData, errorList)
  success = true;
  methods = FindCppDefinitionFunctionInSourceFile(fileData, "isOperator=0 and isDestructor=0 and isConstructor=0");
  iMethod = 0;
  while iMethod < #methods do
    
    /* Error formatting */
    if !(methods[iMethod].Name.Match("[A-Z][a-zA-Z0-9]*", new Match()) ||
         methods[iMethod].Name.Match("[a-z_0-9]+", new Match())) then
      success = false;
      line = methods[iMethod].DefLineNumber;
      description = "Regular functions have mixed case; "cheap" functions may use lower case with underscores.";
      AppendError(fileData, errorList, 5, "Naming [R5]", description, line);
    endif
    iMethod.Increment();
  endwhile
  /*return*/ success;
endfunction

function Rule5(fileData, errorList)
    /*return*/ Rule5_1(fileData, errorList) &&
               Rule5_2(fileData, errorList);
endfunction

/* Enumerators should be named like constants. */
function Rule6(fileData, errorList)
  print("  Enumerators should be named like constants.");
  success = true;
  constants = FindCppEnumConstantInFile(fileData, "NONE");
  iConstant = 0;
  while iConstant < #constants do
  
    /* Error formatting */
    if !(constants[iConstant].Name.Match("k[a-zA-Z0-9]+", new Match())) then
      success = false;
      line = constants[iConstant].LineNumber;
      description = "Enumerators should be named like constants.";
      AppendError(fileData, errorList, 6, "Naming [R6]", description, line);
    endif
    iConstant.Increment();
    endwhile
    /*return*/ success;
endfunction

/* Macros should be named with all capitals and underscores. */
function Rule7(fileData, errorList)
  print("  Macros should be named with all capitals and underscores.");
  success = true;
  macros = FindCMacroInFile(fileData, "isConst=1");
  iMacro = 0;
  while iMacro < #macros do
  
    /* Error formatting */
    if !(macros[iMacro].Name.Match("[A-Z0-9_]+", new Match())) then
      success = false;
      line = macros[iMacro].LineNumber;
      description = "Macros should be named with all capitals and underscores.";
      AppendError(fileData, errorList, 7, "Naming [R7]", description, line);
    endif
    iMacro.Increment();
    endwhile
    /*return*/ success;
endfunction

/* Each class is commented. */
function Rule8(fileData, errorList)
  print("  Each class is commented.");
  success = true;
  classes = FindCppClassInFile(fileData, "NONE");
  iClass = 0;
  while iClass < #classes do
    /* Check if the line before is a comment */
    class = classes[iClass];
    text = FindPreviousCppCommentText(fileData, class.StartBlock);
    /* Error formatting */
    if text == "" then
      success = false;
      description = "The class is not preceded by C++ comments.";
      AppendError(fileData, errorList, 8, "Comments [R8]", description, class.LineNumber);
    endif
    iClass.Increment();
  endwhile
  /*return*/ success;
endfunction

/* Each function declaration is commented. */
function Rule9_1(fileData, errorList)
  print("  Each function declaration is commented.");
  success = true;
  functions = FindCppDeclarationFunctionInFile(fileData, "NONE");
  iFunctions = 0;
  while iFunctions < #functions do
    /* Check if the line before is a comment */
    fct = functions[iFunctions];
    text = FindPreviousCppCommentText(fileData, fct.StartDecBlock);
    /* Error formatting */
    if text == "" then
      success = false;
      if fct.IsConstructor == constant:DB_TRUE then
        description = "The constructor declaration is not preceded by C++ comments.";
      else
        if fct.IsDestructor == constant:DB_TRUE then
          description = "The destructor declaration is not preceded by C++ comments.";
        else
          description = "The method declaration is not preceded by C++ comments.";
        endif
      endif
      AppendError(fileData, errorList, 9, "Comments [R9]", description, fct.DecLineNumber);
    endif
    iFunctions.Increment();
  endwhile
  /*return*/ success;
endfunction

/* Each function declaration is commented. */
function Rule9_2(fileData, errorList)
  success = true;
  functions = FindCppDefinitionFunctionInFile(fileData, "NONE");
  iFunctions = 0;
  while iFunctions < #functions do
    /* Check if the line before is a comment */
    fct = functions[iFunctions];
    text = FindPreviousCppCommentText(fileData, fct.StartDefBlock);
    /* Error formatting */
    if text == "" then
      success = false;
      if fct.IsConstructor == constant:DB_TRUE then
        description = "The constructor definition is not preceded by C++ comments.";
      else
        if fct.IsDestructor == constant:DB_TRUE then
          description = "The destructor definition is not preceded by C++ comments.";
        else
          description = "The method definition is not preceded by C++ comments.";
        endif
      endif
      AppendError(fileData, errorList, 9, "Comments [R9]", description, fct.DefLineNumber);
    endif
    iFunctions.Increment();
  endwhile
  /*return*/ success;
endfunction

function Rule9(fileData, errorList)
    /*return*/ Rule9_1(fileData, errorList) &&
               Rule9_2(fileData, errorList);
endfunction

/* No C comments style. */
function Rule10(fileData, errorList)
  print("  No C comments style.");
  success = true;
  iBlock = 0;
  size = GetCCommentCount(fileData);
  while iBlock < size do
    success = false;
    line = GetCCommentLine(fileData, iBlock)+1;
    description = "C comments style /* */ are not allowed, use C++ comments style //.";
    AppendError(fileData, errorList, 10, "Comments [R10]", description, line);
    iBlock.Increment();
  endwhile
  /*return*/ success;
endfunction

/* Function should not use malloc and free. */
function Rule11(fileData, errorList)
    print("  Function should not use malloc and free.");
    success = true;
    matches = new Match();
    content = fileData.SourceCode;
    start = 0;
    end = #content;
    while content.Search(start, end, "\<malloc\>|\<free\>", matches, start) do
      /* Error formatting */
      success = false;
      line = GetLine(fileData, matches.StringPos)+1;
      description = "Function should not use malloc and free, function shoud use new and delete in place.";
      AppendError(fileData, errorList, 11, "Security [R11]", description, line);
    endwhile
    /*return*/ success;
endfunction

/* Function shoud not use variadic parameter « … ». */
function Rule12_1(fileData, errorList)
    print("  Function shoud not use variadic parameter « … ».");
    success = true;
    functions = FindCppDeclarationFunctionInFile(fileData, "isVariadic=1");
    iFunctions = 0;
    while iFunctions < #functions do
        /* Error formatting */
        success = false;
        line = functions[iFunctions].DecLineNumber;
        description = "Function shoud not use variadic parameter « … ».";
        AppendError(fileData, errorList, 12, "Security [R12]", description, line);
        iFunctions.Increment();
    endwhile
    /*return*/ success;
endfunction

/* Function shoud not use variadic parameter « … ». */
function Rule12_2(fileData, errorList)
    success = true;
    functions = FindCppDefinitionFunctionInFile(fileData, "isVariadic=1");
    iFunctions = 0;
    while iFunctions < #functions do
        /* Error formatting */
        success = false;
        line = functions[iFunctions].DefLineNumber;
        description = "Function shoud not use variadic parameter « … ».";
        AppendError(fileData, errorList, 12, "Security [R12]", description, line);
        iFunctions.Increment();
    endwhile
    /*return*/ success;
endfunction

function Rule12(fileData, errorList)
    /*return*/ Rule12_1(fileData, errorList) &&
               Rule12_2(fileData, errorList);
endfunction

/* Function should not use « goto » keyword. */
function Rule13(fileData, errorList)
    print("  Function should not use « goto » keyword.");
    success = true;
    matches = new Match();
    content = fileData.SourceCode;
    start = 0;
    end = #content;
    while content.Search(start, end, "\<goto\>", matches, start) do
      /* Error formatting */
      success = false;
      line = GetLine(fileData, matches.StringPos)+1;
      description = "« goto » keyword should not be used.";
      AppendError(fileData, errorList, 13, "Readability [R13]", description, line);
    endwhile
    /*return*/ success;
endfunction

/* Attributes should not be public in class. */
function Rule14(fileData, errorList)
    print("  Attributes should not be public in class.");
    success = true;
    attributes = FindCppAttributeInFile(fileData, "accessSpecifier='public' and (isStatic!=1 or isConst!=1)");
    iAttribute = 0;
    while iAttribute < #attributes do
        /* Error formatting */
        success = false;
        line = attributes[iAttribute].LineNumber;
        description = "Attributes should not be public in class.";
        AppendError(fileData, errorList, 14, "Security [R14]", description, line);
        iAttribute.Increment();
    endwhile
    /*return*/ success;
endfunction

/* Function should not have several return. */
function Rule15(fileData, errorList)
  print("  Function should not have several return.");
  success = true;
  matches = new Match();
  content = fileData.SourceCode;
  functions = FindCppDefinitionFunctionInFile(fileData, "NONE");
  iFunctions = 0;
  while iFunctions < #functions do
    /* Search return keyword */
    function = functions[iFunctions];
    startPos = function.StartDefBlock;
    endPos = startPos + function.LengthDefBlock;
    maxReturnCount = 1;
    maxReturnDescription = "Function should not have several return.";
    if function.ReturnType == "void" then
      maxReturnCount = 0;
      maxReturnDescription = "Void return function should not have return.";
    endif
    cpt = 0;
    while content.Search(startPos, endPos, "\<return\>", matches, startPos) && cpt <= maxReturnCount do
      cpt.Increment();
      if cpt > maxReturnCount then
        /* Formatting error */
        success = false;
        line = function.DefLineNumber;
        AppendError(fileData, errorList, 15, "Readability [R15]", maxReturnDescription, line);
      else
        statementReturnId = fileData.Parser.IndexOf(startPos, fileData.Parser.Statement);
        statementEndId = fileData.Parser.Previous(endPos - 1, fileData.Parser.Statement);
        blockReturnId = fileData.Parser.IndexOf(startPos, fileData.Parser.CodeBlock);
        blockEndId = fileData.Parser.IndexOf(endPos - 1, fileData.Parser.CodeBlock);
        if blockReturnId != blockEndId || statementReturnId != statementEndId then
          /* Formatting error */
          success = false;
          line = GetLine(fileData, matches.StringPos) + 1;
          description = "return keyword is not located at the end of the function.";
          AppendError(fileData, errorList, 15, "Readability [R15]", description, line);
        endif
      endif
    endwhile
    iFunctions.Increment();
  endwhile
  /*return*/ success;
endfunction

/* Curly brackets {} should be placed on the same column. */
function Rule16(fileData, errorList)
    print("  Curly brackets {} should be placed on the same column.");
    success = true;
    content = fileData.SourceCode;
    /* Find start block */
    iBlock = 0;
    size = fileData.Parser.Size(fileData.Parser.CodeBlock);
    while iBlock < size do
        block = fileData.Parser.At(iBlock, fileData.Parser.CodeBlock);
        startPos = block[0];
        endPos = block[1] - 1;
        /* Check if_the block have instructions */
        if content.Search(startPos, endPos, ";", new Match(), 0) then
            startColumn = CountColumn(content, startPos);
            endColumn = CountColumn(content, endPos);
            if startColumn != endColumn then
                /* Error formatting */
                success = false;
                line = GetLine(fileData, startPos)+1;
                description = "Curly brackets {} should be placed on the same column.";
                AppendError(fileData, errorList, 16, "Readability [R16]", description, line);
            endif
        endif
        iBlock.Increment();
    endwhile
    /*return*/ success;
endfunction

/* Spaces should be placed around binary operator. */
function Rule17(fileData, errorList)
    print("  Spaces should be placed around binary operator.");
    success = true;
    matches = new Match();
    patternOp =   "(" & Pattern_Include()                              & ")|"
                & "(" & "operator\s*[[:punct:]]+"                      & ")|"
                & "(" & "\w+\s*" & Pattern_TemplateDefinition()        & ")|"
                & "(" & "return"                                       & ")|"
                & "([\]"')}\w]\s*(\+=|-=|\*=|\/=|%=|&=|\|=|\^=|<<=|>>=|==|!=|>=|<=|<<|>>|=|\+|-|\/|%|>|<|&&|\|\||\||\^)(?=[\s\w"'(:{]))";
    /* unmanaged operators : &,* */
    content = fileData.SourceCode;
    start = 0;
    end = #content;
    while content.Search(start, end, patternOp, matches, start) do
        /* Check space */
        index = #matches.SubStrings-1;
        opStr = matches.SubStrings[index];
        opPos = matches.SubStringsPos[index];
        opSize = #opStr;
        if opSize > 0 && !content.SubString(opPos-2, 4).Match("\d(e|E)-\d", new Match()) then
            if (content.SubString(opPos-1, 1) != " " &&
                content.SubString(opPos-1, 1) != Tab &&
                content.SubString(opPos-1, 1) != Lf) ||
                (content.SubString(opPos+opSize, 1) != " " &&
                content.SubString(opPos+opSize, 1) != Tab &&
                content.SubString(opPos+opSize, 1) != Lf  &&
                content.SubString(opPos+opSize, 1) != Cr) then
                /* Error formatting */
                success = false;
                line = GetLine(fileData, opPos)+1;
                description = "Spaces should be placed around binary operator " & opStr & " .";
                AppendError(fileData, errorList, 17, "Readability [R17]", description, line);
            endif
        endif
    endwhile
    /*return*/ success;
endfunction

/* Class allocating memory shoud define copy constructor, copy operator and destructor methods. */
function Rule18(fileData, errorList)
    print("  Class allocating memory shoud define copy constructor, copy operator and destructor methods.");
    success = true;
    content = fileData.SourceCode;
    functions = FindCppDefinitionFunctionInFile(fileData, "isConstructor=1");
    iFunctions = 0;
    while iFunctions < #functions do
        /* Find memory allocation */
        startBody := functions[iFunctions].StartDefBlock;
        endBody := functions[iFunctions].StartDefBlock + functions[iFunctions].LengthDefBlock;
        matches = new Match();
        if content.Search(startBody, endBody, "\s*=\s*new\s*", matches, startBody) then
          constant:DB_ACCESS.cppFunction.FillCppClass(functions[iFunctions]);
          if functions[iFunctions].HasCppClass then
            idClass = functions[iFunctions].CppClass.Identifier;
            /* Find copy constructor */
            signatureCopy = functions[iFunctions].CppClass.FullName & "::" & functions[iFunctions].CppClass.Name & "(const_" & functions[iFunctions].CppClass.Name & "&)";
            hasCopy = #(constant:DB_ACCESS.cppFunction.GetManyCppFunctions("isConstructor=1 and signature='" & signatureCopy & "' and idClass=" & idClass)) > 0;
            /* Find copy operator*/
            signatureOpCopy = functions[iFunctions].CppClass.FullName & "::operator=(const_" & functions[iFunctions].CppClass.Name & "&)";
            hasOpCopy = #(constant:DB_ACCESS.cppFunction.GetManyCppFunctions("isOperator=1 and signature='" & signatureOpCopy & "' and idClass=" & idClass)) > 0;
            /* Find destructor */
            signatureDestructor = functions[iFunctions].CppClass.FullName & "::~" & functions[iFunctions].CppClass.Name & "()";
            hasDestructor = #(constant:DB_ACCESS.cppFunction.GetManyCppFunctions("isDestructor=1 and signature='" & signatureDestructor & "' and idClass=" & idClass)) > 0;
            if !hasCopy || !hasOpCopy || !hasDestructor then
                /* Error formatting */
                success = false;
                line = GetLine(fileData, matches.StringPos)+1;
                description = "Class allocating memory shoud define copy constructor, copy operator and destructor methods.";
                AppendError(fileData, errorList, 18, "Memory [R18]", description, line);
            endif
          endif
        endif
        iFunctions.Increment();
    endwhile
    /*return*/ success;
endfunction

/* Class having virtuals methods should define the destructor as virtual. */
function Rule19(fileData, errorList)
    print("  Class having virtuals methods should define the destructor as virtual.");
    success = true;
    classes = FindCppClassInFile(fileData, "identifier IN (SELECT idClass FROM cppFunction WHERE isVirtual=1)");
    iClass = 0;
    while iClass < #classes do
        /* Find virtual destructor */
        idClass = classes[iClass].Identifier;
        hasVirtualDestructor = #(constant:DB_ACCESS.cppFunction.GetManyCppFunctions("isDestructor=1 and isVirtual=1 and idClass=" & idClass)) > 0;
        if !hasVirtualDestructor  then
            /* Error formatting */
            success = false;
            line = classes[iClass].LineNumber;
            description = "Class having virtuals methods should define the destructor as virtual.";
            AppendError(fileData, errorList, 19, "Memory [R19]", description, line);
        endif
        iClass.Increment();
    endwhile
    /*return*/ success;
endfunction

/* Destructor method should not have throw instruction. */
function Rule20(fileData, errorList)
    print("  Destructor method should not have throw instruction.");
    success = true;
    content = fileData.SourceCode;
    functions = FindCppDefinitionFunctionInFile(fileData, "isDestructor=1");
    iFunctions = 0;
    while iFunctions < #functions do
        startBody := functions[iFunctions].StartDefBlock;
        endBody := functions[iFunctions].StartDefBlock+functions[iFunctions].LengthDefBlock;
        matches = new Match();
        /* Find throw keyword */
        while content.Search(startBody, endBody, "\<throw\>", matches, startBody) do
            /* Error formatting */
            success = false;
            line = GetLine(fileData, matches.StringPos)+1;
            description = "Destructor method should not have throw instruction.";
            AppendError(fileData, errorList, 20, "Memory [R20]", description, line);
        endwhile
        iFunctions.Increment();
    endwhile
    /*return*/ success;
endfunction

/* Array should be desallocated by delete[ ]. */
function Rule21(fileData, errorList)
    print("  Array should be desallocated by delete[ ].");
    success = true;
    content = fileData.SourceCode;
    /* Browse functions */
    functions = FindCppDefinitionFunctionInFile(fileData, "NONE");
    iFunctions = 0;
    while iFunctions < #functions do
        startBody := functions[iFunctions].StartDefBlock;
        endBody := functions[iFunctions].StartDefBlock+functions[iFunctions].LengthDefBlock;
        /* Find new[ ] keyword */
        matches = new Match();
        while content.Search(startBody, endBody, "(\w+)\s*=\s*new\s+(unsigned\s+)?\w+\s*\**\s*\[[^\]]*\]", matches, startBody) do
            /* Get variable name */
            varName = matches.SubStrings[1];    
            /* check if it is member variable */
            attributes = new Array();
            constant:DB_ACCESS.cppFunction.FillCppClass(functions[iFunctions]);
            if functions[iFunctions].HasCppClass then
                attributes = constant:DB_ACCESS.cppAttribute.GetManyCppAttributes("name='" & varName & "' and idClass=" & (functions[iFunctions].CppClass.Identifier));
            endif
            /* Get variable scope */
            if #attributes > 0 then
                scopeQuery = "idClass=" & (functions[iFunctions].CppClass.Identifier);
            else
                scopeQuery = "identifier=" & (functions[iFunctions].Identifier);
            endif
            scopes = FindCppDefinitionFunctionInFile(fileData, scopeQuery);
            iScopes = 0;
            while iScopes < #scopes do
                startScope := scopes[iScopes].StartDefBlock;
                endScope := scopes[iScopes].StartDefBlock+scopes[iScopes].LengthDefBlock;
                /* Find delete keyword */
                matchesDelete = new Match();
                while content.Search(startScope, endScope, "\<delete\>\s+(this\s*->\s*)?" & varName, matchesDelete, startScope) do
                    /* Error formatting */
                    success = false;
                    line = GetLine(fileData, matchesDelete.StringPos)+1;
                    description = "Array should be desallocated by delete[ ].";
                    AppendError(fileData, errorList, 21, "Memory [R21]", description, line);
                endwhile
                iScopes.Increment();
            endwhile
        endwhile
        iFunctions.Increment();
    endwhile
    /*return*/ success;
endfunction

/* Constructor or destructor methods should not call virtuals methods. */
function Rule22(fileData, errorList)
    print("  Constructor or destructor methods should not call vituals methods.");
    success = true;
    content = fileData.SourceCode;
    fctors = FindCppDefinitionFunctionInFile(fileData, "(isDestructor=1 or isConstructor=1) and idClass IS NOT NULL");
    iFctor = 0;
    while iFctor < #fctors do
        fctor = fctors[iFctor];
        startBody := fctor.StartDefBlock;
        endBody := fctor.StartDefBlock + fctor.LengthDefBlock;
        block = fileData.Parser.Range(endBody - 1, fileData.Parser.CodeBlock);
        if #block > 1 then
          startBody = block[0];
          endBody = block[1];
        endif
        constant:DB_ACCESS.cppFunction.FillCppClass(fctor);
        if fctor.HasCppClass then
          fctVirtuals = constant:DB_ACCESS.cppFunction.GetManyCppFunctions("isVirtual=1 and idClass=" & (fctor.CppClass.Identifier)); 
          iFctVirtual = 0;
          while iFctVirtual < #fctVirtuals do
            /* Find virtual method call */
            matches = new Match();
            startSearch := startBody;
            endSearch := endBody;
            regex = "\<" & EscapeRegex(fctVirtuals[iFctVirtual].Name) & "\>";
            while content.Search(startSearch, endSearch, regex, matches, startSearch) do
                /* Error formatting */
                success = false;
                line = GetLine(fileData, matches.StringPos)+1;
                description = "Constructor or destructor methods should not call vituals methods.";
                AppendError(fileData, errorList, 22, "Memory [R22]", description, line);
            endwhile
            iFctVirtual.Increment();
          endwhile
        endif
        iFctor.Increment();
    endwhile
    /*return*/ success;
endfunction

/* Class should declare at least one constructor. */
function Rule23(fileData, errorList)
    print("  Class should declare at least one constructor.");
    success = true;
    classes = FindCppClassInFile(fileData, "isInterface=0");
    iClass = 0;
    while iClass < #classes do
      constant:DB_ACCESS.cppClass.FillManyCppFunctions(classes[iClass], "isConstructor=1", false);
      hasConstructor = classes[iClass].HasCppFunctions();
      constant:DB_ACCESS.cppClass.FillManyCppFunctions(classes[iClass], "isStatic=0 and isVirtualPure=0", false);
      hasNoStatic = classes[iClass].HasCppFunctions();
      constant:DB_ACCESS.cppClass.FillManyCppAttributes(classes[iClass], "isStatic=0", false);
      hasNoStatic = classes[iClass].HasCppAttributes() || hasNoStatic;
      if !hasConstructor && hasNoStatic then
        success = false;
        line = classes[iClass].LineNumber;
        description = "Class should declare at least one constructor.";
        AppendError(fileData, errorList, 23, "Security [R23]", description, line);
      endif
      iClass.Increment();
    endwhile
  /*return*/ success;
endfunction

/* Class should not use multiple inheritances. */
function Rule24(fileData, errorList)
    print("  Class should not use multiple inheritances.");
    success = true;
    classes = FindCppClassInFile(fileData, "NONE");
    iClass = 0;
    while iClass < #classes do
        /* Find all inheritances */
        constant:DB_ACCESS.cppClass.FillAllCppInheritances(classes[iClass], false);
        iInheritance = 0;
        count = 0;
        while success && iInheritance < classes[iClass].CppInheritancesCount do
            /* Check if the class is interface */
            parentName = classes[iClass].CppInheritances(iInheritance).BaseClassName;
            parentClasses = constant:DB_ACCESS.cppClass.GetManyCppClasss("isInterface=0 and name='" & parentName & "'");
            if #parentClasses > 0 then
                count = count + 1;
                if count >= 2 then
                    success = false;
                    line = classes[iClass].LineNumber;
                    description = " Class should not use multiple inheritances.";
                    AppendError(fileData, errorList, 24, "Security [R24]", description, line);
                endif
            endif
            iInheritance.Increment();
        endwhile
        iClass.Increment();
    endwhile
    /*return*/ success;
endfunction

/* Header file « .h » should contain a mechanism that prevents multiple inclusions. */
function Rule25(fileData, errorList)
    print("  Header file « .h » should contain a mechanism that prevents multiple inclusions.");
    success = true;
    constant:DB_ACCESS.cppFile.FillCppFileType(fileData.Properties);
    if fileData.Properties.CppFileType.Identifier == 1 then
      /* Find #ifndef | #if !defined() + #define + #endif */
      preprocessorsFound = false;
      parser = fileData.Parser;
      preprocessorsSize = parser.Size(parser.Preprocessors);
      if preprocessorsSize > 2 then
        matchesIf = new Match();
        strIf = parser.ExtractCode(0, parser.Preprocessors);
        regexIf = "#[[:blank:]]*ifndef[[:blank:]]+(\w+).*";
        preprocessorsFound = strIf.Match(regexIf, matchesIf);
        if !preprocessorsFound then
          regexIf = "#[[:blank:]]*if[[:blank:]]+!defined[[:blank:]]*\([[:blank:]]*(\w+)[[:blank:]]*\).*";
          preprocessorsFound = strIf.Match(regexIf, matchesIf);
        endif
        if preprocessorsFound then
          subStrings = matchesIf.SubStrings;
          regexDefine = "#[[:blank:]]*define[[:blank:]]+" & EscapeRegex(subStrings[1]) & ".*";
          preprocessorsFound = parser.ExtractCode(1, parser.Preprocessors).Match(regexDefine, new Match());
        endif
        if preprocessorsFound then
          regexEndif = "#[[:blank:]]*endif.*";
          lastPreprocessor = preprocessorsSize - 1;
          preprocessorsFound = parser.ExtractCode(lastPreprocessor, parser.Preprocessors).Match(regexEndif, new Match());
        endif
      endif
      if preprocessorsSize > 0 && !preprocessorsFound then
        regexPragma = "#[[:blank:]]*pragma[[:blank:]]+once.*";
        preprocessorsFound = parser.ExtractCode(0, parser.Preprocessors).Match(regexPragma, new Match());
      endif
      if !preprocessorsFound then
        /* Error formatting */
        success = false;
        description = "Header file « .h » should contain a mechanism that prevents multiple inclusions.";
        AppendError(fileData, errorList, 25, "Security [R25]", description, 1);
      endif    
    endif
  /*return*/ success;
endfunction

/*  'operator=' should check for assignment to self. */
function Rule26(fileData, errorList)
    print("  'operator=' should check for assignment to self.");
    success = true;
    functions = FindCppDefinitionFunctionInFile(fileData, "isOperator=1");
    iFunctions = 0;
    while iFunctions < #functions do
        function = functions[iFunctions];
        if function.Name.Match("operator[[:space:]]*=[[:space:]]*", new Match()) then
            startBody = function.StartDefBlock;
            parser = fileData.Parser;
            if parser.Size(parser.Statement) > 0 then
              statementIndex = parser.Previous(startBody, parser.Statement) + 1;
              parameters = FindCppDefinitionParameterInFile(fileData, "(idFunction=" & function.Identifier & ")");
              if #parameters > 0 then
                parameter = parameters[0];
                condition1 = "(\<this\>\s*!=\s*&\s*\<" & parameter.DefName & "\>)";
                condition2 = "(&\s*\<" & parameter.DefName & "\>\s*!=\s*\<this\>)";
                regex = "if\s+\(\s*(" & condition1 & "|" & condition2 & ")\s*\).+";
                if !(parser.ExtractCode(statementIndex, parser.Statement).Match(regex, new Match())) then
                    /* Error formatting */
                    success = false;
                    line = function.DefLineNumber;
                    description = "'operator=' should check for assignment to self.";
                    AppendError(fileData, errorList, 26, "Security [R26]", description, line);
                endif
              endif
            endif
        endif
        iFunctions.Increment();
    endwhile
    /*return*/ success;
endfunction

/* 'operator=' should return reference to self. */
function Rule27(fileData, errorList)
    print("  'operator=' should return reference to self.");
    success = true;
    matches = new Match();
    functions = FindCppDefinitionFunctionInFile(fileData, "isOperator=1");
    iFunctions = 0;
    while iFunctions < #functions do
      function = functions[iFunctions];
      if function.Name.Match("operator[[:space:]]*=[[:space:]]*", matches) then
        startPos = function.StartDefBlock;
        endPos = startPos + function.LengthDefBlock;
        parser = fileData.Parser;
        if parser.Size(parser.Statement) > 0 then
          statementIndex = parser.Previous(endPos, parser.Statement);
          returnText = parser.ExtractCode(statementIndex, parser.Statement);
          if !returnText.Match("\s*return\s*\*\s*\<this\>\s*;", matches) then
            /* Error formatting */
            success = false;
            line = function.DefLineNumber;
            description = "'operator=' should return reference to self.";
            AppendError(fileData, errorList, 27, "Security [R27]", description, line);
          endif
        endif
        constant:DB_ACCESS.cppFunction.FillCppClass(function);
        if function.HasCppClass then
          if !(function.ReturnType.Match("\s*" & function.CppClass.Name & "\s*&\s*", new Match())) then
            /* Error formatting */
            success = false;
            line = function.DefLineNumber;
            description = "'operator=' should return reference to self.";
            AppendError(fileData, errorList, 27, "Security [R27]", description, line);
          endif
        endif
      endif
      iFunctions.Increment();
    endwhile
    /*return*/ success;
endfunction

/* Getter method should be const. */
function Rule28(fileData, errorList)
    print("  Getter method should be const.");
    success = true;
    parser = fileData.Parser;
    functions = FindCppDefinitionFunctionInFile(fileData, "(isConst=0 and isStatic=0 and isVirtual=0 and idClass IS NOT NULL)");
    iFunctions = 0;
    while iFunctions < #functions do
        function = functions[iFunctions];
        startBody := function.StartDefBlock;
        endBody := function.StartDefBlock + function.LengthDefBlock - 1;
        blockId = parser.IndexOf(endBody, parser.CodeBlock);
        if parser.ExtractCode(blockId, parser.CodeBlock).Match("{\s*return\s+\w+\s*;\s*}", new Match()) then
            /* Error formatting */
            success = false;
            line = function.DefLineNumber;
            description = "Getter method should be const.";
            AppendError(fileData, errorList, 28, "Security [R28]", description, line);
        endif
        iFunctions.Increment();
    endwhile
    /*return*/ success;
endfunction