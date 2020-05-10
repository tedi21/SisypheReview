/* 
 * debugValueInfoInterpreter.hpp
 *
 *
 * @date 10-05-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _DEBUGVALUEINFO_INTERPRETER_HPP_
#define _DEBUGVALUEINFO_INTERPRETER_HPP_

#include "config.hpp"
#include "macros.hpp"
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
class DebugVariableInfoInterpreter;

template <class EncodingT>
class DebugStubInfoInterpreter;

template <class EncodingT>
class DebugValueInfoInterpreter
: public Base<EncodingT>
{
private:
	boost::shared_ptr< _DebugValueInfo<EncodingT> > m_value;

public:
	DebugValueInfoInterpreter();

	DebugValueInfoInterpreter(boost::shared_ptr< _DebugValueInfo<EncodingT> > const& value);

	FACTORY_PROTOTYPE1(DebugValueInfoInterpreter,
				In< boost::shared_ptr< Base<EncodingT> > >)
	DebugValueInfoInterpreter(boost::shared_ptr< Base<EncodingT> > const& textValue);

	boost::shared_ptr< _DebugValueInfo<EncodingT> > value() const;

	void value(boost::shared_ptr< _DebugValueInfo<EncodingT> > const& value);

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getIdentifier() const;

	boost::shared_ptr< Base<EncodingT> > getTextValue() const;

	boost::shared_ptr< Base<EncodingT> > getDebugVariableInfo();

	boost::shared_ptr< Base<EncodingT> > getDebugStubInfo();

	FACTORY_PROTOTYPE1(setTextValue, In< boost::shared_ptr< Base<EncodingT> > >)
	void setTextValue(boost::shared_ptr< Base<EncodingT> > const& textValue);

	FACTORY_PROTOTYPE1(setDebugVariableInfo, In< boost::shared_ptr< Base<EncodingT> > >)
	void setDebugVariableInfo(boost::shared_ptr< Base<EncodingT> > const& debugVariableInfo);

	FACTORY_PROTOTYPE1(setDebugStubInfo, In< boost::shared_ptr< Base<EncodingT> > >)
	void setDebugStubInfo(boost::shared_ptr< Base<EncodingT> > const& debugStubInfo);

	boost::shared_ptr< Base<EncodingT> > hasDebugVariableInfo() const;

	boost::shared_ptr< Base<EncodingT> > hasDebugStubInfo() const;

	void removeDebugVariableInfo();

	void removeDebugStubInfo();

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( DebugValueInfoInterpreter, C("DebugValueInfo") );
		CLASS_KEY_REGISTER1( DebugValueInfoInterpreter, C("DebugValueInfo") );
		METHOD_KEY_REGISTER ( DebugValueInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getIdentifier, const_t, C("DebugValueInfo::Identifier") );
		METHOD_KEY_REGISTER ( DebugValueInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getTextValue, const_t, C("DebugValueInfo::TextValue") );
		METHOD_KEY_REGISTER1( DebugValueInfoInterpreter, void, setTextValue, no_const_t, C("DebugValueInfo::TextValue") );
		METHOD_KEY_REGISTER1( DebugValueInfoInterpreter, void, setDebugVariableInfo, no_const_t, C("DebugValueInfo::DebugVariableInfo") );
		METHOD_KEY_REGISTER ( DebugValueInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getDebugVariableInfo, no_const_t, C("DebugValueInfo::DebugVariableInfo") );
		METHOD_KEY_REGISTER ( DebugValueInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, hasDebugVariableInfo, const_t, C("DebugValueInfo::HasDebugVariableInfo") );
		METHOD_KEY_REGISTER ( DebugValueInfoInterpreter, void, removeDebugVariableInfo, no_const_t, C("DebugValueInfo::removeDebugVariableInfo") );
		METHOD_KEY_REGISTER1( DebugValueInfoInterpreter, void, setDebugStubInfo, no_const_t, C("DebugValueInfo::DebugStubInfo") );
		METHOD_KEY_REGISTER ( DebugValueInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getDebugStubInfo, no_const_t, C("DebugValueInfo::DebugStubInfo") );
		METHOD_KEY_REGISTER ( DebugValueInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, hasDebugStubInfo, const_t, C("DebugValueInfo::HasDebugStubInfo") );
		METHOD_KEY_REGISTER ( DebugValueInfoInterpreter, void, removeDebugStubInfo, no_const_t, C("DebugValueInfo::removeDebugStubInfo") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( C("DebugValueInfo") );
		CLASS_KEY_UNREGISTER1( C("DebugValueInfo") );
		METHOD_KEY_UNREGISTER ( C("DebugValueInfo::Identifier") );
		METHOD_KEY_UNREGISTER ( C("DebugValueInfo::TextValue") );
		METHOD_KEY_UNREGISTER1( C("DebugValueInfo::TextValue") );
		METHOD_KEY_UNREGISTER ( C("DebugValueInfo::DebugVariableInfo") );
		METHOD_KEY_UNREGISTER1( C("DebugValueInfo::DebugVariableInfo") );
		METHOD_KEY_UNREGISTER ( C("DebugValueInfo::HasDebugVariableInfo") );
		METHOD_KEY_UNREGISTER ( C("DebugValueInfo::removeDebugVariableInfo") );
		METHOD_KEY_UNREGISTER ( C("DebugValueInfo::DebugStubInfo") );
		METHOD_KEY_UNREGISTER1( C("DebugValueInfo::DebugStubInfo") );
		METHOD_KEY_UNREGISTER ( C("DebugValueInfo::HasDebugStubInfo") );
		METHOD_KEY_UNREGISTER ( C("DebugValueInfo::removeDebugStubInfo") );
	FACTORY_END_UNREGISTER
};

template <class EncodingT>
bool check_debugValueInfo(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _DebugValueInfo<EncodingT> >& o);

template <class EncodingT>
bool reset_debugValueInfo(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _DebugValueInfo<EncodingT> > const& o);

NAMESPACE_END

#undef C
#undef A

#include "debugValueInfoInterpreter_impl.hpp"

#endif
