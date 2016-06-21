#-------------------------------------------------
#
# Project created by QtCreator 2013-11-16T17:49:06
#
#-------------------------------------------------

QT       -= core gui

TARGET = libword
TEMPLATE = lib

DEFINES += BUILD_LIBWORD_DLL \
           HAS_LIBWORD_DLL \
           _UNICODE

SOURCES += \
    ../src/word_wrapper.cpp \
    ../src/word_error.cpp \
    ../src/word.cpp \
    ../src/WordMacro.cpp \
    ../src/WordXMLDocument.cpp \
    ../src/WordXMLNodeList.cpp \
    ../src/WordXMLNode.cpp \
    ../src/WordXMLFunctions.cpp

HEADERS += \
    ../src/word_wrapper.h \
    ../src/word_error.h \
    ../src/word.h \
    ../src/config/config.hpp \
    ../src/WordMacro.h \
    ../src/LibWordExport.h \
    ../src/WordXMLDocument.h \
    ../src/WordXMLNodeList.h \
    ../src/WordXMLNode.h \
    ../src/WordXMLFunctions.h

LIBS += -luuid -loleaut32 -lOle32
LIBS += -L../../../../../../Libraries/log4cpp/src/.libs -llog4cpp-5
LIBS += -L../../../../../../Libraries/xerces-c-3.1.1/src/.libs -lxerces-c-3-1
LIBS += -L../../../../../../Libraries/xalan-c-1.11/lib -lxalan-c1_11_0

release {
LIBS += ../../../../bin_qt/release/Encoding.dll \
        ../../../../bin_qt/release/XercesEncoding.dll
}

INCLUDEPATH += \
    ../../../../../../Libraries/boost_1_54_0 \
    ../../../../../../Libraries/log4cpp/include \
    ../../../../../../Libraries/xerces-c-3.1.1/src \
    ../../../../CodeGeneration/generator \
    ../../../../CodeGeneration/encoding \
    ../../../../CodeGeneration/xerces \
    ../../../../../../Libraries/xalan-c-1.11/src \
    ../../../../../../Libraries/xalan-c-1.11/nls/include \
    ../src \
    ../src/config

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
