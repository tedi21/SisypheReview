#ifndef _SIMPLE_MD_ACCESS_GENERATOR_HPP_
#define _SIMPLE_MD_ACCESS_GENERATOR_HPP_

#include "SimpleInterpreterCommonGenerator.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

        struct SimpleMDAccessGenerator
		: public SimpleInterpreterCommonGenerator,
          public report<SimpleMDAccessGenerator> {

            format<gen_info>    Source_R2,
								CreateFile_R2,
                                CreateClassDescription,
                                CreateClassReference,
                                CreateConstructorReference_R2,
                                CreateGetAllReference_R2,
                                CreateGetManyReference_R2,
                                CreateGetOneReference_R2,
                                CreateSelectOneReference_R2,
                                CreateSelectManyReference_R2,
                                CreateCancelSelectedReference_R2,
                                CreateIsSelectedReference_R2,
                                CreateFillReference_R2,
                                CreateFillAllReference_R2,
                                CreateFillOneReference_R2,
                                CreateFillManyReference_R2,
                                CreateIsModifiedReference_R2,
                                CreateUpdateReference_R2,
                                CreateInsertReference_R2,
                                CreateDeleteReference_R2,
                                CreateGetErrorReference_R2;


            SimpleMDAccessGenerator();

			template <typename InfoT>
			struct etat {
				format<InfoT> const& EtatStart;

                etat(SimpleMDAccessGenerator const& me)
                : EtatStart(me.Source_R2)
				{}

				format<InfoT> const& start() const { return EtatStart; }
			};
		};

	}
}

#endif // _SIMPLE_MD_ACCESS_GENERATOR_HPP_
