#ifndef _SIMPLE_HPP_WORD_GENERATOR_HPP_
#define _SIMPLE_HPP_WORD_GENERATOR_HPP_

#include "SimpleWordCommonGenerator.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

		struct SimpleHPPWordGenerator
		: public SimpleWordCommonGenerator,
		  public report<SimpleHPPWordGenerator> {

				format<gen_info>    SourceHPP,
									CreateFile,
									CreateInclude,
                                    CommentWordClass,
									CreateWordClass,
                                    CommentWordAttribute,
                                    CreateWordAttribute,
                                    CommentWordMethod,
                                    CreateWordMethod,
                                    CommentWordArray,
                                    CreateWordArray,
                                    DeclareWordClass,
                                    CommentWordEnum,
                                    CreateWordEnum,
                                    CommentWordConstant,
                                    CreateWordConstant;

			SimpleHPPWordGenerator();

			template <typename InfoT>
			struct etat {
				format<InfoT> const& EtatStart;

				etat(SimpleHPPWordGenerator const& me)
				: EtatStart(me.SourceHPP)
				{}

				format<InfoT> const& start() const { return EtatStart; }
			};
		};

	}
}

#endif // _SIMPLE_HPP_WORD_GENERATOR_HPP_