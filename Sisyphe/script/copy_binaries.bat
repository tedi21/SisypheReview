@echo off
setlocal enabledelayedexpansion
set files[1]=..\..\CodeGeneration\bin_qt\Encoding64\release\Encoding.dll
set files[2]=..\..\CodeGeneration\bin_qt\Xerces64\release\XercesEncoding.dll
set files[3]=..\..\..\..\Environment\mingw64\bin\libgcc_s_seh-1.dll
set files[4]=..\..\..\..\Environment\mingw64\bin\"libstdc++-6.dll"
set files[5]=..\..\..\..\Environment\mingw64\bin\libwinpthread-1.dll
set files[6]=..\..\..\..\Libraries\boost_1_66_0\stage\lib64\libboost_filesystem-mgw73-mt-x64-1_66.dll
set files[7]=..\..\..\..\Libraries\boost_1_66_0\stage\lib64\libboost_system-mgw73-mt-x64-1_66.dll
set files[8]=..\..\..\..\Libraries\boost_1_66_0\stage\lib64\libboost_regex-mgw73-mt-x64-1_66.dll
set files[9]=..\..\..\..\Libraries\boost_1_66_0\stage\lib64\libboost_date_time-mgw73-mt-x64-1_66.dll
set files[10]=..\..\..\..\Libraries\log4cpp\lib64\liblog4cpp-5.dll
set files[11]=..\..\..\..\Libraries\xerces-c-3.2.1\lib64\libxerces-c-3-2.dll
set files[12]=..\..\..\..\Libraries\xalan-c-1.11\c\lib64\libxalan-c1_11_0.dll
set files[13]=..\..\..\..\Libraries\xalan-c-1.11\c\lib64\libxalanMsg1_11_0.dll
set files[14]=..\..\..\..\Environment\mingw64\bin\libicuuc58.dll
set files[15]=..\..\..\..\Environment\mingw64\bin\libicudt58.dll
set files[16]=..\cppbase\bin64\release\cppbase.dll
set files[17]=..\libword\bin64\release\libword.dll
set files[18]=..\interpreter\bin\cppbasePlg64\release\cppBasePlg.dll
set files[19]=..\interpreter\bin\libDebugPlg64\release\libDebugPlg.dll
set files[20]=..\interpreter\bin\libDiff64\release\libDiffPlg.dll
set files[21]=..\interpreter\bin\libWordPlg64\release\libWordPlg.dll
set files[22]=..\interpreter\bin\libPdbPlg64\release\libPdbPlg.dll
set files[23]=..\interpreter\bin\libWebPlg64\release\libWebPlg.dll
set files[24]=..\interpreter\bin\libParsePlg64\release\libParsePlg.dll
set files[25]=..\interpreter\bin\Plugin64\release\Plugin.dll
set files[26]=..\interpreter\bin\script64\release\script.exe
set len=26

set destination=.\
del tdscript.exe

for /l %%n in (1,1,%len%) do (

    set file=!files[%%n]!
    for %%i in ("!file!") do (
        set filename=%%~ni%%~xi
        set line=!filename!............................................................
        set line=!line:~0,60!
        copy !file! %destination%\!filename! > nul
        if errorlevel 1 (
            echo !line![NOK]
            echo Not found : !file!
        ) else (
            echo !line![OK]
        )
    )
)

rename script.exe tdscript.exe

pause