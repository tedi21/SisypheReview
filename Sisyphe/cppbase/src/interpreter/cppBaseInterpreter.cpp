#include "ProgramInterpreter.hpp"
#include "cppInheritanceInterpreter.hpp"
#include "cppInheritanceInterpreterAccess.hpp"
#include "cppFunctionInterpreter.hpp"
#include "cppFunctionInterpreterAccess.hpp"
#include "cppClassInterpreter.hpp"
#include "cppClassInterpreterAccess.hpp"
#include "debugTypeInfoInterpreter.hpp"
#include "debugTypeInfoInterpreterAccess.hpp"
#include "textFileInterpreter.hpp"
#include "textFileInterpreterAccess.hpp"
#include "cppFileTypeInterpreter.hpp"
#include "cppFileTypeInterpreterAccess.hpp"
#include "cppFileInterpreter.hpp"
#include "cppFileInterpreterAccess.hpp"
#include "cppIncludeInterpreter.hpp"
#include "cppIncludeInterpreterAccess.hpp"
#include "cppParameterInterpreter.hpp"
#include "cppParameterInterpreterAccess.hpp"
#include "cppAttributeInterpreter.hpp"
#include "cppAttributeInterpreterAccess.hpp"
#include "cppVariableInterpreter.hpp"
#include "cppVariableInterpreterAccess.hpp"
#include "cppEnumInterpreter.hpp"
#include "cppEnumInterpreterAccess.hpp"
#include "cppEnumConstantInterpreter.hpp"
#include "cppEnumConstantInterpreterAccess.hpp"
#include "cMacroInterpreter.hpp"
#include "cMacroInterpreterAccess.hpp"
#include "cppNoticeInterpreter.hpp"
#include "cppNoticeInterpreterAccess.hpp"
#include "debugFileInfoInterpreter.hpp"
#include "debugFileInfoInterpreterAccess.hpp"
#include "debugFunctionInfoInterpreter.hpp"
#include "debugFunctionInfoInterpreterAccess.hpp"
#include "debugVariableInfoInterpreter.hpp"
#include "debugVariableInfoInterpreterAccess.hpp"
#include "debugErrorInfoInterpreter.hpp"
#include "debugErrorInfoInterpreterAccess.hpp"
#include "debugStubInfoInterpreter.hpp"
#include "debugStubInfoInterpreterAccess.hpp"
#include "debugValueInfoInterpreter.hpp"
#include "debugValueInfoInterpreterAccess.hpp"

using namespace enc;
using namespace fctr;
using namespace interp;

//////////////////////////////////////////
// Exportation des classes
//////////////////////////////////////////
FACTORY_EXPORT(CppInheritanceInterpreter<ucs>)
FACTORY_EXPORT(CppInheritanceInterpreterAccess<ucs>)
FACTORY_EXPORT(CppFunctionInterpreter<ucs>)
FACTORY_EXPORT(CppFunctionInterpreterAccess<ucs>)
FACTORY_EXPORT(CppClassInterpreter<ucs>)
FACTORY_EXPORT(CppClassInterpreterAccess<ucs>)
FACTORY_EXPORT(DebugTypeInfoInterpreter<ucs>)
FACTORY_EXPORT(DebugTypeInfoInterpreterAccess<ucs>)
FACTORY_EXPORT(TextFileInterpreter<ucs>)
FACTORY_EXPORT(TextFileInterpreterAccess<ucs>)
FACTORY_EXPORT(CppFileTypeInterpreter<ucs>)
FACTORY_EXPORT(CppFileTypeInterpreterAccess<ucs>)
FACTORY_EXPORT(CppFileInterpreter<ucs>)
FACTORY_EXPORT(CppFileInterpreterAccess<ucs>)
FACTORY_EXPORT(CppIncludeInterpreter<ucs>)
FACTORY_EXPORT(CppIncludeInterpreterAccess<ucs>)
FACTORY_EXPORT(CppParameterInterpreter<ucs>)
FACTORY_EXPORT(CppParameterInterpreterAccess<ucs>)
FACTORY_EXPORT(CppAttributeInterpreter<ucs>)
FACTORY_EXPORT(CppAttributeInterpreterAccess<ucs>)
FACTORY_EXPORT(CppVariableInterpreter<ucs>)
FACTORY_EXPORT(CppVariableInterpreterAccess<ucs>)
FACTORY_EXPORT(CppEnumInterpreter<ucs>)
FACTORY_EXPORT(CppEnumInterpreterAccess<ucs>)
FACTORY_EXPORT(CppEnumConstantInterpreter<ucs>)
FACTORY_EXPORT(CppEnumConstantInterpreterAccess<ucs>)
FACTORY_EXPORT(CMacroInterpreter<ucs>)
FACTORY_EXPORT(CMacroInterpreterAccess<ucs>)
FACTORY_EXPORT(CppNoticeInterpreter<ucs>)
FACTORY_EXPORT(CppNoticeInterpreterAccess<ucs>)
FACTORY_EXPORT(DebugFileInfoInterpreter<ucs>)
FACTORY_EXPORT(DebugFileInfoInterpreterAccess<ucs>)
FACTORY_EXPORT(DebugFunctionInfoInterpreter<ucs>)
FACTORY_EXPORT(DebugFunctionInfoInterpreterAccess<ucs>)
FACTORY_EXPORT(DebugVariableInfoInterpreter<ucs>)
FACTORY_EXPORT(DebugVariableInfoInterpreterAccess<ucs>)
FACTORY_EXPORT(DebugErrorInfoInterpreter<ucs>)
FACTORY_EXPORT(DebugErrorInfoInterpreterAccess<ucs>)
FACTORY_EXPORT(DebugStubInfoInterpreter<ucs>)
FACTORY_EXPORT(DebugStubInfoInterpreterAccess<ucs>)
FACTORY_EXPORT(DebugValueInfoInterpreter<ucs>)
FACTORY_EXPORT(DebugValueInfoInterpreterAccess<ucs>)

