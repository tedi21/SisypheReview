#-------------------------------------------------
#
# Project created by QtCreator 2013-11-03T10:57:43
#
#-------------------------------------------------

QT       -= core gui

TARGET = Core
TEMPLATE = lib

DEFINES += HAS_CORE_DLL \
           BUILD_CORE_DLL \
           LOG4CPP_HAS_DLL \
           HAS_ENCODING_DLL \
           HAS_XENCODING_DLL

SOURCES += \
    ../../core/impl/Locale.cpp \
    ../../core/impl/FactoryTypes.cpp \
    ../../core/impl/CoreTypes.cpp

HEADERS += \
    ../../core/Workspace.hpp \
    ../../core/ValidationHandler.hpp \
    ../../core/RelationGroup.hpp \
    ../../core/Relation.hpp \
    ../../core/Parser.hpp \
    ../../core/Logger.hpp \
    ../../core/Locale.hpp \
    ../../core/Generator.hpp \
    ../../core/FlatIterator.hpp \
    ../../core/FlatContainer.hpp \
    ../../core/File.hpp \
    ../../core/FactoryTypes.hpp \
    ../../core/Equality.hpp \
    ../../core/EntityGroup.hpp \
    ../../core/Entity.hpp \
    ../../core/DataModel.hpp \
    ../../core/CoreTypes.hpp \
    ../../core/CoreExport.hpp \
    ../../core/AttributeGroup.hpp \
    ../../core/Attribute.hpp \
    ../../core/impl/Workspace_impl.hpp \
    ../../core/impl/Relation_impl.hpp \
    ../../core/impl/File_impl.hpp \
    ../../core/impl/Entity_impl.hpp \
    ../../core/impl/DataModel_impl.hpp \
    ../../core/impl/Attribute_impl.hpp \
    ../../core/impl/Content_impl.hpp \
    ../../core/Content.hpp

INCLUDEPATH += \
    ../../../../../Libraries/boost_1_66_0 \
    ../../../../../Libraries/log4cpp/include \
    ../../../../../Libraries/xerces-c-3.2.1/src \
    ../../encoding \
    ../../generator \
    ../../factory \
    ../../xerces \
    ../../core

CONFIG(MinGW-64): LIBS += -L../../../../../Libraries/xerces-c-3.2.1/lib64 -lxerces-c \
                          -L../../../../../Libraries/log4cpp/lib64 -llog4cpp

CONFIG(MinGW-64): LIBS +=  ../../bin_qt/Encoding64/Release/Encoding.dll \
                           ../../bin_qt/Xerces64/release/XercesEncoding.dll

CONFIG(MinGW-32): LIBS += -L../../../../../Libraries/xerces-c-3.2.1/lib32 -lxerces-c \
                          -L../../../../../Libraries/log4cpp/lib32 -llog4cpp

CONFIG(MinGW-32): LIBS +=  ../../bin_qt/Encoding32/Release/Encoding.dll \
                           ../../bin_qt/Xerces32/release/XercesEncoding.dll

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
