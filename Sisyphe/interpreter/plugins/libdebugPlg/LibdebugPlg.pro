QT       -= core gui

TARGET = LibdebugPlg
TEMPLATE = lib

DEFINES += HAS_LIBDEBUGPLG_DLL \
           BUILD_LIBDEBUGPLG_DLL \
           HAS_FACTORY_DLL \
           LOG4CPP_HAS_DLL

SOURCES += \
    LibdebugPlg.cpp

HEADERS += \
    config.hpp \
    LibdebugPlg.h

INCLUDEPATH += \
    ../../../../../../../Libraries/boost_1_61_0 \
    ../../../../../../../Libraries/log4cpp/include \
    ../../../../../../../Libraries/xerces-c-3.1.1/src \
    ../../../../../../../Libraries/xalan-c-1.11/src \
    ../../../../../../../Libraries/xalan-c-1.11/nls/include \
    ../../../../../CodeGeneration/encoding \
    ../../../../../CodeGeneration/generator \
    ../../../../../CodeGeneration/factory \
    ../../../../Common/Interpreter \
    ../../../../Common/Exception \
    ../../../../Common/Pointer \
    "..\..\..\..\..\..\..\..\..\..\Program Files (x86)\Microsoft Visual Studio 14.0\DIA SDK\include" \
    ./Interpreter/atl \
    ./Interpreter/src

LIBS += -luuid -loleaut32 -lOle32 -ldbgeng
LIBS += -L../../../../../../../Libraries/log4cpp/lib -llog4cpp \
        -L../../../../../../../Libraries/xerces-c-3.1.1/lib -lxerces-c \
        -L../../../../../../../Libraries/xalan-c-1.11/lib -lxalan-c

#debug {
#LIBS += ../../../../../CodeGeneration/bin_qt/Encoding/debug/Encoding.dll \
#        ../../../Interpreter/bin/Plugin/debug/Plugin.dll
#}

release {
LIBS += ../../../../../CodeGeneration/bin_qt/Encoding/release/Encoding.dll \
        ../../../Interpreter/bin/Plugin/release/Plugin.dll
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

