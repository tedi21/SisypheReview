#ifndef _SIMPLE_CPP_INTERPRETER_GENERATOR_HPP_
#define _SIMPLE_CPP_INTERPRETER_GENERATOR_HPP_

#include "SimpleInterCommonGenerator.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

        struct SimpleCPPInterpreterGenerator
        : public SimpleInterCommonGenerator,
          public report<SimpleCPPInterpreterGenerator> {

                format<gen_info>    SourceCPP,
                                    CreateFile,
                                    CreateMacro,
                                    CreateEndMacro,
                                    CreateDeclaration,
                                    CreateInterpreterClassMembers,
                                    CommentInterpreterMethod,
                                    CreateInterpreterMethod,
                                    CreateInterpreterParameters,
                                    CommentInterpreterConstant,
                                    CreateInterpreterConstant,
                                    CommentInterpreterAttribute,
                                    CreateInterpreterAttribute,
                                    CreateInterpreterCheck,
                                    CreateInterpreterReset;

            SimpleCPPInterpreterGenerator();

			template <typename InfoT>
			struct etat {
				format<InfoT> const& EtatStart;

                etat(SimpleCPPInterpreterGenerator const& me)
                : EtatStart(me.SourceCPP)
				{}

				format<InfoT> const& start() const { return EtatStart; }
			};
		};

	}
}

#endif // _SIMPLE_CPP_INTERPRETER_GENERATOR_HPP_
