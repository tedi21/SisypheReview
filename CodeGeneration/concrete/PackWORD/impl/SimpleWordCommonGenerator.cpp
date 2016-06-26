#include "SimpleWordCommonGenerator.hpp"

namespace dsg {

	namespace generator {

		SimpleWordCommonGenerator::SimpleWordCommonGenerator() {

			CreateHeader =
                                "/*"
                << line_g(1) << " * " << $(0)
                << line_g(1) << " *"
                << line_g(1) << " *"
                << line_g(1) << " * @date " << call_g(getDateHandler("dd-mm-yyyy"))
                << line_g(1) << " * @author " << call_g(getWorkspaceAuthorHandler())
                << line_g(1) << " * @version " << call_g(getWorkspaceVersionHandler())
                << line_g(1) << " * " << call_g(getWorkspaceBriefHandler())
                << line_g(1) << " */";

			CreateHPPDefine = 
				   line_g(1) << "#ifndef " << upper_g($(0))
				<< line_g(1) << "#define " << upper_g($(0));

			CreateHPPEndDefine = 
				   line_g(1) << "#endif";

			CreateNamespace =
				   line_g(1) << "namespace " << $(0)
                << line_g(1) << "{";

			CreateEndNamespace =
                   line_g(1) << "}";

            ListClass =
                   $(0)[If_IsClass][ent0, entN];

            ClassName =
                    ent_g(getEntityNameHandler(KIND_ALIAS));

            ListAttribute =
                   $(0)[If_IsAttribute][attr0, attrN];

            AttributeName =
                   attr_g(getAttributeNameHandler(KIND_ALIAS));

            AttributeType =
                  (str_g("bool")                        [attr_g(getIsAttributeTypeHandler(ATTR_BOOLEAN))]
                << str_g("unsigned char")               [attr_g(getIsAttributeTypeHandler(ATTR_SBYTE))]
                << str_g("char")                        [attr_g(getIsAttributeTypeHandler(ATTR_BYTE))]
                << str_g("TCHAR")                       [attr_g(getIsAttributeTypeHandler(ATTR_CHAR))]
                << str_g("char")                        [attr_g(getIsAttributeTypeHandler(ATTR_ANSICHAR))]
                << str_g("wchar_t")                     [attr_g(getIsAttributeTypeHandler(ATTR_WIDECHAR))]
                << str_g("int")                         [attr_g(getIsAttributeTypeHandler(ATTR_INT))]
                << str_g("unsigned int")                [attr_g(getIsAttributeTypeHandler(ATTR_UINT))]
                << str_g("short")                       [attr_g(getIsAttributeTypeHandler(ATTR_INT16))]
                << str_g("unsigned short")              [attr_g(getIsAttributeTypeHandler(ATTR_UINT16))]
                << str_g("long")                        [attr_g(getIsAttributeTypeHandler(ATTR_INT32))]
                << str_g("unsigned long")               [attr_g(getIsAttributeTypeHandler(ATTR_UINT32))]
                << str_g("long long")                   [attr_g(getIsAttributeTypeHandler(ATTR_INT64))]
                << str_g("unsigned long long")          [attr_g(getIsAttributeTypeHandler(ATTR_UINT64))]
                << str_g("float")                       [attr_g(getIsAttributeTypeHandler(ATTR_SINGLE))]
                << str_g("double")                      [attr_g(getIsAttributeTypeHandler(ATTR_DOUBLE))]
                << str_g("std::basic_string<TCHAR>")    [attr_g(getIsAttributeTypeHandler(ATTR_STRING))]
                << str_g("std::string")                 [attr_g(getIsAttributeTypeHandler(ATTR_ANSISTRING))]
                << str_g("std::wstring")                [attr_g(getIsAttributeTypeHandler(ATTR_WIDESTRING))]
                << str_g("std::basic_string<TCHAR>")    [attr_g(getIsAttributeTypeHandler(ATTR_TEXT))]
                << str_g("time_t")                      [attr_g(getIsAttributeTypeHandler(ATTR_TIME))]
                << str_g("time_t")                      [attr_g(getIsAttributeTypeHandler(ATTR_DATE))]
                << str_g("IDispatch*")                  [attr_g(getIsAttributeTypeHandler(ATTR_ANY))])
                   [!If_IsREF]
                << GotoREF
                   (
                       rel_g(getRelationSourceHandler(KIND_ALIAS))
                   )
                   [If_IsREF];

            AttributeTypeParam =
                   AttributeType                            [!If_IsREF && 
                                                             !attr_g(getIsAttributeTypeHandler(ATTR_STRING)) &&
                                                             !attr_g(getIsAttributeTypeHandler(ATTR_ANSISTRING)) &&
                                                             !attr_g(getIsAttributeTypeHandler(ATTR_WIDESTRING)) &&
                                                             !attr_g(getIsAttributeTypeHandler(ATTR_TEXT))   &&
                                                             !attr_g(getIsAttributeTypeHandler(ATTR_TIME))   &&
                                                             !attr_g(getIsAttributeTypeHandler(ATTR_DATE))]
                << (str_g("const ") << AttributeType << "&")[!If_IsREF && 
                                                             (attr_g(getIsAttributeTypeHandler(ATTR_STRING)) ||
                                                              attr_g(getIsAttributeTypeHandler(ATTR_ANSISTRING)) ||
                                                              attr_g(getIsAttributeTypeHandler(ATTR_WIDESTRING)) ||
                                                              attr_g(getIsAttributeTypeHandler(ATTR_TEXT))   ||
                                                              attr_g(getIsAttributeTypeHandler(ATTR_TIME))   ||
                                                              attr_g(getIsAttributeTypeHandler(ATTR_DATE)))]
                << (AttributeType << WithClassType(str_g(" const&")))
                                                            [If_IsREF];

            AttributeParamName =
                   lower_g(attr_g(getAttributeNameHandler(KIND_ALIAS)));

            MethodName =
                   ent_g(getEntityFunctionNameHandler(KIND_ALIAS));

            ListMethod =
                   $(0)[If_IsMethod]
                       [entitiesByRel(FILTER_TARGET|FILTER_CONTEXTUAL)]
                       [relationsByEnt(FILTER_SOURCE)];

            ReturnType =
                   str_g("void")[!Has_Return]
                << GotoReturn(AttributeType);

            ListParameter =
                   $(0)[set_g((attr0,attrN), If_IsParameter)];

            ParameterType =
                   AttributeTypeParam    [attr_g(getIsAttributeModifierHandler(ATTR_CONST))]
                << (AttributeType << "&")[!attr_g(getIsAttributeModifierHandler(ATTR_CONST))];

            ParameterName =
                   lower_g(attr_g(getAttributeNameHandler(KIND_ALIAS)));

            AttributeVTType =
                  (str_g("VT_BOOL")         [attr_g(getIsAttributeTypeHandler(ATTR_BOOLEAN))]
                << str_g("VT_UI1")          [attr_g(getIsAttributeTypeHandler(ATTR_SBYTE))]
                << str_g("VT_I1")           [attr_g(getIsAttributeTypeHandler(ATTR_BYTE))]
                << str_g("VT_I2")           [attr_g(getIsAttributeTypeHandler(ATTR_CHAR))]
                << str_g("VT_I1")           [attr_g(getIsAttributeTypeHandler(ATTR_ANSICHAR))]
                << str_g("VT_I2")           [attr_g(getIsAttributeTypeHandler(ATTR_WIDECHAR))]
                << str_g("VT_INT")          [attr_g(getIsAttributeTypeHandler(ATTR_INT))]
                << str_g("VT_UINT")         [attr_g(getIsAttributeTypeHandler(ATTR_UINT))]
                << str_g("VT_I2")           [attr_g(getIsAttributeTypeHandler(ATTR_INT16))]
                << str_g("VT_UI2")          [attr_g(getIsAttributeTypeHandler(ATTR_UINT16))]
                << str_g("VT_I4")           [attr_g(getIsAttributeTypeHandler(ATTR_INT32))]
                << str_g("VT_UI4")          [attr_g(getIsAttributeTypeHandler(ATTR_UINT32))]
                << str_g("VT_I8")           [attr_g(getIsAttributeTypeHandler(ATTR_INT64))]
                << str_g("VT_UI8")          [attr_g(getIsAttributeTypeHandler(ATTR_UINT64))]
                << str_g("VT_R4")           [attr_g(getIsAttributeTypeHandler(ATTR_SINGLE))]
                << str_g("VT_R8")           [attr_g(getIsAttributeTypeHandler(ATTR_DOUBLE))]
                << str_g("VT_BSTR")         [attr_g(getIsAttributeTypeHandler(ATTR_STRING))]
                << str_g("VT_LPSTR")        [attr_g(getIsAttributeTypeHandler(ATTR_ANSISTRING))]
                << str_g("VT_LPWSTR")       [attr_g(getIsAttributeTypeHandler(ATTR_WIDESTRING))]
                << str_g("VT_BSTR")         [attr_g(getIsAttributeTypeHandler(ATTR_TEXT))]
                << str_g("VT_DATE")         [attr_g(getIsAttributeTypeHandler(ATTR_TIME))]
                << str_g("VT_DATE")         [attr_g(getIsAttributeTypeHandler(ATTR_DATE))]
                << str_g("VT_UNKNOWN")      [attr_g(getIsAttributeTypeHandler(ATTR_ANY))])
                   [!If_IsREF]
                << (WithClassType(str_g("VT_DISPATCH"))
                <<  WithEnumType(str_g("VT_I4")))
                   [If_IsREF];

            AttributeVTVal =
                (("(" << $(0) << "?VARIANT_TRUE:VARIANT_FALSE)")[attr_g(getIsAttributeTypeHandler(ATTR_BOOLEAN))]
                << $(0)                   [attr_g(getIsAttributeTypeHandler(ATTR_SBYTE))]
                << $(0)                   [attr_g(getIsAttributeTypeHandler(ATTR_BYTE))]
                << $(0)                   [attr_g(getIsAttributeTypeHandler(ATTR_CHAR))]
                << $(0)                   [attr_g(getIsAttributeTypeHandler(ATTR_ANSICHAR))]
                << $(0)                   [attr_g(getIsAttributeTypeHandler(ATTR_WIDECHAR))]
                << $(0)                   [attr_g(getIsAttributeTypeHandler(ATTR_INT))]
                << $(0)                   [attr_g(getIsAttributeTypeHandler(ATTR_UINT))]
                << $(0)                   [attr_g(getIsAttributeTypeHandler(ATTR_INT16))]
                << $(0)                   [attr_g(getIsAttributeTypeHandler(ATTR_UINT16))]
                << $(0)                   [attr_g(getIsAttributeTypeHandler(ATTR_INT32))]
                << $(0)                   [attr_g(getIsAttributeTypeHandler(ATTR_UINT32))]
                << $(0)                   [attr_g(getIsAttributeTypeHandler(ATTR_INT64))]
                << $(0)                   [attr_g(getIsAttributeTypeHandler(ATTR_UINT64))]
                << $(0)                   [attr_g(getIsAttributeTypeHandler(ATTR_SINGLE))]
                << $(0)                   [attr_g(getIsAttributeTypeHandler(ATTR_DOUBLE))]
                << ("SysAllocString(" << $(0) << ".c_str())")[attr_g(getIsAttributeTypeHandler(ATTR_STRING))]
                << ($(0) << ".c_str()")   [attr_g(getIsAttributeTypeHandler(ATTR_ANSISTRING))]
                << ($(0) << ".c_str()")   [attr_g(getIsAttributeTypeHandler(ATTR_WIDESTRING))]
                << ("SysAllocString(" << $(0) << ".c_str())")[attr_g(getIsAttributeTypeHandler(ATTR_TEXT))]
                << $(0)                   [attr_g(getIsAttributeTypeHandler(ATTR_TIME))]
                << $(0)                   [attr_g(getIsAttributeTypeHandler(ATTR_DATE))]
                << $(0)                   [attr_g(getIsAttributeTypeHandler(ATTR_ANY))])
                   [!If_IsREF]
               << (WithClassType(str_g("(IDispatch*) ")) << $(0))
                   [If_IsREF];

            VariantVal =
                  (str_g("boolVal")       [attr_g(getIsAttributeTypeHandler(ATTR_BOOLEAN))]
                << str_g("bVal")          [attr_g(getIsAttributeTypeHandler(ATTR_SBYTE))]
                << str_g("cVal")          [attr_g(getIsAttributeTypeHandler(ATTR_BYTE))]
                << str_g("uiVal")         [attr_g(getIsAttributeTypeHandler(ATTR_CHAR))]
                << str_g("cVal")          [attr_g(getIsAttributeTypeHandler(ATTR_ANSICHAR))]
                << str_g("uiVal")         [attr_g(getIsAttributeTypeHandler(ATTR_WIDECHAR))]
                << str_g("intVal")        [attr_g(getIsAttributeTypeHandler(ATTR_INT))]
                << str_g("uintVal")       [attr_g(getIsAttributeTypeHandler(ATTR_UINT))]
                << str_g("iVal")          [attr_g(getIsAttributeTypeHandler(ATTR_INT16))]
                << str_g("uiVal")         [attr_g(getIsAttributeTypeHandler(ATTR_UINT16))]
                << str_g("lVal")          [attr_g(getIsAttributeTypeHandler(ATTR_INT32))]
                << str_g("ulVal")         [attr_g(getIsAttributeTypeHandler(ATTR_UINT32))]
                << str_g("hVal")          [attr_g(getIsAttributeTypeHandler(ATTR_INT64))]
                << str_g("uhVal")         [attr_g(getIsAttributeTypeHandler(ATTR_UINT64))]
                << str_g("fltVal")        [attr_g(getIsAttributeTypeHandler(ATTR_SINGLE))]
                << str_g("dblVal")        [attr_g(getIsAttributeTypeHandler(ATTR_DOUBLE))]
                << str_g("bstrVal")       [attr_g(getIsAttributeTypeHandler(ATTR_STRING))]
                << str_g("pszVal")        [attr_g(getIsAttributeTypeHandler(ATTR_ANSISTRING))]
                << str_g("pwszVal")       [attr_g(getIsAttributeTypeHandler(ATTR_WIDESTRING))]
                << str_g("bstrVal")       [attr_g(getIsAttributeTypeHandler(ATTR_TEXT))]
                << str_g("date")          [attr_g(getIsAttributeTypeHandler(ATTR_TIME))]
                << str_g("date")          [attr_g(getIsAttributeTypeHandler(ATTR_DATE))]
                << str_g("pdispVal")      [attr_g(getIsAttributeTypeHandler(ATTR_ANY))])
                   [!If_IsREF]
               << (WithClassType(str_g("pdispVal"))
               <<  WithEnumType(str_g("lVal")))
                   [If_IsREF];

            AttributeVTReturn =
                (("(" << $(0) << "!=VARIANT_FALSE)")[attr_g(getIsAttributeTypeHandler(ATTR_BOOLEAN))]
                << $(0)                             [attr_g(getIsAttributeTypeHandler(ATTR_SBYTE))]
                << $(0)                             [attr_g(getIsAttributeTypeHandler(ATTR_BYTE))]
                << $(0)                             [attr_g(getIsAttributeTypeHandler(ATTR_CHAR))]
                << $(0)                             [attr_g(getIsAttributeTypeHandler(ATTR_ANSICHAR))]
                << $(0)                             [attr_g(getIsAttributeTypeHandler(ATTR_WIDECHAR))]
                << $(0)                             [attr_g(getIsAttributeTypeHandler(ATTR_INT))]
                << $(0)                             [attr_g(getIsAttributeTypeHandler(ATTR_UINT))]
                << $(0)                             [attr_g(getIsAttributeTypeHandler(ATTR_INT16))]
                << $(0)                             [attr_g(getIsAttributeTypeHandler(ATTR_UINT16))]
                << $(0)                             [attr_g(getIsAttributeTypeHandler(ATTR_INT32))]
                << $(0)                             [attr_g(getIsAttributeTypeHandler(ATTR_UINT32))]
                << $(0)                             [attr_g(getIsAttributeTypeHandler(ATTR_INT64))]
                << $(0)                             [attr_g(getIsAttributeTypeHandler(ATTR_UINT64))]
                << $(0)                             [attr_g(getIsAttributeTypeHandler(ATTR_SINGLE))]
                << $(0)                             [attr_g(getIsAttributeTypeHandler(ATTR_DOUBLE))]
                << ("std::basic_string<TCHAR>(" << $(0) << " ? " << $(0) << " : _T(\"\"))")
                                                    [attr_g(getIsAttributeTypeHandler(ATTR_STRING))]
                << ("std::string(" << $(0) << " ? " << $(0) << " : \"\")")
                                                    [attr_g(getIsAttributeTypeHandler(ATTR_ANSISTRING))]
                << ("std::wstring(" << $(0) << " ? " << $(0) << " : L\"\")")
                                                    [attr_g(getIsAttributeTypeHandler(ATTR_WIDESTRING))]
                << ("std::basic_string<TCHAR>(" << $(0) << " ? " << $(0) << " : _T(\"\"))")
                                                    [attr_g(getIsAttributeTypeHandler(ATTR_TEXT))]
                << $(0)                             [attr_g(getIsAttributeTypeHandler(ATTR_TIME))]
                << $(0)                             [attr_g(getIsAttributeTypeHandler(ATTR_DATE))]
                << $(0)                             [attr_g(getIsAttributeTypeHandler(ATTR_ANY))])
                   [!If_IsREF]
                << ( "word::"
                  << GotoREF
                     (
                         rel_g(getRelationSourceHandler(KIND_ALIAS))
                     )
                  << "(" << $(0) << ")" )
                   [If_IsREF];

            GotoReturn =
                   (+$(0))[If_IsAUTO][attr0,attrN];

            MethodClassName =
                   (+attr_g(getAttributeNameHandler(KIND_ALIAS)))
                   [If_IsCONTEXTUAL && If_IsREF && !If_IsAUTO && !If_IsID][attr0,attrN];  

            ParameterSize =
                   size_g(set_g((attr0,attrN), If_IsParameter));

            ParameterIndex =
                   math_g( cast_g<size_t>(ParameterSize) - cast_g<size_t>(index_g()+1) );

            AttributeVTRelease =
                   ("SysFreeString(" << $(0) << ")")[attr_g(getIsAttributeTypeHandler(ATTR_STRING))]
                << ("SysFreeString(" << $(0) << ")")[attr_g(getIsAttributeTypeHandler(ATTR_TEXT))];

            GotoREF =
                   $(0)[relationsByAttr(FILTER_TARGET)];

            ProjectName =
                call_g(getWorkspaceNameHandler());

            ListArray =
                   $(0)[If_IsArray]
                       [entitiesByRel(FILTER_TARGET|FILTER_CONTEXTUAL)]
                       [relationsByEnt(FILTER_SOURCE)];

            GotoIndexArray =
                   (+$(0))[If_IsID][attr0,attrN];

            GotoElementArray =
                   (+$(0))[!If_IsID && !If_IsCONTEXTUAL][attr0,attrN];

            ArrayClassName =
                   (+attr_g(getAttributeNameHandler(KIND_ALIAS)))
                   [If_IsCONTEXTUAL && If_IsREF && !If_IsAUTO && !If_IsID][attr0,attrN]; 

            GotoBase =
                   (+$(0))[If_IsBASE][attr0,attrN];

            BaseName =
                   GotoBase(AttributeType);

            EnumName =
                    ent_g(getEntityNameHandler(KIND_ALIAS));

            ListEnum =
                   $(0)[If_IsEnum][ent0, entN];

            ListEnumKey =
                   $(0)[If_IsEnumKey][attr0, attrN];

            EnumKeyName =
                   attr_g(getAttributeNameHandler(KIND_ALIAS));

            EnumValue =
                   attr_g(getAttributeDefaultHandler());

            WithEnumType =
                   $(0)[If_IsEnum]
                       [entitiesByRel(FILTER_SOURCE)]
                       [relationsByAttr(FILTER_TARGET)];

            WithClassType =
                   $(0)[If_IsClass]
                       [entitiesByRel(FILTER_SOURCE)]
                       [relationsByAttr(FILTER_TARGET)];

            ListConstant =
                   $(0)[If_IsConstant][attr0, attrN];

            ConstantName =
                   AttributeName;

            ConstantType =
                   AttributeType;

            ConstantValue =
                   attr_g(getAttributeDefaultHandler());

			If_IsID =
				   attr_g(getIsAttributeModifierHandler(ATTR_ID));

			If_IsREF =
				   attr_g(getIsAttributeModifierHandler(ATTR_REF));

			If_IsCONTEXTUAL =
				   attr_g(getIsAttributeModifierHandler(ATTR_CONTEXTUAL));

			If_IsAUTO =
				   attr_g(getIsAttributeModifierHandler(ATTR_AUTO)); 

			If_IsReadOnly =
				   attr_g(getIsAttributeModifierHandler(ATTR_CONST));

			If_IsBASE =
				   attr_g(getIsAttributeModifierHandler(ATTR_BASE));

			If_IsSTATIC =
				   attr_g(getIsAttributeModifierHandler(ATTR_STATIC));

			If_IsVIRTUAL =
				   attr_g(getIsAttributeModifierHandler(ATTR_VIRTUAL));

			If_IsClass =
				   ent_g(getIsEntityClassHandler(ENTITY_DATA)) && !Has_Contextual;

			If_IsMethod =
				   ent_g(getIsEntityClassHandler(ENTITY_FUNCTION)) && Has_Contextual;

			If_IsArray =
				   ent_g(getIsEntityClassHandler(ENTITY_DATA)) && Has_Contextual;

			If_IsEnum =
				   ent_g(getIsEntityClassHandler(ENTITY_ENUMERATION));

            If_IsAttribute =
                   !If_IsID && !If_IsBASE && !If_IsConstant;

            If_IsParameter =
                   !If_IsAUTO && !If_IsID && !If_IsCONTEXTUAL && !If_IsBASE;

            If_IsAttributeVTAlloc =
                   attr_g(getIsAttributeTypeHandler(ATTR_STRING))
                || attr_g(getIsAttributeTypeHandler(ATTR_TEXT));

            If_IsEnumKey =
                   If_IsSTATIC && If_IsReadOnly;

            If_IsConstant =
                   If_IsSTATIC && If_IsReadOnly;

            If_IsProject =
                   call_g(getIsWorkspaceTypeHandler(WRK_PROJECT));

            Has_Return =
                   has_g(0, set_g((attr0,attrN), If_IsAUTO), gt_g());

            Has_Parameter =
                   has_g(0, set_g((attr0,attrN), If_IsParameter), gt_g());

            Has_Contextual =
                   has_g(0, set_g((attr0,attrN), If_IsCONTEXTUAL), gt_g());

            Has_Base =
                   has_g(0, set_g((attr0,attrN), If_IsBASE), gt_g());

            Has_Static =
                   has_g(0, set_g((attr0,attrN), If_IsSTATIC), gt_g());

            Has_DefaultValue =
                   attr_g(getHasAttributeDefaultHandler());

        }

    }

}
