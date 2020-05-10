/* 
 * cppNoticeInterpreterAccess.hpp
 *
 *
 * @date 10-05-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPNOTICE_INTERPRETER_ACCESS_HPP_
#define _CPPNOTICE_INTERPRETER_ACCESS_HPP_

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
class CppNoticeInterpreterAccess
: public Base<EncodingT>
{
private:
	_CppNoticeAccess<EncodingT>* m_object;
	std::string m_errorText;
	bool m_error;

public:
	CppNoticeInterpreterAccess();

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getAllCppNotices();

	FACTORY_PROTOTYPE1(getManyCppNotices, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getManyCppNotices(const boost::shared_ptr< Base<EncodingT> >& filter);

	FACTORY_PROTOTYPE1(getOneCppNotice,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getOneCppNotice(boost::shared_ptr< Base<EncodingT> > const& identifier);

	FACTORY_PROTOTYPE2(selectOneCppNotice,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > selectOneCppNotice(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE2(selectManyCppNotices, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > selectManyCppNotices(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	void cancelSelection();

	FACTORY_PROTOTYPE1(isSelectedCppNotice, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isSelectedCppNotice(const boost::shared_ptr< Base<EncodingT> >& cppNotice);

	FACTORY_PROTOTYPE1(fillCppFile, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void fillCppFile(boost::shared_ptr< Base<EncodingT> >& cppNotice);

	FACTORY_PROTOTYPE1(isModifiedCppNotice, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isModifiedCppNotice(const boost::shared_ptr< Base<EncodingT> >& cppNotice);

	FACTORY_PROTOTYPE1(updateCppNotice, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void updateCppNotice(boost::shared_ptr< Base<EncodingT> >& cppNotice);

	FACTORY_PROTOTYPE1(insertCppNotice, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void insertCppNotice(boost::shared_ptr< Base<EncodingT> >& cppNotice);

	FACTORY_PROTOTYPE1(deleteCppNotice, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void deleteCppNotice(boost::shared_ptr< Base<EncodingT> >& cppNotice);

	void setError(const std::exception& e);

	void clearError();

	FACTORY_PROTOTYPE1(getError, InOut< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getError(boost::shared_ptr< Base<EncodingT> >& text) const;

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( CppNoticeInterpreterAccess, UCS("CppNoticeAccess") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getAllCppNotices, no_const_t, UCS("CppNoticeAccess::GetAllCppNotices") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getManyCppNotices, no_const_t, UCS("CppNoticeAccess::GetManyCppNotices") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getOneCppNotice, no_const_t, UCS("CppNoticeAccess::GetOneCppNotice") );
		METHOD_KEY_REGISTER2( CppNoticeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectOneCppNotice, no_const_t, UCS("CppNoticeAccess::SelectOneCppNotice") );
		METHOD_KEY_REGISTER2( CppNoticeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectManyCppNotices, no_const_t, UCS("CppNoticeAccess::SelectManyCppNotices") );
		METHOD_KEY_REGISTER ( CppNoticeInterpreterAccess, void, cancelSelection, no_const_t, UCS("CppNoticeAccess::CancelSelection") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isSelectedCppNotice, no_const_t, UCS("CppNoticeAccess::IsSelectedCppNotice") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreterAccess, void, fillCppFile, no_const_t, UCS("CppNoticeAccess::FillCppFile") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isModifiedCppNotice, no_const_t, UCS("CppNoticeAccess::IsModifiedCppNotice") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreterAccess, void, updateCppNotice, no_const_t, UCS("CppNoticeAccess::UpdateCppNotice") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreterAccess, void, insertCppNotice, no_const_t, UCS("CppNoticeAccess::InsertCppNotice") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreterAccess, void, deleteCppNotice, no_const_t, UCS("CppNoticeAccess::DeleteCppNotice") );
		METHOD_KEY_REGISTER1( CppNoticeInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getError, const_t, UCS("CppNoticeAccess::GetError") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( UCS("CppNoticeAccess") );
		METHOD_KEY_UNREGISTER ( UCS("CppNoticeAccess::GetAllCppNotices") );
		METHOD_KEY_UNREGISTER1( UCS("CppNoticeAccess::GetManyCppNotices") );
		METHOD_KEY_UNREGISTER1( UCS("CppNoticeAccess::GetOneCppNotice") );
		METHOD_KEY_UNREGISTER2( UCS("CppNoticeAccess::SelectOneCppNotice") );
		METHOD_KEY_UNREGISTER2( UCS("CppNoticeAccess::SelectManyCppNotices") );
		METHOD_KEY_UNREGISTER ( UCS("CppNoticeAccess::CancelSelection") );
		METHOD_KEY_UNREGISTER1( UCS("CppNoticeAccess::IsSelectedCppNotice") );
		METHOD_KEY_UNREGISTER1( UCS("CppNoticeAccess::FillCppFile") );
		METHOD_KEY_UNREGISTER1( UCS("CppNoticeAccess::IsModifiedCppNotice") );
		METHOD_KEY_UNREGISTER1( UCS("CppNoticeAccess::UpdateCppNotice") );
		METHOD_KEY_UNREGISTER1( UCS("CppNoticeAccess::InsertCppNotice") );
		METHOD_KEY_UNREGISTER1( UCS("CppNoticeAccess::DeleteCppNotice") );
		METHOD_KEY_UNREGISTER1( UCS("CppNoticeAccess::GetError") );
	FACTORY_END_UNREGISTER

	boost::shared_ptr< Base<EncodingT> > convert_array(const std::vector< boost::shared_ptr< _CppNotice<EncodingT> > >& value) const;
};

NAMESPACE_END

#undef C
#undef A

#include "cppNoticeInterpreterAccess_impl.hpp"

#endif
