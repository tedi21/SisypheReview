/* 
 * cppNoticeInterpreter.hpp
 *
 *
 * @date 31-07-2022
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPNOTICE_INTERPRETER_HPP_
#define _CPPNOTICE_INTERPRETER_HPP_

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
class CppNoticeInterpreter
: public Base<EncodingT>
{
private:
	boost::shared_ptr< _CppNotice<EncodingT> > m_value;

public:
	CppNoticeInterpreter();

	CppNoticeInterpreter(boost::shared_ptr< _CppNotice<EncodingT> > const& value);

	FACTORY_PROTOTYPE12(CppNoticeInterpreter,
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
	CppNoticeInterpreter(boost::shared_ptr< Base<EncodingT> > const& description,
				boost::shared_ptr< Base<EncodingT> > const& category,
				boost::shared_ptr< Base<EncodingT> > const& ruleNumber,
				boost::shared_ptr< Base<EncodingT> > const& lineNumber,
				boost::shared_ptr< Base<EncodingT> > const& startBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthBlock,
				boost::shared_ptr< Base<EncodingT> > const& isNew,
				boost::shared_ptr< Base<EncodingT> > const& commitHash,
				boost::shared_ptr< Base<EncodingT> > const& commitDate,
				boost::shared_ptr< Base<EncodingT> > const& commitAuthor,
				boost::shared_ptr< Base<EncodingT> > const& commitLine,
				boost::shared_ptr< Base<EncodingT> > const& derogation);

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

	boost::shared_ptr< Base<EncodingT> > getIsNew() const;

	boost::shared_ptr< Base<EncodingT> > getCommitHash() const;

	boost::shared_ptr< Base<EncodingT> > getCommitDate() const;

	boost::shared_ptr< Base<EncodingT> > getCommitAuthor() const;

	boost::shared_ptr< Base<EncodingT> > getCommitLine() const;

	boost::shared_ptr< Base<EncodingT> > getDerogation() const;

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

	FACTORY_PROTOTYPE1(setIsNew, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsNew(boost::shared_ptr< Base<EncodingT> > const& isNew);

	FACTORY_PROTOTYPE1(setCommitHash, In< boost::shared_ptr< Base<EncodingT> > >)
	void setCommitHash(boost::shared_ptr< Base<EncodingT> > const& commitHash);

	FACTORY_PROTOTYPE1(setCommitDate, In< boost::shared_ptr< Base<EncodingT> > >)
	void setCommitDate(boost::shared_ptr< Base<EncodingT> > const& commitDate);

	FACTORY_PROTOTYPE1(setCommitAuthor, In< boost::shared_ptr< Base<EncodingT> > >)
	void setCommitAuthor(boost::shared_ptr< Base<EncodingT> > const& commitAuthor);

	FACTORY_PROTOTYPE1(setCommitLine, In< boost::shared_ptr< Base<EncodingT> > >)
	void setCommitLine(boost::shared_ptr< Base<EncodingT> > const& commitLine);

	FACTORY_PROTOTYPE1(setDerogation, In< boost::shared_ptr< Base<EncodingT> > >)
	void setDerogation(boost::shared_ptr< Base<EncodingT> > const& derogation);

	boost::shared_ptr< Base<EncodingT> > hasCppFile() const;

	void removeCppFile();

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( CppNoticeInterpreter, UCS("CppNotice") );
		CLASS_KEY_REGISTER12( CppNoticeInterpreter, UCS("CppNotice") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreter, boost::shared_ptr< Base<EncodingT> >, getIdentifier, const_t, UCS("CppNotice::Identifier") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreter, boost::shared_ptr< Base<EncodingT> >, getDescription, const_t, UCS("CppNotice::Description") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreter, void, setDescription, no_const_t, UCS("CppNotice::Description") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreter, boost::shared_ptr< Base<EncodingT> >, getCategory, const_t, UCS("CppNotice::Category") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreter, void, setCategory, no_const_t, UCS("CppNotice::Category") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreter, boost::shared_ptr< Base<EncodingT> >, getRuleNumber, const_t, UCS("CppNotice::RuleNumber") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreter, void, setRuleNumber, no_const_t, UCS("CppNotice::RuleNumber") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreter, void, setCppFile, no_const_t, UCS("CppNotice::CppFile") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreter, boost::shared_ptr< Base<EncodingT> >, getCppFile, no_const_t, UCS("CppNotice::CppFile") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCppFile, const_t, UCS("CppNotice::HasCppFile") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreter, void, removeCppFile, no_const_t, UCS("CppNotice::removeCppFile") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreter, boost::shared_ptr< Base<EncodingT> >, getLineNumber, const_t, UCS("CppNotice::LineNumber") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreter, void, setLineNumber, no_const_t, UCS("CppNotice::LineNumber") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreter, boost::shared_ptr< Base<EncodingT> >, getStartBlock, const_t, UCS("CppNotice::StartBlock") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreter, void, setStartBlock, no_const_t, UCS("CppNotice::StartBlock") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreter, boost::shared_ptr< Base<EncodingT> >, getLengthBlock, const_t, UCS("CppNotice::LengthBlock") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreter, void, setLengthBlock, no_const_t, UCS("CppNotice::LengthBlock") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsNew, const_t, UCS("CppNotice::IsNew") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreter, void, setIsNew, no_const_t, UCS("CppNotice::IsNew") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreter, boost::shared_ptr< Base<EncodingT> >, getCommitHash, const_t, UCS("CppNotice::CommitHash") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreter, void, setCommitHash, no_const_t, UCS("CppNotice::CommitHash") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreter, boost::shared_ptr< Base<EncodingT> >, getCommitDate, const_t, UCS("CppNotice::CommitDate") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreter, void, setCommitDate, no_const_t, UCS("CppNotice::CommitDate") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreter, boost::shared_ptr< Base<EncodingT> >, getCommitAuthor, const_t, UCS("CppNotice::CommitAuthor") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreter, void, setCommitAuthor, no_const_t, UCS("CppNotice::CommitAuthor") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreter, boost::shared_ptr< Base<EncodingT> >, getCommitLine, const_t, UCS("CppNotice::CommitLine") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreter, void, setCommitLine, no_const_t, UCS("CppNotice::CommitLine") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreter, boost::shared_ptr< Base<EncodingT> >, getDerogation, const_t, UCS("CppNotice::Derogation") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreter, void, setDerogation, no_const_t, UCS("CppNotice::Derogation") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( UCS("CppNotice") );
		CLASS_KEY_UNREGISTER12( UCS("CppNotice") );
		METHOD_KEY_UNREGISTER ( UCS("CppNotice::Identifier") );
		METHOD_KEY_UNREGISTER ( UCS("CppNotice::Description") );
		METHOD_KEY_UNREGISTER1( UCS("CppNotice::Description") );
		METHOD_KEY_UNREGISTER ( UCS("CppNotice::Category") );
		METHOD_KEY_UNREGISTER1( UCS("CppNotice::Category") );
		METHOD_KEY_UNREGISTER ( UCS("CppNotice::RuleNumber") );
		METHOD_KEY_UNREGISTER1( UCS("CppNotice::RuleNumber") );
		METHOD_KEY_UNREGISTER ( UCS("CppNotice::CppFile") );
		METHOD_KEY_UNREGISTER1( UCS("CppNotice::CppFile") );
		METHOD_KEY_UNREGISTER ( UCS("CppNotice::HasCppFile") );
		METHOD_KEY_UNREGISTER ( UCS("CppNotice::removeCppFile") );
		METHOD_KEY_UNREGISTER ( UCS("CppNotice::LineNumber") );
		METHOD_KEY_UNREGISTER1( UCS("CppNotice::LineNumber") );
		METHOD_KEY_UNREGISTER ( UCS("CppNotice::StartBlock") );
		METHOD_KEY_UNREGISTER1( UCS("CppNotice::StartBlock") );
		METHOD_KEY_UNREGISTER ( UCS("CppNotice::LengthBlock") );
		METHOD_KEY_UNREGISTER1( UCS("CppNotice::LengthBlock") );
		METHOD_KEY_UNREGISTER ( UCS("CppNotice::IsNew") );
		METHOD_KEY_UNREGISTER1( UCS("CppNotice::IsNew") );
		METHOD_KEY_UNREGISTER ( UCS("CppNotice::CommitHash") );
		METHOD_KEY_UNREGISTER1( UCS("CppNotice::CommitHash") );
		METHOD_KEY_UNREGISTER ( UCS("CppNotice::CommitDate") );
		METHOD_KEY_UNREGISTER1( UCS("CppNotice::CommitDate") );
		METHOD_KEY_UNREGISTER ( UCS("CppNotice::CommitAuthor") );
		METHOD_KEY_UNREGISTER1( UCS("CppNotice::CommitAuthor") );
		METHOD_KEY_UNREGISTER ( UCS("CppNotice::CommitLine") );
		METHOD_KEY_UNREGISTER1( UCS("CppNotice::CommitLine") );
		METHOD_KEY_UNREGISTER ( UCS("CppNotice::Derogation") );
		METHOD_KEY_UNREGISTER1( UCS("CppNotice::Derogation") );
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
