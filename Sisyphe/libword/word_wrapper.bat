cd ..\tools\
refactor.exe -to word ..\libword\word.sidl ..\libword\office.sidl -import ..\libword\word_wrapper.xml -dir ..\libword\src\ -v 5 -export ..\libword\log\export.xml
pause