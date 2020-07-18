/* 
 * cppInheritanceInterpreterAccess.hpp
 *
 *
 * @date 14-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPINHERITANCE_INTERPRETER_ACCESS_HPP_
#define _CPPINHERITANCE_INTERPRETER_ACCESS_HPP_

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
class CppInheritanceInterpreterAccess
: public Base<EncodingT>
{
private:
	_CppInheritanceAccess<EncodingT>* m_object;
	std::string m_errorText;
	bool m_error;

public:
	CppInheritanceInterpreterAccess();

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getAllCppInheritances();

	FACTORY_PROTOTYPE1(getManyCppInheritances, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getManyCppInheritances(const boost::shared_ptr< Base<EncodingT> >& filter);

	FACTORY_PROTOTYPE1(getOneCppInheritance,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getOneCppInheritance(boost::shared_ptr< Base<EncodingT> > const& identifier);

	FACTORY_PROTOTYPE2(selectOneCppInheritance,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > selectOneCppInheritance(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE2(selectManyCppInheritances, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > selectManyCppInheritances(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	void cancelSelection();

	FACTORY_PROTOTYPE1(isSelectedCppInheritance, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isSelectedCppInheritance(const boost::shared_ptr< Base<EncodingT> >& cppInheritance);

	FACTORY_PROTOTYPE1(fillDerived, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void fillDerived(boost::shared_ptr< Base<EncodingT> >& cppInheritance);

	FACTORY_PROTOTYPE1(isModifiedCppInheritance, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isModifiedCppInheritance(const boost::shared_ptr< Base<EncodingT> >& cppInheritance);

	FACTORY_PROTOTYPE1(updateCppInheritance, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void updateCppInheritance(boost::shared_ptr< Base<EncodingT> >& cppInheritance);

	FACTORY_PROTOTYPE1(insertCppInheritance, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void insertCppInheritance(boost::shared_ptr< Base<EncodingT> >& cppInheritance);

	FACTORY_PROTOTYPE1(deleteCppInheritance, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void deleteCppInheritance(boost::shared_ptr< Base<EncodingT> >& cppInheritance);

	void setError(const std::exception& e);

	void clearError();

	FACTORY_PROTOTYPE1(getError, InOut< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getError(boost::shared_ptr< Base<EncodingT> >& text) const;

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( CppInheritanceInterpreterAccess, UCS("CppInheritanceAccess") );
		METHOD_KEY_REGISTER ( CppInheritanceInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getAllCppInheritances, no_const_t, UCS("CppInheritanceAccess::GetAllCppInheritances") );
		METHOD_KEY_REGISTER1( CppInheritanceInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getManyCppInheritances, no_const_t, UCS("CppInheritanceAccess::GetManyCppInheritances") );
		METHOD_KEY_REGISTER1( CppInheritanceInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getOneCppInheritance, no_const_t, UCS("CppInheritanceAccess::GetOneCppInheritance") );
		METHOD_KEY_REGISTER2( CppInheritanceInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectOneCppInheritance, no_const_t, UCS("CppInheritanceAccess::SelectOneCppInheritance") );
		METHOD_KEY_REGISTER2( CppInheritanceInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectManyCppInheritances, no_const_t, UCS("CppInheritanceAccess::SelectManyCppInheritances") );
		METHOD_KEY_REGISTER ( CppInheritanceInterpreterAccess, void, cancelSelection, no_const_t, UCS("CppInheritanceAccess::CancelSelection") );
		METHOD_KEY_REGISTER1( CppInheritanceInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isSelectedCppInheritance, no_const_t, UCS("CppInheritanceAccess::IsSelectedCppInheritance") );
		METHOD_KEY_REGISTER1( CppInheritanceInterpreterAccess, void, fillDerived, no_const_t, UCS("CppInheritanceAccess::FillDerived") );
		METHOD_KEY_REGISTER1( CppInheritanceInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isModifiedCppInheritance, no_const_t, UCS("CppInheritanceAccess::IsModifiedCppInheritance") );
		METHOD_KEY_REGISTER1( CppInheritanceInterpreterAccess, void, updateCppInheritance, no_const_t, UCS("CppInheritanceAccess::UpdateCppInheritance") );
		METHOD_KEY_REGISTER1( CppInheritanceInterpreterAccess, void, insertCppInheritance, no_const_t, UCS("CppInheritanceAccess::InsertCppInheritance") );
		METHOD_KEY_REGISTER1( CppInheritanceInterpreterAccess, void, deleteCppInheritance, no_const_t, UCS("CppInheritanceAccess::DeleteCppInheritance") );
		METHOD_KEY_REGISTER1( CppInheritanceInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getError, const_t, UCS("CppInheritanceAccess::GetError") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( UCS("CppInheritanceAccess") );
		METHOD_KEY_UNREGISTER ( UCS("CppInheritanceAccess::GetAllCppInheritances") );
		METHOD_KEY_UNREGISTER1( UCS("CppInheritanceAccess::GetManyCppInheritances") );
		METHOD_KEY_UNREGISTER1( UCS("CppInheritanceAccess::GetOneCppInheritance") );
		METHOD_KEY_UNREGISTER2( UCS("CppInheritanceAccess::SelectOneCppInheritance") );
		METHOD_KEY_UNREGISTER2( UCS("CppInheritanceAccess::SelectManyCppInheritances") );
		METHOD_KEY_UNREGISTER ( UCS("CppInheritanceAccess::CancelSelection") );
		METHOD_KEY_UNREGISTER1( UCS("CppInheritanceAccess::IsSelectedCppInheritance") );
		METHOD_KEY_UNREGISTER1( UCS("CppInheritanceAccess::FillDerived") );
		METHOD_KEY_UNREGISTER1( UCS("CppInheritanceAccess::IsModifiedCppInheritance") );
		METHOD_KEY_UNREGISTER1( UCS("CppInheritanceAccess::UpdateCppInheritance") );
		METHOD_KEY_UNREGISTER1( UCS("CppInheritanceAccess::InsertCppInheritance") );
		METHOD_KEY_UNREGISTER1( UCS("CppInheritanceAccess::DeleteCppInheritance") );
		METHOD_KEY_UNREGISTER1( UCS("CppInheritanceAccess::GetError") );
	FACTORY_END_UNREGISTER

	boost::shared_ptr< Base<EncodingT> > convert_array(const std::vector< boost::shared_ptr< _CppInheritance<EncodingT> > >& value) const;
};

NAMESPACE_END

#undef C
#undef A

#include "cppInheritanceInterpreterAccess_impl.hpp"

#endif
