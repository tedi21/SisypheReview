#ifndef _SIMPLE_MD_GENERATOR_HPP_
#define _SIMPLE_MD_GENERATOR_HPP_

#include "EtatHandler.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

        struct SimpleMDGenerator
        : public EtatHandler,
          public report<SimpleMDGenerator> {

                format<gen_info>    Source,
                                    CreateFile,
                                    CreateClassDescription,
                                    CreateClassReference,
                                    ClassName,
                                    ListClass,
                                    ConstantName,
                                    ListConstant,
                                    MethodName,
                                    ListMethod,
                                    ParameterType,
                                    ListParameter,
                                    DependenceType,
                                    GetDependence,
                                    ReturnType,
                                    GetReturn,
                                    GetMethodExample,
                                    GetParameterDescription,
                                    GetReturnDescription,
                                    GetConstantExample;

                condition<gen_info> Has_Class,
                                    Has_Constant,
                                    Has_Method,
                                    Has_Contextual,
                                    Has_Parameter,
                                    Has_Return,
                                    Has_MethodExample,
                                    Has_ConstantExample,
                                    If_IsClass,
                                    If_IsConstant,
                                    If_IsMethod,
                                    If_IsParameter,
                                    If_IsID,
                                    If_IsREF,
                                    If_IsCONTEXTUAL,
                                    If_IsAUTO,
                                    If_IsREADONLY,
                                    If_IsBASE,
                                    If_IsSTATIC,
                                    If_IsVIRTUAL;

            SimpleMDGenerator();

			template <typename InfoT>
			struct etat {
				format<InfoT> const& EtatStart;

                etat(SimpleMDGenerator const& me)
                : EtatStart(me.Source)
				{}

				format<InfoT> const& start() const { return EtatStart; }
			};
		};

	}
}

#endif // _SIMPLE_MD_GENERATOR_HPP_
