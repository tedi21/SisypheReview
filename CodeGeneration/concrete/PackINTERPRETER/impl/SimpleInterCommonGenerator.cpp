#include "SimpleInterCommonGenerator.hpp"

namespace dsg {

	namespace generator {

        const UniChar* SimpleInterCommonGenerator::CONTENT_TYPE_GLOBAL              = L"Global";
        const UniChar* SimpleInterCommonGenerator::CONTENT_TYPE_GLOBAL_BODY         = L"Global-body";
        const UniChar* SimpleInterCommonGenerator::CONTENT_TYPE_GLOBALINCLUSION     = L"Global-inclusion";
        const UniChar* SimpleInterCommonGenerator::CONTENT_TYPE_DECLARATION         = L"Declaration";
        const UniChar* SimpleInterCommonGenerator::CONTENT_TYPE_REGISTER            = L"Register";
        const UniChar* SimpleInterCommonGenerator::CONTENT_TYPE_UNREGISTER          = L"Unregister";
        const UniChar* SimpleInterCommonGenerator::CONTENT_TYPE_IMPLEMENTATION      = L"Implementation";
        const UniChar* SimpleInterCommonGenerator::CONTENT_TYPE_IMPLEMENTATIONBODY  = L"Implementation-body";
        const UniChar* SimpleInterCommonGenerator::CONTENT_TYPE_DECLARATIONBODY     = L"Declaration-body";
        const UniChar* SimpleInterCommonGenerator::CONTENT_TYPE_INITIALIZATIONBODY  = L"Initialization-body";
        const UniChar* SimpleInterCommonGenerator::CONTENT_TYPE_DESTRUCTIONBODY     = L"Destruction-body";
        const UniChar* SimpleInterCommonGenerator::CONTENT_TYPE_COPYBODY            = L"Copy-body";
        const UniChar* SimpleInterCommonGenerator::CONTENT_TYPE_VALUEBODY           = L"Value-body";

