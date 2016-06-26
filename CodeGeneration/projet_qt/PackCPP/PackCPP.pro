#-------------------------------------------------
#
# Project created by QtCreator 2013-11-06T21:41:30
#
#-------------------------------------------------

QT       -= core gui

TARGET = PackCPP
TEMPLATE = lib

DEFINES += HAS_PACKCPP_DLL \
           BUILD_PACKCPP_DLL \
           LOG4CPP_HAS_DLL \
           HAS_ENCODING_DLL \
           HAS_PACK_DLL \
           HAS_CORE_DLL

SOURCES += \
    ../../concrete/PackCPP/impl/SimpleInterpreterCommonGenerator.cpp \
    ../../concrete/PackCPP/impl/SimpleHPPPredicateGenerator.cpp \
    ../../concrete/PackCPP/impl/SimpleHPPLogGenerator.cpp \
    ../../concrete/PackCPP/impl/SimpleHPPInterpreterGenerator.cpp \
    ../../concrete/PackCPP/impl/SimpleHPPInterpreterAccessGenerator.cpp \
    ../../concrete/PackCPP/impl/SimpleHPPEntityGenerator.cpp \
    ../../concrete/PackCPP/impl/SimpleHPPAccessGenerator.cpp \
    ../../concrete/PackCPP/impl/SimpleHDataGenerator.cpp \
    ../../concrete/PackCPP/impl/SimpleCPPInterpreterGenerator.cpp \
    ../../concrete/PackCPP/impl/SimpleCPPInterpreterDataGenerator.cpp \
    ../../concrete/PackCPP/impl/SimpleCPPInterpreterAccessGenerator.cpp \
    ../../concrete/PackCPP/impl/SimpleCPPCommonGenerator.cpp \
    ../../concrete/PackCPP/impl/SimpleCPPCommentGenerator.cpp \
    ../../concrete/PackCPP/impl/SimpleCPPAccessGenerator.cpp \
    ../../concrete/PackCPP/impl/PackCPP.cpp \
    ../../concrete/PackCPP/impl/SimpleHPPExportGenerator.cpp \
    ../../concrete/PackCPP/impl/SimpleCPPDataGenerator.cpp \
    ../../concrete/PackCPP/impl/SimpleMDAccessGenerator.cpp \
    ../../concrete/PackCPP/impl/SimpleMDGenerator.cpp

HEADERS += \
    ../../concrete/PackCPP/PackCPP.h \
    ../../concrete/PackCPP/SimpleInterpreterCommonGenerator.hpp \
    ../../concrete/PackCPP/SimpleHPPPredicateGenerator.hpp \
    ../../concrete/PackCPP/SimpleHPPLogGenerator.hpp \
    ../../concrete/PackCPP/SimpleHPPInterpreterGenerator.hpp \
    ../../concrete/PackCPP/SimpleHPPInterpreterAccessGenerator.hpp \
    ../../concrete/PackCPP/SimpleHPPEntityGenerator.hpp \
    ../../concrete/PackCPP/SimpleHPPAccessGenerator.hpp \
    ../../concrete/PackCPP/SimpleHDataGenerator.hpp \
    ../../concrete/PackCPP/SimpleCPPInterpreterGenerator.hpp \
    ../../concrete/PackCPP/SimpleCPPInterpreterDataGenerator.hpp \
    ../../concrete/PackCPP/SimpleCPPInterpreterAccessGenerator.hpp \
    ../../concrete/PackCPP/SimpleCPPConnectionGenerator.hpp \
    ../../concrete/PackCPP/SimpleCPPCommonGenerator.hpp \
    ../../concrete/PackCPP/SimpleCPPCommentGenerator.hpp \
    ../../concrete/PackCPP/SimpleCPPAccessGenerator.hpp \
    ../../concrete/PackCPP/SimpleHPPExportGenerator.hpp \
    ../../concrete/PackCPP/SimpleCPPDataGenerator.hpp \
    ../../concrete/PackCPP/SimpleMDAccessGenerator.hpp \
    ../../concrete/PackCPP/SimpleMDGenerator.hpp

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
    ../../concrete/PackCPP

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
