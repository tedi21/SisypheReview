#ifndef _SIMPLE_CPP_WORD_GENERATOR_HPP_
#define _SIMPLE_CPP_WORD_GENERATOR_HPP_

#include "SimpleWordCommonGenerator.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

		struct SimpleCPPWordGenerator
		: public SimpleWordCommonGenerator,
		  public report<SimpleCPPWordGenerator> {

				format<gen_info>    SourceCPP,
									CreateFile,
									CreateInclude,
									CreateWordClass,
                                    CreateWordAttribute,
                                    CreateWordMethod,
                                    CreateWordArray,
                                    CreateWordConstant;

			SimpleCPPWordGenerator();

			template <typename InfoT>
			struct etat {
				format<InfoT> const& EtatStart;

				etat(SimpleCPPWordGenerator const& me)
				: EtatStart(me.SourceCPP)
				{}

				format<InfoT> const& start() const { return EtatStart; }
			};
		};

	}
}

#endif // _SIMPLE_CPP_WORD_GENERATOR_HPP_