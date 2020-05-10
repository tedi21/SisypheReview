/* 
 * debugTypeInfoInterpreterAccess.hpp
 *
 *
 * @date 10-05-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _DEBUGTYPEINFO_INTERPRETER_ACCESS_HPP_
#define _DEBUGTYPEINFO_INTERPRETER_ACCESS_HPP_

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
class DebugTypeInfoInterpreterAccess
: public Base<EncodingT>
{
private:
	_DebugTypeInfoAccess<EncodingT>* m_object;
	std::string m_errorText;
	bool m_error;

public:
	DebugTypeInfoInterpreterAccess();

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getAllDebugTypeInfos();

	FACTORY_PROTOTYPE1(getManyDebugTypeInfos, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getManyDebugTypeInfos(const boost::shared_ptr< Base<EncodingT> >& filter);

	FACTORY_PROTOTYPE1(getOneDebugTypeInfo,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getOneDebugTypeInfo(boost::shared_ptr< Base<EncodingT> > const& identifier);

	FACTORY_PROTOTYPE2(selectOneDebugTypeInfo,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > selectOneDebugTypeInfo(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE2(selectManyDebugTypeInfos, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > selectManyDebugTypeInfos(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	void cancelSelection();

	FACTORY_PROTOTYPE1(isSelectedDebugTypeInfo, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isSelectedDebugTypeInfo(const boost::shared_ptr< Base<EncodingT> >& debugTypeInfo);

	FACTORY_PROTOTYPE1(fillPrimitiveType, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void fillPrimitiveType(boost::shared_ptr< Base<EncodingT> >& debugTypeInfo);

	FACTORY_PROTOTYPE2(fillAllRichTypes, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillAllRichTypes(boost::shared_ptr< Base<EncodingT> >& debugTypeInfo, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillOneRichType,
				InOut< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	void fillOneRichType(boost::shared_ptr< Base<EncodingT> >& refDebugTypeInfo,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillManyRichTypes, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillManyRichTypes(boost::shared_ptr< Base<EncodingT> >& debugTypeInfo, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE2(fillAllDebugFunctionInfos, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillAllDebugFunctionInfos(boost::shared_ptr< Base<EncodingT> >& debugTypeInfo, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillOneDebugFunctionInfo,
				InOut< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	void fillOneDebugFunctionInfo(boost::shared_ptr< Base<EncodingT> >& refDebugTypeInfo,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillManyDebugFunctionInfos, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillManyDebugFunctionInfos(boost::shared_ptr< Base<EncodingT> >& debugTypeInfo, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE2(fillAllDebugVariableInfos, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillAllDebugVariableInfos(boost::shared_ptr< Base<EncodingT> >& debugTypeInfo, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillOneDebugVariableInfo,
				InOut< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	void fillOneDebugVariableInfo(boost::shared_ptr< Base<EncodingT> >& refDebugTypeInfo,
				const boost::shared_ptr< Base<EncodingT> >& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE3(fillManyDebugVariableInfos, InOut< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	void fillManyDebugVariableInfos(boost::shared_ptr< Base<EncodingT> >& debugTypeInfo, const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE1(isModifiedDebugTypeInfo, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isModifiedDebugTypeInfo(const boost::shared_ptr< Base<EncodingT> >& debugTypeInfo);

	FACTORY_PROTOTYPE1(updateDebugTypeInfo, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void updateDebugTypeInfo(boost::shared_ptr< Base<EncodingT> >& debugTypeInfo);

	FACTORY_PROTOTYPE1(insertDebugTypeInfo, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void insertDebugTypeInfo(boost::shared_ptr< Base<EncodingT> >& debugTypeInfo);

	FACTORY_PROTOTYPE1(deleteDebugTypeInfo, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void deleteDebugTypeInfo(boost::shared_ptr< Base<EncodingT> >& debugTypeInfo);

	void setError(const std::exception& e);

	void clearError();

	FACTORY_PROTOTYPE1(getError, InOut< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getError(boost::shared_ptr< Base<EncodingT> >& text) const;

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( DebugTypeInfoInterpreterAccess, C("DebugTypeInfoAccess") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getAllDebugTypeInfos, no_const_t, C("DebugTypeInfoAccess::GetAllDebugTypeInfos") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getManyDebugTypeInfos, no_const_t, C("DebugTypeInfoAccess::GetManyDebugTypeInfos") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getOneDebugTypeInfo, no_const_t, C("DebugTypeInfoAccess::GetOneDebugTypeInfo") );
		METHOD_KEY_REGISTER2( DebugTypeInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectOneDebugTypeInfo, no_const_t, C("DebugTypeInfoAccess::SelectOneDebugTypeInfo") );
		METHOD_KEY_REGISTER2( DebugTypeInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectManyDebugTypeInfos, no_const_t, C("DebugTypeInfoAccess::SelectManyDebugTypeInfos") );
		METHOD_KEY_REGISTER ( DebugTypeInfoInterpreterAccess, void, cancelSelection, no_const_t, C("DebugTypeInfoAccess::CancelSelection") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isSelectedDebugTypeInfo, no_const_t, C("DebugTypeInfoAccess::IsSelectedDebugTypeInfo") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreterAccess, void, fillPrimitiveType, no_const_t, C("DebugTypeInfoAccess::FillPrimitiveType") );
		METHOD_KEY_REGISTER2( DebugTypeInfoInterpreterAccess, void, fillAllRichTypes, no_const_t, C("DebugTypeInfoAccess::FillAllRichTypes") );
		METHOD_KEY_REGISTER3( DebugTypeInfoInterpreterAccess, void, fillOneRichType, no_const_t, C("DebugTypeInfoAccess::FillOneRichType") );
		METHOD_KEY_REGISTER3( DebugTypeInfoInterpreterAccess, void, fillManyRichTypes, no_const_t, C("DebugTypeInfoAccess::FillManyRichTypes") );
		METHOD_KEY_REGISTER2( DebugTypeInfoInterpreterAccess, void, fillAllDebugFunctionInfos, no_const_t, C("DebugTypeInfoAccess::FillAllDebugFunctionInfos") );
		METHOD_KEY_REGISTER3( DebugTypeInfoInterpreterAccess, void, fillOneDebugFunctionInfo, no_const_t, C("DebugTypeInfoAccess::FillOneDebugFunctionInfo") );
		METHOD_KEY_REGISTER3( DebugTypeInfoInterpreterAccess, void, fillManyDebugFunctionInfos, no_const_t, C("DebugTypeInfoAccess::FillManyDebugFunctionInfos") );
		METHOD_KEY_REGISTER2( DebugTypeInfoInterpreterAccess, void, fillAllDebugVariableInfos, no_const_t, C("DebugTypeInfoAccess::FillAllDebugVariableInfos") );
		METHOD_KEY_REGISTER3( DebugTypeInfoInterpreterAccess, void, fillOneDebugVariableInfo, no_const_t, C("DebugTypeInfoAccess::FillOneDebugVariableInfo") );
		METHOD_KEY_REGISTER3( DebugTypeInfoInterpreterAccess, void, fillManyDebugVariableInfos, no_const_t, C("DebugTypeInfoAccess::FillManyDebugVariableInfos") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isModifiedDebugTypeInfo, no_const_t, C("DebugTypeInfoAccess::IsModifiedDebugTypeInfo") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreterAccess, void, updateDebugTypeInfo, no_const_t, C("DebugTypeInfoAccess::UpdateDebugTypeInfo") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreterAccess, void, insertDebugTypeInfo, no_const_t, C("DebugTypeInfoAccess::InsertDebugTypeInfo") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreterAccess, void, deleteDebugTypeInfo, no_const_t, C("DebugTypeInfoAccess::DeleteDebugTypeInfo") );
		METHOD_KEY_REGISTER1( DebugTypeInfoInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getError, const_t, C("DebugTypeInfoAccess::GetError") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( C("DebugTypeInfoAccess") );
		METHOD_KEY_UNREGISTER ( C("DebugTypeInfoAccess::GetAllDebugTypeInfos") );
		METHOD_KEY_UNREGISTER1( C("DebugTypeInfoAccess::GetManyDebugTypeInfos") );
		METHOD_KEY_UNREGISTER1( C("DebugTypeInfoAccess::GetOneDebugTypeInfo") );
		METHOD_KEY_UNREGISTER2( C("DebugTypeInfoAccess::SelectOneDebugTypeInfo") );
		METHOD_KEY_UNREGISTER2( C("DebugTypeInfoAccess::SelectManyDebugTypeInfos") );
		METHOD_KEY_UNREGISTER ( C("DebugTypeInfoAccess::CancelSelection") );
		METHOD_KEY_UNREGISTER1( C("DebugTypeInfoAccess::IsSelectedDebugTypeInfo") );
		METHOD_KEY_UNREGISTER1( C("DebugTypeInfoAccess::FillPrimitiveType") );
		METHOD_KEY_UNREGISTER2( C("DebugTypeInfoAccess::FillAllRichTypes") );
		METHOD_KEY_UNREGISTER3( C("DebugTypeInfoAccess::FillOneRichType") );
		METHOD_KEY_UNREGISTER3( C("DebugTypeInfoAccess::FillManyRichTypes") );
		METHOD_KEY_UNREGISTER2( C("DebugTypeInfoAccess::FillAllDebugFunctionInfos") );
		METHOD_KEY_UNREGISTER3( C("DebugTypeInfoAccess::FillOneDebugFunctionInfo") );
		METHOD_KEY_UNREGISTER3( C("DebugTypeInfoAccess::FillManyDebugFunctionInfos") );
		METHOD_KEY_UNREGISTER2( C("DebugTypeInfoAccess::FillAllDebugVariableInfos") );
		METHOD_KEY_UNREGISTER3( C("DebugTypeInfoAccess::FillOneDebugVariableInfo") );
		METHOD_KEY_UNREGISTER3( C("DebugTypeInfoAccess::FillManyDebugVariableInfos") );
		METHOD_KEY_UNREGISTER1( C("DebugTypeInfoAccess::IsModifiedDebugTypeInfo") );
		METHOD_KEY_UNREGISTER1( C("DebugTypeInfoAccess::UpdateDebugTypeInfo") );
		METHOD_KEY_UNREGISTER1( C("DebugTypeInfoAccess::InsertDebugTypeInfo") );
		METHOD_KEY_UNREGISTER1( C("DebugTypeInfoAccess::DeleteDebugTypeInfo") );
		METHOD_KEY_UNREGISTER1( C("DebugTypeInfoAccess::GetError") );
	FACTORY_END_UNREGISTER

	boost::shared_ptr< Base<EncodingT> > convert_array(const std::vector< boost::shared_ptr< _DebugTypeInfo<EncodingT> > >& value) const;
};

NAMESPACE_END

#undef C
#undef A

#include "debugTypeInfoInterpreterAccess_impl.hpp"

#endif
