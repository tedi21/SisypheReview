TEMPLATE = app
CONFIG += c++1z console
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
    ../../../../../Libraries/boost_1_66_0 \
    ../../../../../Libraries/log4cpp/include \
    ../../../CodeGeneration/encoding \
    ../../../CodeGeneration/generator \
    ../../../CodeGeneration/factory \
    ../../../CodeGeneration \
    ../../../Common/Interpreter \
    ../../../Common/Exception \
    ../../../Common/Pointer \
    ../../../Common/Sqlite \
    ../config

CONFIG(MinGW-64): LIBS += -L../../../../../../Libraries/boost_1_66_0/stage/lib64 -lboost_date_time-mgw73-mt-x64-1_66 \
                          -L../../../../../../Libraries/boost_1_66_0/stage/lib64 -lboost_filesystem-mgw73-mt-x64-1_66 \
                          -L../../../../../../Libraries/boost_1_66_0/stage/lib64 -lboost_system-mgw73-mt-x64-1_66 \
                          -L../../../../../../Libraries/boost_1_66_0/stage/lib64 -lboost_regex-mgw73-mt-x64-1_66 \
                          -L../../../../../../Libraries/log4cpp/lib64 -llog4cpp

CONFIG(MinGW-64): LIBS += ../../../../CodeGeneration/bin_qt/Encoding64/release/Encoding.dll \
                          ../../../Interpreter/bin/Plugin64/release/Plugin.dll

CONFIG(MinGW-32): LIBS += -L../../../../../../Libraries/boost_1_66_0/stage/lib32 -lboost_date_time-mgw73-mt-x32-1_66 \
                          -L../../../../../../Libraries/boost_1_66_0/stage/lib32 -lboost_filesystem-mgw73-mt-x32-1_66 \
                          -L../../../../../../Libraries/boost_1_66_0/stage/lib32 -lboost_system-mgw73-mt-x32-1_66 \
                          -L../../../../../../Libraries/boost_1_66_0/stage/lib32 -lboost_regex-mgw73-mt-x32-1_66 \
                          -L../../../../../../Libraries/log4cpp/lib32 -llog4cpp

CONFIG(MinGW-32): LIBS += ../../../../CodeGeneration/bin_qt/Encoding32/release/Encoding.dll \
                          ../../../Interpreter/bin/Plugin32/release/Plugin.dll
