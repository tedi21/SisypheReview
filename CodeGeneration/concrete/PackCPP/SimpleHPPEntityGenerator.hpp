#ifndef _SIMPLE_HPP_ENTITY_GENERATOR_HPP_
#define _SIMPLE_HPP_ENTITY_GENERATOR_HPP_

#include <iostream>
#include <string>
#include "SimpleCPPCommentGenerator.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

		struct SimpleHPPEntityGenerator
		: public SimpleCPPCommentGenerator,
		  public report<SimpleHPPEntityGenerator> {

				format<gen_info>    SourceHPP_R2,
									CreateFile_R2, 
									CreateInclude_R2,
									CreateEndInclude_R2, 
									CreateUsingNamespace_R2,
									CreateForwardDeclaration_R2,
									CreateEntityClass_R2,
									CreatePrivateMembers_R2,
									CreateAttributes_R2,
									CreateRelation_R2,
									CreateSerialization_R2,
									CreateSerializationLine_R2,
									CreateProtectedMembers_R2,
									CreateEntityConstructor3_R2,
									CreateEntityInit3_R2,
									CreateEntityParam3_R2,
									CreateEntityPrint3_R2,
                                    CreateEntityCopyConstructor_R2,
                                    CreateEntityAssignOperator_R2,
                                    //CreateEntityCloneCopy_R2,
                                    //CreateEntityDuplicateCopy_R2,
									MethodSetAttribute_R2,
									MethodGetAttribute_R2,
									MethodGetREF_R2,
									MethodIsNullREF_R2,
									MethodEraseREF_R2,
									CreatePublicMembers_R2,
									CreateEntityInit_R2,
									CreateEntityConstructor_R2,
									CreateEntityParam2_R2,
									CreateEntityConstructor2_R2,
									CreateEntityInit2_R2,
									CreateEntityPrint2_R2,
									CreateMethodsAttribute_R2,
									CreateMethodsRelation_R2,
                                    CreateIteratorsRelation_R2,
                                    Iterator_R2,
									MethodBegin_R2,
									MethodEnd_R2, 
									MethodConstBegin_R2,
									MethodConstEnd_R2, 
									MethodAt_R2, 
									MethodConstAt_R2,
									MethodSize_R2, 
									MethodEmpty_R2, 
									MethodPushBack_R2,
									MethodInsert0_R2, 
									MethodInsert1_R2, 
									MethodErase0_R2,
									MethodErase1_R2, 
									MethodClear_R2,
									CreatePrintConsole_R2,
									CreatePrintConsoleLine_R2,
									CreateFriendOperatorStream_R2,
									CreatePredicateClass_R2;

			SimpleHPPEntityGenerator();

			template <typename InfoT>
			struct etat {
				format<InfoT> const& EtatStart;

				etat(SimpleHPPEntityGenerator const& me)
				: EtatStart(me.SourceHPP_R2)
				{}

				format<InfoT> const& start() const { return EtatStart; }
			};
		};

	}
}

#endif // _SIMPLE_HPP_ENTITY_GENERATOR_HPP_
