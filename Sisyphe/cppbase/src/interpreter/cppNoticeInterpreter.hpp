/* 
 * cppNoticeInterpreter.hpp
 *
 *
 * @date 10-05-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPNOTICE_INTERPRETER_HPP_
#define _CPPNOTICE_INTERPRETER_HPP_

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
class CppFileInterpreter;

template <class EncodingT>
class CppNoticeInterpreter
: public Base<EncodingT>
{
private:
	boost::shared_ptr< _CppNotice<EncodingT> > m_value;

public:
	CppNoticeInterpreter();

	CppNoticeInterpreter(boost::shared_ptr< _CppNotice<EncodingT> > const& value);

	FACTORY_PROTOTYPE6(CppNoticeInterpreter,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	CppNoticeInterpreter(boost::shared_ptr< Base<EncodingT> > const& description,
				boost::shared_ptr< Base<EncodingT> > const& category,
				boost::shared_ptr< Base<EncodingT> > const& ruleNumber,
				boost::shared_ptr< Base<EncodingT> > const& lineNumber,
				boost::shared_ptr< Base<EncodingT> > const& startBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthBlock);

	boost::shared_ptr< _CppNotice<EncodingT> > value() const;

	void value(boost::shared_ptr< _CppNotice<EncodingT> > const& value);

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getIdentifier() const;

	boost::shared_ptr< Base<EncodingT> > getDescription() const;

	boost::shared_ptr< Base<EncodingT> > getCategory() const;

	boost::shared_ptr< Base<EncodingT> > getRuleNumber() const;

	boost::shared_ptr< Base<EncodingT> > getLineNumber() const;

	boost::shared_ptr< Base<EncodingT> > getStartBlock() const;

	boost::shared_ptr< Base<EncodingT> > getLengthBlock() const;

	boost::shared_ptr< Base<EncodingT> > getCppFile();

	FACTORY_PROTOTYPE1(setDescription, In< boost::shared_ptr< Base<EncodingT> > >)
	void setDescription(boost::shared_ptr< Base<EncodingT> > const& description);

	FACTORY_PROTOTYPE1(setCategory, In< boost::shared_ptr< Base<EncodingT> > >)
	void setCategory(boost::shared_ptr< Base<EncodingT> > const& category);

	FACTORY_PROTOTYPE1(setRuleNumber, In< boost::shared_ptr< Base<EncodingT> > >)
	void setRuleNumber(boost::shared_ptr< Base<EncodingT> > const& ruleNumber);

	FACTORY_PROTOTYPE1(setCppFile, In< boost::shared_ptr< Base<EncodingT> > >)
	void setCppFile(boost::shared_ptr< Base<EncodingT> > const& cppFile);

	FACTORY_PROTOTYPE1(setLineNumber, In< boost::shared_ptr< Base<EncodingT> > >)
	void setLineNumber(boost::shared_ptr< Base<EncodingT> > const& lineNumber);

	FACTORY_PROTOTYPE1(setStartBlock, In< boost::shared_ptr< Base<EncodingT> > >)
	void setStartBlock(boost::shared_ptr< Base<EncodingT> > const& startBlock);

	FACTORY_PROTOTYPE1(setLengthBlock, In< boost::shared_ptr< Base<EncodingT> > >)
	void setLengthBlock(boost::shared_ptr< Base<EncodingT> > const& lengthBlock);

	boost::shared_ptr< Base<EncodingT> > hasCppFile() const;

	void removeCppFile();

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( CppNoticeInterpreter, C("CppNotice") );
		CLASS_KEY_REGISTER6( CppNoticeInterpreter, C("CppNotice") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreter, boost::shared_ptr< Base<EncodingT> >, getIdentifier, const_t, C("CppNotice::Identifier") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreter, boost::shared_ptr< Base<EncodingT> >, getDescription, const_t, C("CppNotice::Description") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreter, void, setDescription, no_const_t, C("CppNotice::Description") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreter, boost::shared_ptr< Base<EncodingT> >, getCategory, const_t, C("CppNotice::Category") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreter, void, setCategory, no_const_t, C("CppNotice::Category") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreter, boost::shared_ptr< Base<EncodingT> >, getRuleNumber, const_t, C("CppNotice::RuleNumber") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreter, void, setRuleNumber, no_const_t, C("CppNotice::RuleNumber") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreter, void, setCppFile, no_const_t, C("CppNotice::CppFile") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreter, boost::shared_ptr< Base<EncodingT> >, getCppFile, no_const_t, C("CppNotice::CppFile") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCppFile, const_t, C("CppNotice::HasCppFile") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreter, void, removeCppFile, no_const_t, C("CppNotice::removeCppFile") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreter, boost::shared_ptr< Base<EncodingT> >, getLineNumber, const_t, C("CppNotice::LineNumber") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreter, void, setLineNumber, no_const_t, C("CppNotice::LineNumber") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreter, boost::shared_ptr< Base<EncodingT> >, getStartBlock, const_t, C("CppNotice::StartBlock") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreter, void, setStartBlock, no_const_t, C("CppNotice::StartBlock") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreter, boost::shared_ptr< Base<EncodingT> >, getLengthBlock, const_t, C("CppNotice::LengthBlock") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreter, void, setLengthBlock, no_const_t, C("CppNotice::LengthBlock") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( C("CppNotice") );
		CLASS_KEY_UNREGISTER6( C("CppNotice") );
		METHOD_KEY_UNREGISTER ( C("CppNotice::Identifier") );
		METHOD_KEY_UNREGISTER ( C("CppNotice::Description") );
		METHOD_KEY_UNREGISTER1( C("CppNotice::Description") );
		METHOD_KEY_UNREGISTER ( C("CppNotice::Category") );
		METHOD_KEY_UNREGISTER1( C("CppNotice::Category") );
		METHOD_KEY_UNREGISTER ( C("CppNotice::RuleNumber") );
		METHOD_KEY_UNREGISTER1( C("CppNotice::RuleNumber") );
		METHOD_KEY_UNREGISTER ( C("CppNotice::CppFile") );
		METHOD_KEY_UNREGISTER1( C("CppNotice::CppFile") );
		METHOD_KEY_UNREGISTER ( C("CppNotice::HasCppFile") );
		METHOD_KEY_UNREGISTER ( C("CppNotice::removeCppFile") );
		METHOD_KEY_UNREGISTER ( C("CppNotice::LineNumber") );
		METHOD_KEY_UNREGISTER1( C("CppNotice::LineNumber") );
		METHOD_KEY_UNREGISTER ( C("CppNotice::StartBlock") );
		METHOD_KEY_UNREGISTER1( C("CppNotice::StartBlock") );
		METHOD_KEY_UNREGISTER ( C("CppNotice::LengthBlock") );
		METHOD_KEY_UNREGISTER1( C("CppNotice::LengthBlock") );
	FACTORY_END_UNREGISTER
};

template <class EncodingT>
bool check_cppNotice(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _CppNotice<EncodingT> >& o);

template <class EncodingT>
bool reset_cppNotice(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _CppNotice<EncodingT> > const& o);

NAMESPACE_END

#undef C
#undef A

#include "cppNoticeInterpreter_impl.hpp"

#endif
