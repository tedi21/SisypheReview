/* Index des valeurs pour le pattern Enum */
constant INDEX_ENUM_NAME = 2;

/* Index des valeurs pour le pattern Enum constant */
constant INDEX_ENUM_CONSTANT_NAME = 1;
constant INDEX_ENUM_CONSTANT_VALUE = 3;

/* Index des valeurs pour le pattern Class */
constant INDEX_CLASS_STRUCT = 4;
constant INDEX_CLASS_NAME = 8;
constant INDEX_CLASS_INHERITANCE = 14;
constant INDEX_CLASS_TEMPLATE = 1;

/* Index des valeurs pour le pattern Method */
constant INDEX_METHOD_TEMPLATE = 1;
constant INDEX_METHOD_STATIC = 5;
constant INDEX_METHOD_STATIC_2 = 12;
constant INDEX_METHOD_VIRTUAL = 14;
constant INDEX_METHOD_INLINE = 16;
constant INDEX_METHOD_CONSTEXPR = 17;
constant INDEX_METHOD_RETURN = 18;
constant INDEX_METHOD_CLASS_NAME = 35;
constant INDEX_METHOD_NAME = 39;
constant INDEX_METHOD_PARAMETERS = 44;
constant INDEX_METHOD_CONST = 114;
constant INDEX_METHOD_OVERRIDE = 115;
constant INDEX_METHOD_FINAL = 116;
constant INDEX_METHOD_NOEXCEPT = 117;
constant INDEX_METHOD_VIRTUAL_PURE = 118;

/* Index des valeurs pour le pattern Operator */
constant INDEX_OPERATOR_TEMPLATE = 1;
constant INDEX_OPERATOR_VIRTUAL = 7;
constant INDEX_OPERATOR_INLINE = 9;
constant INDEX_OPERATOR_CONSTEXPR = 10;
constant INDEX_OPERATOR_RETURN = 11;
constant INDEX_OPERATOR_CLASS_NAME = 28;
constant INDEX_OPERATOR_NAME = 32;
constant INDEX_OPERATOR_PARAMETERS = 33;
constant INDEX_OPERATOR_CONST = 103;
constant INDEX_OPERATOR_OVERRIDE = 104;
constant INDEX_OPERATOR_FINAL = 105;
constant INDEX_OPERATOR_NOEXCEPT = 106;
constant INDEX_OPERATOR_VIRTUAL_PURE = 109;

/* Index des valeurs pour le pattern Constructor */
constant INDEX_CONSTRUCTOR_TEMPLATE = 1;
constant INDEX_CONSTRUCTOR_INLINE = 4;
constant INDEX_CONSTRUCTOR_CONSTEXPR = 5;
constant INDEX_CONSTRUCTOR_CLASS_NAME = 7;
constant INDEX_CONSTRUCTOR_NAME = 11;
constant INDEX_CONSTRUCTOR_PARAMETERS = 16;
constant INDEX_CONSTRUCTOR_NOEXCEPT = 85;
constant INDEX_CONSTRUCTOR_IN_INLINE = 7;
constant INDEX_CONSTRUCTOR_IN_CONSTEXPR = 8;
constant INDEX_CONSTRUCTOR_IN_NAME = 10;
constant INDEX_CONSTRUCTOR_IN_PARAMETERS = 15;
constant INDEX_CONSTRUCTOR_IN_NOEXCEPT = 84;

/* Index des valeurs pour le pattern Destructor */
constant INDEX_DESTRUCTOR_INLINE = 4;
constant INDEX_DESTRUCTOR_CONSTEXPR = 5;
constant INDEX_DESTRUCTOR_CLASS_NAME = 7;
constant INDEX_DESTRUCTOR_NAME = 11;
constant INDEX_DESTRUCTOR_NOEXCEPT = 14;
constant INDEX_DESTRUCTOR_IN_VIRTUAL = 4;
constant INDEX_DESTRUCTOR_IN_INLINE = 5;
constant INDEX_DESTRUCTOR_IN_CONSTEXPR = 6;
constant INDEX_DESTRUCTOR_IN_NAME = 7;
constant INDEX_DESTRUCTOR_IN_NOEXCEPT = 10;

