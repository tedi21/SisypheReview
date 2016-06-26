#-------------------------------------------------
#
# Project created by QtCreator 2013-11-03T10:37:20
#
#-------------------------------------------------

QT       -= core gui

TARGET = Encoding
TEMPLATE = lib

DEFINES += HAS_ENCODING_DLL \
           BUILD_ENCODING_DLL

SOURCES += \
    ../../encoding/impl/utf16LE_codecvt.cpp \
    ../../encoding/impl/utf16BE_codecvt.cpp \
    ../../encoding/impl/utf16_codecvt.cpp \
    ../../encoding/impl/utf8_codecvt.cpp \
    ../../encoding/impl/iso_8859_15_codecvt.cpp \
    ../../encoding/impl/encoding.cpp

HEADERS += \
    ../../encoding/utf16LE_codecvt.hpp \
    ../../encoding/utf16BE_codecvt.hpp \
    ../../encoding/utf16_codecvt.hpp \
    ../../encoding/utf8_codecvt.hpp \
    ../../encoding/iso_8859_15_codecvt.hpp \
    ../../encoding/endianness.hpp \
    ../../encoding/EncodingExport.hpp \
    ../../encoding/encoding.hpp \
    ../../encoding/impl/utf16_codecvt_impl.hpp

INCLUDEPATH += \
    ../../../../../Libraries/boost_1_54_0 \
    ../../generator \
    ../../encoding

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
