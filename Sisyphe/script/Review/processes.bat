@echo off
echo constant sourcePath = ".\sources\"; > Project.td
echo constant excludePath = "Ex"; >> Project.td
echo constant docPath = ".\doc\"; >> Project.td
echo constant projectName = "project"; >> Project.td
echo constant infoReview = ""; >> Project.td
echo constant jsonPath = ".\HTML\client\json\"; >> Project.td
echo constant dbFile = "cppbase.db"; >> Project.td
echo constant referenceDB = ".\reference\cppbase.db"; >> Project.td
echo constant forceClean = true; >> Project.td

echo include("include.td"); >> Project.td
echo include("Main.td"); >> Project.td
echo include("DBConvert.td"); >> Project.td
echo include("dbdiff.td"); >> Project.td

..\tdscript.exe Project.td -module cppBase cppbase.db -v 6 > log.txt

pause