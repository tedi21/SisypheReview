QT       -= core gui

TARGET = cppBasePlg
TEMPLATE = lib

DEFINES += HAS_CPPBASEPLG_DLL \
           BUILD_CPPBASEPLG_DLL \
           HAS_CPPBASE_DLL \
           HAS_FACTORY_DLL \
           LOG4CPP_HAS_DLL

SOURCES += \
    ../../../../Common/Sqlite/sqlite3.c \
    cppBasePlg.cpp

HEADERS += \
    config.hpp \
    cppBasePlg.h

INCLUDEPATH += \
    ../../../../../../../Libraries/boost_1_61_0 \
    ../../../../../../../Libraries/log4cpp/include \
    ../../../../../CodeGeneration/encoding \
    ../../../../../CodeGeneration/generator \
    ../../../../../CodeGeneration/factory \
    ../../../../Common/Interpreter \
    ../../../../Common/Sqlite \
    ../../../../Common/Sqlite/Interpreter \
    ../../../../Common/Exception \
    ../../../../Common/Pointer \
    ../../../cppBase/src \
    ../../../cppBase/src/Interpreter


LIBS += -L../../../../../../../Libraries/log4cpp/lib -llog4cpp

#debug {
#LIBS += ../../../../../bin_qt/debug/Encoding.dll \
#        ../../../cppBase/bin/debug/cppBase.dll \
#        ../../../Script/bin/Plugin/debug/Plugin.dll
#}

release {
LIBS += ../../../../../CodeGeneration/bin_qt/Encoding/release/Encoding.dll \
        ../../../cppBase/bin/release/cppBase.dll \
        ../../../Interpreter/bin/Plugin/release/Plugin.dll
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

