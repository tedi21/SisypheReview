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
    ../../../../../Libraries/boost_1_66_0 \
    ../../../../../Libraries/log4cpp/include \
    ../../../../../Libraries/xerces-c-3.2.1/src \
    ../../encoding \
    ../../xerces \
    ../../factory \
    ../../generator \
    ../../core

CONFIG(MinGW-64):  LIBS += -L../../../../../Libraries/boost_1_66_0/stage/lib64 -lboost_filesystem-mgw73-mt-x64-1_66 \
                           -L../../../../../Libraries/boost_1_66_0/stage/lib64 -lboost_system-mgw73-mt-x64-1_66 \
                           -L../../../../../Libraries/xerces-c-3.2.1/lib64 -lxerces-c \
                           -L../../../../../Libraries/log4cpp/lib64 -llog4cpp

CONFIG(MinGW-64):  LIBS +=  ../../bin_qt/Core64/release/Core.dll \
                            ../../bin_qt/Encoding64/Release/Encoding.dll \
                            ../../bin_qt/Xerces64/release/XercesEncoding.dll

CONFIG(MinGW-32):  LIBS += -L../../../../../Libraries/boost_1_66_0/stage/lib32 -lboost_filesystem-mgw73-mt-x32-1_66 \
                           -L../../../../../Libraries/boost_1_66_0/stage/lib32 -lboost_system-mgw73-mt-x32-1_66 \
                           -L../../../../../Libraries/xerces-c-3.2.1/lib32 -lxerces-c \
                           -L../../../../../Libraries/log4cpp/lib32 -llog4cpp

CONFIG(MinGW-32):  LIBS +=  ../../bin_qt/Core32/release/Core.dll \
                            ../../bin_qt/Encoding32/Release/Encoding.dll \
                            ../../bin_qt/Xerces32/release/XercesEncoding.dll
