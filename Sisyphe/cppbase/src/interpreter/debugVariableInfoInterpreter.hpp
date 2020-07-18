/* 
 * debugVariableInfoInterpreter.hpp
 *
 *
 * @date 14-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _DEBUGVARIABLEINFO_INTERPRETER_HPP_
#define _DEBUGVARIABLEINFO_INTERPRETER_HPP_

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
class DebugValueInfoInterpreter;

template <class EncodingT>
class DebugTypeInfoInterpreter;

template <class EncodingT>
class DebugFunctionInfoInterpreter;

template <class EncodingT>
class DebugVariableInfoInterpreter
: public Base<EncodingT>
{
private:
	boost::shared_ptr< _DebugVariableInfo<EncodingT> > m_value;

public:
	DebugVariableInfoInterpreter();

	DebugVariableInfoInterpreter(boost::shared_ptr< _DebugVariableInfo<EncodingT> > const& value);

	FACTORY_PROTOTYPE2(DebugVariableInfoInterpreter,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	DebugVariableInfoInterpreter(boost::shared_ptr< Base<EncodingT> > const& category,
				boost::shared_ptr< Base<EncodingT> > const& name);

	boost::shared_ptr< _DebugVariableInfo<EncodingT> > value() const;

	void value(boost::shared_ptr< _DebugVariableInfo<EncodingT> > const& value);

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getIdentifier() const;

	boost::shared_ptr< Base<EncodingT> > getCategory() const;

	boost::shared_ptr< Base<EncodingT> > getName() const;

	boost::shared_ptr< Base<EncodingT> > getDebugTypeInfo();

	boost::shared_ptr< Base<EncodingT> > getDebugFunctionInfo();

	FACTORY_PROTOTYPE1(setCategory, In< boost::shared_ptr< Base<EncodingT> > >)
	void setCategory(boost::shared_ptr< Base<EncodingT> > const& category);

	FACTORY_PROTOTYPE1(setName, In< boost::shared_ptr< Base<EncodingT> > >)
	void setName(boost::shared_ptr< Base<EncodingT> > const& name);

	FACTORY_PROTOTYPE1(setDebugTypeInfo, In< boost::shared_ptr< Base<EncodingT> > >)
	void setDebugTypeInfo(boost::shared_ptr< Base<EncodingT> > const& debugTypeInfo);

	FACTORY_PROTOTYPE1(setDebugFunctionInfo, In< boost::shared_ptr< Base<EncodingT> > >)
	void setDebugFunctionInfo(boost::shared_ptr< Base<EncodingT> > const& debugFunctionInfo);

	boost::shared_ptr< Base<EncodingT> > hasDebugTypeInfo() const;

	boost::shared_ptr< Base<EncodingT> > hasDebugFunctionInfo() const;

	void removeDebugTypeInfo();

	void removeDebugFunctionInfo();

	FACTORY_PROTOTYPE1(removeDebugValueInfo, In< boost::shared_ptr< Base<EncodingT> > >)
	void removeDebugValueInfo(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE2(insertDebugValueInfo, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void insertDebugValueInfo(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& debugValueInfo);

	FACTORY_PROTOTYPE1(getDebugValueInfo, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getDebugValueInfo(boost::shared_ptr< Base<EncodingT> > const& n);

	void clearDebugValueInfos();

	boost::shared_ptr< Base<EncodingT> > hasDebugValueInfos() const;

	boost::shared_ptr< Base<EncodingT> > debugValueInfosCount() const;

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( DebugVariableInfoInterpreter, UCS("DebugVariableInfo") );
		CLASS_KEY_REGISTER2( DebugVariableInfoInterpreter, UCS("DebugVariableInfo") );
		METHOD_KEY_REGISTER ( DebugVariableInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getIdentifier, const_t, UCS("DebugVariableInfo::Identifier") );
		METHOD_KEY_REGISTER ( DebugVariableInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getCategory, const_t, UCS("DebugVariableInfo::Category") );
		METHOD_KEY_REGISTER1( DebugVariableInfoInterpreter, void, setCategory, no_const_t, UCS("DebugVariableInfo::Category") );
		METHOD_KEY_REGISTER ( DebugVariableInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getName, const_t, UCS("DebugVariableInfo::Name") );
		METHOD_KEY_REGISTER1( DebugVariableInfoInterpreter, void, setName, no_const_t, UCS("DebugVariableInfo::Name") );
		METHOD_KEY_REGISTER1( DebugVariableInfoInterpreter, void, setDebugTypeInfo, no_const_t, UCS("DebugVariableInfo::DebugTypeInfo") );
		METHOD_KEY_REGISTER ( DebugVariableInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getDebugTypeInfo, no_const_t, UCS("DebugVariableInfo::DebugTypeInfo") );
		METHOD_KEY_REGISTER ( DebugVariableInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, hasDebugTypeInfo, const_t, UCS("DebugVariableInfo::HasDebugTypeInfo") );
		METHOD_KEY_REGISTER ( DebugVariableInfoInterpreter, void, removeDebugTypeInfo, no_const_t, UCS("DebugVariableInfo::removeDebugTypeInfo") );
		METHOD_KEY_REGISTER1( DebugVariableInfoInterpreter, void, setDebugFunctionInfo, no_const_t, UCS("DebugVariableInfo::DebugFunctionInfo") );
		METHOD_KEY_REGISTER ( DebugVariableInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getDebugFunctionInfo, no_const_t, UCS("DebugVariableInfo::DebugFunctionInfo") );
		METHOD_KEY_REGISTER ( DebugVariableInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, hasDebugFunctionInfo, const_t, UCS("DebugVariableInfo::HasDebugFunctionInfo") );
		METHOD_KEY_REGISTER ( DebugVariableInfoInterpreter, void, removeDebugFunctionInfo, no_const_t, UCS("DebugVariableInfo::removeDebugFunctionInfo") );
		METHOD_KEY_REGISTER1( DebugVariableInfoInterpreter, void, removeDebugValueInfo, no_const_t, UCS("DebugVariableInfo::removeDebugValueInfos") );
		METHOD_KEY_REGISTER2( DebugVariableInfoInterpreter, void, insertDebugValueInfo, no_const_t, UCS("DebugVariableInfo::DebugValueInfos") );
		METHOD_KEY_REGISTER1( DebugVariableInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getDebugValueInfo, no_const_t, UCS("DebugVariableInfo::DebugValueInfos") );
		METHOD_KEY_REGISTER ( DebugVariableInfoInterpreter, void, clearDebugValueInfos, no_const_t, UCS("DebugVariableInfo::ClearDebugValueInfos") );
		METHOD_KEY_REGISTER ( DebugVariableInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, hasDebugValueInfos, const_t, UCS("DebugVariableInfo::HasDebugValueInfos") );
		METHOD_KEY_REGISTER ( DebugVariableInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, debugValueInfosCount, const_t, UCS("DebugVariableInfo::DebugValueInfosCount") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( UCS("DebugVariableInfo") );
		CLASS_KEY_UNREGISTER2( UCS("DebugVariableInfo") );
		METHOD_KEY_UNREGISTER ( UCS("DebugVariableInfo::Identifier") );
		METHOD_KEY_UNREGISTER ( UCS("DebugVariableInfo::Category") );
		METHOD_KEY_UNREGISTER1( UCS("DebugVariableInfo::Category") );
		METHOD_KEY_UNREGISTER ( UCS("DebugVariableInfo::Name") );
		METHOD_KEY_UNREGISTER1( UCS("DebugVariableInfo::Name") );
		METHOD_KEY_UNREGISTER ( UCS("DebugVariableInfo::DebugTypeInfo") );
		METHOD_KEY_UNREGISTER1( UCS("DebugVariableInfo::DebugTypeInfo") );
		METHOD_KEY_UNREGISTER ( UCS("DebugVariableInfo::HasDebugTypeInfo") );
		METHOD_KEY_UNREGISTER ( UCS("DebugVariableInfo::removeDebugTypeInfo") );
		METHOD_KEY_UNREGISTER ( UCS("DebugVariableInfo::DebugFunctionInfo") );
		METHOD_KEY_UNREGISTER1( UCS("DebugVariableInfo::DebugFunctionInfo") );
		METHOD_KEY_UNREGISTER ( UCS("DebugVariableInfo::HasDebugFunctionInfo") );
		METHOD_KEY_UNREGISTER ( UCS("DebugVariableInfo::removeDebugFunctionInfo") );
		METHOD_KEY_UNREGISTER1( UCS("DebugVariableInfo::removeDebugValueInfos") );
		METHOD_KEY_UNREGISTER2( UCS("DebugVariableInfo::DebugValueInfos") );
		METHOD_KEY_UNREGISTER1( UCS("DebugVariableInfo::DebugValueInfos") );
		METHOD_KEY_UNREGISTER ( UCS("DebugVariableInfo::ClearDebugValueInfos") );
		METHOD_KEY_UNREGISTER ( UCS("DebugVariableInfo::HasDebugValueInfos") );
		METHOD_KEY_UNREGISTER ( UCS("DebugVariableInfo::DebugValueInfosCount") );
	FACTORY_END_UNREGISTER
};

template <class EncodingT>
bool check_debugVariableInfo(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _DebugVariableInfo<EncodingT> >& o);

template <class EncodingT>
bool reset_debugVariableInfo(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _DebugVariableInfo<EncodingT> > const& o);

NAMESPACE_END

#undef C
#undef A

#include "debugVariableInfoInterpreter_impl.hpp"

#endif