/* Index des valeurs pour le pattern Parameter */
constant INDEX_PARAMETER_TYPE = 1;
constant INDEX_PARAMETER_CONST = 2;
constant INDEX_PARAMETER_NAME = 18;
constant INDEX_PARAMETER_TYPE_2 = 19;
constant INDEX_PARAMETER_DEFAULT_VALUE = 22;

/* Index des valeurs pour le pattern Inheritance */
constant INDEX_INHERITANCE_ACCESS = 2;
constant INDEX_INHERITANCE_CLASS_INSTANCE = 4;
constant INDEX_INHERITANCE_CLASS_NAME = 9;

/* Index des valeurs pour le pattern Include */
constant INDEX_INCLUDE_FILENAME = 2;

/* Index des valeurs pour le pattern Attributes */
constant INDEX_ATTRIBUTES_STATIC = 4;
constant INDEX_ATTRIBUTES_CONSTEXPR = 5;
constant INDEX_ATTRIBUTES_MUTABLE = 6;
constant INDEX_ATTRIBUTES_TYPE = 7;
constant INDEX_ATTRIBUTES_CONST = 8;
constant INDEX_ATTRIBUTES_ENUM = 21;

/* Index des valeurs pour le pattern AttributeName */
constant INDEX_ATTRIBUTE_NAME_TYPE = 1;
constant INDEX_ATTRIBUTE_NAME = 3;
constant INDEX_ATTRIBUTE_NAME_TYPE_2 = 4;

/* Index des valeurs pour le pattern ConstantAttribute */
constant INDEX_CONSTANT_ATTRIBUTE_TYPE = 4;
constant INDEX_CONSTANT_ATTRIBUTE_CLASS_NAME = 20;
constant INDEX_CONSTANT_ATTRIBUTE_NAME = 24;
constant INDEX_CONSTANT_ATTRIBUTE_TYPE_2 = 25;
constant INDEX_CONSTANT_ATTRIBUTE_VALUE = 28;

/* Index des valeurs pour le pattern Macro */
constant INDEX_MACRO_NAME = 1;
constant INDEX_MACRO_VALUE = 2;

/* Index des valeurs pour le pattern Variables */
constant INDEX_VARIABLES_STATIC = 5;
constant INDEX_VARIABLES_CONSTEXPR = 6;
constant INDEX_VARIABLES_MUTABLE = 7;
constant INDEX_VARIABLES_TYPE = 9;
constant INDEX_VARIABLES_CONST = 10;
constant INDEX_VARIABLES_ENUM = 23;

/* Index des valeurs pour le pattern VariableName */
constant INDEX_VARIABLE_NAME = 3;
constant INDEX_VARIABLE_NAME_TYPE = 1;
constant INDEX_VARIABLE_NAME_TYPE_2 = 4;

function EscapeRegex(str)
  matches = new Match();
  result = "";
  start = 0;
  end = #str;
  remainder = 0;
  pattern = "[-[\]{}()*+?.,\\/^$|#\s]";
  while str.Search(start, end, pattern, matches, start) do
    result = result & matches.Prefix & "\" & matches.String;
    remainder = start;
  endwhile
  result = result & str.SubString(remainder, end - remainder);
  /*return*/ result;
endfunction

function Pattern_String()
      "L?(?<!')" & DblQuotes & "([^\\" & DblQuotes & "]|\\\\|\\\w|\\'|\\" & DblQuotes & ")*" & DblQuotes;
endfunction

function Pattern_Char()
      "L?'([^\\']|\\\\|\\\w|\\'|\\" & DblQuotes & "){1,2}'";
endfunction

function Pattern_Boolean()
      "true|false";
endfunction

function Pattern_Int()
      "(0[Xx]|0)?-?\d+(LL|UL|L|ll|ul|l)?";
endfunction

function Pattern_PointerNull()
      "NULL|nullptr";
endfunction

