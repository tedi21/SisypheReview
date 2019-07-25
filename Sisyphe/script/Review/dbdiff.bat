@echo off
echo constant sourcePath = ".\sources\"; > Project3.td
echo constant excludePath = "Ex"; >> Project3.td
echo constant docPath = ".\doc\"; >> Project3.td
echo constant projectName = "project"; >> Project3.td
echo constant infoReview = ""; >> Project.td
echo constant jsonPath = ".\Html\client\json\"; >> Project3.td
echo constant referenceDB = ".\reference\cppbase.db"; >> Project3.td
echo include("include.td"); >> Project3.td
echo include("dbdiff.td"); >> Project3.td

..\tdscript.exe Project3.td -module cppBase cppbase.db -v 6

pause
