/* 
 * debugVariableInfoAccess.hpp
 *
 *
 * @date 31-07-2022
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _DEBUGVARIABLEINFO_ACCESS_HPP_
#define _DEBUGVARIABLEINFO_ACCESS_HPP_

#include <boost/scoped_ptr.hpp>
#include <memory>
#include <boost/signals2.hpp>
#include <boost/any.hpp>
#include "cppBaseExport.hpp"
#include "debugVariableInfo.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(data_access)

using namespace entity; 

/// Represents an access class for DebugVariableInfo object.
/// This class is used to manage DebugVariableInfo entity in database.
template <class EncodingT>
class CPPBASE_API  _DebugVariableInfoAccess {
private :
	using backup_t = std::set< boost::shared_ptr< _DebugVariableInfo<EncodingT> >, typename _DebugVariableInfo<EncodingT>::DebugVariableInfoIDInferior >;
	backup_t m_backup;
	// Is a transaction in progress before queries ?
	bool m_transactionOwner;
	static _DebugVariableInfoAccess<EncodingT>* m_instance; 

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
	/** Creates a new element DebugVariableInfoAccess.
	*/
	_DebugVariableInfoAccess();
	/** Releases the DebugVariableInfoAccess object.
	*/
	~_DebugVariableInfoAccess();
	Category*	m_logger;

protected :
public :
	/** Returns DebugVariableInfoAccess object.
	@return Instance of DebugVariableInfoAccess.
	*/
	 static _DebugVariableInfoAccess<EncodingT>* getInstance();
	/** Returns DebugVariableInfo objects from database.
	@param filter Condition allowing to filter data.
	@return List of DebugVariableInfo objects.
	*/
	 std::vector< boost::shared_ptr< _DebugVariableInfo<EncodingT> > > getManyDebugVariableInfos(typename EncodingT::string_t const&  filter) const;
	/** Returns all DebugVariableInfo objects from database.
	@return List of DebugVariableInfo objects.
	*/
	 std::vector< boost::shared_ptr< _DebugVariableInfo<EncodingT> > > getAllDebugVariableInfos() const;
	/** Returns DebugVariableInfo object from database.
	@param identifier 
	@return The DebugVariableInfo object.
	*/
	 boost::shared_ptr< _DebugVariableInfo<EncodingT> > getOneDebugVariableInfo(long long identifier) const;
	/** Returns DebugVariableInfo objects from database. Data are locked for update.
	@param filter Condition allowing to filter data.
	@param nowait Asynchonous call.
	@return List of DebugVariableInfo objects.
	*/
	 std::vector< boost::shared_ptr< _DebugVariableInfo<EncodingT> > > selectManyDebugVariableInfos(typename EncodingT::string_t const&  filter, bool nowait = false, bool addition = false);
	/** Returns DebugVariableInfo object from database. Data are locked for update.
	@param identifier 
	@param nowait Asynchonous call.
	@return The DebugVariableInfo object.
	*/
	 boost::shared_ptr< _DebugVariableInfo<EncodingT> > selectOneDebugVariableInfo(long long identifier, bool nowait = false, bool addition = false);
	/** Returns whether the data <i>DebugVariableInfo</i> are selected.
	@param o The DebugVariableInfo object.
	@return True if the data <i>DebugVariableInfo</i> are selected.
	*/
	 bool isSelectedDebugVariableInfo(boost::shared_ptr< _DebugVariableInfo<EncodingT> > o) const;
	/** Cancel the selection. The DebugVariableInfo object cannot be updated or deleted from database.
	*/
	 void cancelSelection();
	/** Fills debugTypeInfo data from database.
	@param o The DebugVariableInfo object.
	*/
	 void fillDebugTypeInfo(boost::shared_ptr< _DebugVariableInfo<EncodingT> > o);
	/** Fills debugFunctionInfo data from database.
	@param o The DebugVariableInfo object.
	*/
	 void fillDebugFunctionInfo(boost::shared_ptr< _DebugVariableInfo<EncodingT> > o);
	/** Fills debugValueInfo data from database.
	@param o The DebugVariableInfo object.
	@param nowait Asynchronous call.
	*/
	 void fillAllDebugValueInfos(boost::shared_ptr< _DebugVariableInfo<EncodingT> > o, bool nowait = false);
	/** Fills debugValueInfo data from database.
	@param o The DebugVariableInfo object.
	@param identifier 
	@param nowait Asynchronous call.
	*/
	 void fillOneDebugValueInfo(boost::shared_ptr< _DebugVariableInfo<EncodingT> > o, long long identifier, bool nowait = false);
	/** Fills debugValueInfo data from database.
	@param o The DebugVariableInfo object.
	@param filter Condition allowing to filter data.
	@param nowait Asynchonous call.
	*/
	 void fillManyDebugValueInfos(boost::shared_ptr< _DebugVariableInfo<EncodingT> > o, typename EncodingT::string_t const&  filter, bool nowait = false);
	/** Returns whether DebugVariableInfo data are altered from database.
	@param o The DebugVariableInfo object.
	@return True if data DebugVariableInfo have been altered.
	*/
	 bool isModifiedDebugVariableInfo(boost::shared_ptr< _DebugVariableInfo<EncodingT> > o) const;
	/** Updates DebugVariableInfo data to database.
	@param o The DebugVariableInfo object.
	*/
	 void updateDebugVariableInfo(boost::shared_ptr< _DebugVariableInfo<EncodingT> > o);
	/** Inserts DebugVariableInfo data to database.
	@param o The DebugVariableInfo object.
	*/
	 void insertDebugVariableInfo(boost::shared_ptr< _DebugVariableInfo<EncodingT> > o);
	/** Deletes DebugVariableInfo data to database.
	@param o The DebugVariableInfo object.
	*/
	 void deleteDebugVariableInfo(boost::shared_ptr< _DebugVariableInfo<EncodingT> > o);
	/** Add signal for DebugVariableInfo insertion.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addInsertSignal(typename signal_t::slot_function_type subscriber);
	/** Add signal for DebugVariableInfo update.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addUpdateSignal(typename signal_t::slot_function_type subscriber);
	/** Add signal for DebugVariableInfo deletion.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addDeleteSignal(typename signal_t::slot_function_type subscriber);
	/** Add signal for DebugVariableInfo transaction result.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber);
	/** Remove signal for DebugVariableInfo insertion.
	@param connection The connection
	*/
	 void removeInsertSignal(connection_t connection);
	/** Remove signal for DebugVariableInfo update.
	@param connection The connection
	*/
	 void removeUpdateSignal(connection_t connection);
	/** Remove signal for DebugVariableInfo deletion.
	@param connection The connection
	*/
	 void removeDeleteSignal(connection_t connection);
	/** Remove signal for DebugVariableInfo transaction result.
	@param connection The connection
	*/
	 void removeTransactionSignal(connection_t connection);
};

typedef _DebugVariableInfoAccess<ucs> UniDebugVariableInfoAccess;
typedef _DebugVariableInfoAccess<ansi> DebugVariableInfoAccess;

NAMESPACE_END

#undef C
#undef A

#if !defined(HAS_CPPBASE_DLL) || defined(BUILD_CPPBASE_DLL)
#include "debugVariableInfoAccess_impl.hpp"
#endif // !defined(HAS_CPPBASE_DLL) || defined(BUILD_CPPBASE_DLL)

#endif
