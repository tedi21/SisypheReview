#ifndef _SIMPLE_HPP_INTERPRETER_GENERATOR_HPP_
#define _SIMPLE_HPP_INTERPRETER_GENERATOR_HPP_

#include "SimpleInterCommonGenerator.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

        struct SimpleHPPInterpreterGenerator
        : public SimpleInterCommonGenerator,
          public report<SimpleHPPInterpreterGenerator> {

				format<gen_info>    SourceHPP,
									CreateFile,
									CreateInclude,
                                    CreateMacro,
                                    CreateEndMacro,
                                    CreateUsingNamespace,
                                    CommentInterpreterClass,
                                    CreateInterpreterClass,
                                    CommentInterpreterMethod,
                                    CreateInterpreterMethod,
                                    CreateInterpreterParameters,
                                    CreateInterpreterRegister,
                                    CreateInterpreterUnregister,
                                    CommentInterpreterConstant,
                                    CreateInterpreterConstant,
                                    CommentInterpreterAttribute,
                                    CreateInterpreterAttribute,
                                    RegisterSize;

            SimpleHPPInterpreterGenerator();

			template <typename InfoT>
			struct etat {
				format<InfoT> const& EtatStart;

                etat(SimpleHPPInterpreterGenerator const& me)
				: EtatStart(me.SourceHPP)
				{}

				format<InfoT> const& start() const { return EtatStart; }
			};
		};

	}
}

#endif // _SIMPLE_HPP_INTERPRETER_GENERATOR_HPP_
