#-------------------------------------------------
#
# Project created by QtCreator 2013-11-08T18:08:46
#
#-------------------------------------------------

QT       -= core gui

TARGET = PackCFG
TEMPLATE = lib

DEFINES += HAS_PACKCFG_DLL \
           BUILD_PACKCFG_DLL \
           LOG4CPP_HAS_DLL \
           HAS_ENCODING_DLL \
           HAS_CORE_DLL

SOURCES += \
    ../../concrete/PackCFG/impl/SimpleCFGHandler.cpp \
    ../../concrete/PackCFG/impl/PackCFG.cpp \
    ../../concrete/PackCFG/impl/FileCFGParser.cpp

HEADERS += \
    ../../concrete/PackCFG/SimpleCFGStructure.hpp \
    ../../concrete/PackCFG/SimpleCFGHandler.hpp \
    ../../concrete/PackCFG/SimpleCFGGrammar.hpp \
    ../../concrete/PackCFG/PackCFG.h \
    ../../concrete/PackCFG/FileCFGParser.hpp

INCLUDEPATH += \
    ../../../../../Libraries/log4cpp/include \
    ../../../../../Libraries/xerces-c-3.1.1/src \
    ../../../../../Libraries/boost_1_61_0 \
    ../../generator \
    ../../encoding \
    ../../xerces \
    ../../factory \
    ../../core \
    ../../concrete/PackCFG

LIBS += -L../../../../../Libraries/boost_1_61_0/stage/lib -lboost_filesystem-mgw61-mt-1_61 \
        -L../../../../../Libraries/boost_1_61_0/stage/lib -lboost_system-mgw61-mt-1_61 \
        -L../../../../../Libraries/xerces-c-3.1.1/lib -lxerces-c \
        -L../../../../../Libraries/log4cpp/lib -llog4cpp

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
