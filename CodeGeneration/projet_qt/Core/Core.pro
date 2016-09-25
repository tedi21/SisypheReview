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
    ../../../../../Libraries/boost_1_61_0 \
    ../../../../../Libraries/log4cpp/include \
    ../../../../../Libraries/xerces-c-3.1.1/src \
    ../../encoding \
    ../../generator \
    ../../factory \
    ../../xerces \
    ../../core

LIBS += -L../../../../../Libraries/xerces-c-3.1.1/lib -lxerces-c \
        -L../../../../../Libraries/log4cpp/lib -llog4cpp

#debug {
#LIBS += ../../bin_qt/Encoding/Debug/Encoding.dll \
#        ../../bin_qt/Xerces/Debug/XercesEncoding.dll
#}

release {
LIBS +=  ../../bin_qt/Encoding/Release/Encoding.dll \
         ../../bin_qt/Xerces/release/XercesEncoding.dll
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
