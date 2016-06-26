#ifndef _SIMPLE_HPP_INTERPRETER_GENERATOR_HPP_
#define _SIMPLE_HPP_INTERPRETER_GENERATOR_HPP_

#include "SimpleInterpreterCommonGenerator.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

		struct SimpleHPPInterpreterGenerator
		: public SimpleInterpreterCommonGenerator,
		  public report<SimpleHPPInterpreterGenerator> {

				format<gen_info>    SourceHPP_R2,
									CreateFile_R2,
									CreateUsingNamespace_R2,
									CreateInclude_R2,
                                    CreateForwardDeclaration_R2,
									CreateEndInclude_R2,
									CreateInterpreterEntity_R2,
									CreateCheckFunction_R2,
									CreateResetFunction_R2,
									CreateConstructorFactoryPrototype_R2,
									CreateAttributeGetter_R2,
                                    CreateAttributeRefGetter_R2,
									CreateAttributeSetter_R2,
									CreateAttributeIsNull_R2,
									CreateAttributeErase_R2,
									CreateAttributeListErase_R2,
									CreateAttributeListInsert_R2,
									CreateAttributeListAt_R2,
									CreateAttributeListClear_R2,
									CreateAttributeListEmpty_R2,
									CreateAttributeListSize_R2,
									CreateAttributeRegister_R2,
									CreateAttributeUnRegister_R2;

			SimpleHPPInterpreterGenerator();

			template <typename InfoT>
			struct etat {
				format<InfoT> const& EtatStart;

				etat(SimpleHPPInterpreterGenerator const& me)
				: EtatStart(me.SourceHPP_R2)
				{}

				format<InfoT> const& start() const { return EtatStart; }
			};
		};

	}
}

#endif // _SIMPLE_HPP_INTERPRETER_GENERATOR_HPP_
