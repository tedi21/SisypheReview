#include "cppBaseData.h"

//////////////////////////////////////////
// Instanciation des classes
//////////////////////////////////////////
namespace entity
{
    template class _CppInheritance<ucs>;
    template class _CppFunction<ucs>;
    template class _CppClass<ucs>;
    template class _DebugTypeInfo<ucs>;
    template class _TextFile<ucs>;
	template class _Rule<ucs>;
    template class _CppFileType<ucs>;
    template class _CppFile<ucs>;
    template class _CppInclude<ucs>;
    template class _CppParameter<ucs>;
    template class _CppAttribute<ucs>;
    template class _CppVariable<ucs>;
    template class _CppEnum<ucs>;
    template class _CppEnumConstant<ucs>;
    template class _CMacro<ucs>;
    template class _CppNotice<ucs>;
    template class _DebugFileInfo<ucs>;
    template class _DebugFunctionInfo<ucs>;
    template class _DebugVariableInfo<ucs>;
    template class _DebugErrorInfo<ucs>;
    template class _DebugStubInfo<ucs>;
    template class _DebugValueInfo<ucs>;
}

namespace data_access
{
    template class _CppInheritanceAccess<ucs>;
    template class _CppFunctionAccess<ucs>;
    template class _CppClassAccess<ucs>;
    template class _DebugTypeInfoAccess<ucs>;
    template class _TextFileAccess<ucs>;
	template class _RuleAccess<ucs>;
    template class _CppFileTypeAccess<ucs>;
    template class _CppFileAccess<ucs>;
    template class _CppIncludeAccess<ucs>;
    template class _CppParameterAccess<ucs>;
    template class _CppAttributeAccess<ucs>;
    template class _CppVariableAccess<ucs>;
    template class _CppEnumAccess<ucs>;
    template class _CppEnumConstantAccess<ucs>;
    template class _CMacroAccess<ucs>;
    template class _CppNoticeAccess<ucs>;
    template class _DebugFileInfoAccess<ucs>;
    template class _DebugFunctionInfoAccess<ucs>;
    template class _DebugVariableInfoAccess<ucs>;
    template class _DebugErrorInfoAccess<ucs>;
    template class _DebugStubInfoAccess<ucs>;
    template class _DebugValueInfoAccess<ucs>;

    template class _DataConnection<ucs>;
    template class _DataStatement<ucs>;
    template class _DataParameters<ucs>;
}
