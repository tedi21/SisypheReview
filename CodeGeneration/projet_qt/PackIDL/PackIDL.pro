#-------------------------------------------------
#
# Project created by QtCreator 2013-11-08T18:08:46
#
#-------------------------------------------------

QT       -= core gui

TARGET = PackIDL
TEMPLATE = lib

DEFINES += HAS_PACKIDL_DLL \
           BUILD_PACKIDL_DLL \
           LOG4CPP_HAS_DLL \
           HAS_ENCODING_DLL \
           HAS_CORE_DLL

SOURCES += \
    ../../concrete/PackIDL/impl/SimpleIDLHandler.cpp \
    ../../concrete/PackIDL/impl/PackIDL.cpp \
    ../../concrete/PackIDL/impl/FileIDLParser.cpp

HEADERS += \
    ../../concrete/PackIDL/SimpleIDLStructure.hpp \
    ../../concrete/PackIDL/SimpleIDLHandler.hpp \
    ../../concrete/PackIDL/SimpleIDLGrammar.hpp \
    ../../concrete/PackIDL/PackIDL.h \
    ../../concrete/PackIDL/FileIDLParser.hpp

INCLUDEPATH += \
    ../../../../../Libraries/log4cpp/include \
    ../../../../../Libraries/xerces-c-3.2.1/src \
    ../../../../../Libraries/boost_1_66_0 \
    ../../generator \
    ../../encoding \
    ../../xerces \
    ../../factory \
    ../../core \
    ../../concrete/PackIDL

CONFIG(MinGW-64): LIBS += -L../../../../../Libraries/boost_1_66_0/stage/lib64 -lboost_filesystem-mgw73-mt-x64-1_66 \
                          -L../../../../../Libraries/boost_1_66_0/stage/lib64 -lboost_system-mgw73-mt-x64-1_66 \
                          -L../../../../../Libraries/xerces-c-3.2.1/lib64 -lxerces-c \
                          -L../../../../../Libraries/log4cpp/lib64 -llog4cpp

CONFIG(MinGW-64): LIBS +=  ../../bin_qt/Core64/release/Core.dll \
                           ../../bin_qt/Encoding64/Release/Encoding.dll

CONFIG(MinGW-32): LIBS += -L../../../../../Libraries/boost_1_66_0/stage/lib32 -lboost_filesystem-mgw73-mt-x32-1_66 \
                          -L../../../../../Libraries/boost_1_66_0/stage/lib32 -lboost_system-mgw73-mt-x32-1_66 \
                          -L../../../../../Libraries/xerces-c-3.2.1/lib32 -lxerces-c \
                          -L../../../../../Libraries/log4cpp/lib32 -llog4cpp

CONFIG(MinGW-32): LIBS +=  ../../bin_qt/Core32/release/Core.dll \
                           ../../bin_qt/Encoding32/Release/Encoding.dll

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
