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
    ../../../../../Libraries/xerces-c-3.1.1/src \
    ../../../../../Libraries/boost_1_54_0 \
    ../../generator \
    ../../encoding \
    ../../xerces \
    ../../factory \
    ../../core \
    ../../concrete/PackIDL

LIBS += -L../../../../../Libraries/boost_1_54_0/stage/lib -lboost_filesystem-mgw48-mt-1_54 \
        -L../../../../../Libraries/boost_1_54_0/stage/lib -lboost_system-mgw48-mt-1_54 \
        -L../../../../../Libraries/xerces-c-3.1.1/src/.libs -lxerces-c-3-1 \
        -L../../../../../Libraries/log4cpp/src/.libs -llog4cpp-5

#debug {
#LIBS += ../../bin_qt/Core/Debug/Core.dll \
#        ../../bin_qt/Encoding/Debug/Encoding.dll
#}

release {
LIBS +=  ../../bin_qt/Core/release/Core.dll \
         ../../bin_qt/Encoding/Release/Encoding.dll
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
