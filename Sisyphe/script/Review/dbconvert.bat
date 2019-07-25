@echo off
echo constant jsonPath = ".\Html\client\json\"; > Project2.td
echo include("DBConvert.td"); >> Project2.td

..\tdscript.exe Project2.td -module cppBase cppbase.db -v 6

pause
