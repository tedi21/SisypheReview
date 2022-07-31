/* 
 * cppIncludeInterpreter.hpp
 *
 *
 * @date 31-07-2022
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPINCLUDE_INTERPRETER_HPP_
#define _CPPINCLUDE_INTERPRETER_HPP_

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
class CppFileInterpreter;

template <class EncodingT>
class CppIncludeInterpreter
: public Base<EncodingT>
{
private:
	boost::shared_ptr< _CppInclude<EncodingT> > m_value;

public:
	CppIncludeInterpreter();

	CppIncludeInterpreter(boost::shared_ptr< _CppInclude<EncodingT> > const& value);

	FACTORY_PROTOTYPE2(CppIncludeInterpreter,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	CppIncludeInterpreter(boost::shared_ptr< Base<EncodingT> > const& fileName,
				boost::shared_ptr< Base<EncodingT> > const& lineNumber);

	boost::shared_ptr< _CppInclude<EncodingT> > value() const;

	void value(boost::shared_ptr< _CppInclude<EncodingT> > const& value);

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getIdentifier() const;

	boost::shared_ptr< Base<EncodingT> > getFileName() const;

	boost::shared_ptr< Base<EncodingT> > getLineNumber() const;

	boost::shared_ptr< Base<EncodingT> > getCppFile();

	FACTORY_PROTOTYPE1(setFileName, In< boost::shared_ptr< Base<EncodingT> > >)
	void setFileName(boost::shared_ptr< Base<EncodingT> > const& fileName);

	FACTORY_PROTOTYPE1(setCppFile, In< boost::shared_ptr< Base<EncodingT> > >)
	void setCppFile(boost::shared_ptr< Base<EncodingT> > const& cppFile);

	FACTORY_PROTOTYPE1(setLineNumber, In< boost::shared_ptr< Base<EncodingT> > >)
	void setLineNumber(boost::shared_ptr< Base<EncodingT> > const& lineNumber);

	boost::shared_ptr< Base<EncodingT> > hasCppFile() const;

	void removeCppFile();

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( CppIncludeInterpreter, UCS("CppInclude") );
		CLASS_KEY_REGISTER2( CppIncludeInterpreter, UCS("CppInclude") );
		METHOD_KEY_REGISTER ( CppIncludeInterpreter, boost::shared_ptr< Base<EncodingT> >, getIdentifier, const_t, UCS("CppInclude::Identifier") );
		METHOD_KEY_REGISTER ( CppIncludeInterpreter, boost::shared_ptr< Base<EncodingT> >, getFileName, const_t, UCS("CppInclude::FileName") );
		METHOD_KEY_REGISTER1( CppIncludeInterpreter, void, setFileName, no_const_t, UCS("CppInclude::FileName") );
		METHOD_KEY_REGISTER1( CppIncludeInterpreter, void, setCppFile, no_const_t, UCS("CppInclude::CppFile") );
		METHOD_KEY_REGISTER ( CppIncludeInterpreter, boost::shared_ptr< Base<EncodingT> >, getCppFile, no_const_t, UCS("CppInclude::CppFile") );
		METHOD_KEY_REGISTER ( CppIncludeInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCppFile, const_t, UCS("CppInclude::HasCppFile") );
		METHOD_KEY_REGISTER ( CppIncludeInterpreter, void, removeCppFile, no_const_t, UCS("CppInclude::removeCppFile") );
		METHOD_KEY_REGISTER ( CppIncludeInterpreter, boost::shared_ptr< Base<EncodingT> >, getLineNumber, const_t, UCS("CppInclude::LineNumber") );
		METHOD_KEY_REGISTER1( CppIncludeInterpreter, void, setLineNumber, no_const_t, UCS("CppInclude::LineNumber") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( UCS("CppInclude") );
		CLASS_KEY_UNREGISTER2( UCS("CppInclude") );
		METHOD_KEY_UNREGISTER ( UCS("CppInclude::Identifier") );
		METHOD_KEY_UNREGISTER ( UCS("CppInclude::FileName") );
		METHOD_KEY_UNREGISTER1( UCS("CppInclude::FileName") );
		METHOD_KEY_UNREGISTER ( UCS("CppInclude::CppFile") );
		METHOD_KEY_UNREGISTER1( UCS("CppInclude::CppFile") );
		METHOD_KEY_UNREGISTER ( UCS("CppInclude::HasCppFile") );
		METHOD_KEY_UNREGISTER ( UCS("CppInclude::removeCppFile") );
		METHOD_KEY_UNREGISTER ( UCS("CppInclude::LineNumber") );
		METHOD_KEY_UNREGISTER1( UCS("CppInclude::LineNumber") );
	FACTORY_END_UNREGISTER
};

template <class EncodingT>
bool check_cppInclude(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _CppInclude<EncodingT> >& o);

template <class EncodingT>
bool reset_cppInclude(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _CppInclude<EncodingT> > const& o);

NAMESPACE_END

#undef C
#undef A

#include "cppIncludeInterpreter_impl.hpp"

#endif
