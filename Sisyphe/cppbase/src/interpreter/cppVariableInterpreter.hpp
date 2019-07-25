/* 
 * cppVariableInterpreter.hpp
 *
 *
 * @date 26-03-2019
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPVARIABLE_INTERPRETER_HPP_
#define _CPPVARIABLE_INTERPRETER_HPP_

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
class CppFunctionInterpreter;

template <class EncodingT>
class CppFileInterpreter;

template <class EncodingT>
class CppVariableInterpreter
: public Base<EncodingT>
{
private:
	boost::shared_ptr< _CppVariable<EncodingT> > m_value;

public:
	CppVariableInterpreter();

	CppVariableInterpreter(boost::shared_ptr< _CppVariable<EncodingT> > const& value);

	FACTORY_PROTOTYPE8(CppVariableInterpreter,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	CppVariableInterpreter(boost::shared_ptr< Base<EncodingT> > const& varType,
				boost::shared_ptr< Base<EncodingT> > const& name,
				boost::shared_ptr< Base<EncodingT> > const& isStatic,
				boost::shared_ptr< Base<EncodingT> > const& isConst,
				boost::shared_ptr< Base<EncodingT> > const& isConstexpr,
				boost::shared_ptr< Base<EncodingT> > const& lineNumber,
				boost::shared_ptr< Base<EncodingT> > const& startBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthBlock);

	boost::shared_ptr< _CppVariable<EncodingT> > value() const;

	void value(boost::shared_ptr< _CppVariable<EncodingT> > const& value);

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getIdentifier() const;

	boost::shared_ptr< Base<EncodingT> > getVarType() const;

	boost::shared_ptr< Base<EncodingT> > getName() const;

	boost::shared_ptr< Base<EncodingT> > getIsStatic() const;

	boost::shared_ptr< Base<EncodingT> > getIsConst() const;

	boost::shared_ptr< Base<EncodingT> > getIsConstexpr() const;

	boost::shared_ptr< Base<EncodingT> > getLineNumber() const;

	boost::shared_ptr< Base<EncodingT> > getStartBlock() const;

	boost::shared_ptr< Base<EncodingT> > getLengthBlock() const;

	boost::shared_ptr< Base<EncodingT> > getCppFunction();

	boost::shared_ptr< Base<EncodingT> > getCppFile();

	FACTORY_PROTOTYPE1(setVarType, In< boost::shared_ptr< Base<EncodingT> > >)
	void setVarType(boost::shared_ptr< Base<EncodingT> > const& varType);

	FACTORY_PROTOTYPE1(setName, In< boost::shared_ptr< Base<EncodingT> > >)
	void setName(boost::shared_ptr< Base<EncodingT> > const& name);

	FACTORY_PROTOTYPE1(setIsStatic, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsStatic(boost::shared_ptr< Base<EncodingT> > const& isStatic);

	FACTORY_PROTOTYPE1(setIsConst, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsConst(boost::shared_ptr< Base<EncodingT> > const& isConst);

	FACTORY_PROTOTYPE1(setIsConstexpr, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsConstexpr(boost::shared_ptr< Base<EncodingT> > const& isConstexpr);

	FACTORY_PROTOTYPE1(setCppFunction, In< boost::shared_ptr< Base<EncodingT> > >)
	void setCppFunction(boost::shared_ptr< Base<EncodingT> > const& cppFunction);

	FACTORY_PROTOTYPE1(setLineNumber, In< boost::shared_ptr< Base<EncodingT> > >)
	void setLineNumber(boost::shared_ptr< Base<EncodingT> > const& lineNumber);

	FACTORY_PROTOTYPE1(setStartBlock, In< boost::shared_ptr< Base<EncodingT> > >)
	void setStartBlock(boost::shared_ptr< Base<EncodingT> > const& startBlock);

	FACTORY_PROTOTYPE1(setLengthBlock, In< boost::shared_ptr< Base<EncodingT> > >)
	void setLengthBlock(boost::shared_ptr< Base<EncodingT> > const& lengthBlock);

	FACTORY_PROTOTYPE1(setCppFile, In< boost::shared_ptr< Base<EncodingT> > >)
	void setCppFile(boost::shared_ptr< Base<EncodingT> > const& cppFile);

	boost::shared_ptr< Base<EncodingT> > hasCppFunction() const;

	boost::shared_ptr< Base<EncodingT> > hasCppFile() const;

	void removeCppFunction();

	void removeCppFile();

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( CppVariableInterpreter, C("CppVariable") );
		CLASS_KEY_REGISTER8( CppVariableInterpreter, C("CppVariable") );
		METHOD_KEY_REGISTER ( CppVariableInterpreter, boost::shared_ptr< Base<EncodingT> >, getIdentifier, const_t, C("CppVariable::Identifier") );
		METHOD_KEY_REGISTER ( CppVariableInterpreter, boost::shared_ptr< Base<EncodingT> >, getVarType, const_t, C("CppVariable::VarType") );
		METHOD_KEY_REGISTER1( CppVariableInterpreter, void, setVarType, no_const_t, C("CppVariable::VarType") );
		METHOD_KEY_REGISTER ( CppVariableInterpreter, boost::shared_ptr< Base<EncodingT> >, getName, const_t, C("CppVariable::Name") );
		METHOD_KEY_REGISTER1( CppVariableInterpreter, void, setName, no_const_t, C("CppVariable::Name") );
		METHOD_KEY_REGISTER ( CppVariableInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsStatic, const_t, C("CppVariable::IsStatic") );
		METHOD_KEY_REGISTER1( CppVariableInterpreter, void, setIsStatic, no_const_t, C("CppVariable::IsStatic") );
		METHOD_KEY_REGISTER ( CppVariableInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsConst, const_t, C("CppVariable::IsConst") );
		METHOD_KEY_REGISTER1( CppVariableInterpreter, void, setIsConst, no_const_t, C("CppVariable::IsConst") );
		METHOD_KEY_REGISTER ( CppVariableInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsConstexpr, const_t, C("CppVariable::IsConstexpr") );
		METHOD_KEY_REGISTER1( CppVariableInterpreter, void, setIsConstexpr, no_const_t, C("CppVariable::IsConstexpr") );
		METHOD_KEY_REGISTER1( CppVariableInterpreter, void, setCppFunction, no_const_t, C("CppVariable::CppFunction") );
		METHOD_KEY_REGISTER ( CppVariableInterpreter, boost::shared_ptr< Base<EncodingT> >, getCppFunction, no_const_t, C("CppVariable::CppFunction") );
		METHOD_KEY_REGISTER ( CppVariableInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCppFunction, const_t, C("CppVariable::HasCppFunction") );
		METHOD_KEY_REGISTER ( CppVariableInterpreter, void, removeCppFunction, no_const_t, C("CppVariable::removeCppFunction") );
		METHOD_KEY_REGISTER ( CppVariableInterpreter, boost::shared_ptr< Base<EncodingT> >, getLineNumber, const_t, C("CppVariable::LineNumber") );
		METHOD_KEY_REGISTER1( CppVariableInterpreter, void, setLineNumber, no_const_t, C("CppVariable::LineNumber") );
		METHOD_KEY_REGISTER ( CppVariableInterpreter, boost::shared_ptr< Base<EncodingT> >, getStartBlock, const_t, C("CppVariable::StartBlock") );
		METHOD_KEY_REGISTER1( CppVariableInterpreter, void, setStartBlock, no_const_t, C("CppVariable::StartBlock") );
		METHOD_KEY_REGISTER ( CppVariableInterpreter, boost::shared_ptr< Base<EncodingT> >, getLengthBlock, const_t, C("CppVariable::LengthBlock") );
		METHOD_KEY_REGISTER1( CppVariableInterpreter, void, setLengthBlock, no_const_t, C("CppVariable::LengthBlock") );
		METHOD_KEY_REGISTER1( CppVariableInterpreter, void, setCppFile, no_const_t, C("CppVariable::CppFile") );
		METHOD_KEY_REGISTER ( CppVariableInterpreter, boost::shared_ptr< Base<EncodingT> >, getCppFile, no_const_t, C("CppVariable::CppFile") );
		METHOD_KEY_REGISTER ( CppVariableInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCppFile, const_t, C("CppVariable::HasCppFile") );
		METHOD_KEY_REGISTER ( CppVariableInterpreter, void, removeCppFile, no_const_t, C("CppVariable::removeCppFile") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( C("CppVariable") );
		CLASS_KEY_UNREGISTER8( C("CppVariable") );
		METHOD_KEY_UNREGISTER ( C("CppVariable::Identifier") );
		METHOD_KEY_UNREGISTER ( C("CppVariable::VarType") );
		METHOD_KEY_UNREGISTER1( C("CppVariable::VarType") );
		METHOD_KEY_UNREGISTER ( C("CppVariable::Name") );
		METHOD_KEY_UNREGISTER1( C("CppVariable::Name") );
		METHOD_KEY_UNREGISTER ( C("CppVariable::IsStatic") );
		METHOD_KEY_UNREGISTER1( C("CppVariable::IsStatic") );
		METHOD_KEY_UNREGISTER ( C("CppVariable::IsConst") );
		METHOD_KEY_UNREGISTER1( C("CppVariable::IsConst") );
		METHOD_KEY_UNREGISTER ( C("CppVariable::IsConstexpr") );
		METHOD_KEY_UNREGISTER1( C("CppVariable::IsConstexpr") );
		METHOD_KEY_UNREGISTER ( C("CppVariable::CppFunction") );
		METHOD_KEY_UNREGISTER1( C("CppVariable::CppFunction") );
		METHOD_KEY_UNREGISTER ( C("CppVariable::HasCppFunction") );
		METHOD_KEY_UNREGISTER ( C("CppVariable::removeCppFunction") );
		METHOD_KEY_UNREGISTER ( C("CppVariable::LineNumber") );
		METHOD_KEY_UNREGISTER1( C("CppVariable::LineNumber") );
		METHOD_KEY_UNREGISTER ( C("CppVariable::StartBlock") );
		METHOD_KEY_UNREGISTER1( C("CppVariable::StartBlock") );
		METHOD_KEY_UNREGISTER ( C("CppVariable::LengthBlock") );
		METHOD_KEY_UNREGISTER1( C("CppVariable::LengthBlock") );
		METHOD_KEY_UNREGISTER ( C("CppVariable::CppFile") );
		METHOD_KEY_UNREGISTER1( C("CppVariable::CppFile") );
		METHOD_KEY_UNREGISTER ( C("CppVariable::HasCppFile") );
		METHOD_KEY_UNREGISTER ( C("CppVariable::removeCppFile") );
	FACTORY_END_UNREGISTER
};

template <class EncodingT>
bool check_cppVariable(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _CppVariable<EncodingT> >& o);

template <class EncodingT>
bool reset_cppVariable(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _CppVariable<EncodingT> > const& o);

NAMESPACE_END

#undef C
#undef A

#include "cppVariableInterpreter_impl.hpp"

#endif
