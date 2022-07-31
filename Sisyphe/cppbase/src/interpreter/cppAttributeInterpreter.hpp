/* 
 * cppAttributeInterpreter.hpp
 *
 *
 * @date 31-07-2022
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPATTRIBUTE_INTERPRETER_HPP_
#define _CPPATTRIBUTE_INTERPRETER_HPP_

#include "config.hpp"
#include "Macros.hpp"
#include "Base.hpp"
#include "Array.hpp"

#include "cppBaseExport.hpp"
#include "cppBaseData.h"
#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

using namespace log4cpp;
using namespace fctr;
using namespace enc;
using namespace entity;
using namespace boost;

template <class EncodingT>
class CppClassInterpreter;

template <class EncodingT>
class CppAttributeInterpreter
: public Base<EncodingT>
{
private:
	boost::shared_ptr< _CppAttribute<EncodingT> > m_value;

public:
	CppAttributeInterpreter();

	CppAttributeInterpreter(boost::shared_ptr< _CppAttribute<EncodingT> > const& value);

	FACTORY_PROTOTYPE10(CppAttributeInterpreter,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	CppAttributeInterpreter(boost::shared_ptr< Base<EncodingT> > const& attrType,
				boost::shared_ptr< Base<EncodingT> > const& name,
				boost::shared_ptr< Base<EncodingT> > const& accessSpecifier,
				boost::shared_ptr< Base<EncodingT> > const& isStatic,
				boost::shared_ptr< Base<EncodingT> > const& isConst,
				boost::shared_ptr< Base<EncodingT> > const& isConstexpr,
				boost::shared_ptr< Base<EncodingT> > const& constValue,
				boost::shared_ptr< Base<EncodingT> > const& lineNumber,
				boost::shared_ptr< Base<EncodingT> > const& startBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthBlock);

	boost::shared_ptr< _CppAttribute<EncodingT> > value() const;

	void value(boost::shared_ptr< _CppAttribute<EncodingT> > const& value);

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getIdentifier() const;

	boost::shared_ptr< Base<EncodingT> > getAttrType() const;

	boost::shared_ptr< Base<EncodingT> > getName() const;

	boost::shared_ptr< Base<EncodingT> > getAccessSpecifier() const;

	boost::shared_ptr< Base<EncodingT> > getIsStatic() const;

	boost::shared_ptr< Base<EncodingT> > getIsConst() const;

	boost::shared_ptr< Base<EncodingT> > getIsConstexpr() const;

	boost::shared_ptr< Base<EncodingT> > getConstValue() const;

	boost::shared_ptr< Base<EncodingT> > getLineNumber() const;

	boost::shared_ptr< Base<EncodingT> > getStartBlock() const;

	boost::shared_ptr< Base<EncodingT> > getLengthBlock() const;

	boost::shared_ptr< Base<EncodingT> > getCppClass();

	FACTORY_PROTOTYPE1(setAttrType, In< boost::shared_ptr< Base<EncodingT> > >)
	void setAttrType(boost::shared_ptr< Base<EncodingT> > const& attrType);

	FACTORY_PROTOTYPE1(setName, In< boost::shared_ptr< Base<EncodingT> > >)
	void setName(boost::shared_ptr< Base<EncodingT> > const& name);

	FACTORY_PROTOTYPE1(setAccessSpecifier, In< boost::shared_ptr< Base<EncodingT> > >)
	void setAccessSpecifier(boost::shared_ptr< Base<EncodingT> > const& accessSpecifier);

	FACTORY_PROTOTYPE1(setIsStatic, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsStatic(boost::shared_ptr< Base<EncodingT> > const& isStatic);

	FACTORY_PROTOTYPE1(setIsConst, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsConst(boost::shared_ptr< Base<EncodingT> > const& isConst);

	FACTORY_PROTOTYPE1(setIsConstexpr, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsConstexpr(boost::shared_ptr< Base<EncodingT> > const& isConstexpr);

	FACTORY_PROTOTYPE1(setConstValue, In< boost::shared_ptr< Base<EncodingT> > >)
	void setConstValue(boost::shared_ptr< Base<EncodingT> > const& constValue);

	FACTORY_PROTOTYPE1(setCppClass, In< boost::shared_ptr< Base<EncodingT> > >)
	void setCppClass(boost::shared_ptr< Base<EncodingT> > const& cppClass);

	FACTORY_PROTOTYPE1(setLineNumber, In< boost::shared_ptr< Base<EncodingT> > >)
	void setLineNumber(boost::shared_ptr< Base<EncodingT> > const& lineNumber);

	FACTORY_PROTOTYPE1(setStartBlock, In< boost::shared_ptr< Base<EncodingT> > >)
	void setStartBlock(boost::shared_ptr< Base<EncodingT> > const& startBlock);

	FACTORY_PROTOTYPE1(setLengthBlock, In< boost::shared_ptr< Base<EncodingT> > >)
	void setLengthBlock(boost::shared_ptr< Base<EncodingT> > const& lengthBlock);

	boost::shared_ptr< Base<EncodingT> > hasCppClass() const;

	void removeCppClass();

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( CppAttributeInterpreter, UCS("CppAttribute") );
		CLASS_KEY_REGISTER10( CppAttributeInterpreter, UCS("CppAttribute") );
		METHOD_KEY_REGISTER ( CppAttributeInterpreter, boost::shared_ptr< Base<EncodingT> >, getIdentifier, const_t, UCS("CppAttribute::Identifier") );
		METHOD_KEY_REGISTER ( CppAttributeInterpreter, boost::shared_ptr< Base<EncodingT> >, getAttrType, const_t, UCS("CppAttribute::AttrType") );
		METHOD_KEY_REGISTER1( CppAttributeInterpreter, void, setAttrType, no_const_t, UCS("CppAttribute::AttrType") );
		METHOD_KEY_REGISTER ( CppAttributeInterpreter, boost::shared_ptr< Base<EncodingT> >, getName, const_t, UCS("CppAttribute::Name") );
		METHOD_KEY_REGISTER1( CppAttributeInterpreter, void, setName, no_const_t, UCS("CppAttribute::Name") );
		METHOD_KEY_REGISTER ( CppAttributeInterpreter, boost::shared_ptr< Base<EncodingT> >, getAccessSpecifier, const_t, UCS("CppAttribute::AccessSpecifier") );
		METHOD_KEY_REGISTER1( CppAttributeInterpreter, void, setAccessSpecifier, no_const_t, UCS("CppAttribute::AccessSpecifier") );
		METHOD_KEY_REGISTER ( CppAttributeInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsStatic, const_t, UCS("CppAttribute::IsStatic") );
		METHOD_KEY_REGISTER1( CppAttributeInterpreter, void, setIsStatic, no_const_t, UCS("CppAttribute::IsStatic") );
		METHOD_KEY_REGISTER ( CppAttributeInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsConst, const_t, UCS("CppAttribute::IsConst") );
		METHOD_KEY_REGISTER1( CppAttributeInterpreter, void, setIsConst, no_const_t, UCS("CppAttribute::IsConst") );
		METHOD_KEY_REGISTER ( CppAttributeInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsConstexpr, const_t, UCS("CppAttribute::IsConstexpr") );
		METHOD_KEY_REGISTER1( CppAttributeInterpreter, void, setIsConstexpr, no_const_t, UCS("CppAttribute::IsConstexpr") );
		METHOD_KEY_REGISTER ( CppAttributeInterpreter, boost::shared_ptr< Base<EncodingT> >, getConstValue, const_t, UCS("CppAttribute::ConstValue") );
		METHOD_KEY_REGISTER1( CppAttributeInterpreter, void, setConstValue, no_const_t, UCS("CppAttribute::ConstValue") );
		METHOD_KEY_REGISTER1( CppAttributeInterpreter, void, setCppClass, no_const_t, UCS("CppAttribute::CppClass") );
		METHOD_KEY_REGISTER ( CppAttributeInterpreter, boost::shared_ptr< Base<EncodingT> >, getCppClass, no_const_t, UCS("CppAttribute::CppClass") );
		METHOD_KEY_REGISTER ( CppAttributeInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCppClass, const_t, UCS("CppAttribute::HasCppClass") );
		METHOD_KEY_REGISTER ( CppAttributeInterpreter, void, removeCppClass, no_const_t, UCS("CppAttribute::removeCppClass") );
		METHOD_KEY_REGISTER ( CppAttributeInterpreter, boost::shared_ptr< Base<EncodingT> >, getLineNumber, const_t, UCS("CppAttribute::LineNumber") );
		METHOD_KEY_REGISTER1( CppAttributeInterpreter, void, setLineNumber, no_const_t, UCS("CppAttribute::LineNumber") );
		METHOD_KEY_REGISTER ( CppAttributeInterpreter, boost::shared_ptr< Base<EncodingT> >, getStartBlock, const_t, UCS("CppAttribute::StartBlock") );
		METHOD_KEY_REGISTER1( CppAttributeInterpreter, void, setStartBlock, no_const_t, UCS("CppAttribute::StartBlock") );
		METHOD_KEY_REGISTER ( CppAttributeInterpreter, boost::shared_ptr< Base<EncodingT> >, getLengthBlock, const_t, UCS("CppAttribute::LengthBlock") );
		METHOD_KEY_REGISTER1( CppAttributeInterpreter, void, setLengthBlock, no_const_t, UCS("CppAttribute::LengthBlock") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( UCS("CppAttribute") );
		CLASS_KEY_UNREGISTER10( UCS("CppAttribute") );
		METHOD_KEY_UNREGISTER ( UCS("CppAttribute::Identifier") );
		METHOD_KEY_UNREGISTER ( UCS("CppAttribute::AttrType") );
		METHOD_KEY_UNREGISTER1( UCS("CppAttribute::AttrType") );
		METHOD_KEY_UNREGISTER ( UCS("CppAttribute::Name") );
		METHOD_KEY_UNREGISTER1( UCS("CppAttribute::Name") );
		METHOD_KEY_UNREGISTER ( UCS("CppAttribute::AccessSpecifier") );
		METHOD_KEY_UNREGISTER1( UCS("CppAttribute::AccessSpecifier") );
		METHOD_KEY_UNREGISTER ( UCS("CppAttribute::IsStatic") );
		METHOD_KEY_UNREGISTER1( UCS("CppAttribute::IsStatic") );
		METHOD_KEY_UNREGISTER ( UCS("CppAttribute::IsConst") );
		METHOD_KEY_UNREGISTER1( UCS("CppAttribute::IsConst") );
		METHOD_KEY_UNREGISTER ( UCS("CppAttribute::IsConstexpr") );
		METHOD_KEY_UNREGISTER1( UCS("CppAttribute::IsConstexpr") );
		METHOD_KEY_UNREGISTER ( UCS("CppAttribute::ConstValue") );
		METHOD_KEY_UNREGISTER1( UCS("CppAttribute::ConstValue") );
		METHOD_KEY_UNREGISTER ( UCS("CppAttribute::CppClass") );
		METHOD_KEY_UNREGISTER1( UCS("CppAttribute::CppClass") );
		METHOD_KEY_UNREGISTER ( UCS("CppAttribute::HasCppClass") );
		METHOD_KEY_UNREGISTER ( UCS("CppAttribute::removeCppClass") );
		METHOD_KEY_UNREGISTER ( UCS("CppAttribute::LineNumber") );
		METHOD_KEY_UNREGISTER1( UCS("CppAttribute::LineNumber") );
		METHOD_KEY_UNREGISTER ( UCS("CppAttribute::StartBlock") );
		METHOD_KEY_UNREGISTER1( UCS("CppAttribute::StartBlock") );
		METHOD_KEY_UNREGISTER ( UCS("CppAttribute::LengthBlock") );
		METHOD_KEY_UNREGISTER1( UCS("CppAttribute::LengthBlock") );
	FACTORY_END_UNREGISTER
};

template <class EncodingT>
bool check_cppAttribute(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _CppAttribute<EncodingT> >& o);

template <class EncodingT>
bool reset_cppAttribute(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _CppAttribute<EncodingT> > const& o);

NAMESPACE_END

#undef C
#undef A

#include "cppAttributeInterpreter_impl.hpp"

#endif
