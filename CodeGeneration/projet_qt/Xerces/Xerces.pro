#-------------------------------------------------
#
# Project created by QtCreator 2013-11-02T09:25:28
#
#-------------------------------------------------

QT       -= core gui

TARGET = XercesEncoding
TEMPLATE = lib

DEFINES += HAS_XENCODING_DLL \
           BUILD_XENCODING_DLL

SOURCES += \
    ../../xerces/impl/xstring.cpp

HEADERS += \
    ../../xerces/xstring.hpp \
    ../../xerces/xiterator.hpp \
    ../../xerces/XEncodingExport.hpp

INCLUDEPATH += \
    ../../../../../Libraries/boost_1_66_0 \
    ../../../../../Libraries/xerces-c-3.2.1/src \
    ../../generator \
    ../../encoding

CONFIG(MinGW-64): LIBS += -L../../../../../Libraries/xerces-c-3.2.1/lib64 -lxerces-c
CONFIG(MinGW-32): LIBS += -L../../../../../Libraries/xerces-c-3.2.1/lib32 -lxerces-c

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
