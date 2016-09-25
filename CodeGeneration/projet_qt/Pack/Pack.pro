#-------------------------------------------------
#
# Project created by QtCreator 2013-11-05T21:14:23
#
#-------------------------------------------------

QT       -= core gui

TARGET = Pack
TEMPLATE = lib

DEFINES += HAS_PACK_DLL \
           BUILD_PACK_DLL \
           LOG4CPP_HAS_DLL \
           HAS_ENCODING_DLL \
           HAS_CORE_DLL

SOURCES += \
    ../../pack/impl/ParserHandlers.cpp \
    ../../pack/impl/GeneratorHandlers.cpp \
    ../../pack/impl/EtatHandler.cpp \
    ../../pack/impl/DefinitionHandler.cpp

HEADERS += \
    ../../pack/ProjectGenerator.hpp \
    ../../pack/ProjectConverter.hpp \
    ../../pack/ParserTypes.hpp \
    ../../pack/ParserHandlers.hpp \
    ../../pack/PackExport.hpp \
    ../../pack/GeneratorTypes.hpp \
    ../../pack/GeneratorHandlers.hpp \
    ../../pack/FileParser.hpp \
    ../../pack/FileGenerator.hpp \
    ../../pack/FileConverter.hpp \
    ../../pack/EtatHandler.hpp \
    ../../pack/DefinitionHandler.hpp \
    ../../pack/impl/ProjectGenerator_impl.hpp \
    ../../pack/impl/ParserHandlers_impl.hpp \
    ../../pack/impl/GeneratorHandlers_impl.hpp \
    ../../pack/impl/FileParser_impl.hpp \
    ../../pack/impl/FileGenerator_impl.hpp

INCLUDEPATH += \
    ../../../../../Libraries/log4cpp/include \
    ../../../../../Libraries/xerces-c-3.1.1/src \
    ../../../../../Libraries/boost_1_61_0 \
    ../../generator \
    ../../encoding \
    ../../xerces \
    ../../factory \
    ../../core \
    ../../pack

LIBS += -L../../../../../Libraries/xerces-c-3.1.1/lib -lxerces-c \
        -L../../../../../Libraries/log4cpp/lib -llog4cpp

#debug {
#LIBS += ../../bin_qt/Encoding/Debug/Encoding.dll \
#        ../../bin_qt/Core/Debug/Core.dll
#}

release {
LIBS +=  ../../bin_qt/Encoding/Release/Encoding.dll \
         ../../bin_qt/Core/release/Core.dll
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
