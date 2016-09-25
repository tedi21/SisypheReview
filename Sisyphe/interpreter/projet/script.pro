TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += LOG4CPP_HAS_DLL \
           HAS_FACTORY_DLL

SOURCES += \
    ../../../Common/Interpreter/interpreter.cpp \
    ../src/main.cpp

HEADERS += \
    ../config/config.hpp \
    ../../../../CodeGeneration/CPlug.h

INCLUDEPATH += \
    ../../../../../../Libraries/boost_1_61_0 \
    ../../../../../../Libraries/log4cpp/include \
    ../../../../CodeGeneration/encoding \
    ../../../../CodeGeneration/generator \
    ../../../../CodeGeneration/factory \
    ../../../../CodeGeneration \
    ../../../Common/Interpreter \
    ../../../Common/Exception \
    ../../../Common/Pointer \
    ../../../Common/Sqlite \
    ../config

LIBS += -L../../../../../../../Libraries/boost_1_61_0/stage/lib -lboost_date_time-mgw61-mt-1_61 \
        -L../../../../../../Libraries/boost_1_61_0/stage/lib -lboost_filesystem-mgw61-mt-1_61 \
        -L../../../../../../Libraries/boost_1_61_0/stage/lib -lboost_system-mgw61-mt-1_61 \
        -L../../../../../../../Libraries/boost_1_61_0/stage/lib -lboost_regex-mgw61-mt-1_61 \
        -L../../../../../../Libraries/log4cpp/lib -llog4cpp

#debug {
#LIBS += ../../../../CodeGeneration/bin_qt/Encoding/debug/Encoding.dll \
#        ../../Interpreter/bin/Plugin/debug/Plugin.dll
#}

release {
LIBS += ../../../../CodeGeneration/bin_qt/Encoding/release/Encoding.dll \
        ../../Interpreter/bin/Plugin/release/Plugin.dll
}

