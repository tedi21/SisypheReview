@echo off
setlocal enabledelayedexpansion
set files[1]=..\..\CodeGeneration\bin_qt\PackCFG64\release\PackCFG.dll
set files[2]=..\..\CodeGeneration\bin_qt\PackCPP64\release\PackCPP.dll
set files[3]=..\..\CodeGeneration\bin_qt\PackIDL64\release\PackIDL.dll
set files[4]=..\..\CodeGeneration\bin_qt\PackINTERPRETER64\release\PackINTERPRETER.dll
set files[5]=..\..\CodeGeneration\bin_qt\PackMD64\release\PackMD.dll
set files[6]=..\..\CodeGeneration\bin_qt\PackSQL64\release\PackSQL.dll
set files[7]=..\..\CodeGeneration\bin_qt\PackSQL64\release\PackSQL.dll
set files[8]=..\..\CodeGeneration\bin_qt\PackWORD64\release\PackWORD.dll
set files[9]=..\..\CodeGeneration\bin_qt\Core64\release\Core.dll
set files[10]=..\..\CodeGeneration\bin_qt\Encoding64\release\Encoding.dll
set files[11]=..\..\CodeGeneration\bin_qt\Pack64\release\Pack.dll
set files[12]=..\..\CodeGeneration\bin_qt\Refactor64\release\Refactor.exe
set files[13]=..\..\CodeGeneration\bin_qt\Xerces64\release\XercesEncoding.dll
set files[14]=..\..\..\..\Environment\mingw64\bin\libgcc_s_seh-1.dll
set files[15]=..\..\..\..\Environment\mingw64\bin\"libstdc++-6.dll"
set files[16]=..\..\..\..\Environment\mingw64\bin\libwinpthread-1.dll
set files[17]=..\..\..\..\Libraries\boost_1_66_0\stage\lib64\libboost_filesystem-mgw73-mt-x64-1_66.dll
set files[18]=..\..\..\..\Libraries\boost_1_66_0\stage\lib64\libboost_system-mgw73-mt-x64-1_66.dll
set files[19]=..\..\..\..\Libraries\log4cpp\lib64\liblog4cpp-5.dll
set files[20]=..\..\..\..\Libraries\xerces-c-3.2.1\lib64\libxerces-c-3-2.dll
set files[21]=..\..\Common\Sqlite\shell\bin64\release\sqlite3.exe
set files[22]=..\..\..\..\Environment\mingw64\bin\libicuuc58.dll
set files[23]=..\..\..\..\Environment\mingw64\bin\libicudt58.dll
set len=23

set destination=.\

mkdir packs 2> nul
for /l %%n in (1,1,%len%) do (

    set file=!files[%%n]!
    for %%i in ("!file!") do (
        set filename=%%~ni%%~xi
        set line=!filename!............................................................
        set line=!line:~0,60!
		set filedest=%destination%
		if not "!filename!"=="Pack.dll" if "!filename:~0,4!"=="Pack" (
		    set filedest=%destination%\packs
		)
        copy !file! !filedest!\!filename! > nul
        if errorlevel 1 (
            echo !line![NOK]
			echo Not found : !file!
        ) else (
            echo !line![OK]
        )
    )
)

pause