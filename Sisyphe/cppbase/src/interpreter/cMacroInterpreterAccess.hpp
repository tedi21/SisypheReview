/* 
 * cMacroInterpreterAccess.hpp
 *
 *
 * @date 31-07-2022
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CMACRO_INTERPRETER_ACCESS_HPP_
#define _CMACRO_INTERPRETER_ACCESS_HPP_

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
class CMacroInterpreterAccess
: public Base<EncodingT>
{
private:
	_CMacroAccess<EncodingT>* m_object;
	std::string m_errorText;
	bool m_error;

public:
	CMacroInterpreterAccess();

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getAllCMacros();

	FACTORY_PROTOTYPE1(getManyCMacros, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getManyCMacros(const boost::shared_ptr< Base<EncodingT> >& filter);

	FACTORY_PROTOTYPE1(getOneCMacro,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getOneCMacro(boost::shared_ptr< Base<EncodingT> > const& identifier);

	FACTORY_PROTOTYPE2(selectOneCMacro,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > selectOneCMacro(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE2(selectManyCMacros, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > selectManyCMacros(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	void cancelSelection();

	FACTORY_PROTOTYPE1(isSelectedCMacro, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isSelectedCMacro(const boost::shared_ptr< Base<EncodingT> >& cMacro);

	FACTORY_PROTOTYPE1(fillCppFile, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void fillCppFile(boost::shared_ptr< Base<EncodingT> >& cMacro);

	FACTORY_PROTOTYPE1(isModifiedCMacro, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isModifiedCMacro(const boost::shared_ptr< Base<EncodingT> >& cMacro);

	FACTORY_PROTOTYPE1(updateCMacro, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void updateCMacro(boost::shared_ptr< Base<EncodingT> >& cMacro);

	FACTORY_PROTOTYPE1(insertCMacro, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void insertCMacro(boost::shared_ptr< Base<EncodingT> >& cMacro);

	FACTORY_PROTOTYPE1(deleteCMacro, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void deleteCMacro(boost::shared_ptr< Base<EncodingT> >& cMacro);

	void setError(const std::exception& e);

	void clearError();

	FACTORY_PROTOTYPE1(getError, InOut< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getError(boost::shared_ptr< Base<EncodingT> >& text) const;

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( CMacroInterpreterAccess, UCS("CMacroAccess") );
		METHOD_KEY_REGISTER ( CMacroInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getAllCMacros, no_const_t, UCS("CMacroAccess::GetAllCMacros") );
		METHOD_KEY_REGISTER1( CMacroInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getManyCMacros, no_const_t, UCS("CMacroAccess::GetManyCMacros") );
		METHOD_KEY_REGISTER1( CMacroInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getOneCMacro, no_const_t, UCS("CMacroAccess::GetOneCMacro") );
		METHOD_KEY_REGISTER2( CMacroInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectOneCMacro, no_const_t, UCS("CMacroAccess::SelectOneCMacro") );
		METHOD_KEY_REGISTER2( CMacroInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectManyCMacros, no_const_t, UCS("CMacroAccess::SelectManyCMacros") );
		METHOD_KEY_REGISTER ( CMacroInterpreterAccess, void, cancelSelection, no_const_t, UCS("CMacroAccess::CancelSelection") );
		METHOD_KEY_REGISTER1( CMacroInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isSelectedCMacro, no_const_t, UCS("CMacroAccess::IsSelectedCMacro") );
		METHOD_KEY_REGISTER1( CMacroInterpreterAccess, void, fillCppFile, no_const_t, UCS("CMacroAccess::FillCppFile") );
		METHOD_KEY_REGISTER1( CMacroInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isModifiedCMacro, no_const_t, UCS("CMacroAccess::IsModifiedCMacro") );
		METHOD_KEY_REGISTER1( CMacroInterpreterAccess, void, updateCMacro, no_const_t, UCS("CMacroAccess::UpdateCMacro") );
		METHOD_KEY_REGISTER1( CMacroInterpreterAccess, void, insertCMacro, no_const_t, UCS("CMacroAccess::InsertCMacro") );
		METHOD_KEY_REGISTER1( CMacroInterpreterAccess, void, deleteCMacro, no_const_t, UCS("CMacroAccess::DeleteCMacro") );
		METHOD_KEY_REGISTER1( CMacroInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getError, const_t, UCS("CMacroAccess::GetError") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( UCS("CMacroAccess") );
		METHOD_KEY_UNREGISTER ( UCS("CMacroAccess::GetAllCMacros") );
		METHOD_KEY_UNREGISTER1( UCS("CMacroAccess::GetManyCMacros") );
		METHOD_KEY_UNREGISTER1( UCS("CMacroAccess::GetOneCMacro") );
		METHOD_KEY_UNREGISTER2( UCS("CMacroAccess::SelectOneCMacro") );
		METHOD_KEY_UNREGISTER2( UCS("CMacroAccess::SelectManyCMacros") );
		METHOD_KEY_UNREGISTER ( UCS("CMacroAccess::CancelSelection") );
		METHOD_KEY_UNREGISTER1( UCS("CMacroAccess::IsSelectedCMacro") );
		METHOD_KEY_UNREGISTER1( UCS("CMacroAccess::FillCppFile") );
		METHOD_KEY_UNREGISTER1( UCS("CMacroAccess::IsModifiedCMacro") );
		METHOD_KEY_UNREGISTER1( UCS("CMacroAccess::UpdateCMacro") );
		METHOD_KEY_UNREGISTER1( UCS("CMacroAccess::InsertCMacro") );
		METHOD_KEY_UNREGISTER1( UCS("CMacroAccess::DeleteCMacro") );
		METHOD_KEY_UNREGISTER1( UCS("CMacroAccess::GetError") );
	FACTORY_END_UNREGISTER

	boost::shared_ptr< Base<EncodingT> > convert_array(const std::vector< boost::shared_ptr< _CMacro<EncodingT> > >& value) const;
};

NAMESPACE_END

#undef C
#undef A

#include "cMacroInterpreterAccess_impl.hpp"

#endif
