cd ..\..\..\..\tools\
refactor.exe -UTF8 ..\script\plugins\libwordPlg\interpreter\WordMacro.sidl ..\script\plugins\libwordPlg\interpreter\WordXMLDocument.sidl ..\script\plugins\libwordPlg\interpreter\WordXMLNode.sidl ..\script\plugins\libwordPlg\interpreter\WordXMLNodeList.sidl -to interpreter -import ..\script\plugins\libwordPlg\interpreter\interpreter.project.xml -dir ..\script\plugins\libwordPlg\interpreter\src\ -v 5 -export ..\script\plugins\libwordPlg\interpreter\src\exportWordXML.xml

refactor.exe -UTF8 ..\script\plugins\libwordPlg\interpreter\WordXML.sidl -to interpreter -import ..\script\plugins\libwordPlg\interpreter\interpreter.wordxml.xml -dir ..\script\plugins\libwordPlg\interpreter\src\ -v 5 -export ..\script\plugins\libwordPlg\interpreter\src\exportXML.xml
pause