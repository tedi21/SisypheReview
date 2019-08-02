#include "SimpleCPPInterpreterGenerator.hpp"

namespace dsg {

	namespace generator {

        SimpleCPPInterpreterGenerator::SimpleCPPInterpreterGenerator()
		{
            SourceCPP =
                CreateFile[Has_ClassOrEnum];

			CreateFile =
                                CreateHeader(file_g(getFileNameHandler(KIND_ALIAS)) << "Interpreter_impl.hpp")
                << line_g(1) << CreateMacro
                << line_g(1) << CreateNamespace(str_g("interp"))
                << line_g(1) << CreateDeclaration
                << ListClassOrEnum
                   (   
                      (line_g(1)
                    << CreateInterpreterClassMembers)[Has_Constant || Has_Method || Has_Attribute]
                   )       
				<< line_g(1) << CreateEndNamespace
                << (line_g(2)
                <<  cnt_g(getContentDataHandler())) [contentByType(CONTENT_TYPE_GLOBAL_BODY)]
                << line_g(1) << CreateEndMacro;

            CreateMacro =
                   line_g(1) << str_g("#define A(str) encode<EncodingT,ansi>(str)")
                << line_g(1) << str_g("#define C(str) encode<ansi,EncodingT>(str)");

            CreateEndMacro =
                   line_g(1) << str_g("#undef A")
                << line_g(1) << str_g("#undef C");

            CreateDeclaration =
                   ListDependence
                   (
                        line_g(1) << "template <class EncodingT>"
                     << line_g(1) << "class " << DependenceName << "Interpreter;"
                     << ~-line_g(1)
                   );

            CreateInterpreterClassMembers =
                   line_g(1) << "template <class EncodingT>"
                << line_g(1) << ClassName << "Interpreter<EncodingT>::" << ClassName << "Interpreter()"
                << line_g(1) << "{"
                << (line_g(1) << cnt_g(getContentDataHandler()))     [contentByType(CONTENT_TYPE_INITIALIZATIONBODY)]
                << line_g(1) << "}"
                << (line_g(2) << "template <class EncodingT>"
                <<  line_g(1) << ClassName << "Interpreter<EncodingT>::~" << ClassName << "Interpreter()"
                <<  line_g(1) << "{"
                <<  line_g(1) << htab_g(1) << "tidyValue();"
                <<  line_g(1) << "}")                               [has_g(0, contentByType(CONTENT_TYPE_DESTRUCTIONBODY), gt_g())]
                << (line_g(2) << "template <class EncodingT>"
                <<  line_g(1) << "void " << ClassName << "Interpreter<EncodingT>::tidyValue()"
                <<  line_g(1) << "{"
                <<  (line_g(1) << cnt_g(getContentDataHandler()))   [contentByType(CONTENT_TYPE_DESTRUCTIONBODY)]
                <<  line_g(1) << "}")                               [has_g(0, contentByType(CONTENT_TYPE_DESTRUCTIONBODY), gt_g()) || Has_DynamicMethod || Has_Attribute]
                << (line_g(2) << "template <class EncodingT>"
                <<  line_g(1) << "void " << ClassName << "Interpreter<EncodingT>::initValue(const " << ClassName << "& object)"
                <<  line_g(1) << "{"
                <<  (line_g(1) << htab_g(1) << "m_object = object;") [empty_g(contentByType(CONTENT_TYPE_COPYBODY))]
                <<  (line_g(1) << cnt_g(getContentDataHandler()))    [contentByType(CONTENT_TYPE_COPYBODY)]
                <<  line_g(1) << "}"
                <<  line_g(2) << "template <class EncodingT>"
                <<  line_g(1) << ClassName << "& " << ClassName << "Interpreter<EncodingT>::refValue()"
                <<  line_g(1) << "{"
                <<  line_g(1) << (htab_g(1) << "return m_object;")   [empty_g(contentByType(CONTENT_TYPE_VALUEBODY))]
                              << cnt_g(getContentDataHandler())      [contentByType(CONTENT_TYPE_VALUEBODY)]
                <<  line_g(1) << "}"
                <<  line_g(2) << "template <class EncodingT>"
                <<  line_g(1) << "const " << ClassName << "& " << ClassName << "Interpreter<EncodingT>::refValue() const"
                <<  line_g(1) << "{"
                <<  line_g(1) << (htab_g(1) << "return m_object;")   [empty_g(contentByType(CONTENT_TYPE_VALUEBODY))]
                              << cnt_g(getContentDataHandler())      [contentByType(CONTENT_TYPE_VALUEBODY)]
                <<  line_g(1) << "}"
                <<  line_g(2) << "template <class EncodingT>"
                <<  line_g(1) << ClassName << "Interpreter<EncodingT>::" << ClassName << "Interpreter(const " << ClassName << "& object)"
                <<  line_g(1) << "{"
                <<  line_g(1) << htab_g(1) << "initValue(object);"
                <<  line_g(1) << "}"
                <<  (line_g(2) << "template <class EncodingT>"
                <<   line_g(1) << ClassName << "Interpreter<EncodingT>::" << ClassName << "Interpreter(const " << ClassName << "Interpreter<EncodingT>& rhs)"
                <<   line_g(1) << "{"
                <<   line_g(1) << htab_g(1) << "initValue(rhs.refValue());"
                <<   line_g(1) << "}"
                <<   line_g(2) << "template <class EncodingT>"
                <<   line_g(1) << ClassName << "Interpreter<EncodingT>& " << ClassName << "Interpreter<EncodingT>::operator=(const " << ClassName << "Interpreter<EncodingT>& rhs)"
                <<   line_g(1) << "{"
                <<   line_g(1) << htab_g(1) << "value(rhs.refValue());"
                <<   line_g(1) << htab_g(1) << "return *this;"
                <<   line_g(1) << "}")                               [has_g(0, contentByType(CONTENT_TYPE_COPYBODY), gt_g())]
                <<  line_g(2) << "template <class EncodingT>"
                <<  line_g(1) << "const " << ClassName << "& " << ClassName << "Interpreter<EncodingT>::value() const"
                <<  line_g(1) << "{"
                <<  line_g(1) << htab_g(1) << "return refValue();"
                <<  line_g(1) << "}"
                <<  line_g(2) << "template <class EncodingT>"
                <<  line_g(1) << "void " << ClassName << "Interpreter<EncodingT>::value(" << ClassName << " const& object)"
                <<  line_g(1) << "{"
                <<  line_g(1) << htab_g(1) << "if (&object != &value()) {"
                <<  line_g(1) << htab_g(2) << "tidyValue();"
                <<  line_g(1) << htab_g(2) << "initValue(object);"
                <<  line_g(1) << htab_g(1) << "}"
                <<  line_g(1) << "}") [Has_DynamicMethod || Has_Attribute]
                << line_g(2) << "template <class EncodingT>"
                << line_g(1) << "typename EncodingT::string_t " << ClassName << "Interpreter<EncodingT>::toString() const"
                << line_g(1) << "{"
                << line_g(1) << htab_g(1) << "return EncodingT::EMPTY;"
                << line_g(1) << "}"
                << line_g(2) << "template <class EncodingT>"
                << line_g(1) << "boost::shared_ptr< Base<EncodingT> > " << ClassName << "Interpreter<EncodingT>::clone() const"
                << line_g(1) << "{"
                << line_g(1) << htab_g(1) << "return boost::shared_ptr< Base<EncodingT> >(new " << ClassName << "Interpreter<EncodingT>(*this));"
                << line_g(1) << "}"
                << line_g(2) << "template <class EncodingT>"
                << line_g(1) << "typename EncodingT::string_t " << ClassName << "Interpreter<EncodingT>::getClassName() const"
                << line_g(1) << "{"
                << line_g(1) << htab_g(1) << "return UCS(\"" << ClassName << "\");"
                << line_g(1) << "}"
                << line_g(2) << "template <class EncodingT>"
                << line_g(1) << "boost::shared_ptr< Base<EncodingT> > " << ClassName << "Interpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)"
                << line_g(1) << "{"
                << line_g(1) << htab_g(1) << "boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());"
                << line_g(1) << htab_g(1) << "ParameterArray args, ret;"
                << line_g(1) << htab_g(1) << "if (check_parameters_array(params, args))"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "if (tryInvoke(this, UCS(\"" << ClassName << "\"), method, args, ret) ||"
                << line_g(1) << htab_g(3) << "tryInvoke(this, UCS(\"Base\"), method, args, ret))"
                << line_g(1) << htab_g(2) << "{"
                << line_g(1) << htab_g(3) << "find_parameter(ret, FACTORY_RETURN_PARAMETER, obj);"
                << line_g(1) << htab_g(3) << "for (size_t i = 0; i < params.size(); ++i)"
                << line_g(1) << htab_g(3) << "{"
                << line_g(1) << htab_g(4) << "find_parameter(ret, i, params[i]);"
                << line_g(1) << htab_g(3) << "}"
                << line_g(1) << htab_g(2) << "}"
                << line_g(1) << htab_g(2) << "else"
                << line_g(1) << htab_g(2) << "{"
                << line_g(1) << htab_g(3) << "Category* logger = &Category::getInstance(LOGNAME);"
                << line_g(1) << htab_g(3) << "logger->errorStream() << \"Unexpected call in " << ClassName << ", no method \\\"\" << A(method) << \"\\\" exists.\";"
                << line_g(1) << htab_g(2) << "}"
                << line_g(1) << htab_g(1) << "}"
                << line_g(1) << htab_g(1) << "return obj;"
                << line_g(1) << "}"
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
                <<  cnt_g(getContentDataHandler()) [contentByType(CONTENT_TYPE_IMPLEMENTATION)])
                << (line_g(1)
                <<  CreateInterpreterCheck
                <<  line_g(1)
                <<  CreateInterpreterReset) [Has_DynamicMethod || Has_Attribute];