function Pattern_Double()
      "-?\d*\.\d+(F|L|f|l)?";
endfunction

function Pattern_ConstantArray()
    "\{(?<C>([^\{\}" & DblQuotes & "']|" & Pattern_String() & "|" & Pattern_Char() & "|\{(?&C)\})*)\}";
endfunction

function Pattern_ConstantPrimitive()
    "(\<(" & Pattern_PointerNull() & "|"
    & Pattern_Boolean() & ")\>|"
    & Pattern_ConstantArray() & "|"
    & Pattern_String() & "|"
    & Pattern_Char() & "|"
    & Pattern_Double() & "|"
    & Pattern_Int() & ")";
endfunction

function Reserved_Keyword()
      "(?!\<(this|new|delete|const|constexpr|static|mutable|volatile|virtual|inline|explicit|public|protected|private|friend|struct|union|enum|class|template|typename|namespace|typedef|if|else|switch|case|break|default|while|for|try|catch|throw|return|operator|goto|do|decltype|override|final|noexcept|register|using|__raise|__asm__|__volatile__|"
    & Pattern_Boolean() & "|"
    & Pattern_PointerNull()
    & ")\>)";
endfunction

function Pattern_Identifier()
    Reserved_Keyword() & "\<[A-Za-z_]\w*\>";
endfunction

function Pattern_TemplateDeclaration()
    "(?<!<)<(?!<)(?<TDC>([^<>;\{#&|-]|-(?!>)|&(?!&)|<(?&TDC)>)*)>";
endfunction

function Pattern_TemplateDefinition()
    "(?<!<)<(?!<)(?<TDF>([^<>;\{#&|-]|-(?!>)|&(?!&)|<(?&TDF)>)*)>";
endfunction

function Pattern_TypeDeclaration() 
      "(const[[:space:]]+)?"
    & "(unsigned[[:space:]]+)?"
    & "(typename[[:space:]]+)?"
    & Pattern_Identifier() & "[[:space:]]*"
    & "(" & Pattern_TemplateDefinition() & "[[:space:]]*)?"
    & "(::(template[[:space:]]+)?" & Pattern_Identifier() & "[[:space:]]*(" & Pattern_TemplateDefinition() & "[[:space:]]*)?)*";
endfunction

function Pattern_TypeModifier()
      "(const(?!\w)\s*|&\s*|\*\s*)*";
endfunction

function Pattern_Type() 
      Pattern_TypeDeclaration()
    & Pattern_TypeModifier();
endfunction

function Pattern_IsConst()
  "^(.*\<const\>.*(?<![\*\]])|.+\*\s*\<const\>)$";
endfunction

function Pattern_IsReference()
  "^.+&$";
endfunction

function Pattern_ClassStruct(keyword)
      "^[[:blank:]]*"
    & "(template[[:space:]]*" & Pattern_TemplateDeclaration() & "[[:space:]]*)?"
    & "(" & keyword & ")[[:space:]]*"
    & "(\<\w+\>([[:blank:]]*\(+[^)]*\)+)?[[:space:]]*(?!\<final\>)(?=\<\w+\>))?"
    & "((\<\w*\>)[[:space:]]*"
    & "(" & Pattern_TemplateDefinition() & "[[:space:]]*)?)"
    & "(\<final\>[[:space:]]*)?"
    & "(\{|:([^;\{]+)\{)";
endfunction

function Pattern_Class()
    Pattern_ClassStruct("class");
endfunction

function Pattern_Struct()
    Pattern_ClassStruct("struct");
endfunction

function Pattern_InheritanceClass()
    "(\w+\s*(" & Pattern_TemplateDefinition() & ")?\s*::\s*)*(" & Pattern_Identifier() & ")\s*(" & Pattern_TemplateDefinition() & ")?";
endfunction

function Pattern_Inheritance()
    "(\<(public|protected|private)\>\s+)?(\<virtual\>\s+)?(" & Pattern_InheritanceClass() & ")";
endfunction

