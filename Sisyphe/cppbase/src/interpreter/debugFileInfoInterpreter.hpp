/* 
 * debugFileInfoInterpreter.hpp
 *
 *
 * @date 10-05-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _DEBUGFILEINFO_INTERPRETER_HPP_
#define _DEBUGFILEINFO_INTERPRETER_HPP_

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
class DebugFunctionInfoInterpreter;

template <class EncodingT>
class DebugStubInfoInterpreter;

template <class EncodingT>
class TextFileInterpreter;

template <class EncodingT>
class DebugFileInfoInterpreter
: public Base<EncodingT>
{
private:
	boost::shared_ptr< _DebugFileInfo<EncodingT> > m_value;

public:
	DebugFileInfoInterpreter();

	DebugFileInfoInterpreter(boost::shared_ptr< _DebugFileInfo<EncodingT> > const& value);

	FACTORY_PROTOTYPE3(DebugFileInfoInterpreter,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	DebugFileInfoInterpreter(boost::shared_ptr< Base<EncodingT> > const& name,
				boost::shared_ptr< Base<EncodingT> > const& compilandPath,
				boost::shared_ptr< Base<EncodingT> > const& checksum);

	boost::shared_ptr< _DebugFileInfo<EncodingT> > value() const;

	void value(boost::shared_ptr< _DebugFileInfo<EncodingT> > const& value);

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getIdentifier() const;

	boost::shared_ptr< Base<EncodingT> > getName() const;

	boost::shared_ptr< Base<EncodingT> > getCompilandPath() const;

	boost::shared_ptr< Base<EncodingT> > getChecksum() const;

	boost::shared_ptr< Base<EncodingT> > getTextFile();

	FACTORY_PROTOTYPE1(setTextFile, In< boost::shared_ptr< Base<EncodingT> > >)
	void setTextFile(boost::shared_ptr< Base<EncodingT> > const& textFile);

	FACTORY_PROTOTYPE1(setName, In< boost::shared_ptr< Base<EncodingT> > >)
	void setName(boost::shared_ptr< Base<EncodingT> > const& name);

	FACTORY_PROTOTYPE1(setCompilandPath, In< boost::shared_ptr< Base<EncodingT> > >)
	void setCompilandPath(boost::shared_ptr< Base<EncodingT> > const& compilandPath);

	FACTORY_PROTOTYPE1(setChecksum, In< boost::shared_ptr< Base<EncodingT> > >)
	void setChecksum(boost::shared_ptr< Base<EncodingT> > const& checksum);

	boost::shared_ptr< Base<EncodingT> > hasTextFile() const;

	void removeTextFile();

	FACTORY_PROTOTYPE1(removeDebugFunctionInfo, In< boost::shared_ptr< Base<EncodingT> > >)
	void removeDebugFunctionInfo(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE1(removeDebugStubInfo, In< boost::shared_ptr< Base<EncodingT> > >)
	void removeDebugStubInfo(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE2(insertDebugFunctionInfo, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void insertDebugFunctionInfo(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& debugFunctionInfo);

	FACTORY_PROTOTYPE2(insertDebugStubInfo, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void insertDebugStubInfo(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& debugStubInfo);

	FACTORY_PROTOTYPE1(getDebugFunctionInfo, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getDebugFunctionInfo(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE1(getDebugStubInfo, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getDebugStubInfo(boost::shared_ptr< Base<EncodingT> > const& n);

	void clearDebugFunctionInfos();

	void clearDebugStubInfos();

	boost::shared_ptr< Base<EncodingT> > hasDebugFunctionInfos() const;

	boost::shared_ptr< Base<EncodingT> > hasDebugStubInfos() const;

	boost::shared_ptr< Base<EncodingT> > debugFunctionInfosCount() const;

	boost::shared_ptr< Base<EncodingT> > debugStubInfosCount() const;

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( DebugFileInfoInterpreter, UCS("DebugFileInfo") );
		CLASS_KEY_REGISTER3( DebugFileInfoInterpreter, UCS("DebugFileInfo") );
		METHOD_KEY_REGISTER ( DebugFileInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getIdentifier, const_t, UCS("DebugFileInfo::Identifier") );
		METHOD_KEY_REGISTER1( DebugFileInfoInterpreter, void, setTextFile, no_const_t, UCS("DebugFileInfo::TextFile") );
		METHOD_KEY_REGISTER ( DebugFileInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getTextFile, no_const_t, UCS("DebugFileInfo::TextFile") );
		METHOD_KEY_REGISTER ( DebugFileInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, hasTextFile, const_t, UCS("DebugFileInfo::HasTextFile") );
		METHOD_KEY_REGISTER ( DebugFileInfoInterpreter, void, removeTextFile, no_const_t, UCS("DebugFileInfo::removeTextFile") );
		METHOD_KEY_REGISTER ( DebugFileInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getName, const_t, UCS("DebugFileInfo::Name") );
		METHOD_KEY_REGISTER1( DebugFileInfoInterpreter, void, setName, no_const_t, UCS("DebugFileInfo::Name") );
		METHOD_KEY_REGISTER ( DebugFileInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getCompilandPath, const_t, UCS("DebugFileInfo::CompilandPath") );
		METHOD_KEY_REGISTER1( DebugFileInfoInterpreter, void, setCompilandPath, no_const_t, UCS("DebugFileInfo::CompilandPath") );
		METHOD_KEY_REGISTER ( DebugFileInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getChecksum, const_t, UCS("DebugFileInfo::Checksum") );
		METHOD_KEY_REGISTER1( DebugFileInfoInterpreter, void, setChecksum, no_const_t, UCS("DebugFileInfo::Checksum") );
		METHOD_KEY_REGISTER1( DebugFileInfoInterpreter, void, removeDebugFunctionInfo, no_const_t, UCS("DebugFileInfo::removeDebugFunctionInfos") );
		METHOD_KEY_REGISTER2( DebugFileInfoInterpreter, void, insertDebugFunctionInfo, no_const_t, UCS("DebugFileInfo::DebugFunctionInfos") );
		METHOD_KEY_REGISTER1( DebugFileInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getDebugFunctionInfo, no_const_t, UCS("DebugFileInfo::DebugFunctionInfos") );
		METHOD_KEY_REGISTER ( DebugFileInfoInterpreter, void, clearDebugFunctionInfos, no_const_t, UCS("DebugFileInfo::ClearDebugFunctionInfos") );
		METHOD_KEY_REGISTER ( DebugFileInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, hasDebugFunctionInfos, const_t, UCS("DebugFileInfo::HasDebugFunctionInfos") );
		METHOD_KEY_REGISTER ( DebugFileInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, debugFunctionInfosCount, const_t, UCS("DebugFileInfo::DebugFunctionInfosCount") );
		METHOD_KEY_REGISTER1( DebugFileInfoInterpreter, void, removeDebugStubInfo, no_const_t, UCS("DebugFileInfo::removeDebugStubInfos") );
		METHOD_KEY_REGISTER2( DebugFileInfoInterpreter, void, insertDebugStubInfo, no_const_t, UCS("DebugFileInfo::DebugStubInfos") );
		METHOD_KEY_REGISTER1( DebugFileInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, getDebugStubInfo, no_const_t, UCS("DebugFileInfo::DebugStubInfos") );
		METHOD_KEY_REGISTER ( DebugFileInfoInterpreter, void, clearDebugStubInfos, no_const_t, UCS("DebugFileInfo::ClearDebugStubInfos") );
		METHOD_KEY_REGISTER ( DebugFileInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, hasDebugStubInfos, const_t, UCS("DebugFileInfo::HasDebugStubInfos") );
		METHOD_KEY_REGISTER ( DebugFileInfoInterpreter, boost::shared_ptr< Base<EncodingT> >, debugStubInfosCount, const_t, UCS("DebugFileInfo::DebugStubInfosCount") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( UCS("DebugFileInfo") );
		CLASS_KEY_UNREGISTER3( UCS("DebugFileInfo") );
		METHOD_KEY_UNREGISTER ( UCS("DebugFileInfo::Identifier") );
		METHOD_KEY_UNREGISTER ( UCS("DebugFileInfo::TextFile") );
		METHOD_KEY_UNREGISTER1( UCS("DebugFileInfo::TextFile") );
		METHOD_KEY_UNREGISTER ( UCS("DebugFileInfo::HasTextFile") );
		METHOD_KEY_UNREGISTER ( UCS("DebugFileInfo::removeTextFile") );
		METHOD_KEY_UNREGISTER ( UCS("DebugFileInfo::Name") );
		METHOD_KEY_UNREGISTER1( UCS("DebugFileInfo::Name") );
		METHOD_KEY_UNREGISTER ( UCS("DebugFileInfo::CompilandPath") );
		METHOD_KEY_UNREGISTER1( UCS("DebugFileInfo::CompilandPath") );
		METHOD_KEY_UNREGISTER ( UCS("DebugFileInfo::Checksum") );
		METHOD_KEY_UNREGISTER1( UCS("DebugFileInfo::Checksum") );
		METHOD_KEY_UNREGISTER1( UCS("DebugFileInfo::removeDebugFunctionInfos") );
		METHOD_KEY_UNREGISTER2( UCS("DebugFileInfo::DebugFunctionInfos") );
		METHOD_KEY_UNREGISTER1( UCS("DebugFileInfo::DebugFunctionInfos") );
		METHOD_KEY_UNREGISTER ( UCS("DebugFileInfo::ClearDebugFunctionInfos") );
		METHOD_KEY_UNREGISTER ( UCS("DebugFileInfo::HasDebugFunctionInfos") );
		METHOD_KEY_UNREGISTER ( UCS("DebugFileInfo::DebugFunctionInfosCount") );
		METHOD_KEY_UNREGISTER1( UCS("DebugFileInfo::removeDebugStubInfos") );
		METHOD_KEY_UNREGISTER2( UCS("DebugFileInfo::DebugStubInfos") );
		METHOD_KEY_UNREGISTER1( UCS("DebugFileInfo::DebugStubInfos") );
		METHOD_KEY_UNREGISTER ( UCS("DebugFileInfo::ClearDebugStubInfos") );
		METHOD_KEY_UNREGISTER ( UCS("DebugFileInfo::HasDebugStubInfos") );
		METHOD_KEY_UNREGISTER ( UCS("DebugFileInfo::DebugStubInfosCount") );
	FACTORY_END_UNREGISTER
};

template <class EncodingT>
bool check_debugFileInfo(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _DebugFileInfo<EncodingT> >& o);

template <class EncodingT>
bool reset_debugFileInfo(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _DebugFileInfo<EncodingT> > const& o);

NAMESPACE_END

#undef C
#undef A

#include "debugFileInfoInterpreter_impl.hpp"

#endif