            CommentInterpreterMethod =
                   (line_g(1) << "//" << ent_g(getEntityCommentHandler()))
                   [ent_g(getHasEntityCommentHandler())];

            htabIsPointer =
                    WithClassMethod(htab_g(1)[If_IsPointerEntity]);

            CreateInterpreterMethod =
                   line_g(1) << "template <class EncodingT>"
                << line_g(1)
                << str_g("boost::shared_ptr< Base<EncodingT> > ")[Has_Return]
                << str_g("void ")                                [else_g()]
                << MethodClassName << "Interpreter<EncodingT>::" << lower_g(InternalMethodName, 0, 1) << "(" << CreateInterpreterParameters << ")"
                << str_g(" const")[If_IsConstMethod]
                << line_g(1) << "{"
                << ((line_g(1) << htab_g(1) << "boost::shared_ptr< Base<EncodingT> > res(new " << GotoReturn(InterpreterType) << "());")[Has_Return]
                << WithClassMethod(
                    (
                        line_g(1) << htab_g(1) << ClassName << " valuePtr = refValue();"
                     << line_g(1) << htab_g(1) << "if (valuePtr != NULL)"
                     << line_g(1) << htab_g(1) << "{"
                    )
                    [If_IsPointerEntity])
                << (
                       ListParameter
                       (
                           line_g(1) << htab_g(1) << htabIsPointer
                        << AttributeType << " native" << upper_g(attr_g(getAttributeNameHandler(KIND_ALIAS)), 0, 1) << ";"
                       )
                    << line_g(1) << htab_g(1) << htabIsPointer
                    << "if ("
                    << ListParameter
                       (
                           ~+(line_g(1) << htab_g(2) << htabIsPointer)
                        << InterpreterCheck << "(" << ParameterName << ", native" << upper_g(attr_g(getAttributeNameHandler(KIND_ALIAS)), 0, 1) << (str_g(", ") << InterpreterCheckFunction)[If_IsARRAY] << ")"
                        << ~-str_g(" && ")
                       )
                    << ")"
                    << line_g(1) << htab_g(1) << htabIsPointer << "{"
                   )[Has_Parameter]
                << line_g(1) << htab_g(1)
                << htabIsPointer
                << htab_g(1) [Has_Parameter]
                << ("res.reset(new " << GotoReturn(InterpreterType) << "(")[Has_Return]
                << (
                        (+attr_g(getAttributeNameHandler(KIND_NAME)))
                        [If_IsCONTEXTUAL && If_IsREF && !If_IsAUTO && !If_IsID]
                        [attr0,attrN]
                     << "::"
                   )                    [If_IsStaticMethod]
                << WithClassMethod(
                        str_g("valuePtr->")    [If_IsPointerEntity]
                     << str_g("refValue().")   [else_g()]
                   )                    [else_g()]
                << ent_g(getEntityFunctionNameHandler(KIND_NAME)) << "("
                << ListParameter
                   (
                       ParameterPassing( str_g("&")[If_IsVIRTUAL] << "native" << upper_g(attr_g(getAttributeNameHandler(KIND_ALIAS)), 0, 1)) << ~-str_g(", ")
                   )
                << ")"
                << str_g("))")[Has_Return]
                << str_g(";")
                << ListOutputParameter
                   (
                       line_g(1) << htab_g(2) << htabIsPointer << InterpreterReset << "(" << ParameterName << ", native" << upper_g(attr_g(getAttributeNameHandler(KIND_ALIAS)), 0, 1) << (str_g(", ") << InterpreterResetFunction)[If_IsARRAY] << ");"
                   )
                << ( line_g(1) << htab_g(1) << htabIsPointer << "}")[Has_Parameter]
                << WithClassMethod((line_g(1) << htab_g(1) << "}")[If_IsPointerEntity])
                << (line_g(1) << htab_g(1) << "return res;")[Has_Return])
                                                                 [empty_g(contentByEnt(CONTENT_TYPE_IMPLEMENTATIONBODY))]
                << (line_g(1) << cnt_g(getContentDataHandler())) [contentByEnt(CONTENT_TYPE_IMPLEMENTATIONBODY)]
                << line_g(1) << "}";