function Pattern_Enum()
      "^[[:blank:]]*"
    & "\<enum\>[[:space:]]*"
    & "(\<class\>)?[[:space:]]*"
    & "(\<\w*\>)[[:space:]]*"
    & "\{";
endfunction

function Pattern_ConstantEnum()
	  "(\<\w+\>)([[:space:]]*=[[:space:]]*([^,}]+))?";
endfunction

function Pattern_Parenthesis()
      "\((?<P>([^(;)]|\((?&P)\))*)\)";
endfunction

function Pattern_Bracket()
      "\{(?<B>([^{;}]|\{(?&B)\})*)\}";
endfunction

function Pattern_Init()
      "(?>((\[\w*\][[:space:]]*)*)(=(([^,;(){<]+|" & Pattern_TemplateDefinition() & "|" & Pattern_Parenthesis() & "|" & Pattern_Bracket() & "|<)+))?(" & Pattern_Parenthesis() & "[[:space:]]*)?)";
endfunction

function Pattern_VariableName()
      "(" & Pattern_TypeModifier() & ")(\<[A-Za-z_]\w*\>)[[:space:]]*" & Pattern_Init();
endfunction

function Pattern_Variables()
      "^[[:blank:]]*"
    & "(template[[:space:]]*" & Pattern_TemplateDeclaration() & "[[:space:]]*){0,1}"
    & "(extern[[:space:]]+)?(static[[:space:]]+)?(constexpr[[:space:]]+)?(mutable[[:space:]]+)?(for[[:space:]]*\([[:space:]]*)?(" 
    & Pattern_TypeDeclaration() & ")(" 
    & Pattern_VariableName() & "(,[[:space:]]*" 
    & Pattern_VariableName() & ")*);";
endfunction

function Pattern_Parameter()
      "(" & Pattern_Type() & "(\.\.\.[[:space:]]*)?)((\<[A-Za-z_]\w*\>)[[:space:]]*)?" & Pattern_Init();
endfunction

function Pattern_Parameters()
      "(" & Pattern_Parameter()
    & "(,[[:space:]]*(\.\.\.|" & Pattern_Parameter() & "))*)?";
endfunction

function Pattern_AttributeName()
      "(" & Pattern_TypeModifier() & ")(\<[A-Za-z_]\w*\>)[[:space:]]*((\[\w*\][[:space:]]*)*)";
endfunction

function Pattern_Attributes()
      "^[[:blank:]]*"
    & "(template[[:space:]]*" & Pattern_TemplateDeclaration() & "[[:space:]]*){0,1}"
    & "(static[[:space:]]+)?(constexpr[[:space:]]+)?(mutable[[:space:]]+)?(" 
    & Pattern_TypeDeclaration() & ")(" 
    & Pattern_AttributeName() & "(,[[:space:]]*" 
    & Pattern_AttributeName() & ")*)[;=]";
endfunction

function Pattern_ConstantAttribute()
      "^[[:blank:]]*"
    & "(template[[:space:]]*" & Pattern_TemplateDeclaration() & "[[:space:]]*){0,2}"
    & "(" & Pattern_Type() & ")"
    & "((\<[A-Za-z_]\w*\>)[[:space:]]*"
    & "(" & Pattern_TemplateDefinition() & "[[:space:]]*)?)"
    & "::[[:space:]]*(\<\w+\>)[[:space:]]*" & Pattern_Init() & ";";
endfunction