        SimpleInterCommonGenerator::SimpleInterCommonGenerator() {

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
                   line_g(1) << "NAMESPACE_BEGIN(" << $(0) << ")";

			CreateEndNamespace =
                   line_g(1) << "NAMESPACE_END";

            ListFile =
                   $(0)[file0, fileN];

            Dependences =
                    unique_g(set_g((ent0, entN), If_IsClass)
                  * (unique_g((set_g(relationsByEnt(FILTER_SOURCE) * entitiesByRel(FILTER_TARGET|FILTER_CONTEXTUAL), If_IsMethod)
                  * (set_g((attr0, attrN), If_IsREF && (If_IsParameter || If_IsAUTO))
                  * (relationsByAttr(FILTER_TARGET)
                  * (entitiesByRel(FILTER_SOURCE)))))) - current_g<ent_context>()));

            ListDependence =
                    $(0)[Dependences];

            DependenceName =
                    ent_g(getEntityNameHandler(KIND_ALIAS));

            ListClass =
                   $(0)[If_IsClass][ent0, entN];

            ClassName =
                    ent_g(getEntityNameHandler(KIND_ALIAS));

            ListAttribute =
                   $(0)[If_IsAttribute][attr0, attrN];

            AttributeName =
                    attr_g(getAttributeNameHandler(KIND_ALIAS))
                                            [attr_g(getHasAttributeAliasHandler())]
                 << upper_g( attr_g(getAttributeNameHandler(KIND_NAME)), 0, 1)
                                            [else_g()];

            InternalAttributeName =
                    attr_g(getAttributeNameHandler(KIND_NAME));

            InternalAttributeType =
                  (str_g("bool")            [attr_g(getIsAttributeTypeHandler(ATTR_BOOLEAN))]
                << str_g("char")            [attr_g(getIsAttributeTypeHandler(ATTR_SBYTE))]
                << str_g("unsigned char")   [attr_g(getIsAttributeTypeHandler(ATTR_BYTE))]
                << str_g("typename EncodingT::char_t")[attr_g(getIsAttributeTypeHandler(ATTR_CHAR))]
                << str_g("typename ansi::char_t")     [attr_g(getIsAttributeTypeHandler(ATTR_ANSICHAR))]
                << str_g("typename ucs::char_t")      [attr_g(getIsAttributeTypeHandler(ATTR_WIDECHAR))]
                << str_g("int")             [attr_g(getIsAttributeTypeHandler(ATTR_INT))]
                << str_g("unsigned int")    [attr_g(getIsAttributeTypeHandler(ATTR_UINT))]
                << str_g("short")           [attr_g(getIsAttributeTypeHandler(ATTR_INT16))]
                << str_g("unsigned short")  [attr_g(getIsAttributeTypeHandler(ATTR_UINT16))]
                << str_g("long")            [attr_g(getIsAttributeTypeHandler(ATTR_INT32))]
                << str_g("unsigned long")   [attr_g(getIsAttributeTypeHandler(ATTR_UINT32))]
                << str_g("long long")       [attr_g(getIsAttributeTypeHandler(ATTR_INT64))]
                << str_g("unsigned long long")[attr_g(getIsAttributeTypeHandler(ATTR_UINT64))]
                << str_g("float")           [attr_g(getIsAttributeTypeHandler(ATTR_SINGLE))]
                << str_g("double")          [attr_g(getIsAttributeTypeHandler(ATTR_DOUBLE))]
                << str_g("typename EncodingT::string_t")[attr_g(getIsAttributeTypeHandler(ATTR_STRING))]
                << str_g("typename ansi::string_t")     [attr_g(getIsAttributeTypeHandler(ATTR_ANSISTRING))]
                << str_g("typename ucs::string_t")      [attr_g(getIsAttributeTypeHandler(ATTR_WIDESTRING))]
                << str_g("typename EncodingT::string_t")[attr_g(getIsAttributeTypeHandler(ATTR_TEXT))]
                << str_g("time_t")          [attr_g(getIsAttributeTypeHandler(ATTR_TIME))]
                << str_g("time_t")          [attr_g(getIsAttributeTypeHandler(ATTR_DATE))]
                << str_g("void*")           [attr_g(getIsAttributeTypeHandler(ATTR_ANY))])
                   [!If_IsREF]
                << GotoREF
                   (
                       rel_g(getRelationSourceHandler(KIND_ALIAS))
                   )
                   [If_IsREF];

            AttributeType =
                   InternalAttributeType
                   [!If_IsARRAY]
                << (str_g("std::vector< ") << InternalAttributeType << str_g(" >"))
                   [If_IsARRAY];

            AttributeParamType =
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
                   ent_g(getEntityFunctionNameHandler(KIND_ALIAS))
                                                            [ent_g(getHasEntityAliasHandler())]
                << upper_g( ent_g(getEntityFunctionNameHandler(KIND_NAME)), 0, 1)
                                                            [else_g()];

            InternalMethodName =
                   ent_g(getEntityFunctionNameHandler(KIND_NAME));

            ListMethod =
                   $(0)[If_IsMethod]
                       [entitiesByRel(FILTER_TARGET|FILTER_CONTEXTUAL)]
                       [relationsByEnt(FILTER_SOURCE)];

            ReturnType =
                   str_g("void")[!Has_Return]
                << GotoReturn(AttributeType);

            ListParameter =
                   $(0)[set_g((attr0,attrN), If_IsParameter)];

            ListOutputParameter =
                   $(0)[set_g((attr0,attrN), If_IsOutputParameter)];

            ParameterType =
                   AttributeParamType    [attr_g(getIsAttributeModifierHandler(ATTR_CONST))]
                << (AttributeType << "&")[!attr_g(getIsAttributeModifierHandler(ATTR_CONST))];

            ParameterName =
                   lower_g(attr_g(getAttributeNameHandler(KIND_ALIAS)), 0, 1);

            GotoReturn =
                   (+$(0))[If_IsAUTO][attr0,attrN];

            MethodClassName =
                   (+attr_g(getAttributeNameHandler(KIND_ALIAS)))
                   [If_IsCONTEXTUAL && If_IsREF && !If_IsAUTO && !If_IsID][attr0,attrN];  

            ParameterSize =
                   size_g(set_g((attr0,attrN), If_IsParameter));

            ParameterIndex =
                   math_g( cast_g<size_t>(ParameterSize) - cast_g<size_t>(index_g()+1) );

            GotoREF =
                   $(0)[relationsByAttr(FILTER_TARGET)];

            ProjectName =
                call_g(getWorkspaceNameHandler());

            ListArray =
                   $(0)[If_IsArrayEntity]
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

            PackageName =
                    ent_g(getEntityNameHandler(KIND_ALIAS));

            ListPackage =
                    $(0)[If_IsPackage]
                        [entitiesByRel(FILTER_TARGET)]
                        [relationsByEnt(FILTER_SOURCE)]
                        [ent0, entN];

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

            WithClassMethod =
                   $(0)[entitiesByRel(FILTER_SOURCE)]
                       [relationsByAttr(FILTER_TARGET)]
                       [If_IsCONTEXTUAL && If_IsREF && !If_IsAUTO && !If_IsID][attr0,attrN];

            ListConstant =
                   $(0)[If_IsConstant][attr0, attrN];

            ConstantName =
                   AttributeName;

            InternalConstantName =
                   InternalAttributeName;

            ConstantType =
                   AttributeType;

            ConstantValue =
                   attr_g(getAttributeDefaultHandler());

            InterpreterType =
                  (str_g("Bool<EncodingT>")     [attr_g(getIsAttributeTypeHandler(ATTR_BOOLEAN))]
                << str_g("Numeric<EncodingT>")  [attr_g(getIsAttributeTypeHandler(ATTR_SBYTE))]
                << str_g("Numeric<EncodingT>")  [attr_g(getIsAttributeTypeHandler(ATTR_BYTE))]
                << str_g("String<EncodingT>")   [attr_g(getIsAttributeTypeHandler(ATTR_CHAR))]
                << str_g("String<EncodingT>")   [attr_g(getIsAttributeTypeHandler(ATTR_ANSICHAR))]
                << str_g("String<EncodingT>")   [attr_g(getIsAttributeTypeHandler(ATTR_WIDECHAR))]
                << str_g("Numeric<EncodingT>")  [attr_g(getIsAttributeTypeHandler(ATTR_INT))]
                << str_g("Numeric<EncodingT>")  [attr_g(getIsAttributeTypeHandler(ATTR_UINT))]
                << str_g("Numeric<EncodingT>")  [attr_g(getIsAttributeTypeHandler(ATTR_INT16))]
                << str_g("Numeric<EncodingT>")  [attr_g(getIsAttributeTypeHandler(ATTR_UINT16))]
                << str_g("Numeric<EncodingT>")  [attr_g(getIsAttributeTypeHandler(ATTR_INT32))]
                << str_g("Numeric<EncodingT>")  [attr_g(getIsAttributeTypeHandler(ATTR_UINT32))]
                << str_g("Numeric<EncodingT>")  [attr_g(getIsAttributeTypeHandler(ATTR_INT64))]
                << str_g("Numeric<EncodingT>")  [attr_g(getIsAttributeTypeHandler(ATTR_UINT64))]
                << str_g("Numeric<EncodingT>")  [attr_g(getIsAttributeTypeHandler(ATTR_SINGLE))]
                << str_g("Numeric<EncodingT>")  [attr_g(getIsAttributeTypeHandler(ATTR_DOUBLE))]
                << str_g("String<EncodingT>")   [attr_g(getIsAttributeTypeHandler(ATTR_STRING))]
                << str_g("String<EncodingT>")   [attr_g(getIsAttributeTypeHandler(ATTR_ANSISTRING))]
                << str_g("String<EncodingT>")   [attr_g(getIsAttributeTypeHandler(ATTR_WIDESTRING))]
                << str_g("String<EncodingT>")   [attr_g(getIsAttributeTypeHandler(ATTR_TEXT))]
                << str_g("")                    [attr_g(getIsAttributeTypeHandler(ATTR_TIME))]
                << str_g("")                    [attr_g(getIsAttributeTypeHandler(ATTR_DATE))]
                << str_g("")                    [attr_g(getIsAttributeTypeHandler(ATTR_ANY))])
                   [!If_IsREF]
                << GotoREF
                   (
                       rel_g(getRelationSourceHandler(KIND_ALIAS)) << "Interpreter<EncodingT>"
                   )
                   [If_IsREF];

            InterpreterCheck =
                    ((str_g("check_bool")               [attr_g(getIsAttributeTypeHandler(ATTR_BOOLEAN))]
                  << str_g("check_numeric_i")           [attr_g(getIsAttributeTypeHandler(ATTR_SBYTE))]
                  << str_g("check_numeric_i")           [attr_g(getIsAttributeTypeHandler(ATTR_BYTE))]
                  << str_g("check_char<EncodingT>")     [attr_g(getIsAttributeTypeHandler(ATTR_CHAR))]
                  << str_g("check_char<ansi>")          [attr_g(getIsAttributeTypeHandler(ATTR_ANSICHAR))]
                  << str_g("check_char<ucs>")           [attr_g(getIsAttributeTypeHandler(ATTR_WIDECHAR))]
                  << str_g("check_numeric_i")           [attr_g(getIsAttributeTypeHandler(ATTR_INT))]
                  << str_g("check_numeric_i")           [attr_g(getIsAttributeTypeHandler(ATTR_UINT))]
                  << str_g("check_numeric_i")           [attr_g(getIsAttributeTypeHandler(ATTR_INT16))]
                  << str_g("check_numeric_i")           [attr_g(getIsAttributeTypeHandler(ATTR_UINT16))]
                  << str_g("check_numeric_i")           [attr_g(getIsAttributeTypeHandler(ATTR_INT32))]
                  << str_g("check_numeric_i")           [attr_g(getIsAttributeTypeHandler(ATTR_UINT32))]
                  << str_g("check_numeric_i")           [attr_g(getIsAttributeTypeHandler(ATTR_INT64))]
                  << str_g("check_numeric_i")           [attr_g(getIsAttributeTypeHandler(ATTR_UINT64))]
                  << str_g("check_numeric_d")           [attr_g(getIsAttributeTypeHandler(ATTR_SINGLE))]
                  << str_g("check_numeric_d")           [attr_g(getIsAttributeTypeHandler(ATTR_DOUBLE))]
                  << str_g("check_string<EncodingT>")   [attr_g(getIsAttributeTypeHandler(ATTR_STRING))]
                  << str_g("check_string<ansi>")        [attr_g(getIsAttributeTypeHandler(ATTR_ANSISTRING))]
                  << str_g("check_string<ucs>")         [attr_g(getIsAttributeTypeHandler(ATTR_WIDESTRING))]
                  << str_g("check_string<EncodingT>")   [attr_g(getIsAttributeTypeHandler(ATTR_TEXT))]
                  << str_g("")                          [attr_g(getIsAttributeTypeHandler(ATTR_TIME))]
                  << str_g("")                          [attr_g(getIsAttributeTypeHandler(ATTR_DATE))]
                  << str_g("")                          [attr_g(getIsAttributeTypeHandler(ATTR_ANY))])
                     [!If_IsREF]
                  << GotoREF
                     (
                         str_g("check_") << rel_g(getRelationSourceHandler(KIND_ALIAS))
                     )
                     [If_IsREF])
                     [!If_IsARRAY]
                  << str_g("check_array")
                     [If_IsARRAY];

            InterpreterCheckFunction =
                    (str_g("check_bool<EncodingT>")                     [attr_g(getIsAttributeTypeHandler(ATTR_BOOLEAN))]
                  << str_g("check_numeric_i<EncodingT, char>")          [attr_g(getIsAttributeTypeHandler(ATTR_SBYTE))]
                  << str_g("check_numeric_i<EncodingT, unsigned char>") [attr_g(getIsAttributeTypeHandler(ATTR_BYTE))]
                  << str_g("check_string<EncodingT, EncodingT>")        [attr_g(getIsAttributeTypeHandler(ATTR_CHAR))]
                  << str_g("check_string<ansi ,EncodingT>")             [attr_g(getIsAttributeTypeHandler(ATTR_ANSICHAR))]
                  << str_g("check_string<ucs, EncodingT>")              [attr_g(getIsAttributeTypeHandler(ATTR_WIDECHAR))]
                  << str_g("check_numeric_i<EncodingT, int>")           [attr_g(getIsAttributeTypeHandler(ATTR_INT))]
                  << str_g("check_numeric_i<EncodingT, unsigned int>")  [attr_g(getIsAttributeTypeHandler(ATTR_UINT))]
                  << str_g("check_numeric_i<EncodingT, short>")         [attr_g(getIsAttributeTypeHandler(ATTR_INT16))]
                  << str_g("check_numeric_i<EncodingT, unsigned short>")[attr_g(getIsAttributeTypeHandler(ATTR_UINT16))]
                  << str_g("check_numeric_i<EncodingT, long>")          [attr_g(getIsAttributeTypeHandler(ATTR_INT32))]
                  << str_g("check_numeric_i<EncodingT, unsigned long>") [attr_g(getIsAttributeTypeHandler(ATTR_UINT32))]
                  << str_g("check_numeric_i<EncodingT, long long>")     [attr_g(getIsAttributeTypeHandler(ATTR_INT64))]
                  << str_g("check_numeric_i<EncodingT, unsigned long long>")[attr_g(getIsAttributeTypeHandler(ATTR_UINT64))]
                  << str_g("check_numeric_d<EncodingT, float>")         [attr_g(getIsAttributeTypeHandler(ATTR_SINGLE))]
                  << str_g("check_numeric_d<EncodingT, double>")        [attr_g(getIsAttributeTypeHandler(ATTR_DOUBLE))]
                  << str_g("check_string<EncodingT, EncodingT>")        [attr_g(getIsAttributeTypeHandler(ATTR_STRING))]
                  << str_g("check_string<ansi, EncodingT>")             [attr_g(getIsAttributeTypeHandler(ATTR_ANSISTRING))]
                  << str_g("check_string<ucs, EncodingT>")              [attr_g(getIsAttributeTypeHandler(ATTR_WIDESTRING))]
                  << str_g("check_string<EncodingT, EncodingT>")        [attr_g(getIsAttributeTypeHandler(ATTR_TEXT))]
                  << str_g("")                                          [attr_g(getIsAttributeTypeHandler(ATTR_TIME))]
                  << str_g("")                                          [attr_g(getIsAttributeTypeHandler(ATTR_DATE))]
                  << str_g("")                                          [attr_g(getIsAttributeTypeHandler(ATTR_ANY))])
                     [!If_IsREF]
                  << GotoREF
                     (
                         str_g("check_") << rel_g(getRelationSourceHandler(KIND_ALIAS)) << str_g("<EncodingT>")
                     )
                     [If_IsREF];

            InterpreterReset =
                    ((str_g("reset_bool")               [attr_g(getIsAttributeTypeHandler(ATTR_BOOLEAN))]
                  << str_g("reset_numeric_i")           [attr_g(getIsAttributeTypeHandler(ATTR_SBYTE))]
                  << str_g("reset_numeric_i")           [attr_g(getIsAttributeTypeHandler(ATTR_BYTE))]
                  << str_g("reset_string<EncodingT>")   [attr_g(getIsAttributeTypeHandler(ATTR_CHAR))]
                  << str_g("reset_string<ansi>")        [attr_g(getIsAttributeTypeHandler(ATTR_ANSICHAR))]
                  << str_g("reset_string<ucs>")         [attr_g(getIsAttributeTypeHandler(ATTR_WIDECHAR))]
                  << str_g("reset_numeric_i")           [attr_g(getIsAttributeTypeHandler(ATTR_INT))]
                  << str_g("reset_numeric_i")           [attr_g(getIsAttributeTypeHandler(ATTR_UINT))]
                  << str_g("reset_numeric_i")           [attr_g(getIsAttributeTypeHandler(ATTR_INT16))]
                  << str_g("reset_numeric_i")           [attr_g(getIsAttributeTypeHandler(ATTR_UINT16))]
                  << str_g("reset_numeric_i")           [attr_g(getIsAttributeTypeHandler(ATTR_INT32))]
                  << str_g("reset_numeric_i")           [attr_g(getIsAttributeTypeHandler(ATTR_UINT32))]
                  << str_g("reset_numeric_i")           [attr_g(getIsAttributeTypeHandler(ATTR_INT64))]
                  << str_g("reset_numeric_i")           [attr_g(getIsAttributeTypeHandler(ATTR_UINT64))]
                  << str_g("reset_numeric_d")           [attr_g(getIsAttributeTypeHandler(ATTR_SINGLE))]
                  << str_g("reset_numeric_d")           [attr_g(getIsAttributeTypeHandler(ATTR_DOUBLE))]
                  << str_g("reset_string<EncodingT>")   [attr_g(getIsAttributeTypeHandler(ATTR_STRING))]
                  << str_g("reset_string<ansi>")        [attr_g(getIsAttributeTypeHandler(ATTR_ANSISTRING))]
                  << str_g("reset_string<ucs>")         [attr_g(getIsAttributeTypeHandler(ATTR_WIDESTRING))]
                  << str_g("reset_string<EncodingT>")   [attr_g(getIsAttributeTypeHandler(ATTR_TEXT))]
                  << str_g("")                          [attr_g(getIsAttributeTypeHandler(ATTR_TIME))]
                  << str_g("")                          [attr_g(getIsAttributeTypeHandler(ATTR_DATE))]
                  << str_g("")                          [attr_g(getIsAttributeTypeHandler(ATTR_ANY))])
                     [!If_IsREF]
                  << GotoREF
                     (
                         str_g("reset_") << rel_g(getRelationSourceHandler(KIND_ALIAS))
                     )
                     [If_IsREF])
                    [!If_IsARRAY]
                 << str_g("reset_array")
                    [If_IsARRAY];

            InterpreterResetFunction =
                    (str_g("reset_bool<EncodingT>")                       [attr_g(getIsAttributeTypeHandler(ATTR_BOOLEAN))]
                  << str_g("reset_numeric_i<EncodingT, char>")            [attr_g(getIsAttributeTypeHandler(ATTR_SBYTE))]
                  << str_g("reset_numeric_i<EncodingT, unsigned char>")   [attr_g(getIsAttributeTypeHandler(ATTR_BYTE))]
                  << str_g("reset_string<EncodingT, EncodingT>")          [attr_g(getIsAttributeTypeHandler(ATTR_CHAR))]
                  << str_g("reset_string<ansi, EncodingT>")               [attr_g(getIsAttributeTypeHandler(ATTR_ANSICHAR))]
                  << str_g("reset_string<ucs, EncodingT>")                [attr_g(getIsAttributeTypeHandler(ATTR_WIDECHAR))]
                  << str_g("reset_numeric_i<EncodingT, int>")             [attr_g(getIsAttributeTypeHandler(ATTR_INT))]
                  << str_g("reset_numeric_i<EncodingT, unsigned int>")    [attr_g(getIsAttributeTypeHandler(ATTR_UINT))]
                  << str_g("reset_numeric_i<EncodingT, short>")           [attr_g(getIsAttributeTypeHandler(ATTR_INT16))]
                  << str_g("reset_numeric_i<EncodingT, unsigned short>")  [attr_g(getIsAttributeTypeHandler(ATTR_UINT16))]
                  << str_g("reset_numeric_i<EncodingT, long>")            [attr_g(getIsAttributeTypeHandler(ATTR_INT32))]
                  << str_g("reset_numeric_i<EncodingT, unsigned long>")   [attr_g(getIsAttributeTypeHandler(ATTR_UINT32))]
                  << str_g("reset_numeric_i<EncodingT, long long>")       [attr_g(getIsAttributeTypeHandler(ATTR_INT64))]
                  << str_g("reset_numeric_i<EncodingT, unsigned long long>")[attr_g(getIsAttributeTypeHandler(ATTR_UINT64))]
                  << str_g("reset_numeric_d<EncodingT, float>")           [attr_g(getIsAttributeTypeHandler(ATTR_SINGLE))]
                  << str_g("reset_numeric_d<EncodingT, double>")          [attr_g(getIsAttributeTypeHandler(ATTR_DOUBLE))]
                  << str_g("reset_string<EncodingT, EncodingT>")          [attr_g(getIsAttributeTypeHandler(ATTR_STRING))]
                  << str_g("reset_string<ansi, EncodingT>")               [attr_g(getIsAttributeTypeHandler(ATTR_ANSISTRING))]
                  << str_g("reset_string<ucs, EncodingT>")                [attr_g(getIsAttributeTypeHandler(ATTR_WIDESTRING))]
                  << str_g("reset_string<EncodingT, EncodingT>")          [attr_g(getIsAttributeTypeHandler(ATTR_TEXT))]
                  << str_g("")                                            [attr_g(getIsAttributeTypeHandler(ATTR_TIME))]
                  << str_g("")                                            [attr_g(getIsAttributeTypeHandler(ATTR_DATE))]
                  << str_g("")                                            [attr_g(getIsAttributeTypeHandler(ATTR_ANY))])
                     [!If_IsREF]
                  << GotoREF
                     (
                         str_g("reset_") << rel_g(getRelationSourceHandler(KIND_ALIAS)) << str_g("<EncodingT>")
                     )
                     [If_IsREF];

            InterpreterValue =
                  (str_g("value")     [attr_g(getIsAttributeTypeHandler(ATTR_BOOLEAN))]
                << str_g("LLvalue")   [attr_g(getIsAttributeTypeHandler(ATTR_SBYTE))]
                << str_g("LLvalue")   [attr_g(getIsAttributeTypeHandler(ATTR_BYTE))]
                << str_g("value")     [attr_g(getIsAttributeTypeHandler(ATTR_CHAR))]
                << str_g("value")     [attr_g(getIsAttributeTypeHandler(ATTR_ANSICHAR))]
                << str_g("value")     [attr_g(getIsAttributeTypeHandler(ATTR_WIDECHAR))]
                << str_g("LLvalue")   [attr_g(getIsAttributeTypeHandler(ATTR_INT))]
                << str_g("LLvalue")   [attr_g(getIsAttributeTypeHandler(ATTR_UINT))]
                << str_g("LLvalue")   [attr_g(getIsAttributeTypeHandler(ATTR_INT16))]
                << str_g("LLvalue")   [attr_g(getIsAttributeTypeHandler(ATTR_UINT16))]
                << str_g("LLvalue")   [attr_g(getIsAttributeTypeHandler(ATTR_INT32))]
                << str_g("LLvalue")   [attr_g(getIsAttributeTypeHandler(ATTR_UINT32))]
                << str_g("LLvalue")   [attr_g(getIsAttributeTypeHandler(ATTR_INT64))]
                << str_g("LLvalue")   [attr_g(getIsAttributeTypeHandler(ATTR_UINT64))]
                << str_g("Dvalue")    [attr_g(getIsAttributeTypeHandler(ATTR_SINGLE))]
                << str_g("Dvalue")    [attr_g(getIsAttributeTypeHandler(ATTR_DOUBLE))]
                << str_g("value")     [attr_g(getIsAttributeTypeHandler(ATTR_STRING))]
                << str_g("value")     [attr_g(getIsAttributeTypeHandler(ATTR_ANSISTRING))]
                << str_g("value")     [attr_g(getIsAttributeTypeHandler(ATTR_WIDESTRING))]
                << str_g("value")     [attr_g(getIsAttributeTypeHandler(ATTR_TEXT))]
                << str_g("")          [attr_g(getIsAttributeTypeHandler(ATTR_TIME))]
                << str_g("")          [attr_g(getIsAttributeTypeHandler(ATTR_DATE))]
                << str_g("")          [attr_g(getIsAttributeTypeHandler(ATTR_ANY))])
                   [!If_IsREF]
                << GotoREF
                   (
                       str_g("value")
                   )
                   [If_IsREF];

            ParameterPassing =
                   (($(0)                   [attr_g(getIsAttributeTypeHandler(ATTR_BOOLEAN))]
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
                  << ($(0) << ".c_str()")   [attr_g(getIsAttributeTypeHandler(ATTR_STRING))]
                  << ($(0) << ".c_str()")   [attr_g(getIsAttributeTypeHandler(ATTR_ANSISTRING))]
                  << ($(0) << ".c_str()")   [attr_g(getIsAttributeTypeHandler(ATTR_WIDESTRING))]
                  << ($(0) << ".c_str()")   [attr_g(getIsAttributeTypeHandler(ATTR_TEXT))]
                  << $(0)                   [attr_g(getIsAttributeTypeHandler(ATTR_TIME))]
                  << $(0)                   [attr_g(getIsAttributeTypeHandler(ATTR_DATE))]
                  << $(0)                   [attr_g(getIsAttributeTypeHandler(ATTR_ANY))])
                     [!If_IsREF]
                  << $(0)
                     [If_IsREF])
                     [!If_IsARRAY]
                  << ($(0) << ".data()")
                     [If_IsARRAY];

            ListClassOrEnum =
                   $(0)[If_IsClass || If_IsEnum][ent0, entN];

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

            If_IsARRAY =
                   attr_g(getIsAttributeModifierHandler(ATTR_ARRAY));

			If_IsClass =
				   ent_g(getIsEntityClassHandler(ENTITY_DATA)) && !Has_Contextual;

			If_IsMethod =
				   ent_g(getIsEntityClassHandler(ENTITY_FUNCTION)) && Has_Contextual;

            If_IsConstMethod =
                   ent_g(getIsEntityClassHandler(ENTITY_FUNCTION)) && Has_ConstContextual;

            If_IsStaticMethod =
                   ent_g(getIsEntityClassHandler(ENTITY_FUNCTION)) && Has_StaticContextual;

            If_IsStaticConstMethod =
                   ent_g(getIsEntityClassHandler(ENTITY_FUNCTION)) && Has_StaticConstContextual;

            If_IsArrayEntity =
				   ent_g(getIsEntityClassHandler(ENTITY_DATA)) && Has_Contextual;

			If_IsEnum =
				   ent_g(getIsEntityClassHandler(ENTITY_ENUMERATION));

            If_IsPackage =
                   ent_g(getIsEntityClassHandler(ENTITY_PACKAGE));

            If_IsAttribute =
                   !If_IsID && !If_IsBASE && !If_IsConstant;

            If_IsParameter =
                   !If_IsAUTO && !If_IsID && !If_IsCONTEXTUAL && !If_IsBASE;

            If_IsOutputParameter =
                   !If_IsAUTO && !If_IsID && !If_IsCONTEXTUAL && !If_IsBASE && !If_IsReadOnly;

            If_IsEnumKey =
                   If_IsSTATIC && If_IsReadOnly;

            If_IsConstant =
                   If_IsSTATIC && If_IsReadOnly;

            If_IsProject =
                   call_g(getIsWorkspaceTypeHandler(WRK_PROJECT));

            If_IsPointerEntity =
                   has_g(0, set_g((attr0,attrN), If_IsVIRTUAL && If_IsID), gt_g());

            Has_Class =
                   has_g(0, set_g((ent0,entN), If_IsClass), gt_g());

            Has_Return =
                   has_g(0, set_g((attr0,attrN), If_IsAUTO), gt_g());

            Has_Parameter =
                   has_g(0, set_g((attr0,attrN), If_IsParameter), gt_g());

            Has_OutputParameter =
                   has_g(0, set_g((attr0,attrN), If_IsOutputParameter), gt_g());

            Has_Contextual =
                   has_g(0, set_g((attr0,attrN), If_IsCONTEXTUAL), gt_g());

            Has_ConstContextual =
                   has_g(0, set_g((attr0,attrN), If_IsCONTEXTUAL && If_IsReadOnly), gt_g());

            Has_StaticContextual =
                   has_g(0, set_g((attr0,attrN), If_IsCONTEXTUAL && If_IsSTATIC), gt_g());

            Has_StaticConstContextual =
                   has_g(0, set_g((attr0,attrN), If_IsCONTEXTUAL && If_IsSTATIC && If_IsReadOnly), gt_g());

            Has_Base =
                   has_g(0, set_g((attr0,attrN), If_IsBASE), gt_g());

            Has_Static =
                   has_g(0, set_g((attr0,attrN), If_IsSTATIC), gt_g());

            Has_DefaultValue =
                   attr_g(getHasAttributeDefaultHandler());

            Has_DynamicMethod =
                   has_g(0, set_g(relationsByEnt(FILTER_SOURCE) * entitiesByRel(FILTER_TARGET|FILTER_CONTEXTUAL), !If_IsStaticMethod), gt_g());

            Has_Constant =
                   has_g(0, set_g((attr0,attrN), If_IsConstant), gt_g());

            Has_Attribute =
                   has_g(0, set_g((attr0,attrN), If_IsAttribute), gt_g());

            Has_Method =
                   has_g(0, set_g(relationsByEnt(FILTER_SOURCE) * entitiesByRel(FILTER_TARGET|FILTER_CONTEXTUAL), If_IsMethod), gt_g());

            Has_ClassOrEnum =
                   has_g(0, set_g((ent0,entN), If_IsClass || If_IsEnum), gt_g());

        }

    }

}