            CreateInterpreterParameters =
                   ListParameter
                   (
                        str_g("const ")[If_IsReadOnly]
                     << "boost::shared_ptr< Base<EncodingT> >& " << ParameterName << ~-str_g(", ")
                   );

           CommentInterpreterConstant =
                  (line_g(1) << "//" << attr_g(getAttributeCommentHandler()))
                  [attr_g(getHasAttributeCommentHandler())];

           CreateInterpreterConstant =
                   line_g(1) << "template <class EncodingT>"
                << line_g(1)
                << str_g("boost::shared_ptr< Base<EncodingT> > ")
                << ClassName << "Interpreter<EncodingT>::get" << upper_g(InternalConstantName, 0, 1) << "() const"
                << line_g(1) << "{"
                << line_g(1) << htab_g(1) << "return boost::shared_ptr< Base<EncodingT> > (new " << InterpreterType << "(" << (ClassName << "::")[If_IsClass] << attr_g(getAttributeNameHandler(KIND_NAME)) << "));"
                << line_g(1) << "}";

            CommentInterpreterAttribute =
                   (line_g(1) << "//" << attr_g(getAttributeCommentHandler()))
                   [attr_g(getHasAttributeCommentHandler())];

            CreateInterpreterAttribute =
                   line_g(1) << "template <class EncodingT>"
                << line_g(1)
                << "boost::shared_ptr< Base<EncodingT> > "
                << ClassName << "Interpreter<EncodingT>::get" << lower_g(InternalAttributeName, 0, 1) << "() const"
                << line_g(1) << "{"
                << ((
                        line_g(1) << htab_g(1) << ClassName << " valuePtr = refValue();"
                     << line_g(1) << htab_g(1) << "if (valuePtr != NULL)"
                     << line_g(1) << htab_g(1) << "{"
                     << line_g(1) << htab_g(2)
                   )                        [If_IsPointerEntity]
                << (line_g(1) << htab_g(1)) [else_g]
                << "boost::shared_ptr< Base<EncodingT> > res(new " << InterpreterType << "("
                << str_g("valuePtr->")    [If_IsPointerEntity]
                << str_g("refValue().")   [else_g()]
                << attr_g(getAttributeNameHandler(KIND_NAME))
                << "));"
                << (line_g(1) << htab_g(1) << "}")               [If_IsPointerEntity]
                << line_g(1) << htab_g(1) << "return res;")
                                                                 [empty_g(contentByAttr(CONTENT_TYPE_IMPLEMENTATIONBODY))]
                << (line_g(1) << cnt_g(getContentDataHandler())) [contentByAttr(CONTENT_TYPE_IMPLEMENTATIONBODY)]
                << line_g(1) << "}";

