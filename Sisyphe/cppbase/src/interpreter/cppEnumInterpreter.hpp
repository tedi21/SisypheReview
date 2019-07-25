/* 
 * cppEnumInterpreter.hpp
 *
 *
 * @date 26-03-2019
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPENUM_INTERPRETER_HPP_
#define _CPPENUM_INTERPRETER_HPP_

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
class CppEnumConstantInterpreter;

template <class EncodingT>
class CppFileInterpreter;

template <class EncodingT>
class CppClassInterpreter;

template <class EncodingT>
class CppEnumInterpreter
: public Base<EncodingT>
{
private:
	boost::shared_ptr< _CppEnum<EncodingT> > m_value;

public:
	CppEnumInterpreter();

	CppEnumInterpreter(boost::shared_ptr< _CppEnum<EncodingT> > const& value);

	FACTORY_PROTOTYPE5(CppEnumInterpreter,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	CppEnumInterpreter(boost::shared_ptr< Base<EncodingT> > const& name,
				boost::shared_ptr< Base<EncodingT> > const& accessSpecifier,
				boost::shared_ptr< Base<EncodingT> > const& lineNumber,
				boost::shared_ptr< Base<EncodingT> > const& startBlock,
				boost::shared_ptr< Base<EncodingT> > const& lengthBlock);

	boost::shared_ptr< _CppEnum<EncodingT> > value() const;

	void value(boost::shared_ptr< _CppEnum<EncodingT> > const& value);

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getIdentifier() const;

	boost::shared_ptr< Base<EncodingT> > getName() const;

	boost::shared_ptr< Base<EncodingT> > getAccessSpecifier() const;

	boost::shared_ptr< Base<EncodingT> > getLineNumber() const;

	boost::shared_ptr< Base<EncodingT> > getStartBlock() const;

	boost::shared_ptr< Base<EncodingT> > getLengthBlock() const;

	boost::shared_ptr< Base<EncodingT> > getCppFile();

	boost::shared_ptr< Base<EncodingT> > getCppClass();

	FACTORY_PROTOTYPE1(setName, In< boost::shared_ptr< Base<EncodingT> > >)
	void setName(boost::shared_ptr< Base<EncodingT> > const& name);

	FACTORY_PROTOTYPE1(setCppFile, In< boost::shared_ptr< Base<EncodingT> > >)
	void setCppFile(boost::shared_ptr< Base<EncodingT> > const& cppFile);

	FACTORY_PROTOTYPE1(setCppClass, In< boost::shared_ptr< Base<EncodingT> > >)
	void setCppClass(boost::shared_ptr< Base<EncodingT> > const& cppClass);

	FACTORY_PROTOTYPE1(setAccessSpecifier, In< boost::shared_ptr< Base<EncodingT> > >)
	void setAccessSpecifier(boost::shared_ptr< Base<EncodingT> > const& accessSpecifier);

	FACTORY_PROTOTYPE1(setLineNumber, In< boost::shared_ptr< Base<EncodingT> > >)
	void setLineNumber(boost::shared_ptr< Base<EncodingT> > const& lineNumber);

	FACTORY_PROTOTYPE1(setStartBlock, In< boost::shared_ptr< Base<EncodingT> > >)
	void setStartBlock(boost::shared_ptr< Base<EncodingT> > const& startBlock);

	FACTORY_PROTOTYPE1(setLengthBlock, In< boost::shared_ptr< Base<EncodingT> > >)
	void setLengthBlock(boost::shared_ptr< Base<EncodingT> > const& lengthBlock);

	boost::shared_ptr< Base<EncodingT> > hasCppFile() const;

	boost::shared_ptr< Base<EncodingT> > hasCppClass() const;

	void removeCppFile();

	void removeCppClass();

	FACTORY_PROTOTYPE1(removeCppEnumConstant, In< boost::shared_ptr< Base<EncodingT> > >)
	void removeCppEnumConstant(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE2(insertCppEnumConstant, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void insertCppEnumConstant(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppEnumConstant);

	FACTORY_PROTOTYPE1(getCppEnumConstant, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getCppEnumConstant(boost::shared_ptr< Base<EncodingT> > const& n);

	void clearCppEnumConstants();

	boost::shared_ptr< Base<EncodingT> > hasCppEnumConstants() const;

	boost::shared_ptr< Base<EncodingT> > cppEnumConstantsCount() const;

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( CppEnumInterpreter, C("CppEnum") );
		CLASS_KEY_REGISTER5( CppEnumInterpreter, C("CppEnum") );
		METHOD_KEY_REGISTER ( CppEnumInterpreter, boost::shared_ptr< Base<EncodingT> >, getIdentifier, const_t, C("CppEnum::Identifier") );
		METHOD_KEY_REGISTER ( CppEnumInterpreter, boost::shared_ptr< Base<EncodingT> >, getName, const_t, C("CppEnum::Name") );
		METHOD_KEY_REGISTER1( CppEnumInterpreter, void, setName, no_const_t, C("CppEnum::Name") );
		METHOD_KEY_REGISTER1( CppEnumInterpreter, void, setCppFile, no_const_t, C("CppEnum::CppFile") );
		METHOD_KEY_REGISTER ( CppEnumInterpreter, boost::shared_ptr< Base<EncodingT> >, getCppFile, no_const_t, C("CppEnum::CppFile") );
		METHOD_KEY_REGISTER ( CppEnumInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCppFile, const_t, C("CppEnum::HasCppFile") );
		METHOD_KEY_REGISTER ( CppEnumInterpreter, void, removeCppFile, no_const_t, C("CppEnum::removeCppFile") );
		METHOD_KEY_REGISTER1( CppEnumInterpreter, void, setCppClass, no_const_t, C("CppEnum::CppClass") );
		METHOD_KEY_REGISTER ( CppEnumInterpreter, boost::shared_ptr< Base<EncodingT> >, getCppClass, no_const_t, C("CppEnum::CppClass") );
		METHOD_KEY_REGISTER ( CppEnumInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCppClass, const_t, C("CppEnum::HasCppClass") );
		METHOD_KEY_REGISTER ( CppEnumInterpreter, void, removeCppClass, no_const_t, C("CppEnum::removeCppClass") );
		METHOD_KEY_REGISTER ( CppEnumInterpreter, boost::shared_ptr< Base<EncodingT> >, getAccessSpecifier, const_t, C("CppEnum::AccessSpecifier") );
		METHOD_KEY_REGISTER1( CppEnumInterpreter, void, setAccessSpecifier, no_const_t, C("CppEnum::AccessSpecifier") );
		METHOD_KEY_REGISTER ( CppEnumInterpreter, boost::shared_ptr< Base<EncodingT> >, getLineNumber, const_t, C("CppEnum::LineNumber") );
		METHOD_KEY_REGISTER1( CppEnumInterpreter, void, setLineNumber, no_const_t, C("CppEnum::LineNumber") );
		METHOD_KEY_REGISTER ( CppEnumInterpreter, boost::shared_ptr< Base<EncodingT> >, getStartBlock, const_t, C("CppEnum::StartBlock") );
		METHOD_KEY_REGISTER1( CppEnumInterpreter, void, setStartBlock, no_const_t, C("CppEnum::StartBlock") );
		METHOD_KEY_REGISTER ( CppEnumInterpreter, boost::shared_ptr< Base<EncodingT> >, getLengthBlock, const_t, C("CppEnum::LengthBlock") );
		METHOD_KEY_REGISTER1( CppEnumInterpreter, void, setLengthBlock, no_const_t, C("CppEnum::LengthBlock") );
		METHOD_KEY_REGISTER1( CppEnumInterpreter, void, removeCppEnumConstant, no_const_t, C("CppEnum::removeCppEnumConstants") );
		METHOD_KEY_REGISTER2( CppEnumInterpreter, void, insertCppEnumConstant, no_const_t, C("CppEnum::CppEnumConstants") );
		METHOD_KEY_REGISTER1( CppEnumInterpreter, boost::shared_ptr< Base<EncodingT> >, getCppEnumConstant, no_const_t, C("CppEnum::CppEnumConstants") );
		METHOD_KEY_REGISTER ( CppEnumInterpreter, void, clearCppEnumConstants, no_const_t, C("CppEnum::ClearCppEnumConstants") );
		METHOD_KEY_REGISTER ( CppEnumInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCppEnumConstants, const_t, C("CppEnum::HasCppEnumConstants") );
		METHOD_KEY_REGISTER ( CppEnumInterpreter, boost::shared_ptr< Base<EncodingT> >, cppEnumConstantsCount, const_t, C("CppEnum::CppEnumConstantsCount") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( C("CppEnum") );
		CLASS_KEY_UNREGISTER5( C("CppEnum") );
		METHOD_KEY_UNREGISTER ( C("CppEnum::Identifier") );
		METHOD_KEY_UNREGISTER ( C("CppEnum::Name") );
		METHOD_KEY_UNREGISTER1( C("CppEnum::Name") );
		METHOD_KEY_UNREGISTER ( C("CppEnum::CppFile") );
		METHOD_KEY_UNREGISTER1( C("CppEnum::CppFile") );
		METHOD_KEY_UNREGISTER ( C("CppEnum::HasCppFile") );
		METHOD_KEY_UNREGISTER ( C("CppEnum::removeCppFile") );
		METHOD_KEY_UNREGISTER ( C("CppEnum::CppClass") );
		METHOD_KEY_UNREGISTER1( C("CppEnum::CppClass") );
		METHOD_KEY_UNREGISTER ( C("CppEnum::HasCppClass") );
		METHOD_KEY_UNREGISTER ( C("CppEnum::removeCppClass") );
		METHOD_KEY_UNREGISTER ( C("CppEnum::AccessSpecifier") );
		METHOD_KEY_UNREGISTER1( C("CppEnum::AccessSpecifier") );
		METHOD_KEY_UNREGISTER ( C("CppEnum::LineNumber") );
		METHOD_KEY_UNREGISTER1( C("CppEnum::LineNumber") );
		METHOD_KEY_UNREGISTER ( C("CppEnum::StartBlock") );
		METHOD_KEY_UNREGISTER1( C("CppEnum::StartBlock") );
		METHOD_KEY_UNREGISTER ( C("CppEnum::LengthBlock") );
		METHOD_KEY_UNREGISTER1( C("CppEnum::LengthBlock") );
		METHOD_KEY_UNREGISTER1( C("CppEnum::removeCppEnumConstants") );
		METHOD_KEY_UNREGISTER2( C("CppEnum::CppEnumConstants") );
		METHOD_KEY_UNREGISTER1( C("CppEnum::CppEnumConstants") );
		METHOD_KEY_UNREGISTER ( C("CppEnum::ClearCppEnumConstants") );
		METHOD_KEY_UNREGISTER ( C("CppEnum::HasCppEnumConstants") );
		METHOD_KEY_UNREGISTER ( C("CppEnum::CppEnumConstantsCount") );
	FACTORY_END_UNREGISTER
};

template <class EncodingT>
bool check_cppEnum(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _CppEnum<EncodingT> >& o);

template <class EncodingT>
bool reset_cppEnum(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _CppEnum<EncodingT> > const& o);

NAMESPACE_END

#undef C
#undef A

#include "cppEnumInterpreter_impl.hpp"

#endif
