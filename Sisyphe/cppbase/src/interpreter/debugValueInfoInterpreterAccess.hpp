/* 
 * debugValueInfoInterpreterAccess.hpp
 *
 *
 * @date 25-06-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _DEBUGVALUEINFO_INTERPRETER_ACCESS_HPP_
#define _DEBUGVALUEINFO_INTERPRETER_ACCESS_HPP_

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
class DebugValueInfoInterpreterAccess
: public Base<EncodingT>
{
private:
	_DebugValueInfoAccess<EncodingT>* m_object;
	std::string m_errorText;
	bool m_error;

public:
	DebugValueInfoInterpreterAccess();

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getAllDebugValueInfos();

	FACTORY_PROTOTYPE1(getManyDebugValueInfos, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getManyDebugValueInfos(const boost::shared_ptr< Base<EncodingT> >& filter);

	FACTORY_PROTOTYPE1(getOneDebugValueInfo,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getOneDebugValueInfo(boost::shared_ptr< Base<EncodingT> > const& identifier);

	FACTORY_PROTOTYPE2(selectOneDebugValueInfo,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > selectOneDebugValueInfo(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE2(selectManyDebugValueInfos, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > selectManyDebugValueInfos(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	void cancelSelection();

	FACTORY_PROTOTYPE1(isSelectedDebugValueInfo, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isSelectedDebugValueInfo(const boost::shared_ptr< Base<EncodingT> >& debugValueInfo);

	FACTORY_PROTOTYPE1(fillDebugVariableInfo, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void fillDebugVariableInfo(boost::shared_ptr< Base<EncodingT> >& debugValueInfo);

	FACTORY_PROTOTYPE1(fillDebugStubInfo, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void fillDebugStubInfo(boost::shared_ptr< Base<EncodingT> >& debugValueInfo);

	FACTORY_PROTOTYPE1(isModifiedDebugValueInfo, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isModifiedDebugValueInfo(const boost::shared_ptr< Base<EncodingT> >& debugValueInfo);

	FACTORY_PROTOTYPE1(updateDebugValueInfo, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void updateDebugValueInfo(boost::shared_ptr< Base<EncodingT> >& debugValueInfo);

	FACTORY_PROTOTYPE1(insertDebugValueInfo, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void insertDebugValueInfo(boost::shared_ptr< Base<EncodingT> >& debugValueInfo);

	FACTORY_PROTOTYPE1(deleteDebugValueInfo, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void deleteDebugValueInfo(boost::shared_ptr< Base<EncodingT> >& debugValueInfo);

	void setError(const std::exception& e);

	void clearError();

	FACTORY_PROTOTYPE1(getError, InOut< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getError(boost::shared_ptr< Base<EncodingT> >& text) const;

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( DebugValueInfoInterpreterAccess, UCS("DebugValueInfoAccess") );
		METHOD_KEY_REGISTER ( DebugValueInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getAllDebugValueInfos, no_const_t, UCS("DebugValueInfoAccess::GetAllDebugValueInfos") );
		METHOD_KEY_REGISTER1( DebugValueInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getManyDebugValueInfos, no_const_t, UCS("DebugValueInfoAccess::GetManyDebugValueInfos") );
		METHOD_KEY_REGISTER1( DebugValueInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getOneDebugValueInfo, no_const_t, UCS("DebugValueInfoAccess::GetOneDebugValueInfo") );
		METHOD_KEY_REGISTER2( DebugValueInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectOneDebugValueInfo, no_const_t, UCS("DebugValueInfoAccess::SelectOneDebugValueInfo") );
		METHOD_KEY_REGISTER2( DebugValueInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectManyDebugValueInfos, no_const_t, UCS("DebugValueInfoAccess::SelectManyDebugValueInfos") );
		METHOD_KEY_REGISTER ( DebugValueInfoInterpreterAccess, void, cancelSelection, no_const_t, UCS("DebugValueInfoAccess::CancelSelection") );
		METHOD_KEY_REGISTER1( DebugValueInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isSelectedDebugValueInfo, no_const_t, UCS("DebugValueInfoAccess::IsSelectedDebugValueInfo") );
		METHOD_KEY_REGISTER1( DebugValueInfoInterpreterAccess, void, fillDebugVariableInfo, no_const_t, UCS("DebugValueInfoAccess::FillDebugVariableInfo") );
		METHOD_KEY_REGISTER1( DebugValueInfoInterpreterAccess, void, fillDebugStubInfo, no_const_t, UCS("DebugValueInfoAccess::FillDebugStubInfo") );
		METHOD_KEY_REGISTER1( DebugValueInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isModifiedDebugValueInfo, no_const_t, UCS("DebugValueInfoAccess::IsModifiedDebugValueInfo") );
		METHOD_KEY_REGISTER1( DebugValueInfoInterpreterAccess, void, updateDebugValueInfo, no_const_t, UCS("DebugValueInfoAccess::UpdateDebugValueInfo") );
		METHOD_KEY_REGISTER1( DebugValueInfoInterpreterAccess, void, insertDebugValueInfo, no_const_t, UCS("DebugValueInfoAccess::InsertDebugValueInfo") );
		METHOD_KEY_REGISTER1( DebugValueInfoInterpreterAccess, void, deleteDebugValueInfo, no_const_t, UCS("DebugValueInfoAccess::DeleteDebugValueInfo") );
		METHOD_KEY_REGISTER1( DebugValueInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getError, const_t, UCS("DebugValueInfoAccess::GetError") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( UCS("DebugValueInfoAccess") );
		METHOD_KEY_UNREGISTER ( UCS("DebugValueInfoAccess::GetAllDebugValueInfos") );
		METHOD_KEY_UNREGISTER1( UCS("DebugValueInfoAccess::GetManyDebugValueInfos") );
		METHOD_KEY_UNREGISTER1( UCS("DebugValueInfoAccess::GetOneDebugValueInfo") );
		METHOD_KEY_UNREGISTER2( UCS("DebugValueInfoAccess::SelectOneDebugValueInfo") );
		METHOD_KEY_UNREGISTER2( UCS("DebugValueInfoAccess::SelectManyDebugValueInfos") );
		METHOD_KEY_UNREGISTER ( UCS("DebugValueInfoAccess::CancelSelection") );
		METHOD_KEY_UNREGISTER1( UCS("DebugValueInfoAccess::IsSelectedDebugValueInfo") );
		METHOD_KEY_UNREGISTER1( UCS("DebugValueInfoAccess::FillDebugVariableInfo") );
		METHOD_KEY_UNREGISTER1( UCS("DebugValueInfoAccess::FillDebugStubInfo") );
		METHOD_KEY_UNREGISTER1( UCS("DebugValueInfoAccess::IsModifiedDebugValueInfo") );
		METHOD_KEY_UNREGISTER1( UCS("DebugValueInfoAccess::UpdateDebugValueInfo") );
		METHOD_KEY_UNREGISTER1( UCS("DebugValueInfoAccess::InsertDebugValueInfo") );
		METHOD_KEY_UNREGISTER1( UCS("DebugValueInfoAccess::DeleteDebugValueInfo") );
		METHOD_KEY_UNREGISTER1( UCS("DebugValueInfoAccess::GetError") );
	FACTORY_END_UNREGISTER

	boost::shared_ptr< Base<EncodingT> > convert_array(const std::vector< boost::shared_ptr< _DebugValueInfo<EncodingT> > >& value) const;
};

NAMESPACE_END

#undef C
#undef A

#include "debugValueInfoInterpreterAccess_impl.hpp"

#endif
