cd ..\..\..\..\tools\
refactor.exe -UTF8 ..\Interpreter\plugins\libDebugPlg\interpreter\interpreter.project.cfg -v 5 -export ..\Interpreter\plugins\libDebugPlg\interpreter\interpreter.project.xml
refactor.exe -UTF8 ..\Interpreter\plugins\libDebugPlg\interpreter\DebugEngine.sidl -to interpreter -import ..\Interpreter\plugins\libDebugPlg\interpreter\interpreter.project.xml -dir ..\Interpreter\plugins\libDebugPlg\interpreter\src\ -v 5 -export ..\Interpreter\plugins\libDebugPlg\interpreter\src\exportDEBUG.xml
pause