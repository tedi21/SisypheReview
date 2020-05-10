/* 
 * debugErrorInfoInterpreter.hpp
 *
 *
 * @date 10-05-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _DEBUGERRORINFO_INTERPRETER_HPP_
#define _DEBUGERRORINFO_INTERPRETER_HPP_

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
class DebugErrorInfoInterpreter
: public Base<EncodingT>
{
private:
	boost::shared_ptr< _DebugErrorInfo<EncodingT> > m_value;

public:
	DebugErrorInfoInterpreter();

	DebugErrorInfoInterpreter(boost::shared_ptr< _DebugErrorInfo<EncodingT> > const& value);

	FACTORY_PROTOTYPE1(DebugErrorInfoInterpreter,
				In< boost::shared_ptr< Base<EncodingT> > >)
	DebugErrorInfoInterpreter(boost::shared_ptr< Base<EncodingT> > const& callStack);

	boost::shared_ptr< _DebugErrorInfo<EncodingT> > value() const;

	void value(boost::shared_ptr< _DebugErrorInfo<EncodingT> > const& value);

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getIdentifier() const;

	boost::shared_ptr< Base<EncodingT> > getCallStack() const;

	FACTORY_PROTOTYPE1(setCallStack, In< boost::shared_ptr< Base<EncodingT> > >)
	void setCallStack(boost::shared_ptr< Base<EncodingT> > const& callStack);

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( DebugErrorInfoInterpreter, C("DebugErrorInfo") );
		CLASS_KEY_REGISTER1( DebugErrorInfoInterpreter, C("DebugErrorInfo") );
		METHOD_KEY_REGISTER ( DebugErrorInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getIdentifier, const_t, C("DebugErrorInfo::Identifier") );
		METHOD_KEY_REGISTER ( DebugErrorInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getCallStack, const_t, C("DebugErrorInfo::CallStack") );
		METHOD_KEY_REGISTER1( DebugErrorInfoInterpreter, void, setCallStack, no_const_t, C("DebugErrorInfo::CallStack") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( C("DebugErrorInfo") );
		CLASS_KEY_UNREGISTER1( C("DebugErrorInfo") );
		METHOD_KEY_UNREGISTER ( C("DebugErrorInfo::Identifier") );
		METHOD_KEY_UNREGISTER ( C("DebugErrorInfo::CallStack") );
		METHOD_KEY_UNREGISTER1( C("DebugErrorInfo::CallStack") );
	FACTORY_END_UNREGISTER
};

template <class EncodingT>
bool check_debugErrorInfo(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _DebugErrorInfo<EncodingT> >& o);

template <class EncodingT>
bool reset_debugErrorInfo(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _DebugErrorInfo<EncodingT> > const& o);

NAMESPACE_END

#undef C
#undef A

#include "debugErrorInfoInterpreter_impl.hpp"

#endif
