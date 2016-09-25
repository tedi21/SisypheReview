#include "SimpleHPPInterpreterGenerator.hpp"

namespace dsg {

	namespace generator {

        SimpleHPPInterpreterGenerator::SimpleHPPInterpreterGenerator()
		{
			SourceHPP = 
                CreateFile[Has_ClassOrEnum];

			CreateFile =
                                CreateHeader(file_g(getFileNameHandler(KIND_ALIAS)) << "Interpreter.hpp")
                << line_g(1) << CreateHPPDefine("_" << file_g(getFileNameHandler(KIND_ALIAS)) << "_INTERPRETER_H_")
				<< line_g(1) << CreateInclude
                << line_g(1) << CreateMacro
                << line_g(1) << CreateUsingNamespace
                << (line_g(2)
                <<  cnt_g(getContentDataHandler())) [contentByType(CONTENT_TYPE_GLOBAL)]
                << line_g(1) << CreateNamespace(str_g("interp"))
                << ListClassOrEnum
                   (   
                      (line_g(1)
                    << CommentInterpreterClass
                    << CreateInterpreterClass)[Has_Constant || Has_Method || Has_Attribute]
                   )       
				<< line_g(1) << CreateEndNamespace
                << line_g(1) << CreateEndMacro
                << line_g(1) << str_g("#include \"") << file_g(getFileNameHandler(KIND_ALIAS)) << "Interpreter_impl.hpp\""
				<< line_g(1) << CreateHPPEndDefine;            

			CreateInclude =
                   line_g(1) << str_g("#include \"config.hpp\"")
                << line_g(1) << str_g("#include \"macros.hpp\"")
                << line_g(1) << str_g("#include \"String.hpp\"")
                << line_g(1) << str_g("#include \"Array.hpp\"")
                << (line_g(1) << str_g("#include \"") << file_g(getFileNameHandler(KIND_NAME)) << ".h\"") [empty_g(contentByType(CONTENT_TYPE_GLOBALINCLUSION))]
                << (line_g(1) << cnt_g(getContentDataHandler()))                                          [contentByType(CONTENT_TYPE_GLOBALINCLUSION)];

            CreateMacro =
                   line_g(1) << str_g("#define A(str) encode<EncodingT,ansi>(str)")
                << line_g(1) << str_g("#define C(str) encode<ansi,EncodingT>(str)");

            CreateEndMacro =
                   line_g(1) << str_g("#undef A")
                << line_g(1) << str_g("#undef C");

            CreateUsingNamespace =
                   line_g(1) << str_g("using namespace boost;")
                << ListPackage
                   (
                       line_g(1) << str_g("using namespace ") << PackageName << ";"
                   );

            CommentInterpreterClass =
                   (line_g(1) << htab_g(1) << "//" << ent_g(getEntityCommentHandler()))
                   [ent_g(getHasEntityCommentHandler())];

            CreateInterpreterClass =
                    line_g(1) << htab_g(1) << "template <class EncodingT>"
                 << line_g(1) << htab_g(1) << "class " << ClassName << "Interpreter"
                 << line_g(1) << htab_g(1) << ": public Base<EncodingT>"
                 << line_g(1) << htab_g(1) << "{"
                 << line_g(1) << htab_g(1) << "private:"
                 <<((line_g(1) << htab_g(2) << ClassName << " m_object;") [empty_g(contentByType(CONTENT_TYPE_DECLARATIONBODY))]
                 << (line_g(1) << cnt_g(getContentDataHandler()))         [contentByType(CONTENT_TYPE_DECLARATIONBODY)]
                 <<  line_g(2) << htab_g(2) << "void initValue(const " << ClassName << "& object);"
                 <<  line_g(2) << htab_g(2) << ClassName << "& value();"
                 <<  line_g(2) << htab_g(2) << "const " << ClassName << "& value() const;")
                                                                          [Has_DynamicMethod || Has_Attribute]
                 << line_g(2) << htab_g(2) << "void tidyValue();"
                 << line_g(2) << htab_g(1) << "public:"
                 << line_g(1) << htab_g(2) << ClassName << "Interpreter();"
                 << line_g(2) << htab_g(2) << "~" << ClassName << "Interpreter();"
                 << (line_g(2) << htab_g(2) << ClassName << "Interpreter(const " << ClassName << "& object);"
                 <<  line_g(2) << htab_g(2) << ClassName << "Interpreter(const " << ClassName << "Interpreter<EncodingT>& rhs);"
                 <<  line_g(2) << htab_g(2) << ClassName << "Interpreter<EncodingT>& operator=(const " << ClassName << "Interpreter<EncodingT>& rhs);"
                 <<  line_g(2) << htab_g(2) << "const " << ClassName << "& getValue() const;"
                 <<  line_g(2) << htab_g(2) << "void setValue(" << ClassName << " const& object);") [Has_DynamicMethod || Has_Attribute]
                 << line_g(2) << htab_g(2) << "virtual typename EncodingT::string_t toString() const;"
                 << line_g(2) << htab_g(2) << "virtual boost::shared_ptr< Base<EncodingT> > clone() const;"
                 << line_g(2) << htab_g(2) << "virtual typename EncodingT::string_t getClassName() const;"
                 << line_g(2) << htab_g(2) << "virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);"
                 << ListConstant
                    (
                       line_g(1)
                       << CommentInterpreterConstant
                       << CreateInterpreterConstant
                    )
                 << ListMethod
                    (
                       line_g(1)
                       << CommentInterpreterMethod
                       << CreateInterpreterMethod
                    )
                 << ListAttribute
                    (
                       line_g(1)
                       << CommentInterpreterAttribute
                       << CreateInterpreterAttribute
                    )
                  << (line_g(1)
                  <<  cnt_g(getContentDataHandler())) [contentByType(CONTENT_TYPE_DECLARATION)]
                  << line_g(1)
                  << CreateInterpreterRegister
                  << line_g(1)
                  << CreateInterpreterUnregister
                  << line_g(1) << htab_g(1) << "};"
                  << (line_g(1)
                  <<  line_g(1) << htab_g(1) << "template <class EncodingT>"
                  <<  line_g(1) << htab_g(1) << "bool check_" << ClassName << "(boost::shared_ptr< Base<EncodingT> > const& val, " << ClassName << "& a);"
                  <<  line_g(1)
                  <<  line_g(1) << htab_g(1) << "template <class EncodingT>"
                  <<  line_g(1) << htab_g(1) << "bool reset_" << ClassName << "(boost::shared_ptr< Base<EncodingT> >& val, " << ClassName << " const& a);") [Has_DynamicMethod || Has_Attribute];

            CommentInterpreterMethod =
                   (line_g(1) << htab_g(2) << "//" << ent_g(getEntityCommentHandler()))
                   [ent_g(getHasEntityCommentHandler())];

            CreateInterpreterMethod =
                   (line_g(1) << htab_g(2) << "FACTORY_PROTOTYPE" << ParameterSize << "(" << lower_g(InternalMethodName, 0, 1) << ", "
                    << ListParameter
                       (
                            str_g("In")   [If_IsReadOnly]
                         << str_g("InOut")[else_g()]
                         << "< boost::shared_ptr< Base<EncodingT> > >" << ~-str_g(", ")
                       )
                    << ")")[Has_Parameter]
                << line_g(1) << htab_g(2)
                << str_g("boost::shared_ptr< Base<EncodingT> >")[Has_Return]
                << str_g("void")                         [else_g()]
                << " " << lower_g(InternalMethodName, 0, 1) << "(" << CreateInterpreterParameters << ")" << str_g(" const")[If_IsConstMethod] << ";";

            CreateInterpreterParameters =
                   ListParameter
                   (
                        str_g("const ")[If_IsReadOnly]
                     << "boost::shared_ptr< Base<EncodingT> >& " << ParameterName << ~-str_g(", ")
                   );

            CommentInterpreterConstant =
                   (line_g(1) << htab_g(2) << "//" << attr_g(getAttributeCommentHandler()))
                   [attr_g(getHasAttributeCommentHandler())];

            CreateInterpreterConstant =
                    line_g(1) << htab_g(2)
                 << str_g("boost::shared_ptr< Base<EncodingT> > get") << upper_g(InternalConstantName, 0, 1) << "() const;";

            CommentInterpreterAttribute =
                   (line_g(1) << htab_g(2) << "//" << attr_g(getAttributeCommentHandler()))
                   [attr_g(getHasAttributeCommentHandler())];

            CreateInterpreterAttribute =
                    line_g(1) << htab_g(2)
                 << str_g("boost::shared_ptr< Base<EncodingT> > get") << lower_g(InternalAttributeName, 0, 1) << "() const;";

            RegisterSize =
                    ParameterSize [Has_Parameter]
                 << str_g(" ")    [else_g()];

            CreateInterpreterRegister =
                    line_g(1) << htab_g(2) << "FACTORY_BEGIN_REGISTER"
                 << line_g(1) << htab_g(3) << "CLASS_KEY_REGISTER  ( " << ClassName << "Interpreter, C(\"" << ClassName << "\") );"
                 << ListConstant
                    (
                        line_g(1) << htab_g(3) << "METHOD_KEY_REGISTER ( " << ClassName << "Interpreter, "
                     << str_g("boost::shared_ptr< Base<EncodingT> >, ")
                     << "get" << upper_g(InternalConstantName, 0, 1) << ", "
                     << str_g("const_t, ")
                     << "C(\"" << ClassName << "::" << ConstantName << "\") );"
                    )
                 << ListMethod
                    (
                        line_g(1) << htab_g(3) << "METHOD_KEY_REGISTER" << RegisterSize << "( " << MethodClassName << "Interpreter, "
                     << str_g("boost::shared_ptr< Base<EncodingT> >, ")[Has_Return]
                     << str_g("void, ")                         [else_g()]
                     << lower_g(InternalMethodName, 0, 1) << ", "
                     << str_g("const_t")    [If_IsConstMethod]
                     << str_g("no_const_t") [else_g()]
                     << ", C(\"" << MethodClassName << "::" << MethodName << "\") );"
                    )
                << ListAttribute
                   (
                       line_g(1) << htab_g(3) << "METHOD_KEY_REGISTER ( " << ClassName << "Interpreter, "
                    << str_g("boost::shared_ptr< Base<EncodingT> >, ")
                    << "get" << lower_g(InternalAttributeName, 0, 1) << ", "
                    << str_g("const_t, ")
                    << "C(\"" << ClassName << "::" << AttributeName << "\") );"
                   )
                 << (line_g(1)
                 <<  cnt_g(getContentDataHandler())) [contentByType(CONTENT_TYPE_REGISTER)]
                 << line_g(1) << htab_g(2) << "FACTORY_END_REGISTER";

            CreateInterpreterUnregister =
                    line_g(1) << htab_g(2) << "FACTORY_BEGIN_UNREGISTER"
                 << line_g(1) << htab_g(3) << "CLASS_KEY_UNREGISTER  ( C(\"" << ClassName << "\") );"
                 << ListConstant
                    (
                        line_g(1) << htab_g(3) << "METHOD_KEY_UNREGISTER ( C(\"" << ClassName << "::" << ConstantName << "\") );"
                    )
                 << ListMethod
                    (
                        line_g(1) << htab_g(3) << "METHOD_KEY_UNREGISTER" << RegisterSize << "( C(\"" << MethodClassName << "::" << MethodName << "\") );"
                    )
                 << ListAttribute
                    (
                        line_g(1) << htab_g(3) << "METHOD_KEY_UNREGISTER ( C(\"" << ClassName << "::" << AttributeName << "\") );"
                    )
                 << (line_g(1)
                 <<  cnt_g(getContentDataHandler())) [contentByType(CONTENT_TYPE_UNREGISTER)]
                 << line_g(1) << htab_g(2) << "FACTORY_END_UNREGISTER";
		}
    }
}
