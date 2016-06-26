#ifndef _SIMPLE_CPP_COMMENT_GENERATOR_HPP_
#define _SIMPLE_CPP_COMMENT_GENERATOR_HPP_

#include <iostream>
#include <string>
#include "SimpleCPPCommonGenerator.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

		struct SimpleCPPCommentGenerator
		: public SimpleCPPCommonGenerator 
		{
			format<gen_info>     CommentParam_R2,
								 CommentReturn_R2,
								 CreateMethodComment_R2,
								 CommentEntity_R2,
								 CommentEntityClass_R2,
								 CommentEntityConstructor_R2,
								 CommentEntityConstructor2_R2,
								 CommentAttribute_R2,
								 CommentReturnAttribute_R2,
								 CommentRelation_R2,
								 CommentRelationAttribute_R2,
								 CommentEntityConstructor3_R2,
                                 CommentEntityCopyConstructor_R2,
                                 CommentEntityAssignOperator_R2,
                                 //CommentEntityCloneCopy_R2,
                                 //CommentEntityDuplicateCopy_R2
								 CommentSerialization_R2,
								 CommentSetAttribute_R2,
								 CommentGetAttribute_R2,
								 CommentGetREF_R2,
								 CommentIsNullREF_R2,
								 CommentEraseREF_R2,
                                 CommentIterator_R2,
								 CommentMethodBegin_R2,
								 CommentMethodEnd_R2,
								 CommentMethodConstBegin_R2,
								 CommentMethodConstEnd_R2,
								 CommentMethodAt_R2,
								 CommentMethodConstAt_R2,
								 CommentMethodSize_R2,
								 CommentMethodEmpty_R2,
								 CommentMethodPushBack_R2,
								 CommentMethodInsert0_R2,
								 CommentMethodInsert1_R2,
								 CommentMethodErase0_R2,
								 CommentMethodErase1_R2,
								 CommentMethodClear_R2,
								 CommentPrintConsole_R2,
								 CommentFriendOperatorStream_R2,
								 CommentPredicateEqualID_R2,
								 CommentPredicateEqualIDConstructor_R2,
								 CommentPredicateEqual_R2,
								 CommentPredicateEqualConstructor_R2,
								 CommentPredicateLessThan_R2,
								 CommentPredicateGreaterThan_R2,
								 CommentAccessClass_R2,
								 CommentAccessDestructor_R2,
								 CommentAccessConstructor_R2,
								 CommentAccessGetAll_R2,
								 CommentAccessGetMany_R2,
								 CommentAccessGetOne_R2,
								 CommentAccessGetInstance_R2,
								 CommentAccessSelectMany_R2,
								 CommentAccessCancel_R2,
								 CommentAccessSelectOne_R2,
								 CommentAccessIsSelected_R2,
								 CommentAccessUpdate_R2,
								 CommentAccessAltered_R2,
								 CommentAccessInsert_R2,
								 CommentAccessDelete_R2,
								 CommentAccessFill1_R2,
								 CommentAccessFill2_R2,
								 CommentAccessFill3_R2,
								 CommentAccessFill4_R2,
                                 CommentAccessAddInsertSignal_R2,
                                 CommentAccessAddUpdateSignal_R2,
                                 CommentAccessAddDeleteSignal_R2,
                                 CommentAccessAddTransactionSignal_R2,
                                 CommentAccessRemoveInsertSignal_R2,
                                 CommentAccessRemoveUpdateSignal_R2,
                                 CommentAccessRemoveDeleteSignal_R2,
                                 CommentAccessRemoveTransactionSignal_R2;

			SimpleCPPCommentGenerator();
		};

	}
}

#endif // _SIMPLE_CPP_COMMENT_GENERATOR_HPP_
