QT       -= core gui

TARGET = Plugin
TEMPLATE = lib

DEFINES += HAS_FACTORY_DLL \
           BUILD_FACTORY_DLL

HEADERS +=

SOURCES += \
    ../src/plugin.cpp

INCLUDEPATH += \
    ../../../../../../Libraries/log4cpp/include \
    ../../../../../../Libraries/boost_1_61_0 \
    ../../../../CodeGeneration/encoding \
    ../../../../CodeGeneration/generator \
    ../../../../CodeGeneration/factory \
    ../../../Common/Interpreter \
    ../config

LIBS += -L../../../../../../../Libraries/log4cpp/lib -llog4cpp

#debug {
#LIBS += ../../../../CodeGeneration/bin_qt/Encoding/debug/Encoding.dll
#}

release {
LIBS += ../../../../../CodeGeneration/bin_qt/Encoding/release/Encoding.dll
}

