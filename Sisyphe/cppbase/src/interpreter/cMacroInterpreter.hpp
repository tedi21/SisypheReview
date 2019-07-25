/* 
 * cMacroInterpreter.hpp
 *
 *
 * @date 26-03-2019
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CMACRO_INTERPRETER_HPP_
#define _CMACRO_INTERPRETER_HPP_

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
class CMacroInterpreter
: public Base<EncodingT>
{
private:
	boost::shared_ptr< _CMacro<EncodingT> > m_value;

public:
	CMacroInterpreter();

	CMacroInterpreter(boost::shared_ptr< _CMacro<EncodingT> > const& value);

	FACTORY_PROTOTYPE6(CMacroInterpreter,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	CMacroInterpreter(boost::shared_ptr< Base<EncodingT> > const& name,
				boost::shared_ptr< Base<EncodingT> > const& isConst,
				boost::shared_ptr< Base<EncodingT> > const& constValue,
				boost::shared_ptr< Base<EncodingT> > const& lineNumber,
				boost::shared_ptr< Base<EncodingT> > const& startBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthBlock);

	boost::shared_ptr< _CMacro<EncodingT> > value() const;

	void value(boost::shared_ptr< _CMacro<EncodingT> > const& value);

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getIdentifier() const;

	boost::shared_ptr< Base<EncodingT> > getName() const;

	boost::shared_ptr< Base<EncodingT> > getIsConst() const;

	boost::shared_ptr< Base<EncodingT> > getConstValue() const;

	boost::shared_ptr< Base<EncodingT> > getLineNumber() const;

	boost::shared_ptr< Base<EncodingT> > getStartBlock() const;

	boost::shared_ptr< Base<EncodingT> > getLengthBlock() const;

	boost::shared_ptr< Base<EncodingT> > getCppFile();

	FACTORY_PROTOTYPE1(setName, In< boost::shared_ptr< Base<EncodingT> > >)
	void setName(boost::shared_ptr< Base<EncodingT> > const& name);

	FACTORY_PROTOTYPE1(setIsConst, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsConst(boost::shared_ptr< Base<EncodingT> > const& isConst);

	FACTORY_PROTOTYPE1(setConstValue, In< boost::shared_ptr< Base<EncodingT> > >)
	void setConstValue(boost::shared_ptr< Base<EncodingT> > const& constValue);

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
		CLASS_KEY_REGISTER ( CMacroInterpreter, C("CMacro") );
		CLASS_KEY_REGISTER6( CMacroInterpreter, C("CMacro") );
		METHOD_KEY_REGISTER ( CMacroInterpreter, boost::shared_ptr< Base<EncodingT> >, getIdentifier, const_t, C("CMacro::Identifier") );
		METHOD_KEY_REGISTER ( CMacroInterpreter, boost::shared_ptr< Base<EncodingT> >, getName, const_t, C("CMacro::Name") );
		METHOD_KEY_REGISTER1( CMacroInterpreter, void, setName, no_const_t, C("CMacro::Name") );
		METHOD_KEY_REGISTER ( CMacroInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsConst, const_t, C("CMacro::IsConst") );
		METHOD_KEY_REGISTER1( CMacroInterpreter, void, setIsConst, no_const_t, C("CMacro::IsConst") );
		METHOD_KEY_REGISTER ( CMacroInterpreter, boost::shared_ptr< Base<EncodingT> >, getConstValue, const_t, C("CMacro::ConstValue") );
		METHOD_KEY_REGISTER1( CMacroInterpreter, void, setConstValue, no_const_t, C("CMacro::ConstValue") );
		METHOD_KEY_REGISTER1( CMacroInterpreter, void, setCppFile, no_const_t, C("CMacro::CppFile") );
		METHOD_KEY_REGISTER ( CMacroInterpreter, boost::shared_ptr< Base<EncodingT> >, getCppFile, no_const_t, C("CMacro::CppFile") );
		METHOD_KEY_REGISTER ( CMacroInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCppFile, const_t, C("CMacro::HasCppFile") );
		METHOD_KEY_REGISTER ( CMacroInterpreter, void, removeCppFile, no_const_t, C("CMacro::removeCppFile") );
		METHOD_KEY_REGISTER ( CMacroInterpreter, boost::shared_ptr< Base<EncodingT> >, getLineNumber, const_t, C("CMacro::LineNumber") );
		METHOD_KEY_REGISTER1( CMacroInterpreter, void, setLineNumber, no_const_t, C("CMacro::LineNumber") );
		METHOD_KEY_REGISTER ( CMacroInterpreter, boost::shared_ptr< Base<EncodingT> >, getStartBlock, const_t, C("CMacro::StartBlock") );
		METHOD_KEY_REGISTER1( CMacroInterpreter, void, setStartBlock, no_const_t, C("CMacro::StartBlock") );
		METHOD_KEY_REGISTER ( CMacroInterpreter, boost::shared_ptr< Base<EncodingT> >, getLengthBlock, const_t, C("CMacro::LengthBlock") );
		METHOD_KEY_REGISTER1( CMacroInterpreter, void, setLengthBlock, no_const_t, C("CMacro::LengthBlock") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( C("CMacro") );
		CLASS_KEY_UNREGISTER6( C("CMacro") );
		METHOD_KEY_UNREGISTER ( C("CMacro::Identifier") );
		METHOD_KEY_UNREGISTER ( C("CMacro::Name") );
		METHOD_KEY_UNREGISTER1( C("CMacro::Name") );
		METHOD_KEY_UNREGISTER ( C("CMacro::IsConst") );
		METHOD_KEY_UNREGISTER1( C("CMacro::IsConst") );
		METHOD_KEY_UNREGISTER ( C("CMacro::ConstValue") );
		METHOD_KEY_UNREGISTER1( C("CMacro::ConstValue") );
		METHOD_KEY_UNREGISTER ( C("CMacro::CppFile") );
		METHOD_KEY_UNREGISTER1( C("CMacro::CppFile") );
		METHOD_KEY_UNREGISTER ( C("CMacro::HasCppFile") );
		METHOD_KEY_UNREGISTER ( C("CMacro::removeCppFile") );
		METHOD_KEY_UNREGISTER ( C("CMacro::LineNumber") );
		METHOD_KEY_UNREGISTER1( C("CMacro::LineNumber") );
		METHOD_KEY_UNREGISTER ( C("CMacro::StartBlock") );
		METHOD_KEY_UNREGISTER1( C("CMacro::StartBlock") );
		METHOD_KEY_UNREGISTER ( C("CMacro::LengthBlock") );
		METHOD_KEY_UNREGISTER1( C("CMacro::LengthBlock") );
	FACTORY_END_UNREGISTER
};

template <class EncodingT>
bool check_cMacro(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _CMacro<EncodingT> >& o);

template <class EncodingT>
bool reset_cMacro(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _CMacro<EncodingT> > const& o);

NAMESPACE_END

#undef C
#undef A

#include "cMacroInterpreter_impl.hpp"

#endif
