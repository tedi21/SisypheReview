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
    ../../../../../../Libraries/boost_1_54_0 \
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

LIBS += -L../../../../../../../Libraries/boost_1_54_0/stage/lib -lboost_date_time-mgw48-mt-1_54 \
        -L../../../../../../Libraries/boost_1_54_0/stage/lib -lboost_filesystem-mgw48-mt-1_54 \
        -L../../../../../../Libraries/boost_1_54_0/stage/lib -lboost_system-mgw48-mt-1_54 \
        -L../../../../../../../Libraries/boost_1_54_0/stage/lib -lboost_regex-mgw48-mt-1_54 \
        -L../../../../../../Libraries/log4cpp/src/.libs -llog4cpp-5

#debug {
#LIBS += ../../../../bin_qt/debug/Encoding.dll \
#        ../../Script/bin/Plugin/debug/Plugin.dll
#}

release {
LIBS += ../../../../bin_qt/release/Encoding.dll \
        ../../Script/bin/Plugin/release/Plugin.dll
}

