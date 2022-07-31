/* 
 * ruleInterpreterAccess.hpp
 *
 *
 * @date 31-07-2022
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _RULE_INTERPRETER_ACCESS_HPP_
#define _RULE_INTERPRETER_ACCESS_HPP_

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
class RuleInterpreterAccess
: public Base<EncodingT>
{
private:
	_RuleAccess<EncodingT>* m_object;
	std::string m_errorText;
	bool m_error;

public:
	RuleInterpreterAccess();

	virtual typename EncodingT::string_t toString() const;

	virtual boost::shared_ptr< Base<EncodingT> > clone() const;

	virtual typename EncodingT::string_t getClassName() const;

	virtual boost::shared_ptr< Base<EncodingT> > invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params);

	boost::shared_ptr< Base<EncodingT> > getAllRules();

	FACTORY_PROTOTYPE1(getManyRules, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getManyRules(const boost::shared_ptr< Base<EncodingT> >& filter);

	FACTORY_PROTOTYPE1(getOneRule,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getOneRule(boost::shared_ptr< Base<EncodingT> > const& identifier);

	FACTORY_PROTOTYPE2(selectOneRule,
				In< boost::shared_ptr< Base<EncodingT> > >,
				In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > selectOneRule(boost::shared_ptr< Base<EncodingT> > const& identifier,
				const boost::shared_ptr< Base<EncodingT> >& nowait);

	void cancelSelection();

	FACTORY_PROTOTYPE1(isSelectedRule, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isSelectedRule(const boost::shared_ptr< Base<EncodingT> >& rule);

	FACTORY_PROTOTYPE1(isModifiedRule, In< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > isModifiedRule(const boost::shared_ptr< Base<EncodingT> >& rule);

	FACTORY_PROTOTYPE1(updateRule, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void updateRule(boost::shared_ptr< Base<EncodingT> >& rule);

	FACTORY_PROTOTYPE1(insertRule, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void insertRule(boost::shared_ptr< Base<EncodingT> >& rule);

	FACTORY_PROTOTYPE1(deleteRule, InOut< boost::shared_ptr< Base<EncodingT> > >)
	void deleteRule(boost::shared_ptr< Base<EncodingT> >& rule);

	void setError(const std::exception& e);

	void clearError();

	FACTORY_PROTOTYPE1(getError, InOut< boost::shared_ptr< Base<EncodingT> > >)
	boost::shared_ptr< Base<EncodingT> > getError(boost::shared_ptr< Base<EncodingT> >& text) const;

	FACTORY_BEGIN_REGISTER
		CLASS_KEY_REGISTER ( RuleInterpreterAccess, UCS("RuleAccess") );
		METHOD_KEY_REGISTER ( RuleInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getAllRules, no_const_t, UCS("RuleAccess::GetAllRules") );
		METHOD_KEY_REGISTER1( RuleInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getManyRules, no_const_t, UCS("RuleAccess::GetManyRules") );
		METHOD_KEY_REGISTER1( RuleInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getOneRule, no_const_t, UCS("RuleAccess::GetOneRule") );
		METHOD_KEY_REGISTER2( RuleInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, selectOneRule, no_const_t, UCS("RuleAccess::SelectOneRule") );
		METHOD_KEY_REGISTER ( RuleInterpreterAccess, void, cancelSelection, no_const_t, UCS("RuleAccess::CancelSelection") );
		METHOD_KEY_REGISTER1( RuleInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isSelectedRule, no_const_t, UCS("RuleAccess::IsSelectedRule") );
		METHOD_KEY_REGISTER1( RuleInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, isModifiedRule, no_const_t, UCS("RuleAccess::IsModifiedRule") );
		METHOD_KEY_REGISTER1( RuleInterpreterAccess, void, updateRule, no_const_t, UCS("RuleAccess::UpdateRule") );
		METHOD_KEY_REGISTER1( RuleInterpreterAccess, void, insertRule, no_const_t, UCS("RuleAccess::InsertRule") );
		METHOD_KEY_REGISTER1( RuleInterpreterAccess, void, deleteRule, no_const_t, UCS("RuleAccess::DeleteRule") );
		METHOD_KEY_REGISTER1( RuleInterpreterAccess, boost::shared_ptr< Base<EncodingT> >, getError, const_t, UCS("RuleAccess::GetError") );
	FACTORY_END_REGISTER

	FACTORY_BEGIN_UNREGISTER
		CLASS_KEY_UNREGISTER ( UCS("RuleAccess") );
		METHOD_KEY_UNREGISTER ( UCS("RuleAccess::GetAllRules") );
		METHOD_KEY_UNREGISTER1( UCS("RuleAccess::GetManyRules") );
		METHOD_KEY_UNREGISTER1( UCS("RuleAccess::GetOneRule") );
		METHOD_KEY_UNREGISTER2( UCS("RuleAccess::SelectOneRule") );
		METHOD_KEY_UNREGISTER ( UCS("RuleAccess::CancelSelection") );
		METHOD_KEY_UNREGISTER1( UCS("RuleAccess::IsSelectedRule") );
		METHOD_KEY_UNREGISTER1( UCS("RuleAccess::IsModifiedRule") );
		METHOD_KEY_UNREGISTER1( UCS("RuleAccess::UpdateRule") );
		METHOD_KEY_UNREGISTER1( UCS("RuleAccess::InsertRule") );
		METHOD_KEY_UNREGISTER1( UCS("RuleAccess::DeleteRule") );
		METHOD_KEY_UNREGISTER1( UCS("RuleAccess::GetError") );
	FACTORY_END_UNREGISTER

	boost::shared_ptr< Base<EncodingT> > convert_array(const std::vector< boost::shared_ptr< _Rule<EncodingT> > >& value) const;
};

NAMESPACE_END

#undef C
#undef A

#include "ruleInterpreterAccess_impl.hpp"

#endif
