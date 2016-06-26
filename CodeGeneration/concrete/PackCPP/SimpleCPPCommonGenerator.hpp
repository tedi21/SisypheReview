#ifndef _SIMPLE_CPP_COMMON_GENERATOR_HPP_
#define _SIMPLE_CPP_COMMON_GENERATOR_HPP_

#include <iostream>
#include <string>
#include "EtatHandler.hpp"

using namespace std;
using namespace gen;

namespace dsg {

	namespace generator {

		enum cpp_option_t
		{
			BOOST_SERIAL = 1,
		};

		struct SimpleCPPCommonGenerator
		: public EtatHandler {

			format<gen_info>    CreateHeader_R2,
								CreateHPPDefine_R2,
								CreateHPPEndDefine_R2,
								CreateNamespace_R2,
								CreateEndNamespace_R2,
								CreateMacro_R2,
								CreateEndMacro_R2,
								ExportAPI_R2,
								CreateExportTClass_R2,
								CreateTClass_R2,
								CreateExportClass_R2,
								CreateClass_R2,
								CreateExportInternClass_R2,
								CreateInternClass_R2,
								MemberName_R2,
								Member_R2,
								CreateInlineMethod_R2,
								CreateInlineGetMethod_R2,
								CreateInlineSetMethod_R2,
								IndentationInlineMethod_R2,
								CreateInlineConstructor_R2,
								CreateInlineTConstructor_R2,
								CreateInternConstructor_R2,
								IndentationMethod_R2,
								CreateTMethod_R2,
								CreateTDestructor_R2,
								CreateGetTMethod_R2,
								CreateSetTMethod_R2,
                                CreateTypedef_R2,
								CreateTConstructor_R2,
								CreateInit_R2,
								CreatePrint_R2,
								CommaParam_R2,
								SpaceParam_R2,
								InitializeConnection_R2,
								UEntity_R2,
								LEntity_R2,
                                ListRelationPA_R2,
                                ListRelationPB_R2,
								ListRelationN_R2,
								ListRelation1_R2,
								URelation1_R2,
								URelationN_R2,
								LRelation1_R2,
								LRelationN_R2,
								UAccess_R2,
								LAccess_R2,
								EncodingClass_R2,
								EntityClass_R2, 
								Relation1Class_R2,
								RelationNClass_R2,
                                URelationNName_R2,
                                LRelationNName_R2,
                                URelation1Name_R2,
                                LRelation1Name_R2,
								AccessClass_R2,
								EncodingClassDeclaration_R2,
								EntityClassDeclaration_R2,
								Relation1ClassDeclaration_R2,
								RelationNClassDeclaration_R2,
								AccessClassDeclaration_R2,
                                EntityPointer_R2,
								EntityReference_R2,
								EntityConstReference_R2,
                                URawAttribute_R2,
								UAttribute_R2,
								LAttribute_R2,
                                AttributeClassName_R2,
								AttributeType_R2,
								AttributeClass_R2,
								Reference_R2,
								ConstReference_R2,
								AttributeMemberName_R2,
								AttributeMember_R2,
								AttributeValueType_R2,
								AttributeValueMember_R2,
								AttributeInit_R2,
								AttributeReference_R2,
								AttributeConstReference_R2,
                                AttributeAccessor_R2,
                                AttributeId_R2,
								AttributeVariable_R2,
								AttributeAssignment_R2,
                                AttributeCopy_R2,
								ConvertToAString_R2,
								AttributeIDParam_R2,
								RelationNType_R2,
								RelationNMemberName_R2,
								RelationNMember_R2,
								RelationNTypedef_R2,
								RelationNIterator_R2,
								RelationNConstIterator_R2,
								RelationNReference_R2,
								RelationNConstReference_R2,
								Relation1Reference_R2,
								Relation1ConstReference_R2,
								ConvertToType_R2,
								ConvertToCString_R2,
								AttributeIDParamName_R2,
								Accessor_R2,
                                RelationAccessor_R2,
								IDParamName_R2,
								CreateInterpretObject_R2,
								CreateInterpretNumeric_R2,
                                AddDataParameter_R2,
                                GetDataStatement_R2,
                                DataStatementType_R2,
                                ListAttribute_R2,
                                GetReferencedAttribute_R2;

			condition<gen_info> If_IsNUMBER_R2,
								If_IsTEXT_R2,
                                If_IsGROUP_R2,
								If_IsID_R2,
								If_IsREF_R2,
								If_IsNotNULL_R2,
								If_IsAUTO_R2,
								If_IsCONST_R2,
								If_IsDATA_R2,
								If_IsFUNCTION_R2,
                                If_IsInitializable_R2,
                                If_IsComparable_R2,
                                If_IsPrintable_R2,
                                If_HasREF_ID_R2,
                                If_HasUniqueID_R2,
                                If_HasRelationNName_R2,
                                If_HasRelation1Name_R2;

            collection<ent_context>  ReferencedEntity_R2;

            collection<rel_context>  ReferencedRelations_R2;

            collection<rel_context>  RelationN;

			SimpleCPPCommonGenerator();

		};

	}
}

#endif //  _SIMPLE_CPP_COMMON_GENERATOR_HPP_
