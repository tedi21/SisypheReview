#-------------------------------------------------
#
# Project created by QtCreator 2013-11-08T18:00:44
#
#-------------------------------------------------

QT       -= core gui

TARGET = PackSQL
TEMPLATE = lib

DEFINES += HAS_PACKSQL_DLL \
           BUILD_PACKSQL_DLL \
           LOG4CPP_HAS_DLL \
           HAS_ENCODING_DLL \
           HAS_PACK_DLL \
           HAS_CORE_DLL

SOURCES += \
    ../../concrete/PackSQL/impl/SimpleSQLParser.cpp \
    ../../concrete/PackSQL/impl/PackSQL.cpp

HEADERS += \
    ../../concrete/PackSQL/SimpleSQLParser.hpp \
    ../../concrete/PackSQL/SimpleSQLGenerator.hpp \
    ../../concrete/PackSQL/PackSQL.h

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
    ../../concrete/PackSQL

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
