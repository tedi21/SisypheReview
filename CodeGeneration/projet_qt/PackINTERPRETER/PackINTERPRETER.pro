#-------------------------------------------------
#
# Project created by QtCreator 2013-11-08T19:01:52
#
#-------------------------------------------------

QT       -= core gui

TARGET = PackINTERPRETER
TEMPLATE = lib

DEFINES += HAS_PACKINTERPRETER_DLL \
           BUILD_PACKINTERPRETER_DLL \
           LOG4CPP_HAS_DLL \
           HAS_ENCODING_DLL \
           HAS_PACK_DLL \
           HAS_CORE_DLL

SOURCES += \
    ../../concrete/PackINTERPRETER/impl/SimpleInterCommonGenerator.cpp \
    ../../concrete/PackINTERPRETER/impl/PackINTERPRETER.cpp \
    ../../concrete/PackINTERPRETER/impl/SimpleHPPInterpreterGenerator.cpp \
    ../../concrete/PackINTERPRETER/impl/SimpleCPPInterpreterGenerator.cpp \
    ../../concrete/PackINTERPRETER/impl/SimpleCPPDataInterpreterGenerator.cpp

HEADERS += \
    ../../concrete/PackINTERPRETER/SimpleInterCommonGenerator.hpp \
    ../../concrete/PackINTERPRETER/PackINTERPRETER.h \
    ../../concrete/PackINTERPRETER/SimpleHPPInterpreterGenerator.hpp \
    ../../concrete/PackINTERPRETER/SimpleCPPInterpreterGenerator.hpp \
    ../../concrete/PackINTERPRETER/SimpleCPPDataInterpreterGenerator.hpp

INCLUDEPATH += \
    ../../../../../Libraries/log4cpp/include \
    ../../../../../Libraries/xerces-c-3.1.1/src \
    ../../../../../Libraries/boost_1_54_0 \
    ../../generator \
    ../../encoding \
    ../../xerces \
    ../../factory \
    ../../core \
    ../../pack \
    ../../concrete/PackINTERPRETER

LIBS += -L../../../../../Libraries/boost_1_54_0/stage/lib -lboost_filesystem-mgw48-mt-1_54 \
        -L../../../../../Libraries/boost_1_54_0/stage/lib -lboost_system-mgw48-mt-1_54 \
        -L../../../../../Libraries/xerces-c-3.1.1/src/.libs -lxerces-c-3-1 \
        -L../../../../../Libraries/log4cpp/src/.libs -llog4cpp-5

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
