/* 
 * cppVariableAccess.hpp
 *
 *
 * @date 14-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPVARIABLE_ACCESS_HPP_
#define _CPPVARIABLE_ACCESS_HPP_

#include <boost/scoped_ptr.hpp>
#include <memory>
#include <boost/signals2.hpp>
#include <boost/any.hpp>
#include "cppBaseExport.hpp"
#include "cppVariable.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(data_access)

using namespace entity; 

/// Represents an access class for CppVariable object.
/// This class is used to manage CppVariable entity in database.
template <class EncodingT>
class CPPBASE_API  _CppVariableAccess {
private :
	std::list< boost::shared_ptr< _CppVariable<EncodingT> > > m_backup;
	// Is a transaction in progress before queries ?
	bool m_transactionOwner;
	static _CppVariableAccess<EncodingT>* m_instance; 

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
	/** Creates a new element CppVariableAccess.
	*/
	_CppVariableAccess();
	/** Releases the CppVariableAccess object.
	*/
	~_CppVariableAccess();
	Category*	m_logger;

protected :
public :
	/** Returns CppVariableAccess object.
	@return Instance of CppVariableAccess.
	*/
	 static _CppVariableAccess<EncodingT>* getInstance();
	/** Returns CppVariable objects from database.
	@param filter Condition allowing to filter data.
	@return List of CppVariable objects.
	*/
	 std::vector< boost::shared_ptr< _CppVariable<EncodingT> > > getManyCppVariables(typename EncodingT::string_t const&  filter) const;
	/** Returns all CppVariable objects from database.
	@return List of CppVariable objects.
	*/
	 std::vector< boost::shared_ptr< _CppVariable<EncodingT> > > getAllCppVariables() const;
	/** Returns CppVariable object from database.
	@param identifier 
	@return The CppVariable object.
	*/
	 boost::shared_ptr< _CppVariable<EncodingT> > getOneCppVariable(long long identifier) const;
	/** Returns CppVariable objects from database. Data are locked for update.
	@param filter Condition allowing to filter data.
	@param nowait Asynchonous call.
	@return List of CppVariable objects.
	*/
	 std::vector< boost::shared_ptr< _CppVariable<EncodingT> > > selectManyCppVariables(typename EncodingT::string_t const&  filter, bool nowait = false, bool addition = false);
	/** Returns CppVariable object from database. Data are locked for update.
	@param identifier 
	@param nowait Asynchonous call.
	@return The CppVariable object.
	*/
	 boost::shared_ptr< _CppVariable<EncodingT> > selectOneCppVariable(long long identifier, bool nowait = false, bool addition = false);
	/** Returns whether the data <i>CppVariable</i> are selected.
	@param o The CppVariable object.
	@return True if the data <i>CppVariable</i> are selected.
	*/
	 bool isSelectedCppVariable(boost::shared_ptr< _CppVariable<EncodingT> > o) const;
	/** Cancel the selection. The CppVariable object cannot be updated or deleted from database.
	*/
	 void cancelSelection();
	/** Fills cppFunction data from database.
	@param o The CppVariable object.
	*/
	 void fillCppFunction(boost::shared_ptr< _CppVariable<EncodingT> > o);
	/** Fills cppFile data from database.
	@param o The CppVariable object.
	*/
	 void fillCppFile(boost::shared_ptr< _CppVariable<EncodingT> > o);
	/** Returns whether CppVariable data are altered from database.
	@param o The CppVariable object.
	@return True if data CppVariable have been altered.
	*/
	 bool isModifiedCppVariable(boost::shared_ptr< _CppVariable<EncodingT> > o) const;
	/** Updates CppVariable data to database.
	@param o The CppVariable object.
	*/
	 void updateCppVariable(boost::shared_ptr< _CppVariable<EncodingT> > o);
	/** Inserts CppVariable data to database.
	@param o The CppVariable object.
	*/
	 void insertCppVariable(boost::shared_ptr< _CppVariable<EncodingT> > o);
	/** Deletes CppVariable data to database.
	@param o The CppVariable object.
	*/
	 void deleteCppVariable(boost::shared_ptr< _CppVariable<EncodingT> > o);
	/** Add signal for CppVariable insertion.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addInsertSignal(typename signal_t::slot_function_type subscriber);
	/** Add signal for CppVariable update.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addUpdateSignal(typename signal_t::slot_function_type subscriber);
	/** Add signal for CppVariable deletion.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addDeleteSignal(typename signal_t::slot_function_type subscriber);
	/** Add signal for CppVariable transaction result.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber);
	/** Remove signal for CppVariable insertion.
	@param connection The connection
	*/
	 void removeInsertSignal(connection_t connection);
	/** Remove signal for CppVariable update.
	@param connection The connection
	*/
	 void removeUpdateSignal(connection_t connection);
	/** Remove signal for CppVariable deletion.
	@param connection The connection
	*/
	 void removeDeleteSignal(connection_t connection);
	/** Remove signal for CppVariable transaction result.
	@param connection The connection
	*/
	 void removeTransactionSignal(connection_t connection);
};

typedef _CppVariableAccess<ucs> UniCppVariableAccess;
typedef _CppVariableAccess<ansi> CppVariableAccess;

NAMESPACE_END

#undef C
#undef A

#if !defined(HAS_CPPBASE_DLL) || defined(BUILD_CPPBASE_DLL)
#include "cppVariableAccess_impl.hpp"
#endif // !defined(HAS_CPPBASE_DLL) || defined(BUILD_CPPBASE_DLL)

#endif
