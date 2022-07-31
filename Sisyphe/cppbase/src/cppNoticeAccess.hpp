/* 
 * cppNoticeAccess.hpp
 *
 *
 * @date 31-07-2022
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPNOTICE_ACCESS_HPP_
#define _CPPNOTICE_ACCESS_HPP_

#include <boost/scoped_ptr.hpp>
#include <memory>
#include <boost/signals2.hpp>
#include <boost/any.hpp>
#include "cppBaseExport.hpp"
#include "cppNotice.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(data_access)

using namespace entity; 

/// Represents an access class for CppNotice object.
/// This class is used to manage CppNotice entity in database.
template <class EncodingT>
class CPPBASE_API  _CppNoticeAccess {
private :
	using backup_t = std::set< boost::shared_ptr< _CppNotice<EncodingT> >, typename _CppNotice<EncodingT>::CppNoticeIDInferior >;
	backup_t m_backup;
	// Is a transaction in progress before queries ?
	bool m_transactionOwner;
	static _CppNoticeAccess<EncodingT>* m_instance; 

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
	/** Creates a new element CppNoticeAccess.
	*/
	_CppNoticeAccess();
	/** Releases the CppNoticeAccess object.
	*/
	~_CppNoticeAccess();
	Category*	m_logger;

protected :
public :
	/** Returns CppNoticeAccess object.
	@return Instance of CppNoticeAccess.
	*/
	 static _CppNoticeAccess<EncodingT>* getInstance();
	/** Returns CppNotice objects from database.
	@param filter Condition allowing to filter data.
	@return List of CppNotice objects.
	*/
	 std::vector< boost::shared_ptr< _CppNotice<EncodingT> > > getManyCppNotices(typename EncodingT::string_t const&  filter) const;
	/** Returns all CppNotice objects from database.
	@return List of CppNotice objects.
	*/
	 std::vector< boost::shared_ptr< _CppNotice<EncodingT> > > getAllCppNotices() const;
	/** Returns CppNotice object from database.
	@param identifier 
	@return The CppNotice object.
	*/
	 boost::shared_ptr< _CppNotice<EncodingT> > getOneCppNotice(long long identifier) const;
	/** Returns CppNotice objects from database. Data are locked for update.
	@param filter Condition allowing to filter data.
	@param nowait Asynchonous call.
	@return List of CppNotice objects.
	*/
	 std::vector< boost::shared_ptr< _CppNotice<EncodingT> > > selectManyCppNotices(typename EncodingT::string_t const&  filter, bool nowait = false, bool addition = false);
	/** Returns CppNotice object from database. Data are locked for update.
	@param identifier 
	@param nowait Asynchonous call.
	@return The CppNotice object.
	*/
	 boost::shared_ptr< _CppNotice<EncodingT> > selectOneCppNotice(long long identifier, bool nowait = false, bool addition = false);
	/** Returns whether the data <i>CppNotice</i> are selected.
	@param o The CppNotice object.
	@return True if the data <i>CppNotice</i> are selected.
	*/
	 bool isSelectedCppNotice(boost::shared_ptr< _CppNotice<EncodingT> > o) const;
	/** Cancel the selection. The CppNotice object cannot be updated or deleted from database.
	*/
	 void cancelSelection();
	/** Fills cppFile data from database.
	@param o The CppNotice object.
	*/
	 void fillCppFile(boost::shared_ptr< _CppNotice<EncodingT> > o);
	/** Returns whether CppNotice data are altered from database.
	@param o The CppNotice object.
	@return True if data CppNotice have been altered.
	*/
	 bool isModifiedCppNotice(boost::shared_ptr< _CppNotice<EncodingT> > o) const;
	/** Updates CppNotice data to database.
	@param o The CppNotice object.
	*/
	 void updateCppNotice(boost::shared_ptr< _CppNotice<EncodingT> > o);
	/** Inserts CppNotice data to database.
	@param o The CppNotice object.
	*/
	 void insertCppNotice(boost::shared_ptr< _CppNotice<EncodingT> > o);
	/** Deletes CppNotice data to database.
	@param o The CppNotice object.
	*/
	 void deleteCppNotice(boost::shared_ptr< _CppNotice<EncodingT> > o);
	/** Add signal for CppNotice insertion.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addInsertSignal(typename signal_t::slot_function_type subscriber);
	/** Add signal for CppNotice update.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addUpdateSignal(typename signal_t::slot_function_type subscriber);
	/** Add signal for CppNotice deletion.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addDeleteSignal(typename signal_t::slot_function_type subscriber);
	/** Add signal for CppNotice transaction result.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber);
	/** Remove signal for CppNotice insertion.
	@param connection The connection
	*/
	 void removeInsertSignal(connection_t connection);
	/** Remove signal for CppNotice update.
	@param connection The connection
	*/
	 void removeUpdateSignal(connection_t connection);
	/** Remove signal for CppNotice deletion.
	@param connection The connection
	*/
	 void removeDeleteSignal(connection_t connection);
	/** Remove signal for CppNotice transaction result.
	@param connection The connection
	*/
	 void removeTransactionSignal(connection_t connection);
};

typedef _CppNoticeAccess<ucs> UniCppNoticeAccess;
typedef _CppNoticeAccess<ansi> CppNoticeAccess;

NAMESPACE_END

#undef C
#undef A

#if !defined(HAS_CPPBASE_DLL) || defined(BUILD_CPPBASE_DLL)
#include "cppNoticeAccess_impl.hpp"
#endif // !defined(HAS_CPPBASE_DLL) || defined(BUILD_CPPBASE_DLL)

#endif
