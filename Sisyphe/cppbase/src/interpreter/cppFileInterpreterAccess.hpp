/* 
 * cppFileInterpreterAccess.hpp
 *
 *
 * @date 25-06-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPFILE_INTERPRETER_ACCESS_HPP_
#define _CPPFILE_INTERPRETER_ACCESS_HPP_

#include "config.hpp"
#include "Macros.hpp"
#include "String.hpp"

#include "cppBaseExport.hpp"
#include "cppBaseData.h"
#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

using namespace log4cpp;
using namespace fctr;
using namespace enc;
using namespace data_access;
using namespace boost;

template <class EncodingT>
class CppFileInterpreterAccess
: public Base<EncodingT>
{
private:
	_CppFileAccess<EncodingT>* m_object;
	std::string m_errorText;
	bool m_error;

public:
	CppFileInterpreterAccess();

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getAllCppFiles();

	FACTORY_PROTOTYPE1(getManyCppFiles, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getManyCppFiles(const boost::shared_ptr< Base<EncodingT> >& filter);

	FACTORY_PROTOTYPE1(getOneCppFile,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getOneCppFile(boost::shared_ptr< Base<EncodingT> > const& identifier);

	FACTORY_PROTOTYPE2(selectOneCppFile,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > selectOneCppFile(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE2(selectManyCppFiles, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > selectManyCppFiles(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	void cancelSelection();

	FACTORY_PROTOTYPE1(isSelectedCppFile, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isSelectedCppFile(const boost::shared_ptr< Base<EncodingT> >& cppFile);

	FACTORY_PROTOTYPE1(fillTextFile, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void fillTextFile(boost::shared_ptr< Base<EncodingT> >& cppFile);

	FACTORY_PROTOTYPE1(fillCppFileType, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void fillCppFileType(boost::shared_ptr< Base<EncodingT> >& cppFile);

	FACTORY_PROTOTYPE2(fillAllCppDeclarationFunctions, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillAllCppDeclarationFunctions(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillOneCppDeclarationFunction,
				InOut< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	void fillOneCppDeclarationFunction(boost::shared_ptr< Base<EncodingT> >& refCppFile,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillManyCppDeclarationFunctions, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillManyCppDeclarationFunctions(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE2(fillAllCppDefinitionFunctions, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillAllCppDefinitionFunctions(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillOneCppDefinitionFunction,
				InOut< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	void fillOneCppDefinitionFunction(boost::shared_ptr< Base<EncodingT> >& refCppFile,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillManyCppDefinitionFunctions, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillManyCppDefinitionFunctions(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE2(fillAllCppClasss, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillAllCppClasss(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillOneCppClass,
				InOut< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	void fillOneCppClass(boost::shared_ptr< Base<EncodingT> >& refCppFile,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillManyCppClasss, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillManyCppClasss(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE2(fillAllCppIncludes, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillAllCppIncludes(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillOneCppInclude,
				InOut< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	void fillOneCppInclude(boost::shared_ptr< Base<EncodingT> >& refCppFile,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillManyCppIncludes, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillManyCppIncludes(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE2(fillAllCppVariables, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillAllCppVariables(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillOneCppVariable,
				InOut< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	void fillOneCppVariable(boost::shared_ptr< Base<EncodingT> >& refCppFile,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillManyCppVariables, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillManyCppVariables(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE2(fillAllCppEnums, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillAllCppEnums(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillOneCppEnum,
				InOut< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	void fillOneCppEnum(boost::shared_ptr< Base<EncodingT> >& refCppFile,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillManyCppEnums, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillManyCppEnums(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE2(fillAllCMacros, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillAllCMacros(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillOneCMacro,
				InOut< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	void fillOneCMacro(boost::shared_ptr< Base<EncodingT> >& refCppFile,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillManyCMacros, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillManyCMacros(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE2(fillAllCppNotices, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillAllCppNotices(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillOneCppNotice,
				InOut< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	void fillOneCppNotice(boost::shared_ptr< Base<EncodingT> >& refCppFile,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillManyCppNotices, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillManyCppNotices(boost::shared_ptr< Base<EncodingT> >& cppFile, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE1(isModifiedCppFile, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isModifiedCppFile(const boost::shared_ptr< Base<EncodingT> >& cppFile);

	FACTORY_PROTOTYPE1(updateCppFile, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void updateCppFile(boost::shared_ptr< Base<EncodingT> >& cppFile);

	FACTORY_PROTOTYPE1(insertCppFile, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void insertCppFile(boost::shared_ptr< Base<EncodingT> >& cppFile);

	FACTORY_PROTOTYPE1(deleteCppFile, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void deleteCppFile(boost::shared_ptr< Base<EncodingT> >& cppFile);

	void setError(const std::exception& e);

	void clearError();

	FACTORY_PROTOTYPE1(getError, InOut< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getError(boost::shared_ptr< Base<EncodingT> >& text) const;

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( CppFileInterpreterAccess, UCS("CppFileAccess") );
		METHOD_KEY_REGISTER ( CppFileInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getAllCppFiles, no_const_t, UCS("CppFileAccess::GetAllCppFiles") );
		METHOD_KEY_REGISTER1( CppFileInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getManyCppFiles, no_const_t, UCS("CppFileAccess::GetManyCppFiles") );
		METHOD_KEY_REGISTER1( CppFileInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getOneCppFile, no_const_t, UCS("CppFileAccess::GetOneCppFile") );
		METHOD_KEY_REGISTER2( CppFileInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectOneCppFile, no_const_t, UCS("CppFileAccess::SelectOneCppFile") );
		METHOD_KEY_REGISTER2( CppFileInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectManyCppFiles, no_const_t, UCS("CppFileAccess::SelectManyCppFiles") );
		METHOD_KEY_REGISTER ( CppFileInterpreterAccess, void, cancelSelection, no_const_t, UCS("CppFileAccess::CancelSelection") );
		METHOD_KEY_REGISTER1( CppFileInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isSelectedCppFile, no_const_t, UCS("CppFileAccess::IsSelectedCppFile") );
		METHOD_KEY_REGISTER1( CppFileInterpreterAccess, void, fillTextFile, no_const_t, UCS("CppFileAccess::FillTextFile") );
		METHOD_KEY_REGISTER1( CppFileInterpreterAccess, void, fillCppFileType, no_const_t, UCS("CppFileAccess::FillCppFileType") );
		METHOD_KEY_REGISTER2( CppFileInterpreterAccess, void, fillAllCppDeclarationFunctions, no_const_t, UCS("CppFileAccess::FillAllCppDeclarationFunctions") );
		METHOD_KEY_REGISTER3( CppFileInterpreterAccess, void, fillOneCppDeclarationFunction, no_const_t, UCS("CppFileAccess::FillOneCppDeclarationFunction") );
		METHOD_KEY_REGISTER3( CppFileInterpreterAccess, void, fillManyCppDeclarationFunctions, no_const_t, UCS("CppFileAccess::FillManyCppDeclarationFunctions") );
		METHOD_KEY_REGISTER2( CppFileInterpreterAccess, void, fillAllCppDefinitionFunctions, no_const_t, UCS("CppFileAccess::FillAllCppDefinitionFunctions") );
		METHOD_KEY_REGISTER3( CppFileInterpreterAccess, void, fillOneCppDefinitionFunction, no_const_t, UCS("CppFileAccess::FillOneCppDefinitionFunction") );
		METHOD_KEY_REGISTER3( CppFileInterpreterAccess, void, fillManyCppDefinitionFunctions, no_const_t, UCS("CppFileAccess::FillManyCppDefinitionFunctions") );
		METHOD_KEY_REGISTER2( CppFileInterpreterAccess, void, fillAllCppClasss, no_const_t, UCS("CppFileAccess::FillAllCppClasss") );
		METHOD_KEY_REGISTER3( CppFileInterpreterAccess, void, fillOneCppClass, no_const_t, UCS("CppFileAccess::FillOneCppClass") );
		METHOD_KEY_REGISTER3( CppFileInterpreterAccess, void, fillManyCppClasss, no_const_t, UCS("CppFileAccess::FillManyCppClasss") );
		METHOD_KEY_REGISTER2( CppFileInterpreterAccess, void, fillAllCppIncludes, no_const_t, UCS("CppFileAccess::FillAllCppIncludes") );
		METHOD_KEY_REGISTER3( CppFileInterpreterAccess, void, fillOneCppInclude, no_const_t, UCS("CppFileAccess::FillOneCppInclude") );
		METHOD_KEY_REGISTER3( CppFileInterpreterAccess, void, fillManyCppIncludes, no_const_t, UCS("CppFileAccess::FillManyCppIncludes") );
		METHOD_KEY_REGISTER2( CppFileInterpreterAccess, void, fillAllCppVariables, no_const_t, UCS("CppFileAccess::FillAllCppVariables") );
		METHOD_KEY_REGISTER3( CppFileInterpreterAccess, void, fillOneCppVariable, no_const_t, UCS("CppFileAccess::FillOneCppVariable") );
		METHOD_KEY_REGISTER3( CppFileInterpreterAccess, void, fillManyCppVariables, no_const_t, UCS("CppFileAccess::FillManyCppVariables") );
		METHOD_KEY_REGISTER2( CppFileInterpreterAccess, void, fillAllCppEnums, no_const_t, UCS("CppFileAccess::FillAllCppEnums") );
		METHOD_KEY_REGISTER3( CppFileInterpreterAccess, void, fillOneCppEnum, no_const_t, UCS("CppFileAccess::FillOneCppEnum") );
		METHOD_KEY_REGISTER3( CppFileInterpreterAccess, void, fillManyCppEnums, no_const_t, UCS("CppFileAccess::FillManyCppEnums") );
		METHOD_KEY_REGISTER2( CppFileInterpreterAccess, void, fillAllCMacros, no_const_t, UCS("CppFileAccess::FillAllCMacros") );
		METHOD_KEY_REGISTER3( CppFileInterpreterAccess, void, fillOneCMacro, no_const_t, UCS("CppFileAccess::FillOneCMacro") );
		METHOD_KEY_REGISTER3( CppFileInterpreterAccess, void, fillManyCMacros, no_const_t, UCS("CppFileAccess::FillManyCMacros") );
		METHOD_KEY_REGISTER2( CppFileInterpreterAccess, void, fillAllCppNotices, no_const_t, UCS("CppFileAccess::FillAllCppNotices") );
		METHOD_KEY_REGISTER3( CppFileInterpreterAccess, void, fillOneCppNotice, no_const_t, UCS("CppFileAccess::FillOneCppNotice") );
		METHOD_KEY_REGISTER3( CppFileInterpreterAccess, void, fillManyCppNotices, no_const_t, UCS("CppFileAccess::FillManyCppNotices") );
		METHOD_KEY_REGISTER1( CppFileInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isModifiedCppFile, no_const_t, UCS("CppFileAccess::IsModifiedCppFile") );
		METHOD_KEY_REGISTER1( CppFileInterpreterAccess, void, updateCppFile, no_const_t, UCS("CppFileAccess::UpdateCppFile") );
		METHOD_KEY_REGISTER1( CppFileInterpreterAccess, void, insertCppFile, no_const_t, UCS("CppFileAccess::InsertCppFile") );
		METHOD_KEY_REGISTER1( CppFileInterpreterAccess, void, deleteCppFile, no_const_t, UCS("CppFileAccess::DeleteCppFile") );
		METHOD_KEY_REGISTER1( CppFileInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getError, const_t, UCS("CppFileAccess::GetError") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( UCS("CppFileAccess") );
		METHOD_KEY_UNREGISTER ( UCS("CppFileAccess::GetAllCppFiles") );
		METHOD_KEY_UNREGISTER1( UCS("CppFileAccess::GetManyCppFiles") );
		METHOD_KEY_UNREGISTER1( UCS("CppFileAccess::GetOneCppFile") );
		METHOD_KEY_UNREGISTER2( UCS("CppFileAccess::SelectOneCppFile") );
		METHOD_KEY_UNREGISTER2( UCS("CppFileAccess::SelectManyCppFiles") );
		METHOD_KEY_UNREGISTER ( UCS("CppFileAccess::CancelSelection") );
		METHOD_KEY_UNREGISTER1( UCS("CppFileAccess::IsSelectedCppFile") );
		METHOD_KEY_UNREGISTER1( UCS("CppFileAccess::FillTextFile") );
		METHOD_KEY_UNREGISTER1( UCS("CppFileAccess::FillCppFileType") );
		METHOD_KEY_UNREGISTER2( UCS("CppFileAccess::FillAllCppDeclarationFunctions") );
		METHOD_KEY_UNREGISTER3( UCS("CppFileAccess::FillOneCppDeclarationFunction") );
		METHOD_KEY_UNREGISTER3( UCS("CppFileAccess::FillManyCppDeclarationFunctions") );
		METHOD_KEY_UNREGISTER2( UCS("CppFileAccess::FillAllCppDefinitionFunctions") );
		METHOD_KEY_UNREGISTER3( UCS("CppFileAccess::FillOneCppDefinitionFunction") );
		METHOD_KEY_UNREGISTER3( UCS("CppFileAccess::FillManyCppDefinitionFunctions") );
		METHOD_KEY_UNREGISTER2( UCS("CppFileAccess::FillAllCppClasss") );
		METHOD_KEY_UNREGISTER3( UCS("CppFileAccess::FillOneCppClass") );
		METHOD_KEY_UNREGISTER3( UCS("CppFileAccess::FillManyCppClasss") );
		METHOD_KEY_UNREGISTER2( UCS("CppFileAccess::FillAllCppIncludes") );
		METHOD_KEY_UNREGISTER3( UCS("CppFileAccess::FillOneCppInclude") );
		METHOD_KEY_UNREGISTER3( UCS("CppFileAccess::FillManyCppIncludes") );
		METHOD_KEY_UNREGISTER2( UCS("CppFileAccess::FillAllCppVariables") );
		METHOD_KEY_UNREGISTER3( UCS("CppFileAccess::FillOneCppVariable") );
		METHOD_KEY_UNREGISTER3( UCS("CppFileAccess::FillManyCppVariables") );
		METHOD_KEY_UNREGISTER2( UCS("CppFileAccess::FillAllCppEnums") );
		METHOD_KEY_UNREGISTER3( UCS("CppFileAccess::FillOneCppEnum") );
		METHOD_KEY_UNREGISTER3( UCS("CppFileAccess::FillManyCppEnums") );
		METHOD_KEY_UNREGISTER2( UCS("CppFileAccess::FillAllCMacros") );
		METHOD_KEY_UNREGISTER3( UCS("CppFileAccess::FillOneCMacro") );
		METHOD_KEY_UNREGISTER3( UCS("CppFileAccess::FillManyCMacros") );
		METHOD_KEY_UNREGISTER2( UCS("CppFileAccess::FillAllCppNotices") );
		METHOD_KEY_UNREGISTER3( UCS("CppFileAccess::FillOneCppNotice") );
		METHOD_KEY_UNREGISTER3( UCS("CppFileAccess::FillManyCppNotices") );
		METHOD_KEY_UNREGISTER1( UCS("CppFileAccess::IsModifiedCppFile") );
		METHOD_KEY_UNREGISTER1( UCS("CppFileAccess::UpdateCppFile") );
		METHOD_KEY_UNREGISTER1( UCS("CppFileAccess::InsertCppFile") );
		METHOD_KEY_UNREGISTER1( UCS("CppFileAccess::DeleteCppFile") );
		METHOD_KEY_UNREGISTER1( UCS("CppFileAccess::GetError") );
	FACTORY_END_UNREGISTER

	boost::shared_ptr< Base<EncodingT> > convert_array(const std::vector< boost::shared_ptr< _CppFile<EncodingT> > >& value) const;
};

NAMESPACE_END

#undef C
#undef A

#include "cppFileInterpreterAccess_impl.hpp"

#endif