function Pattern_Method()
      "^[[:blank:]]*"
    & "(template[[:space:]]*" & Pattern_TemplateDeclaration() & "[[:space:]]*){0,2}"
    & "((static[[:space:]]+)?((__declspec[[:blank:]]*\([[:blank:]]*(dllimport|dllexport)[[:blank:]]*\)|[A-Z][A-Z0-9_]*_API)[[:space:]]+)?"
    & "|((__declspec[[:blank:]]*\([[:blank:]]*(dllimport|dllexport)[[:blank:]]*\)|[A-Z][A-Z0-9_]*_API)[[:space:]]+)?(static[[:space:]]+)?)"
    & "(afx_msg[[:space:]]+)?"
    & "(virtual[[:space:]]+)?"
    & "(friend[[:space:]]+)?"
    & "(inline[[:space:]]+)?"
    & "(constexpr[[:space:]]+)?"
    & "(" & Pattern_Type() & ")"
    & "(((\<\w+\>)[[:space:]]*"
    & "(" & Pattern_TemplateDefinition() & "[[:space:]]*)?)"
    & "::[[:space:]]*)?"
    & "((\<\w+\>)[[:space:]]*"
    & "(" & Pattern_TemplateDefinition() & "[[:space:]]*)?)"
    & "\([[:space:]]*"
    & "(" & Pattern_Parameters() & ")"
    & "\)([[:space:]]+((const)|(override)|(final)|(noexcept)))*([[:space:]]*=[[:space:]]*0)?"
    & "[[:space:]]*[;\{]";
endfunction

function Pattern_Operator()
      "^[[:blank:]]*"
    & "(template[[:space:]]*" & Pattern_TemplateDeclaration() & "[[:space:]]*){0,2}"
    & "((__declspec[[:blank:]]*\([[:blank:]]*(dllimport|dllexport)[[:blank:]]*\)|[A-Z][A-Z0-9_]*_API)[[:space:]]+)?"
    & "(virtual[[:space:]]+)?"
    & "(friend[[:space:]]+)?"
    & "(inline[[:space:]]+)?"
    & "(constexpr[[:space:]]+)?"
    & "(" & Pattern_Type() & ")?"
    & "(((\<\w+\>)[[:space:]]*"
    & "(" & Pattern_TemplateDefinition() & "[[:space:]]*)?)"
    & "::[[:space:]]*)?"
    & "(operator[[:space:]]*[^(]+)"
    & "\([[:space:]]*"
    & "(" & Pattern_Parameters() & ")"
    & "\)([[:space:]]+((const)|(override)|(final)|(noexcept)))*([[:space:]]*=[[:space:]]*((0)|delete))?"
    & "[[:space:]]*[;\{]";
endfunction

function Pattern_Constructor(className)
      "^[[:blank:]]*"
    & "(template[[:space:]]*" & Pattern_TemplateDeclaration() & "[[:space:]]*){0,2}"
    & "((__declspec[[:blank:]]*\([[:blank:]]*(dllimport|dllexport)[[:blank:]]*\)|[A-Z][A-Z0-9_]*_API)[[:space:]]+)?"
    & "(inline[[:space:]]+)?"
    & "(constexpr[[:space:]]+)?"
    & "(explicit[[:space:]]+)?"
    & "((" & EscapeRegex(className) & ")[[:space:]]*"
    & "(" & Pattern_TemplateDefinition() & "[[:space:]]*)?)"
    & "\([[:space:]]*"
    & "(" & Pattern_Parameters() & ")"
    & "\)([[:space:]]+(noexcept))?[^;\{]*[;\{]";
endfunction

function Pattern_Destructor(className)
      "^[[:blank:]]*"
    & "((__declspec[[:blank:]]*\([[:blank:]]*(dllimport|dllexport)[[:blank:]]*\)|[A-Z][A-Z0-9_]*_API)[[:space:]]+)?"
    & "(virtual[[:space:]]+)?"
    & "(inline[[:space:]]+)?"
    & "(constexpr[[:space:]]+)?"
    & "(~" & EscapeRegex(className) & ")[[:space:]]*"
    & "\([[:space:]]*"
    & "(void[[:space:]]*)?"
    & "\)([[:space:]]+(noexcept))?[^;\{]*[;\{]";
endfunction

