/* 
 * cppClassInterpreterAccess.hpp
 *
 *
 * @date 26-03-2019
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPCLASS_INTERPRETER_ACCESS_HPP_
#define _CPPCLASS_INTERPRETER_ACCESS_HPP_

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
class CppClassInterpreterAccess
: public Base<EncodingT>
{
private:
	_CppClassAccess<EncodingT>* m_object;
	std::string m_errorText;
	bool m_error;

public:
	CppClassInterpreterAccess();

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getAllCppClasss();

	FACTORY_PROTOTYPE1(getManyCppClasss, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getManyCppClasss(const boost::shared_ptr< Base<EncodingT> >& filter);

	FACTORY_PROTOTYPE1(getOneCppClass,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getOneCppClass(boost::shared_ptr< Base<EncodingT> > const& identifier);

	FACTORY_PROTOTYPE2(selectOneCppClass,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > selectOneCppClass(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE2(selectManyCppClasss, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > selectManyCppClasss(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	void cancelSelection();

	FACTORY_PROTOTYPE1(isSelectedCppClass, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isSelectedCppClass(const boost::shared_ptr< Base<EncodingT> >& cppClass);

	FACTORY_PROTOTYPE1(fillEncapsulationClass, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void fillEncapsulationClass(boost::shared_ptr< Base<EncodingT> >& cppClass);

	FACTORY_PROTOTYPE1(fillCppFile, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void fillCppFile(boost::shared_ptr< Base<EncodingT> >& cppClass);

	FACTORY_PROTOTYPE2(fillAllCppInheritances, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillAllCppInheritances(boost::shared_ptr< Base<EncodingT> >& cppClass, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillOneCppInheritance,
				InOut< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	void fillOneCppInheritance(boost::shared_ptr< Base<EncodingT> >& refCppClass,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillManyCppInheritances, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillManyCppInheritances(boost::shared_ptr< Base<EncodingT> >& cppClass, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE2(fillAllCppFunctions, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillAllCppFunctions(boost::shared_ptr< Base<EncodingT> >& cppClass, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillOneCppFunction,
				InOut< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	void fillOneCppFunction(boost::shared_ptr< Base<EncodingT> >& refCppClass,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillManyCppFunctions, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillManyCppFunctions(boost::shared_ptr< Base<EncodingT> >& cppClass, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE2(fillAllInternClasses, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillAllInternClasses(boost::shared_ptr< Base<EncodingT> >& cppClass, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillOneInternClasse,
				InOut< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	void fillOneInternClasse(boost::shared_ptr< Base<EncodingT> >& refCppClass,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillManyInternClasses, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillManyInternClasses(boost::shared_ptr< Base<EncodingT> >& cppClass, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE2(fillAllCppAttributes, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillAllCppAttributes(boost::shared_ptr< Base<EncodingT> >& cppClass, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillOneCppAttribute,
				InOut< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	void fillOneCppAttribute(boost::shared_ptr< Base<EncodingT> >& refCppClass,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillManyCppAttributes, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillManyCppAttributes(boost::shared_ptr< Base<EncodingT> >& cppClass, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE2(fillAllCppEnums, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillAllCppEnums(boost::shared_ptr< Base<EncodingT> >& cppClass, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillOneCppEnum,
				InOut< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	void fillOneCppEnum(boost::shared_ptr< Base<EncodingT> >& refCppClass,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillManyCppEnums, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillManyCppEnums(boost::shared_ptr< Base<EncodingT> >& cppClass, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE1(isModifiedCppClass, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isModifiedCppClass(const boost::shared_ptr< Base<EncodingT> >& cppClass);

	FACTORY_PROTOTYPE1(updateCppClass, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void updateCppClass(boost::shared_ptr< Base<EncodingT> >& cppClass);

	FACTORY_PROTOTYPE1(insertCppClass, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void insertCppClass(boost::shared_ptr< Base<EncodingT> >& cppClass);

	FACTORY_PROTOTYPE1(deleteCppClass, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void deleteCppClass(boost::shared_ptr< Base<EncodingT> >& cppClass);

	void setError(const std::exception& e);

	void clearError();

	FACTORY_PROTOTYPE1(getError, InOut< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getError(boost::shared_ptr< Base<EncodingT> >& text) const;

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( CppClassInterpreterAccess, UCS("CppClassAccess") );
		METHOD_KEY_REGISTER ( CppClassInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getAllCppClasss, no_const_t, UCS("CppClassAccess::GetAllCppClasss") );
		METHOD_KEY_REGISTER1( CppClassInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getManyCppClasss, no_const_t, UCS("CppClassAccess::GetManyCppClasss") );
		METHOD_KEY_REGISTER1( CppClassInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getOneCppClass, no_const_t, UCS("CppClassAccess::GetOneCppClass") );
		METHOD_KEY_REGISTER2( CppClassInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectOneCppClass, no_const_t, UCS("CppClassAccess::SelectOneCppClass") );
		METHOD_KEY_REGISTER2( CppClassInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectManyCppClasss, no_const_t, UCS("CppClassAccess::SelectManyCppClasss") );
		METHOD_KEY_REGISTER ( CppClassInterpreterAccess, void, cancelSelection, no_const_t, UCS("CppClassAccess::CancelSelection") );
		METHOD_KEY_REGISTER1( CppClassInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isSelectedCppClass, no_const_t, UCS("CppClassAccess::IsSelectedCppClass") );
		METHOD_KEY_REGISTER1( CppClassInterpreterAccess, void, fillEncapsulationClass, no_const_t, UCS("CppClassAccess::FillEncapsulationClass") );
		METHOD_KEY_REGISTER1( CppClassInterpreterAccess, void, fillCppFile, no_const_t, UCS("CppClassAccess::FillCppFile") );
		METHOD_KEY_REGISTER2( CppClassInterpreterAccess, void, fillAllCppInheritances, no_const_t, UCS("CppClassAccess::FillAllCppInheritances") );
		METHOD_KEY_REGISTER3( CppClassInterpreterAccess, void, fillOneCppInheritance, no_const_t, UCS("CppClassAccess::FillOneCppInheritance") );
		METHOD_KEY_REGISTER3( CppClassInterpreterAccess, void, fillManyCppInheritances, no_const_t, UCS("CppClassAccess::FillManyCppInheritances") );
		METHOD_KEY_REGISTER2( CppClassInterpreterAccess, void, fillAllCppFunctions, no_const_t, UCS("CppClassAccess::FillAllCppFunctions") );
		METHOD_KEY_REGISTER3( CppClassInterpreterAccess, void, fillOneCppFunction, no_const_t, UCS("CppClassAccess::FillOneCppFunction") );
		METHOD_KEY_REGISTER3( CppClassInterpreterAccess, void, fillManyCppFunctions, no_const_t, UCS("CppClassAccess::FillManyCppFunctions") );
		METHOD_KEY_REGISTER2( CppClassInterpreterAccess, void, fillAllInternClasses, no_const_t, UCS("CppClassAccess::FillAllInternClasses") );
		METHOD_KEY_REGISTER3( CppClassInterpreterAccess, void, fillOneInternClasse, no_const_t, UCS("CppClassAccess::FillOneInternClasse") );
		METHOD_KEY_REGISTER3( CppClassInterpreterAccess, void, fillManyInternClasses, no_const_t, UCS("CppClassAccess::FillManyInternClasses") );
		METHOD_KEY_REGISTER2( CppClassInterpreterAccess, void, fillAllCppAttributes, no_const_t, UCS("CppClassAccess::FillAllCppAttributes") );
		METHOD_KEY_REGISTER3( CppClassInterpreterAccess, void, fillOneCppAttribute, no_const_t, UCS("CppClassAccess::FillOneCppAttribute") );
		METHOD_KEY_REGISTER3( CppClassInterpreterAccess, void, fillManyCppAttributes, no_const_t, UCS("CppClassAccess::FillManyCppAttributes") );
		METHOD_KEY_REGISTER2( CppClassInterpreterAccess, void, fillAllCppEnums, no_const_t, UCS("CppClassAccess::FillAllCppEnums") );
		METHOD_KEY_REGISTER3( CppClassInterpreterAccess, void, fillOneCppEnum, no_const_t, UCS("CppClassAccess::FillOneCppEnum") );
		METHOD_KEY_REGISTER3( CppClassInterpreterAccess, void, fillManyCppEnums, no_const_t, UCS("CppClassAccess::FillManyCppEnums") );
		METHOD_KEY_REGISTER1( CppClassInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isModifiedCppClass, no_const_t, UCS("CppClassAccess::IsModifiedCppClass") );
		METHOD_KEY_REGISTER1( CppClassInterpreterAccess, void, updateCppClass, no_const_t, UCS("CppClassAccess::UpdateCppClass") );
		METHOD_KEY_REGISTER1( CppClassInterpreterAccess, void, insertCppClass, no_const_t, UCS("CppClassAccess::InsertCppClass") );
		METHOD_KEY_REGISTER1( CppClassInterpreterAccess, void, deleteCppClass, no_const_t, UCS("CppClassAccess::DeleteCppClass") );
		METHOD_KEY_REGISTER1( CppClassInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getError, const_t, UCS("CppClassAccess::GetError") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( UCS("CppClassAccess") );
		METHOD_KEY_UNREGISTER ( UCS("CppClassAccess::GetAllCppClasss") );
		METHOD_KEY_UNREGISTER1( UCS("CppClassAccess::GetManyCppClasss") );
		METHOD_KEY_UNREGISTER1( UCS("CppClassAccess::GetOneCppClass") );
		METHOD_KEY_UNREGISTER2( UCS("CppClassAccess::SelectOneCppClass") );
		METHOD_KEY_UNREGISTER2( UCS("CppClassAccess::SelectManyCppClasss") );
		METHOD_KEY_UNREGISTER ( UCS("CppClassAccess::CancelSelection") );
		METHOD_KEY_UNREGISTER1( UCS("CppClassAccess::IsSelectedCppClass") );
		METHOD_KEY_UNREGISTER1( UCS("CppClassAccess::FillEncapsulationClass") );
		METHOD_KEY_UNREGISTER1( UCS("CppClassAccess::FillCppFile") );
		METHOD_KEY_UNREGISTER2( UCS("CppClassAccess::FillAllCppInheritances") );
		METHOD_KEY_UNREGISTER3( UCS("CppClassAccess::FillOneCppInheritance") );
		METHOD_KEY_UNREGISTER3( UCS("CppClassAccess::FillManyCppInheritances") );
		METHOD_KEY_UNREGISTER2( UCS("CppClassAccess::FillAllCppFunctions") );
		METHOD_KEY_UNREGISTER3( UCS("CppClassAccess::FillOneCppFunction") );
		METHOD_KEY_UNREGISTER3( UCS("CppClassAccess::FillManyCppFunctions") );
		METHOD_KEY_UNREGISTER2( UCS("CppClassAccess::FillAllInternClasses") );
		METHOD_KEY_UNREGISTER3( UCS("CppClassAccess::FillOneInternClasse") );
		METHOD_KEY_UNREGISTER3( UCS("CppClassAccess::FillManyInternClasses") );
		METHOD_KEY_UNREGISTER2( UCS("CppClassAccess::FillAllCppAttributes") );
		METHOD_KEY_UNREGISTER3( UCS("CppClassAccess::FillOneCppAttribute") );
		METHOD_KEY_UNREGISTER3( UCS("CppClassAccess::FillManyCppAttributes") );
		METHOD_KEY_UNREGISTER2( UCS("CppClassAccess::FillAllCppEnums") );
		METHOD_KEY_UNREGISTER3( UCS("CppClassAccess::FillOneCppEnum") );
		METHOD_KEY_UNREGISTER3( UCS("CppClassAccess::FillManyCppEnums") );
		METHOD_KEY_UNREGISTER1( UCS("CppClassAccess::IsModifiedCppClass") );
		METHOD_KEY_UNREGISTER1( UCS("CppClassAccess::UpdateCppClass") );
		METHOD_KEY_UNREGISTER1( UCS("CppClassAccess::InsertCppClass") );
		METHOD_KEY_UNREGISTER1( UCS("CppClassAccess::DeleteCppClass") );
		METHOD_KEY_UNREGISTER1( UCS("CppClassAccess::GetError") );
	FACTORY_END_UNREGISTER

	boost::shared_ptr< Base<EncodingT> > convert_array(const std::vector< boost::shared_ptr< _CppClass<EncodingT> > >& value) const;
};

NAMESPACE_END

#undef C
#undef A

#include "cppClassInterpreterAccess_impl.hpp"

#endif
