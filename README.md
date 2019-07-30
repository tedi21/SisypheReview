# SisypheReview
C++ code review 

## Installation prerequisites
 * Optional [GraphViz] (http://www.graphviz.org/Download.php "GraphViz") 
 
## Download
Windows Binaries are available [here](https://github.com/tedi21/SisypheReview/blob/master/sisyphe.7z "SisypheReview").

## Start
Modify the script .\Review\processes.bat with the source folder.
Run the script.

Run .\Review\Html\client\sisyphe.html to visualize the results.
![Sisyphe screenshot](/screen.png "Sisyphe screenshot")

## Adding Coding Rules
Edit the file Review\CodingRules\CppCustom\rules.td.
Create a new function checking the new rule. The function must have two parameters :
 * fileData Data related to the source file
 * errorList List of errors, append an error to the list if the new rule is violated.
```
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
```

Once your new rule is written, you can add it in the function ReviewCode located in the file Review\CodingRules\CppCustom\review.td
```
rulesCollection[27] = function:Rule28;
```

If you want to disable a rule, edit the file Review\main.td and write :
```
constant:ENABLED_RULES.Rule28 = false;
```

## Customize the word report
Open the xml model located in Review\CodingRules\CppCustom\Models\ModeleRevue_Custom.xml with Microsoft Word.
Change the document and save it in XML Word 2003 format.
You can modify the report programmatically by editing the file Review\CodingRules\CppCustom\review.td. The functions InitDoc, WriteDoc and CloseDoc are use to modify the xml word report.

## Wiki
[link](https://github.com/tedi21/SisypheReview/blob/master/Sisyphe\script\Help\wiki\TDScript "Wiki")

[![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/tedi21/SisypheReview/master)