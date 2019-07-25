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
    ../../../../../Libraries/xerces-c-3.2.1/src \
    ../../../../../Libraries/boost_1_66_0 \
    ../../generator \
    ../../encoding \
    ../../xerces \
    ../../factory \
    ../../core \
    ../../pack \
    ../../concrete/PackWORD

CONFIG(MinGW-64): LIBS += -L../../../../../Libraries/boost_1_66_0/stage/lib64 -lboost_filesystem-mgw73-mt-x64-1_66 \
                          -L../../../../../Libraries/boost_1_66_0/stage/lib64 -lboost_system-mgw73-mt-x64-1_66 \
                          -L../../../../../Libraries/xerces-c-3.2.1/lib64 -lxerces-c \
                          -L../../../../../Libraries/log4cpp/lib64 -llog4cpp

CONFIG(MinGW-64): LIBS +=  ../../bin_qt/Pack64/release/Pack.dll \
                           ../../bin_qt/Core64/release/Core.dll \
                           ../../bin_qt/Encoding64/Release/Encoding.dll

CONFIG(MinGW-32): LIBS += -L../../../../../Libraries/boost_1_66_0/stage/lib32 -lboost_filesystem-mgw73-mt-x32-1_66 \
                          -L../../../../../Libraries/boost_1_66_0/stage/lib32 -lboost_system-mgw73-mt-x32-1_66 \
                          -L../../../../../Libraries/xerces-c-3.2.1/lib32 -lxerces-c \
                          -L../../../../../Libraries/log4cpp/lib32 -llog4cpp

CONFIG(MinGW-32): LIBS +=  ../../bin_qt/Pack32/release/Pack.dll \
                           ../../bin_qt/Core32/release/Core.dll \
                           ../../bin_qt/Encoding32/Release/Encoding.dll

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
