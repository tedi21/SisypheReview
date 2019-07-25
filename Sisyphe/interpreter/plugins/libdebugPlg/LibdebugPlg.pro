QT       -= core gui

TARGET = LibdebugPlg
TEMPLATE = lib
CONFIG += c++1z

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
    ../../../../../../Libraries/boost_1_66_0 \
    ../../../../../../Libraries/log4cpp/include \
    ../../../../../../Libraries/xerces-c-3.2.1/src \
    ../../../../../../Libraries/xalan-c-1.11/c/src \
    ../../../../../../Libraries/xalan-c-1.11/c/nls/include \
    ../../../../CodeGeneration/encoding \
    ../../../../CodeGeneration/generator \
    ../../../../CodeGeneration/factory \
    ../../../../Common/Interpreter \
    ../../../../Common/Exception \
    ../../../../Common/Pointer \
    ./Interpreter/atl \
    ./Interpreter/src

LIBS += -luuid -loleaut32 -lOle32 -ldbgeng
CONFIG(MinGW-64): LIBS += -L../../../../../../Libraries/log4cpp/lib64 -llog4cpp \
                          -L../../../../../../Libraries/xerces-c-3.2.1/lib64 -lxerces-c \
                          -L../../../../../../Libraries/xalan-c-1.11/c/lib64 -lxalan-c

CONFIG(MinGW-64): LIBS += ../../../../CodeGeneration/bin_qt/Encoding64/release/Encoding.dll \
                          ../../../Interpreter/bin/Plugin64/release/Plugin.dll

CONFIG(MinGW-32): LIBS += -L../../../../../../Libraries/log4cpp/lib32 -llog4cpp \
                          -L../../../../../../Libraries/xerces-c-3.2.1/lib32 -lxerces-c \
                          -L../../../../../../Libraries/xalan-c-1.11/c/lib32 -lxalan-c

CONFIG(MinGW-32): LIBS += ../../../../CodeGeneration/bin_qt/Encoding32/release/Encoding.dll \
                          ../../../Interpreter/bin/Plugin32/release/Plugin.dll

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

