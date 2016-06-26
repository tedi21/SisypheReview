#ifndef _SIMPLE_HPP_WORD_ERROR_GENERATOR_HPP_
#define _SIMPLE_HPP_WORD_ERROR_GENERATOR_HPP_

#include "SimpleWordCommonGenerator.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

		struct SimpleHPPWordErrorGenerator
		: public SimpleWordCommonGenerator,
		  public report<SimpleHPPWordErrorGenerator> {

				format<gen_info>    SourceHPP,
									CreateFile,
									CreateInclude,
									CreateWordFunction;

			SimpleHPPWordErrorGenerator();

			template <typename InfoT>
			struct etat {
				format<InfoT> const& EtatStart;

				etat(SimpleHPPWordErrorGenerator const& me)
				: EtatStart(me.SourceHPP)
				{}

				format<InfoT> const& start() const { return EtatStart; }
			};
		};

	}
}

#endif // _SIMPLE_HPP_WORD_ERROR_GENERATOR_HPP_
