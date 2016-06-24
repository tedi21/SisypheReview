cd ..\..\..\..\tools\
refactor.exe -UTF8 ..\script\plugins\libPdbPlg\interpreter\interpreter.project.cfg -v 5 -export ..\script\plugins\libPdbPlg\interpreter\interpreter.project.xml
refactor.exe -UTF8 ..\script\plugins\libPdbPlg\interpreter\PdbParser.sidl -to interpreter -import ..\script\plugins\libPdbPlg\interpreter\interpreter.project.xml -dir ..\script\plugins\libPdbPlg\interpreter\src\ -v 5 -export ..\script\plugins\libPdbPlg\interpreter\src\exportPDB.xml
pause