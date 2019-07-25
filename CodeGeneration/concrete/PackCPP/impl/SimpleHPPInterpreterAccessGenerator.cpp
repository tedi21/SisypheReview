#include "SimpleHPPInterpreterAccessGenerator.hpp"

namespace dsg {

	namespace generator {

		SimpleHPPInterpreterAccessGenerator::SimpleHPPInterpreterAccessGenerator()
		{
			SourceHPP_R2 = 
				CreateFile_R2;

			CreateFile_R2 =
                CreateHeader_R2(file_g(getFileNameHandler(KIND_ALIAS)) << "InterpreterAccess.hpp")
                << CreateHPPDefine_R2("_" << file_g(getFileNameHandler(KIND_ALIAS)) << "_interpreter_access_hpp_")
				<< CreateInclude_R2
                << CreateMacro_R2
                << CreateNamespace_R2(str_g("interp"))
				<< CreateUsingNamespace_R2
				<< CreateInterpreterAccessClass_R2  [ent0, entN]
				<< CreateEndNamespace_R2
                << CreateEndMacro_R2
				<< CreateEndInclude_R2
				<< CreateHPPEndDefine_R2;  

			CreateInclude_R2 =
                str_g(  "#include \"config.hpp\"\r\n"
						"#include \"macros.hpp\"\r\n"
                        "#include \"String.hpp\"\r\n\r\n" )
                << (str_g("#include \"") << call_g(getWorkspaceNameHandler()) << "Export.hpp\"\r\n")
                << (str_g("#include \"") << call_g(getWorkspaceNameHandler()) << "Data.h\"\r\n");

			CreateEndInclude_R2 =
                str_g(  "#include \"") << file_g(getFileNameHandler(KIND_ALIAS)) << "InterpreterAccess_impl.hpp\"\r\n\r\n";


			CreateUsingNamespace_R2 =
				str_g(  "using namespace log4cpp;\r\n"
						"using namespace fctr;\r\n"
						"using namespace enc;\r\n"
						"using namespace data_access;\r\n"
						"using namespace boost;\r\n\r\n");

			CreateInterpreterAccessClass_R2 =
				str_g("template <class EncodingT>")
				<< line_g(1) << "class " << UEntity_R2 << "InterpreterAccess"
                << line_g(1) << ": public Base<EncodingT>"
				<< line_g(1) << "{"
				<< line_g(1) << "private:"
				<< line_g(1) << htab_g(1) << AccessClass_R2 << "* m_object;"
                << line_g(1) << htab_g(1) << "std::string m_errorText;"
                << line_g(1) << htab_g(1) << "bool m_error;"
				<< line_g(2) << "public:"
				<< line_g(1) << htab_g(1) << UEntity_R2 << "InterpreterAccess();"
				<< line_g(2) << htab_g(1) << "virtual typename EncodingT::string_t toString() const;"
                << line_g(2) << htab_g(1) << "virtual boost::shared_ptr< Base<EncodingT> > clone() const;"
				<< line_g(2) << htab_g(1) << "virtual typename EncodingT::string_t getClassName() const;"
                << line_g(2) << htab_g(1) << "virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);"
				<< CreateGetAll_R2
				<< CreateGetMany_R2
				<< CreateGetOne_R2
				<< CreateSelectOne_R2
				<< CreateSelectMany_R2
				<< CreateCancelSelected_R2
				<< CreateIsSelected_R2
				<< CreateFillREF_R2
				<< CreateFillRelation_R2
				<< CreateIsAltered_R2
				<< CreateUpdate_R2
				<< CreateInsert_R2
				<< CreateDelete_R2
                << SetError_R2
                << ClearError_R2
                << GetError_R2
				<< CreateFactoryRegister_R2
				<< CreateFactoryUnRegister_R2
				<< ConvertPtrVectorToArray_R2
				<< line_g(1) << "};"
				<< line_g(2);

			CreateGetAll_R2 =
                line_g(2) << htab_g(1) << "boost::shared_ptr< Base<EncodingT> > getAll" << UEntity_R2 << "s();";

			CreateGetMany_R2 =
                line_g(2) << htab_g(1) << "FACTORY_PROTOTYPE1(getMany" << UEntity_R2 << "s, In< boost::shared_ptr< Base<EncodingT> > >)"
                << line_g(1) << htab_g(1) << "boost::shared_ptr< Base<EncodingT> > getMany" << UEntity_R2 << "s(const boost::shared_ptr< Base<EncodingT> >& filter);";

			CreateGetOne_R2 =
                line_g(2) << htab_g(1) << "FACTORY_PROTOTYPE" << EntityIDParamSize_R2 << "(getOne" << UEntity_R2 << ListEntityIDParam_R2(CommaParam_R2 << "In< boost::shared_ptr< Base<EncodingT> > >") << ")"
                << line_g(1) << htab_g(1) << "boost::shared_ptr< Base<EncodingT> > getOne" << UEntity_R2 << "(" << CreateIDParam_R2 << ");";

			CreateSelectOne_R2 =
                line_g(2) << htab_g(1) << "FACTORY_PROTOTYPE" << SelectOneParamSize_R2 << "(selectOne" << UEntity_R2 << CommaParam_R2 << ListEntityIDParam_R2("In< boost::shared_ptr< Base<EncodingT> > >" << CommaParam_R2) << "In< boost::shared_ptr< Base<EncodingT> > >)"
                << line_g(1) << htab_g(1) << "boost::shared_ptr< Base<EncodingT> > selectOne" << UEntity_R2 << "(" << CreateIDParam_R2 << CommaParam_R2 << "const boost::shared_ptr< Base<EncodingT> >& nowait);";

			CreateSelectMany_R2 =
                (line_g(2) << htab_g(1) << "FACTORY_PROTOTYPE2(selectMany" << UEntity_R2 << "s, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)"
                << line_g(1) << htab_g(1) << "boost::shared_ptr< Base<EncodingT> > selectMany" << UEntity_R2 << "s(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);")
				[has_g(0, set_g((attr0,attrN), If_IsREF_R2), gt_g())];

			CreateCancelSelected_R2 =
				line_g(2) << htab_g(1) << "void cancelSelection();";

			CreateIsSelected_R2 =
                line_g(2) << htab_g(1) << "FACTORY_PROTOTYPE1(isSelected" << UEntity_R2 << ", In< boost::shared_ptr< Base<EncodingT> > >)"
                << line_g(1) << htab_g(1) << "boost::shared_ptr< Base<EncodingT> > isSelected" << UEntity_R2 << "(const boost::shared_ptr< Base<EncodingT> >& " << LEntity_R2 << ");";

			CreateFillREF_R2 =
                (line_g(2) << htab_g(1) << "FACTORY_PROTOTYPE1(fill" << UAttribute_R2 << ", InOut< boost::shared_ptr< Base<EncodingT> > >)"
                << line_g(1) << htab_g(1) << "void fill" << UAttribute_R2 << "(boost::shared_ptr< Base<EncodingT> >& " << LEntity_R2 << ");")
				[If_IsREF_R2 && !If_IsID_R2]       
				[attr0, attrN];

			CreateFillRelation_R2 =
				ListRelationN_R2(
                line_g(2) << htab_g(1) << "FACTORY_PROTOTYPE2(fillAll" << URelationNName_R2 << "s, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)"
                << line_g(1) << htab_g(1) << "void fillAll" << URelationNName_R2 << "s(boost::shared_ptr< Base<EncodingT> >& " << LRelation1_R2 << ", const boost::shared_ptr< Base<EncodingT> >& nowait);"
                << line_g(2) << htab_g(1) << "FACTORY_PROTOTYPE" << FillRelationParamSize_R2 << "(fillOne" << URelationNName_R2 << CommaParam_R2 << "InOut< boost::shared_ptr< Base<EncodingT> > >" << CommaParam_R2 << "In< boost::shared_ptr< Base<EncodingT> > >" << ListRelationIDParam_R2(CommaParam_R2 << "In< boost::shared_ptr< Base<EncodingT> > >") << ")"
                << line_g(1) << htab_g(1) << "void fillOne" << URelationNName_R2 << "(boost::shared_ptr< Base<EncodingT> >& ref" << URelation1_R2 << ListRelationIDParam_R2(CommaParam_R2 << "const boost::shared_ptr< Base<EncodingT> >& " << LAttribute_R2)
                << CommaParam_R2 << "const boost::shared_ptr< Base<EncodingT> >& nowait);"
                << line_g(2) << htab_g(1) << "FACTORY_PROTOTYPE3(fillMany" << URelationNName_R2 << "s, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)"
                << line_g(1) << htab_g(1) << "void fillMany" << URelationNName_R2 << "s(boost::shared_ptr< Base<EncodingT> >& " << LRelation1_R2 << ", const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);");

			CreateIsAltered_R2 =
                line_g(2) << htab_g(1) << "FACTORY_PROTOTYPE1(isModified" << UEntity_R2 << ", In< boost::shared_ptr< Base<EncodingT> > >)"
                << line_g(1) << htab_g(1) << "boost::shared_ptr< Base<EncodingT> > isModified" << UEntity_R2 << "(const boost::shared_ptr< Base<EncodingT> >& " << LEntity_R2 << ");";

			CreateUpdate_R2 =
                line_g(2) << htab_g(1) << "FACTORY_PROTOTYPE1(update" << UEntity_R2 << ", InOut< boost::shared_ptr< Base<EncodingT> > >)"
                << line_g(1) << htab_g(1) << "void update" << UEntity_R2 << "(boost::shared_ptr< Base<EncodingT> >& " << LEntity_R2 << ");";

			CreateInsert_R2 =
                line_g(2) << htab_g(1) << "FACTORY_PROTOTYPE1(insert" << UEntity_R2 << ", InOut< boost::shared_ptr< Base<EncodingT> > >)"
                << line_g(1) << htab_g(1) << "void insert" << UEntity_R2 << "(boost::shared_ptr< Base<EncodingT> >& " << LEntity_R2 << ");";

			CreateDelete_R2 =
                line_g(2) << htab_g(1) << "FACTORY_PROTOTYPE1(delete" << UEntity_R2 << ", InOut< boost::shared_ptr< Base<EncodingT> > >)"
                << line_g(1) << htab_g(1) << "void delete" << UEntity_R2 << "(boost::shared_ptr< Base<EncodingT> >& " << LEntity_R2 << ");";

            SetError_R2 =
                   line_g(2) << htab_g(1) << "void setError(const std::exception& e);";

            ClearError_R2 =
                   line_g(2) << htab_g(1) << "void clearError();";

            GetError_R2 =
                   line_g(2) << htab_g(1) << "FACTORY_PROTOTYPE1(getError, InOut< boost::shared_ptr< Base<EncodingT> > >)"
                   << line_g(1) << htab_g(1) << "boost::shared_ptr< Base<EncodingT> > getError(boost::shared_ptr< Base<EncodingT> >& text) const;";

			CreateFactoryRegister_R2 =
				line_g(2) << htab_g(1) << "FACTORY_BEGIN_REGISTER"
				<< line_g(1) << htab_g(2) << "CLASS_KEY_REGISTER ( " << UEntity_R2 << "InterpreterAccess, C(\"" << UEntity_R2 << "Access\") );" 
                << line_g(1) << htab_g(2) << "METHOD_KEY_REGISTER ( " << UEntity_R2 << "InterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getAll" << UEntity_R2 << "s, no_const_t, C(\"" << UEntity_R2 << "Access::GetAll" << UEntity_R2 << "s\") );"
                << line_g(1) << htab_g(2) << "METHOD_KEY_REGISTER1( " << UEntity_R2 << "InterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getMany" << UEntity_R2 << "s, no_const_t, C(\"" << UEntity_R2 << "Access::GetMany" << UEntity_R2 << "s\") );"
                << line_g(1) << htab_g(2) << "METHOD_KEY_REGISTER" << EntityIDParamSize_R2 << "( " << UEntity_R2 << "InterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getOne" << UEntity_R2 << ", no_const_t, C(\"" << UEntity_R2 << "Access::GetOne" << UEntity_R2 << "\") );"
                << line_g(1) << htab_g(2) << "METHOD_KEY_REGISTER" << SelectOneParamSize_R2 << "( " << UEntity_R2 << "InterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectOne" << UEntity_R2 << ", no_const_t, C(\"" << UEntity_R2 << "Access::SelectOne" << UEntity_R2 << "\") );"
                << (line_g(1) << htab_g(2) << "METHOD_KEY_REGISTER2( " << UEntity_R2 << "InterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectMany" << UEntity_R2 << "s, no_const_t, C(\"" << UEntity_R2 << "Access::SelectMany" << UEntity_R2 << "s\") );")
				[has_g(0, set_g((attr0,attrN), If_IsREF_R2), gt_g())]
				<< line_g(1) << htab_g(2) << "METHOD_KEY_REGISTER ( " << UEntity_R2 << "InterpreterAccess, void, cancelSelection, no_const_t, C(\"" << UEntity_R2 << "Access::CancelSelection\") );" 
                << line_g(1) << htab_g(2) << "METHOD_KEY_REGISTER1( " << UEntity_R2 << "InterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isSelected" << UEntity_R2 << ", no_const_t, C(\"" << UEntity_R2 << "Access::IsSelected" << UEntity_R2 << "\") );"
				<< (line_g(1) << htab_g(2) << "METHOD_KEY_REGISTER1( " << UEntity_R2 << "InterpreterAccess, void, fill" << UAttribute_R2 << ", no_const_t, C(\"" << UEntity_R2 << "Access::Fill" << UAttribute_R2 << "\") );")
				[If_IsREF_R2 && !If_IsID_R2]       
				[attr0, attrN]
				<< ListRelationN_R2(
                line_g(1) << htab_g(2) << "METHOD_KEY_REGISTER2( " << URelation1_R2 << "InterpreterAccess, void, fillAll" << URelationNName_R2 << "s, no_const_t, C(\"" << URelation1_R2 << "Access::FillAll" << URelationNName_R2 << "s\") );"
                << line_g(1) << htab_g(2) << "METHOD_KEY_REGISTER" << FillRelationParamSize_R2 << "( " << URelation1_R2 << "InterpreterAccess, void, fillOne" << URelationNName_R2 << ", no_const_t, C(\"" << URelation1_R2 << "Access::FillOne" << URelationNName_R2 << "\") );"
                << line_g(1) << htab_g(2) << "METHOD_KEY_REGISTER3( " << URelation1_R2 << "InterpreterAccess, void, fillMany" << URelationNName_R2 << "s, no_const_t, C(\"" << URelation1_R2 << "Access::FillMany" << URelationNName_R2 << "s\") );"
				)
                << line_g(1) << htab_g(2) << "METHOD_KEY_REGISTER1( " << UEntity_R2 << "InterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isModified" << UEntity_R2 << ", no_const_t, C(\"" << UEntity_R2 << "Access::IsModified" << UEntity_R2 << "\") );"
				<< line_g(1) << htab_g(2) << "METHOD_KEY_REGISTER1( " << UEntity_R2 << "InterpreterAccess, void, update" << UEntity_R2 << ", no_const_t, C(\"" << UEntity_R2 << "Access::Update" << UEntity_R2 << "\") );" 
				<< line_g(1) << htab_g(2) << "METHOD_KEY_REGISTER1( " << UEntity_R2 << "InterpreterAccess, void, insert" << UEntity_R2 << ", no_const_t, C(\"" << UEntity_R2 << "Access::Insert" << UEntity_R2 << "\") );" 
				<< line_g(1) << htab_g(2) << "METHOD_KEY_REGISTER1( " << UEntity_R2 << "InterpreterAccess, void, delete" << UEntity_R2 << ", no_const_t, C(\"" << UEntity_R2 << "Access::Delete" << UEntity_R2 << "\") );" 
                << line_g(1) << htab_g(2) << "METHOD_KEY_REGISTER1( " << UEntity_R2 << "InterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getError, const_t, C(\"" << UEntity_R2 << "Access::GetError\") );"
				<< line_g(1) << htab_g(1) << "FACTORY_END_REGISTER";

			CreateFactoryUnRegister_R2 =
				line_g(2) << htab_g(1) << "FACTORY_BEGIN_UNREGISTER"
				<< line_g(1) << htab_g(2) << "CLASS_KEY_UNREGISTER ( C(\"" << UEntity_R2 << "Access\") );"
				<< line_g(1) << htab_g(2) << "METHOD_KEY_UNREGISTER ( C(\"" << UEntity_R2 << "Access::GetAll" << UEntity_R2 << "s\") );"
				<< line_g(1) << htab_g(2) << "METHOD_KEY_UNREGISTER1( C(\"" << UEntity_R2 << "Access::GetMany" << UEntity_R2 << "s\") );"
				<< line_g(1) << htab_g(2) << "METHOD_KEY_UNREGISTER" << EntityIDParamSize_R2 << "( C(\"" << UEntity_R2 << "Access::GetOne" << UEntity_R2 << "\") );"            
				<< line_g(1) << htab_g(2) << "METHOD_KEY_UNREGISTER" << SelectOneParamSize_R2 << "( C(\"" << UEntity_R2 << "Access::SelectOne" << UEntity_R2 << "\") );" 
				<< (line_g(1) << htab_g(2) << "METHOD_KEY_UNREGISTER2( C(\"" << UEntity_R2 << "Access::SelectMany" << UEntity_R2 << "s\") );")
				[has_g(0, set_g((attr0,attrN), If_IsREF_R2), gt_g())]
				<< line_g(1) << htab_g(2) << "METHOD_KEY_UNREGISTER ( C(\"" << UEntity_R2 << "Access::CancelSelection\") );" 
				<< line_g(1) << htab_g(2) << "METHOD_KEY_UNREGISTER1( C(\"" << UEntity_R2 << "Access::IsSelected" << UEntity_R2 << "\") );"
				<< (line_g(1) << htab_g(2) << "METHOD_KEY_UNREGISTER1( C(\"" << UEntity_R2 << "Access::Fill" << UAttribute_R2 << "\") );")
				[If_IsREF_R2 && !If_IsID_R2]       
				[attr0, attrN]
				<< ListRelationN_R2(
                line_g(1) << htab_g(2) << "METHOD_KEY_UNREGISTER2( C(\"" << URelation1_R2 << "Access::FillAll" << URelationNName_R2 << "s\") );"
                << line_g(1) << htab_g(2) << "METHOD_KEY_UNREGISTER" << FillRelationParamSize_R2 << "( C(\"" << URelation1_R2 << "Access::FillOne" << URelationNName_R2 << "\") );"
                << line_g(1) << htab_g(2) << "METHOD_KEY_UNREGISTER3( C(\"" << URelation1_R2 << "Access::FillMany" << URelationNName_R2 << "s\") );"
				)
				<< line_g(1) << htab_g(2) << "METHOD_KEY_UNREGISTER1( C(\"" << UEntity_R2 << "Access::IsModified" << UEntity_R2 << "\") );"
				<< line_g(1) << htab_g(2) << "METHOD_KEY_UNREGISTER1( C(\"" << UEntity_R2 << "Access::Update" << UEntity_R2 << "\") );"
				<< line_g(1) << htab_g(2) << "METHOD_KEY_UNREGISTER1( C(\"" << UEntity_R2 << "Access::Insert" << UEntity_R2 << "\") );"
				<< line_g(1) << htab_g(2) << "METHOD_KEY_UNREGISTER1( C(\"" << UEntity_R2 << "Access::Delete" << UEntity_R2 << "\") );"
                << line_g(1) << htab_g(2) << "METHOD_KEY_UNREGISTER1( C(\"" << UEntity_R2 << "Access::GetError\") );"
				<< line_g(1) << htab_g(1) << "FACTORY_END_UNREGISTER";

			ConvertPtrVectorToArray_R2 =
                line_g(2) << htab_g(1) << "boost::shared_ptr< Base<EncodingT> > convert_array(const std::vector< boost::shared_ptr< _" << UEntity_R2 << "<EncodingT> > >& value) const;";

		}
    }
}
