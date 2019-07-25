QT       -= core gui

TARGET = Plugin
TEMPLATE = lib

DEFINES += HAS_FACTORY_DLL \
           BUILD_FACTORY_DLL

HEADERS +=

SOURCES += \
    ../src/plugin.cpp

INCLUDEPATH += \
    ../../../../../Libraries/log4cpp/include \
    ../../../../../Libraries/boost_1_66_0 \
    ../../../CodeGeneration/encoding \
    ../../../CodeGeneration/generator \
    ../../../CodeGeneration/factory \
    ../../../Common/Interpreter \
    ../config

CONFIG(MinGW-64): LIBS += -L../../../../../../Libraries/log4cpp/lib64 -llog4cpp

CONFIG(MinGW-64): LIBS += ../../../../CodeGeneration/bin_qt/Encoding64/release/Encoding.dll

CONFIG(MinGW-32): LIBS += -L../../../../../../Libraries/log4cpp/lib32 -llog4cpp

CONFIG(MinGW-32): LIBS += ../../../../CodeGeneration/bin_qt/Encoding32/release/Encoding.dll
