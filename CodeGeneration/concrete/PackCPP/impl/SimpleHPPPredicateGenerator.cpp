#include "SimpleHPPPredicateGenerator.hpp"

namespace dsg {

	namespace generator {

		SimpleHPPPredicateGenerator::SimpleHPPPredicateGenerator()
		{
			SourceHPP_R2 = 
				CreateFile_R2;

			CreateFile_R2 =
                CreateHeader_R2(file_g(getFileNameHandler(KIND_ALIAS)) << "Predicate.hpp")
                << CreateHPPDefine_R2("_" << file_g(getFileNameHandler(KIND_ALIAS)) << "_predicate_hpp_")
				<< CreateNamespace_R2(str_g("entity"))
				<< CreatePredicateClass_R2 [ent0, entN]
				<< CreateEndNamespace_R2
				<< CreateHPPEndDefine_R2;            

			CreatePredicateClass_R2 =
				CommentPredicateEqualID_R2
				<< CreateEqualIDFunctor_R2
				<< CreateAttributFunctor_R2 [!If_IsID_R2 && !If_IsREF_R2][attr0, attrN];

			// Functor
			CreateEqualIDFunctor_R2 =
				CreateInternClass_R2(EntityClass_R2, UEntity_R2 << "IDEquality", CreatePrivateMembersIDFunctor_R2, CreatePublicMembersIDFunctor_R2);

			CreatePrivateMembersIDFunctor_R2 = 
				(AttributeMember_R2                     [If_IsID_R2])[attr0, attrN];

			CreateEqualIDParam_R2 =
				(ConstReference_R2(AttributeType_R2) << SpaceParam_R2 << LAttribute_R2 << ~-CommaParam_R2)    
														[If_IsID_R2][attr0, attrN];

			CreateEqualIDInit_R2 =
				CreateInit_R2( AttributeMemberName_R2,
							   $(0) )                   [If_IsID_R2][attr0, attrN];

			CreatePublicMembersIDFunctor_R2 =
				CommentPredicateEqualIDConstructor_R2
				<< CreateInternConstructor_R2(  UEntity_R2 << "IDEquality",
												CreateEqualIDParam_R2,
												CreateEqualIDInit_R2(LAttribute_R2) )
				<< CreateInternConstructor_R2(  UEntity_R2 << "IDEquality",
												EntityConstReference_R2 << " elem",
												CreateEqualIDInit_R2(str_g("elem.get") << UAttribute_R2 << "()") )
				<< CreateInlineMethod_R2(   str_g("bool"),
											str_g("operator()"),
											EntityPointer_R2 << " other",
											str_g("const"),
		                                    (IndentationInlineMethod_R2 << str_g("bool eq") << UAttribute_R2 << " = (other != NULL && m_" << LAttribute_R2 << " == NULL && other->isNull" << UAttribute_R2 << "());"
		                                    << IndentationInlineMethod_R2 << "if (other != NULL && !eq" << UAttribute_R2 << " && m_" << LAttribute_R2 << " != NULL && !other->isNull" << UAttribute_R2 << "())"
		                                    << IndentationInlineMethod_R2 << "{"
                                            << IndentationInlineMethod_R2 << htab_g(1) << "eq" << UAttribute_R2 << " = typename _"
                                            << AttributeClassName_R2 << "<EncodingT>::" << AttributeClassName_R2 << "IDEquality(*m_" << LAttribute_R2 << ")(other->get" << UAttribute_R2 << "());"
		                                    << IndentationInlineMethod_R2 << "}")
                                                                                        [If_IsID_R2 && If_IsREF_R2][attr0, attrN]
											<< IndentationInlineMethod_R2 << "return ("
											<< ( ("other != NULL && "
                                            <<    AttributeMemberName_R2 << "==" 
											<<    "other->get" << UAttribute_R2 << "()")
                                                                                        [!If_IsREF_R2]
                                            <<   (str_g("eq") << UAttribute_R2)         [If_IsREF_R2]
											<<   ~-(str_g(" && ") << IndentationInlineMethod_R2 << '\t') ) 
																						[If_IsID_R2][attr0, attrN]
											<< ");" );

			CreateAttributFunctor_R2 =
				CommentPredicateEqual_R2
				<< CreateInternClass_R2(EntityClass_R2, UAttribute_R2 << "Equality", CreatePrivateMembersFunctor_R2, CreatePublicMembersEqualFunctor_R2)
				<< (CommentPredicateLessThan_R2
				<<  CreateInternClass_R2(EntityClass_R2, UAttribute_R2 << "Inferior", str_g(""), CreatePublicMembersLessThanFunctor_R2)
				<<  CommentPredicateGreaterThan_R2
                <<  CreateInternClass_R2(EntityClass_R2, UAttribute_R2 << "Superior", str_g(""), CreatePublicMembersGreaterThanFunctor_R2))
                    [If_IsComparable_R2];

			CreatePrivateMembersFunctor_R2 = 
				AttributeValueMember_R2;

			CreatePublicMembersEqualFunctor_R2 =
				CommentPredicateEqualConstructor_R2
				<< CreateInternConstructor_R2(  UAttribute_R2 << "Equality",
												ConstReference_R2(AttributeValueType_R2) << SpaceParam_R2 << LAttribute_R2,
												str_g(": ") << AttributeMemberName_R2 << '(' << LAttribute_R2 << ")\r\n\t" )
				<< CreateInlineMethod_R2(   str_g("bool"),
											str_g("operator()"),
											EntityPointer_R2 << " other",
											str_g("const"),
											IndentationInlineMethod_R2 << "return (other != NULL && "
											<< AttributeMemberName_R2 << "==other->get" << UAttribute_R2 << "());" );

			CreatePublicMembersLessThanFunctor_R2 =
				CreateInlineMethod_R2(      str_g("bool"),
											str_g("operator()"),
											EntityPointer_R2 << " elem1, " << EntityPointer_R2 << " elem2",
											str_g("const"),
											IndentationInlineMethod_R2
											<< "return (elem1 != NULL && elem2 != NULL && "
                                            << "elem1->get" << UAttribute_R2 << "()" 
											<< " < elem2->get" << UAttribute_R2 << "());" );

			CreatePublicMembersGreaterThanFunctor_R2 =
				CreateInlineMethod_R2(      str_g("bool"),
											str_g("operator()"),
											EntityPointer_R2 << " elem1, " << EntityPointer_R2 << " elem2",
											str_g("const"),
											IndentationInlineMethod_R2 
											<< "return (elem1 != NULL && elem2 != NULL && "
                                            << "elem1->get" << UAttribute_R2 << "()" 
											<< " > elem2->get" << UAttribute_R2 << "());" );
		}
    }
}
