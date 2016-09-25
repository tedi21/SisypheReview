#-------------------------------------------------
#
# Project created by QtCreator 2013-11-05T19:39:01
#
#-------------------------------------------------

QT       -= core gui

TARGET = Refactor
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += LOG4CPP_HAS_DLL \
           HAS_ENCODING_DLL \
           HAS_CORE_DLL

SOURCES += \
    ../../main.cpp

HEADERS += \
    ../../CPlug.h

INCLUDEPATH += \
    ../../../../../Libraries/boost_1_61_0 \
    ../../../../../Libraries/log4cpp/include \
    ../../../../../Libraries/xerces-c-3.1.1/src \
    ../../encoding \
    ../../xerces \
    ../../factory \
    ../../generator \
    ../../core

LIBS += -L../../../../../Libraries/boost_1_61_0/stage/lib -lboost_filesystem-mgw61-mt-1_61 \
        -L../../../../../Libraries/boost_1_61_0/stage/lib -lboost_system-mgw61-mt-1_61 \
        -L../../../../../Libraries/xerces-c-3.1.1/lib -lxerces-c \
        -L../../../../../Libraries/log4cpp/lib -llog4cpp

#debug {
#LIBS += ../../bin_qt/Core/Debug/Core.dll \
#        ../../bin_qt/Encoding/Debug/Encoding.dll \
#        ../../bin_qt/Xerces/Debug/XercesEncoding.dll
#}

release {
LIBS +=  ../../bin_qt/Core/release/Core.dll \
         ../../bin_qt/Encoding/Release/Encoding.dll \
         ../../bin_qt/Xerces/release/XercesEncoding.dll
}
