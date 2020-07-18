/* 
 * cppFileInterpreter.hpp
 *
 *
 * @date 14-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPFILE_INTERPRETER_HPP_
#define _CPPFILE_INTERPRETER_HPP_

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
class CppFunctionInterpreter;

template <class EncodingT>
class CppFunctionInterpreter;

template <class EncodingT>
class CppClassInterpreter;

template <class EncodingT>
class CppIncludeInterpreter;

template <class EncodingT>
class CppVariableInterpreter;

template <class EncodingT>
class CppEnumInterpreter;

template <class EncodingT>
class CMacroInterpreter;

template <class EncodingT>
class CppNoticeInterpreter;

template <class EncodingT>
class TextFileInterpreter;

template <class EncodingT>
class CppFileTypeInterpreter;

template <class EncodingT>
class CppFileInterpreter
: public Base<EncodingT>
{
private:
	boost::shared_ptr< _CppFile<EncodingT> > m_value;

public:
	CppFileInterpreter();

	CppFileInterpreter(boost::shared_ptr< _CppFile<EncodingT> > const& value);

	FACTORY_PROTOTYPE6(CppFileInterpreter,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	CppFileInterpreter(boost::shared_ptr< Base<EncodingT> > const& path,
				boost::shared_ptr< Base<EncodingT> > const& name,
				boost::shared_ptr< Base<EncodingT> > const& linesCount,
				boost::shared_ptr< Base<EncodingT> > const& hash,
				boost::shared_ptr< Base<EncodingT> > const& analyzed,
				boost::shared_ptr< Base<EncodingT> > const& isTracked);

	boost::shared_ptr< _CppFile<EncodingT> > value() const;

	void value(boost::shared_ptr< _CppFile<EncodingT> > const& value);

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getIdentifier() const;

	boost::shared_ptr< Base<EncodingT> > getPath() const;

	boost::shared_ptr< Base<EncodingT> > getName() const;

	boost::shared_ptr< Base<EncodingT> > getLinesCount() const;

	boost::shared_ptr< Base<EncodingT> > getHash() const;

	boost::shared_ptr< Base<EncodingT> > getAnalyzed() const;

	boost::shared_ptr< Base<EncodingT> > getIsTracked() const;

	boost::shared_ptr< Base<EncodingT> > getTextFile();

	boost::shared_ptr< Base<EncodingT> > getCppFileType();

	FACTORY_PROTOTYPE1(setTextFile, In< boost::shared_ptr< Base<EncodingT> > >)
	void setTextFile(boost::shared_ptr< Base<EncodingT> > const& textFile);

	FACTORY_PROTOTYPE1(setPath, In< boost::shared_ptr< Base<EncodingT> > >)
	void setPath(boost::shared_ptr< Base<EncodingT> > const& path);

	FACTORY_PROTOTYPE1(setName, In< boost::shared_ptr< Base<EncodingT> > >)
	void setName(boost::shared_ptr< Base<EncodingT> > const& name);

	FACTORY_PROTOTYPE1(setCppFileType, In< boost::shared_ptr< Base<EncodingT> > >)
	void setCppFileType(boost::shared_ptr< Base<EncodingT> > const& cppFileType);

	FACTORY_PROTOTYPE1(setLinesCount, In< boost::shared_ptr< Base<EncodingT> > >)
	void setLinesCount(boost::shared_ptr< Base<EncodingT> > const& linesCount);

	FACTORY_PROTOTYPE1(setHash, In< boost::shared_ptr< Base<EncodingT> > >)
	void setHash(boost::shared_ptr< Base<EncodingT> > const& hash);

	FACTORY_PROTOTYPE1(setAnalyzed, In< boost::shared_ptr< Base<EncodingT> > >)
	void setAnalyzed(boost::shared_ptr< Base<EncodingT> > const& analyzed);

	FACTORY_PROTOTYPE1(setIsTracked, In< boost::shared_ptr< Base<EncodingT> > >)
	void setIsTracked(boost::shared_ptr< Base<EncodingT> > const& isTracked);

	boost::shared_ptr< Base<EncodingT> > hasTextFile() const;

	boost::shared_ptr< Base<EncodingT> > hasCppFileType() const;

	void removeTextFile();

	void removeCppFileType();

	FACTORY_PROTOTYPE1(removeCppDeclarationFunction, In< boost::shared_ptr< Base<EncodingT> > >)
	void removeCppDeclarationFunction(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE1(removeCppDefinitionFunction, In< boost::shared_ptr< Base<EncodingT> > >)
	void removeCppDefinitionFunction(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE1(removeCppClass, In< boost::shared_ptr< Base<EncodingT> > >)
	void removeCppClass(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE1(removeCppInclude, In< boost::shared_ptr< Base<EncodingT> > >)
	void removeCppInclude(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE1(removeCppVariable, In< boost::shared_ptr< Base<EncodingT> > >)
	void removeCppVariable(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE1(removeCppEnum, In< boost::shared_ptr< Base<EncodingT> > >)
	void removeCppEnum(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE1(removeCMacro, In< boost::shared_ptr< Base<EncodingT> > >)
	void removeCMacro(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE1(removeCppNotice, In< boost::shared_ptr< Base<EncodingT> > >)
	void removeCppNotice(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE2(insertCppDeclarationFunction, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void insertCppDeclarationFunction(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppDeclarationFunction);

	FACTORY_PROTOTYPE2(insertCppDefinitionFunction, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void insertCppDefinitionFunction(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppDefinitionFunction);

	FACTORY_PROTOTYPE2(insertCppClass, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void insertCppClass(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppClass);

	FACTORY_PROTOTYPE2(insertCppInclude, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void insertCppInclude(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppInclude);

	FACTORY_PROTOTYPE2(insertCppVariable, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void insertCppVariable(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppVariable);

	FACTORY_PROTOTYPE2(insertCppEnum, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void insertCppEnum(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppEnum);

	FACTORY_PROTOTYPE2(insertCMacro, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void insertCMacro(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cMacro);

	FACTORY_PROTOTYPE2(insertCppNotice, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void insertCppNotice(boost::shared_ptr< Base<EncodingT> > const& n, boost::shared_ptr< Base<EncodingT> > const& cppNotice);

	FACTORY_PROTOTYPE1(getCppDeclarationFunction, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getCppDeclarationFunction(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE1(getCppDefinitionFunction, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getCppDefinitionFunction(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE1(getCppClass, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getCppClass(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE1(getCppInclude, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getCppInclude(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE1(getCppVariable, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getCppVariable(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE1(getCppEnum, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getCppEnum(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE1(getCMacro, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getCMacro(boost::shared_ptr< Base<EncodingT> > const& n);

	FACTORY_PROTOTYPE1(getCppNotice, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getCppNotice(boost::shared_ptr< Base<EncodingT> > const& n);

	void clearCppDeclarationFunctions();

	void clearCppDefinitionFunctions();

	void clearCppClasss();

	void clearCppIncludes();

	void clearCppVariables();

	void clearCppEnums();

	void clearCMacros();

	void clearCppNotices();

	boost::shared_ptr< Base<EncodingT> > hasCppDeclarationFunctions() const;

	boost::shared_ptr< Base<EncodingT> > hasCppDefinitionFunctions() const;

	boost::shared_ptr< Base<EncodingT> > hasCppClasss() const;

	boost::shared_ptr< Base<EncodingT> > hasCppIncludes() const;

	boost::shared_ptr< Base<EncodingT> > hasCppVariables() const;

	boost::shared_ptr< Base<EncodingT> > hasCppEnums() const;

	boost::shared_ptr< Base<EncodingT> > hasCMacros() const;

	boost::shared_ptr< Base<EncodingT> > hasCppNotices() const;

	boost::shared_ptr< Base<EncodingT> > cppDeclarationFunctionsCount() const;

	boost::shared_ptr< Base<EncodingT> > cppDefinitionFunctionsCount() const;

	boost::shared_ptr< Base<EncodingT> > cppClasssCount() const;

	boost::shared_ptr< Base<EncodingT> > cppIncludesCount() const;

	boost::shared_ptr< Base<EncodingT> > cppVariablesCount() const;

	boost::shared_ptr< Base<EncodingT> > cppEnumsCount() const;

	boost::shared_ptr< Base<EncodingT> > cMacrosCount() const;

	boost::shared_ptr< Base<EncodingT> > cppNoticesCount() const;

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( CppFileInterpreter, UCS("CppFile") );
		CLASS_KEY_REGISTER6( CppFileInterpreter, UCS("CppFile") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, getIdentifier, const_t, UCS("CppFile::Identifier") );
		METHOD_KEY_REGISTER1( CppFileInterpreter, void, setTextFile, no_const_t, UCS("CppFile::TextFile") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, getTextFile, no_const_t, UCS("CppFile::TextFile") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, hasTextFile, const_t, UCS("CppFile::HasTextFile") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, void, removeTextFile, no_const_t, UCS("CppFile::removeTextFile") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, getPath, const_t, UCS("CppFile::Path") );
		METHOD_KEY_REGISTER1( CppFileInterpreter, void, setPath, no_const_t, UCS("CppFile::Path") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, getName, const_t, UCS("CppFile::Name") );
		METHOD_KEY_REGISTER1( CppFileInterpreter, void, setName, no_const_t, UCS("CppFile::Name") );
		METHOD_KEY_REGISTER1( CppFileInterpreter, void, setCppFileType, no_const_t, UCS("CppFile::CppFileType") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, getCppFileType, no_const_t, UCS("CppFile::CppFileType") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCppFileType, const_t, UCS("CppFile::HasCppFileType") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, void, removeCppFileType, no_const_t, UCS("CppFile::removeCppFileType") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, getLinesCount, const_t, UCS("CppFile::LinesCount") );
		METHOD_KEY_REGISTER1( CppFileInterpreter, void, setLinesCount, no_const_t, UCS("CppFile::LinesCount") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, getHash, const_t, UCS("CppFile::Hash") );
		METHOD_KEY_REGISTER1( CppFileInterpreter, void, setHash, no_const_t, UCS("CppFile::Hash") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, getAnalyzed, const_t, UCS("CppFile::Analyzed") );
		METHOD_KEY_REGISTER1( CppFileInterpreter, void, setAnalyzed, no_const_t, UCS("CppFile::Analyzed") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, getIsTracked, const_t, UCS("CppFile::IsTracked") );
		METHOD_KEY_REGISTER1( CppFileInterpreter, void, setIsTracked, no_const_t, UCS("CppFile::IsTracked") );
		METHOD_KEY_REGISTER1( CppFileInterpreter, void, removeCppDeclarationFunction, no_const_t, UCS("CppFile::removeCppDeclarationFunctions") );
		METHOD_KEY_REGISTER2( CppFileInterpreter, void, insertCppDeclarationFunction, no_const_t, UCS("CppFile::CppDeclarationFunctions") );
		METHOD_KEY_REGISTER1( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, getCppDeclarationFunction, no_const_t, UCS("CppFile::CppDeclarationFunctions") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, void, clearCppDeclarationFunctions, no_const_t, UCS("CppFile::ClearCppDeclarationFunctions") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCppDeclarationFunctions, const_t, UCS("CppFile::HasCppDeclarationFunctions") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, cppDeclarationFunctionsCount, const_t, UCS("CppFile::CppDeclarationFunctionsCount") );
		METHOD_KEY_REGISTER1( CppFileInterpreter, void, removeCppDefinitionFunction, no_const_t, UCS("CppFile::removeCppDefinitionFunctions") );
		METHOD_KEY_REGISTER2( CppFileInterpreter, void, insertCppDefinitionFunction, no_const_t, UCS("CppFile::CppDefinitionFunctions") );
		METHOD_KEY_REGISTER1( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, getCppDefinitionFunction, no_const_t, UCS("CppFile::CppDefinitionFunctions") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, void, clearCppDefinitionFunctions, no_const_t, UCS("CppFile::ClearCppDefinitionFunctions") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCppDefinitionFunctions, const_t, UCS("CppFile::HasCppDefinitionFunctions") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, cppDefinitionFunctionsCount, const_t, UCS("CppFile::CppDefinitionFunctionsCount") );
		METHOD_KEY_REGISTER1( CppFileInterpreter, void, removeCppClass, no_const_t, UCS("CppFile::removeCppClasss") );
		METHOD_KEY_REGISTER2( CppFileInterpreter, void, insertCppClass, no_const_t, UCS("CppFile::CppClasss") );
		METHOD_KEY_REGISTER1( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, getCppClass, no_const_t, UCS("CppFile::CppClasss") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, void, clearCppClasss, no_const_t, UCS("CppFile::ClearCppClasss") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCppClasss, const_t, UCS("CppFile::HasCppClasss") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, cppClasssCount, const_t, UCS("CppFile::CppClasssCount") );
		METHOD_KEY_REGISTER1( CppFileInterpreter, void, removeCppInclude, no_const_t, UCS("CppFile::removeCppIncludes") );
		METHOD_KEY_REGISTER2( CppFileInterpreter, void, insertCppInclude, no_const_t, UCS("CppFile::CppIncludes") );
		METHOD_KEY_REGISTER1( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, getCppInclude, no_const_t, UCS("CppFile::CppIncludes") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, void, clearCppIncludes, no_const_t, UCS("CppFile::ClearCppIncludes") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCppIncludes, const_t, UCS("CppFile::HasCppIncludes") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, cppIncludesCount, const_t, UCS("CppFile::CppIncludesCount") );
		METHOD_KEY_REGISTER1( CppFileInterpreter, void, removeCppVariable, no_const_t, UCS("CppFile::removeCppVariables") );
		METHOD_KEY_REGISTER2( CppFileInterpreter, void, insertCppVariable, no_const_t, UCS("CppFile::CppVariables") );
		METHOD_KEY_REGISTER1( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, getCppVariable, no_const_t, UCS("CppFile::CppVariables") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, void, clearCppVariables, no_const_t, UCS("CppFile::ClearCppVariables") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCppVariables, const_t, UCS("CppFile::HasCppVariables") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, cppVariablesCount, const_t, UCS("CppFile::CppVariablesCount") );
		METHOD_KEY_REGISTER1( CppFileInterpreter, void, removeCppEnum, no_const_t, UCS("CppFile::removeCppEnums") );
		METHOD_KEY_REGISTER2( CppFileInterpreter, void, insertCppEnum, no_const_t, UCS("CppFile::CppEnums") );
		METHOD_KEY_REGISTER1( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, getCppEnum, no_const_t, UCS("CppFile::CppEnums") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, void, clearCppEnums, no_const_t, UCS("CppFile::ClearCppEnums") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCppEnums, const_t, UCS("CppFile::HasCppEnums") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, cppEnumsCount, const_t, UCS("CppFile::CppEnumsCount") );
		METHOD_KEY_REGISTER1( CppFileInterpreter, void, removeCMacro, no_const_t, UCS("CppFile::removeCMacros") );
		METHOD_KEY_REGISTER2( CppFileInterpreter, void, insertCMacro, no_const_t, UCS("CppFile::CMacros") );
		METHOD_KEY_REGISTER1( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, getCMacro, no_const_t, UCS("CppFile::CMacros") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, void, clearCMacros, no_const_t, UCS("CppFile::ClearCMacros") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCMacros, const_t, UCS("CppFile::HasCMacros") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, cMacrosCount, const_t, UCS("CppFile::CMacrosCount") );
		METHOD_KEY_REGISTER1( CppFileInterpreter, void, removeCppNotice, no_const_t, UCS("CppFile::removeCppNotices") );
		METHOD_KEY_REGISTER2( CppFileInterpreter, void, insertCppNotice, no_const_t, UCS("CppFile::CppNotices") );
		METHOD_KEY_REGISTER1( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, getCppNotice, no_const_t, UCS("CppFile::CppNotices") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, void, clearCppNotices, no_const_t, UCS("CppFile::ClearCppNotices") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, hasCppNotices, const_t, UCS("CppFile::HasCppNotices") );
		METHOD_KEY_REGISTER ( CppFileInterpreter, boost::shared_ptr< Base<EncodingT> >, cppNoticesCount, const_t, UCS("CppFile::CppNoticesCount") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( UCS("CppFile") );
		CLASS_KEY_UNREGISTER6( UCS("CppFile") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::Identifier") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::TextFile") );
		METHOD_KEY_UNREGISTER1( UCS("CppFile::TextFile") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::HasTextFile") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::removeTextFile") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::Path") );
		METHOD_KEY_UNREGISTER1( UCS("CppFile::Path") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::Name") );
		METHOD_KEY_UNREGISTER1( UCS("CppFile::Name") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::CppFileType") );
		METHOD_KEY_UNREGISTER1( UCS("CppFile::CppFileType") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::HasCppFileType") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::removeCppFileType") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::LinesCount") );
		METHOD_KEY_UNREGISTER1( UCS("CppFile::LinesCount") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::Hash") );
		METHOD_KEY_UNREGISTER1( UCS("CppFile::Hash") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::Analyzed") );
		METHOD_KEY_UNREGISTER1( UCS("CppFile::Analyzed") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::IsTracked") );
		METHOD_KEY_UNREGISTER1( UCS("CppFile::IsTracked") );
		METHOD_KEY_UNREGISTER1( UCS("CppFile::removeCppDeclarationFunctions") );
		METHOD_KEY_UNREGISTER2( UCS("CppFile::CppDeclarationFunctions") );
		METHOD_KEY_UNREGISTER1( UCS("CppFile::CppDeclarationFunctions") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::ClearCppDeclarationFunctions") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::HasCppDeclarationFunctions") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::CppDeclarationFunctionsCount") );
		METHOD_KEY_UNREGISTER1( UCS("CppFile::removeCppDefinitionFunctions") );
		METHOD_KEY_UNREGISTER2( UCS("CppFile::CppDefinitionFunctions") );
		METHOD_KEY_UNREGISTER1( UCS("CppFile::CppDefinitionFunctions") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::ClearCppDefinitionFunctions") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::HasCppDefinitionFunctions") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::CppDefinitionFunctionsCount") );
		METHOD_KEY_UNREGISTER1( UCS("CppFile::removeCppClasss") );
		METHOD_KEY_UNREGISTER2( UCS("CppFile::CppClasss") );
		METHOD_KEY_UNREGISTER1( UCS("CppFile::CppClasss") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::ClearCppClasss") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::HasCppClasss") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::CppClasssCount") );
		METHOD_KEY_UNREGISTER1( UCS("CppFile::removeCppIncludes") );
		METHOD_KEY_UNREGISTER2( UCS("CppFile::CppIncludes") );
		METHOD_KEY_UNREGISTER1( UCS("CppFile::CppIncludes") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::ClearCppIncludes") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::HasCppIncludes") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::CppIncludesCount") );
		METHOD_KEY_UNREGISTER1( UCS("CppFile::removeCppVariables") );
		METHOD_KEY_UNREGISTER2( UCS("CppFile::CppVariables") );
		METHOD_KEY_UNREGISTER1( UCS("CppFile::CppVariables") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::ClearCppVariables") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::HasCppVariables") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::CppVariablesCount") );
		METHOD_KEY_UNREGISTER1( UCS("CppFile::removeCppEnums") );
		METHOD_KEY_UNREGISTER2( UCS("CppFile::CppEnums") );
		METHOD_KEY_UNREGISTER1( UCS("CppFile::CppEnums") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::ClearCppEnums") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::HasCppEnums") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::CppEnumsCount") );
		METHOD_KEY_UNREGISTER1( UCS("CppFile::removeCMacros") );
		METHOD_KEY_UNREGISTER2( UCS("CppFile::CMacros") );
		METHOD_KEY_UNREGISTER1( UCS("CppFile::CMacros") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::ClearCMacros") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::HasCMacros") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::CMacrosCount") );
		METHOD_KEY_UNREGISTER1( UCS("CppFile::removeCppNotices") );
		METHOD_KEY_UNREGISTER2( UCS("CppFile::CppNotices") );
		METHOD_KEY_UNREGISTER1( UCS("CppFile::CppNotices") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::ClearCppNotices") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::HasCppNotices") );
		METHOD_KEY_UNREGISTER ( UCS("CppFile::CppNoticesCount") );
	FACTORY_END_UNREGISTER
};

template <class EncodingT>
bool check_cppFile(boost::shared_ptr< Base<EncodingT> > const& val, boost::shared_ptr< _CppFile<EncodingT> >& o);

template <class EncodingT>
bool reset_cppFile(boost::shared_ptr< Base<EncodingT> >& val, boost::shared_ptr< _CppFile<EncodingT> > const& o);

NAMESPACE_END

#undef C
#undef A

#include "cppFileInterpreter_impl.hpp"

#endif
