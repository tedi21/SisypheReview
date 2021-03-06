/* 
 * cppEnumConstantInterpreter.hpp
 *
 *
 * @date 14-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPENUMCONSTANT_INTERPRETER_HPP_
#define _CPPENUMCONSTANT_INTERPRETER_HPP_

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
class CppEnumInterpreter;

template <class EncodingT>
class CppEnumConstantInterpreter
: public Base<EncodingT>
{
private:
	boost::shared_ptr< _CppEnumConstant<EncodingT> > m_value;

public:
	CppEnumConstantInterpreter();

	CppEnumConstantInterpreter(boost::shared_ptr< _CppEnumConstant<EncodingT> > const& value);

	FACTORY_PROTOTYPE5(CppEnumConstantInterpreter,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	CppEnumConstantInterpreter(boost::shared_ptr< Base<EncodingT> > const& name,
				boost::shared_ptr< Base<EncodingT> > const& defaultValue,
				boost::shared_ptr< Base<EncodingT> > const& lineNumber,
				boost::shared_ptr< Base<EncodingT> > const& startBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthBlock);

	boost::shared_ptr< _CppEnumConstant<EncodingT> > value() const;

	void value(boost::shared_ptr< _CppEnumConstant<EncodingT> > const& value);

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getIdentifier() const;

	boost::shared_ptr< Base<EncodingT> > getName() const;

	boost::shared_ptr< Base<EncodingT> > getDefaultValue() const;

	boost::shared_ptr< Base<EncodingT> > getLineNumber() const;

	boost::shared_ptr< Base<EncodingT> > getStartBlock() const;

	boost::shared_ptr< Base<EncodingT> > getLengthBlock() const;

	boost::shared_ptr< Base<EncodingT> > getCppEnum();

	FACTORY_PROTOTYPE1(setName, In< boost::shared_ptr< Base<EncodingT> > >)
	void setName(boost::shared_ptr< Base<EncodingT> > const& name);

	FACTORY_PROTOTYPE1(setDefaultValue, In< boost::shared_ptr< Base<EncodingT> > >)
	void setDefaultValue(boost::shared_ptr< Base<EncodingT> > const& defaultValue);

	FACTORY_PROTOTYPE1(setCppEnum, In< boost::shared_ptr< Base<EncodingT> > >)
	void setCppEnum(boost::shared_ptr< Base<EncodingT> > const& cppEnum);

	FACTORY_PROTOTYPE1(setLineNumber, In< boost::shared_ptr< Base<EncodingT> > >)
	void setLineNumber(boost::shared_ptr< Base<EncodingT> > const& lineNumber);

	FACTORY_PROTOTYPE1(setStartBlock, In< boost::shared_ptr< Base<EncodingT> > >)
	void setStartBlock(boost::shared_ptr< Base<EncodingT> > const& startBlock);

	FACTORY_PROTOTYPE1(setLengthBlock, In< boost::shared_ptr< Base<EncodingT> > >)
	void setLengthBlock(boost::shared_ptr< Base<EncodingT> > const& lengthBlock);

	boost::shared_ptr< Base<EncodingT> > hasCppEnum() const;

	void removeCppEnum();

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( CppEnumConstantInterpreter, UCS("CppEnumConstant") );
		CLASS_KEY_REGISTER5( CppEnumConstantInterpreter, UCS("CppEnumConstant") );
		METHOD_KEY_REGISTER ( CppEnumConstantInterpreter, boost::shared_ptr< Base<EncodingT> >, getIdentifier, const_t, UCS("CppEnumConstant::Identifier") );
		METHOD_KEY_REGISTER ( CppEnumConstantInterpreter, boost::shared_ptr< Base<EncodingT> >, getName, const_t, UCS("CppEnumConstant::Name") );
		METHOD_KEY_REGISTER1( CppEnumConstantInterpreter, void, setName, no_const_t, UCS("CppEnumConstant::Name") );
		METHOD_KEY_REGISTER ( CppEnumConstantInterpreter, boost::shared_ptr< Base<EncodingT> >, getDefaultValue, const_t, UCS("CppEnumConstant::DefaultValue") );
		METHOD_KEY_REGISTER1( CppEnumConstantInterpreter, void, setDefaultValue, no_const_t, UCS("CppEnumConstant::DefaultValue") );
		METHOD_KEY_REGISTER1( CppEnumConstantInterpreter, void, setCppEnum, no_const_t, UCS("CppEnumConstant::CppEnum") );
		METHOD_KEY_REGISTER ( CppEnumConstantInterpreter, boost::shared_ptr< Base<EncodingT> >, getCppEnum, no_const_t, UCS("CppEnumConstant::CppEnum") );
		METHOD_KEY_REGISTER ( CppEnumConstantInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCppEnum, const_t, UCS("CppEnumConstant::HasCppEnum") );
		METHOD_KEY_REGISTER ( CppEnumConstantInterpreter, void, removeCppEnum, no_const_t, UCS("CppEnumConstant::removeCppEnum") );
		METHOD_KEY_REGISTER ( CppEnumConstantInterpreter, boost::shared_ptr< Base<EncodingT> >, getLineNumber, const_t, UCS("CppEnumConstant::LineNumber") );
		METHOD_KEY_REGISTER1( CppEnumConstantInterpreter, void, setLineNumber, no_const_t, UCS("CppEnumConstant::LineNumber") );
		METHOD_KEY_REGISTER ( CppEnumConstantInterpreter, boost::shared_ptr< Base<EncodingT> >, getStartBlock, const_t, UCS("CppEnumConstant::StartBlock") );
		METHOD_KEY_REGISTER1( CppEnumConstantInterpreter, void, setStartBlock, no_const_t, UCS("CppEnumConstant::StartBlock") );
		METHOD_KEY_REGISTER ( CppEnumConstantInterpreter, boost::shared_ptr< Base<EncodingT> >, getLengthBlock, const_t, UCS("CppEnumConstant::LengthBlock") );
		METHOD_KEY_REGISTER1( CppEnumConstantInterpreter, void, setLengthBlock, no_const_t, UCS("CppEnumConstant::LengthBlock") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( UCS("CppEnumConstant") );
		CLASS_KEY_UNREGISTER5( UCS("CppEnumConstant") );
		METHOD_KEY_UNREGISTER ( UCS("CppEnumConstant::Identifier") );
		METHOD_KEY_UNREGISTER ( UCS("CppEnumConstant::Name") );
		METHOD_KEY_UNREGISTER1( UCS("CppEnumConstant::Name") );
		METHOD_KEY_UNREGISTER ( UCS("CppEnumConstant::DefaultValue") );
		METHOD_KEY_UNREGISTER1( UCS("CppEnumConstant::DefaultValue") );
		METHOD_KEY_UNREGISTER ( UCS("CppEnumConstant::CppEnum") );
		METHOD_KEY_UNREGISTER1( UCS("CppEnumConstant::CppEnum") );
		METHOD_KEY_UNREGISTER ( UCS("CppEnumConstant::HasCppEnum") );
		METHOD_KEY_UNREGISTER ( UCS("CppEnumConstant::removeCppEnum") );
		METHOD_KEY_UNREGISTER ( UCS("CppEnumConstant::LineNumber") );
		METHOD_KEY_UNREGISTER1( UCS("CppEnumConstant::LineNumber") );
		METHOD_KEY_UNREGISTER ( UCS("CppEnumConstant::StartBlock") );
		METHOD_KEY_UNREGISTER1( UCS("CppEnumConstant::StartBlock") );
		METHOD_KEY_UNREGISTER ( UCS("CppEnumConstant::LengthBlock") );
		METHOD_KEY_UNREGISTER1( UCS("CppEnumConstant::LengthBlock") );
	FACTORY_END_UNREGISTER
};

template <class EncodingT>
bool check_cppEnumConstant(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _CppEnumConstant<EncodingT> >& o);

template <class EncodingT>
bool reset_cppEnumConstant(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _CppEnumConstant<EncodingT> > const& o);

NAMESPACE_END

#undef C
#undef A

#include "cppEnumConstantInterpreter_impl.hpp"

#endif
