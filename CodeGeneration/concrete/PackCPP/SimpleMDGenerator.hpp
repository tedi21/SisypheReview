#ifndef _SIMPLE_MD_GENERATOR_HPP_
#define _SIMPLE_MD_GENERATOR_HPP_

#include "SimpleInterpreterCommonGenerator.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

        struct SimpleMDGenerator
		: public SimpleInterpreterCommonGenerator,
          public report<SimpleMDGenerator> {

                format<gen_info>    Source_R2,
									CreateFile_R2,
                                    CreateClassDescription,
                                    CreateClassReference,
                                    CreateDefaultConstructorReference_R2,
                                    CreateConstructorReference_R2,
                                    CreateAttributeGetterReference_R2,
                                    CreateAttributeRefGetterReference_R2,
                                    CreateAttributeSetterReference_R2,
                                    CreateAttributeIsNullReference_R2,
                                    CreateAttributeEraseReference_R2,
                                    CreateAttributeListEraseReference_R2,
                                    CreateAttributeListInsertReference_R2,
                                    CreateAttributeListAtReference_R2,
                                    CreateAttributeListClearReference_R2,
                                    CreateAttributeListEmptyReference_R2,
                                    CreateAttributeListSize_R2;

            SimpleMDGenerator();

			template <typename InfoT>
			struct etat {
				format<InfoT> const& EtatStart;

                etat(SimpleMDGenerator const& me)
                : EtatStart(me.Source_R2)
				{}

				format<InfoT> const& start() const { return EtatStart; }
			};
		};

	}
}

#endif // _SIMPLE_MD_GENERATOR_HPP_
