QT       -= core gui

TARGET = Plugin
TEMPLATE = lib

DEFINES += HAS_FACTORY_DLL \
           BUILD_FACTORY_DLL

HEADERS += \
    ../config/config.hpp

SOURCES += \
    ../src/plugin.cpp

INCLUDEPATH += \
    ../../../../../../Libraries/log4cpp/include \
    ../../../../../../Libraries/boost_1_54_0 \
    ../../../../CodeGeneration/encoding \
    ../../../../CodeGeneration/generator \
    ../../../../CodeGeneration/factory \
    ../../../Common/Interpreter \
    ../config

#debug {
#LIBS += ../../../../../bin_qt/debug/Encoding.dll
#}

release {
LIBS += ../../../../../bin_qt/release/Encoding.dll
}

