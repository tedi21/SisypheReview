#-------------------------------------------------
#
# Project created by QtCreator 2013-11-08T19:01:52
#
#-------------------------------------------------

QT       -= core gui

TARGET = PackWORD
TEMPLATE = lib

DEFINES += HAS_PACKWORD_DLL \
           BUILD_PACKWORD_DLL \
           LOG4CPP_HAS_DLL \
           HAS_ENCODING_DLL \
           HAS_PACK_DLL \
           HAS_CORE_DLL

SOURCES += \
    ../../concrete/PackWORD/impl/SimpleWordCommonGenerator.cpp \
    ../../concrete/PackWORD/impl/SimpleHPPWordGenerator.cpp \
    ../../concrete/PackWORD/impl/SimpleHPPWordErrorGenerator.cpp \
    ../../concrete/PackWORD/impl/SimpleHPPCOMWordGenerator.cpp \
    ../../concrete/PackWORD/impl/SimpleCPPWordGenerator.cpp \
    ../../concrete/PackWORD/impl/SimpleCPPWordErrorGenerator.cpp \
    ../../concrete/PackWORD/impl/SimpleCPPCOMWordGenerator.cpp \
    ../../concrete/PackWORD/impl/PackWord.cpp

HEADERS += \
    ../../concrete/PackWORD/SimpleWordCommonGenerator.hpp \
    ../../concrete/PackWORD/SimpleHPPWordGenerator.hpp \
    ../../concrete/PackWORD/SimpleHPPWordErrorGenerator.hpp \
    ../../concrete/PackWORD/SimpleHPPCOMWordGenerator.hpp \
    ../../concrete/PackWORD/SimpleCPPWordGenerator.hpp \
    ../../concrete/PackWORD/SimpleCPPWordErrorGenerator.hpp \
    ../../concrete/PackWORD/SimpleCPPCOMWordGenerator.hpp \
    ../../concrete/PackWORD/PackWord.h

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
    ../../concrete/PackWORD

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
