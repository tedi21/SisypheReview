/* 
 * cppIncludeInterpreterAccess.hpp
 *
 *
 * @date 14-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPINCLUDE_INTERPRETER_ACCESS_HPP_
#define _CPPINCLUDE_INTERPRETER_ACCESS_HPP_

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
class CppIncludeInterpreterAccess
: public Base<EncodingT>
{
private:
	_CppIncludeAccess<EncodingT>* m_object;
	std::string m_errorText;
	bool m_error;

public:
	CppIncludeInterpreterAccess();

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getAllCppIncludes();

	FACTORY_PROTOTYPE1(getManyCppIncludes, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getManyCppIncludes(const boost::shared_ptr< Base<EncodingT> >& filter);

	FACTORY_PROTOTYPE1(getOneCppInclude,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getOneCppInclude(boost::shared_ptr< Base<EncodingT> > const& identifier);

	FACTORY_PROTOTYPE2(selectOneCppInclude,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > selectOneCppInclude(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE2(selectManyCppIncludes, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > selectManyCppIncludes(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	void cancelSelection();

	FACTORY_PROTOTYPE1(isSelectedCppInclude, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isSelectedCppInclude(const boost::shared_ptr< Base<EncodingT> >& cppInclude);

	FACTORY_PROTOTYPE1(fillCppFile, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void fillCppFile(boost::shared_ptr< Base<EncodingT> >& cppInclude);

	FACTORY_PROTOTYPE1(isModifiedCppInclude, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isModifiedCppInclude(const boost::shared_ptr< Base<EncodingT> >& cppInclude);

	FACTORY_PROTOTYPE1(updateCppInclude, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void updateCppInclude(boost::shared_ptr< Base<EncodingT> >& cppInclude);

	FACTORY_PROTOTYPE1(insertCppInclude, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void insertCppInclude(boost::shared_ptr< Base<EncodingT> >& cppInclude);

	FACTORY_PROTOTYPE1(deleteCppInclude, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void deleteCppInclude(boost::shared_ptr< Base<EncodingT> >& cppInclude);

	void setError(const std::exception& e);

	void clearError();

	FACTORY_PROTOTYPE1(getError, InOut< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getError(boost::shared_ptr< Base<EncodingT> >& text) const;

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( CppIncludeInterpreterAccess, UCS("CppIncludeAccess") );
		METHOD_KEY_REGISTER ( CppIncludeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getAllCppIncludes, no_const_t, UCS("CppIncludeAccess::GetAllCppIncludes") );
		METHOD_KEY_REGISTER1( CppIncludeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getManyCppIncludes, no_const_t, UCS("CppIncludeAccess::GetManyCppIncludes") );
		METHOD_KEY_REGISTER1( CppIncludeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getOneCppInclude, no_const_t, UCS("CppIncludeAccess::GetOneCppInclude") );
		METHOD_KEY_REGISTER2( CppIncludeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectOneCppInclude, no_const_t, UCS("CppIncludeAccess::SelectOneCppInclude") );
		METHOD_KEY_REGISTER2( CppIncludeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectManyCppIncludes, no_const_t, UCS("CppIncludeAccess::SelectManyCppIncludes") );
		METHOD_KEY_REGISTER ( CppIncludeInterpreterAccess, void, cancelSelection, no_const_t, UCS("CppIncludeAccess::CancelSelection") );
		METHOD_KEY_REGISTER1( CppIncludeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isSelectedCppInclude, no_const_t, UCS("CppIncludeAccess::IsSelectedCppInclude") );
		METHOD_KEY_REGISTER1( CppIncludeInterpreterAccess, void, fillCppFile, no_const_t, UCS("CppIncludeAccess::FillCppFile") );
		METHOD_KEY_REGISTER1( CppIncludeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isModifiedCppInclude, no_const_t, UCS("CppIncludeAccess::IsModifiedCppInclude") );
		METHOD_KEY_REGISTER1( CppIncludeInterpreterAccess, void, updateCppInclude, no_const_t, UCS("CppIncludeAccess::UpdateCppInclude") );
		METHOD_KEY_REGISTER1( CppIncludeInterpreterAccess, void, insertCppInclude, no_const_t, UCS("CppIncludeAccess::InsertCppInclude") );
		METHOD_KEY_REGISTER1( CppIncludeInterpreterAccess, void, deleteCppInclude, no_const_t, UCS("CppIncludeAccess::DeleteCppInclude") );
		METHOD_KEY_REGISTER1( CppIncludeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getError, const_t, UCS("CppIncludeAccess::GetError") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( UCS("CppIncludeAccess") );
		METHOD_KEY_UNREGISTER ( UCS("CppIncludeAccess::GetAllCppIncludes") );
		METHOD_KEY_UNREGISTER1( UCS("CppIncludeAccess::GetManyCppIncludes") );
		METHOD_KEY_UNREGISTER1( UCS("CppIncludeAccess::GetOneCppInclude") );
		METHOD_KEY_UNREGISTER2( UCS("CppIncludeAccess::SelectOneCppInclude") );
		METHOD_KEY_UNREGISTER2( UCS("CppIncludeAccess::SelectManyCppIncludes") );
		METHOD_KEY_UNREGISTER ( UCS("CppIncludeAccess::CancelSelection") );
		METHOD_KEY_UNREGISTER1( UCS("CppIncludeAccess::IsSelectedCppInclude") );
		METHOD_KEY_UNREGISTER1( UCS("CppIncludeAccess::FillCppFile") );
		METHOD_KEY_UNREGISTER1( UCS("CppIncludeAccess::IsModifiedCppInclude") );
		METHOD_KEY_UNREGISTER1( UCS("CppIncludeAccess::UpdateCppInclude") );
		METHOD_KEY_UNREGISTER1( UCS("CppIncludeAccess::InsertCppInclude") );
		METHOD_KEY_UNREGISTER1( UCS("CppIncludeAccess::DeleteCppInclude") );
		METHOD_KEY_UNREGISTER1( UCS("CppIncludeAccess::GetError") );
	FACTORY_END_UNREGISTER

	boost::shared_ptr< Base<EncodingT> > convert_array(const std::vector< boost::shared_ptr< _CppInclude<EncodingT> > >& value) const;
};

NAMESPACE_END

#undef C
#undef A

#include "cppIncludeInterpreterAccess_impl.hpp"

#endif
