QT       -= core gui

TARGET = LibpdbPlg
TEMPLATE = lib

DEFINES += HAS_LIBPDBPLG_DLL \
           BUILD_LIBPDBPLG_DLL \
           HAS_FACTORY_DLL \
           LOG4CPP_HAS_DLL

SOURCES += \
    LibpdbPlg.cpp

HEADERS += \
    config.hpp \
    LibpdbPlg.h

INCLUDEPATH += \
    ../../../../../../../Libraries/boost_1_54_0 \
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
    "..\..\..\..\..\..\..\..\..\..\Program Files (x86)\Microsoft Visual Studio 12.0\DIA SDK\include" \
    ./Interpreter/atl \
    ./Interpreter/src

LIBS += -luuid -loleaut32 -lOle32
LIBS += -L../../../../../../../Libraries/log4cpp/src/.libs -llog4cpp-5 \
        -L../../../../../../../Libraries/xerces-c-3.1.1/src/.libs -lxerces-c-3-1 \
        -L../../../../../../../Libraries/xalan-c-1.11/lib -lxalan-c1_11_0

#debug {
#LIBS += ../../../../../bin_qt/debug/Encoding.dll \
#        ../../../Script/bin/Plugin/debug/Plugin.dll
#}

release {
LIBS += ../../../../../bin_qt/release/Encoding.dll \
        ../../../Script/bin/Plugin/release/Plugin.dll
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

