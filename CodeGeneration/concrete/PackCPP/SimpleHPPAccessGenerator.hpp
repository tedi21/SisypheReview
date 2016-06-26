#ifndef _SIMPLE_HPP_ACCESS_GENERATOR_HPP_
#define _SIMPLE_HPP_ACCESS_GENERATOR_HPP_

#include <iostream>
#include <string>
#include "SimpleCPPCommentGenerator.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

		struct SimpleHPPAccessGenerator
		: public SimpleCPPCommentGenerator,
		  public report<SimpleHPPAccessGenerator> {

			format<gen_info>    SourceHPP_R2,
								CreateFile_R2, 
								CreateInclude_R2,
								CreateEndInclude_R2, 
								CreateUsingNamespace_R2,
								CreateAccessClass_R2, 
								CreatePrivateMembers_R2, 
								CreatePublicMembers_R2;

			SimpleHPPAccessGenerator();

			template <typename InfoT>
			struct etat {
				format<InfoT> const& EtatStart;

				etat(SimpleHPPAccessGenerator const& me)
				: EtatStart(me.SourceHPP_R2)
				{}

				format<InfoT> const& start() const { return EtatStart; }
			};
		};

	}
} 

#endif // _SIMPLE_HPP_ACCESS_GENERATOR_HPP_