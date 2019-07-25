#include "SimpleCPPInterpreterAccessGenerator.hpp"

namespace dsg {

	namespace generator {

		SimpleCPPInterpreterAccessGenerator::SimpleCPPInterpreterAccessGenerator()
		{
			SourceCPP_R2 = 
				CreateFile_R2;

			CreateFile_R2 =
                CreateMacro_R2
                << CreateNamespace_R2(str_g("interp"))
				<< ( CreateInterpretAccess_R2 ) [ent0, entN]
                << CreateEndNamespace_R2
                << CreateEndMacro_R2;

			CreateInterpretAccess_R2 =
				CreateInterpreterAccessConstructor_R2
				<< CreateInterpreterAccessToString_R2
				<< CreateInterpreterAccessClone_R2
				<< CreateInterpreterAccessGetClassName_R2
				<< CreateInterpreterAccessInvoke_R2
				<< ConvertPtrVectorToArray_R2
				<< CreateInterpreterAccessGetAll_R2
				<< CreateInterpreterAccessGetMany_R2
				<< CreateInterpreterAccessGetOne_R2
				<< CreateInterpreterAccessSelectOne_R2
				<< CreateInterpreterAccessSelectMany_R2
				<< CreateInterpreterAccessCancelSelected_R2
				<< CreateInterpreterAccessIsSelected_R2
				<< CreateInterpreterAccessFillREF_R2
				<< CreateInterpreterAccessFillAllRelation_R2
				<< CreateInterpreterAccessFillOneRelation_R2
				<< CreateInterpreterAccessFillManyRelation_R2
                << CreateInterpreterAccessIsAltered_R2
				<< CreateInterpreterAccessUpdate_R2
				<< CreateInterpreterAccessInsert_R2
                << CreateInterpreterAccessDelete_R2
                << CreateInterpreterAccessSetError_R2
                << CreateInterpreterAccessClearError_R2
                << CreateInterpreterAccessGetError_R2;

			CreateInterpreterAccessConstructor_R2 =
				str_g("template <class EncodingT>")
				<< line_g(1) << UEntity_R2 << "InterpreterAccess<EncodingT>::" << UEntity_R2 << "InterpreterAccess()"
				<< line_g(1) << "{"
				<< line_g(1) << htab_g(1) << "m_object = " << AccessClass_R2 << "::getInstance();"
                << line_g(1) << htab_g(1) << "m_error = false;"
				<< line_g(1) << "}"
				<< line_g(2);    
	    
			CreateInterpreterAccessDestructor_R2 =
				str_g("template <class EncodingT>")
				<< line_g(1) << UEntity_R2 << "InterpreterAccess<EncodingT>::~" << UEntity_R2 << "InterpreterAccess()"
				<< line_g(1) << "{}"
				<< line_g(2);  

			CreateInterpreterAccessToString_R2 =
				str_g("template <class EncodingT>")
				<< line_g(1) << "typename EncodingT::string_t " << UEntity_R2 << "InterpreterAccess<EncodingT>::toString() const"
				<< line_g(1) << "{"
				<< line_g(1) << htab_g(1) << "return EncodingT::EMPTY;"
				<< line_g(1) << "}"
				<< line_g(2);   

			CreateInterpreterAccessClone_R2 =
				str_g("template <class EncodingT>")
				<< line_g(1) << "boost::shared_ptr< Base<EncodingT> > " << UEntity_R2 << "InterpreterAccess<EncodingT>::clone() const"
				<< line_g(1) << "{"
				<< line_g(1) << htab_g(1) << "return boost::shared_ptr< Base<EncodingT> >(new " << UEntity_R2 << "InterpreterAccess<EncodingT>());"
				<< line_g(1) << "}"
				<< line_g(2); 

			CreateInterpreterAccessGetClassName_R2 =
				str_g("template <class EncodingT>")
				<< line_g(1) << "typename EncodingT::string_t " << UEntity_R2 << "InterpreterAccess<EncodingT>::getClassName() const"
				<< line_g(1) << "{"
				<< line_g(1) << htab_g(1) << "return C(\"" << UEntity_R2 << "Access\");"
				<< line_g(1) << "}"
				<< line_g(2);   

			CreateInterpreterAccessInvoke_R2 =
				str_g("template <class EncodingT>")
                << line_g(1) << "boost::shared_ptr< Base<EncodingT> > " << UEntity_R2 << "InterpreterAccess<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)"
				<< line_g(1) << "{"
				<< line_g(1) << htab_g(1) << "boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());"
				<< line_g(1)    
				<< line_g(1) << htab_g(1) << "ParameterArray args, ret;"
				<< line_g(1) << htab_g(1) << "if (check_parameters_array(params, args))"
				<< line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "if (tryInvoke(this, C(\"" << UEntity_R2 << "Access\"), method, args, ret) ||"
                << line_g(1) << htab_g(3) << "tryInvoke(this, C(\"Base\"), method, args, ret))"
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
				<< line_g(1) << htab_g(3) << "logger->errorStream() << \"Unexpected call in " << UEntity_R2 << "Access, no method \\\"\" << A(method) << \"\\\" exists.\";"
				<< line_g(1) << htab_g(2) << "}"
				<< line_g(1) << htab_g(1) << "}"
				<< line_g(1) << htab_g(1) << "return obj;"
				<< line_g(1) << "}"
				<< line_g(2);

			ConvertPtrVectorToArray_R2 =
				str_g("template <class EncodingT>")
				<< line_g(1) << "boost::shared_ptr< Base<EncodingT> > " << UEntity_R2 << "InterpreterAccess<EncodingT>::convert_array(const std::vector< boost::shared_ptr< _" << UEntity_R2 << "<EncodingT> > >& value) const"
				<< line_g(1) << "{"
				<< line_g(1) << htab_g(1) << "boost::shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());"
				<< line_g(1) << htab_g(1) << "for (size_t i=0; i<value.size(); ++i)"
				<< line_g(1) << htab_g(1) << "{"
				<< line_g(1) << htab_g(2) << "arr->addValue(boost::shared_ptr< Base<EncodingT> >(new " << UEntity_R2 << "Interpreter<EncodingT>(value[i])));"
				<< line_g(1) << htab_g(1) << "}"
				<< line_g(1) << htab_g(1) << "return arr;"
				<< line_g(1) << "}"
				<< line_g(2);

			CreateInterpreterAccessGetAll_R2 =
				str_g("template <class EncodingT>")
                << line_g(1) << "boost::shared_ptr< Base<EncodingT> > " << UEntity_R2 << "InterpreterAccess<EncodingT>::getAll" << UEntity_R2 << "s()"
				<< line_g(1) << "{"
                << line_g(1) << htab_g(1) << "boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());"
                << line_g(1) << htab_g(1) << "clearError();"
                << line_g(1) << htab_g(1) << "try"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "res = convert_array(m_object->getAll" << UEntity_R2 << "s());"
                << line_g(1) << htab_g(1) << "}"
                << line_g(1) << htab_g(1) << "catch (std::exception& e)"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "setError(e);"
                << line_g(1) << htab_g(1) << "}"
                << line_g(1) << htab_g(1) << "return res;"
				<< line_g(1) << "}"
				<< line_g(2);  

			CreateInterpreterAccessGetMany_R2 =
				str_g("template <class EncodingT>")
                << line_g(1) << "boost::shared_ptr< Base<EncodingT> > " << UEntity_R2 << "InterpreterAccess<EncodingT>::getMany" << UEntity_R2 << "s(const boost::shared_ptr< Base<EncodingT> >& filter)"
				<< line_g(1) << "{"
				<< line_g(1) << htab_g(1) << "boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());"
                << line_g(1) << htab_g(1) << "clearError();"
                << line_g(1) << htab_g(1) << "try"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "typename EncodingT::string_t nativeFilter;"
                << line_g(1) << htab_g(2) << "if (check_string<EncodingT>(filter, nativeFilter))"
                << line_g(1) << htab_g(2) << "{"
                << line_g(1) << htab_g(3) << "res = convert_array(m_object->getMany" << UEntity_R2 << "s(nativeFilter));"
                << line_g(1) << htab_g(2) << "}"
                << line_g(1) << htab_g(1) << "}"
                << line_g(1) << htab_g(1) << "catch (std::exception& e)"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "setError(e);"
                << line_g(1) << htab_g(1) << "}"
				<< line_g(1) << htab_g(1) << "return res;"
				<< line_g(1) << "}"
				<< line_g(2); 

			CreateInterpreterAccessGetOne_R2 =
				str_g("template <class EncodingT>")
                << line_g(1) << "boost::shared_ptr< Base<EncodingT> > " << UEntity_R2 << "InterpreterAccess<EncodingT>::getOne" << UEntity_R2 << "(" << CreateIDParam_R2 << ")"
				<< line_g(1) << "{"
				<< line_g(1) << htab_g(1) << "boost::shared_ptr< Base<EncodingT> > res(new " << UEntity_R2 << "Interpreter<EncodingT>());"
                << line_g(1) << htab_g(1) << "clearError();"
                << line_g(1) << htab_g(1) << "try"
                << line_g(1) << htab_g(1) << "{"
                << ListEntityIDParam_R2( line_g(1) << htab_g(2) << AttributeNativeType_R2 << " native" << UAttribute_R2 << ";" )
                << line_g(1) << htab_g(2) << "if ("
                << ListEntityIDParam_R2( ~+(line_g(1) << htab_g(3)) << AttributeCheck_R2( LAttribute_R2, "native" << UAttribute_R2) << ~-str_g(" &&") ) << ")"
                << line_g(1) << htab_g(2) << "{"
                << line_g(1) << htab_g(3) << "res.reset(new " << UEntity_R2 << "Interpreter<EncodingT>(m_object->getOne" << UEntity_R2 << "(" << ListEntityIDParam_R2(str_g("native") << UAttribute_R2 << ~-CommaParam_R2) << ")));"
                << line_g(1) << htab_g(2) << "}"
                << line_g(1) << htab_g(1) << "}"
                << line_g(1) << htab_g(1) << "catch (std::exception& e)"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "setError(e);"
                << line_g(1) << htab_g(1) << "}"
				<< line_g(1) << htab_g(1) << "return res;"
				<< line_g(1) << "}"
				<< line_g(2);

			CreateInterpreterAccessSelectOne_R2 =
				str_g("template <class EncodingT>")
				<< line_g(1) << "boost::shared_ptr< Base<EncodingT> > " << UEntity_R2 << "InterpreterAccess<EncodingT>::selectOne" << UEntity_R2 << "(" << CreateIDParam_R2 << CommaParam_R2 << "const boost::shared_ptr< Base<EncodingT> >& nowait)"
				<< line_g(1) << "{"
				<< line_g(1) << htab_g(1) << "boost::shared_ptr< Base<EncodingT> > res(new " << UEntity_R2 << "Interpreter<EncodingT>());"
                << line_g(1) << htab_g(1) << "clearError();"
                << line_g(1) << htab_g(1) << "try"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "bool nativeNoWait;"
                << ListEntityIDParam_R2( line_g(1) << htab_g(2) << AttributeNativeType_R2 << " native" << UAttribute_R2 << ";" )
                << line_g(1) << htab_g(2) << "if ("
                << ListEntityIDParam_R2( ~+(line_g(1) << htab_g(3)) << AttributeCheck_R2( LAttribute_R2, "native" << UAttribute_R2) << " &&" )
                << line_g(1) << htab_g(3) << "check_bool(nowait, nativeNoWait))"
                << line_g(1) << htab_g(2) << "{"
                << line_g(1) << htab_g(3) << "res.reset(new " << UEntity_R2 << "Interpreter<EncodingT>(m_object->selectOne" << UEntity_R2 << "(" << ListEntityIDParam_R2(str_g("native") << UAttribute_R2 << CommaParam_R2) << "nativeNoWait)));"
                << line_g(1) << htab_g(2) << "}"
                << line_g(1) << htab_g(1) << "}"
                << line_g(1) << htab_g(1) << "catch (std::exception& e)"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "setError(e);"
                << line_g(1) << htab_g(1) << "}"
				<< line_g(1) << htab_g(1) << "return res;"
				<< line_g(1) << "}"
				<< line_g(2);

			CreateInterpreterAccessSelectMany_R2 =
				(str_g("template <class EncodingT>")
				<< line_g(1) << "boost::shared_ptr< Base<EncodingT> > " << UEntity_R2 << "InterpreterAccess<EncodingT>::selectMany" << UEntity_R2 << "s(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)"
				<< line_g(1) << "{"
				<< line_g(1) << htab_g(1) << "boost::shared_ptr< Base<EncodingT> > res(new Array<EncodingT>());"
                << line_g(1) << htab_g(1) << "clearError();"
                << line_g(1) << htab_g(1) << "try"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "typename EncodingT::string_t nativeFilter;"
                << line_g(1) << htab_g(2) << "bool nativeNoWait;"
                << line_g(1) << htab_g(2) << "if (check_string<EncodingT>(filter, nativeFilter) &&"
                << line_g(1) << htab_g(3) << "check_bool(nowait, nativeNoWait))"
                << line_g(1) << htab_g(2) << "{"
                << line_g(1) << htab_g(3) << "res = convert_array(m_object->selectMany" << UEntity_R2 << "s(nativeFilter, nativeNoWait));"
                << line_g(1) << htab_g(2) << "}"
                << line_g(1) << htab_g(1) << "}"
                << line_g(1) << htab_g(1) << "catch (std::exception& e)"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "setError(e);"
                << line_g(1) << htab_g(1) << "}"
				<< line_g(1) << htab_g(1) << "return res;"
				<< line_g(1) << "}"
				<< line_g(2))
				[has_g(0, set_g((attr0,attrN), If_IsREF_R2), gt_g())]; 

			CreateInterpreterAccessCancelSelected_R2 =
				str_g("template <class EncodingT>")
				<< line_g(1) << "void " << UEntity_R2 << "InterpreterAccess<EncodingT>::cancelSelection()"
				<< line_g(1) << "{"
                << line_g(1) << htab_g(1) << "clearError();"
                << line_g(1) << htab_g(1) << "try"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "m_object->cancelSelection();"
                << line_g(1) << htab_g(1) << "}"
                << line_g(1) << htab_g(1) << "catch (std::exception& e)"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "setError(e);"
                << line_g(1) << htab_g(1) << "}"
				<< line_g(1) << "}"
				<< line_g(2); 

			CreateInterpreterAccessIsSelected_R2 =
				str_g("template <class EncodingT>")
                << line_g(1) << "boost::shared_ptr< Base<EncodingT> > " << UEntity_R2 << "InterpreterAccess<EncodingT>::isSelected" << UEntity_R2 << "(const boost::shared_ptr< Base<EncodingT> >& " << LEntity_R2 << ")"
				<< line_g(1) << "{"
				<< line_g(1) << htab_g(1) << "boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());"
                << line_g(1) << htab_g(1) << "clearError();"
                << line_g(1) << htab_g(1) << "try"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "boost::shared_ptr< " << EntityClass_R2 << " > native" << UEntity_R2 << ";"
                << line_g(1) << htab_g(2) << "if (check_" << LEntity_R2 << "(" << LEntity_R2 << ", native" << UEntity_R2 << "))"
                << line_g(1) << htab_g(2) << "{"
                << line_g(1) << htab_g(3) << "res.reset(new Bool<EncodingT>(m_object->isSelected" << UEntity_R2 << "(native" << UEntity_R2 << ")));"
                << line_g(1) << htab_g(2) << "}"
                << line_g(1) << htab_g(1) << "}"
                << line_g(1) << htab_g(1) << "catch (std::exception& e)"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "setError(e);"
                << line_g(1) << htab_g(1) << "}"
				<< line_g(1) << htab_g(1) << "return res;"
				<< line_g(1) << "}"
				<< line_g(2); 

			CreateInterpreterAccessFillREF_R2 =
				(str_g("template <class EncodingT>")
				<< line_g(1) << "void " << UEntity_R2 << "InterpreterAccess<EncodingT>::fill" << UAttribute_R2 << "(boost::shared_ptr< Base<EncodingT> >& " << LEntity_R2 << ")"
				<< line_g(1) << "{"
                << line_g(1) << htab_g(1) << "clearError();"
                << line_g(1) << htab_g(1) << "try"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "boost::shared_ptr< " << EntityClass_R2 << " > native" << UEntity_R2 << ";"
                << line_g(1) << htab_g(2) << "if (check_" << LEntity_R2 << "(" << LEntity_R2 << ", native" << UEntity_R2 << "))"
                << line_g(1) << htab_g(2) << "{"
                << line_g(1) << htab_g(3) << "m_object->fill" << UAttribute_R2 << "(native" << UEntity_R2 << ");"
                << line_g(1) << htab_g(3) << "reset_" << LEntity_R2 << "(" << LEntity_R2 << ", native" << UEntity_R2 << ");"
                << line_g(1) << htab_g(2) << "}"
                << line_g(1) << htab_g(1) << "}"
                << line_g(1) << htab_g(1) << "catch (std::exception& e)"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "setError(e);"
                << line_g(1) << htab_g(1) << "}"
				<< line_g(1) << "}"
				<< line_g(2))
				[If_IsREF_R2 && !If_IsID_R2]       
				[attr0, attrN];

			CreateInterpreterAccessFillAllRelation_R2 =
				ListRelationN_R2(
				str_g("template <class EncodingT>")
                << line_g(1) << "void " << URelation1_R2 << "InterpreterAccess<EncodingT>::fillAll" << URelationNName_R2 << "s(boost::shared_ptr< Base<EncodingT> >& " << LRelation1_R2 << ", const boost::shared_ptr< Base<EncodingT> >& nowait)"
				<< line_g(1) << "{"
                << line_g(1) << htab_g(1) << "clearError();"
                << line_g(1) << htab_g(1) << "try"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "bool nativeNoWait;"
                << line_g(1) << htab_g(2) << "boost::shared_ptr< " << Relation1Class_R2 << " > native" << URelation1_R2 << ";"
                << line_g(1) << htab_g(2) << "if (check_" << LRelation1_R2 << "(" << LRelation1_R2 << ", native" << URelation1_R2 << ") && "
                << line_g(1) << htab_g(3) << "check_bool(nowait, nativeNoWait))"
                << line_g(1) << htab_g(2) << "{"
                << line_g(1) << htab_g(3) << "m_object->fillAll" << URelationNName_R2 << "s(native" << URelation1_R2 << ", nativeNoWait);"
                << line_g(1) << htab_g(3) << "reset_" << LRelation1_R2 << "(" << LRelation1_R2 << ", native" << URelation1_R2 << ");"
                << line_g(1) << htab_g(2) << "}"
                << line_g(1) << htab_g(1) << "}"
                << line_g(1) << htab_g(1) << "catch (std::exception& e)"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "setError(e);"
                << line_g(1) << htab_g(1) << "}"
				<< line_g(1) << "}"
				<< line_g(2));

			CreateInterpreterAccessFillOneRelation_R2 =
				ListRelationN_R2(
				str_g("template <class EncodingT>")
                << line_g(1) << "void " << URelation1_R2 << "InterpreterAccess<EncodingT>::fillOne" << URelationNName_R2 << "(boost::shared_ptr< Base<EncodingT> >& ref" << URelation1_R2
				<< ListRelationIDParam_R2(CommaParam_R2 << "const boost::shared_ptr< Base<EncodingT> >& " << LAttribute_R2)
				<< CommaParam_R2 << "const boost::shared_ptr< Base<EncodingT> >& nowait)"
				<< line_g(1) << "{"
                << line_g(1) << htab_g(1) << "clearError();"
                << line_g(1) << htab_g(1) << "try"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "bool nativeNoWait;"
                << line_g(1) << htab_g(2) << "boost::shared_ptr< " << Relation1Class_R2 << " > nativeRef" << URelation1_R2 << ";"
                << ListRelationIDParam_R2(line_g(1) << htab_g(2) << AttributeNativeType_R2 << " native" << UAttribute_R2 << ";")
                << line_g(1) << htab_g(2) << "if (check_" << LRelation1_R2 << "(ref" << URelation1_R2 << ", nativeRef" << URelation1_R2 << ") && "
                << ListRelationIDParam_R2(line_g(1) << htab_g(3) << AttributeCheck_R2( LAttribute_R2, "native" << UAttribute_R2) << " &&")
                << line_g(1) << htab_g(3) << "check_bool(nowait, nativeNoWait))"
                << line_g(1) << htab_g(2) << "{"
                << line_g(1) << htab_g(3) << "m_object->fillOne" << URelationNName_R2 << "(nativeRef" << URelation1_R2 << CommaParam_R2
                << ListRelationIDParam_R2(str_g("native") << UAttribute_R2 << CommaParam_R2)
				<< "nativeNoWait);"
                << line_g(1) << htab_g(3) << "reset_" << LRelation1_R2 << "(ref" << URelation1_R2 << ", nativeRef" << URelation1_R2 << ");"
                << line_g(1) << htab_g(2) << "}"
                << line_g(1) << htab_g(1) << "}"
                << line_g(1) << htab_g(1) << "catch (std::exception& e)"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "setError(e);"
                << line_g(1) << htab_g(1) << "}"
				<< line_g(1) << "}"
				<< line_g(2));


			CreateInterpreterAccessFillManyRelation_R2 =
				ListRelationN_R2(
				str_g("template <class EncodingT>")
                << line_g(1) << "void " << URelation1_R2 << "InterpreterAccess<EncodingT>::fillMany" << URelationNName_R2 << "s(boost::shared_ptr< Base<EncodingT> >& " << LRelation1_R2 << ", const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait)"
				<< line_g(1) << "{"
                << line_g(1) << htab_g(1) << "clearError();"
                << line_g(1) << htab_g(1) << "try"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "bool nativeNoWait;"
                << line_g(1) << htab_g(2) << "typename EncodingT::string_t nativeFilter;"
                << line_g(1) << htab_g(2) << "boost::shared_ptr< " << Relation1Class_R2 << " > native" << URelation1_R2 << ";"
                << line_g(1) << htab_g(2) << "if (check_" << LRelation1_R2 << "(" << LRelation1_R2 << ", native" << URelation1_R2 << ") &&"
                << line_g(1) << htab_g(3) << "check_string<EncodingT>(filter, nativeFilter) &&"
                << line_g(1) << htab_g(3) << "check_bool(nowait, nativeNoWait))"
                << line_g(1) << htab_g(2) << "{"
                << line_g(1) << htab_g(3) << "m_object->fillMany" << URelationNName_R2 << "s(native" << URelation1_R2 << ", nativeFilter, nativeNoWait);"
                << line_g(1) << htab_g(3) << "reset_" << LRelation1_R2 << "(" << LRelation1_R2 << ", native" << URelation1_R2 << ");"
                << line_g(1) << htab_g(2) << "}"
                << line_g(1) << htab_g(1) << "}"
                << line_g(1) << htab_g(1) << "catch (std::exception& e)"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "setError(e);"
                << line_g(1) << htab_g(1) << "}"
				<< line_g(1) << "}"
				<< line_g(2));

			CreateInterpreterAccessIsAltered_R2 =
				(str_g("template <class EncodingT>")
                << line_g(1) << "boost::shared_ptr< Base<EncodingT> > " << UEntity_R2 << "InterpreterAccess<EncodingT>::isModified" << UEntity_R2 << "(const boost::shared_ptr< Base<EncodingT> >& " << LEntity_R2 << ")"
				<< line_g(1) << "{"
				<< line_g(1) << htab_g(1) << "boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>());"
                << line_g(1) << htab_g(1) << "clearError();"
                << line_g(1) << htab_g(1) << "try"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "boost::shared_ptr< " << EntityClass_R2 << " > native" << UEntity_R2 << ";"
                << line_g(1) << htab_g(2) << "if (check_" << LEntity_R2 << "(" << LEntity_R2 << ", native" << UEntity_R2 << "))"
                << line_g(1) << htab_g(2) << "{"
                << line_g(1) << htab_g(3) << "res.reset(new Bool<EncodingT>(m_object->isModified" << UEntity_R2 << "(native" << UEntity_R2 << ")));"
                << line_g(1) << htab_g(2) << "}"
                << line_g(1) << htab_g(1) << "}"
                << line_g(1) << htab_g(1) << "catch (std::exception& e)"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "setError(e);"
                << line_g(1) << htab_g(1) << "}"
				<< line_g(1) << htab_g(1) << "return res;"
				<< line_g(1) << "}"
				<< line_g(2));

			CreateInterpreterAccessUpdate_R2 =
				(str_g("template <class EncodingT>")
				<< line_g(1) << "void " << UEntity_R2 << "InterpreterAccess<EncodingT>::update" << UEntity_R2 << "(boost::shared_ptr< Base<EncodingT> >& " << LEntity_R2 << ")"
				<< line_g(1) << "{"
                << line_g(1) << htab_g(1) << "clearError();"
                << line_g(1) << htab_g(1) << "try"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "boost::shared_ptr< " << EntityClass_R2 << " > native" << UEntity_R2 << ";"
                << line_g(1) << htab_g(2) << "if (check_" << LEntity_R2 << "(" << LEntity_R2 << ", native" << UEntity_R2 << "))"
                << line_g(1) << htab_g(2) << "{"
                << line_g(1) << htab_g(3) << "m_object->update" << UEntity_R2 << "(native" << UEntity_R2 << ");"
                << line_g(1) << htab_g(3) << "reset_" << LEntity_R2 << "(" << LEntity_R2 << ", native" << UEntity_R2 << ");"
                << line_g(1) << htab_g(2) << "}"
                << line_g(1) << htab_g(1) << "}"
                << line_g(1) << htab_g(1) << "catch (std::exception& e)"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "setError(e);"
                << line_g(1) << htab_g(1) << "}"
				<< line_g(1) << "}"
				<< line_g(2));

			CreateInterpreterAccessInsert_R2 =
				(str_g("template <class EncodingT>")
				<< line_g(1) << "void " << UEntity_R2 << "InterpreterAccess<EncodingT>::insert" << UEntity_R2 << "(boost::shared_ptr< Base<EncodingT> >& " << LEntity_R2 << ")"
				<< line_g(1) << "{"
                << line_g(1) << htab_g(1) << "clearError();"
                << line_g(1) << htab_g(1) << "try"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "boost::shared_ptr< " << EntityClass_R2 << " > native" << UEntity_R2 << ";"
                << line_g(1) << htab_g(2) << "if (check_" << LEntity_R2 << "(" << LEntity_R2 << ", native" << UEntity_R2 << "))"
                << line_g(1) << htab_g(2) << "{"
                << line_g(1) << htab_g(3) << "m_object->insert" << UEntity_R2 << "(native" << UEntity_R2 << ");"
                << line_g(1) << htab_g(3) << "reset_" << LEntity_R2 << "(" << LEntity_R2 << ", native" << UEntity_R2 << ");"
                << line_g(1) << htab_g(2) << "}"
                << line_g(1) << htab_g(1) << "}"
                << line_g(1) << htab_g(1) << "catch (std::exception& e)"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "setError(e);"
                << line_g(1) << htab_g(1) << "}"
				<< line_g(1) << "}"
				<< line_g(2));

			CreateInterpreterAccessDelete_R2 =
				(str_g("template <class EncodingT>")
				<< line_g(1) << "void " << UEntity_R2 << "InterpreterAccess<EncodingT>::delete" << UEntity_R2 << "(boost::shared_ptr< Base<EncodingT> >& " << LEntity_R2 << ")"
				<< line_g(1) << "{"
                << line_g(1) << htab_g(1) << "clearError();"
                << line_g(1) << htab_g(1) << "try"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "boost::shared_ptr< " << EntityClass_R2 << " > native" << UEntity_R2 << ";"
                << line_g(1) << htab_g(2) << "if (check_" << LEntity_R2 << "(" << LEntity_R2 << ", native" << UEntity_R2 << "))"
                << line_g(1) << htab_g(2) << "{"
                << line_g(1) << htab_g(3) << "m_object->delete" << UEntity_R2 << "(native" << UEntity_R2 << ");"
                << line_g(1) << htab_g(3) << "reset_" << LEntity_R2 << "(" << LEntity_R2 << ", native" << UEntity_R2 << ");"
                << line_g(1) << htab_g(2) << "}"
                << line_g(1) << htab_g(1) << "}"
                << line_g(1) << htab_g(1) << "catch (std::exception& e)"
                << line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "setError(e);"
                << line_g(1) << htab_g(1) << "}"
				<< line_g(1) << "}"
				<< line_g(2));

            CreateInterpreterAccessSetError_R2 =
                   (str_g("template <class EncodingT>")
                   << line_g(1) << "void " << UEntity_R2 << "InterpreterAccess<EncodingT>::setError(const std::exception& error)"
                   << line_g(1) << "{"
                   << line_g(1) << htab_g(1) << "m_error = true;"
                   << line_g(1) << htab_g(1) << "m_errorText = error.what();"
                   << line_g(1) << "}"
                   << line_g(2));

            CreateInterpreterAccessClearError_R2 =
                   (str_g("template <class EncodingT>")
                   << line_g(1) << "void " << UEntity_R2 << "InterpreterAccess<EncodingT>::clearError()"
                   << line_g(1) << "{"
                   << line_g(1) << htab_g(1) << "m_error = false;"
                   << line_g(1) << htab_g(1) << "m_errorText.clear();"
                   << line_g(1) << "}"
                   << line_g(2));

            CreateInterpreterAccessGetError_R2 =
                   (str_g("template <class EncodingT>")
                   << line_g(1) << "boost::shared_ptr< Base<EncodingT> > " << UEntity_R2 << "InterpreterAccess<EncodingT>::getError(boost::shared_ptr< Base<EncodingT> >& text) const"
                   << line_g(1) << "{"
                   << line_g(1) << htab_g(1) << "boost::shared_ptr< String<EncodingT> > str  = dynamic_pointer_cast< String<EncodingT> >(text);"
                   << line_g(1) << htab_g(1) << "if (str)"
                   << line_g(1) << htab_g(1) << "{"
                   << line_g(1) << htab_g(2) << "str->value(C(m_errorText));"
                   << line_g(1) << htab_g(1) << "}"
                   << line_g(1) << htab_g(1) << "return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(m_error));"
                   << line_g(1) << "}"
                   << line_g(2));
		}
	}
}
