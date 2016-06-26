#ifndef _SIMPLE_CPP_INTERPRETER_GENERATOR_HPP_
#define _SIMPLE_CPP_INTERPRETER_GENERATOR_HPP_

#include "SimpleInterpreterCommonGenerator.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

		struct SimpleCPPInterpreterGenerator
		: public SimpleInterpreterCommonGenerator,
		  public report<SimpleCPPInterpreterGenerator> {

				format<gen_info>    SourceCPP_R2,
									CreateFile_R2,
									CreateInterpretEntity_R2,
									CreateInterpreterEntityConstructor_R2,
									CreateInterpreterEntityConstructor2_R2,
									CreateInterpreterEntityConstructor3_R2,
									CreateInterpreterEntityDestructor_R2,
									CreateInterpreterEntityGetValue_R2,
									CreateInterpreterEntitySetValue_R2,
									CreateInterpreterEntityAttributeGetter_R2,
                                    CreateInterpreterEntityAttributeRefGetter_R2,
									CreateInterpreterEntityAttributeSetter_R2,
									CreateInterpreterEntityAttributeIsNull_R2,
									CreateInterpreterEntityAttributeErase_R2,
									CreateInterpreterEntityAttributeListErase_R2,
									CreateInterpreterEntityAttributeListInsert_R2,
									CreateInterpreterEntityAttributeListAt_R2,
									CreateInterpreterEntityAttributeListClear_R2,
									CreateInterpreterEntityAttributeListEmpty_R2,
									CreateInterpreterEntityAttributeListSize_R2,
									CreateInterpreterEntityToString_R2,
									CreateInterpreterEntityClone_R2,
									CreateInterpreterEntityGetClassName_R2,
									CreateInterpreterEntityInvoke_R2,
									CreateCheckFunction_R2,
									CreateResetFunction_R2;

			SimpleCPPInterpreterGenerator();

			template <typename InfoT>
			struct etat {
				format<InfoT> const& EtatStart;

				etat(SimpleCPPInterpreterGenerator const& me)
				: EtatStart(me.SourceCPP_R2)
				{}

				format<InfoT> const& start() const { return EtatStart; }
			};
		};

	}
}

#endif // _SIMPLE_CPP_INTERPRETER_GENERATOR_HPP_
