#ifndef _SIMPLE_CPP_DATA_INTERPRETER_GENERATOR_HPP_
#define _SIMPLE_CPP_DATA_INTERPRETER_GENERATOR_HPP_

#include "SimpleInterCommonGenerator.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

        struct SimpleCPPDataInterpreterGenerator
        : public SimpleInterCommonGenerator,
          public report<SimpleCPPDataInterpreterGenerator> {

                format<gen_info>        SourceCPP,
                                        CreateFile,
                                        CreateInclude,
                                        CreateNamespace,
                                        CreateExport;

            SimpleCPPDataInterpreterGenerator();

			template <typename InfoT>
			struct etat {
				format<InfoT> const& EtatStart;

                etat(SimpleCPPDataInterpreterGenerator const& me)
                : EtatStart(me.SourceCPP)
				{}

				format<InfoT> const& start() const { return EtatStart; }
			};
		};

	}
}

#endif // _SIMPLE_CPP_INTERPRETER_GENERATOR_HPP_
