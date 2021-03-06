constant ENABLED_RULES = new Structure();

function FillBlameInfo(error)
endfunction

include("Pattern.td");
include("DataBase.td");
include("Parse.td");
include("FileData.td");
include("Report.td");
include("Rules.td");

/* Désactivation règle 4 : Français */
constant:ENABLED_RULES.Rule4  = false;

/* Démarrage de la mise à jour de la Base de données */
print("Start parsing");
constant:DB_ACCESS.connection.StartTransaction();

/* Création d'un faux fichier */
iFile = 0;
while iFile < #FILES do
    file = FILES[iFile];
    content = file.Text;
    /* 1 : header file */
    /* 2 : source file */
    nFileType = file.Type; 
    if nFileType == 1 then
        fileName = "file" & iFile & ".h";
    else
        fileName = "file" & iFile & ".cpp";
    endif

    /* Analyse du contenu */
    parser = new CPPParser();
    parser.Parse(content);

    /* Suppression du faux fichier si le fichier existe déjà */
    DeleteCppFile(fileName);
    /* Analyse des informations du fichier */
    sourceFile = new CppFile();
    sourceFile.TextFile = new TextFile();

    sourceFile.Path = fileName;
    sourceFile.Hash = 1;
    sourceFile.Analyzed = constant:DB_FALSE;
    sourceFile.Name = fileName;
    sourceFile.CppFileType = constant:DB_ACCESS.cppFileType.GetOneCppFileType(nFileType);
    sourceFile.TextFile.Content := "file not available.";
    sourceFile.LinesCount := parser.Size(parser.Lines);
        
    /* Ajout du fichier dans la base de données */
    constant:DB_ACCESS.textFile.InsertTextFile(sourceFile.TextFile);
    constant:DB_ACCESS.cppFile.InsertCppFile(sourceFile);

    /* Analyse des éléments */
    index = parser.Size(parser.Composition) - 1;
    while index >= 0 && !IsError() do
        type = parser.Type(index, parser.Composition);
        if type == parser.Class || type == parser.Struct then
            ParseClass(sourceFile, "NONE", parser, index, type);
        endif
        if type == parser.Enum then
            ParseEnum(sourceFile, "NONE", parser, index);
        endif
        if type == parser.Function then
            ParseMethod(sourceFile, "NONE", parser, index);
        endif
        if type == parser.Attribute then
            sourceConstant = ParseConstant(sourceFile, parser, index);
            if sourceConstant.Identifier == -1 then
                ParseGlobalVariable(sourceFile, parser, index);
            endif
        endif
        index.Decrement();
    endwhile

    /* Analyse des directives préprocesseurs */
    index = parser.Size(parser.Preprocessors) - 1;
    while index >= 0 && !IsError() do
        directive = parser.Name(index, parser.Preprocessors);
        if directive == "include" then
            ParseInclude(sourceFile, parser, index);
        endif
        if directive == "define" then
            ParseMacro(sourceFile, parser, index);
        endif
        index.Decrement();
    endwhile
    file.Parser = parser;
    file.SourceFile = sourceFile;
    iFile.Increment();
endwhile

/* Mise à jour de la base de données */
if IsError() then
    /* Annule transaction */
    constant:DB_ACCESS.connection.Rollback();
    print("Parsing failed");
else
    /* Commit transaction */
    constant:DB_ACCESS.connection.Commit();
    print("Parsing succeded");
endif

/* Vérification des règles */
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
rulesCollection[28] = function:Rule29;
rulesCollection[29] = function:Rule30;
rulesCollection[30] = function:Rule31;
rulesCollection[31] = function:Rule32;
rulesCollection[32] = function:Rule33;
rulesCollection[33] = function:Rule34;
rulesCollection[34] = function:Rule35;
rulesCollection[35] = function:Rule36;
rulesCollection[36] = function:Rule37;
rulesCollection[37] = function:Rule38;
rulesCollection[38] = function:Rule39;
rulesCollection[39] = function:Rule40;
rulesCollection[40] = function:Rule41;
rulesCollection[41] = function:Rule42;
rulesCollection[42] = function:Rule43;
rulesCollection[43] = function:Rule44;
rulesCollection[44] = function:Rule45;
rulesCollection[45] = function:Rule46;
rulesCollection[46] = function:Rule47;
rulesCollection[47] = function:Rule48;
rulesCollection[48] = function:Rule49;
rulesCollection[49] = function:Rule50;
rulesCollection[50] = function:Rule51;
rulesCollection[51] = function:Rule52;
rulesCollection[52] = function:Rule53;
rulesCollection[53] = function:Rule54;
rulesCollection[54] = function:Rule55;
rulesCollection[55] = function:Rule56;
rulesCollection[56] = function:Rule57;
rulesCollection[57] = function:Rule58;
rulesCollection[58] = function:Rule59;
rulesCollection[59] = function:Rule60;
rulesCollection[60] = function:Rule61;
rulesCollection[61] = function:Rule62;
rulesCollection[62] = function:Rule63;
rulesCollection[63] = function:Rule64;
rulesCollection[64] = function:Rule65;
rulesCollection[65] = function:Rule66;

iFile = 0;
RESULT = new String(1024);
while iFile < #FILES do
    file = FILES[iFile];
    fileData = new Structure();
    fileData.Properties = file.SourceFile;
    fileData.Identifier = fileData.Properties.Identifier;
    fileData.Name = fileData.Properties.Name;
    fileData.Parser = file.Parser;
    fileData.Text = file.Text;
    fileData.SourceCode = fileData.Parser.SourceCode;

    irule = 0;
    /* Check each rule */
    while irule < #rulesCollection do

        if EnabledRule(irule) then
        
            print("RULE " & irule+1);
            errorList = new Array();
            params = new Array();
            params[0] = fileData;
            params[1] = errorList;
            success = rulesCollection[irule].Call(params);
            print("  ==> " & success);

            iError = 0;
            while iError < #errorList do
                RESULT = RESULT & ("" & iFile & Tab & errorList[iError].StartBlock & Tab & errorList[iError].LineNumber & Tab & errorList[iError].Category & Tab & errorList[iError].Description & Lf);
                iError.Increment();
            endwhile
        endif
        irule.Increment();
    endwhile
    iFile.Increment();
endwhile

