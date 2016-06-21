#-------------------------------------------------
#
# Project created by QtCreator 2013-11-11T14:03:20
#
#-------------------------------------------------

QT       -= core gui

TARGET = cppbase
TEMPLATE = lib

DEFINES += HAS_CPPBASE_DLL \
           BUILD_CPPBASE_DLL \
           LOG4CPP_HAS_DLL \
           SQLITE_ENABLE_FTS3 \
           SQLITE_ENABLE_FTS3_PARENTHESIS

SOURCES += \
    ../src/cppBaseData.cpp \
    ../../../Common/Sqlite/sqlite3.c

HEADERS += \
    ../src/cppBaseData.h \
    ../src/cppBaseExport.hpp \
    ../src/cppFile.hpp \
    ../src/cppFileAccess.hpp \
    ../src/cppFileAccess_impl.hpp \
    ../src/cppFilePredicate.hpp \
    ../src/cppFileType.hpp \
    ../src/cppFileTypeAccess.hpp \
    ../src/cppFileTypeAccess_impl.hpp \
    ../src/cppFileTypePredicate.hpp \
    ../src/cppInclude.hpp \
    ../src/cppIncludeAccess.hpp \
    ../src/cppIncludeAccess_impl.hpp \
    ../src/cppIncludePredicate.hpp \
    ../src/textFile.hpp \
    ../src/textFileAccess.hpp \
    ../src/textFileAccess_impl.hpp \
    ../src/textFilePredicate.hpp \
    ../src/config/config.hpp \
    ../src/cppAttribute.hpp \
    ../src/cppAttributeAccess.hpp \
    ../src/cppAttributeAccess_impl.hpp \
    ../src/cppAttributePredicate.hpp \
    ../src/cppClass.hpp \
    ../src/cppClassAccess.hpp \
    ../src/cppClassAccess_impl.hpp \
    ../src/cppClassPredicate.hpp \
    ../src/cppFunction.hpp \
    ../src/cppFunctionAccess.hpp \
    ../src/cppFunctionAccess_impl.hpp \
    ../src/cppFunctionPredicate.hpp \
    ../src/cppInheritance.hpp \
    ../src/cppInheritanceAccess.hpp \
    ../src/cppInheritanceAccess_impl.hpp \
    ../src/cppInheritancePredicate.hpp \
    ../src/cppParameter.hpp \
    ../src/cppParameterAccess.hpp \
    ../src/cppParameterAccess_impl.hpp \
    ../src/cppParameterPredicate.hpp \
    ../src/cMacro.hpp \
    ../src/cMacroAccess.hpp \
    ../src/cMacroAccess_impl.hpp \
    ../src/cMacroPredicate.hpp \
    ../src/cppEnum.hpp \
    ../src/cppEnumAccess.hpp \
    ../src/cppEnumAccess_impl.hpp \
    ../src/cppEnumConstant.hpp \
    ../src/cppEnumConstantAccess.hpp \
    ../src/cppEnumConstantAccess_impl.hpp \
    ../src/cppEnumConstantPredicate.hpp \
    ../src/cppEnumPredicate.hpp \
    ../src/debugFileInfo.hpp \
    ../src/debugFileInfoAccess.hpp \
    ../src/debugFileInfoAccess_impl.hpp \
    ../src/debugFileInfoPredicate.hpp \
    ../src/debugFunctionInfo.hpp \
    ../src/debugFunctionInfoAccess.hpp \
    ../src/debugFunctionInfoAccess_impl.hpp \
    ../src/debugFunctionInfoPredicate.hpp \
    ../src/debugVariableInfo.hpp \
    ../src/debugVariableInfoAccess.hpp \
    ../src/debugVariableInfoAccess_impl.hpp \
    ../src/debugVariableInfoPredicate.hpp \
    ../src/textNotice.hpp \
    ../src/textNoticeAccess.hpp \
    ../src/textNoticeAccess_impl.hpp \
    ../src/textNoticePredicate.hpp

INCLUDEPATH += \
    ../../../../../../Libraries/boost_1_54_0 \
    ../../../../../../Libraries/log4cpp/include \
    ../../../../CodeGeneration/encoding \
    ../../../../CodeGeneration/generator \
    ../../../../CodeGeneration/factory \
    ../../../Common/Sqlite \
    ../../../Common/Exception \
    ../../../Common/Pointer \
    ../src \
    ../src/config

LIBS += -L../../../../../../Libraries/log4cpp/src/.libs -llog4cpp-5

#debug {
#LIBS += ../bin_qt/debug/Encoding.dll
#}

release {
LIBS += ../../../../bin_qt/release/Encoding.dll
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
