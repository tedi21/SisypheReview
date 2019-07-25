@echo off
echo constant sourcePath = ".\sources\"; > Project.td
echo constant excludePath = "Ex"; >> Project.td
echo constant docPath = ".\doc\"; >> Project.td
echo constant projectName = "project"; >> Project.td
echo constant infoReview = ""; >> Project.td
echo constant forceClean = true; >> Project.td
echo include("include.td"); >> Project.td
echo include("Main.td"); >> Project.td

..\tdscript.exe Project.td -module cppBase cppbase.db -v 6 > log.txt

pause
