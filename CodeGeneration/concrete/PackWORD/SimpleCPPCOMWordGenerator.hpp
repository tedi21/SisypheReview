#ifndef _SIMPLE_CPP_COM_WORD_GENERATOR_HPP_
#define _SIMPLE_CPP_COM_WORD_GENERATOR_HPP_

#include "SimpleWordCommonGenerator.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

		struct SimpleCPPCOMWordGenerator
		: public SimpleWordCommonGenerator,
		  public report<SimpleCPPCOMWordGenerator> {

				format<gen_info>    SourceCPP,
									CreateFile,
									CreateInclude,
									CreateWordClass;

			SimpleCPPCOMWordGenerator();

			template <typename InfoT>
			struct etat {
				format<InfoT> const& EtatStart;

				etat(SimpleCPPCOMWordGenerator const& me)
				: EtatStart(me.SourceCPP)
				{}

				format<InfoT> const& start() const { return EtatStart; }
			};
		};

	}
}

#endif // _SIMPLE_CPP_COM_WORD_GENERATOR_HPP_
