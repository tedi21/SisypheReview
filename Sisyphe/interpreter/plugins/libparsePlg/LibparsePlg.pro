QT       -= core gui

TARGET = LibParsePlg
TEMPLATE = lib
CONFIG += c++1z

DEFINES += HAS_LIBPARSEPLG_DLL \
           BUILD_LIBPARSEPLG_DLL \
           HAS_LIBPARSE_DLL \
           HAS_FACTORY_DLL \
           LOG4CPP_HAS_DLL

SOURCES += \
    LibParsePlg.cpp

HEADERS += \
    config.hpp \
    LibParsePlg.h \
    interpreter/src/CPPParserInterpreter.hpp \
    interpreter/src/CPPParserInterpreter_impl.hpp \
    interpreter/src/GitInterpreter.hpp \
    interpreter/src/GitInterpreter_impl.hpp \
    interpreter/src/GitRepositoryInterpreter.hpp \
    interpreter/src/GitRepositoryInterpreter_impl.hpp \
    interpreter/src/GitBlameInterpreter.hpp \
    interpreter/src/GitBlameInterpreter_impl.hpp
    
INCLUDEPATH += \
    ../../../../../../Libraries/boost_1_66_0 \
    ../../../../../../Libraries/log4cpp/include \
    ../../../../../../Libraries/libgit2-1.0.1/include \
    ../../../../CodeGeneration/encoding \
    ../../../../CodeGeneration/generator \
    ../../../../CodeGeneration/factory \
    ../../../../Common/Interpreter \
    ../../../../Common/Exception \
    ../../../../Common/Pointer \
    ./interpreter/src


CONFIG(MinGW-64): LIBS += -L../../../../../../Libraries/log4cpp/lib64 -llog4cpp \
                          -L../../../../../../Libraries/boost_1_66_0/stage/lib64 -lboost_filesystem-mgw73-mt-x64-1_66 \
                          -L../../../../../../Libraries/boost_1_66_0/stage/lib64 -lboost_system-mgw73-mt-x64-1_66 \
                          -L../../../../../../Libraries/libgit2-1.0.1/Build64 -lgit2

CONFIG(MinGW-64): LIBS += ../../../../CodeGeneration/bin_qt/Encoding64/release/Encoding.dll \
                          ../../../Interpreter/bin/Plugin64/release/Plugin.dll

CONFIG(MinGW-32): LIBS += -L../../../../../../Libraries/log4cpp/lib32 -llog4cpp \
                          -L../../../../../../Libraries/boost_1_66_0/stage/lib32 -lboost_filesystem-mgw73-mt-x32-1_66 \
                          -L../../../../../../Libraries/boost_1_66_0/stage/lib32 -lboost_system-mgw73-mt-x32-1_66 \
                          -L../../../../../../Libraries/libgit2-1.0.1/Build32 -lgit2

CONFIG(MinGW-32): LIBS += ../../../../CodeGeneration/bin_qt/Encoding32/release/Encoding.dll \
                          ../../../Interpreter/bin/Plugin32/release/Plugin.dll

CONFIG(Linux-64): LIBS += -L../../../../../../Libraries/log4cpp/lib64 -llog4cpp \
                          -L../../../../../../Libraries/boost_1_66_0/stage/lib64 -lboost_filesystem \
                          -L../../../../../../Libraries/boost_1_66_0/stage/lib64 -lboost_system \
                          -L../../../../../../Libraries/libgit2-1.0.1/build -lgit2 \
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

