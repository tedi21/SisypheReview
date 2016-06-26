#ifndef _SIMPLE_WORD_COMMON_GENERATOR_HPP_
#define _SIMPLE_WORD_COMMON_GENERATOR_HPP_

#include <iostream>
#include <string>
#include "EtatHandler.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

		struct SimpleWordCommonGenerator
		: public EtatHandler {

			format<gen_info>    CreateHeader,
                                CreateHPPDefine,
                                CreateHPPEndDefine,
                                CreateNamespace,
                                CreateEndNamespace,
                                ListClass,
                                ClassName,
                                ListAttribute,
                                AttributeName,
                                AttributeType,
                                AttributeTypeParam,
                                AttributeParamName,
                                ListMethod,
                                MethodName,
                                ReturnType,
                                ListParameter,
                                CreateParameters,
                                ParameterType,
                                ParameterName,
                                AttributeVTType,
                                AttributeVTVal,
                                VariantVal,
                                AttributeVTReturn,
                                MethodClassName,
                                GotoReturn,
                                ParameterSize,
                                ParameterIndex,
                                AttributeVTRelease,
                                GotoREF,
                                ProjectName,
                                ListArray,
                                GotoIndexArray,
                                GotoElementArray,
                                ArrayClassName,
                                GotoBase,
                                BaseName,
                                ListEnum,
                                EnumName,
                                ListEnumKey,
                                EnumKeyName, 
                                EnumValue,
                                WithEnumType,
                                WithClassType,
                                ListConstant,
                                ConstantName,
                                ConstantType,
                                ConstantValue;

			condition<gen_info> If_IsID,
								If_IsREF,
								If_IsAUTO,
                                If_IsCONTEXTUAL,
                                If_IsBASE,
								If_IsReadOnly,
                                If_IsSTATIC,
                                If_IsVIRTUAL,
								If_IsClass,
								If_IsMethod,
                                If_IsEnum,
                                If_IsAttribute,
                                If_IsParameter,
                                If_IsAttributeVTAlloc,
                                If_IsEnumKey,
                                If_IsConstant,
                                If_IsProject,
                                If_IsArray,
                                Has_Return,
                                Has_Parameter,
                                Has_Contextual,
                                Has_Base,
                                Has_Static,
                                Has_DefaultValue;

			SimpleWordCommonGenerator();

		};

	}
}

#endif //  _SIMPLE_WORD_COMMON_GENERATOR_HPP_
