#include "SimpleHPPEntityGenerator.hpp"

namespace dsg {

	namespace generator {

		SimpleHPPEntityGenerator::SimpleHPPEntityGenerator()
		{
			SourceHPP_R2 = 
				CreateFile_R2;

			CreateFile_R2 =
                CreateHeader_R2(file_g(getFileNameHandler(KIND_ALIAS)) << ".hpp")
                << CreateHPPDefine_R2("_" << file_g(getFileNameHandler(KIND_ALIAS)) << "_hpp_")
				<< CreateInclude_R2
				<< CreateMacro_R2
				<< CreateNamespace_R2(str_g("data_access"))
				<< AccessClassDeclaration_R2    [ent0, entN]
				<< CreateEndNamespace_R2
				<< CreateNamespace_R2(str_g("entity"))
				<< CreateUsingNamespace_R2
				<< (CreateForwardDeclaration_R2
				<<  CommentEntityClass_R2
				<<  CreateEntityClass_R2)       [ent0, entN]
				<< CreateEndNamespace_R2
				<< CreateEndMacro_R2
				<< CreateEndInclude_R2
				<< CreateHPPEndDefine_R2;            

			CreateInclude_R2 =
				str_g(   "#include <boost/serialization/serialization.hpp>\r\n"
						 "#include <boost/serialization/shared_ptr.hpp>\r\n")[call_g(getIsWorkspaceOptionHandler(BOOST_SERIAL))]
				<< str_g("#include <boost/shared_ptr.hpp>\r\n"
                         "#include <boost/container/vector.hpp>\r\n"
                         "#include \"copy_ptr.h\"\r\n"                         
						 "#include \"config.hpp\"\r\n"
						 "#include \"convert.hpp\"\r\n"
                         "#include \"encoding.hpp\"\r\n\r\n")
                << (str_g("#include \"") << call_g(getWorkspaceNameHandler()) << "Export.hpp\"\r\n");

			CreateEndInclude_R2 =
                str_g("#include \"") << file_g(getFileNameHandler(KIND_ALIAS)) << "Predicate.hpp\"\r\n\r\n";

			CreateUsingNamespace_R2 =
				str_g(  "using namespace log4cpp;\r\n"
						"using namespace fctr;\r\n"
						"using namespace enc;\r\n"
                        "using namespace boost;\r\n\r\n");

			CreateForwardDeclaration_R2 =
				ListRelationN_R2(RelationNClassDeclaration_R2)
				<< ListRelation1_R2(Relation1ClassDeclaration_R2);

			CreatePrivateMembers_R2 =
				CreateAttributes_R2
				<< CreateRelation_R2
				<< CreateSerialization_R2   [call_g(getIsWorkspaceOptionHandler(BOOST_SERIAL))];

			CreateProtectedMembers_R2 =
				(str_g("\tfriend class data_access::") << AccessClass_R2 << ";\r\n\r\n"
				<< CommentEntityConstructor3_R2
				<< CreateEntityConstructor3_R2
				<< ListAttribute_R2(
                   (CommentSetAttribute_R2
				<<  MethodSetAttribute_R2)  [If_IsID_R2]))
											[has_g(0, set_g((attr0,attrN), If_IsID_R2 && If_IsREF_R2), eq_g())];

			CreatePublicMembers_R2 =
				CommentEntityConstructor_R2
				<< CreateEntityConstructor_R2
				<< ( CommentEntityConstructor2_R2
                <<   CreateEntityConstructor2_R2 )  [has_g(0, set_g((attr0,attrN), !If_IsID_R2 && !If_IsREF_R2), gt_g())]  // au moins un attribut qui ne soit pas ID
													[has_g(0, set_g((attr0,attrN), If_IsID_R2 && If_IsREF_R2), eq_g())]    // il ne faut qu'un attribut soit � la fois une REF et un ID
				<< ( CommentEntityConstructor3_R2
				<<   CreateEntityConstructor3_R2 )  [has_g(0, set_g((attr0,attrN), If_IsID_R2 && If_IsREF_R2), gt_g())]
                << CommentEntityCopyConstructor_R2
                << CreateEntityCopyConstructor_R2
                << CommentEntityAssignOperator_R2
                << CreateEntityAssignOperator_R2
                << CreateMethodsAttribute_R2
                << CreateIteratorsRelation_R2
				<< CreateMethodsRelation_R2
				<< CommentPrintConsole_R2
				<< CreatePrintConsole_R2
				<< CommentFriendOperatorStream_R2
				<< CreateFriendOperatorStream_R2
				<< CreatePredicateClass_R2;

			CreateEntityClass_R2 =
				CreateTClass_R2(UEntity_R2, CreatePrivateMembers_R2, CreateProtectedMembers_R2, CreatePublicMembers_R2);
	    
			// members management
			CreateAttributes_R2 =
				ListAttribute_R2(AttributeMember_R2);

			CreateEntityInit_R2 =
				CreateInit_R2(  AttributeMemberName_R2, 
								str_g("-1")                 [If_IsNUMBER_R2 && If_IsID_R2]
								<< str_g("0")               [If_IsNUMBER_R2 && !If_IsID_R2]
								<< str_g("EncodingT::EMPTY")[If_IsTEXT_R2])[!If_IsREF_R2 && If_IsInitializable_R2][attr0, attrN];

			CreateEntityConstructor_R2 =
				CreateInlineTConstructor_R2(UEntity_R2, 
											str_g(""), 
											CreateEntityInit_R2 );

			CreateEntityParam2_R2 =
				(AttributeConstReference_R2 << SpaceParam_R2 << LAttribute_R2 << ~-CommaParam_R2)    
															[!If_IsREF_R2 && !If_IsID_R2][attr0, attrN];

			CreateEntityInit2_R2 =
				ListAttribute_R2(
                    CreateInit_R2(  AttributeMemberName_R2, 
								str_g("-1")                 [If_IsNUMBER_R2 && If_IsID_R2]
								<< str_g("EncodingT::EMPTY")[If_IsTEXT_R2   && If_IsID_R2]
								<< LAttribute_R2            [!If_IsID_R2])[!If_IsREF_R2] );

			CreateEntityPrint2_R2 =
                ListAttribute_R2(
				    CreatePrint_R2( AttributeVariable_R2(AttributeMemberName_R2) )  
                                                            [If_IsPrintable_R2][!If_IsREF_R2] );

			CreateEntityConstructor2_R2 =
				CreateInlineTConstructor_R2(    UEntity_R2, 
												CreateEntityParam2_R2, 
												CreateEntityInit2_R2,
												CreateEntityPrint2_R2 );

			CreateEntityParam3_R2 =
                ListAttribute_R2(
				    (AttributeConstReference_R2 << SpaceParam_R2 << LAttribute_R2 << ~-CommaParam_R2)    
																			[!If_IsREF_R2 || If_IsID_R2] );

			CreateEntityInit3_R2 =
                ListAttribute_R2(
				    CreateInit_R2(  AttributeMemberName_R2,
								    AttributeInit_R2(LAttribute_R2) )           [!If_IsREF_R2 || If_IsID_R2] );

			CreateEntityPrint3_R2 =
                ListAttribute_R2(
				    CreatePrint_R2( AttributeVariable_R2(AttributeMemberName_R2) ) 
                                                                            [If_IsPrintable_R2][!If_IsREF_R2 || If_IsID_R2] );

			CreateEntityConstructor3_R2 =
				CreateInlineTConstructor_R2(    UEntity_R2, 
												CreateEntityParam3_R2, 
												CreateEntityInit3_R2,
												CreateEntityPrint3_R2 );

            CreateEntityAssignOperator_R2 =
				CreateInlineMethod_R2(  EntityReference_R2,
										str_g("operator="),
										EntityConstReference_R2 << " elem",
										str_g(""),
                                        (line_g(1) << htab_g(2) << AttributeMemberName_R2 << " = " << AttributeCopy_R2("elem." << AttributeMemberName_R2) << ";")[attr0, attrN]
										<< ListRelationN_R2(line_g(1) << htab_g(2) << RelationNMemberName_R2 << " = copy_ptr(elem." << RelationNMemberName_R2 << ");")
                                        << line_g(1) << htab_g(2) << "return *this;" );

            CreateEntityCopyConstructor_R2 =
				CreateInlineTConstructor_R2(  UEntity_R2,
										      EntityConstReference_R2 << " elem",
										      (str_g(": ")
                                              << (AttributeMemberName_R2 << "(" << AttributeCopy_R2("elem." << AttributeMemberName_R2) << ')' << ~-str_g(",\r\n\t  "))[attr0, attrN]
                                              << str_g(",\r\n\t  ") [has_g(0, RelationN, gt_g()) && has_g(0, (attr0, attrN), gt_g())]
                                              << ListRelationN_R2(RelationNMemberName_R2 << "(copy_ptr(elem."<< RelationNMemberName_R2 << "))" << ~-str_g(",\r\n\t  "))
                                              << str_g("\r\n\t"))   [has_g(0, RelationN, gt_g()) || has_g(0, (attr0, attrN), gt_g())],
                                              str_g(" << \": copy\"") );

			CreateMethodsAttribute_R2 =
				ListAttribute_R2(  
                   CommentGetAttribute_R2
				<< MethodGetAttribute_R2
				<< (CommentSetAttribute_R2
				<< MethodSetAttribute_R2 )          [!If_IsID_R2 || has_g(0, set_g((attr0,attrN), If_IsID_R2 && If_IsREF_R2), gt_g())]
				<< ( CommentIsNullREF_R2
				<< MethodIsNullREF_R2
				<< CommentEraseREF_R2
				<< MethodEraseREF_R2)               [If_IsREF_R2]);
	        
			MethodGetAttribute_R2 = 
				CreateInlineGetMethod_R2(   AttributeConstReference_R2, 
											UAttribute_R2, 
											IndentationInlineMethod_R2 << "return " << AttributeVariable_R2(AttributeMemberName_R2) << ";");

			MethodSetAttribute_R2 =
				CreateInlineSetMethod_R2(   UAttribute_R2,
											AttributeConstReference_R2 << SpaceParam_R2 << LAttribute_R2,
											IndentationInlineMethod_R2 << AttributeAssignment_R2(AttributeMemberName_R2, AttributeInit_R2(LAttribute_R2)) << ";");

			MethodIsNullREF_R2 =
				CreateInlineMethod_R2(  str_g("bool"),
										str_g("isNull") << UAttribute_R2,
										str_g(""),
										str_g("const"),
										IndentationInlineMethod_R2 << "return !" << AttributeMemberName_R2 << ";");

			MethodEraseREF_R2 =
				CreateInlineMethod_R2(  str_g("void"),
										str_g("erase") << UAttribute_R2,
										str_g(""),
										str_g(""),
										IndentationInlineMethod_R2 << AttributeMemberName_R2 << ".reset();");

			MethodGetREF_R2 =
				CreateInlineMethod_R2(  AttributeReference_R2,
										str_g("get") << UAttribute_R2,
										str_g(""),
										str_g(""),
										IndentationInlineMethod_R2 << "return " << AttributeVariable_R2(AttributeMemberName_R2) << ";");

			/// Relation Management
			CreateRelation_R2 =
				ListRelationN_R2(RelationNTypedef_R2 << RelationNMember_R2);

            CreateIteratorsRelation_R2 =
                ListRelationN_R2(CommentIterator_R2
				<< Iterator_R2);

			CreateMethodsRelation_R2 =
				ListRelationN_R2(CommentMethodBegin_R2
				<< MethodBegin_R2
				<< CommentMethodEnd_R2
				<< MethodEnd_R2
				<< CommentMethodConstBegin_R2
				<< MethodConstBegin_R2
				<< CommentMethodConstEnd_R2
				<< MethodConstEnd_R2
				<< CommentMethodAt_R2
				<< MethodAt_R2
				<< CommentMethodConstAt_R2
				<< MethodConstAt_R2
				<< CommentMethodSize_R2
				<< MethodSize_R2
				<< CommentMethodEmpty_R2
				<< MethodEmpty_R2
				<< CommentMethodPushBack_R2
				<< MethodPushBack_R2
				<< CommentMethodInsert0_R2
				<< MethodInsert0_R2
				<< CommentMethodInsert1_R2
				<< MethodInsert1_R2
				<< CommentMethodErase0_R2
				<< MethodErase0_R2
				<< CommentMethodErase1_R2
				<< MethodErase1_R2
				<< CommentMethodClear_R2
				<< MethodClear_R2);

            Iterator_R2 =
                CreateTypedef_R2(       str_g("typename ") << RelationNType_R2 << "::iterator", 
                                        RelationNIterator_R2)
                << CreateTypedef_R2(    str_g("typename ") << RelationNType_R2 << "::const_iterator", 
                                        RelationNConstIterator_R2)
                << "\r\n";

			MethodBegin_R2 =
				CreateInlineMethod_R2(  RelationNIterator_R2,
                                        str_g("get") << URelationNName_R2 << "sBeginning",
										str_g(""),
										str_g(""),
										IndentationInlineMethod_R2 << "return " << RelationNMemberName_R2 << ".begin();");

			MethodEnd_R2 =
				CreateInlineMethod_R2(  RelationNIterator_R2,
                                        str_g("get") << URelationNName_R2 << "sEnd",
										str_g(""),
										str_g(""),
										IndentationInlineMethod_R2 << "return " << RelationNMemberName_R2 << ".end();");

			MethodConstBegin_R2 =
				CreateInlineMethod_R2(  RelationNConstIterator_R2,
                                        str_g("get") << URelationNName_R2 << "sBeginning",
										str_g(""),
										str_g("const"),
										IndentationInlineMethod_R2 << "return " << RelationNMemberName_R2 << ".begin();");

			MethodConstEnd_R2 =
				CreateInlineMethod_R2(  RelationNConstIterator_R2,
                                        str_g("get") << URelationNName_R2 << "sEnd",
										str_g(""),
										str_g("const"),
										IndentationInlineMethod_R2 << "return " << RelationNMemberName_R2 << ".end();");
	            
			MethodAt_R2 =
				CreateInlineMethod_R2(  RelationNReference_R2,
                                        str_g("get") << URelationNName_R2 << "At",
										str_g("size_t n"),
										str_g(""),
										IndentationInlineMethod_R2 << "return " << RelationNMemberName_R2 << ".at(n);");
	            
			MethodConstAt_R2 =
				CreateInlineMethod_R2(  RelationNClass_R2,
                                        str_g("get") << URelationNName_R2 << "At",
										str_g("size_t n"),
										str_g("const"),
										IndentationInlineMethod_R2 << "return " << RelationNMemberName_R2 << ".at(n);");
	            
			MethodSize_R2 =
				CreateInlineMethod_R2(  str_g("size_t"),
                                        str_g("get") << URelationNName_R2 << "sSize",
										str_g(""),
										str_g("const"),
										IndentationInlineMethod_R2 << "return " << RelationNMemberName_R2 << ".size();");

			MethodEmpty_R2 =
				CreateInlineMethod_R2(  str_g("bool"),
                                        str_g("is") << URelationNName_R2 << "sEmpty",
										str_g(""),
										str_g("const"),
										IndentationInlineMethod_R2 << "return " << RelationNMemberName_R2 << ".empty();");    

			MethodPushBack_R2 =
				CreateInlineMethod_R2(  str_g("void"),
                                        str_g("add") << URelationNName_R2,
										RelationNClass_R2 << " o",
										str_g(""),
										IndentationInlineMethod_R2 << RelationNMemberName_R2 << ".push_back(copy_ptr(o));");    
	        
			MethodInsert0_R2 =
				CreateInlineMethod_R2(  RelationNIterator_R2,
                                        str_g("insert") << URelationNName_R2,
										RelationNIterator_R2 << " pos, " << RelationNClass_R2 << " o",
										str_g(""),
										IndentationInlineMethod_R2 << "return " << RelationNMemberName_R2 << ".insert(pos, copy_ptr(o));");    

			MethodInsert1_R2 =
				CreateInlineMethod_R2(  str_g("void"),
                                        str_g("insert") << URelationNName_R2,
										RelationNIterator_R2 << " pos, " << RelationNIterator_R2 << " first, " << RelationNIterator_R2 << " last",
										str_g(""),
                                        IndentationInlineMethod_R2 << "std::transform(first, last, std::inserter(" 
                                        << RelationNMemberName_R2 << ", pos), static_cast< " << RelationNClass_R2 << "(*)(" << RelationNClass_R2 << ") >(copy_ptr));");    
	        
			MethodErase0_R2 =
				CreateInlineMethod_R2(  RelationNIterator_R2,
                                        str_g("erase") << URelationNName_R2,
										RelationNIterator_R2 << " pos",
										str_g(""),
										IndentationInlineMethod_R2 << "return " << RelationNMemberName_R2 << ".erase(pos);");    
	            
			MethodErase1_R2 =
				CreateInlineMethod_R2(  RelationNIterator_R2,
                                        str_g("erase") << URelationNName_R2,
										RelationNIterator_R2 << " first, " << RelationNIterator_R2 << " last",
										str_g(""),
										IndentationInlineMethod_R2 << "return " << RelationNMemberName_R2 << ".erase(first, last);");    
	            
			MethodClear_R2 =
				CreateInlineMethod_R2(  str_g("void"),
                                        str_g("clear") << URelationNName_R2 << "s",
										str_g(""),
										str_g(""),
										IndentationInlineMethod_R2 << RelationNMemberName_R2 << ".clear();");    
	        
			// Functor
			CreatePredicateClass_R2 =
				str_g("\tclass ") << UEntity_R2 << "IDEquality;\r\n" 
				<< (str_g("\tclass ") << UAttribute_R2 << "Equality;\r\n"
				<< ("\tclass " << UAttribute_R2 << "Inferior;\r\n"
				<<  "\tclass " << UAttribute_R2 << "Superior;\r\n")
                    [If_IsComparable_R2])
                    [!If_IsREF_R2 && !If_IsID_R2][attr0, attrN];

			// output
			CreatePrintConsole_R2 =
				CreateInlineMethod_R2(  str_g("ostream&"),
										str_g("printConsole"),
										str_g("ostream& o"),
										str_g("const"),
										IndentationInlineMethod_R2
										<< str_g("return o << \"") << UEntity_R2 << "\""
										<< CreatePrintConsoleLine_R2( LAttribute_R2, AttributeVariable_R2(AttributeMemberName_R2))
                                                                                    [If_IsPrintable_R2]
																					[!If_IsREF_R2]
																					[attr0, attrN]
										<< str_g(";"));

			CreatePrintConsoleLine_R2 =
				str_g(" << endl") << IndentationInlineMethod_R2
				<< "         << \"" << $(0) << " : \" << "    
				<< $(1)                 [If_IsNUMBER_R2]
				<< ("A(" << $(1) << ")")[If_IsTEXT_R2];

			CreateFriendOperatorStream_R2 =
				CreateInlineMethod_R2(  str_g("friend ostream&"),
										str_g("operator<<"),
										str_g("ostream& o, ") << EntityConstReference_R2 << " elem",
										str_g(""),
										IndentationInlineMethod_R2 << "return elem.printConsole(o<<\"[ \")<<\" ]\";");

			CreateSerialization_R2 =
				str_g(  "\r\n\t"
						"friend class boost::serialization::access;\r\n\t"
						"template<class Archive>\r\n" )
				<< CommentSerialization_R2
				<< CreateInlineMethod_R2(   str_g("void"),
											str_g("serialize"),
											str_g("Archive& ar, const unsigned int file_version"),
											str_g(""),
											CreateSerializationLine_R2( LAttribute_R2, AttributeMemberName_R2)
																								[attr0, attrN]);

			CreateSerializationLine_R2 =
				IndentationInlineMethod_R2  << +str_g("ar")
											<< ~+str_g("  ")
											<< " & boost::serialization::make_nvp(\""
											<< $(0)    << "\", " << $(1) << ")" << -str_g(";");
		}
    }
}
