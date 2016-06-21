SET ROOT=..\cppbase
SET SRC=%ROOT%\src
SET CONFIG=%SRC%\config
SET INTERP=%SRC%\interpreter
SET WIKI=%SRC%\wiki

cd ..\tools
sqlite3.exe %ROOT%\cppbase.db < %ROOT%\cppbase.sql

mkdir %SRC%
refactor.exe -to cpp %ROOT%\cppbase.sql -import %ROOT%\cppbase.project.xml -dir %SRC%\ -v 5 -export %ROOT%\log\export.xml

mkdir %CONFIG%
copy /Y %SRC%\config.hpp %CONFIG%\config.hpp
del /F %SRC%\config.hpp

mkdir %INTERP%
copy /Y %SRC%\*Interpreter* %INTERP%\*Interpreter*
del /F %SRC%\*Interpreter*

mkdir %WIKI%
copy /Y %SRC%\*.md %WIKI%\*.md
del /F %SRC%\*.md

pause