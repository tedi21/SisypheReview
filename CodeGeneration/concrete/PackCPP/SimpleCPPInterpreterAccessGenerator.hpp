#ifndef _SIMPLE_CPP_INTERPRETER_ACCESS_GENERATOR_HPP_
#define _SIMPLE_CPP_INTERPRETER_ACCESS_GENERATOR_HPP_

#include "SimpleInterpreterCommonGenerator.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

		struct SimpleCPPInterpreterAccessGenerator
		: public SimpleInterpreterCommonGenerator,
		  public report<SimpleCPPInterpreterAccessGenerator> {

			format<gen_info>    SourceCPP_R2,
								CreateFile_R2,
								CreateInterpretAccess_R2,
								CreateInterpreterAccessConstructor_R2,
								CreateInterpreterAccessDestructor_R2,
								CreateInterpreterAccessToString_R2,
								CreateInterpreterAccessClone_R2,
								CreateInterpreterAccessGetClassName_R2,
								CreateInterpreterAccessInvoke_R2,
								ConvertPtrVectorToArray_R2,
								CreateInterpreterAccessGetAll_R2,
								CreateInterpreterAccessGetMany_R2,
								CreateInterpreterAccessGetOne_R2,
								CreateInterpreterAccessSelectOne_R2,
								CreateInterpreterAccessSelectMany_R2,
								CreateInterpreterAccessCancelSelected_R2,
								CreateInterpreterAccessIsSelected_R2,
								CreateInterpreterAccessFillREF_R2,
								CreateInterpreterAccessFillAllRelation_R2,
								CreateInterpreterAccessFillOneRelation_R2,
								CreateInterpreterAccessFillManyRelation_R2,
								CreateInterpreterAccessUpdate_R2,
								CreateInterpreterAccessIsAltered_R2,
								CreateInterpreterAccessInsert_R2,
                                CreateInterpreterAccessDelete_R2,
                                CreateInterpreterAccessSetError_R2,
                                CreateInterpreterAccessClearError_R2,
                                CreateInterpreterAccessGetError_R2;

			SimpleCPPInterpreterAccessGenerator();

			template <typename InfoT>
			struct etat {
				format<InfoT> const& EtatStart;

				etat(SimpleCPPInterpreterAccessGenerator const& me)
				: EtatStart(me.SourceCPP_R2)
				{}

				format<InfoT> const& start() const { return EtatStart; }
			};
		};
	}
}

#endif // _SIMPLE_CPP_INTERPRETER_ACCESS_GENERATOR_HPP_
