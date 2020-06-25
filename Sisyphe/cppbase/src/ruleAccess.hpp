/* 
 * ruleAccess.hpp
 *
 *
 * @date 25-06-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _RULE_ACCESS_HPP_
#define _RULE_ACCESS_HPP_

#include <boost/scoped_ptr.hpp>
#include <memory>
#include <boost/signals2.hpp>
#include <boost/any.hpp>
#include "cppBaseExport.hpp"
#include "rule.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(data_access)

using namespace entity; 

/// Represents an access class for Rule object.
/// This class is used to manage Rule entity in database.
template <class EncodingT>
class CPPBASE_API  _RuleAccess {
private :
	std::list< boost::shared_ptr< _Rule<EncodingT> > > m_backup;
	// Is a transaction in progress before queries ?
	bool m_transactionOwner;
	static _RuleAccess<EncodingT>* m_instance; 

public:
	typedef boost::signals2::signal<void (operation_access_t, typename EncodingT::string_t const&, boost::any const&)>  signal_t;
	typedef boost::signals2::signal<void (operation_access_t)>  signal_transaction_t;
	typedef boost::signals2::connection  connection_t;

private:
	signal_t m_insertSignal;
	signal_t m_updateSignal;
	signal_t m_deleteSignal;
	signal_transaction_t m_transactionSignal;

private:
	/** Creates a new element RuleAccess.
	*/
	_RuleAccess();
	/** Releases the RuleAccess object.
	*/
	~_RuleAccess();
	Category*	m_logger;

protected :
public :
	/** Returns RuleAccess object.
	@return Instance of RuleAccess.
	*/
	 static _RuleAccess<EncodingT>* getInstance();
	/** Returns Rule objects from database.
	@param filter Condition allowing to filter data.
	@return List of Rule objects.
	*/
	 std::vector< boost::shared_ptr< _Rule<EncodingT> > > getManyRules(typename EncodingT::string_t const&  filter) const;
	/** Returns all Rule objects from database.
	@return List of Rule objects.
	*/
	 std::vector< boost::shared_ptr< _Rule<EncodingT> > > getAllRules() const;
	/** Returns Rule object from database.
	@param identifier 
	@return The Rule object.
	*/
	 boost::shared_ptr< _Rule<EncodingT> > getOneRule(long long identifier) const;
	/** Returns Rule objects from database. Data are locked for update.
	@param filter Condition allowing to filter data.
	@param nowait Asynchonous call.
	@return List of Rule objects.
	*/
	 std::vector< boost::shared_ptr< _Rule<EncodingT> > > selectManyRules(typename EncodingT::string_t const&  filter, bool nowait = false, bool addition = false);
	/** Returns Rule object from database. Data are locked for update.
	@param identifier 
	@param nowait Asynchonous call.
	@return The Rule object.
	*/
	 boost::shared_ptr< _Rule<EncodingT> > selectOneRule(long long identifier, bool nowait = false, bool addition = false);
	/** Returns whether the data <i>Rule</i> are selected.
	@param o The Rule object.
	@return True if the data <i>Rule</i> are selected.
	*/
	 bool isSelectedRule(boost::shared_ptr< _Rule<EncodingT> > o) const;
	/** Cancel the selection. The Rule object cannot be updated or deleted from database.
	*/
	 void cancelSelection();
	/** Returns whether Rule data are altered from database.
	@param o The Rule object.
	@return True if data Rule have been altered.
	*/
	 bool isModifiedRule(boost::shared_ptr< _Rule<EncodingT> > o) const;
	/** Updates Rule data to database.
	@param o The Rule object.
	*/
	 void updateRule(boost::shared_ptr< _Rule<EncodingT> > o);
	/** Inserts Rule data to database.
	@param o The Rule object.
	*/
	 void insertRule(boost::shared_ptr< _Rule<EncodingT> > o);
	/** Deletes Rule data to database.
	@param o The Rule object.
	*/
	 void deleteRule(boost::shared_ptr< _Rule<EncodingT> > o);
	/** Add signal for Rule insertion.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addInsertSignal(typename signal_t::slot_function_type subscriber);
	/** Add signal for Rule update.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addUpdateSignal(typename signal_t::slot_function_type subscriber);
	/** Add signal for Rule deletion.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addDeleteSignal(typename signal_t::slot_function_type subscriber);
	/** Add signal for Rule transaction result.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber);
	/** Remove signal for Rule insertion.
	@param connection The connection
	*/
	 void removeInsertSignal(connection_t connection);
	/** Remove signal for Rule update.
	@param connection The connection
	*/
	 void removeUpdateSignal(connection_t connection);
	/** Remove signal for Rule deletion.
	@param connection The connection
	*/
	 void removeDeleteSignal(connection_t connection);
	/** Remove signal for Rule transaction result.
	@param connection The connection
	*/
	 void removeTransactionSignal(connection_t connection);
};

typedef _RuleAccess<ucs> UniRuleAccess;
typedef _RuleAccess<ansi> RuleAccess;

NAMESPACE_END

#undef C
#undef A

#if !defined(HAS_CPPBASE_DLL) || defined(BUILD_CPPBASE_DLL)
#include "ruleAccess_impl.hpp"
#endif // !defined(HAS_CPPBASE_DLL) || defined(BUILD_CPPBASE_DLL)

#endif
