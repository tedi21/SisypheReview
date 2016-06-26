#ifndef _SIMPLE_HPP_COM_WORD_GENERATOR_HPP_
#define _SIMPLE_HPP_COM_WORD_GENERATOR_HPP_

#include "SimpleWordCommonGenerator.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

		struct SimpleHPPCOMWordGenerator
		: public SimpleWordCommonGenerator,
		  public report<SimpleHPPCOMWordGenerator> {

				format<gen_info>    SourceHPP,
									CreateFile,
									CreateInclude,
									CreateWordClass;

			SimpleHPPCOMWordGenerator();

			template <typename InfoT>
			struct etat {
				format<InfoT> const& EtatStart;

				etat(SimpleHPPCOMWordGenerator const& me)
				: EtatStart(me.SourceHPP)
				{}

				format<InfoT> const& start() const { return EtatStart; }
			};
		};

	}
}

#endif // _SIMPLE_HPP_COM_WORD_GENERATOR_HPP_
