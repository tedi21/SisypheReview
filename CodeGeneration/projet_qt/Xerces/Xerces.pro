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

HEADERS += xerces.h\
    ../../xerces/xstring.hpp \
    ../../xerces/xiterator.hpp \
    ../../xerces/XEncodingExport.hpp

INCLUDEPATH += \
    ../../../../../Libraries/boost_1_61_0 \
    ../../../../../Libraries/xerces-c-3.1.1/src \
    ../../generator \
    ../../encoding

LIBS += -L../../../../../Libraries/xerces-c-3.1.1/lib -lxerces-c

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
