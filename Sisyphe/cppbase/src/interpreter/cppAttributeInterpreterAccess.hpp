/* 
 * cppAttributeInterpreterAccess.hpp
 *
 *
 * @date 26-03-2019
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPATTRIBUTE_INTERPRETER_ACCESS_HPP_
#define _CPPATTRIBUTE_INTERPRETER_ACCESS_HPP_

#include "config.hpp"
#include "macros.hpp"
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
class CppAttributeInterpreterAccess
: public Base<EncodingT>
{
private:
	_CppAttributeAccess<EncodingT>* m_object;
	std::string m_errorText;
	bool m_error;

public:
	CppAttributeInterpreterAccess();

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getAllCppAttributes();

	FACTORY_PROTOTYPE1(getManyCppAttributes, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getManyCppAttributes(const boost::shared_ptr< Base<EncodingT> >& filter);

	FACTORY_PROTOTYPE1(getOneCppAttribute,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getOneCppAttribute(boost::shared_ptr< Base<EncodingT> > const& identifier);

	FACTORY_PROTOTYPE2(selectOneCppAttribute,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > selectOneCppAttribute(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE2(selectManyCppAttributes, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > selectManyCppAttributes(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	void cancelSelection();

	FACTORY_PROTOTYPE1(isSelectedCppAttribute, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isSelectedCppAttribute(const boost::shared_ptr< Base<EncodingT> >& cppAttribute);

	FACTORY_PROTOTYPE1(fillCppClass, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void fillCppClass(boost::shared_ptr< Base<EncodingT> >& cppAttribute);

	FACTORY_PROTOTYPE1(isModifiedCppAttribute, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isModifiedCppAttribute(const boost::shared_ptr< Base<EncodingT> >& cppAttribute);

	FACTORY_PROTOTYPE1(updateCppAttribute, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void updateCppAttribute(boost::shared_ptr< Base<EncodingT> >& cppAttribute);

	FACTORY_PROTOTYPE1(insertCppAttribute, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void insertCppAttribute(boost::shared_ptr< Base<EncodingT> >& cppAttribute);

	FACTORY_PROTOTYPE1(deleteCppAttribute, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void deleteCppAttribute(boost::shared_ptr< Base<EncodingT> >& cppAttribute);

	void setError(const std::exception& e);

	void clearError();

	FACTORY_PROTOTYPE1(getError, InOut< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getError(boost::shared_ptr< Base<EncodingT> >& text) const;

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( CppAttributeInterpreterAccess, C("CppAttributeAccess") );
		METHOD_KEY_REGISTER ( CppAttributeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getAllCppAttributes, no_const_t, C("CppAttributeAccess::GetAllCppAttributes") );
		METHOD_KEY_REGISTER1( CppAttributeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getManyCppAttributes, no_const_t, C("CppAttributeAccess::GetManyCppAttributes") );
		METHOD_KEY_REGISTER1( CppAttributeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getOneCppAttribute, no_const_t, C("CppAttributeAccess::GetOneCppAttribute") );
		METHOD_KEY_REGISTER2( CppAttributeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectOneCppAttribute, no_const_t, C("CppAttributeAccess::SelectOneCppAttribute") );
		METHOD_KEY_REGISTER2( CppAttributeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectManyCppAttributes, no_const_t, C("CppAttributeAccess::SelectManyCppAttributes") );
		METHOD_KEY_REGISTER ( CppAttributeInterpreterAccess, void, cancelSelection, no_const_t, C("CppAttributeAccess::CancelSelection") );
		METHOD_KEY_REGISTER1( CppAttributeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isSelectedCppAttribute, no_const_t, C("CppAttributeAccess::IsSelectedCppAttribute") );
		METHOD_KEY_REGISTER1( CppAttributeInterpreterAccess, void, fillCppClass, no_const_t, C("CppAttributeAccess::FillCppClass") );
		METHOD_KEY_REGISTER1( CppAttributeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isModifiedCppAttribute, no_const_t, C("CppAttributeAccess::IsModifiedCppAttribute") );
		METHOD_KEY_REGISTER1( CppAttributeInterpreterAccess, void, updateCppAttribute, no_const_t, C("CppAttributeAccess::UpdateCppAttribute") );
		METHOD_KEY_REGISTER1( CppAttributeInterpreterAccess, void, insertCppAttribute, no_const_t, C("CppAttributeAccess::InsertCppAttribute") );
		METHOD_KEY_REGISTER1( CppAttributeInterpreterAccess, void, deleteCppAttribute, no_const_t, C("CppAttributeAccess::DeleteCppAttribute") );
		METHOD_KEY_REGISTER1( CppAttributeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getError, const_t, C("CppAttributeAccess::GetError") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( C("CppAttributeAccess") );
		METHOD_KEY_UNREGISTER ( C("CppAttributeAccess::GetAllCppAttributes") );
		METHOD_KEY_UNREGISTER1( C("CppAttributeAccess::GetManyCppAttributes") );
		METHOD_KEY_UNREGISTER1( C("CppAttributeAccess::GetOneCppAttribute") );
		METHOD_KEY_UNREGISTER2( C("CppAttributeAccess::SelectOneCppAttribute") );
		METHOD_KEY_UNREGISTER2( C("CppAttributeAccess::SelectManyCppAttributes") );
		METHOD_KEY_UNREGISTER ( C("CppAttributeAccess::CancelSelection") );
		METHOD_KEY_UNREGISTER1( C("CppAttributeAccess::IsSelectedCppAttribute") );
		METHOD_KEY_UNREGISTER1( C("CppAttributeAccess::FillCppClass") );
		METHOD_KEY_UNREGISTER1( C("CppAttributeAccess::IsModifiedCppAttribute") );
		METHOD_KEY_UNREGISTER1( C("CppAttributeAccess::UpdateCppAttribute") );
		METHOD_KEY_UNREGISTER1( C("CppAttributeAccess::InsertCppAttribute") );
		METHOD_KEY_UNREGISTER1( C("CppAttributeAccess::DeleteCppAttribute") );
		METHOD_KEY_UNREGISTER1( C("CppAttributeAccess::GetError") );
	FACTORY_END_UNREGISTER

	boost::shared_ptr< Base<EncodingT> > convert_array(const std::vector< boost::shared_ptr< _CppAttribute<EncodingT> > >& value) const;
};

NAMESPACE_END

#undef C
#undef A

#include "cppAttributeInterpreterAccess_impl.hpp"

#endif
