cd ..\..\..\..\tools\
refactor.exe -UTF8 ..\script\plugins\libDebugPlg\interpreter\interpreter.project.cfg -v 5 -export ..\script\plugins\libDebugPlg\interpreter\interpreter.project.xml
refactor.exe -UTF8 ..\script\plugins\libDebugPlg\interpreter\DebugEngine.sidl -to interpreter -import ..\script\plugins\libDebugPlg\interpreter\interpreter.project.xml -dir ..\script\plugins\libDebugPlg\interpreter\src\ -v 5 -export ..\script\plugins\libDebugPlg\interpreter\src\exportDEBUG.xml
pause