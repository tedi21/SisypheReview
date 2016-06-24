#include "cppBasePlg.h"

// Nombre d'attributs maximums pour une classe
#define FCTR_MAX_SIZE 22

// Classe d'interface Interpreter
#include "ProgramInterpreter.hpp"

#include "textFileInterpreter.hpp"
#include "textFileInterpreterAccess.hpp"
#include "textNoticeInterpreter.hpp"
#include "textNoticeInterpreterAccess.hpp"
#include "cppFileTypeInterpreter.hpp"
#include "cppFileTypeInterpreterAccess.hpp"
#include "cppFileInterpreter.hpp"
#include "cppFileInterpreterAccess.hpp"
#include "cppIncludeInterpreter.hpp"
#include "cppIncludeInterpreterAccess.hpp"
#include "cppClassInterpreter.hpp"
#include "cppClassInterpreterAccess.hpp"
#include "cppInheritanceInterpreter.hpp"
#include "cppInheritanceInterpreterAccess.hpp"
#include "cppAttributeInterpreter.hpp"
#include "cppAttributeInterpreterAccess.hpp"
#include "cppFunctionInterpreter.hpp"
#include "cppFunctionInterpreterAccess.hpp"
#include "cppParameterInterpreter.hpp"
#include "cppParameterInterpreterAccess.hpp"
#include "cppVariableInterpreter.hpp"
#include "cppVariableInterpreterAccess.hpp"
#include "cppEnumInterpreter.hpp"
#include "cppEnumInterpreterAccess.hpp"
#include "cppEnumConstantInterpreter.hpp"
#include "cppEnumConstantInterpreterAccess.hpp"
#include "cMacroInterpreter.hpp"
#include "cMacroInterpreterAccess.hpp"
#include "debugFileInfoInterpreter.hpp"
#include "debugFileInfoInterpreterAccess.hpp"
#include "debugFunctionInfoInterpreter.hpp"
#include "debugFunctionInfoInterpreterAccess.hpp"
#include "debugVariableInfoInterpreter.hpp"
#include "debugVariableInfoInterpreterAccess.hpp"

#include "connectionInterpreter.hpp"
#include "statementInterpreter.hpp"
#include "dataParametersInterpreter.hpp"

using namespace enc;
using namespace fctr;
using namespace interp;

extern "C" CPPBASEPLG_API void PlugInit(va_list vl, void** res)
{
    TextFileInterpreter<ucs>::register_class();
    TextFileInterpreterAccess<ucs>::register_class();
    TextNoticeInterpreter<ucs>::register_class();
    TextNoticeInterpreterAccess<ucs>::register_class();
    CppFileTypeInterpreter<ucs>::register_class();
    CppFileTypeInterpreterAccess<ucs>::register_class();
    CppFileInterpreter<ucs>::register_class();
    CppFileInterpreterAccess<ucs>::register_class();
    CppIncludeInterpreter<ucs>::register_class();
    CppIncludeInterpreterAccess<ucs>::register_class();   
    CppClassInterpreter<ucs>::register_class();
    CppClassInterpreterAccess<ucs>::register_class();
    CppInheritanceInterpreter<ucs>::register_class();
    CppInheritanceInterpreterAccess<ucs>::register_class();
    CppFunctionInterpreter<ucs>::register_class();
    CppFunctionInterpreterAccess<ucs>::register_class();
    CppAttributeInterpreter<ucs>::register_class();
    CppAttributeInterpreterAccess<ucs>::register_class();
    CppParameterInterpreter<ucs>::register_class();
    CppParameterInterpreterAccess<ucs>::register_class();
    CppVariableInterpreter<ucs>::register_class();
    CppVariableInterpreterAccess<ucs>::register_class();
    CppEnumInterpreter<ucs>::register_class();
    CppEnumInterpreterAccess<ucs>::register_class();
    CppEnumConstantInterpreter<ucs>::register_class();
    CppEnumConstantInterpreterAccess<ucs>::register_class();
    CMacroInterpreter<ucs>::register_class();
    CMacroInterpreterAccess<ucs>::register_class();
    DebugFileInfoInterpreter<ucs>::register_class();
    DebugFileInfoInterpreterAccess<ucs>::register_class();
    DebugFunctionInfoInterpreter<ucs>::register_class();
    DebugFunctionInfoInterpreterAccess<ucs>::register_class();
    DebugVariableInfoInterpreter<ucs>::register_class();
    DebugVariableInfoInterpreterAccess<ucs>::register_class();

    ConnectionInterpreter<ucs>::register_class();
    StatementInterpreter<ucs>::register_class();
    DataParametersInterpreter<ucs>::register_class();

    const std::vector<string>& args = *(va_arg(vl,const std::vector<string>*));
    if (!args.empty())
    {
        if (!data_access::UniDataConnection::openConnection(L"", 0, encode<ansi,ucs>(args[0]), L"", L""))
        {
            Category* logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "cannot open DB connection " << args[0] << ".";
        }
    }
    *res = (void*) LOGNAME;
}

extern "C" CPPBASEPLG_API void PlugTerm(void** res)
{
    TextFileInterpreter<ucs>::unregister_class();
    TextFileInterpreterAccess<ucs>::unregister_class();
    TextNoticeInterpreter<ucs>::unregister_class();
    TextNoticeInterpreterAccess<ucs>::unregister_class();
    CppFileTypeInterpreter<ucs>::unregister_class();
    CppFileTypeInterpreterAccess<ucs>::unregister_class();
    CppFileInterpreter<ucs>::unregister_class();
    CppFileInterpreterAccess<ucs>::unregister_class();
    CppIncludeInterpreter<ucs>::unregister_class();
    CppIncludeInterpreterAccess<ucs>::unregister_class();
    CppClassInterpreter<ucs>::unregister_class();
    CppClassInterpreterAccess<ucs>::unregister_class();
    CppInheritanceInterpreter<ucs>::unregister_class();
    CppInheritanceInterpreterAccess<ucs>::unregister_class();
    CppFunctionInterpreter<ucs>::unregister_class();
    CppFunctionInterpreterAccess<ucs>::unregister_class();
    CppAttributeInterpreter<ucs>::unregister_class();
    CppAttributeInterpreterAccess<ucs>::unregister_class();
    CppParameterInterpreter<ucs>::unregister_class();
    CppParameterInterpreterAccess<ucs>::unregister_class();   
    CppVariableInterpreter<ucs>::unregister_class();
    CppVariableInterpreterAccess<ucs>::unregister_class();
    CppEnumInterpreter<ucs>::unregister_class();
    CppEnumInterpreterAccess<ucs>::unregister_class();
    CppEnumConstantInterpreter<ucs>::unregister_class();
    CppEnumConstantInterpreterAccess<ucs>::unregister_class();
    CMacroInterpreter<ucs>::unregister_class();
    CMacroInterpreterAccess<ucs>::unregister_class();
    DebugFileInfoInterpreter<ucs>::unregister_class();
    DebugFileInfoInterpreterAccess<ucs>::unregister_class();
    DebugFunctionInfoInterpreter<ucs>::unregister_class();
    DebugFunctionInfoInterpreterAccess<ucs>::unregister_class();
    DebugVariableInfoInterpreter<ucs>::unregister_class();
    DebugVariableInfoInterpreterAccess<ucs>::unregister_class();

    ConnectionInterpreter<ucs>::unregister_class();
    StatementInterpreter<ucs>::unregister_class();
    DataParametersInterpreter<ucs>::unregister_class();

    data_access::UniDataConnection::closeConnection();
}