function Pattern_Constructor_ClassOut(className)
    name1 = "\<\w+\>";
    name2 = "\g7";
    if "" != className then
        name1 = EscapeRegex(className);
        name2 = EscapeRegex(className);
    endif

      "^[[:blank:]]*"
    & "(template[[:space:]]*" & Pattern_TemplateDeclaration() & "[[:space:]]*){0,2}"
    & "(inline[[:space:]]+)?"
    & "(constexpr[[:space:]]+)?"
    & "((" & name1 & ")[[:space:]]*"
    & "(" & Pattern_TemplateDefinition() & "[[:space:]]*)?)"
    & "::[[:space:]]*"
    & "((" & name2 & ")[[:space:]]*"
    & "(" & Pattern_TemplateDefinition() & "[[:space:]]*)?)"
    & "\([[:space:]]*"
    & "(" & Pattern_Parameters() & ")"
    & "\)([[:space:]]+(noexcept))?[[:space:]]*(\{|:[^;\{]+\{)";
endfunction

function Pattern_Destructor_ClassOut(className)
    name1 = "\<\w+\>";
    name2 = "\g7";
    if "" != className then
        name1 = EscapeRegex(className);
        name2 = EscapeRegex(className);
    endif

      "^[[:blank:]]*"
    & "(template[[:space:]]*" & Pattern_TemplateDeclaration() & "[[:space:]]*){0,1}"
    & "(inline[[:space:]]+)?"
    & "(constexpr[[:space:]]+)?"
    & "((" & name1 & ")[[:space:]]*"
    & "(" & Pattern_TemplateDefinition() & "[[:space:]]*)?)"
    & "::[[:space:]]*"
    & "(~" & name2 & ")[[:space:]]*"
    & "\([[:space:]]*"
    & "(void[[:space:]]*)?"
    & "\)([[:space:]]+(noexcept))?[[:space:]]*\{";
endfunction

function Pattern_Lambda()
      "(^|\W)[[:blank:]]*"
    & "\[[^\]]*\]"
    & "\([[:space:]]*"
    & "(" & Pattern_Parameters() & ")"
    & "\)"
    & "[[:space:]]*$";
endfunction

function Pattern_Comment_C()
      "(?<!/)/\*([^*]|(\*+[^/]))*\*+/";
endfunction

function Pattern_Comment_CPP()
      "//+[^\r\n]*";
endfunction

function Pattern_French()
      "\<([Ll][Ee]|"
	  & "[Ll][Aa]|"
	  & "[Ll][Ee][Ss]|"
	  & "à|"
	  & "[Aa][Uu]|"
	  & "[Dd][Uu]|"
	  & "[Aa][Uu][Xx]|"
	  & "[Dd][Ee]|"
	  & "[Dd][Ee][Ss]|"
	  & "[Uu][Nn]|"
	  & "[Uu][Nn][Ee]|"
	  & "[Cc][Ee]|"
	  & "[Cc]ette|"
	  & "[Cc]'|"
	  & "[Cc]ela|"
	  & "[Ee]n|"
	  & "[Cc]lasse|"
	  & "[Ff]onction|"
	  & "[Mm]éthode|"
	  & "[Cc]onstructeur|"
	  & "[Dd]estructeur|"
	  & "[Oo]pérateur|"
	  & "[Cc]as)\>|"
	  & "\s[Ll]'|"
	  & "\s[Dd]'";
endfunction

function Pattern_Macro()
      "^[[:blank:]]*#[[:blank:]]*define[[:blank:]]*(\<\w+\>)([^\r\n]+)";
endfunction

function Pattern_Include()
      "^[[:blank:]]*#[[:blank:]]*include[[:blank:]]*(" & DblQuotes & "|<)([^" & DblQuotes & ">]+)(" & DblQuotes & "|>)";
endfunction

function Pattern_InsideCPPComment()
  "(//+[^\r\n]*?(?=[^\r\n]*[\r\n]))";
endfunction

function Pattern_InsideCComment()
  "((?<!/)/\*([^*]|(\*+[^/]))*?(?=([^*]|(\*+[^/]))*\*+/))";
endfunction

function Pattern_InsideString()
  "(\n[^" & DblQuotes & "\r\n]+?(" & Pattern_String() & "[^" & DblQuotes & "\r\n]+?)*?" & DblQuotes & "[^" & DblQuotes & "\r\n]*?(?=[^" & DblQuotes & "\r\n]*" & DblQuotes & "))";
endfunction
