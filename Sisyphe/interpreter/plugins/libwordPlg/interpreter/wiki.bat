cd ..\..\..\..\tools\
refactor.exe -UTF8 ..\script\plugins\libwordPlg\interpreter\WordMacro.sidl ..\script\plugins\libwordPlg\interpreter\WordXMLDocument.sidl ..\script\plugins\libwordPlg\interpreter\WordXMLNode.sidl ..\script\plugins\libwordPlg\interpreter\WordXMLNodeList.sidl -to MD -import ..\script\plugins\libwordPlg\interpreter\interpreter.project.xml -dir ..\script\plugins\libwordPlg\interpreter\wiki\ -v 5

refactor.exe -UTF8 ..\script\plugins\libwordPlg\interpreter\WordXML.sidl -to MD -import ..\script\plugins\libwordPlg\interpreter\interpreter.wordxml.xml -dir ..\script\plugins\libwordPlg\interpreter\wiki\ -v 5
pause