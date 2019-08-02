/* 
 * cppParameterInterpreter.hpp
 *
 *
 * @date 26-03-2019
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPPARAMETER_INTERPRETER_HPP_
#define _CPPPARAMETER_INTERPRETER_HPP_

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
class CppFunctionInterpreter;

template <class EncodingT>
class CppParameterInterpreter
: public Base<EncodingT>
{
private:
	boost::shared_ptr< _CppParameter<EncodingT> > m_value;

public:
	CppParameterInterpreter();

	CppParameterInterpreter(boost::shared_ptr< _CppParameter<EncodingT> > const& value);

	FACTORY_PROTOTYPE12(CppParameterInterpreter,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
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
	CppParameterInterpreter(boost::shared_ptr< Base<EncodingT> > const& paramOrder,
				boost::shared_ptr< Base<EncodingT> > const& paramType,
				boost::shared_ptr< Base<EncodingT> > const& isConst,
				boost::shared_ptr< Base<EncodingT> > const& defaultValue,
				boost::shared_ptr< Base<EncodingT> > const& decName,
				boost::shared_ptr< Base<EncodingT> > const& decLineNumber,
				boost::shared_ptr< Base<EncodingT> > const& startDecBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthDecBlock,
				boost::shared_ptr< Base<EncodingT> > const& defName,
				boost::shared_ptr< Base<EncodingT> > const& defLineNumber,
				boost::shared_ptr< Base<EncodingT> > const& startDefBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthDefBlock);

	boost::shared_ptr< _CppParameter<EncodingT> > value() const;

	void value(boost::shared_ptr< _CppParameter<EncodingT> > const& value);

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getIdentifier() const;

	boost::shared_ptr< Base<EncodingT> > getParamOrder() const;

	boost::shared_ptr< Base<EncodingT> > getParamType() const;

	boost::shared_ptr< Base<EncodingT> > getIsConst() const;

	boost::shared_ptr< Base<EncodingT> > getDefaultValue() const;

	boost::shared_ptr< Base<EncodingT> > getDecName() const;

	boost::shared_ptr< Base<EncodingT> > getDecLineNumber() const;

	boost::shared_ptr< Base<EncodingT> > getStartDecBlock() const;

	boost::shared_ptr< Base<EncodingT> > getLengthDecBlock() const;

	boost::shared_ptr< Base<EncodingT> > getDefName() const;

	boost::shared_ptr< Base<EncodingT> > getDefLineNumber() const;

	boost::shared_ptr< Base<EncodingT> > getStartDefBlock() const;

	boost::shared_ptr< Base<EncodingT> > getLengthDefBlock() const;

	boost::shared_ptr< Base<EncodingT> > getCppFunction();

	FACTORY_PROTOTYPE1(setParamOrder, In< boost::shared_ptr< Base<EncodingT> > >)
	void setParamOrder(boost::shared_ptr< Base<EncodingT> > const& paramOrder);

	FACTORY_PROTOTYPE1(setParamType, In< boost::shared_ptr< Base<EncodingT> > >)
	void setParamType(boost::shared_ptr< Base<EncodingT> > const& paramType);

	FACTORY_PROTOTYPE1(setIsConst, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsConst(boost::shared_ptr< Base<EncodingT> > const& isConst);

	FACTORY_PROTOTYPE1(setDefaultValue, In< boost::shared_ptr< Base<EncodingT> > >)
	void setDefaultValue(boost::shared_ptr< Base<EncodingT> > const& defaultValue);

	FACTORY_PROTOTYPE1(setCppFunction, In< boost::shared_ptr< Base<EncodingT> > >)
	void setCppFunction(boost::shared_ptr< Base<EncodingT> > const& cppFunction);

	FACTORY_PROTOTYPE1(setDecName, In< boost::shared_ptr< Base<EncodingT> > >)
	void setDecName(boost::shared_ptr< Base<EncodingT> > const& decName);

	FACTORY_PROTOTYPE1(setDecLineNumber, In< boost::shared_ptr< Base<EncodingT> > >)
	void setDecLineNumber(boost::shared_ptr< Base<EncodingT> > const& decLineNumber);

	FACTORY_PROTOTYPE1(setStartDecBlock, In< boost::shared_ptr< Base<EncodingT> > >)
	void setStartDecBlock(boost::shared_ptr< Base<EncodingT> > const& startDecBlock);

	FACTORY_PROTOTYPE1(setLengthDecBlock, In< boost::shared_ptr< Base<EncodingT> > >)
	void setLengthDecBlock(boost::shared_ptr< Base<EncodingT> > const& lengthDecBlock);

	FACTORY_PROTOTYPE1(setDefName, In< boost::shared_ptr< Base<EncodingT> > >)
	void setDefName(boost::shared_ptr< Base<EncodingT> > const& defName);

	FACTORY_PROTOTYPE1(setDefLineNumber, In< boost::shared_ptr< Base<EncodingT> > >)
	void setDefLineNumber(boost::shared_ptr< Base<EncodingT> > const& defLineNumber);

	FACTORY_PROTOTYPE1(setStartDefBlock, In< boost::shared_ptr< Base<EncodingT> > >)
	void setStartDefBlock(boost::shared_ptr< Base<EncodingT> > const& startDefBlock);

	FACTORY_PROTOTYPE1(setLengthDefBlock, In< boost::shared_ptr< Base<EncodingT> > >)
	void setLengthDefBlock(boost::shared_ptr< Base<EncodingT> > const& lengthDefBlock);

	boost::shared_ptr< Base<EncodingT> > hasCppFunction() const;

	void removeCppFunction();

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( CppParameterInterpreter, UCS("CppParameter") );
		CLASS_KEY_REGISTER12( CppParameterInterpreter, UCS("CppParameter") );
		METHOD_KEY_REGISTER ( CppParameterInterpreter, boost::shared_ptr< Base<EncodingT> >, getIdentifier, const_t, UCS("CppParameter::Identifier") );
		METHOD_KEY_REGISTER ( CppParameterInterpreter, boost::shared_ptr< Base<EncodingT> >, getParamOrder, const_t, UCS("CppParameter::ParamOrder") );
		METHOD_KEY_REGISTER1( CppParameterInterpreter, void, setParamOrder, no_const_t, UCS("CppParameter::ParamOrder") );
		METHOD_KEY_REGISTER ( CppParameterInterpreter, boost::shared_ptr< Base<EncodingT> >, getParamType, const_t, UCS("CppParameter::ParamType") );
		METHOD_KEY_REGISTER1( CppParameterInterpreter, void, setParamType, no_const_t, UCS("CppParameter::ParamType") );
		METHOD_KEY_REGISTER ( CppParameterInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsConst, const_t, UCS("CppParameter::IsConst") );
		METHOD_KEY_REGISTER1( CppParameterInterpreter, void, setIsConst, no_const_t, UCS("CppParameter::IsConst") );
		METHOD_KEY_REGISTER ( CppParameterInterpreter, boost::shared_ptr< Base<EncodingT> >, getDefaultValue, const_t, UCS("CppParameter::DefaultValue") );
		METHOD_KEY_REGISTER1( CppParameterInterpreter, void, setDefaultValue, no_const_t, UCS("CppParameter::DefaultValue") );
		METHOD_KEY_REGISTER1( CppParameterInterpreter, void, setCppFunction, no_const_t, UCS("CppParameter::CppFunction") );
		METHOD_KEY_REGISTER ( CppParameterInterpreter, boost::shared_ptr< Base<EncodingT> >, getCppFunction, no_const_t, UCS("CppParameter::CppFunction") );
		METHOD_KEY_REGISTER ( CppParameterInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCppFunction, const_t, UCS("CppParameter::HasCppFunction") );
		METHOD_KEY_REGISTER ( CppParameterInterpreter, void, removeCppFunction, no_const_t, UCS("CppParameter::removeCppFunction") );
		METHOD_KEY_REGISTER ( CppParameterInterpreter, boost::shared_ptr< Base<EncodingT> >, getDecName, const_t, UCS("CppParameter::DecName") );
		METHOD_KEY_REGISTER1( CppParameterInterpreter, void, setDecName, no_const_t, UCS("CppParameter::DecName") );
		METHOD_KEY_REGISTER ( CppParameterInterpreter, boost::shared_ptr< Base<EncodingT> >, getDecLineNumber, const_t, UCS("CppParameter::DecLineNumber") );
		METHOD_KEY_REGISTER1( CppParameterInterpreter, void, setDecLineNumber, no_const_t, UCS("CppParameter::DecLineNumber") );
		METHOD_KEY_REGISTER ( CppParameterInterpreter, boost::shared_ptr< Base<EncodingT> >, getStartDecBlock, const_t, UCS("CppParameter::StartDecBlock") );
		METHOD_KEY_REGISTER1( CppParameterInterpreter, void, setStartDecBlock, no_const_t, UCS("CppParameter::StartDecBlock") );
		METHOD_KEY_REGISTER ( CppParameterInterpreter, boost::shared_ptr< Base<EncodingT> >, getLengthDecBlock, const_t, UCS("CppParameter::LengthDecBlock") );
		METHOD_KEY_REGISTER1( CppParameterInterpreter, void, setLengthDecBlock, no_const_t, UCS("CppParameter::LengthDecBlock") );
		METHOD_KEY_REGISTER ( CppParameterInterpreter, boost::shared_ptr< Base<EncodingT> >, getDefName, const_t, UCS("CppParameter::DefName") );
		METHOD_KEY_REGISTER1( CppParameterInterpreter, void, setDefName, no_const_t, UCS("CppParameter::DefName") );
		METHOD_KEY_REGISTER ( CppParameterInterpreter, boost::shared_ptr< Base<EncodingT> >, getDefLineNumber, const_t, UCS("CppParameter::DefLineNumber") );
		METHOD_KEY_REGISTER1( CppParameterInterpreter, void, setDefLineNumber, no_const_t, UCS("CppParameter::DefLineNumber") );
		METHOD_KEY_REGISTER ( CppParameterInterpreter, boost::shared_ptr< Base<EncodingT> >, getStartDefBlock, const_t, UCS("CppParameter::StartDefBlock") );
		METHOD_KEY_REGISTER1( CppParameterInterpreter, void, setStartDefBlock, no_const_t, UCS("CppParameter::StartDefBlock") );
		METHOD_KEY_REGISTER ( CppParameterInterpreter, boost::shared_ptr< Base<EncodingT> >, getLengthDefBlock, const_t, UCS("CppParameter::LengthDefBlock") );
		METHOD_KEY_REGISTER1( CppParameterInterpreter, void, setLengthDefBlock, no_const_t, UCS("CppParameter::LengthDefBlock") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( UCS("CppParameter") );
		CLASS_KEY_UNREGISTER12( UCS("CppParameter") );
		METHOD_KEY_UNREGISTER ( UCS("CppParameter::Identifier") );
		METHOD_KEY_UNREGISTER ( UCS("CppParameter::ParamOrder") );
		METHOD_KEY_UNREGISTER1( UCS("CppParameter::ParamOrder") );
		METHOD_KEY_UNREGISTER ( UCS("CppParameter::ParamType") );
		METHOD_KEY_UNREGISTER1( UCS("CppParameter::ParamType") );
		METHOD_KEY_UNREGISTER ( UCS("CppParameter::IsConst") );
		METHOD_KEY_UNREGISTER1( UCS("CppParameter::IsConst") );
		METHOD_KEY_UNREGISTER ( UCS("CppParameter::DefaultValue") );
		METHOD_KEY_UNREGISTER1( UCS("CppParameter::DefaultValue") );
		METHOD_KEY_UNREGISTER ( UCS("CppParameter::CppFunction") );
		METHOD_KEY_UNREGISTER1( UCS("CppParameter::CppFunction") );
		METHOD_KEY_UNREGISTER ( UCS("CppParameter::HasCppFunction") );
		METHOD_KEY_UNREGISTER ( UCS("CppParameter::removeCppFunction") );
		METHOD_KEY_UNREGISTER ( UCS("CppParameter::DecName") );
		METHOD_KEY_UNREGISTER1( UCS("CppParameter::DecName") );
		METHOD_KEY_UNREGISTER ( UCS("CppParameter::DecLineNumber") );
		METHOD_KEY_UNREGISTER1( UCS("CppParameter::DecLineNumber") );
		METHOD_KEY_UNREGISTER ( UCS("CppParameter::StartDecBlock") );
		METHOD_KEY_UNREGISTER1( UCS("CppParameter::StartDecBlock") );
		METHOD_KEY_UNREGISTER ( UCS("CppParameter::LengthDecBlock") );
		METHOD_KEY_UNREGISTER1( UCS("CppParameter::LengthDecBlock") );
		METHOD_KEY_UNREGISTER ( UCS("CppParameter::DefName") );
		METHOD_KEY_UNREGISTER1( UCS("CppParameter::DefName") );
		METHOD_KEY_UNREGISTER ( UCS("CppParameter::DefLineNumber") );
		METHOD_KEY_UNREGISTER1( UCS("CppParameter::DefLineNumber") );
		METHOD_KEY_UNREGISTER ( UCS("CppParameter::StartDefBlock") );
		METHOD_KEY_UNREGISTER1( UCS("CppParameter::StartDefBlock") );
		METHOD_KEY_UNREGISTER ( UCS("CppParameter::LengthDefBlock") );
		METHOD_KEY_UNREGISTER1( UCS("CppParameter::LengthDefBlock") );
	FACTORY_END_UNREGISTER
};

template <class EncodingT>
bool check_cppParameter(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _CppParameter<EncodingT> >& o);

template <class EncodingT>
bool reset_cppParameter(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _CppParameter<EncodingT> > const& o);

NAMESPACE_END

#undef C
#undef A

#include "cppParameterInterpreter_impl.hpp"

#endif
