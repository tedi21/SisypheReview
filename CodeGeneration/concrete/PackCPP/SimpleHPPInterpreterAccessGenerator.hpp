#ifndef _SIMPLE_HPP_INTERPRETER_ACCESS_GENERATOR_HPP_
#define _SIMPLE_HPP_INTERPRETER_ACCESS_GENERATOR_HPP_

#include "SimpleInterpreterCommonGenerator.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

		struct SimpleHPPInterpreterAccessGenerator
		: public SimpleInterpreterCommonGenerator,
		  public report<SimpleHPPInterpreterAccessGenerator> {

			format<gen_info>    SourceHPP_R2,
								CreateFile_R2,
								CreateInclude_R2,
								CreateEndInclude_R2,
								CreateUsingNamespace_R2,
								CreateInterpreterAccessClass_R2,
								CreateFactoryRegister_R2,
								CreateFactoryUnRegister_R2,
								CreateGetAll_R2,
								CreateGetMany_R2,
								CreateGetOne_R2,
								CreateSelectOne_R2,
								CreateSelectMany_R2,
								CreateCancelSelected_R2,
								CreateIsSelected_R2,
								CreateFillREF_R2,
								CreateFillRelation_R2,
								CreateUpdate_R2,
								CreateIsAltered_R2,
								CreateInsert_R2,
								CreateDelete_R2,
                                ConvertPtrVectorToArray_R2,
                                SetError_R2,
                                ClearError_R2,
                                GetError_R2;


			SimpleHPPInterpreterAccessGenerator();

			template <typename InfoT>
			struct etat {
				format<InfoT> const& EtatStart;

				etat(SimpleHPPInterpreterAccessGenerator const& me)
				: EtatStart(me.SourceHPP_R2)
				{}

				format<InfoT> const& start() const { return EtatStart; }
			};
		};

	}
}

#endif // _SIMPLE_HPP_INTERPRETER_ACCESS_GENERATOR_HPP_
