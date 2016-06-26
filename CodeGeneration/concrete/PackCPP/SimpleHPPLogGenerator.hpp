#ifndef _SIMPLE_HPP_LOG_GENERATOR_HPP_
#define _SIMPLE_HPP_LOG_GENERATOR_HPP_

#include <iostream>
#include <string>
#include "SimpleCPPCommonGenerator.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

		struct SimpleHPPLogGenerator
		: public SimpleCPPCommonGenerator,
		  public report<SimpleHPPLogGenerator> {

			format<gen_info>    SourceHPP_R2,
								CreateFile_R2, 
								CreateInclude_R2,
								CreateDefine_R2;
		    
			SimpleHPPLogGenerator();

			template <typename InfoT>
			struct etat {
				format<InfoT> const& EtatStart;

				etat(SimpleHPPLogGenerator const& me)
				: EtatStart(me.SourceHPP_R2)
				{}

				format<InfoT> const& start() const { return EtatStart; }
			};
		};

	}
}

#endif // _SIMPLE_HPP_LOG_GENERATOR_HPP_