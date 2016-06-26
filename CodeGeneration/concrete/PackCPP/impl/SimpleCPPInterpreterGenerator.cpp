#include "SimpleCPPInterpreterGenerator.hpp"

namespace dsg {

	namespace generator {

		SimpleCPPInterpreterGenerator::SimpleCPPInterpreterGenerator()
		{
			SourceCPP_R2 = 
				CreateFile_R2;

			CreateFile_R2 =
                CreateMacro_R2
                << CreateNamespace_R2(str_g("interp"))
				<< ( CreateInterpretEntity_R2
				<<   CreateCheckFunction_R2
				<<   CreateResetFunction_R2) [ent0, entN]
                << CreateEndNamespace_R2
                << CreateEndMacro_R2;

			CreateInterpretEntity_R2 =
				CreateInterpreterEntityConstructor_R2
				<< CreateInterpreterEntityConstructor2_R2
				<< CreateInterpreterEntityConstructor3_R2
				<< CreateInterpreterEntityDestructor_R2
				<< CreateInterpreterEntityGetValue_R2
				<< CreateInterpreterEntitySetValue_R2
				<< CreateInterpreterEntityAttributeGetter_R2
                << CreateInterpreterEntityAttributeRefGetter_R2
				<< CreateInterpreterEntityAttributeSetter_R2
				<< CreateInterpreterEntityAttributeIsNull_R2
				<< CreateInterpreterEntityAttributeErase_R2
				<< CreateInterpreterEntityAttributeListErase_R2
				<< CreateInterpreterEntityAttributeListInsert_R2
				<< CreateInterpreterEntityAttributeListAt_R2
				<< CreateInterpreterEntityAttributeListClear_R2
				<< CreateInterpreterEntityAttributeListEmpty_R2
				<< CreateInterpreterEntityAttributeListSize_R2
				<< CreateInterpreterEntityToString_R2
				<< CreateInterpreterEntityClone_R2
				<< CreateInterpreterEntityGetClassName_R2
				<< CreateInterpreterEntityInvoke_R2;

			CreateInterpreterEntityConstructor_R2 =
				str_g("template <class EncodingT>")
				<< line_g(1) << UEntity_R2 << "Interpreter<EncodingT>::" << UEntity_R2 << "Interpreter()"
				<< line_g(1) << "{"
				<< line_g(1) << htab_g(1) << "setValue( shared_ptr< " << EntityClass_R2 << " > (new " << EntityClass_R2 << "()) );"
				<< line_g(1) << "}"
				<< line_g(2);

			CreateInterpreterEntityConstructor2_R2 =
				str_g("template <class EncodingT>")
				<< line_g(1) << UEntity_R2 << "Interpreter<EncodingT>::" << UEntity_R2 << "Interpreter(shared_ptr< " << EntityClass_R2 << " > const& value)"
				<< line_g(1) << "{"
				<< line_g(1) << htab_g(1) << "setValue(value);"
				<< line_g(1) << "}"
				<< line_g(2);

			CreateInterpreterEntityConstructor3_R2 =
				str_g("template <class EncodingT>")
				<< line_g(1) << UEntity_R2 << "Interpreter<EncodingT>::" << UEntity_R2 << "Interpreter(" << CreateConstructorParam_R2 << ")"
				<< line_g(1) << "{"
				<< ListEntityParam_R2( line_g(1) << htab_g(1) << AttributeNativeType_R2 << " native" << UAttribute_R2 << ";" )
				<< line_g(1) << htab_g(1) << "if ("
				<< ListEntityParam_R2( ~+(line_g(1) << htab_g(2)) << AttributeCheck_R2( LAttribute_R2, "native" << UAttribute_R2) << ~-str_g(" &&") ) << ")"
				<< line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "setValue(shared_ptr< " << EntityClass_R2 << " >(new " << EntityClass_R2 << "(" << ListEntityParam_R2(str_g("native") << UAttribute_R2 << ~-CommaParam_R2) << ")));"
				<< line_g(1) << htab_g(1) << "}"
				<< line_g(1) << "}"
				<< line_g(2);

			CreateInterpreterEntityDestructor_R2 =
				str_g("template <class EncodingT>")
				<< line_g(1) << UEntity_R2 << "Interpreter<EncodingT>::~" << UEntity_R2 << "Interpreter()"
				<< line_g(1) << "{}"
				<< line_g(2);

			CreateInterpreterEntityGetValue_R2 = 
				str_g("template <class EncodingT>")
				<< line_g(1) << "shared_ptr< " << EntityClass_R2 << " > " << UEntity_R2 << "Interpreter<EncodingT>::getValue() const"
				<< line_g(1) << "{"
				<< line_g(1) << htab_g(1) << "return m_value;"
				<< line_g(1) << "}"
				<< line_g(2);

			CreateInterpreterEntitySetValue_R2 = 
				str_g("template <class EncodingT>")
				<< line_g(1) << "void " << UEntity_R2 << "Interpreter<EncodingT>::setValue(shared_ptr< " << EntityClass_R2 << " > const& object)"
				<< line_g(1) << "{"
				<< line_g(1) << htab_g(1) << "m_value = object;"
				<< line_g(1) << htab_g(1) << "String<EncodingT>::setValue(toString());"
				<< line_g(1) << "}"
				<< line_g(2);

			CreateInterpreterEntityToString_R2 = 
				str_g("template <class EncodingT>")
				<< line_g(1) << "typename EncodingT::string_t " << UEntity_R2 << "Interpreter<EncodingT>::toString() const"
				<< line_g(1) << "{"
				<< line_g(1) << htab_g(1) << "std::stringstream stream;"
				<< line_g(1) << htab_g(1) << "stream << *(getValue());"
				<< line_g(1) << htab_g(1) << "return C(stream.str());"
				<< line_g(1) << "}"
				<< line_g(2);

			CreateInterpreterEntityClone_R2 = 
				str_g("template <class EncodingT>")
				<< line_g(1) << "shared_ptr< Base<EncodingT> > " << UEntity_R2 << "Interpreter<EncodingT>::clone() const"
				<< line_g(1) << "{"
				<< line_g(1) << htab_g(1) << "return shared_ptr< Base<EncodingT> >(new " << UEntity_R2 << "Interpreter<EncodingT>(copy_ptr(getValue())));"
				<< line_g(1) << "}"
				<< line_g(2);

			CreateInterpreterEntityGetClassName_R2 = 
				str_g("template <class EncodingT>")
				<< line_g(1) << "typename EncodingT::string_t " << UEntity_R2 << "Interpreter<EncodingT>::getClassName() const"
				<< line_g(1) << "{"
				<< line_g(1) << htab_g(1) << "return C(\"" << UEntity_R2 << "\");"
				<< line_g(1) << "}"
				<< line_g(2); 

			CreateInterpreterEntityInvoke_R2 = 
				str_g("template <class EncodingT>")
                << line_g(1) << "shared_ptr< Base<EncodingT> > " << UEntity_R2 << "Interpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)"
				<< line_g(1) << "{"
				<< line_g(1) << htab_g(1) << "shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());"
				<< line_g(1)    
				<< line_g(1) << htab_g(1) << "ParameterArray args, ret;"
				<< line_g(1) << htab_g(1) << "if (check_parameters_array(params, args))"
				<< line_g(1) << htab_g(1) << "{"
				<< line_g(1) << htab_g(2) << "if (tryInvoke(this, C(\"" << UEntity_R2 << "\"), method, args, ret) ||"
				<< line_g(1) << htab_g(3) << "tryInvoke(this, C(\"String\"), method, args, ret))"
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
				<< line_g(1) << htab_g(3) << "logger->errorStream() << \"Unexpected call in " << UEntity_R2 << ", no method \\\"\" << A(method) << \"\\\" exists.\";"
				<< line_g(1) << htab_g(2) << "}"
				<< line_g(1) << htab_g(1) << "}"
				<< line_g(1) << htab_g(1) << "return obj;"
				<< line_g(1) << "}"
				<< line_g(2);

			CreateCheckFunction_R2 =
				str_g("template <class EncodingT>")
				<< line_g(1) << "bool check_" << LEntity_R2 << "(shared_ptr< Base<EncodingT> > const& val, shared_ptr< " << EntityClass_R2 << " >& o)"
				<< line_g(1) << "{"
				<< line_g(1) << htab_g(1) << "shared_ptr< " << UEntity_R2 << "Interpreter<EncodingT> > value  = dynamic_pointer_cast< " << UEntity_R2 << "Interpreter<EncodingT> >(val);"       
				<< line_g(1) << htab_g(1) << "if (value)"
				<< line_g(1) << htab_g(1) << "{"
				<< line_g(1) << htab_g(2) << "o = value->getValue();"
				<< line_g(1) << htab_g(1) << "}"
				<< line_g(1) << htab_g(1) << "else"
				<< line_g(1) << htab_g(1) << "{"
				<< line_g(1) << htab_g(2) << "Category* logger = &Category::getInstance(LOGNAME);"
				<< line_g(1) << htab_g(2) << "logger->errorStream() << \"" << UEntity_R2 << " expected, got \" << A(val->getClassName());"            
				<< line_g(1) << htab_g(1) << "}"
				<< line_g(1) << htab_g(1) << "return value;"
				<< line_g(1) << "}"
				<< line_g(2);

			CreateResetFunction_R2 =
				str_g("template <class EncodingT>")
				<< line_g(1) << "bool reset_" << LEntity_R2 << "(shared_ptr< Base<EncodingT> >& val, shared_ptr< " << EntityClass_R2 << " > const& o)"
				<< line_g(1) << "{"
				<< line_g(1) << htab_g(1) << "shared_ptr< " << UEntity_R2 << "Interpreter<EncodingT> > value  = dynamic_pointer_cast< " << UEntity_R2 << "Interpreter<EncodingT> >(val);"       
				<< line_g(1) << htab_g(1) << "if (value)"
				<< line_g(1) << htab_g(1) << "{"
				<< line_g(1) << htab_g(2) << "value->setValue(o);"
				<< line_g(1) << htab_g(1) << "}"
				<< line_g(1) << htab_g(1) << "else"
				<< line_g(1) << htab_g(1) << "{"
				<< line_g(1) << htab_g(2) << "Category* logger = &Category::getInstance(LOGNAME);"
				<< line_g(1) << htab_g(2) << "logger->errorStream() << \"" << UEntity_R2 << " expected, got \" << A(val->getClassName());"            
				<< line_g(1) << htab_g(1) << "}"
				<< line_g(1) << htab_g(1) << "return value;"
				<< line_g(1) << "}"
				<< line_g(2);

			CreateInterpreterEntityAttributeGetter_R2 =
				(line_g(1) << "template <class EncodingT>"
				<< line_g(1) << "shared_ptr< Base<EncodingT> > " << UEntity_R2 << "Interpreter<EncodingT>::get" << UAttribute_R2 << "() const"
				<< line_g(1) << "{"
				<< line_g(1) << htab_g(1) << "return " << AttributeInterpreterType_R2("getValue()->get" << UAttribute_R2 << "()") << ";"
				<< line_g(1) << "}"
				<< line_g(2))[!If_IsREF_R2][attr0, attrN];

			CreateInterpreterEntityAttributeRefGetter_R2 =
				(line_g(1) << "template <class EncodingT>"
				<< line_g(1) << "shared_ptr< Base<EncodingT> > " << UEntity_R2 << "Interpreter<EncodingT>::get" << UAttribute_R2 << "()"
				<< line_g(1) << "{"
				<< line_g(1) << htab_g(1) << "return " << AttributeInterpreterType_R2("getValue()->get" << UAttribute_R2 << "()") << ";"
				<< line_g(1) << "}"
				<< line_g(2))[If_IsREF_R2][attr0, attrN];

			CreateInterpreterEntityAttributeSetter_R2 =
				(line_g(1) << "template <class EncodingT>"
				<< line_g(1) << "void " << UEntity_R2 << "Interpreter<EncodingT>::set" << UAttribute_R2 << "(shared_ptr< Base<EncodingT> > const& " << LAttribute_R2 << ")"
				<< line_g(1) << "{"
				<< line_g(1) << htab_g(1) << AttributeNativeType_R2 << " native" << UAttribute_R2 << ";"
				<< line_g(1) << htab_g(1) << "if (" << AttributeCheck_R2( LAttribute_R2, "native" << UAttribute_R2) << ")"
				<< line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "getValue()->set" << UAttribute_R2 << "(" << "native" << UAttribute_R2 << ");"
				<< line_g(1) << htab_g(1) << "}"
				<< line_g(1) << "}"
				<< line_g(2))[If_IsWriteAttribute_R2][attr0, attrN];

			CreateInterpreterEntityAttributeIsNull_R2 =
				(line_g(1) << "template <class EncodingT>"
				<< line_g(1) << "shared_ptr< Base<EncodingT> > " << UEntity_R2 << "Interpreter<EncodingT>::has" << UAttribute_R2 << "() const"
				<< line_g(1) << "{"
				<< line_g(1) << htab_g(1) << "return shared_ptr< Base<EncodingT> >( new Bool<EncodingT>(!getValue()->isNull" << UAttribute_R2 << "()) );"
				<< line_g(1) << "}"
				<< line_g(2))[If_IsREF_R2][attr0, attrN];

			CreateInterpreterEntityAttributeErase_R2 =
				(line_g(1) << "template <class EncodingT>"
				<< line_g(1) << "void " << UEntity_R2 << "Interpreter<EncodingT>::remove" << UAttribute_R2 << "()"
				<< line_g(1) << "{"
				<< line_g(1) << htab_g(1) << "getValue()->erase" << UAttribute_R2 << "();"
				<< line_g(1) << "}"
				<< line_g(2))[If_IsREF_R2][attr0, attrN];

			CreateInterpreterEntityAttributeListErase_R2 =
				ListRelationN_R2(line_g(1) << "template <class EncodingT>"
                << line_g(1) << "void " << URelation1_R2 << "Interpreter<EncodingT>::remove" << URelationNName_R2 << "(shared_ptr< Base<EncodingT> > const& n)"
				<< line_g(1) << "{"
                << line_g(1) << htab_g(1) << "int nativePosition;"
				<< line_g(1) << htab_g(1) << "if (check_numeric(n, nativePosition))"
				<< line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "getValue()->erase" << URelationNName_R2 << "(getValue()->get" << URelationNName_R2 << "sBeginning()+nativePosition);"
				<< line_g(1) << htab_g(1) << "}"
				<< line_g(1) << "}"
				<< line_g(2));

			CreateInterpreterEntityAttributeListInsert_R2 =
				ListRelationN_R2(line_g(1) << "template <class EncodingT>"
                << line_g(1) << "void " << URelation1_R2 << "Interpreter<EncodingT>::insert" << URelationNName_R2 << "(shared_ptr< Base<EncodingT> > const& n, shared_ptr< Base<EncodingT> > const& " << LRelationNName_R2 << ")"
				<< line_g(1) << "{"
                << line_g(1) << htab_g(1) << "int nativePosition;"
                << line_g(1) << htab_g(1) << "shared_ptr< _" << URelationN_R2 << "<EncodingT> > native" << URelationNName_R2 << ";"
				<< line_g(1) << htab_g(1) << "if (check_numeric(n, nativePosition) &&"
                << line_g(1) << htab_g(2) << "check_" << LRelationN_R2 << "(" << LRelationNName_R2 << ", native" << URelationNName_R2 << "))"
				<< line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "getValue()->insert" << URelationNName_R2 << "(getValue()->get" << URelationNName_R2 << "sBeginning()+nativePosition, native" << URelationNName_R2 << ");"
				<< line_g(1) << htab_g(1) << "}"
				<< line_g(1) << "}"
				<< line_g(2));

			CreateInterpreterEntityAttributeListAt_R2 =
				ListRelationN_R2(line_g(1) << "template <class EncodingT>"
                << line_g(1) << "shared_ptr< Base<EncodingT> > " << URelation1_R2 << "Interpreter<EncodingT>::get" << URelationNName_R2 << "(shared_ptr< Base<EncodingT> > const& n)"
				<< line_g(1) << "{"
                << line_g(1) << htab_g(1) << "shared_ptr< Base<EncodingT> > res(new " << URelationN_R2 << "Interpreter<EncodingT>());"
                << line_g(1) << htab_g(1) << "int nativePosition;"
				<< line_g(1) << htab_g(1) << "if (check_numeric(n, nativePosition))"
				<< line_g(1) << htab_g(1) << "{"
                << line_g(1) << htab_g(2) << "res.reset(new " << URelationN_R2 << "Interpreter<EncodingT>(getValue()->get" << URelationNName_R2 << "At(nativePosition)));"
				<< line_g(1) << htab_g(1) << "}"
				<< line_g(1) << htab_g(1) << "return res;"
				<< line_g(1) << "}"
				<< line_g(2));

			CreateInterpreterEntityAttributeListClear_R2 =
				ListRelationN_R2(line_g(1) << "template <class EncodingT>"
                << line_g(1) << "void " << URelation1_R2 << "Interpreter<EncodingT>::clear" << URelationNName_R2 << "s()"
				<< line_g(1) << "{"
                << line_g(1) << htab_g(1) << "getValue()->clear" << URelationNName_R2 << "s();"
				<< line_g(1) << "}"
				<< line_g(2));

			CreateInterpreterEntityAttributeListEmpty_R2 =
				ListRelationN_R2(line_g(1) << "template <class EncodingT>"
                << line_g(1) << "shared_ptr< Base<EncodingT> > " << URelation1_R2 << "Interpreter<EncodingT>::has" << URelationNName_R2 << "s() const"
				<< line_g(1) << "{"
                << line_g(1) << htab_g(1) << "return shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(!getValue()->is" << URelationNName_R2 << "sEmpty()));"
				<< line_g(1) << "}"
				<< line_g(2));

			CreateInterpreterEntityAttributeListSize_R2 =
				ListRelationN_R2(line_g(1) << "template <class EncodingT>"
                << line_g(1) << "shared_ptr< Base<EncodingT> > " << URelation1_R2 << "Interpreter<EncodingT>::" << LRelationNName_R2 << "sCount() const"
				<< line_g(1) << "{"
                << line_g(1) << htab_g(1) << "return shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(getValue()->get" << URelationNName_R2 << "sSize()));"
				<< line_g(1) << "}"
				<< line_g(2));

		}
    }
}


