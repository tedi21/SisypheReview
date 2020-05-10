/* 
 * cppVariableInterpreterAccess.hpp
 *
 *
 * @date 10-05-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPVARIABLE_INTERPRETER_ACCESS_HPP_
#define _CPPVARIABLE_INTERPRETER_ACCESS_HPP_

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
class CppVariableInterpreterAccess
: public Base<EncodingT>
{
private:
	_CppVariableAccess<EncodingT>* m_object;
	std::string m_errorText;
	bool m_error;

public:
	CppVariableInterpreterAccess();

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getAllCppVariables();

	FACTORY_PROTOTYPE1(getManyCppVariables, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getManyCppVariables(const boost::shared_ptr< Base<EncodingT> >& filter);

	FACTORY_PROTOTYPE1(getOneCppVariable,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getOneCppVariable(boost::shared_ptr< Base<EncodingT> > const& identifier);

	FACTORY_PROTOTYPE2(selectOneCppVariable,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > selectOneCppVariable(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	FACTORY_PROTOTYPE2(selectManyCppVariables, In< boost::shared_ptr< Base<EncodingT> > >, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > selectManyCppVariables(const boost::shared_ptr< Base<EncodingT> >& filter, const boost::shared_ptr< Base<EncodingT> >& nowait);

	void cancelSelection();

	FACTORY_PROTOTYPE1(isSelectedCppVariable, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isSelectedCppVariable(const boost::shared_ptr< Base<EncodingT> >& cppVariable);

	FACTORY_PROTOTYPE1(fillCppFunction, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void fillCppFunction(boost::shared_ptr< Base<EncodingT> >& cppVariable);

	FACTORY_PROTOTYPE1(fillCppFile, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void fillCppFile(boost::shared_ptr< Base<EncodingT> >& cppVariable);

	FACTORY_PROTOTYPE1(isModifiedCppVariable, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isModifiedCppVariable(const boost::shared_ptr< Base<EncodingT> >& cppVariable);

	FACTORY_PROTOTYPE1(updateCppVariable, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void updateCppVariable(boost::shared_ptr< Base<EncodingT> >& cppVariable);

	FACTORY_PROTOTYPE1(insertCppVariable, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void insertCppVariable(boost::shared_ptr< Base<EncodingT> >& cppVariable);

	FACTORY_PROTOTYPE1(deleteCppVariable, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void deleteCppVariable(boost::shared_ptr< Base<EncodingT> >& cppVariable);

	void setError(const std::exception& e);

	void clearError();

	FACTORY_PROTOTYPE1(getError, InOut< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getError(boost::shared_ptr< Base<EncodingT> >& text) const;

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( CppVariableInterpreterAccess, C("CppVariableAccess") );
		METHOD_KEY_REGISTER ( CppVariableInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getAllCppVariables, no_const_t, C("CppVariableAccess::GetAllCppVariables") );
		METHOD_KEY_REGISTER1( CppVariableInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getManyCppVariables, no_const_t, C("CppVariableAccess::GetManyCppVariables") );
		METHOD_KEY_REGISTER1( CppVariableInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getOneCppVariable, no_const_t, C("CppVariableAccess::GetOneCppVariable") );
		METHOD_KEY_REGISTER2( CppVariableInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectOneCppVariable, no_const_t, C("CppVariableAccess::SelectOneCppVariable") );
		METHOD_KEY_REGISTER2( CppVariableInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectManyCppVariables, no_const_t, C("CppVariableAccess::SelectManyCppVariables") );
		METHOD_KEY_REGISTER ( CppVariableInterpreterAccess, void, cancelSelection, no_const_t, C("CppVariableAccess::CancelSelection") );
		METHOD_KEY_REGISTER1( CppVariableInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isSelectedCppVariable, no_const_t, C("CppVariableAccess::IsSelectedCppVariable") );
		METHOD_KEY_REGISTER1( CppVariableInterpreterAccess, void, fillCppFunction, no_const_t, C("CppVariableAccess::FillCppFunction") );
		METHOD_KEY_REGISTER1( CppVariableInterpreterAccess, void, fillCppFile, no_const_t, C("CppVariableAccess::FillCppFile") );
		METHOD_KEY_REGISTER1( CppVariableInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isModifiedCppVariable, no_const_t, C("CppVariableAccess::IsModifiedCppVariable") );
		METHOD_KEY_REGISTER1( CppVariableInterpreterAccess, void, updateCppVariable, no_const_t, C("CppVariableAccess::UpdateCppVariable") );
		METHOD_KEY_REGISTER1( CppVariableInterpreterAccess, void, insertCppVariable, no_const_t, C("CppVariableAccess::InsertCppVariable") );
		METHOD_KEY_REGISTER1( CppVariableInterpreterAccess, void, deleteCppVariable, no_const_t, C("CppVariableAccess::DeleteCppVariable") );
		METHOD_KEY_REGISTER1( CppVariableInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getError, const_t, C("CppVariableAccess::GetError") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( C("CppVariableAccess") );
		METHOD_KEY_UNREGISTER ( C("CppVariableAccess::GetAllCppVariables") );
		METHOD_KEY_UNREGISTER1( C("CppVariableAccess::GetManyCppVariables") );
		METHOD_KEY_UNREGISTER1( C("CppVariableAccess::GetOneCppVariable") );
		METHOD_KEY_UNREGISTER2( C("CppVariableAccess::SelectOneCppVariable") );
		METHOD_KEY_UNREGISTER2( C("CppVariableAccess::SelectManyCppVariables") );
		METHOD_KEY_UNREGISTER ( C("CppVariableAccess::CancelSelection") );
		METHOD_KEY_UNREGISTER1( C("CppVariableAccess::IsSelectedCppVariable") );
		METHOD_KEY_UNREGISTER1( C("CppVariableAccess::FillCppFunction") );
		METHOD_KEY_UNREGISTER1( C("CppVariableAccess::FillCppFile") );
		METHOD_KEY_UNREGISTER1( C("CppVariableAccess::IsModifiedCppVariable") );
		METHOD_KEY_UNREGISTER1( C("CppVariableAccess::UpdateCppVariable") );
		METHOD_KEY_UNREGISTER1( C("CppVariableAccess::InsertCppVariable") );
		METHOD_KEY_UNREGISTER1( C("CppVariableAccess::DeleteCppVariable") );
		METHOD_KEY_UNREGISTER1( C("CppVariableAccess::GetError") );
	FACTORY_END_UNREGISTER

	boost::shared_ptr< Base<EncodingT> > convert_array(const std::vector< boost::shared_ptr< _CppVariable<EncodingT> > >& value) const;
};

NAMESPACE_END

#undef C
#undef A

#include "cppVariableInterpreterAccess_impl.hpp"

#endif
