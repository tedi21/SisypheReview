QT       -= core gui

TARGET = LibDiffPlg
TEMPLATE = lib
CONFIG += c++1z

DEFINES += HAS_LIBDIFFPLG_DLL \
           BUILD_LIBDIFFPLG_DLL \
           HAS_LIBDIFF_DLL \
           HAS_FACTORY_DLL \
           LOG4CPP_HAS_DLL

SOURCES += \
    LibDiffPlg.cpp

HEADERS += \
    config.hpp \
    LibDiffPlg.h \
    interpreter/src/DiffInterpreter.hpp \
    interpreter/src/DiffInterpreter_impl.hpp \
    interpreter/src/DiffTypeInterpreter.hpp \
    interpreter/src/DiffTypeInterpreter_impl.hpp \
    interpreter/src/DiffValueInterpreter.hpp \
    interpreter/src/DiffValueInterpreter_impl.hpp

INCLUDEPATH += \
    ../../../../../../Libraries/boost_1_66_0 \
    ../../../../../../Libraries/log4cpp/include \
    ../../../../CodeGeneration/encoding \
    ../../../../CodeGeneration/generator \
    ../../../../CodeGeneration/factory \
    ../../../../Common/Interpreter \
    ../../../../Common/Exception \
    ../../../../Common/Pointer \
    ./interpreter/src


CONFIG(MinGW-64): LIBS += -L../../../../../../Libraries/log4cpp/lib64 -llog4cpp

CONFIG(MinGW-64): LIBS += ../../../../CodeGeneration/bin_qt/Encoding64/release/Encoding.dll \
                          ../../../Interpreter/bin/Plugin64/release/Plugin.dll

CONFIG(MinGW-32): LIBS += -L../../../../../../Libraries/log4cpp/lib32 -llog4cpp \

CONFIG(MinGW-32): LIBS += ../../../../CodeGeneration/bin_qt/Encoding32/release/Encoding.dll \
                          ../../../Interpreter/bin/Plugin32/release/Plugin.dll

CONFIG(Linux-64): LIBS += -L../../../../../../Libraries/log4cpp/lib64 -llog4cpp \
                          -L../../../../CodeGeneration/bin_qt/Encoding64 -lEncoding \
                          -L../../../interpreter/bin/Plugin64 -lPlugin

CONFIG(Linux-64): QMAKE_CXXFLAGS += -std=c++17

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

