/* 
 * debugFunctionInfoInterpreter.hpp
 *
 *
 * @date 28-08-2016
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _DEBUGFUNCTIONINFO_INTERPRETER_HPP_
#define _DEBUGFUNCTIONINFO_INTERPRETER_HPP_

#include "config.hpp"
#include "macros.hpp"
#include "String.hpp"
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
class CppFunctionInterpreter;

template <class EncodingT>
class DebugFunctionInfoInterpreter
: public String<EncodingT>
{
private:
	boost::shared_ptr< _DebugFunctionInfo<EncodingT> > m_value;

public:
	DebugFunctionInfoInterpreter();

	DebugFunctionInfoInterpreter(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > const& value);

	FACTORY_PROTOTYPE5(DebugFunctionInfoInterpreter,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	DebugFunctionInfoInterpreter(boost::shared_ptr< Base<EncodingT> > const& lineNumber,
				boost::shared_ptr< Base<EncodingT> > const& address,
				boost::shared_ptr< Base<EncodingT> > const& debugStart,
				boost::shared_ptr< Base<EncodingT> > const& debugEnd,
				boost::shared_ptr< Base<EncodingT> > const& debugReturnType);

	~DebugFunctionInfoInterpreter();

	boost::shared_ptr< _DebugFunctionInfo<EncodingT> > getValue() const;

	void setValue(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > const& value);

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getIdentifier() const;

	boost::shared_ptr< Base<EncodingT> > getLineNumber() const;

	boost::shared_ptr< Base<EncodingT> > getAddress() const;

	boost::shared_ptr< Base<EncodingT> > getDebugStart() const;

	boost::shared_ptr< Base<EncodingT> > getDebugEnd() const;

	boost::shared_ptr< Base<EncodingT> > getDebugReturnType() const;

	boost::shared_ptr< Base<EncodingT> > getCppFunction();

	FACTORY_PROTOTYPE1(setLineNumber, In< boost::shared_ptr< Base<EncodingT> > >)
	void setLineNumber(boost::shared_ptr< Base<EncodingT> > const& lineNumber);

	FACTORY_PROTOTYPE1(setAddress, In< boost::shared_ptr< Base<EncodingT> > >)
	void setAddress(boost::shared_ptr< Base<EncodingT> > const& address);

	FACTORY_PROTOTYPE1(setDebugStart, In< boost::shared_ptr< Base<EncodingT> > >)
	void setDebugStart(boost::shared_ptr< Base<EncodingT> > const& debugStart);

	FACTORY_PROTOTYPE1(setDebugEnd, In< boost::shared_ptr< Base<EncodingT> > >)
	void setDebugEnd(boost::shared_ptr< Base<EncodingT> > const& debugEnd);

	FACTORY_PROTOTYPE1(setDebugReturnType, In< boost::shared_ptr< Base<EncodingT> > >)
	void setDebugReturnType(boost::shared_ptr< Base<EncodingT> > const& debugReturnType);

	FACTORY_PROTOTYPE1(setCppFunction, In< boost::shared_ptr< Base<EncodingT> > >)
	void setCppFunction(boost::shared_ptr< Base<EncodingT> > const& cppFunction);

	boost::shared_ptr< Base<EncodingT> > hasCppFunction() const;

	void removeCppFunction();

	FACTORY_PROTOTYPE1(removeDebugVariableInfo, In< boost::shared_ptr< Base<EncodingT> > >)
	void removeDebugVariableInfo(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE2(insertDebugVariableInfo, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void insertDebugVariableInfo(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& debugVariableInfo);

	FACTORY_PROTOTYPE1(getDebugVariableInfo, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getDebugVariableInfo(boost::shared_ptr< Base<EncodingT> > const& n);

	void clearDebugVariableInfos();

	boost::shared_ptr< Base<EncodingT> > hasDebugVariableInfos() const;

	boost::shared_ptr< Base<EncodingT> > debugVariableInfosCount() const;

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( DebugFunctionInfoInterpreter, C("DebugFunctionInfo") );
		CLASS_KEY_REGISTER5( DebugFunctionInfoInterpreter, C("DebugFunctionInfo") );
		METHOD_KEY_REGISTER ( DebugFunctionInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getIdentifier, const_t, C("DebugFunctionInfo::Identifier") );
		METHOD_KEY_REGISTER ( DebugFunctionInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getLineNumber, const_t, C("DebugFunctionInfo::LineNumber") );
		METHOD_KEY_REGISTER1( DebugFunctionInfoInterpreter, void, setLineNumber, no_const_t, C("DebugFunctionInfo::LineNumber") );
		METHOD_KEY_REGISTER ( DebugFunctionInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getAddress, const_t, C("DebugFunctionInfo::Address") );
		METHOD_KEY_REGISTER1( DebugFunctionInfoInterpreter, void, setAddress, no_const_t, C("DebugFunctionInfo::Address") );
		METHOD_KEY_REGISTER ( DebugFunctionInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getDebugStart, const_t, C("DebugFunctionInfo::DebugStart") );
		METHOD_KEY_REGISTER1( DebugFunctionInfoInterpreter, void, setDebugStart, no_const_t, C("DebugFunctionInfo::DebugStart") );
		METHOD_KEY_REGISTER ( DebugFunctionInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getDebugEnd, const_t, C("DebugFunctionInfo::DebugEnd") );
		METHOD_KEY_REGISTER1( DebugFunctionInfoInterpreter, void, setDebugEnd, no_const_t, C("DebugFunctionInfo::DebugEnd") );
		METHOD_KEY_REGISTER ( DebugFunctionInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getDebugReturnType, const_t, C("DebugFunctionInfo::DebugReturnType") );
		METHOD_KEY_REGISTER1( DebugFunctionInfoInterpreter, void, setDebugReturnType, no_const_t, C("DebugFunctionInfo::DebugReturnType") );
		METHOD_KEY_REGISTER1( DebugFunctionInfoInterpreter, void, setCppFunction, no_const_t, C("DebugFunctionInfo::CppFunction") );
		METHOD_KEY_REGISTER ( DebugFunctionInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getCppFunction, no_const_t, C("DebugFunctionInfo::CppFunction") );
		METHOD_KEY_REGISTER ( DebugFunctionInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCppFunction, const_t, C("DebugFunctionInfo::HasCppFunction") );
		METHOD_KEY_REGISTER ( DebugFunctionInfoInterpreter, void, removeCppFunction, no_const_t, C("DebugFunctionInfo::removeCppFunction") );
		METHOD_KEY_REGISTER1( DebugFunctionInfoInterpreter, void, removeDebugVariableInfo, no_const_t, C("DebugFunctionInfo::removeDebugVariableInfos") );
		METHOD_KEY_REGISTER2( DebugFunctionInfoInterpreter, void, insertDebugVariableInfo, no_const_t, C("DebugFunctionInfo::DebugVariableInfos") );
		METHOD_KEY_REGISTER1( DebugFunctionInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getDebugVariableInfo, no_const_t, C("DebugFunctionInfo::DebugVariableInfos") );
		METHOD_KEY_REGISTER ( DebugFunctionInfoInterpreter, void, clearDebugVariableInfos, no_const_t, C("DebugFunctionInfo::ClearDebugVariableInfos") );
		METHOD_KEY_REGISTER ( DebugFunctionInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, hasDebugVariableInfos, const_t, C("DebugFunctionInfo::HasDebugVariableInfos") );
		METHOD_KEY_REGISTER ( DebugFunctionInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, debugVariableInfosCount, const_t, C("DebugFunctionInfo::DebugVariableInfosCount") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( C("DebugFunctionInfo") );
		CLASS_KEY_UNREGISTER5( C("DebugFunctionInfo") );
		METHOD_KEY_UNREGISTER ( C("DebugFunctionInfo::Identifier") );
		METHOD_KEY_UNREGISTER ( C("DebugFunctionInfo::LineNumber") );
		METHOD_KEY_UNREGISTER1( C("DebugFunctionInfo::LineNumber") );
		METHOD_KEY_UNREGISTER ( C("DebugFunctionInfo::Address") );
		METHOD_KEY_UNREGISTER1( C("DebugFunctionInfo::Address") );
		METHOD_KEY_UNREGISTER ( C("DebugFunctionInfo::DebugStart") );
		METHOD_KEY_UNREGISTER1( C("DebugFunctionInfo::DebugStart") );
		METHOD_KEY_UNREGISTER ( C("DebugFunctionInfo::DebugEnd") );
		METHOD_KEY_UNREGISTER1( C("DebugFunctionInfo::DebugEnd") );
		METHOD_KEY_UNREGISTER ( C("DebugFunctionInfo::DebugReturnType") );
		METHOD_KEY_UNREGISTER1( C("DebugFunctionInfo::DebugReturnType") );
		METHOD_KEY_UNREGISTER ( C("DebugFunctionInfo::CppFunction") );
		METHOD_KEY_UNREGISTER1( C("DebugFunctionInfo::CppFunction") );
		METHOD_KEY_UNREGISTER ( C("DebugFunctionInfo::HasCppFunction") );
		METHOD_KEY_UNREGISTER ( C("DebugFunctionInfo::removeCppFunction") );
		METHOD_KEY_UNREGISTER1( C("DebugFunctionInfo::removeDebugVariableInfos") );
		METHOD_KEY_UNREGISTER2( C("DebugFunctionInfo::DebugVariableInfos") );
		METHOD_KEY_UNREGISTER1( C("DebugFunctionInfo::DebugVariableInfos") );
		METHOD_KEY_UNREGISTER ( C("DebugFunctionInfo::ClearDebugVariableInfos") );
		METHOD_KEY_UNREGISTER ( C("DebugFunctionInfo::HasDebugVariableInfos") );
		METHOD_KEY_UNREGISTER ( C("DebugFunctionInfo::DebugVariableInfosCount") );
	FACTORY_END_UNREGISTER
};

template <class EncodingT>
bool check_debugFunctionInfo(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _DebugFunctionInfo<EncodingT> >& o);

template <class EncodingT>
bool reset_debugFunctionInfo(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _DebugFunctionInfo<EncodingT> > const& o);

NAMESPACE_END

#undef C
#undef A

#include "debugFunctionInfoInterpreter_impl.hpp"

#endif
