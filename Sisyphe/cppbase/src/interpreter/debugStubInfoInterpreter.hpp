/* 
 * debugStubInfoInterpreter.hpp
 *
 *
 * @date 31-07-2022
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _DEBUGSTUBINFO_INTERPRETER_HPP_
#define _DEBUGSTUBINFO_INTERPRETER_HPP_

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
class DebugFileInfoInterpreter;

template <class EncodingT>
class DebugStubInfoInterpreter
: public Base<EncodingT>
{
private:
	boost::shared_ptr< _DebugStubInfo<EncodingT> > m_value;

public:
	DebugStubInfoInterpreter();

	DebugStubInfoInterpreter(boost::shared_ptr< _DebugStubInfo<EncodingT> > const& value);

	FACTORY_PROTOTYPE2(DebugStubInfoInterpreter,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	DebugStubInfoInterpreter(boost::shared_ptr< Base<EncodingT> > const& lineNumber,
				boost::shared_ptr< Base<EncodingT> > const& isLineSkipped);

	boost::shared_ptr< _DebugStubInfo<EncodingT> > value() const;

	void value(boost::shared_ptr< _DebugStubInfo<EncodingT> > const& value);

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getIdentifier() const;

	boost::shared_ptr< Base<EncodingT> > getLineNumber() const;

	boost::shared_ptr< Base<EncodingT> > getIsLineSkipped() const;

	boost::shared_ptr< Base<EncodingT> > getDebugFileInfo();

	FACTORY_PROTOTYPE1(setLineNumber, In< boost::shared_ptr< Base<EncodingT> > >)
	void setLineNumber(boost::shared_ptr< Base<EncodingT> > const& lineNumber);

	FACTORY_PROTOTYPE1(setIsLineSkipped, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsLineSkipped(boost::shared_ptr< Base<EncodingT> > const& isLineSkipped);

	FACTORY_PROTOTYPE1(setDebugFileInfo, In< boost::shared_ptr< Base<EncodingT> > >)
	void setDebugFileInfo(boost::shared_ptr< Base<EncodingT> > const& debugFileInfo);

	boost::shared_ptr< Base<EncodingT> > hasDebugFileInfo() const;

	void removeDebugFileInfo();

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
		CLASS_KEY_REGISTER ( DebugStubInfoInterpreter, UCS("DebugStubInfo") );
		CLASS_KEY_REGISTER2( DebugStubInfoInterpreter, UCS("DebugStubInfo") );
		METHOD_KEY_REGISTER ( DebugStubInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getIdentifier, const_t, UCS("DebugStubInfo::Identifier") );
		METHOD_KEY_REGISTER ( DebugStubInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getLineNumber, const_t, UCS("DebugStubInfo::LineNumber") );
		METHOD_KEY_REGISTER1( DebugStubInfoInterpreter, void, setLineNumber, no_const_t, UCS("DebugStubInfo::LineNumber") );
		METHOD_KEY_REGISTER ( DebugStubInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsLineSkipped, const_t, UCS("DebugStubInfo::IsLineSkipped") );
		METHOD_KEY_REGISTER1( DebugStubInfoInterpreter, void, setIsLineSkipped, no_const_t, UCS("DebugStubInfo::IsLineSkipped") );
		METHOD_KEY_REGISTER1( DebugStubInfoInterpreter, void, setDebugFileInfo, no_const_t, UCS("DebugStubInfo::DebugFileInfo") );
		METHOD_KEY_REGISTER ( DebugStubInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getDebugFileInfo, no_const_t, UCS("DebugStubInfo::DebugFileInfo") );
		METHOD_KEY_REGISTER ( DebugStubInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, hasDebugFileInfo, const_t, UCS("DebugStubInfo::HasDebugFileInfo") );
		METHOD_KEY_REGISTER ( DebugStubInfoInterpreter, void, removeDebugFileInfo, no_const_t, UCS("DebugStubInfo::removeDebugFileInfo") );
		METHOD_KEY_REGISTER1( DebugStubInfoInterpreter, void, removeDebugValueInfo, no_const_t, UCS("DebugStubInfo::removeDebugValueInfos") );
		METHOD_KEY_REGISTER2( DebugStubInfoInterpreter, void, insertDebugValueInfo, no_const_t, UCS("DebugStubInfo::DebugValueInfos") );
		METHOD_KEY_REGISTER1( DebugStubInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getDebugValueInfo, no_const_t, UCS("DebugStubInfo::DebugValueInfos") );
		METHOD_KEY_REGISTER ( DebugStubInfoInterpreter, void, clearDebugValueInfos, no_const_t, UCS("DebugStubInfo::ClearDebugValueInfos") );
		METHOD_KEY_REGISTER ( DebugStubInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, hasDebugValueInfos, const_t, UCS("DebugStubInfo::HasDebugValueInfos") );
		METHOD_KEY_REGISTER ( DebugStubInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, debugValueInfosCount, const_t, UCS("DebugStubInfo::DebugValueInfosCount") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( UCS("DebugStubInfo") );
		CLASS_KEY_UNREGISTER2( UCS("DebugStubInfo") );
		METHOD_KEY_UNREGISTER ( UCS("DebugStubInfo::Identifier") );
		METHOD_KEY_UNREGISTER ( UCS("DebugStubInfo::LineNumber") );
		METHOD_KEY_UNREGISTER1( UCS("DebugStubInfo::LineNumber") );
		METHOD_KEY_UNREGISTER ( UCS("DebugStubInfo::IsLineSkipped") );
		METHOD_KEY_UNREGISTER1( UCS("DebugStubInfo::IsLineSkipped") );
		METHOD_KEY_UNREGISTER ( UCS("DebugStubInfo::DebugFileInfo") );
		METHOD_KEY_UNREGISTER1( UCS("DebugStubInfo::DebugFileInfo") );
		METHOD_KEY_UNREGISTER ( UCS("DebugStubInfo::HasDebugFileInfo") );
		METHOD_KEY_UNREGISTER ( UCS("DebugStubInfo::removeDebugFileInfo") );
		METHOD_KEY_UNREGISTER1( UCS("DebugStubInfo::removeDebugValueInfos") );
		METHOD_KEY_UNREGISTER2( UCS("DebugStubInfo::DebugValueInfos") );
		METHOD_KEY_UNREGISTER1( UCS("DebugStubInfo::DebugValueInfos") );
		METHOD_KEY_UNREGISTER ( UCS("DebugStubInfo::ClearDebugValueInfos") );
		METHOD_KEY_UNREGISTER ( UCS("DebugStubInfo::HasDebugValueInfos") );
		METHOD_KEY_UNREGISTER ( UCS("DebugStubInfo::DebugValueInfosCount") );
	FACTORY_END_UNREGISTER
};

template <class EncodingT>
bool check_debugStubInfo(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _DebugStubInfo<EncodingT> >& o);

template <class EncodingT>
bool reset_debugStubInfo(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _DebugStubInfo<EncodingT> > const& o);

NAMESPACE_END

#undef C
#undef A

#include "debugStubInfoInterpreter_impl.hpp"

#endif
