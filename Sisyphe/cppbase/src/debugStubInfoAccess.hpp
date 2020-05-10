/* 
 * debugStubInfoAccess.hpp
 *
 *
 * @date 10-05-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _DEBUGSTUBINFO_ACCESS_HPP_
#define _DEBUGSTUBINFO_ACCESS_HPP_

#include <boost/scoped_ptr.hpp>
#include <memory>
#include <boost/signals2.hpp>
#include <boost/any.hpp>
#include "cppBaseExport.hpp"
#include "debugStubInfo.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(data_access)

using namespace entity; 

/// Represents an access class for DebugStubInfo object.
/// This class is used to manage DebugStubInfo entity in database.
template <class EncodingT>
class CPPBASE_API  _DebugStubInfoAccess {
private :
	std::list< boost::shared_ptr< _DebugStubInfo<EncodingT> > > m_backup;
	// Is a transaction in progress before queries ?
	bool m_transactionOwner;
	static _DebugStubInfoAccess<EncodingT>* m_instance; 

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
	/** Creates a new element DebugStubInfoAccess.
	*/
	_DebugStubInfoAccess();
	/** Releases the DebugStubInfoAccess object.
	*/
	~_DebugStubInfoAccess();
	Category*	m_logger;

protected :
public :
	/** Returns DebugStubInfoAccess object.
	@return Instance of DebugStubInfoAccess.
	*/
	 static _DebugStubInfoAccess<EncodingT>* getInstance();
	/** Returns DebugStubInfo objects from database.
	@param filter Condition allowing to filter data.
	@return List of DebugStubInfo objects.
	*/
	 std::vector< boost::shared_ptr< _DebugStubInfo<EncodingT> > > getManyDebugStubInfos(typename EncodingT::string_t const&  filter) const;
	/** Returns all DebugStubInfo objects from database.
	@return List of DebugStubInfo objects.
	*/
	 std::vector< boost::shared_ptr< _DebugStubInfo<EncodingT> > > getAllDebugStubInfos() const;
	/** Returns DebugStubInfo object from database.
	@param identifier 
	@return The DebugStubInfo object.
	*/
	 boost::shared_ptr< _DebugStubInfo<EncodingT> > getOneDebugStubInfo(long long identifier) const;
	/** Returns DebugStubInfo objects from database. Data are locked for update.
	@param filter Condition allowing to filter data.
	@param nowait Asynchonous call.
	@return List of DebugStubInfo objects.
	*/
	 std::vector< boost::shared_ptr< _DebugStubInfo<EncodingT> > > selectManyDebugStubInfos(typename EncodingT::string_t const&  filter, bool nowait = false, bool addition = false);
	/** Returns DebugStubInfo object from database. Data are locked for update.
	@param identifier 
	@param nowait Asynchonous call.
	@return The DebugStubInfo object.
	*/
	 boost::shared_ptr< _DebugStubInfo<EncodingT> > selectOneDebugStubInfo(long long identifier, bool nowait = false, bool addition = false);
	/** Returns whether the data <i>DebugStubInfo</i> are selected.
	@param o The DebugStubInfo object.
	@return True if the data <i>DebugStubInfo</i> are selected.
	*/
	 bool isSelectedDebugStubInfo(boost::shared_ptr< _DebugStubInfo<EncodingT> > o) const;
	/** Cancel the selection. The DebugStubInfo object cannot be updated or deleted from database.
	*/
	 void cancelSelection();
	/** Fills debugFileInfo data from database.
	@param o The DebugStubInfo object.
	*/
	 void fillDebugFileInfo(boost::shared_ptr< _DebugStubInfo<EncodingT> > o);
	/** Fills debugValueInfo data from database.
	@param o The DebugStubInfo object.
	@param nowait Asynchronous call.
	*/
	 void fillAllDebugValueInfos(boost::shared_ptr< _DebugStubInfo<EncodingT> > o, bool nowait = false);
	/** Fills debugValueInfo data from database.
	@param o The DebugStubInfo object.
	@param identifier 
	@param nowait Asynchronous call.
	*/
	 void fillOneDebugValueInfo(boost::shared_ptr< _DebugStubInfo<EncodingT> > o, long long identifier, bool nowait = false);
	/** Fills debugValueInfo data from database.
	@param o The DebugStubInfo object.
	@param filter Condition allowing to filter data.
	@param nowait Asynchonous call.
	*/
	 void fillManyDebugValueInfos(boost::shared_ptr< _DebugStubInfo<EncodingT> > o, typename EncodingT::string_t const&  filter, bool nowait = false);
	/** Returns whether DebugStubInfo data are altered from database.
	@param o The DebugStubInfo object.
	@return True if data DebugStubInfo have been altered.
	*/
	 bool isModifiedDebugStubInfo(boost::shared_ptr< _DebugStubInfo<EncodingT> > o) const;
	/** Updates DebugStubInfo data to database.
	@param o The DebugStubInfo object.
	*/
	 void updateDebugStubInfo(boost::shared_ptr< _DebugStubInfo<EncodingT> > o);
	/** Inserts DebugStubInfo data to database.
	@param o The DebugStubInfo object.
	*/
	 void insertDebugStubInfo(boost::shared_ptr< _DebugStubInfo<EncodingT> > o);
	/** Deletes DebugStubInfo data to database.
	@param o The DebugStubInfo object.
	*/
	 void deleteDebugStubInfo(boost::shared_ptr< _DebugStubInfo<EncodingT> > o);
	/** Add signal for DebugStubInfo insertion.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addInsertSignal(typename signal_t::slot_function_type subscriber);
	/** Add signal for DebugStubInfo update.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addUpdateSignal(typename signal_t::slot_function_type subscriber);
	/** Add signal for DebugStubInfo deletion.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addDeleteSignal(typename signal_t::slot_function_type subscriber);
	/** Add signal for DebugStubInfo transaction result.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber);
	/** Remove signal for DebugStubInfo insertion.
	@param connection The connection
	*/
	 void removeInsertSignal(connection_t connection);
	/** Remove signal for DebugStubInfo update.
	@param connection The connection
	*/
	 void removeUpdateSignal(connection_t connection);
	/** Remove signal for DebugStubInfo deletion.
	@param connection The connection
	*/
	 void removeDeleteSignal(connection_t connection);
	/** Remove signal for DebugStubInfo transaction result.
	@param connection The connection
	*/
	 void removeTransactionSignal(connection_t connection);
};

typedef _DebugStubInfoAccess<ucs> UniDebugStubInfoAccess;
typedef _DebugStubInfoAccess<ansi> DebugStubInfoAccess;

NAMESPACE_END

#undef C
#undef A

#if !defined(HAS_CPPBASE_DLL) || defined(BUILD_CPPBASE_DLL)
#include "debugStubInfoAccess_impl.hpp"
#endif // !defined(HAS_CPPBASE_DLL) || defined(BUILD_CPPBASE_DLL)

#endif
