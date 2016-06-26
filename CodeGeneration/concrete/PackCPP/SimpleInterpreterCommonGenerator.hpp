#ifndef _SIMPLE_INTERPRETER_COMMON_GENERATOR_HPP_
#define _SIMPLE_INTERPRETER_COMMON_GENERATOR_HPP_

#include "SimpleCPPCommonGenerator.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

		struct SimpleInterpreterCommonGenerator
		: public SimpleCPPCommonGenerator {

			format<gen_info>    	ListEntityParam_R2,
									ListEntityIDParam_R2,
									ListRelationIDParam_R2,
									EntityIDParamSize_R2,
									FillRelationParamSize_R2,
									SelectOneParamSize_R2,
									CreateIDParam_R2,
									CreateConstructorParam_R2,
									EntityParamSize_R2,
                                    AttributeInterpreterTypeName_R2,
									AttributeInterpreterType_R2,
									AttributeCheck_R2,
                                    AttributeNativeType_R2;

			condition<gen_info>     If_HasReferenceID_R2,
									If_HasAttribute_R2,
									If_IsWriteAttribute_R2;

			SimpleInterpreterCommonGenerator();

		};

	}
}

#endif //  _SIMPLE_INTERPRETER_COMMON_GENERATOR_HPP_
