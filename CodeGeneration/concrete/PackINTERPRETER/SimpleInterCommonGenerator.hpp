#ifndef _SIMPLE_INTER_COMMON_GENERATOR_HPP_
#define _SIMPLE_INTER_COMMON_GENERATOR_HPP_

#include <iostream>
#include <string>
#include "EtatHandler.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

        struct SimpleInterCommonGenerator
		: public EtatHandler {

            const static UniChar* CONTENT_TYPE_GLOBAL;
            const static UniChar* CONTENT_TYPE_GLOBAL_BODY;
            const static UniChar* CONTENT_TYPE_GLOBALINCLUSION;
            const static UniChar* CONTENT_TYPE_DECLARATION;
            const static UniChar* CONTENT_TYPE_REGISTER;
            const static UniChar* CONTENT_TYPE_UNREGISTER;
            const static UniChar* CONTENT_TYPE_IMPLEMENTATION;
            const static UniChar* CONTENT_TYPE_IMPLEMENTATIONBODY;
            const static UniChar* CONTENT_TYPE_DECLARATIONBODY;
            const static UniChar* CONTENT_TYPE_INITIALIZATIONBODY;
            const static UniChar* CONTENT_TYPE_DESTRUCTIONBODY;
            const static UniChar* CONTENT_TYPE_COPYBODY;
            const static UniChar* CONTENT_TYPE_VALUEBODY;

			format<gen_info>    CreateHeader,
                                CreateHPPDefine,
                                CreateHPPEndDefine,
                                CreateNamespace,
                                CreateEndNamespace,
                                ListFile,
                                ListClass,
                                ListDependence,
                                DependenceName,
                                ClassName,
                                ListAttribute,
                                AttributeName,
                                InternalAttributeName,
                                InternalAttributeType,
                                AttributeType,
                                AttributeParamType,
                                AttributeParamName,
                                ListMethod,
                                MethodName,
                                InternalMethodName,
                                ReturnType,
                                ListParameter,
                                ListOutputParameter,
                                ParameterType,
                                ParameterName,
                                MethodClassName,
                                GotoReturn,
                                ParameterSize,
                                ParameterIndex,
                                GotoREF,
                                ProjectName,
                                ListArray,
                                GotoIndexArray,
                                GotoElementArray,
                                ArrayClassName,
                                GotoBase,
                                BaseName,
                                PackageName,
                                ListPackage,
                                ListEnum,
                                EnumName,
                                ListEnumKey,
                                EnumKeyName, 
                                EnumValue,
                                WithEnumType,
                                WithClassType,
                                WithClassMethod,
                                ListConstant,
                                ConstantName,
                                InternalConstantName,
                                ConstantType,
                                ConstantValue,
                                InterpreterType,
                                InterpreterValue,
                                InterpreterCheck,
                                InterpreterCheckFunction,
                                InterpreterReset,
                                InterpreterResetFunction,
                                ParameterPassing,
                                ListClassOrEnum;

			condition<gen_info> If_IsID,
								If_IsREF,
								If_IsAUTO,
                                If_IsCONTEXTUAL,
                                If_IsBASE,
								If_IsReadOnly,
                                If_IsSTATIC,
                                If_IsVIRTUAL,
                                If_IsARRAY,
								If_IsClass,
								If_IsMethod,
                                If_IsConstMethod,
                                If_IsStaticMethod,
                                If_IsStaticConstMethod,
                                If_IsEnum,
                                If_IsPackage,
                                If_IsAttribute,
                                If_IsParameter,
                                If_IsOutputParameter,
                                If_IsEnumKey,
                                If_IsConstant,
                                If_IsProject,
                                If_IsArrayEntity,
                                If_IsPointerEntity,
                                Has_Class,
                                Has_Return,
                                Has_Parameter,
                                Has_OutputParameter,
                                Has_Contextual,
                                Has_ConstContextual,
                                Has_StaticContextual,
                                Has_StaticConstContextual,
                                Has_Base,
                                Has_Static,
                                Has_DefaultValue,
                                Has_DynamicMethod,
                                Has_Constant,
                                Has_Method,
                                Has_Attribute,
                                Has_ClassOrEnum;

            collection<ent_context> Dependences;

            SimpleInterCommonGenerator();

		};

	}
}

#endif //  _SIMPLE_INTER_COMMON_GENERATOR_HPP_
