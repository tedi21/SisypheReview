QT       -= core gui

TARGET = cppBasePlg
TEMPLATE = lib
CONFIG += c++1z

DEFINES += HAS_CPPBASEPLG_DLL \
           BUILD_CPPBASEPLG_DLL \
           HAS_CPPBASE_DLL \
           HAS_FACTORY_DLL \
           LOG4CPP_HAS_DLL

SOURCES += \
    cppBasePlg.cpp

HEADERS += \
    config.hpp \
    cppBasePlg.h

INCLUDEPATH += \
    ../../../../../../Libraries/boost_1_66_0 \
    ../../../../../../Libraries/log4cpp/include \
    ../../../../CodeGeneration/encoding \
    ../../../../CodeGeneration/generator \
    ../../../../CodeGeneration/factory \
    ../../../../Common/Interpreter \
    ../../../../Common/Sqlite \
    ../../../../Common/Sqlite/Interpreter \
    ../../../../Common/Exception \
    ../../../../Common/Pointer \
    ../../../cppBase/src \
    ../../../cppBase/src/Interpreter


CONFIG(MinGW-64): LIBS += -L../../../../../../Libraries/log4cpp/lib64 -llog4cpp

CONFIG(MinGW-64): LIBS += ../../../../CodeGeneration/bin_qt/Encoding64/release/Encoding.dll \
                          ../../../cppBase/bin64/release/cppBase.dll \
                          ../../../Interpreter/bin/Plugin64/release/Plugin.dll

CONFIG(MinGW-32): LIBS += -L../../../../../../Libraries/log4cpp/lib32 -llog4cpp

CONFIG(MinGW-32): LIBS += ../../../../CodeGeneration/bin_qt/Encoding32/release/Encoding.dll \
                          ../../../cppBase/bin32/release/cppBase.dll \
                          ../../../Interpreter/bin/Plugin32/release/Plugin.dll

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
