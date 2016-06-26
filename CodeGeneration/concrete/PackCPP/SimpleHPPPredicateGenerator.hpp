#ifndef _SIMPLE_HPP_PREDICATE_GENERATOR_HPP_
#define _SIMPLE_HPP_PREDICATE_GENERATOR_HPP_

#include <iostream>
#include <string>
#include "SimpleCPPCommentGenerator.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

		struct SimpleHPPPredicateGenerator
		: public SimpleCPPCommentGenerator,
		  public report<SimpleHPPPredicateGenerator> {

				format<gen_info>    SourceHPP_R2,
									CreateFile_R2,
				// functor
									CreatePredicateClass_R2,
									CreateEqualIDFunctor_R2,
									CreatePrivateMembersIDFunctor_R2, 
									CreatePublicMembersIDFunctor_R2,
									CreateEqualIDParam_R2,
									CreateEqualIDInit_R2,
									CreateAttributFunctor_R2,
									CreatePrivateMembersFunctor_R2,
									CreatePublicMembersEqualFunctor_R2,
									CreatePublicMembersLessThanFunctor_R2,
									CreatePublicMembersGreaterThanFunctor_R2;

			SimpleHPPPredicateGenerator();

			template <typename InfoT>
			struct etat {
				format<InfoT> const& EtatStart;

				etat(SimpleHPPPredicateGenerator const& me)
				: EtatStart(me.SourceHPP_R2)
				{}

				format<InfoT> const& start() const { return EtatStart; }
			};
		};

	}
}

#endif // _SIMPLE_HPP_PREDICATE_GENERATOR_HPP_
