/* 
 * debugFileInfoInterpreterAccess.hpp
 *
 *
 * @date 14-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _DEBUGFILEINFO_INTERPRETER_ACCESS_HPP_
#define _DEBUGFILEINFO_INTERPRETER_ACCESS_HPP_

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
class DebugFileInfoInterpreterAccess
: public Base<EncodingT>
{
private:
	_DebugFileInfoAccess<EncodingT>* m_object;
	std::string m_errorText;
	bool m_error;

public:
	DebugFileInfoInterpreterAccess();

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getAllDebugFileInfos();

	FACTORY_PROTOTYPE1(getManyDebugFileInfos, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getManyDebugFileInfos(const boost::shared_ptr< Base<EncodingT> >& filter);

	FACTORY_PROTOTYPE1(getOneDebugFileInfo,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getOneDebugFileInfo(boost::shared_ptr< Base<EncodingT> > const& identifier);

	FACTORY_PROTOTYPE2(selectOneDebugFileInfo,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > selectOneDebugFileInfo(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE2(selectManyDebugFileInfos, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > selectManyDebugFileInfos(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	void cancelSelection();

	FACTORY_PROTOTYPE1(isSelectedDebugFileInfo, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isSelectedDebugFileInfo(const boost::shared_ptr< Base<EncodingT> >& debugFileInfo);

	FACTORY_PROTOTYPE1(fillTextFile, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void fillTextFile(boost::shared_ptr< Base<EncodingT> >& debugFileInfo);

	FACTORY_PROTOTYPE2(fillAllDebugFunctionInfos, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillAllDebugFunctionInfos(boost::shared_ptr< Base<EncodingT> >& debugFileInfo, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillOneDebugFunctionInfo,
				InOut< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	void fillOneDebugFunctionInfo(boost::shared_ptr< Base<EncodingT> >& refDebugFileInfo,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillManyDebugFunctionInfos, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillManyDebugFunctionInfos(boost::shared_ptr< Base<EncodingT> >& debugFileInfo, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE2(fillAllDebugStubInfos, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillAllDebugStubInfos(boost::shared_ptr< Base<EncodingT> >& debugFileInfo, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillOneDebugStubInfo,
				InOut< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	void fillOneDebugStubInfo(boost::shared_ptr< Base<EncodingT> >& refDebugFileInfo,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillManyDebugStubInfos, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillManyDebugStubInfos(boost::shared_ptr< Base<EncodingT> >& debugFileInfo, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE1(isModifiedDebugFileInfo, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isModifiedDebugFileInfo(const boost::shared_ptr< Base<EncodingT> >& debugFileInfo);

	FACTORY_PROTOTYPE1(updateDebugFileInfo, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void updateDebugFileInfo(boost::shared_ptr< Base<EncodingT> >& debugFileInfo);

	FACTORY_PROTOTYPE1(insertDebugFileInfo, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void insertDebugFileInfo(boost::shared_ptr< Base<EncodingT> >& debugFileInfo);

	FACTORY_PROTOTYPE1(deleteDebugFileInfo, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void deleteDebugFileInfo(boost::shared_ptr< Base<EncodingT> >& debugFileInfo);

	void setError(const std::exception& e);

	void clearError();

	FACTORY_PROTOTYPE1(getError, InOut< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getError(boost::shared_ptr< Base<EncodingT> >& text) const;

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( DebugFileInfoInterpreterAccess, UCS("DebugFileInfoAccess") );
		METHOD_KEY_REGISTER ( DebugFileInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getAllDebugFileInfos, no_const_t, UCS("DebugFileInfoAccess::GetAllDebugFileInfos") );
		METHOD_KEY_REGISTER1( DebugFileInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getManyDebugFileInfos, no_const_t, UCS("DebugFileInfoAccess::GetManyDebugFileInfos") );
		METHOD_KEY_REGISTER1( DebugFileInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getOneDebugFileInfo, no_const_t, UCS("DebugFileInfoAccess::GetOneDebugFileInfo") );
		METHOD_KEY_REGISTER2( DebugFileInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectOneDebugFileInfo, no_const_t, UCS("DebugFileInfoAccess::SelectOneDebugFileInfo") );
		METHOD_KEY_REGISTER2( DebugFileInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectManyDebugFileInfos, no_const_t, UCS("DebugFileInfoAccess::SelectManyDebugFileInfos") );
		METHOD_KEY_REGISTER ( DebugFileInfoInterpreterAccess, void, cancelSelection, no_const_t, UCS("DebugFileInfoAccess::CancelSelection") );
		METHOD_KEY_REGISTER1( DebugFileInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isSelectedDebugFileInfo, no_const_t, UCS("DebugFileInfoAccess::IsSelectedDebugFileInfo") );
		METHOD_KEY_REGISTER1( DebugFileInfoInterpreterAccess, void, fillTextFile, no_const_t, UCS("DebugFileInfoAccess::FillTextFile") );
		METHOD_KEY_REGISTER2( DebugFileInfoInterpreterAccess, void, fillAllDebugFunctionInfos, no_const_t, UCS("DebugFileInfoAccess::FillAllDebugFunctionInfos") );
		METHOD_KEY_REGISTER3( DebugFileInfoInterpreterAccess, void, fillOneDebugFunctionInfo, no_const_t, UCS("DebugFileInfoAccess::FillOneDebugFunctionInfo") );
		METHOD_KEY_REGISTER3( DebugFileInfoInterpreterAccess, void, fillManyDebugFunctionInfos, no_const_t, UCS("DebugFileInfoAccess::FillManyDebugFunctionInfos") );
		METHOD_KEY_REGISTER2( DebugFileInfoInterpreterAccess, void, fillAllDebugStubInfos, no_const_t, UCS("DebugFileInfoAccess::FillAllDebugStubInfos") );
		METHOD_KEY_REGISTER3( DebugFileInfoInterpreterAccess, void, fillOneDebugStubInfo, no_const_t, UCS("DebugFileInfoAccess::FillOneDebugStubInfo") );
		METHOD_KEY_REGISTER3( DebugFileInfoInterpreterAccess, void, fillManyDebugStubInfos, no_const_t, UCS("DebugFileInfoAccess::FillManyDebugStubInfos") );
		METHOD_KEY_REGISTER1( DebugFileInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isModifiedDebugFileInfo, no_const_t, UCS("DebugFileInfoAccess::IsModifiedDebugFileInfo") );
		METHOD_KEY_REGISTER1( DebugFileInfoInterpreterAccess, void, updateDebugFileInfo, no_const_t, UCS("DebugFileInfoAccess::UpdateDebugFileInfo") );
		METHOD_KEY_REGISTER1( DebugFileInfoInterpreterAccess, void, insertDebugFileInfo, no_const_t, UCS("DebugFileInfoAccess::InsertDebugFileInfo") );
		METHOD_KEY_REGISTER1( DebugFileInfoInterpreterAccess, void, deleteDebugFileInfo, no_const_t, UCS("DebugFileInfoAccess::DeleteDebugFileInfo") );
		METHOD_KEY_REGISTER1( DebugFileInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getError, const_t, UCS("DebugFileInfoAccess::GetError") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( UCS("DebugFileInfoAccess") );
		METHOD_KEY_UNREGISTER ( UCS("DebugFileInfoAccess::GetAllDebugFileInfos") );
		METHOD_KEY_UNREGISTER1( UCS("DebugFileInfoAccess::GetManyDebugFileInfos") );
		METHOD_KEY_UNREGISTER1( UCS("DebugFileInfoAccess::GetOneDebugFileInfo") );
		METHOD_KEY_UNREGISTER2( UCS("DebugFileInfoAccess::SelectOneDebugFileInfo") );
		METHOD_KEY_UNREGISTER2( UCS("DebugFileInfoAccess::SelectManyDebugFileInfos") );
		METHOD_KEY_UNREGISTER ( UCS("DebugFileInfoAccess::CancelSelection") );
		METHOD_KEY_UNREGISTER1( UCS("DebugFileInfoAccess::IsSelectedDebugFileInfo") );
		METHOD_KEY_UNREGISTER1( UCS("DebugFileInfoAccess::FillTextFile") );
		METHOD_KEY_UNREGISTER2( UCS("DebugFileInfoAccess::FillAllDebugFunctionInfos") );
		METHOD_KEY_UNREGISTER3( UCS("DebugFileInfoAccess::FillOneDebugFunctionInfo") );
		METHOD_KEY_UNREGISTER3( UCS("DebugFileInfoAccess::FillManyDebugFunctionInfos") );
		METHOD_KEY_UNREGISTER2( UCS("DebugFileInfoAccess::FillAllDebugStubInfos") );
		METHOD_KEY_UNREGISTER3( UCS("DebugFileInfoAccess::FillOneDebugStubInfo") );
		METHOD_KEY_UNREGISTER3( UCS("DebugFileInfoAccess::FillManyDebugStubInfos") );
		METHOD_KEY_UNREGISTER1( UCS("DebugFileInfoAccess::IsModifiedDebugFileInfo") );
		METHOD_KEY_UNREGISTER1( UCS("DebugFileInfoAccess::UpdateDebugFileInfo") );
		METHOD_KEY_UNREGISTER1( UCS("DebugFileInfoAccess::InsertDebugFileInfo") );
		METHOD_KEY_UNREGISTER1( UCS("DebugFileInfoAccess::DeleteDebugFileInfo") );
		METHOD_KEY_UNREGISTER1( UCS("DebugFileInfoAccess::GetError") );
	FACTORY_END_UNREGISTER

	boost::shared_ptr< Base<EncodingT> > convert_array(const std::vector< boost::shared_ptr< _DebugFileInfo<EncodingT> > >& value) const;
};

NAMESPACE_END

#undef C
#undef A

#include "debugFileInfoInterpreterAccess_impl.hpp"

#endif
