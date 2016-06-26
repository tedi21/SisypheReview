#ifndef _SIMPLE_H_DATA_GENERATOR_HPP_
#define _SIMPLE_H_DATA_GENERATOR_HPP_

#include <iostream>
#include <string>
#include "SimpleCPPCommonGenerator.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

		struct SimpleHDataGenerator
		: public SimpleCPPCommonGenerator,
		  public report<SimpleHDataGenerator> {

			format<gen_info>    SourceH_R2,
								CreateFile_R2, 
								CreateInclude_R2,
                                CreateEnum_R2;

			SimpleHDataGenerator();

			template <typename InfoT>
			struct etat {
				format<InfoT> const& EtatStart;

				etat(SimpleHDataGenerator const& me)
				: EtatStart(me.SourceH_R2)
				{}

				format<InfoT> const& start() const { return EtatStart; }
			};
		};

	}
}

#endif // _SIMPLE_H_DATA_GENERATOR_HPP_