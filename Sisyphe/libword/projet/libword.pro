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

INCLUDEPATH += \
    ../../../../../Libraries/boost_1_66_0 \
    ../../../../../Libraries/log4cpp/include \
    ../../../../../Libraries/xerces-c-3.2.1/src \
    ../../../CodeGeneration/generator \
    ../../../CodeGeneration/encoding \
    ../../../CodeGeneration/xerces \
    ../../../../../Libraries/xalan-c-1.11/c/src \
    ../../../../../Libraries/xalan-c-1.11/c/nls/include \
    ../src \
    ../src/config


LIBS += -luuid -loleaut32 -lOle32

CONFIG(MinGW-64): LIBS += -L../../../../../Libraries/log4cpp/lib64 -llog4cpp \
                          -L../../../../../Libraries/xerces-c-3.2.1/lib64 -lxerces-c \
                          -L../../../../../Libraries/xalan-c-1.11/c/lib64 -lxalan-c

CONFIG(MinGW-64): LIBS += ../../../CodeGeneration/bin_qt/Encoding64/release/Encoding.dll \
                          ../../../CodeGeneration/bin_qt/Xerces64/release/XercesEncoding.dll

CONFIG(MinGW-32): LIBS += -L../../../../../Libraries/log4cpp/lib32 -llog4cpp \
                          -L../../../../../Libraries/xerces-c-3.2.1/lib32 -lxerces-c \
                          -L../../../../../Libraries/xalan-c-1.11/c/lib32 -lxalan-c

CONFIG(MinGW-32): LIBS += ../../../CodeGeneration/bin_qt/Encoding32/release/Encoding.dll \
                          ../../../CodeGeneration/bin_qt/Xerces32/release/XercesEncoding.dll

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
