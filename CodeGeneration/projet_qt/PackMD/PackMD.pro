#-------------------------------------------------
#
# Project created by QtCreator 2013-11-08T19:01:52
#
#-------------------------------------------------

QT       -= core gui

TARGET = PackMD
TEMPLATE = lib

DEFINES += HAS_PACKMD_DLL \
           BUILD_PACKMD_DLL \
           LOG4CPP_HAS_DLL \
           HAS_ENCODING_DLL \
           HAS_PACK_DLL \
           HAS_CORE_DLL

SOURCES += \
    ../../concrete/PackMD/impl/PackMD.cpp \
    ../../concrete/PackMD/impl/SimpleMDGenerator.cpp

HEADERS += \
    ../../concrete/PackMD/PackMD.h \
    ../../concrete/PackMD/SimpleMDGenerator.hpp

INCLUDEPATH += \
    ../../../../../Libraries/log4cpp/include \
    ../../../../../Libraries/xerces-c-3.1.1/src \
    ../../../../../Libraries/boost_1_61_0 \
    ../../generator \
    ../../encoding \
    ../../xerces \
    ../../factory \
    ../../core \
    ../../pack \
    ../../concrete/PackMD

LIBS += -L../../../../../Libraries/boost_1_61_0/stage/lib -lboost_filesystem-mgw61-mt-1_61 \
        -L../../../../../Libraries/boost_1_61_0/stage/lib -lboost_system-mgw61-mt-1_61 \
        -L../../../../../Libraries/xerces-c-3.1.1/lib -lxerces-c \
        -L../../../../../Libraries/log4cpp/lib -llog4cpp

#debug {
#LIBS += ../../bin_qt/Pack/debug/Pack.dll \
#        ../../bin_qt/Core/Debug/Core.dll \
#        ../../bin_qt/Encoding/Debug/Encoding.dll
#}

release {
LIBS +=  ../../bin_qt/Pack/release/Pack.dll \
         ../../bin_qt/Core/release/Core.dll \
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