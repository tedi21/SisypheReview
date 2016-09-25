cd ..\..\..\..\tools\
refactor.exe -UTF8 ..\interpreter\plugins\libPdbPlg\interpreter\interpreter.project.cfg -v 5 -export ..\interpreter\plugins\libPdbPlg\interpreter\interpreter.project.xml
refactor.exe -UTF8 ..\interpreter\plugins\libPdbPlg\interpreter\PdbParser.sidl -to interpreter -import ..\interpreter\plugins\libPdbPlg\interpreter\interpreter.project.xml -dir ..\interpreter\plugins\libPdbPlg\interpreter\src\ -v 5 -export ..\interpreter\plugins\libPdbPlg\interpreter\src\exportPDB.xml
pause