           CreateInterpreterCheck =
                   line_g(1) << "template <class EncodingT>"
                << line_g(1) << "bool check_" << ClassName << "(boost::shared_ptr< Base<EncodingT> > const& val, " << ClassName << "& a)"
                << line_g(1) << "{"
                << line_g(1) << htab_g(1) << "boost::shared_ptr< " << ClassName << "Interpreter<EncodingT> > value  = dynamic_pointer_cast< " << ClassName << "Interpreter<EncodingT> >(val);"
                << line_g(1) << htab_g(1) << "if (value)"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "a = value->value();"
                << line_g(1) << htab_g(1) << "}"
                << line_g(1) << htab_g(1) << "else"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "Category * logger = &Category::getInstance(LOGNAME);"
                << line_g(1) << htab_g(2) << "logger->errorStream() << \"" << ClassName << " expected, got \" << A(val->getClassName());"
                << line_g(1) << htab_g(1) << "}"
                << line_g(1) << htab_g(1) << "return (value != NULL);"
                << line_g(1) << "}";

           CreateInterpreterReset =
                   line_g(1) << "template <class EncodingT>"
                << line_g(1) << "bool reset_" << ClassName << "(boost::shared_ptr< Base<EncodingT> >& val, " << ClassName << " const& a)"
                << line_g(1) << "{"
                << line_g(1) << htab_g(1) << "boost::shared_ptr< " << ClassName << "Interpreter<EncodingT> > value  = dynamic_pointer_cast< " << ClassName << "Interpreter<EncodingT> >(val);"
                << line_g(1) << htab_g(1) << "if (value)"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "value->value(a);"
                << line_g(1) << htab_g(1) << "}"
                << line_g(1) << htab_g(1) << "else"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "Category* logger = &Category::getInstance(LOGNAME);"
                << line_g(1) << htab_g(2) << "logger->errorStream() << \"" << ClassName << " expected, got \" << A(val->getClassName());"
                << line_g(1) << htab_g(1) << "}"
                << line_g(1) << htab_g(1) << "return (value != NULL);"
                << line_g(1) << "}";
		}
    }
}
