#include "SimpleCPPAccessGenerator.hpp"

namespace dsg {

	namespace generator {

		SimpleCPPAccessGenerator::SimpleCPPAccessGenerator()
		{
			SourceCPP_R2 = 
				CreateFile_R2;

			CreateFile_R2 =
				CreateInclude_R2
				<< CreateMacro_R2
				<< CreateNamespace_R2(str_g("data_access"))
				<< CreateUsingNamespace_R2
				<< CreateAccessClass_R2        [ent0, entN]
				<< CreateEndNamespace_R2
				<< CreateEndMacro_R2;            

			CreateInclude_R2 =
				str_g("#include \"DataConnection.hpp\"\r\n"
                      "#include \"DataParameters.hpp\"\r\n"
                      "#include \"DataStatement.hpp\"\r\n"
					  "#include \"NullPointerException.hpp\"\r\n"
					  "#include \"NoSqlRowException.hpp\"\r\n"
					  "#include \"UnIdentifiedObjectException.hpp\"\r\n"
					  "#include \"InvalidQueryException.hpp\"\r\n"
					  "#include \"UnSelectedObjectException.hpp\"\r\n"
					  "#include <algorithm> \r\n");

			CreateUsingNamespace_R2 =
				str_g("using namespace boost;\r\n"
					  "using namespace entity;\r\n\r\n");

			CreateAccessClass_R2 =
				CreateStaticAttribute_R2
				<< CreateStaticMethod_R2
				<< CreateAccessConstructor_R2
				<< CreateAccessDestructor_R2
				<< GetManyMeth_R2
                << GetAllMeth_R2
				<< GetOneMeth_R2
                << SelectManyMeth_R2
				<< SelectOneMeth_R2 
				<< IsSelectMeth_R2 
				<< CancelSelectMeth_R2
				<< ListAttribute_R2(
                     FillMeth1_R2[If_IsREF_R2 && !If_IsID_R2] )        
				<< ListRelationN_R2(
					 FillMeth2_R2
				<<   FillMeth3_R2
				<<   FillMeth4_R2 )
				<< IsUpdateMeth_R2
				<< UpdateMeth_R2
				<< InsertMeth_R2
				<< DeleteMeth_R2
                << AddInsertSignalMeth_R2
                << AddUpdateSignalMeth_R2
                << AddDeleteSignalMeth_R2
                << AddTransactionSignalMeth_R2
                << RemoveInsertSignalMeth_R2
                << RemoveUpdateSignalMeth_R2
                << RemoveDeleteSignalMeth_R2
                << RemoveTransactionSignalMeth_R2
				<< "\r\n";

			CreateStaticAttribute_R2 =
				str_g("template<class EncodingT>\r\n")
				<< AccessClass_R2 << "* " << AccessClass_R2 << "::m_instance = NULL;\r\n\r\n";
	            
			CreateStaticMethod_R2 = 
				CreateTMethod_R2(   AccessClass_R2 << "* ",
									AccessClass_R2,
									str_g("getInstance"),
									str_g(""),
									str_g(""),
									IndentationMethod_R2 << "if (m_instance == NULL) {" <<
									IndentationMethod_R2 << "\tm_instance = new " << AccessClass_R2 << "();" <<
									IndentationMethod_R2 << "}" <<
									IndentationMethod_R2 << "return m_instance;" );
	               
			CreateAccessConstructor_R2 = 
				CreateTConstructor_R2(  UAccess_R2,
										str_g(""),
										str_g(": m_transactionOwner(false) \r\n"),
										str_g(" << m_transactionOwner")
									);

			CreateAccessDestructor_R2 =
				CreateTDestructor_R2(   UAccess_R2,
										IndentationMethod_R2 << "cancelSelection();"
									);

			GetAllMeth_R2 =
                CreateGetTMethod_R2(    str_g("std::vector< boost::shared_ptr< ") << EntityClass_R2 << " > >",
										AccessClass_R2,
										str_g("All") << UEntity_R2 << "s",
										AllMethodBody_R2 );

			GetType_R2 =
				ConvertToType_R2($(0))                          [!If_IsREF_R2]
				<< (LAttribute_R2 << "Access->getOne" <<  UAttribute_R2
				<< "(" << ConvertToType_R2($(0)) << ")")        [If_IsREF_R2];

			AttrDeclarationLoop_R2 =
				( DataStatementType_R2 << " " << LAttribute_R2 << ";\r\n\t\t" ) 
                                                                [!If_IsREF_R2 || If_IsID_R2]
																[attr0, attrN];

            SetAttrLoop_R2 =
				( GetDataStatement_R2(str_g("statement"), index_g(), LAttribute_R2)
                << ~-(str_g(" &&\r\n\t\t\t")) )
																[set_g((attr0, attrN), !If_IsREF_R2 || If_IsID_R2)];

            EnumREFAttrLoop_R2 =
                (~-("boost::shared_ptr< _" << URelation1_R2 << "<EncodingT> >(new _" << URelation1_R2 << "<EncodingT>("))
                                                                [ReferencedRelations_R2]
                << $(0)
                << (~-str_g("))"))                              [ReferencedRelations_R2];

			EnumAttrLoop_R2 =
				( str_g("\r\n\t\t\t\t") 
				<< LAttribute_R2                                [!If_IsREF_R2]
                << EnumREFAttrLoop_R2(LAttribute_R2 << "Access->getOne" << GetReferencedAttribute_R2(str_g(""), UEntity_R2) << "(" << LAttribute_R2 << ")")
                                                                [If_IsREF_R2]
                << ~-str_g(",") )                               [!If_IsREF_R2 || If_IsID_R2]
																[attr0, attrN];

			SelEnumAttrLoop_R2 =
				( str_g("\r\n\t\t\t\t") 
				<< LAttribute_R2                                [!If_IsREF_R2]
                << (EnumREFAttrLoop_R2(LAttribute_R2 << "Access->selectOne" << GetReferencedAttribute_R2(str_g(""), UEntity_R2) << "(" << LAttribute_R2 << ", false, true)")
                                                                [If_HasUniqueID_R2]
                <<  EnumREFAttrLoop_R2(LAttribute_R2 << "Access->getOne" << GetReferencedAttribute_R2(str_g(""), UEntity_R2) << "(" << LAttribute_R2 << ")")
                                                                [!If_HasUniqueID_R2])
                                                                [If_IsREF_R2]
                << ~-str_g(",") )                               [!If_IsREF_R2 || If_IsID_R2]
																[attr0, attrN];

			ConvertAttrLoop_R2 =
				( str_g("\r\n\t\t\t") 
				<< GetType_R2(str_g("(") << $(0) << ")[" << index_g() << "]")
				<< ~-str_g(",") )                               [!If_IsREF_R2 || If_IsID_R2]
																[attr0, attrN];

			AttributeColumns_R2 =
                str_g("std::vector<typename EncodingT::string_t> columns;                   \r\n\t")
                << ( "columns.push_back(C(\"" << attr_g(getAttributeNameHandler(KIND_NAME)) << "\"));\r\n\t" )
																[!If_IsREF_R2 || If_IsID_R2]
																[attr0, attrN];

			InitializeAccess_R2 =
				IndentationMethod_R2
                << EncodingClass_R2($(0) << "Access") << "* " << LAttribute_R2 << "Access = "
                << EncodingClass_R2($(0) << "Access") << "::getInstance();" << IndentationMethod_R2
				<< "if (!" << LAttribute_R2 << "Access) {" << IndentationMethod_R2
                << htab() << "m_logger->errorStream() << \"" << $(0) << "Access class is not initialized.\";" << IndentationMethod_R2
                << htab() << "throw NullPointerException(\"" << $(0) << "Access class is not initialized.\");" << IndentationMethod_R2
				<< "}";

			InitializeRelationAccess_R2 =
				IndentationMethod_R2
                << EncodingClass_R2(URelationN_R2 << "Access") << "* " << LRelationNName_R2 << "Access = "
				<< EncodingClass_R2(URelationN_R2 << "Access") << "::getInstance();" << IndentationMethod_R2
                << "if (!" << LRelationNName_R2 << "Access) {" << IndentationMethod_R2
				<< htab() << "m_logger->errorStream() << \"" << URelationN_R2  << "Access class is not initialized.\";" << IndentationMethod_R2
				<< htab() << "throw NullPointerException(\"" << URelationN_R2  << "Access class is not initialized.\");" << IndentationMethod_R2
				<< "}";

			InitializeAccessLoop_R2 =
                InitializeAccess_R2(GetReferencedAttribute_R2(str_g(""), UEntity_R2))
                                        [If_IsREF_R2 && If_IsID_R2]
								        [attr0, attrN];

			AllMethodDecl_R2 =
                IndentationMethod_R2 << "boost::shared_ptr< " << EntityClass_R2 << " > value;" <<
                IndentationMethod_R2 << "_DataStatement<EncodingT> statement;" <<
                IndentationMethod_R2 << "std::vector< boost::shared_ptr< " << EntityClass_R2 << " > > tab;";

			AllMethodBody_R2 =
                str_g("\r\n\treturn getMany") << UEntity_R2 << "s(EncodingT::EMPTY);";


			GetManyMeth_R2 =
                CreateTMethod_R2(   str_g("std::vector< boost::shared_ptr< ") << EntityClass_R2 << " > >",
									AccessClass_R2,
									str_g("getMany") << UEntity_R2 << "s",
									str_g("typename EncodingT::string_t const&  filter"),
									str_g("const"),
									ManyMethodBody_R2 );

			ManyMethodBody_R2 =
				AllMethodDecl_R2
				<< InitializeConnection_R2
				<< InitializeAccessLoop_R2
				<< "\r\n\t"
				<< AttributeColumns_R2
                << "statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,C(\"" << ent_g(getEntityNameHandler(KIND_NAME)) << "\")), filter) );" "\r\n\t"
				   "while( statement.executeStep() ) {"                                       "\r\n\t\t"
                << AttrDeclarationLoop_R2
                << "if (" << SetAttrLoop_R2 << ") {"                                          "\r\n\t\t\t" 
				   "value.reset(new " << EntityClass_R2 << "(" << EnumAttrLoop_R2 << "));"    "\r\n\t\t\t"
				   "tab.push_back(value);"                                                    "\r\n\t\t"
                   "}"                                                                        "\r\n\t"
				   "}"                                                                        "\r\n\t"
				   "return tab;";

			GetOneMeth_R2 =
                CreateTMethod_R2(   "boost::shared_ptr< " << EntityClass_R2 << " >",
									AccessClass_R2,
									str_g("getOne") << UEntity_R2,
									AttributeIDParam_R2,
									str_g("const"),
									OneMethodBody_R2 );


			ConvertCStringLoop_R2 =
				( +str_g("C(\"") 
                << attr_g(getAttributeNameHandler(KIND_NAME)) << " = \") /*+ C(\"\\'\") */+ "
				<< ConvertToCString_R2( $(0)  )    
                << "/* + C(\"\\'\")*/" << ~-str_g(" + C(\" AND ") ) [If_IsID_R2]
                                                                    [attr0, attrN];

			VerifyPTR_R2 =
				str_g("\r\n\tif (!") 
                << $(0) << ") {\r\n\t\t"
				<< "m_logger->errorStream() << \"Parameter is null.\";\r\n\t\t"
				   "throw NullPointerException(\"Parameter is null.\");\r\n\t"
				   "}";

			VerifyRELATION_R2 =
				str_g("\r\n\t\t\tif (!") 
                << $(0) << ") {\r\n\t\t\t\t"
				<< "m_logger->errorStream() << \"Aggregate is null.\";\r\n\t\t\t\t"
				   "throw NullPointerException(\"Aggregate is null.\");\r\n\t\t\t"
				   "}";

			VerifyRELATION2_R2 =
				str_g("\r\n\t\tif (!") 
                << $(0) << ") {\r\n\t\t\t"
				<< "m_logger->errorStream() << \"Aggregate is null.\";\r\n\t\t\t"
				   "throw NullPointerException(\"Aggregate is null.\");\r\n\t\t"
				   "}";

			VerifyID_R2 =
				( str_g("\r\n\tif ( ") 
                << ($(0) << "==" << str_g("EncodingT::EMPTY")[If_IsTEXT_R2]
								 << str_g("-1")              [If_IsNUMBER_R2])
                                                             [!If_IsREF_R2]
                << (((+$(1) << ~+("->get" << URelation1Name_R2 << "()"))
                                                             [leading_g<rel_context>()]
                << " == NULL || ")
                                                             [ReferencedRelations_R2]
                << "typename _" << GetReferencedAttribute_R2(str_g(""), UEntity_R2)
                << "<EncodingT>::" << GetReferencedAttribute_R2(str_g(""), UEntity_R2) << "IDEquality(-1)("
                << (+$(1) << ~+("->get" << URelation1Name_R2 << "()"))
                                                             [ReferencedRelations_R2]
                << ")")                                      [If_IsREF_R2]
                << " ) {\r\n\t\t"
				<< "m_logger->errorStream() << \"" << UAttribute_R2 << " : Identifier is null.\";\r\n\t\t"
				   "throw UnIdentifiedObjectException(\"" << UAttribute_R2 << " : Identifier is null.\");\r\n\t"
				   "}")                                     [If_IsID_R2]
															[attr0, attrN];
            
            VerifyREF_R2 =
                ($(0) << "->isNull" << UAttribute_R2 << "() || ") [If_IsREF_R2];

			OneMethodBody_R2 =
                VerifyID_R2(LAttribute_R2, LRelation1Name_R2)
                << "\r\n\t"
                   "std::vector< boost::shared_ptr< " << EntityClass_R2 << " > > result = getMany" << UEntity_R2 << "s("
                << ConvertCStringLoop_R2(AttributeId_R2(LAttribute_R2))
                << ");"                                                               "\r\n\t"
				   "if (result.size()==0) {"                                          "\r\n\t\t"
				   "m_logger->errorStream() << \"identifier not found.\";"            "\r\n\t\t"
				   "throw NoSqlRowException(\"identifier not found.\");"              "\r\n\t"
				   "}"                                                                "\r\n\t"
				   "return result.back();";

			SelectOneMeth_R2 =
                CreateTMethod_R2(   "boost::shared_ptr< " << EntityClass_R2 << " >",
									AccessClass_R2,
									str_g("selectOne") << UEntity_R2,
									AttributeIDParam_R2 << ", bool nowait, bool addition",
									str_g(""),
									SelOneMethodBody_R2 );

			SelOneMethodBody_R2 =
                VerifyID_R2(LAttribute_R2, LRelation1Name_R2)
                << "\r\n\t"
                   "std::vector< boost::shared_ptr< " << EntityClass_R2 << " > > result = selectMany" << UEntity_R2 << "s("
                << ConvertCStringLoop_R2(AttributeId_R2(LAttribute_R2))
                << ", nowait, addition);\r\n\t"
				   "if (result.size()==0) {"                                          "\r\n\t\t"
				   "m_logger->errorStream() << \"identifier not found.\";"            "\r\n\t\t"
				   "throw NoSqlRowException(\"identifier not found.\");"              "\r\n\t"
				   "}"                                                                "\r\n\t"
				   "return result.back();";

			SelectManyMeth_R2 =
                CreateTMethod_R2(   str_g("std::vector< boost::shared_ptr< ") << EntityClass_R2 << " > >",
									AccessClass_R2,
									str_g("selectMany") << UEntity_R2 << "s",
									str_g("typename EncodingT::string_t const&  filter, bool nowait, bool addition"),
									str_g(""),
									SelManyMethodBody_R2 );

			SelManyMethodBody_R2 =
				IndentationMethod_R2 << "_DataStatement<EncodingT> statement;"
                << IndentationMethod_R2 << "std::vector< boost::shared_ptr< " << EntityClass_R2 << " > > tab;"
				<< InitializeConnection_R2
				<< InitializeAccessLoop_R2
				<< "\r\n\t"
				<< AttributeColumns_R2
                << "if (!addition || !connection->isTransactionInProgress()) {"             "\r\n\t\t"
                   "cancelSelection();"                                                     "\r\n\t\t"
				   "m_transactionOwner = !connection->isTransactionInProgress();"           "\r\n\t\t"
                   "if (m_transactionOwner) {"                                              "\r\n\t\t\t"
                   "connection->startTransaction();"                                        "\r\n\t\t\t"
                   "m_transactionSignal(OPERATION_ACCESS_START);"                           "\r\n\t\t"
                   "}"                                                                      "\r\n\t"
                   "}"                                                                      "\r\n\t"
                   "statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,C(\"" << ent_g(getEntityNameHandler(KIND_NAME)) << "\")), filter, nowait) );\r\n\t"
				   "while( statement.executeStep() ) {"                                     "\r\n\t\t"
                << AttrDeclarationLoop_R2
                << "if (" << SetAttrLoop_R2 << ") {"                                        "\r\n\t\t\t" 
                   "tab.push_back(boost::shared_ptr< " << EntityClass_R2 << " >(new " << EntityClass_R2 << "(" << SelEnumAttrLoop_R2 << ")));\r\n\t\t"
				   "}"                                                                      "\r\n\t"
				   "}"                                                                      "\r\n\t"
                   "m_backup.insert(m_backup.end(), tab.begin(), tab.end());"               "\r\n\t"
				   "return copy_ptr(tab);";

			CancelSelectMeth_R2 =
				CreateTMethod_R2(   str_g("void"),
									AccessClass_R2,
									str_g("cancelSelection"),
									str_g(""),
									str_g(""),
									InitializeConnection_R2
                                    << InitializeAccessLoop_R2 [If_HasUniqueID_R2]
                                    << ListRelationN_R2(InitializeRelationAccess_R2)
									<< "\r\n\t"
                    	            "if (!m_backup.empty()) {"          "\r\n\t\t"
                                    "if (connection->isTransactionInProgress() && m_transactionOwner) {\r\n\t\t\t"
									"connection->rollback();"           "\r\n\t\t\t"
                                    "m_transactionOwner = false;"       "\r\n\t\t\t"
                                    "m_transactionSignal(OPERATION_ACCESS_ROLLBACK);\r\n\t\t"
                                    "}"                                 "\r\n\t\t"
		                            "m_backup.clear();"                 "\r\n\t"
                                    << ListRelationN_R2(str_g("\t") << LRelationNName_R2 << "Access->cancelSelection();\r\n\t")
                                    << ListRelationPB_R2(str_g("\t") << LAttribute_R2 << "Access->cancelSelection();\r\n\t")
	                                << "}"
							 );

			IsSelectMeth_R2 =
				CreateTMethod_R2(   str_g("bool"),
									AccessClass_R2,
									str_g("isSelected") << UEntity_R2,
                                    "boost::shared_ptr< " << EntityClass_R2 << " > o",
                                    str_g("const"),
                                    VerifyPTR_R2(str_g("o"))
                                    << VerifyID_R2(Accessor_R2(str_g("o")), RelationAccessor_R2(str_g("o")))
									<< "\r\n\t"
									<< EntityEqualFunctor_R2( LEntity_R2 << "IdEquality", str_g("*o") ) 
									<< "\r\n\t"
									"return (!m_backup.empty() && (std::find_if(m_backup.begin(), m_backup.end(), " << LEntity_R2 << "IdEquality)!=m_backup.end()));"
							 );

			EntityEqualFunctor_R2 =
				str_g("typename ") << EntityClass_R2 << "::" << UEntity_R2 << "IDEquality " << $(0) << "(" << $(1) << ");";

			RelationNEqualFunctor_R2 =
				str_g("typename ") << EncodingClass_R2(URelationN_R2) << "::" << URelationN_R2 << "IDEquality " << $(0) << "(" << $(1) << ");";

			FillMeth1_R2 =
				CreateTMethod_R2(   str_g("void"),
									AccessClass_R2,
									str_g("fill") << UAttribute_R2,
                                    "boost::shared_ptr< " << EntityClass_R2 << " > o",
									str_g(""),
									FillMeth1Body_R2
								);

			FillMeth1Body_R2 =
                VerifyPTR_R2(str_g("o"))
                << VerifyID_R2( Accessor_R2(str_g("o")), RelationAccessor_R2(str_g("o")) )
                << "\r\n\t"
                << "_DataStatement<EncodingT> statement;"
				<< InitializeConnection_R2
                << GetReferencedAttribute_R2(InitializeAccess_R2(AttributeClassName_R2))
				<< "\r\n\t"
				<< AttributeValueType_R2 << " id;"                                                  "\r\n\t"
                << "statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,C(\"" << attr_g(getAttributeNameHandler(KIND_NAME))
                << "\")), std::vector<typename EncodingT::string_t>(1,C(\"" << ent_g(getEntityNameHandler(KIND_NAME)) << "\")), "
				<< ConvertCStringLoop_R2(AttributeAccessor_R2(Accessor_R2(str_g("o")))) << ") );"   "\r\n\t"
                   "if( statement.executeStep() && "
                << GetDataStatement_R2(str_g("statement"), str_g("0"), str_g("id")) << " && id != 0 ) {\r\n\t\t"
                << EntityEqualFunctor_R2( LEntity_R2 << "IdEquality", IDParamName_R2(Accessor_R2(str_g("o"))) )
                << "\r\n\t\t"
                << AttributeType_R2 << " val = "
                << GetReferencedAttribute_R2(LAttribute_R2 << "Access->getOne" << AttributeClassName_R2 << "(", str_g("id"), str_g(")"))
                << ";"                                                                              "\r\n\t\t"
                   "typename std::vector< boost::shared_ptr<" << EntityClass_R2 << " > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), " << LEntity_R2 << "IdEquality);\r\n\t\t"
                   "if (save != m_backup.end()) {"                                                  "\r\n\t\t\t"
                   "(*save)->set" << UAttribute_R2 << "(val);"                                      "\r\n\t\t"
                   "}"                                                                              "\r\n\t\t"
                   "o->set" << UAttribute_R2 << "(val);"                                            "\r\n\t"
                   "}"                                                                              "\r\n\t"
                   "else {"                                                                         "\r\n\t\t"
                << (str_g("m_logger->errorStream() << \"identifier not found.\";"                   "\r\n\t\t"
                          "throw NoSqlRowException(\"identifier not found.\");"                     "\r\n\t")
                   [If_IsNotNULL_R2]
                <<  str_g("m_logger->debugStream() << \"identifier not found.\";"                   "\r\n\t")
                   [!If_IsNotNULL_R2])
                   [relationsByAttr(FILTER_TARGET)]
                << "}";

			FillMeth2_R2 = 
				CreateTMethod_R2(   str_g("void"),
									EncodingClass_R2(URelation1_R2 << "Access"),
                                    str_g("fillAll") << URelationNName_R2 << "s",
                                    "boost::shared_ptr< " << Relation1Class_R2 << " > o, bool nowait",
									str_g(""),
									FillMeth2Body_R2
								);

			FillMeth2Body_R2 =
                str_g("\r\n\tfillMany") << URelationNName_R2 << "s(o, EncodingT::EMPTY, nowait);";

			FillMeth3_R2 = 
				CreateTMethod_R2(   str_g("void"),
									EncodingClass_R2(URelation1_R2 << "Access"),
                                    str_g("fillOne") << URelationNName_R2,
                                    "boost::shared_ptr< " << Relation1Class_R2 << " > o"
									<< (", " << AttributeConstReference_R2 << SpaceParam_R2 << LAttribute_R2)    
																							[If_IsID_R2]
																							[attr0, attrN]
																							[entitiesByRel(FILTER_TARGET|FILTER_ERASE_REF)] 
									<< ", bool nowait",
									str_g(""),
									FillMeth3Body_R2
								);

			FillMeth3Body_R2 =
                str_g("\r\n\tfillMany") << URelationNName_R2 << "s(o, "
                << (( +str_g("C(\"") 
                << attr_g(getAttributeNameHandler(KIND_NAME)) << " = \") /*+ C(\"\\'\") */+ "
				<< ConvertToCString_R2( AttributeAccessor_R2(LAttribute_R2) )    
                << "/* + C(\"\\'\")*/" << ~-str_g(" + C(\" AND ") ) [If_IsID_R2]
																    [attr0, attrN]
                                                                    [has_g(0, set_g((attr0,attrN), If_IsID_R2), gt_g())]
                << str_g("EncodingT::EMPTY")
                                                                    [has_g(0, set_g((attr0,attrN), If_IsID_R2), eq_g())])
                                                                    [entitiesByRel(FILTER_TARGET|FILTER_ERASE_REF)] 
                << ", nowait);";

			FillMeth4_R2 = 
				CreateTMethod_R2(   str_g("void"),
									EncodingClass_R2(URelation1_R2 << "Access"),
                                    str_g("fillMany") << URelationNName_R2 << "s",
                                    "boost::shared_ptr< " << Relation1Class_R2 << " > o, typename EncodingT::string_t const& filter, bool nowait",
									str_g(""),
									FillMeth4Body_R2
								);

			FillMeth4Body_R2 =
				VerifyPTR_R2(str_g("o"))
                << VerifyID_R2( Accessor_R2(str_g("o")), RelationAccessor_R2(str_g("o")) )
                                                                                [entitiesByRel(FILTER_SOURCE)]
			    << InitializeRelationAccess_R2
				<< "\r\n\t"
                   "std::vector< boost::shared_ptr< " << EncodingClass_R2(URelationN_R2) << " > > tab;"    "\r\n\t"
                   "typename EncodingT::string_t " << LRelationN_R2 << "Filter = " 
                   "C(\"" << rel_g(getRelationTargetRefHandler(KIND_NAME)) << " = \") + "
                << ConvertToCString_R2(AttributeAccessor_R2(Accessor_R2(str_g("o"))))
                                                                                [If_IsID_R2][attr0, attrN]
                                                                                [entitiesByRel(FILTER_SOURCE)] 
                << ";"                                                                              "\r\n\t"
                   "if (!filter.empty()) {"                                                         "\r\n\t\t"
                << LRelationN_R2 << "Filter += C(\" AND \") + filter;"                              "\r\n\t"
                   "}"                                                                              "\r\n\t"
                << EntityEqualFunctor_R2( LEntity_R2 << "IdEquality", IDParamName_R2(Accessor_R2(str_g("o"))) )
																			    [entitiesByRel(FILTER_SOURCE)]
                << "\r\n\t"
                    "typename std::vector< boost::shared_ptr< " << Relation1Class_R2 << " > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), " << LRelation1_R2 << "IdEquality);\r\n\t"
				   "if (save != m_backup.end())"                                                    "\r\n\t"
				   "{"                                                                              "\r\n\t\t"
                   "tab = " << LRelationNName_R2 << "Access->selectMany" << URelationN_R2
				<< "s(" << LRelationN_R2 << "Filter, nowait);"                                      "\r\n\t\t"
                   "(*save)->clear" << URelationNName_R2 << "s();"                                         "\r\n\t\t"
                   "(*save)->insert" << URelationNName_R2 << "((*save)->get" << URelationNName_R2 << "sEnd(), tab.begin(), tab.end());\r\n\t"
				   "}"                                                                              "\r\n\t"
				   "else"                                                                           "\r\n\t"
				   "{"                                                                              "\r\n\t\t"
                   "tab = " << LRelationNName_R2 << "Access->getMany" << URelationN_R2
				<< "s(" << LRelationN_R2 << "Filter);"                                              "\r\n\t"
				   "}"                                                                              "\r\n\t"
                   "o->clear" << URelationNName_R2 << "s();"                                             "\r\n\t"
                   "o->insert" << URelationNName_R2 << "(o->get" << URelationNName_R2 << "sEnd(), tab.begin(), tab.end());";

			IsUpdateMeth_R2 =
				CreateTMethod_R2(   str_g("bool"),
									AccessClass_R2,
									str_g("isModified") << UEntity_R2,
                                    "boost::shared_ptr< " << EntityClass_R2 << " > o",
									str_g("const"),
									IsUpdateMethBody_R2
								);

			IsUpdateMethBody_R2 =
				VerifyPTR_R2(str_g("o"))
                << VerifyID_R2( Accessor_R2(str_g("o")), RelationAccessor_R2(str_g("o")) )
                << InitializeAccessLoop_R2 [If_HasUniqueID_R2]
                << ListRelationN_R2(InitializeRelationAccess_R2)
				<< "\r\n\t"
				<< EntityEqualFunctor_R2( LEntity_R2 << "IdEquality", str_g("*o") )
				<< "\r\n\t"
                   "typename std::vector< boost::shared_ptr< " << EntityClass_R2 << " > >::const_iterator save = std::find_if(m_backup.begin(), m_backup.end(), " << LEntity_R2 << "IdEquality);\r\n\t"
				   "if (save == m_backup.end()) {"                                                  "\r\n\t\t"
				   "m_logger->errorStream() << \"You must select object before update.\";"          "\r\n\t\t"
				   "throw UnSelectedObjectException(\"You must select object before update.\");"    "\r\n\t"
				   "}"                                                                              "\r\n\t"
				   "bool bUpdate = false;"                                                          "\r\n\t"    
				<< ("bUpdate = bUpdate || ((*save)->get" << UAttribute_R2 << "() != o->get" << UAttribute_R2 << "());"    "\r\n\t")
															[!If_IsREF_R2 && !If_IsID_R2]
															[attr0, attrN]
				<< ("bUpdate = bUpdate "
                    "|| (!(*save)->isNull" << UAttribute_R2 << "() "
					"&& !o->isNull" << UAttribute_R2 << "() "
                    "&& !typename " << AttributeClass_R2 << "::" << AttributeClassName_R2 << "IDEquality(*"
                    << Accessor_R2(str_g("(*save)")) << ")(" << Accessor_R2(str_g("o")) << "))"     "\r\n\t\t"
					"|| ((*save)->isNull" << UAttribute_R2 << "() "
					"&& !o->isNull" << UAttribute_R2 << "()) "                                      "\r\n\t\t"
					"|| (!(*save)->isNull" << UAttribute_R2 << "() "
					"&& o->isNull" << UAttribute_R2 << "());"                                      "\r\n\t")
															[If_IsREF_R2 && !If_IsID_R2]
															[attr0, attrN]
				<< ListRelationN_R2(
                   "typename " << Relation1Class_R2 << "::"<< RelationNIterator_R2 << " " << LRelationNName_R2 << ";\r\n\t"
                   "for ( " << LRelationNName_R2 << "=o->get"<< URelationNName_R2 << "sBeginning(); "
                << LRelationNName_R2 << "!=o->get" << URelationNName_R2 << "sEnd(); ++" << LRelationNName_R2 << " ) {"
                << VerifyRELATION2_R2("(*" << LRelationNName_R2 << ")")
                << "\r\n\t\t"
                << RelationNEqualFunctor_R2(LRelationNName_R2 << "IdEquality", "*(*" << LRelationNName_R2 << ")")
				<< "\r\n\t\t"
                   "bUpdate = bUpdate || (std::find_if((*save)->get" << URelationNName_R2 << "sBeginning(), (*save)->get" << URelationNName_R2
                << "sEnd(), " << LRelationNName_R2 << "IdEquality) == (*save)->get" << URelationNName_R2 << "sEnd())\r\n\t\t\t"
                   "|| (" << LRelationNName_R2 << "Access->isModified" << URelationN_R2 << "(*" << LRelationNName_R2 << "));\r\n\t"
                   "}"                                                                              "\r\n\t"
                   "for ( " << LRelationNName_R2 << "=(*save)->get" << URelationNName_R2 << "sBeginning(); "
                << LRelationNName_R2 << "<(*save)->get" << URelationNName_R2 << "sEnd(); ++" << LRelationNName_R2 << " ) {"
                << VerifyRELATION2_R2("(*" << LRelationNName_R2 << ")")
                << "\r\n\t\t"
                << RelationNEqualFunctor_R2(LRelationNName_R2 << "IdEquality", "*(*" << LRelationNName_R2 << ")")
				<< "\r\n\t\t"
                   "bUpdate = bUpdate || (std::find_if(o->get" << URelationNName_R2    << "sBeginning(), o->get" << URelationNName_R2
                << "sEnd(), " << LRelationNName_R2 << "IdEquality) == o->get" << URelationNName_R2 << "sEnd());\r\n\t"
				   "}"                                                                              "\r\n\t")
                << ListRelationPB_R2(
                   "bUpdate = bUpdate || "
                << LAttribute_R2 << "Access->isModified" << AttributeClassName_R2 << "(" << Accessor_R2(str_g("o")) << ");\r\n\t")
				<< "return bUpdate;";

			UpdateMeth_R2 =
				CreateTMethod_R2(   str_g("void"),
									AccessClass_R2,
									str_g("update") << UEntity_R2,
                                    "boost::shared_ptr< " << EntityClass_R2 << " > o",
									str_g(""),
									UpdateMethBody_R2
								);

			UpdateMethBody_R2 = 
				   VerifyPTR_R2(str_g("o"))
				<< "\r\n\t"
				   "_DataParameters<EncodingT> values;"                                                    "\r\n\t"
                   "_DataStatement<EncodingT> statement;"                                                  "\r\n\t"
                   "std::vector<typename EncodingT::string_t> fields;"
                << VerifyID_R2( Accessor_R2(str_g("o")), RelationAccessor_R2(str_g("o")) )
				<< InitializeConnection_R2
                << InitializeAccessLoop_R2 [If_HasUniqueID_R2]
				<< ListRelationN_R2(InitializeRelationAccess_R2)
				<< "\r\n\t"
				<< EntityEqualFunctor_R2( LEntity_R2 << "IdEquality", str_g("*o") )
				<< "\r\n\t"
                   "typename std::vector< boost::shared_ptr< " << EntityClass_R2 << " > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), " << LEntity_R2 << "IdEquality);\r\n\t"
				   "if (save == m_backup.end()) {"                                                         "\r\n\t\t"
				   "m_logger->errorStream() << \"You must select object before update.\";"                 "\r\n\t\t"
				   "throw UnSelectedObjectException(\"You must select object before update.\");"           "\r\n\t"
				   "}"                                                                                     "\r\n\t"
                   "try {"                                                                                 "\r\n\t\t"
				<< ("if ( (*save)->get" << UAttribute_R2 << "() != o->get" << UAttribute_R2 << "() ) {"     "\r\n\t\t\t"
				<< AddDataParameter_R2(str_g("values"),Accessor_R2(str_g("o"))) <<                         "\r\n\t\t\t"
                   "fields.push_back( C(\"" << attr_g(getAttributeNameHandler(KIND_NAME)) << "\") );"      "\r\n\t\t"
				   "}"                                                                                     "\r\n\t\t")
															[!If_IsID_R2 && !If_IsREF_R2]
															[attr0, attrN]
				<< ("if ( " 
                << ("!o" 
                << (~-str_g("->get") << -str_g("->isNull") << URelation1Name_R2 << "()")
                                                            [leading_g<rel_context>()]
                << " && ")
                                                            [ReferencedRelations_R2]
                << GetReferencedAttribute_R2(str_g(""), "typename " << EntityClass_R2 << "::" << UEntity_R2 << "IDEquality(-1)")
                << "(o" << GetReferencedAttribute_R2(Accessor_R2(str_g(""))) << ") ) {"
                   "\r\n\t\t\t"
                   "m_logger->errorStream() << \"" << attr_g(getAttributeNameHandler(KIND_NAME)) << " : Identifier is null.\";\r\n\t\t\t"
                   "throw InvalidQueryException(\"" << attr_g(getAttributeNameHandler(KIND_NAME)) << " : Identifier is null.\");\r\n\t\t"
				   "}"                                                                                    "\r\n\t\t"
                   "else if ( "
                << ("!o" 
                << (~-str_g("->get") << -str_g("->isNull") << URelation1Name_R2 << "()")
                                                            [leading_g<rel_context>()]
                << " && ")
                                                            [ReferencedRelations_R2]
                << "!typename " << AttributeClass_R2 << "::" << AttributeClassName_R2 << "IDEquality(*(" << Accessor_R2(str_g("o")) << "))(" << Accessor_R2(str_g("(*save)")) << ") ) {"
                   "\r\n\t\t\t"
                << AddDataParameter_R2(str_g("values"), "o" << GetReferencedAttribute_R2(Accessor_R2(str_g("")), "->get" << UAttribute_R2 << "()")) << "\r\n\t\t\t"
                   "fields.push_back( C(\"" << attr_g(getAttributeNameHandler(KIND_NAME)) << "\") );"     "\r\n\t\t"
				   "}"                                                                                    "\r\n\t\t"
				   "else if ( o->isNull" << UAttribute_R2 << "() "
				   "&& !(*save)->isNull" << UAttribute_R2 << "() ) {"                                     "\r\n\t\t\t"
				<< InsertNULLAttribute_R2                   [relationsByAttr(FILTER_TARGET)]
				<< "}"                                                                                    "\r\n\t\t")
															[If_IsREF_R2 && !If_IsID_R2]
															[attr0, attrN]
				<< ListRelationN_R2(
                   "std::vector< boost::shared_ptr< " << EncodingClass_R2(URelationN_R2) << " > > listOf" << URelationNName_R2 << "ToAdd;\r\n\t\t"
                   "std::vector< boost::shared_ptr< " << EncodingClass_R2(URelationN_R2) << " > > listOf" << URelationNName_R2 << "ToUpdate;\r\n\t\t"
                   "typename " << Relation1Class_R2 << "::"<< RelationNIterator_R2 << " " << LRelationNName_R2 << ";\r\n\t\t"
                   "for ( " << LRelationNName_R2 << "=o->get"<< URelationNName_R2 << "sBeginning(); "
                << LRelationNName_R2 << "!=o->get" << URelationNName_R2 << "sEnd(); ++" << LRelationNName_R2 << " ) {"
                << VerifyRELATION_R2("(*" << LRelationNName_R2 << ")")
                << "\r\n\t\t\t"
                << "(*" << LRelationNName_R2 << ")->set" << URelation1Name_R2 << "(o);"
				   "\r\n\t\t\t"
                << RelationNEqualFunctor_R2(LRelationNName_R2 << "IdEquality", "*(*" << LRelationNName_R2 << ")")
				<< "\r\n\t\t\t"
                   "if ( std::find_if((*save)->get" << URelationNName_R2 << "sBeginning(), (*save)->get" << URelationNName_R2
                << "sEnd(), " << LRelationNName_R2 << "IdEquality) == (*save)->get" << URelationNName_R2 << "sEnd()) {\r\n\t\t\t\t"
                   "listOf" << URelationNName_R2 << "ToAdd.push_back(*" << LRelationNName_R2 << ");"                "\r\n\t\t\t"
				   "}"                                                                                      "\r\n\t\t\t"
				   "else {"                                                                                 "\r\n\t\t\t\t"
                   "if (" << LRelationNName_R2 << "Access->isModified" << URelationN_R2 << "(*" << LRelationNName_R2 << "))\r\n\t\t\t\t\t"
                   "listOf" << URelationNName_R2 << "ToUpdate.push_back(*" << LRelationNName_R2 << ");"             "\r\n\t\t\t"
				   "}"                                                                                      "\r\n\t\t"
				   "}"                                                                                      "\r\n\t\t"
                   "std::vector< boost::shared_ptr< " << EncodingClass_R2(URelationN_R2) << " > > listOf" << URelationNName_R2 << "ToRemove;\r\n\t\t"
                << "for ( " << LRelationNName_R2 << "=(*save)->get" << URelationNName_R2 << "sBeginning(); "
                << LRelationNName_R2 << "<(*save)->get" << URelationNName_R2 << "sEnd(); ++" << LRelationNName_R2 << " ) {"
                << VerifyRELATION_R2("(*" << LRelationNName_R2 << ")")
                << "\r\n\t\t\t"
                << RelationNEqualFunctor_R2(LRelationNName_R2 << "IdEquality", "*(*" << LRelationNName_R2 << ")")
				<< "\r\n\t\t\t"
                   "if ( std::find_if(o->get" << URelationNName_R2    << "sBeginning(), o->get" << URelationNName_R2
                << "sEnd(), " << LRelationNName_R2 << "IdEquality) == o->get" << URelationNName_R2 << "sEnd()) {"   "\r\n\t\t\t\t"
                   "listOf" << URelationNName_R2 << "ToRemove.push_back(*" << LRelationNName_R2 << ");"             "\r\n\t\t\t"
				   "}"                                                                                      "\r\n\t\t"
				   "}"                                                                                      "\r\n\t\t")
                << "if (!fields.empty()) {"                                                                 "\r\n\t\t\t"
                   "statement.swap( connection->update(C(\"" << ent_g(getEntityNameHandler(KIND_NAME)) << "\"), fields, "
                << ConvertCStringLoop_R2(AttributeAccessor_R2(Accessor_R2(str_g("o")))) << ") );"           "\r\n\t\t\t"
				<< "if ( !values.fill(statement) || !statement.executeQuery() ) {"                          "\r\n\t\t\t\t"
				   "m_logger->fatalStream() << \"invalid query.\";"                                         "\r\n\t\t\t\t"
				   "throw InvalidQueryException(\"invalid query.\");"                                       "\r\n\t\t\t"
				   "}"                                                                                      "\r\n\t\t\t"
                   "m_updateSignal(OPERATION_ACCESS_UPDATE, C(\"" << ent_g(getEntityNameHandler(KIND_ALIAS)) << "\"), o);\r\n\t\t"
                   "}"                                                                                      "\r\n\t\t"
				<< ListRelationN_R2( 
                   "for ( " << LRelationNName_R2 << "=listOf" << URelationNName_R2 << "ToAdd.begin(); "
                << LRelationNName_R2 << "!=listOf" << URelationNName_R2 << "ToAdd.end() ; ++" << LRelationNName_R2 << " ) {\r\n\t\t\t"
                << LRelationNName_R2 << "Access->insert" << URelationN_R2 << "(*" << LRelationNName_R2 << ");"      "\r\n\t\t"
				   "}"                                                                                      "\r\n\t\t"
                   "for ( " << LRelationNName_R2 << "=listOf" << URelationNName_R2 << "ToUpdate.begin(); "
                << LRelationNName_R2 << "!=listOf" << URelationNName_R2 << "ToUpdate.end() ; ++" << LRelationNName_R2 << " ) {\r\n\t\t\t"
                << LRelationNName_R2 << "Access->update" << URelationN_R2 << "(*" << LRelationNName_R2 << ");"      "\r\n\t\t"
				   "}"                                                                                      "\r\n\t\t"
                   "for ( " << LRelationNName_R2 << "=listOf" << URelationNName_R2 << "ToRemove.begin(); "
                << LRelationNName_R2 << "!=listOf" << URelationNName_R2 << "ToRemove.end() ; ++" << LRelationNName_R2 << " ) {\r\n\t\t\t"
                << UpdateRelationOnDelete_R2(LRelationNName_R2) <<                                              "\r\n\t\t"
				   "}"                                                                                      "\r\n\t\t")
                << ListRelationPB_R2(
                   "if (" << LAttribute_R2 << "Access->isModified" << AttributeClassName_R2 << "(" << Accessor_R2(str_g("o")) << ")) {\r\n\t\t\t"
                << LAttribute_R2 << "Access->update" << AttributeClassName_R2 << "(" << Accessor_R2(str_g("o")) << ");\r\n\t\t"
                   "}\r\n\t\t")
                << "if (connection->isTransactionInProgress() && m_transactionOwner) {"                     "\r\n\t\t\t"
                   "connection->commit();"                                                                  "\r\n\t\t\t"
			       "m_transactionOwner = false;"                                                            "\r\n\t\t\t"
                   "m_transactionSignal(OPERATION_ACCESS_COMMIT);"                                          "\r\n\t\t"
                   "}"                                                                                      "\r\n\t\t"
                   "m_backup.erase(save);"                                                                  "\r\n\t"
                   "} catch (...) {"                                                                        "\r\n\t\t"
                   "if (m_transactionOwner) {"                                                              "\r\n\t\t\t"
                   "cancelSelection();"                                                                     "\r\n\t\t"
                   "}"                                                                                      "\r\n\t\t"
                   "throw;"                                                                                 "\r\n\t"
                   "}";

			InsertMeth_R2 =
				CreateTMethod_R2(    str_g("void"),
									AccessClass_R2,
									str_g("insert") << UEntity_R2,
                                    "boost::shared_ptr< " << EntityClass_R2 << " > o",
									str_g(""),
									InsertMethBody_R2
								);

			InsertMethBody_R2 =
				   VerifyPTR_R2(str_g("o"))
				<< str_g("\r\n\t"
				   "_DataParameters<EncodingT> values;"                                             "\r\n\t"
                   "_DataStatement<EncodingT> statement;"                                           "\r\n\t"
                   "std::vector<typename EncodingT::string_t> fields;")
				<< InitializeConnection_R2
                << InitializeAccessLoop_R2 [If_HasUniqueID_R2]
				<< ListRelationN_R2(InitializeRelationAccess_R2)
				<< "\r\n\t"
                   "try {"                                                                          "\r\n\t\t"
				   "m_transactionOwner = !connection->isTransactionInProgress();"                   "\r\n\t\t"
                   "if (m_transactionOwner) {"                                                      "\r\n\t\t\t"
                   "connection->startTransaction();"                                                "\r\n\t\t\t"
                   "m_transactionSignal(OPERATION_ACCESS_START);"                                   "\r\n\t\t"
                   "}"                                                                              "\r\n\t\t"
				<< ((AddDataParameter_R2(str_g("values"),Accessor_R2(str_g("o"))) <<                "\r\n\t\t"
                   "fields.push_back( C(\"" << attr_g(getAttributeNameHandler(KIND_NAME)) << "\") );\r\n\t\t")
															[!If_IsID_R2 && !If_IsREF_R2]
                << ("int id = connection->selectMaxID(C(\"" << attr_g(getAttributeNameHandler(KIND_NAME)) << "\"), C(\"" << ent_g(getEntityNameHandler(KIND_NAME)) << "\"))+1;""\r\n\t\t"
					"values.addInt( id );"                                                          "\r\n\t\t"
                    "fields.push_back( C(\"" << attr_g(getAttributeNameHandler(KIND_NAME)) << "\") );\r\n\t\t")
															[!If_HasREF_ID_R2 && If_IsID_R2]
				<< (AddDataParameter_R2(str_g("values"),Accessor_R2(str_g("o"))) <<                 "\r\n\t\t"
                    "fields.push_back( C(\"" << attr_g(getAttributeNameHandler(KIND_NAME)) << "\") );\r\n\t\t")
															[If_HasREF_ID_R2 && If_IsID_R2 && !If_IsREF_R2]
				<< ((
                   "if ( "
                << ("!o" 
                << (~-str_g("->get") << -str_g("->isNull") << URelation1Name_R2 << "()")
                                                            [leading_g<rel_context>()]
                << " && ")
                                                            [ReferencedRelations_R2]
                << GetReferencedAttribute_R2(str_g(""), "typename " << EntityClass_R2 << "::" << UEntity_R2 << "IDEquality(-1)")
                << "(o" << GetReferencedAttribute_R2(Accessor_R2(str_g(""))) << ") ) {"                  
                   "\r\n\t\t\t"
                   "m_logger->errorStream() << \"" << attr_g(getAttributeNameHandler(KIND_NAME)) << " : Identifier is null.\";\r\n\t\t\t"
                   "throw InvalidQueryException(\"" << attr_g(getAttributeNameHandler(KIND_NAME)) << " : Identifier is null.\");\r\n\t\t"
				   "}"                                                                              "\r\n\t\t"
                   "else if ( "
                << ("!o" 
                << (~-str_g("->get") << -str_g("->isNull") << URelation1Name_R2 << "()")
                                                            [leading_g<rel_context>()]
                << ~-str_g(" && "))
                                                            [ReferencedRelations_R2]
                << " ) {"                                                                           "\r\n\t\t\t"
				<< AddDataParameter_R2(str_g("values"), "o" << GetReferencedAttribute_R2(Accessor_R2(str_g("")), "->get" << UAttribute_R2 << "()")) << "\r\n\t\t\t"
                   "fields.push_back( C(\"" << attr_g(getAttributeNameHandler(KIND_NAME)) << "\") );\r\n\t\t"
				   "}"                                                                              "\r\n\t\t"
				   "else {"                                                                         "\r\n\t\t\t"
				<< InsertNULLAttribute_R2                   [relationsByAttr(FILTER_TARGET)]
				<< "}"                                                                              "\r\n\t\t")
                                                            [!(If_IsID_R2 && If_HasUniqueID_R2)]
                << (
                   "if ( !o->isNull" << UAttribute_R2 << "() && typename " << AttributeClass_R2 << "::" << AttributeClassName_R2 << "IDEquality(-1)(" << Accessor_R2(str_g("o")) << ")) {"
                   "\r\n\t\t\t"
                   << LAttribute_R2 << "Access->insert" << AttributeClassName_R2 << "(" << Accessor_R2(str_g("o")) << ");\r\n\t\t"
				   "}"                                                                              "\r\n\t\t"
                   "if ( !o->isNull" << UAttribute_R2 << "() ) {"                                   "\r\n\t\t\t"
				<< AddDataParameter_R2(str_g("values"), AttributeAccessor_R2(Accessor_R2(str_g("o")))) << "\r\n\t\t\t"
                   "fields.push_back( C(\"" << attr_g(getAttributeNameHandler(KIND_NAME)) << "\") );\r\n\t\t"
				   "}"                                                                              "\r\n\t\t"
				   "else {"                                                                         "\r\n\t\t\t"
				<< InsertNULLAttribute_R2                   [relationsByAttr(FILTER_TARGET)]
				<< "}"                                                                              "\r\n\t\t")
                                                            [If_IsID_R2 && If_HasUniqueID_R2])
															[If_IsREF_R2])
															[!If_IsAUTO_R2]
															[attr0, attrN]
                << "statement.swap( connection->insert(C(\"" << ent_g(getEntityNameHandler(KIND_NAME)) << "\"), fields) );\r\n\t\t"
				<< "if ( !values.fill(statement) || !statement.executeQuery() ) {"                  "\r\n\t\t\t"
				   "m_logger->fatalStream() << \"invalid query.\";"                                 "\r\n\t\t\t"
				   "throw InvalidQueryException(\"invalid query.\");"                               "\r\n\t\t"
				   "}"                                                                              "\r\n\t\t"
				<< (str_g("int id = connection->getLastInsertID();"                                 "\r\n\t\t")
															[If_IsAUTO_R2]
				<< "o->set" << UAttribute_R2 << "(id);"                                              "\r\n\t\t")
															[If_IsID_R2]
															[attr0, attrN]
															[!If_HasREF_ID_R2]
                << "m_insertSignal(OPERATION_ACCESS_INSERT, C(\"" << ent_g(getEntityNameHandler(KIND_ALIAS)) << "\"), o);\r\n\t\t"
				<< ListRelationN_R2( 
                   "typename " << Relation1Class_R2 << "::" << RelationNIterator_R2 
                << " " << LRelationNName_R2 << ";"                                                      "\r\n\t\t"
                   "for ( " << LRelationNName_R2 << "=o->get" << URelationNName_R2 << "sBeginning(); "
                << LRelationNName_R2 << "!=o->get" << URelationNName_R2 << "sEnd(); ++" << LRelationNName_R2 << " ) {\r\n\t\t\t"
                << "(*" << LRelationNName_R2 << ")->set" << URelation1Name_R2 << "(o);"                     "\r\n\t\t\t"
                << LRelationNName_R2 << "Access->insert" << URelationN_R2 << "(*" << LRelationNName_R2 << ");\r\n\t\t"
				   "}"                                                                              "\r\n\t\t")
                << "if (connection->isTransactionInProgress() && m_transactionOwner) {"             "\r\n\t\t\t"
                   "connection->commit();"                                                          "\r\n\t\t\t"
                   "m_transactionOwner = false;"                                                    "\r\n\t\t\t"
                   "m_transactionSignal(OPERATION_ACCESS_COMMIT);"                                  "\r\n\t\t"
                   "}"                                                                              "\r\n\t"
				   "} catch (...) {"                                                                "\r\n\t\t"
                   "if (connection->isTransactionInProgress() && m_transactionOwner) {"             "\r\n\t\t\t"
                   "connection->rollback();"                                                        "\r\n\t\t\t"
                   "m_transactionOwner = false;"                                                    "\r\n\t\t\t"
                   "m_transactionSignal(OPERATION_ACCESS_ROLLBACK);"                                "\r\n\t\t"
                   "}"                                                                              "\r\n\t\t"
				   "throw;"                                                                         "\r\n\t"
				   "}";

			DeleteMeth_R2 =
				CreateTMethod_R2(   str_g("void"),
									AccessClass_R2,
									str_g("delete") << UEntity_R2,
                                    "boost::shared_ptr< " << EntityClass_R2 << " > o"
                                 << str_g(", bool deleteid")[If_HasREF_ID_R2 && If_HasUniqueID_R2],
									str_g(""),
									DeleteMethBody_R2
								);

			DeleteMethBody_R2 =
				VerifyPTR_R2(str_g("o"))
				<< str_g("\r\n\t"
                   "_DataStatement<EncodingT> statement;")
                << VerifyID_R2( Accessor_R2(str_g("o")), RelationAccessor_R2(str_g("o")) )
				<< InitializeConnection_R2
                << InitializeAccessLoop_R2 [If_HasUniqueID_R2]
				<< ListRelationN_R2(InitializeRelationAccess_R2)
                << ListRelationPA_R2(InitializeRelationAccess_R2)
				<< "\r\n\t"
				<< EntityEqualFunctor_R2(UEntity_R2 << "IdEquality", str_g("*o"))
				<< "\r\n\t"
                   "typename std::vector< boost::shared_ptr< " << EntityClass_R2 << " > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), " << UEntity_R2 << "IdEquality);\r\n\t"
				   "if (save == m_backup.end()) {"                                                  "\r\n\t\t"
				   "m_logger->errorStream() << \"You must select object before deletion.\";"        "\r\n\t\t"
				   "throw UnSelectedObjectException(\"You must select object before deletion.\");"  "\r\n\t"
				   "}"                                                                              "\r\n\t"
                   "try {"                                                                          "\r\n\t\t"
				<< ListRelationN_R2(
                   "typename " << Relation1Class_R2 << "::" << URelationNName_R2 << "Iterator " << LRelationNName_R2 << ";\r\n\t\t"
                   "fillAll" << URelationNName_R2 << "s(o);"                                            "\r\n\t\t"
                   "for ( " << LRelationNName_R2 << "=o->get" << URelationNName_R2 << "sBeginning(); "
                << LRelationNName_R2 << "!=o->get" << URelationNName_R2 << "sEnd(); ++"
                << LRelationNName_R2 << " ) {"                                                          "\r\n\t\t\t"
                << UpdateRelationOnDelete_R2(LRelationNName_R2) <<                                      "\r\n\t\t"
				   "}"                                                                              "\r\n\t\t")
                << "statement.swap( connection->deleteFrom(C(\"" << ent_g(getEntityNameHandler(KIND_NAME)) << "\"), "
				<< ConvertCStringLoop_R2(AttributeAccessor_R2(Accessor_R2(str_g("o")))) << ") );"   "\r\n\t\t"
				<< "if ( !statement.executeQuery() ) {"                                             "\r\n\t\t\t"
				   "m_logger->fatalStream() << \"invalid query.\";"                                 "\r\n\t\t\t"
				   "throw InvalidQueryException(\"invalid query.\");"                               "\r\n\t\t"
				   "}"                                                                              "\r\n\t\t"
                   "m_deleteSignal(OPERATION_ACCESS_DELETE, C(\"" << ent_g(getEntityNameHandler(KIND_ALIAS)) << "\"), o);\r\n\t\t"
                << ListRelationPB_R2(
                   "if (deleteid) {\r\n\t\t\t"
                << LAttribute_R2 << "Access->delete" << AttributeClassName_R2 << "(" << Accessor_R2(str_g("o")) << ");\r\n\t\t"
                   "}\r\n\t\t")
                << "if (connection->isTransactionInProgress() && m_transactionOwner) {"             "\r\n\t\t\t"
                << ListRelationPA_R2(
                   LRelationNName_R2 << "Access->delete" << URelationN_R2 << "(" << LRelationNName_R2 << "Access->selectOne" << URelationN_R2 << "(o), false);\r\n\t\t\t")
                << "connection->commit();"                                                          "\r\n\t\t\t"
			       "m_transactionOwner = false;"                                                    "\r\n\t\t\t"
                   "m_transactionSignal(OPERATION_ACCESS_COMMIT);"                                  "\r\n\t\t"
		           "}"                                                                              "\r\n\t\t"
                   "m_backup.erase(save);"                                                          "\r\n\t"
				<< ("\to->set" << UAttribute_R2 << "(-1);"                                          "\r\n\t")
															[If_IsID_R2]
															[attr0, attrN]
															[!If_HasREF_ID_R2]
                << "} catch (...) {"                                                                "\r\n\t\t"
                   "if (m_transactionOwner) {"                                                      "\r\n\t\t\t"
                   "cancelSelection();"                                                             "\r\n\t\t"
                   "}"                                                                              "\r\n\t\t"
                   "throw;"                                                                         "\r\n\t"
                   "}";
	        
			UpdateRelationOnDelete_R2 =
                (LRelationNName_R2 << "Access->delete" << URelationN_R2    << "(*" << $(0) << ");")
															[If_IsNotNULL_R2]
                << ( LRelationNName_R2 << "Access->fill" << URelation1Name_R2 << "(*" << $(0) << ");" "\r\n\t\t\t"
                << "(*" << $(0) << ")->erase" << URelation1Name_R2 << "();"                       "\r\n\t\t\t"
                << LRelationNName_R2 << "Access->update" << URelationN_R2 << "(*" << $(0) << ");")
															[!If_IsNotNULL_R2];
			InsertNULLAttribute_R2 =
				(str_g("values.addText( C(\"NULL\") );\r\n\t\t\t"
                 "fields.push_back( C(\"") << rel_g(getRelationTargetRefHandler(KIND_NAME)) << "\") );\r\n\t\t")
															[!If_IsNotNULL_R2]
                << (str_g("m_logger->errorStream() << \"") << rel_g(getRelationTargetRefHandler(KIND_NAME)) << " : null reference is forbidden.\";\r\n\t\t\t"
                   "throw InvalidQueryException(\"" << rel_g(getRelationTargetRefHandler(KIND_NAME)) << " : null reference is forbidden.\");\r\n\t\t")
															[If_IsNotNULL_R2];

            AddInsertSignalMeth_R2 =
				CreateTMethod_R2(   "typename " << AccessClass_R2 << "::connection_t",
									AccessClass_R2,
									str_g("addInsertSignal"),
									str_g("typename signal_t::slot_function_type subscriber"),
									str_g(""),
									line_g(1) << htab_g(1) << str_g("return m_insertSignal.connect(subscriber);")
								);

            AddUpdateSignalMeth_R2 =
				CreateTMethod_R2(   "typename " << AccessClass_R2 << "::connection_t",
									AccessClass_R2,
									str_g("addUpdateSignal"),
									str_g("typename signal_t::slot_function_type subscriber"),
									str_g(""),
									line_g(1) << htab_g(1) << str_g("return m_updateSignal.connect(subscriber);")
								);

            AddDeleteSignalMeth_R2 =
				CreateTMethod_R2(   "typename " << AccessClass_R2 << "::connection_t",
									AccessClass_R2,
									str_g("addDeleteSignal"),
									str_g("typename signal_t::slot_function_type subscriber"),
									str_g(""),
									line_g(1) << htab_g(1) << str_g("return m_deleteSignal.connect(subscriber);")
								);

            AddTransactionSignalMeth_R2 =
				CreateTMethod_R2(   "typename " << AccessClass_R2 << "::connection_t",
									AccessClass_R2,
									str_g("addTransactionSignal"),
									str_g("typename signal_transaction_t::slot_function_type subscriber"),
									str_g(""),
									line_g(1) << htab_g(1) << str_g("return m_transactionSignal.connect(subscriber);")
								);

            RemoveInsertSignalMeth_R2 =
				CreateTMethod_R2(   str_g("void"),
									AccessClass_R2,
									str_g("removeInsertSignal"),
									str_g("connection_t connection"),
									str_g(""),
									line_g(1) << htab_g(1) << str_g("connection.disconnect();")
								);

            RemoveUpdateSignalMeth_R2 =
				CreateTMethod_R2(   str_g("void"),
									AccessClass_R2,
									str_g("removeUpdateSignal"),
									str_g("connection_t connection"),
									str_g(""),
									line_g(1) << htab_g(1) << str_g("connection.disconnect();")
								);

            RemoveDeleteSignalMeth_R2 =
				CreateTMethod_R2(   str_g("void"),
									AccessClass_R2,
									str_g("removeDeleteSignal"),
									str_g("connection_t connection"),
									str_g(""),
									line_g(1) << htab_g(1) << str_g("connection.disconnect();")
								);

            RemoveTransactionSignalMeth_R2 =
				CreateTMethod_R2(   str_g("void"),
									AccessClass_R2,
									str_g("removeTransactionSignal"),
									str_g("connection_t connection"),
									str_g(""),
									line_g(1) << htab_g(1) << str_g("connection.disconnect();")
								);
		}
	}
}
