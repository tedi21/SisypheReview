cd ..\..\..\..\tools\
refactor.exe -UTF8 ..\interpreter\plugins\libwordPlg\interpreter\WordMacro.sidl ..\interpreter\plugins\libwordPlg\interpreter\WordXMLDocument.sidl ..\interpreter\plugins\libwordPlg\interpreter\WordXMLNode.sidl ..\interpreter\plugins\libwordPlg\interpreter\WordXMLNodeList.sidl -to MD -import ..\interpreter\plugins\libwordPlg\interpreter\interpreter.project.xml -dir ..\interpreter\plugins\libwordPlg\interpreter\wiki\ -v 5

refactor.exe -UTF8 ..\interpreter\plugins\libwordPlg\interpreter\WordXML.sidl -to MD -import ..\interpreter\plugins\libwordPlg\interpreter\interpreter.wordxml.xml -dir ..\interpreter\plugins\libwordPlg\interpreter\wiki\ -v 5
pause