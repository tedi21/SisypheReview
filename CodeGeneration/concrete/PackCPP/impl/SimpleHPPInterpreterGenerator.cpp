#include "SimpleHPPInterpreterGenerator.hpp"

namespace dsg {

	namespace generator {

		SimpleHPPInterpreterGenerator::SimpleHPPInterpreterGenerator()
		{
			SourceHPP_R2 = 
				CreateFile_R2;

			CreateFile_R2 =
                CreateHeader_R2(file_g(getFileNameHandler(KIND_ALIAS)) << "Interpreter.hpp")
                << CreateHPPDefine_R2("_" << file_g(getFileNameHandler(KIND_ALIAS)) << "_interpreter_hpp_")
				<< CreateInclude_R2
                << CreateMacro_R2
				<< CreateNamespace_R2(str_g("interp"))
                << CreateUsingNamespace_R2
                << (CreateForwardDeclaration_R2
                <<  CreateInterpreterEntity_R2
				<<  CreateCheckFunction_R2
				<<  CreateResetFunction_R2) [ent0, entN]
				<< CreateEndNamespace_R2
                << CreateEndMacro_R2
				<< CreateEndInclude_R2
				<< CreateHPPEndDefine_R2;    

			CreateInclude_R2 =
                str_g("#include \"config.hpp\"\r\n"
                      "#include \"macros.hpp\"\r\n"
                      "#include \"Base.hpp\"\r\n"
                      "#include \"Array.hpp\"\r\n\r\n")
                << (str_g("#include \"") << call_g(getWorkspaceNameHandler()) << "Export.hpp\"\r\n")
                << (str_g("#include \"") << call_g(getWorkspaceNameHandler()) << "Data.h\"\r\n");

			CreateEndInclude_R2 =
                str_g("#include \"") << file_g(getFileNameHandler(KIND_ALIAS)) << "Interpreter_impl.hpp\"\r\n\r\n";

			CreateUsingNamespace_R2 =
				str_g(  "using namespace log4cpp;\r\n"
						"using namespace fctr;\r\n"
						"using namespace enc;\r\n"
						"using namespace entity;\r\n"
                        "using namespace boost;\r\n\r\n");

           CreateForwardDeclaration_R2 =
               ListRelationN_R2(
                   str_g("template <class EncodingT>")
                   << line_g(1) << "class " << URelationN_R2 << "Interpreter;"
                   << line_g(2))
               << ListRelation1_R2(
                   str_g("template <class EncodingT>")
                   << line_g(1) << "class " << URelation1_R2 << "Interpreter;"
                   << line_g(2));

			CreateInterpreterEntity_R2 =
				str_g("template <class EncodingT>")
				<< line_g(1) << "class " << UEntity_R2 << "Interpreter"
                << line_g(1) << ": public Base<EncodingT>"
				<< line_g(1) << "{"
				<< line_g(1) << "private:"
				<< line_g(1) << htab_g(1) << "boost::shared_ptr< " << EntityClass_R2 << " > m_value;"
				<< line_g(2) << "public:"
				<< line_g(1) << htab_g(1) << UEntity_R2 << "Interpreter();"
				<< line_g(2) << htab_g(1) << UEntity_R2 << "Interpreter(boost::shared_ptr< " << EntityClass_R2 << " > const& value);"
				<< line_g(2) << htab_g(1) << CreateConstructorFactoryPrototype_R2
                << line_g(1) << htab_g(1) << UEntity_R2 << "Interpreter(" << CreateConstructorParam_R2 << ");"
                << line_g(2) << htab_g(1) << "boost::shared_ptr< " << EntityClass_R2 << " > value() const;"
                << line_g(2) << htab_g(1) << "void value(boost::shared_ptr< " << EntityClass_R2 << " > const& value);"
				<< line_g(2) << htab_g(1) << "virtual typename EncodingT::string_t toString() const;"
				<< line_g(2) << htab_g(1) << "virtual boost::shared_ptr< Base<EncodingT> > clone() const;"
				<< line_g(2) << htab_g(1) << "virtual typename EncodingT::string_t getClassName() const;"
                << line_g(2) << htab_g(1) << "virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);" 
				<< CreateAttributeGetter_R2
                << CreateAttributeRefGetter_R2
				<< CreateAttributeSetter_R2
				<< CreateAttributeIsNull_R2
				<< CreateAttributeErase_R2
				<< CreateAttributeListErase_R2
				<< CreateAttributeListInsert_R2
				<< CreateAttributeListAt_R2
				<< CreateAttributeListClear_R2
				<< CreateAttributeListEmpty_R2
				<< CreateAttributeListSize_R2
				<< line_g(2) << htab_g(1) << "FACTORY_BEGIN_REGISTER"
				<< line_g(1) << htab_g(2) << "CLASS_KEY_REGISTER ( " << UEntity_R2 << "Interpreter, C(\"" << UEntity_R2 << "\") );"
				<< line_g(1) << htab_g(2) << "CLASS_KEY_REGISTER" << EntityParamSize_R2 << "( " << UEntity_R2 << "Interpreter, C(\"" << UEntity_R2 << "\") );"
				<< CreateAttributeRegister_R2
				<< line_g(1) << htab_g(1) << "FACTORY_END_REGISTER"
				<< line_g(2) << htab_g(1) << "FACTORY_BEGIN_UNREGISTER"
				<< line_g(1) << htab_g(2) << "CLASS_KEY_UNREGISTER ( C(\"" << UEntity_R2 << "\") );"
				<< line_g(1) << htab_g(2) << "CLASS_KEY_UNREGISTER" << EntityParamSize_R2 << "( C(\"" << UEntity_R2 << "\") );"
				<< CreateAttributeUnRegister_R2
				<< line_g(1) << htab_g(1) << "FACTORY_END_UNREGISTER"
				<< line_g(1) << "};"
				<< line_g(2);

			CreateCheckFunction_R2 = 
				str_g("template <class EncodingT>")
				<< line_g(1) << "bool check_" << LEntity_R2 << "(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< " << EntityClass_R2 << " >& o);"
				<< line_g(2);

			CreateResetFunction_R2 = 
				str_g("template <class EncodingT>")
				<< line_g(1) << "bool reset_" << LEntity_R2 << "(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< " << EntityClass_R2 << " > const& o);"
				<< line_g(2);

			CreateAttributeGetter_R2 =
				(line_g(2) << htab_g(1) << "boost::shared_ptr< Base<EncodingT> > get" << UAttribute_R2 << "() const;")
				[!If_IsREF_R2][attr0, attrN];

			CreateAttributeRefGetter_R2 =
				(line_g(2) << htab_g(1) << "boost::shared_ptr< Base<EncodingT> > get" << UAttribute_R2 << "();")
				[If_IsREF_R2][attr0, attrN];

			CreateAttributeSetter_R2 =
				(line_g(2) << htab_g(1) << "FACTORY_PROTOTYPE1(set" << UAttribute_R2 << ", In< boost::shared_ptr< Base<EncodingT> > >)"
				<< line_g(1) << htab_g(1) << "void set" << UAttribute_R2 << "(boost::shared_ptr< Base<EncodingT> > const& " << LAttribute_R2 << ");")
				[If_IsWriteAttribute_R2]
				[attr0, attrN];

			CreateAttributeIsNull_R2 =
				(line_g(2) << htab_g(1) << "boost::shared_ptr< Base<EncodingT> > has" << UAttribute_R2 << "() const;")
				[If_IsREF_R2][attr0, attrN];

			CreateAttributeErase_R2 =
				(line_g(2) << htab_g(1) << "void remove" << UAttribute_R2 << "();")
				[If_IsREF_R2][attr0, attrN];

			CreateAttributeListErase_R2 =
                ListRelationN_R2(line_g(2) << htab_g(1) << "FACTORY_PROTOTYPE1(remove" << URelationNName_R2 << ", In< boost::shared_ptr< Base<EncodingT> > >)"
                << line_g(1) << htab_g(1) << "void remove" << URelationNName_R2 << "(boost::shared_ptr< Base<EncodingT> > const& n);");

			CreateAttributeListInsert_R2 =
                ListRelationN_R2(line_g(2) << htab_g(1) << "FACTORY_PROTOTYPE2(insert" << URelationNName_R2 << ", In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)"
                << line_g(1) << htab_g(1) << "void insert" << URelationNName_R2 << "(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& " << LRelationNName_R2 << ");");

			CreateAttributeListAt_R2 =
                ListRelationN_R2(line_g(2) << htab_g(1) << "FACTORY_PROTOTYPE1(get" << URelationNName_R2 << ", In< boost::shared_ptr< Base<EncodingT> > >)"
                << line_g(1) << htab_g(1) << "boost::shared_ptr< Base<EncodingT> > get" << URelationNName_R2 << "(boost::shared_ptr< Base<EncodingT> > const& n);");

			CreateAttributeListClear_R2 =
                ListRelationN_R2(line_g(2) << htab_g(1) << "void clear" << URelationNName_R2 << "s();");

			CreateAttributeListEmpty_R2 =
                ListRelationN_R2(line_g(2) << htab_g(1) << "boost::shared_ptr< Base<EncodingT> > has" << URelationNName_R2 << "s() const;");

			CreateAttributeListSize_R2 =
                ListRelationN_R2(line_g(2) << htab_g(1) << "boost::shared_ptr< Base<EncodingT> > " << LRelationNName_R2 << "sCount() const;");

			CreateAttributeRegister_R2 =
				((line_g(1) << htab_g(2) << "METHOD_KEY_REGISTER ( " << UEntity_R2 << "Interpreter, boost::shared_ptr< Base<EncodingT> >, get" << UAttribute_R2 << ", const_t, C(\"" << UEntity_R2 << "::" << UAttribute_R2 << "\") );")
                [!If_IsREF_R2]
				<< (line_g(1) << htab_g(2) << "METHOD_KEY_REGISTER1( " << UEntity_R2 << "Interpreter, void, set" << UAttribute_R2 << ", no_const_t, C(\"" << UEntity_R2 << "::" << UAttribute_R2 << "\") );")
				[If_IsWriteAttribute_R2]
				<< (line_g(1) << htab_g(2) << "METHOD_KEY_REGISTER ( " << UEntity_R2 << "Interpreter, boost::shared_ptr< Base<EncodingT> >, get" << UAttribute_R2 << ", no_const_t, C(\"" << UEntity_R2 << "::" << UAttribute_R2 << "\") );" 
                << line_g(1) << htab_g(2) << "METHOD_KEY_REGISTER ( " << UEntity_R2 << "Interpreter, boost::shared_ptr< Base<EncodingT> >, has" << UAttribute_R2 << ", const_t, C(\"" << UEntity_R2 << "::Has" << UAttribute_R2 << "\") );" 
				<< line_g(1) << htab_g(2) << "METHOD_KEY_REGISTER ( " << UEntity_R2 << "Interpreter, void, remove" << UAttribute_R2 << ", no_const_t, C(\"" << UEntity_R2 << "::remove" << UAttribute_R2 << "\") );")
				[If_IsREF_R2])
				[attr0, attrN]
				<< ListRelationN_R2(
                   line_g(1) << htab_g(2) << "METHOD_KEY_REGISTER1( " << URelation1_R2 << "Interpreter, void, remove" << URelationNName_R2 << ", no_const_t, C(\"" << URelation1_R2 << "::remove" << URelationNName_R2 << "s\") );"
                << line_g(1) << htab_g(2) << "METHOD_KEY_REGISTER2( " << URelation1_R2 << "Interpreter, void, insert" << URelationNName_R2 << ", no_const_t, C(\"" << URelation1_R2 << "::" << URelationNName_R2 << "s\") );"
                << line_g(1) << htab_g(2) << "METHOD_KEY_REGISTER1( " << URelation1_R2 << "Interpreter, boost::shared_ptr< Base<EncodingT> >, get" << URelationNName_R2 << ", no_const_t, C(\"" << URelation1_R2 << "::" << URelationNName_R2 << "s\") );"
                << line_g(1) << htab_g(2) << "METHOD_KEY_REGISTER ( " << URelation1_R2 << "Interpreter, void, clear" << URelationNName_R2 << "s, no_const_t, C(\"" << URelation1_R2 << "::Clear" << URelationNName_R2 << "s\") );"
                << line_g(1) << htab_g(2) << "METHOD_KEY_REGISTER ( " << URelation1_R2 << "Interpreter, boost::shared_ptr< Base<EncodingT> >, has" << URelationNName_R2 << "s, const_t, C(\"" << URelation1_R2 << "::Has" << URelationNName_R2 << "s\") );"
                << line_g(1) << htab_g(2) << "METHOD_KEY_REGISTER ( " << URelation1_R2 << "Interpreter, boost::shared_ptr< Base<EncodingT> >, " << LRelationNName_R2 << "sCount, const_t, C(\"" << URelation1_R2 << "::" << URelationNName_R2 << "sCount\") );");

			CreateAttributeUnRegister_R2 =
				(line_g(1) << htab_g(2) << "METHOD_KEY_UNREGISTER ( C(\"" << UEntity_R2 << "::" << UAttribute_R2 << "\") );"
				<< (line_g(1) << htab_g(2) << "METHOD_KEY_UNREGISTER1( C(\"" << UEntity_R2 << "::" << UAttribute_R2 << "\") );")
				[If_IsWriteAttribute_R2]
				<< (line_g(1) << htab_g(2) << "METHOD_KEY_UNREGISTER ( C(\"" << UEntity_R2 << "::Has" << UAttribute_R2 << "\") );"
				<< line_g(1) << htab_g(2) << "METHOD_KEY_UNREGISTER ( C(\"" << UEntity_R2 << "::remove" << UAttribute_R2 << "\") );")
				[If_IsREF_R2])
				[attr0, attrN]
				<< ListRelationN_R2(
                   line_g(1) << htab_g(2) << "METHOD_KEY_UNREGISTER1( C(\"" << URelation1_R2 << "::remove" << URelationNName_R2 << "s\") );"
                << line_g(1) << htab_g(2) << "METHOD_KEY_UNREGISTER2( C(\"" << URelation1_R2 << "::" << URelationNName_R2 << "s\") );"
                << line_g(1) << htab_g(2) << "METHOD_KEY_UNREGISTER1( C(\"" << URelation1_R2 << "::" << URelationNName_R2 << "s\") );"
                << line_g(1) << htab_g(2) << "METHOD_KEY_UNREGISTER ( C(\"" << URelation1_R2 << "::Clear" << URelationNName_R2 << "s\") );"
                << line_g(1) << htab_g(2) << "METHOD_KEY_UNREGISTER ( C(\"" << URelation1_R2 << "::Has" << URelationNName_R2 << "s\") );"
                << line_g(1) << htab_g(2) << "METHOD_KEY_UNREGISTER ( C(\"" << URelation1_R2 << "::" << URelationNName_R2 << "sCount\") );");

			CreateConstructorFactoryPrototype_R2 =
				str_g("FACTORY_PROTOTYPE") << EntityParamSize_R2 << "(" << UEntity_R2 << "Interpreter"
				<< ListEntityParam_R2(CommaParam_R2 << "In< boost::shared_ptr< Base<EncodingT> > >")
				<< ")";	

		}
    }
}


