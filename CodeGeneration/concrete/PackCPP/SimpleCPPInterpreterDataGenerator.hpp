#ifndef _SIMPLE_CPP_INTERPRETER_DATA_GENERATOR_HPP_
#define _SIMPLE_CPP_INTERPRETER_DATA_GENERATOR_HPP_

#include "SimpleInterpreterCommonGenerator.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

		struct SimpleCPPInterpreterDataGenerator
		: public SimpleInterpreterCommonGenerator,
		  public report<SimpleCPPInterpreterDataGenerator> {

			format<gen_info>    SourceCPP_R2,
								CreateFile_R2,
								CreateInclude_R2,
								CreateNamespace_R2,
								CreateExport_R2;  

			SimpleCPPInterpreterDataGenerator();

			template <typename InfoT>
			struct etat {
				format<InfoT> const& EtatStart;

				etat(SimpleCPPInterpreterDataGenerator const& me)
				: EtatStart(me.SourceCPP_R2)
				{}

				format<InfoT> const& start() const { return EtatStart; }
			};
		};

	}
}

#endif // _SIMPLE_CPP_INTERPRETER_DATA_GENERATOR_HPP_