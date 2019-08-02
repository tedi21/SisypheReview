/* 
 * cppFunctionInterpreter.hpp
 *
 *
 * @date 26-03-2019
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPFUNCTION_INTERPRETER_HPP_
#define _CPPFUNCTION_INTERPRETER_HPP_

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
class CppParameterInterpreter;

template <class EncodingT>
class CppVariableInterpreter;

template <class EncodingT>
class CppFileInterpreter;

template <class EncodingT>
class CppFileInterpreter;

template <class EncodingT>
class CppClassInterpreter;

template <class EncodingT>
class CppFunctionInterpreter
: public Base<EncodingT>
{
private:
	boost::shared_ptr< _CppFunction<EncodingT> > m_value;

public:
	CppFunctionInterpreter();

	CppFunctionInterpreter(boost::shared_ptr< _CppFunction<EncodingT> > const& value);

	FACTORY_PROTOTYPE26(CppFunctionInterpreter,
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
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	CppFunctionInterpreter(boost::shared_ptr< Base<EncodingT> > const& name,
				boost::shared_ptr< Base<EncodingT> > const& accessSpecifier,
				boost::shared_ptr< Base<EncodingT> > const& returnType,
				boost::shared_ptr< Base<EncodingT> > const& isConst,
				boost::shared_ptr< Base<EncodingT> > const& isVirtual,
				boost::shared_ptr< Base<EncodingT> > const& isVirtualPure,
				boost::shared_ptr< Base<EncodingT> > const& isStatic,
				boost::shared_ptr< Base<EncodingT> > const& isOperator,
				boost::shared_ptr< Base<EncodingT> > const& isDestructor,
				boost::shared_ptr< Base<EncodingT> > const& isConstructor,
				boost::shared_ptr< Base<EncodingT> > const& isVariadic,
				boost::shared_ptr< Base<EncodingT> > const& isTemplate,
				boost::shared_ptr< Base<EncodingT> > const& isInline,
				boost::shared_ptr< Base<EncodingT> > const& isConstexpr,
				boost::shared_ptr< Base<EncodingT> > const& isOverride,
				boost::shared_ptr< Base<EncodingT> > const& isFinal,
				boost::shared_ptr< Base<EncodingT> > const& isNoexcept,
				boost::shared_ptr< Base<EncodingT> > const& signature,
				boost::shared_ptr< Base<EncodingT> > const& decLineNumber,
				boost::shared_ptr< Base<EncodingT> > const& startDecBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthDecBlock,
				boost::shared_ptr< Base<EncodingT> > const& linesCount,
				boost::shared_ptr< Base<EncodingT> > const& complexity,
				boost::shared_ptr< Base<EncodingT> > const& defLineNumber,
				boost::shared_ptr< Base<EncodingT> > const& startDefBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthDefBlock);

	boost::shared_ptr< _CppFunction<EncodingT> > value() const;

	void value(boost::shared_ptr< _CppFunction<EncodingT> > const& value);

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getIdentifier() const;

	boost::shared_ptr< Base<EncodingT> > getName() const;

	boost::shared_ptr< Base<EncodingT> > getAccessSpecifier() const;

	boost::shared_ptr< Base<EncodingT> > getReturnType() const;

	boost::shared_ptr< Base<EncodingT> > getIsConst() const;

	boost::shared_ptr< Base<EncodingT> > getIsVirtual() const;

	boost::shared_ptr< Base<EncodingT> > getIsVirtualPure() const;

	boost::shared_ptr< Base<EncodingT> > getIsStatic() const;

	boost::shared_ptr< Base<EncodingT> > getIsOperator() const;

	boost::shared_ptr< Base<EncodingT> > getIsDestructor() const;

	boost::shared_ptr< Base<EncodingT> > getIsConstructor() const;

	boost::shared_ptr< Base<EncodingT> > getIsVariadic() const;

	boost::shared_ptr< Base<EncodingT> > getIsTemplate() const;

	boost::shared_ptr< Base<EncodingT> > getIsInline() const;

	boost::shared_ptr< Base<EncodingT> > getIsConstexpr() const;

	boost::shared_ptr< Base<EncodingT> > getIsOverride() const;

	boost::shared_ptr< Base<EncodingT> > getIsFinal() const;

	boost::shared_ptr< Base<EncodingT> > getIsNoexcept() const;

	boost::shared_ptr< Base<EncodingT> > getSignature() const;

	boost::shared_ptr< Base<EncodingT> > getDecLineNumber() const;

	boost::shared_ptr< Base<EncodingT> > getStartDecBlock() const;

	boost::shared_ptr< Base<EncodingT> > getLengthDecBlock() const;

	boost::shared_ptr< Base<EncodingT> > getLinesCount() const;

	boost::shared_ptr< Base<EncodingT> > getComplexity() const;

	boost::shared_ptr< Base<EncodingT> > getDefLineNumber() const;

	boost::shared_ptr< Base<EncodingT> > getStartDefBlock() const;

	boost::shared_ptr< Base<EncodingT> > getLengthDefBlock() const;

	boost::shared_ptr< Base<EncodingT> > getCppDeclarationFile();

	boost::shared_ptr< Base<EncodingT> > getCppDefinitionFile();

	boost::shared_ptr< Base<EncodingT> > getCppClass();

	FACTORY_PROTOTYPE1(setCppDeclarationFile, In< boost::shared_ptr< Base<EncodingT> > >)
	void setCppDeclarationFile(boost::shared_ptr< Base<EncodingT> > const& cppDeclarationFile);

	FACTORY_PROTOTYPE1(setCppDefinitionFile, In< boost::shared_ptr< Base<EncodingT> > >)
	void setCppDefinitionFile(boost::shared_ptr< Base<EncodingT> > const& cppDefinitionFile);

	FACTORY_PROTOTYPE1(setName, In< boost::shared_ptr< Base<EncodingT> > >)
	void setName(boost::shared_ptr< Base<EncodingT> > const& name);

	FACTORY_PROTOTYPE1(setCppClass, In< boost::shared_ptr< Base<EncodingT> > >)
	void setCppClass(boost::shared_ptr< Base<EncodingT> > const& cppClass);

	FACTORY_PROTOTYPE1(setAccessSpecifier, In< boost::shared_ptr< Base<EncodingT> > >)
	void setAccessSpecifier(boost::shared_ptr< Base<EncodingT> > const& accessSpecifier);

	FACTORY_PROTOTYPE1(setReturnType, In< boost::shared_ptr< Base<EncodingT> > >)
	void setReturnType(boost::shared_ptr< Base<EncodingT> > const& returnType);

	FACTORY_PROTOTYPE1(setIsConst, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsConst(boost::shared_ptr< Base<EncodingT> > const& isConst);

	FACTORY_PROTOTYPE1(setIsVirtual, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsVirtual(boost::shared_ptr< Base<EncodingT> > const& isVirtual);

	FACTORY_PROTOTYPE1(setIsVirtualPure, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsVirtualPure(boost::shared_ptr< Base<EncodingT> > const& isVirtualPure);

	FACTORY_PROTOTYPE1(setIsStatic, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsStatic(boost::shared_ptr< Base<EncodingT> > const& isStatic);

	FACTORY_PROTOTYPE1(setIsOperator, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsOperator(boost::shared_ptr< Base<EncodingT> > const& isOperator);

	FACTORY_PROTOTYPE1(setIsDestructor, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsDestructor(boost::shared_ptr< Base<EncodingT> > const& isDestructor);

	FACTORY_PROTOTYPE1(setIsConstructor, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsConstructor(boost::shared_ptr< Base<EncodingT> > const& isConstructor);

	FACTORY_PROTOTYPE1(setIsVariadic, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsVariadic(boost::shared_ptr< Base<EncodingT> > const& isVariadic);

	FACTORY_PROTOTYPE1(setIsTemplate, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsTemplate(boost::shared_ptr< Base<EncodingT> > const& isTemplate);

	FACTORY_PROTOTYPE1(setIsInline, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsInline(boost::shared_ptr< Base<EncodingT> > const& isInline);

	FACTORY_PROTOTYPE1(setIsConstexpr, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsConstexpr(boost::shared_ptr< Base<EncodingT> > const& isConstexpr);

	FACTORY_PROTOTYPE1(setIsOverride, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsOverride(boost::shared_ptr< Base<EncodingT> > const& isOverride);

	FACTORY_PROTOTYPE1(setIsFinal, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsFinal(boost::shared_ptr< Base<EncodingT> > const& isFinal);

	FACTORY_PROTOTYPE1(setIsNoexcept, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsNoexcept(boost::shared_ptr< Base<EncodingT> > const& isNoexcept);

	FACTORY_PROTOTYPE1(setSignature, In< boost::shared_ptr< Base<EncodingT> > >)
	void setSignature(boost::shared_ptr< Base<EncodingT> > const& signature);

	FACTORY_PROTOTYPE1(setDecLineNumber, In< boost::shared_ptr< Base<EncodingT> > >)
	void setDecLineNumber(boost::shared_ptr< Base<EncodingT> > const& decLineNumber);

	FACTORY_PROTOTYPE1(setStartDecBlock, In< boost::shared_ptr< Base<EncodingT> > >)
	void setStartDecBlock(boost::shared_ptr< Base<EncodingT> > const& startDecBlock);

	FACTORY_PROTOTYPE1(setLengthDecBlock, In< boost::shared_ptr< Base<EncodingT> > >)
	void setLengthDecBlock(boost::shared_ptr< Base<EncodingT> > const& lengthDecBlock);

	FACTORY_PROTOTYPE1(setLinesCount, In< boost::shared_ptr< Base<EncodingT> > >)
	void setLinesCount(boost::shared_ptr< Base<EncodingT> > const& linesCount);

	FACTORY_PROTOTYPE1(setComplexity, In< boost::shared_ptr< Base<EncodingT> > >)
	void setComplexity(boost::shared_ptr< Base<EncodingT> > const& complexity);

	FACTORY_PROTOTYPE1(setDefLineNumber, In< boost::shared_ptr< Base<EncodingT> > >)
	void setDefLineNumber(boost::shared_ptr< Base<EncodingT> > const& defLineNumber);

	FACTORY_PROTOTYPE1(setStartDefBlock, In< boost::shared_ptr< Base<EncodingT> > >)
	void setStartDefBlock(boost::shared_ptr< Base<EncodingT> > const& startDefBlock);

	FACTORY_PROTOTYPE1(setLengthDefBlock, In< boost::shared_ptr< Base<EncodingT> > >)
	void setLengthDefBlock(boost::shared_ptr< Base<EncodingT> > const& lengthDefBlock);

	boost::shared_ptr< Base<EncodingT> > hasCppDeclarationFile() const;

	boost::shared_ptr< Base<EncodingT> > hasCppDefinitionFile() const;

	boost::shared_ptr< Base<EncodingT> > hasCppClass() const;

	void removeCppDeclarationFile();

	void removeCppDefinitionFile();

	void removeCppClass();

	FACTORY_PROTOTYPE1(removeCppParameter, In< boost::shared_ptr< Base<EncodingT> > >)
	void removeCppParameter(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE1(removeCppVariable, In< boost::shared_ptr< Base<EncodingT> > >)
	void removeCppVariable(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE2(insertCppParameter, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void insertCppParameter(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppParameter);

	FACTORY_PROTOTYPE2(insertCppVariable, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void insertCppVariable(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppVariable);

	FACTORY_PROTOTYPE1(getCppParameter, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getCppParameter(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE1(getCppVariable, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getCppVariable(boost::shared_ptr< Base<EncodingT> > const& n);

	void clearCppParameters();

	void clearCppVariables();

	boost::shared_ptr< Base<EncodingT> > hasCppParameters() const;

	boost::shared_ptr< Base<EncodingT> > hasCppVariables() const;

	boost::shared_ptr< Base<EncodingT> > cppParametersCount() const;

	boost::shared_ptr< Base<EncodingT> > cppVariablesCount() const;

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( CppFunctionInterpreter, UCS("CppFunction") );
		CLASS_KEY_REGISTER26( CppFunctionInterpreter, UCS("CppFunction") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setCppDeclarationFile, no_const_t, UCS("CppFunction::CppDeclarationFile") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getCppDeclarationFile, no_const_t, UCS("CppFunction::CppDeclarationFile") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCppDeclarationFile, const_t, UCS("CppFunction::HasCppDeclarationFile") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, void, removeCppDeclarationFile, no_const_t, UCS("CppFunction::removeCppDeclarationFile") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setCppDefinitionFile, no_const_t, UCS("CppFunction::CppDefinitionFile") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getCppDefinitionFile, no_const_t, UCS("CppFunction::CppDefinitionFile") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCppDefinitionFile, const_t, UCS("CppFunction::HasCppDefinitionFile") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, void, removeCppDefinitionFile, no_const_t, UCS("CppFunction::removeCppDefinitionFile") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getIdentifier, const_t, UCS("CppFunction::Identifier") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getName, const_t, UCS("CppFunction::Name") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setName, no_const_t, UCS("CppFunction::Name") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setCppClass, no_const_t, UCS("CppFunction::CppClass") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getCppClass, no_const_t, UCS("CppFunction::CppClass") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCppClass, const_t, UCS("CppFunction::HasCppClass") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, void, removeCppClass, no_const_t, UCS("CppFunction::removeCppClass") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getAccessSpecifier, const_t, UCS("CppFunction::AccessSpecifier") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setAccessSpecifier, no_const_t, UCS("CppFunction::AccessSpecifier") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getReturnType, const_t, UCS("CppFunction::ReturnType") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setReturnType, no_const_t, UCS("CppFunction::ReturnType") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsConst, const_t, UCS("CppFunction::IsConst") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setIsConst, no_const_t, UCS("CppFunction::IsConst") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsVirtual, const_t, UCS("CppFunction::IsVirtual") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setIsVirtual, no_const_t, UCS("CppFunction::IsVirtual") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsVirtualPure, const_t, UCS("CppFunction::IsVirtualPure") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setIsVirtualPure, no_const_t, UCS("CppFunction::IsVirtualPure") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsStatic, const_t, UCS("CppFunction::IsStatic") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setIsStatic, no_const_t, UCS("CppFunction::IsStatic") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsOperator, const_t, UCS("CppFunction::IsOperator") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setIsOperator, no_const_t, UCS("CppFunction::IsOperator") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsDestructor, const_t, UCS("CppFunction::IsDestructor") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setIsDestructor, no_const_t, UCS("CppFunction::IsDestructor") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsConstructor, const_t, UCS("CppFunction::IsConstructor") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setIsConstructor, no_const_t, UCS("CppFunction::IsConstructor") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsVariadic, const_t, UCS("CppFunction::IsVariadic") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setIsVariadic, no_const_t, UCS("CppFunction::IsVariadic") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsTemplate, const_t, UCS("CppFunction::IsTemplate") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setIsTemplate, no_const_t, UCS("CppFunction::IsTemplate") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsInline, const_t, UCS("CppFunction::IsInline") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setIsInline, no_const_t, UCS("CppFunction::IsInline") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsConstexpr, const_t, UCS("CppFunction::IsConstexpr") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setIsConstexpr, no_const_t, UCS("CppFunction::IsConstexpr") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsOverride, const_t, UCS("CppFunction::IsOverride") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setIsOverride, no_const_t, UCS("CppFunction::IsOverride") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsFinal, const_t, UCS("CppFunction::IsFinal") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setIsFinal, no_const_t, UCS("CppFunction::IsFinal") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsNoexcept, const_t, UCS("CppFunction::IsNoexcept") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setIsNoexcept, no_const_t, UCS("CppFunction::IsNoexcept") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getSignature, const_t, UCS("CppFunction::Signature") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setSignature, no_const_t, UCS("CppFunction::Signature") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getDecLineNumber, const_t, UCS("CppFunction::DecLineNumber") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setDecLineNumber, no_const_t, UCS("CppFunction::DecLineNumber") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getStartDecBlock, const_t, UCS("CppFunction::StartDecBlock") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setStartDecBlock, no_const_t, UCS("CppFunction::StartDecBlock") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getLengthDecBlock, const_t, UCS("CppFunction::LengthDecBlock") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setLengthDecBlock, no_const_t, UCS("CppFunction::LengthDecBlock") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getLinesCount, const_t, UCS("CppFunction::LinesCount") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setLinesCount, no_const_t, UCS("CppFunction::LinesCount") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getComplexity, const_t, UCS("CppFunction::Complexity") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setComplexity, no_const_t, UCS("CppFunction::Complexity") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getDefLineNumber, const_t, UCS("CppFunction::DefLineNumber") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setDefLineNumber, no_const_t, UCS("CppFunction::DefLineNumber") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getStartDefBlock, const_t, UCS("CppFunction::StartDefBlock") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setStartDefBlock, no_const_t, UCS("CppFunction::StartDefBlock") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getLengthDefBlock, const_t, UCS("CppFunction::LengthDefBlock") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, setLengthDefBlock, no_const_t, UCS("CppFunction::LengthDefBlock") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, removeCppParameter, no_const_t, UCS("CppFunction::removeCppParameters") );
		METHOD_KEY_REGISTER2( CppFunctionInterpreter, void, insertCppParameter, no_const_t, UCS("CppFunction::CppParameters") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getCppParameter, no_const_t, UCS("CppFunction::CppParameters") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, void, clearCppParameters, no_const_t, UCS("CppFunction::ClearCppParameters") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCppParameters, const_t, UCS("CppFunction::HasCppParameters") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, cppParametersCount, const_t, UCS("CppFunction::CppParametersCount") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, void, removeCppVariable, no_const_t, UCS("CppFunction::removeCppVariables") );
		METHOD_KEY_REGISTER2( CppFunctionInterpreter, void, insertCppVariable, no_const_t, UCS("CppFunction::CppVariables") );
		METHOD_KEY_REGISTER1( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, getCppVariable, no_const_t, UCS("CppFunction::CppVariables") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, void, clearCppVariables, no_const_t, UCS("CppFunction::ClearCppVariables") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCppVariables, const_t, UCS("CppFunction::HasCppVariables") );
		METHOD_KEY_REGISTER ( CppFunctionInterpreter, boost::shared_ptr< Base<EncodingT> >, cppVariablesCount, const_t, UCS("CppFunction::CppVariablesCount") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( UCS("CppFunction") );
		CLASS_KEY_UNREGISTER26( UCS("CppFunction") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::CppDeclarationFile") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::CppDeclarationFile") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::HasCppDeclarationFile") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::removeCppDeclarationFile") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::CppDefinitionFile") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::CppDefinitionFile") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::HasCppDefinitionFile") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::removeCppDefinitionFile") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::Identifier") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::Name") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::Name") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::CppClass") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::CppClass") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::HasCppClass") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::removeCppClass") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::AccessSpecifier") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::AccessSpecifier") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::ReturnType") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::ReturnType") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::IsConst") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::IsConst") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::IsVirtual") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::IsVirtual") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::IsVirtualPure") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::IsVirtualPure") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::IsStatic") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::IsStatic") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::IsOperator") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::IsOperator") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::IsDestructor") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::IsDestructor") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::IsConstructor") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::IsConstructor") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::IsVariadic") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::IsVariadic") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::IsTemplate") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::IsTemplate") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::IsInline") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::IsInline") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::IsConstexpr") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::IsConstexpr") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::IsOverride") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::IsOverride") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::IsFinal") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::IsFinal") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::IsNoexcept") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::IsNoexcept") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::Signature") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::Signature") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::DecLineNumber") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::DecLineNumber") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::StartDecBlock") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::StartDecBlock") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::LengthDecBlock") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::LengthDecBlock") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::LinesCount") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::LinesCount") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::Complexity") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::Complexity") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::DefLineNumber") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::DefLineNumber") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::StartDefBlock") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::StartDefBlock") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::LengthDefBlock") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::LengthDefBlock") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::removeCppParameters") );
		METHOD_KEY_UNREGISTER2( UCS("CppFunction::CppParameters") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::CppParameters") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::ClearCppParameters") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::HasCppParameters") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::CppParametersCount") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::removeCppVariables") );
		METHOD_KEY_UNREGISTER2( UCS("CppFunction::CppVariables") );
		METHOD_KEY_UNREGISTER1( UCS("CppFunction::CppVariables") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::ClearCppVariables") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::HasCppVariables") );
		METHOD_KEY_UNREGISTER ( UCS("CppFunction::CppVariablesCount") );
	FACTORY_END_UNREGISTER
};

template <class EncodingT>
bool check_cppFunction(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _CppFunction<EncodingT> >& o);

template <class EncodingT>
bool reset_cppFunction(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _CppFunction<EncodingT> > const& o);

NAMESPACE_END

#undef C
#undef A

#include "cppFunctionInterpreter_impl.hpp"

#endif
