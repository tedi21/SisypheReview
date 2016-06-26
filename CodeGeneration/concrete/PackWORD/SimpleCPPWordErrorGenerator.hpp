#ifndef _SIMPLE_CPP_WORD_ERROR_GENERATOR_HPP_
#define _SIMPLE_CPP_WORD_ERROR_GENERATOR_HPP_

#include "SimpleWordCommonGenerator.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

		struct SimpleCPPWordErrorGenerator
		: public SimpleWordCommonGenerator,
		  public report<SimpleCPPWordErrorGenerator> {

				format<gen_info>    SourceCPP,
									CreateFile,
									CreateInclude,
									CreateWordFunction;

			SimpleCPPWordErrorGenerator();

			template <typename InfoT>
			struct etat {
				format<InfoT> const& EtatStart;

				etat(SimpleCPPWordErrorGenerator const& me)
				: EtatStart(me.SourceCPP)
				{}

				format<InfoT> const& start() const { return EtatStart; }
			};
		};

	}
}

#endif // _SIMPLE_CPP_WORD_ERROR_GENERATOR_HPP_
