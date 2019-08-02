/* 
 * debugFunctionInfoInterpreterAccess.hpp
 *
 *
 * @date 26-03-2019
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _DEBUGFUNCTIONINFO_INTERPRETER_ACCESS_HPP_
#define _DEBUGFUNCTIONINFO_INTERPRETER_ACCESS_HPP_

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
class DebugFunctionInfoInterpreterAccess
: public Base<EncodingT>
{
private:
	_DebugFunctionInfoAccess<EncodingT>* m_object;
	std::string m_errorText;
	bool m_error;

public:
	DebugFunctionInfoInterpreterAccess();

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getAllDebugFunctionInfos();

	FACTORY_PROTOTYPE1(getManyDebugFunctionInfos, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getManyDebugFunctionInfos(const boost::shared_ptr< Base<EncodingT> >& filter);

	FACTORY_PROTOTYPE1(getOneDebugFunctionInfo,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getOneDebugFunctionInfo(boost::shared_ptr< Base<EncodingT> > const& identifier);

	FACTORY_PROTOTYPE2(selectOneDebugFunctionInfo,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > selectOneDebugFunctionInfo(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE2(selectManyDebugFunctionInfos, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > selectManyDebugFunctionInfos(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	void cancelSelection();

	FACTORY_PROTOTYPE1(isSelectedDebugFunctionInfo, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isSelectedDebugFunctionInfo(const boost::shared_ptr< Base<EncodingT> >& debugFunctionInfo);

	FACTORY_PROTOTYPE1(fillDebugTypeInfo, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void fillDebugTypeInfo(boost::shared_ptr< Base<EncodingT> >& debugFunctionInfo);

	FACTORY_PROTOTYPE1(fillDebugFileInfo, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void fillDebugFileInfo(boost::shared_ptr< Base<EncodingT> >& debugFunctionInfo);

	FACTORY_PROTOTYPE2(fillAllDebugVariableInfos, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillAllDebugVariableInfos(boost::shared_ptr< Base<EncodingT> >& debugFunctionInfo, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillOneDebugVariableInfo,
				InOut< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	void fillOneDebugVariableInfo(boost::shared_ptr< Base<EncodingT> >& refDebugFunctionInfo,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillManyDebugVariableInfos, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillManyDebugVariableInfos(boost::shared_ptr< Base<EncodingT> >& debugFunctionInfo, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE1(isModifiedDebugFunctionInfo, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isModifiedDebugFunctionInfo(const boost::shared_ptr< Base<EncodingT> >& debugFunctionInfo);

	FACTORY_PROTOTYPE1(updateDebugFunctionInfo, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void updateDebugFunctionInfo(boost::shared_ptr< Base<EncodingT> >& debugFunctionInfo);

	FACTORY_PROTOTYPE1(insertDebugFunctionInfo, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void insertDebugFunctionInfo(boost::shared_ptr< Base<EncodingT> >& debugFunctionInfo);

	FACTORY_PROTOTYPE1(deleteDebugFunctionInfo, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void deleteDebugFunctionInfo(boost::shared_ptr< Base<EncodingT> >& debugFunctionInfo);

	void setError(const std::exception& e);

	void clearError();

	FACTORY_PROTOTYPE1(getError, InOut< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getError(boost::shared_ptr< Base<EncodingT> >& text) const;

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( DebugFunctionInfoInterpreterAccess, UCS("DebugFunctionInfoAccess") );
		METHOD_KEY_REGISTER ( DebugFunctionInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getAllDebugFunctionInfos, no_const_t, UCS("DebugFunctionInfoAccess::GetAllDebugFunctionInfos") );
		METHOD_KEY_REGISTER1( DebugFunctionInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getManyDebugFunctionInfos, no_const_t, UCS("DebugFunctionInfoAccess::GetManyDebugFunctionInfos") );
		METHOD_KEY_REGISTER1( DebugFunctionInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getOneDebugFunctionInfo, no_const_t, UCS("DebugFunctionInfoAccess::GetOneDebugFunctionInfo") );
		METHOD_KEY_REGISTER2( DebugFunctionInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectOneDebugFunctionInfo, no_const_t, UCS("DebugFunctionInfoAccess::SelectOneDebugFunctionInfo") );
		METHOD_KEY_REGISTER2( DebugFunctionInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectManyDebugFunctionInfos, no_const_t, UCS("DebugFunctionInfoAccess::SelectManyDebugFunctionInfos") );
		METHOD_KEY_REGISTER ( DebugFunctionInfoInterpreterAccess, void, cancelSelection, no_const_t, UCS("DebugFunctionInfoAccess::CancelSelection") );
		METHOD_KEY_REGISTER1( DebugFunctionInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isSelectedDebugFunctionInfo, no_const_t, UCS("DebugFunctionInfoAccess::IsSelectedDebugFunctionInfo") );
		METHOD_KEY_REGISTER1( DebugFunctionInfoInterpreterAccess, void, fillDebugTypeInfo, no_const_t, UCS("DebugFunctionInfoAccess::FillDebugTypeInfo") );
		METHOD_KEY_REGISTER1( DebugFunctionInfoInterpreterAccess, void, fillDebugFileInfo, no_const_t, UCS("DebugFunctionInfoAccess::FillDebugFileInfo") );
		METHOD_KEY_REGISTER2( DebugFunctionInfoInterpreterAccess, void, fillAllDebugVariableInfos, no_const_t, UCS("DebugFunctionInfoAccess::FillAllDebugVariableInfos") );
		METHOD_KEY_REGISTER3( DebugFunctionInfoInterpreterAccess, void, fillOneDebugVariableInfo, no_const_t, UCS("DebugFunctionInfoAccess::FillOneDebugVariableInfo") );
		METHOD_KEY_REGISTER3( DebugFunctionInfoInterpreterAccess, void, fillManyDebugVariableInfos, no_const_t, UCS("DebugFunctionInfoAccess::FillManyDebugVariableInfos") );
		METHOD_KEY_REGISTER1( DebugFunctionInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isModifiedDebugFunctionInfo, no_const_t, UCS("DebugFunctionInfoAccess::IsModifiedDebugFunctionInfo") );
		METHOD_KEY_REGISTER1( DebugFunctionInfoInterpreterAccess, void, updateDebugFunctionInfo, no_const_t, UCS("DebugFunctionInfoAccess::UpdateDebugFunctionInfo") );
		METHOD_KEY_REGISTER1( DebugFunctionInfoInterpreterAccess, void, insertDebugFunctionInfo, no_const_t, UCS("DebugFunctionInfoAccess::InsertDebugFunctionInfo") );
		METHOD_KEY_REGISTER1( DebugFunctionInfoInterpreterAccess, void, deleteDebugFunctionInfo, no_const_t, UCS("DebugFunctionInfoAccess::DeleteDebugFunctionInfo") );
		METHOD_KEY_REGISTER1( DebugFunctionInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getError, const_t, UCS("DebugFunctionInfoAccess::GetError") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( UCS("DebugFunctionInfoAccess") );
		METHOD_KEY_UNREGISTER ( UCS("DebugFunctionInfoAccess::GetAllDebugFunctionInfos") );
		METHOD_KEY_UNREGISTER1( UCS("DebugFunctionInfoAccess::GetManyDebugFunctionInfos") );
		METHOD_KEY_UNREGISTER1( UCS("DebugFunctionInfoAccess::GetOneDebugFunctionInfo") );
		METHOD_KEY_UNREGISTER2( UCS("DebugFunctionInfoAccess::SelectOneDebugFunctionInfo") );
		METHOD_KEY_UNREGISTER2( UCS("DebugFunctionInfoAccess::SelectManyDebugFunctionInfos") );
		METHOD_KEY_UNREGISTER ( UCS("DebugFunctionInfoAccess::CancelSelection") );
		METHOD_KEY_UNREGISTER1( UCS("DebugFunctionInfoAccess::IsSelectedDebugFunctionInfo") );
		METHOD_KEY_UNREGISTER1( UCS("DebugFunctionInfoAccess::FillDebugTypeInfo") );
		METHOD_KEY_UNREGISTER1( UCS("DebugFunctionInfoAccess::FillDebugFileInfo") );
		METHOD_KEY_UNREGISTER2( UCS("DebugFunctionInfoAccess::FillAllDebugVariableInfos") );
		METHOD_KEY_UNREGISTER3( UCS("DebugFunctionInfoAccess::FillOneDebugVariableInfo") );
		METHOD_KEY_UNREGISTER3( UCS("DebugFunctionInfoAccess::FillManyDebugVariableInfos") );
		METHOD_KEY_UNREGISTER1( UCS("DebugFunctionInfoAccess::IsModifiedDebugFunctionInfo") );
		METHOD_KEY_UNREGISTER1( UCS("DebugFunctionInfoAccess::UpdateDebugFunctionInfo") );
		METHOD_KEY_UNREGISTER1( UCS("DebugFunctionInfoAccess::InsertDebugFunctionInfo") );
		METHOD_KEY_UNREGISTER1( UCS("DebugFunctionInfoAccess::DeleteDebugFunctionInfo") );
		METHOD_KEY_UNREGISTER1( UCS("DebugFunctionInfoAccess::GetError") );
	FACTORY_END_UNREGISTER

	boost::shared_ptr< Base<EncodingT> > convert_array(const std::vector< boost::shared_ptr< _DebugFunctionInfo<EncodingT> > >& value) const;
};

NAMESPACE_END

#undef C
#undef A

#include "debugFunctionInfoInterpreterAccess_impl.hpp"

#endif
