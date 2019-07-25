#include "SimpleHPPAccessGenerator.hpp"

namespace dsg {

	namespace generator {

		SimpleHPPAccessGenerator::SimpleHPPAccessGenerator()
		{
			SourceHPP_R2 = 
				CreateFile_R2;

			CreateFile_R2 =
                CreateHeader_R2(file_g(getFileNameHandler(KIND_ALIAS)) << "Access.hpp")
                << CreateHPPDefine_R2("_" << file_g(getFileNameHandler(KIND_ALIAS)) << "_access_hpp_")
				<< CreateInclude_R2
				<< CreateMacro_R2
				<< CreateNamespace_R2(str_g("data_access"))
				<< CreateUsingNamespace_R2
				<< CreateAccessClass_R2        [ent0, entN]
				<< CreateEndNamespace_R2
				<< CreateEndMacro_R2
				<< CreateEndInclude_R2
				<< CreateHPPEndDefine_R2;                

			CreateInclude_R2 =
				str_g("#include <boost/scoped_ptr.hpp>\r\n"
					  "#include <memory>\r\n"
                      "#include <boost/signals2.hpp>\r\n"
                      "#include <boost/any.hpp>\r\n")
                 << (str_g("#include \"") << call_g(getWorkspaceNameHandler()) << "Export.hpp\"\r\n")
                 << (str_g("#include \"") << file_g(getFileNameHandler(KIND_ALIAS)) << ".hpp\"\r\n\r\n");

			CreateUsingNamespace_R2 = 
				str_g("using namespace entity; \r\n\r\n");

			CreateAccessClass_R2 =
				CommentAccessClass_R2
				<< CreateExportTClass_R2(    UEntity_R2 << "Access",                 
											CreatePrivateMembers_R2, 
											str_g(""),
											CreatePublicMembers_R2,
											ExportAPI_R2);

			CreatePrivateMembers_R2 =
                   "\tstd::list< boost::shared_ptr< " << EntityClass_R2 << " > > m_backup;"          "\r\n"
				   "\t// Is a transaction in progress before queries ?"                              "\r\n"
				   "\tbool m_transactionOwner;"                                                      "\r\n"
				   "\tstatic " << AccessClass_R2 << "* m_instance; "                                 "\r\n\r\n"
                   "public:"                                                                         "\r\n"
                   "\ttypedef boost::signals2::signal<void (operation_access_t, typename EncodingT::string_t const&, boost::any const&)>  signal_t;\r\n"
                   "\ttypedef boost::signals2::signal<void (operation_access_t)>  signal_transaction_t;\r\n"
                   "\ttypedef boost::signals2::connection  connection_t;"                            "\r\n\r\n"
                   "private:"                                                                        "\r\n"
                   "\tsignal_t m_insertSignal;"                                                      "\r\n"
                   "\tsignal_t m_updateSignal;"                                                      "\r\n"
                   "\tsignal_t m_deleteSignal;"                                                      "\r\n"
                   "\tsignal_transaction_t m_transactionSignal;"                                     "\r\n\r\n"
				   "private:"                                                                        "\r\n"
				<< CommentAccessConstructor_R2
				<< "\t_" << UEntity_R2 << "Access();"                                                "\r\n"
				<< CommentAccessDestructor_R2
				<< "\t~_" << UEntity_R2 << "Access();"                                               "\r\n";

			CreatePublicMembers_R2 =
				   CommentAccessGetInstance_R2
				<< "\t static " << AccessClass_R2 << "* getInstance();\r\n"
				<< CommentAccessGetMany_R2
                << "\t std::vector< boost::shared_ptr< " << EntityClass_R2 << " > > getMany" << UEntity_R2 << "s(typename EncodingT::string_t const&  filter) const;\r\n"
				<< CommentAccessGetAll_R2
				<< "\t std::vector< boost::shared_ptr< " << EntityClass_R2 << " > > getAll" << UEntity_R2 << "s() const;\r\n"
				<< CommentAccessGetOne_R2   
				<< "\t boost::shared_ptr< " << EntityClass_R2 << " > getOne" << UEntity_R2 << "(" << AttributeIDParam_R2 << ") const;\r\n"
				<< CommentAccessSelectMany_R2
				<< "\t std::vector< boost::shared_ptr< " << EntityClass_R2 << " > > selectMany" << UEntity_R2 << "s(typename EncodingT::string_t const&  filter, bool nowait = false, bool addition = false);\r\n"
				<< CommentAccessSelectOne_R2
				<< "\t boost::shared_ptr< " << EntityClass_R2 << " > selectOne" << UEntity_R2 << "(" << AttributeIDParam_R2 << ", bool nowait = false, bool addition = false);\r\n"
				<< CommentAccessIsSelected_R2
                << "\t bool isSelected" << UEntity_R2 << "(boost::shared_ptr< " << EntityClass_R2 << " > o) const;\r\n"
				<< CommentAccessCancel_R2
				<< "\t void cancelSelection();\r\n"
				<< (( CommentAccessFill1_R2
                << "\t void fill" << UAttribute_R2 << "(boost::shared_ptr< " << EntityClass_R2 << " > o);\r\n")
																							[If_IsREF_R2 && !If_IsID_R2])        
																							[attr0, attrN]
				<<  ListRelationN_R2( CommentAccessFill2_R2
                <<  "\t void fillAll" << URelationNName_R2 << "s(boost::shared_ptr< " << Relation1Class_R2 << " > o, bool nowait = false);\r\n"
				<<  CommentAccessFill3_R2
                <<  "\t void fillOne" << URelationNName_R2 << "(boost::shared_ptr< " <<  Relation1Class_R2 << " > o"
				<<    (", " << AttributeConstReference_R2 << SpaceParam_R2 << LAttribute_R2)    
																							[If_IsID_R2]
																							[attr0, attrN]
																							[entitiesByRel(FILTER_TARGET|FILTER_ERASE_REF)]
				<<    ", bool nowait = false);\r\n"
				<<  CommentAccessFill4_R2
                <<  "\t void fillMany" << URelationNName_R2 << "s(boost::shared_ptr< " << Relation1Class_R2 << " > o, typename EncodingT::string_t const&  filter, bool nowait = false);\r\n")
				<<  CommentAccessAltered_R2
				<<  "\t bool isModified" << UEntity_R2 << "(boost::shared_ptr< " << EntityClass_R2 << " > o) const;\r\n"
				<<  CommentAccessUpdate_R2
				<<  "\t void update" << UEntity_R2 << "(boost::shared_ptr< " << EntityClass_R2 << " > o);\r\n"
				<<  CommentAccessInsert_R2
				<<  "\t void insert" << UEntity_R2 << "(boost::shared_ptr< " << EntityClass_R2 << " > o);\r\n"
				<<  CommentAccessDelete_R2
                <<  "\t void delete" << UEntity_R2 << "(boost::shared_ptr< " << EntityClass_R2 << " > o" << str_g(", bool deleteid = true")[If_HasREF_ID_R2 && If_HasUniqueID_R2] << ");\r\n"
                <<  CommentAccessAddInsertSignal_R2
                << "\t connection_t addInsertSignal(typename signal_t::slot_function_type subscriber);\r\n"
                <<  CommentAccessAddUpdateSignal_R2
                << "\t connection_t addUpdateSignal(typename signal_t::slot_function_type subscriber);\r\n"
                <<  CommentAccessAddDeleteSignal_R2
                << "\t connection_t addDeleteSignal(typename signal_t::slot_function_type subscriber);\r\n"
                <<  CommentAccessAddTransactionSignal_R2
                << "\t connection_t addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber);\r\n"
                <<  CommentAccessRemoveInsertSignal_R2
                << "\t void removeInsertSignal(connection_t connection);\r\n"
                <<  CommentAccessRemoveUpdateSignal_R2
                << "\t void removeUpdateSignal(connection_t connection);\r\n"
                <<  CommentAccessRemoveDeleteSignal_R2
                << "\t void removeDeleteSignal(connection_t connection);\r\n"
                <<  CommentAccessRemoveTransactionSignal_R2
                << "\t void removeTransactionSignal(connection_t connection);\r\n";

			CreateEndInclude_R2 =
				str_g("#if !defined(HAS_") << upper_g(call_g(getWorkspaceNameHandler())) << "_DLL) || defined(BUILD_" 
				<< upper_g(call_g(getWorkspaceNameHandler())) << "_DLL)\r\n" 
                   "#include \"" << file_g(getFileNameHandler(KIND_ALIAS)) << "Access_impl.hpp\"\r\n"
				   "#endif // !defined(HAS_" << upper_g(call_g(getWorkspaceNameHandler())) << "_DLL) || defined(BUILD_" 
				<< upper_g(call_g(getWorkspaceNameHandler())) << "_DLL)\r\n\r\n";
		}
    }
}
