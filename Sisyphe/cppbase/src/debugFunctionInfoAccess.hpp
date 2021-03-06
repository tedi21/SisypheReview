/* 
 * debugFunctionInfoAccess.hpp
 *
 *
 * @date 14-07-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _DEBUGFUNCTIONINFO_ACCESS_HPP_
#define _DEBUGFUNCTIONINFO_ACCESS_HPP_

#include <boost/scoped_ptr.hpp>
#include <memory>
#include <boost/signals2.hpp>
#include <boost/any.hpp>
#include "cppBaseExport.hpp"
#include "debugFunctionInfo.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(data_access)

using namespace entity; 

/// Represents an access class for DebugFunctionInfo object.
/// This class is used to manage DebugFunctionInfo entity in database.
template <class EncodingT>
class CPPBASE_API  _DebugFunctionInfoAccess {
private :
	std::list< boost::shared_ptr< _DebugFunctionInfo<EncodingT> > > m_backup;
	// Is a transaction in progress before queries ?
	bool m_transactionOwner;
	static _DebugFunctionInfoAccess<EncodingT>* m_instance; 

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
	/** Creates a new element DebugFunctionInfoAccess.
	*/
	_DebugFunctionInfoAccess();
	/** Releases the DebugFunctionInfoAccess object.
	*/
	~_DebugFunctionInfoAccess();
	Category*	m_logger;

protected :
public :
	/** Returns DebugFunctionInfoAccess object.
	@return Instance of DebugFunctionInfoAccess.
	*/
	 static _DebugFunctionInfoAccess<EncodingT>* getInstance();
	/** Returns DebugFunctionInfo objects from database.
	@param filter Condition allowing to filter data.
	@return List of DebugFunctionInfo objects.
	*/
	 std::vector< boost::shared_ptr< _DebugFunctionInfo<EncodingT> > > getManyDebugFunctionInfos(typename EncodingT::string_t const&  filter) const;
	/** Returns all DebugFunctionInfo objects from database.
	@return List of DebugFunctionInfo objects.
	*/
	 std::vector< boost::shared_ptr< _DebugFunctionInfo<EncodingT> > > getAllDebugFunctionInfos() const;
	/** Returns DebugFunctionInfo object from database.
	@param identifier 
	@return The DebugFunctionInfo object.
	*/
	 boost::shared_ptr< _DebugFunctionInfo<EncodingT> > getOneDebugFunctionInfo(long long identifier) const;
	/** Returns DebugFunctionInfo objects from database. Data are locked for update.
	@param filter Condition allowing to filter data.
	@param nowait Asynchonous call.
	@return List of DebugFunctionInfo objects.
	*/
	 std::vector< boost::shared_ptr< _DebugFunctionInfo<EncodingT> > > selectManyDebugFunctionInfos(typename EncodingT::string_t const&  filter, bool nowait = false, bool addition = false);
	/** Returns DebugFunctionInfo object from database. Data are locked for update.
	@param identifier 
	@param nowait Asynchonous call.
	@return The DebugFunctionInfo object.
	*/
	 boost::shared_ptr< _DebugFunctionInfo<EncodingT> > selectOneDebugFunctionInfo(long long identifier, bool nowait = false, bool addition = false);
	/** Returns whether the data <i>DebugFunctionInfo</i> are selected.
	@param o The DebugFunctionInfo object.
	@return True if the data <i>DebugFunctionInfo</i> are selected.
	*/
	 bool isSelectedDebugFunctionInfo(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > o) const;
	/** Cancel the selection. The DebugFunctionInfo object cannot be updated or deleted from database.
	*/
	 void cancelSelection();
	/** Fills debugTypeInfo data from database.
	@param o The DebugFunctionInfo object.
	*/
	 void fillDebugTypeInfo(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > o);
	/** Fills debugFileInfo data from database.
	@param o The DebugFunctionInfo object.
	*/
	 void fillDebugFileInfo(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > o);
	/** Fills debugVariableInfo data from database.
	@param o The DebugFunctionInfo object.
	@param nowait Asynchronous call.
	*/
	 void fillAllDebugVariableInfos(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > o, bool nowait = false);
	/** Fills debugVariableInfo data from database.
	@param o The DebugFunctionInfo object.
	@param identifier 
	@param nowait Asynchronous call.
	*/
	 void fillOneDebugVariableInfo(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > o, long long identifier, bool nowait = false);
	/** Fills debugVariableInfo data from database.
	@param o The DebugFunctionInfo object.
	@param filter Condition allowing to filter data.
	@param nowait Asynchonous call.
	*/
	 void fillManyDebugVariableInfos(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > o, typename EncodingT::string_t const&  filter, bool nowait = false);
	/** Returns whether DebugFunctionInfo data are altered from database.
	@param o The DebugFunctionInfo object.
	@return True if data DebugFunctionInfo have been altered.
	*/
	 bool isModifiedDebugFunctionInfo(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > o) const;
	/** Updates DebugFunctionInfo data to database.
	@param o The DebugFunctionInfo object.
	*/
	 void updateDebugFunctionInfo(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > o);
	/** Inserts DebugFunctionInfo data to database.
	@param o The DebugFunctionInfo object.
	*/
	 void insertDebugFunctionInfo(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > o);
	/** Deletes DebugFunctionInfo data to database.
	@param o The DebugFunctionInfo object.
	*/
	 void deleteDebugFunctionInfo(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > o);
	/** Add signal for DebugFunctionInfo insertion.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addInsertSignal(typename signal_t::slot_function_type subscriber);
	/** Add signal for DebugFunctionInfo update.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addUpdateSignal(typename signal_t::slot_function_type subscriber);
	/** Add signal for DebugFunctionInfo deletion.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addDeleteSignal(typename signal_t::slot_function_type subscriber);
	/** Add signal for DebugFunctionInfo transaction result.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber);
	/** Remove signal for DebugFunctionInfo insertion.
	@param connection The connection
	*/
	 void removeInsertSignal(connection_t connection);
	/** Remove signal for DebugFunctionInfo update.
	@param connection The connection
	*/
	 void removeUpdateSignal(connection_t connection);
	/** Remove signal for DebugFunctionInfo deletion.
	@param connection The connection
	*/
	 void removeDeleteSignal(connection_t connection);
	/** Remove signal for DebugFunctionInfo transaction result.
	@param connection The connection
	*/
	 void removeTransactionSignal(connection_t connection);
};

typedef _DebugFunctionInfoAccess<ucs> UniDebugFunctionInfoAccess;
typedef _DebugFunctionInfoAccess<ansi> DebugFunctionInfoAccess;

NAMESPACE_END

#undef C
#undef A

#if !defined(HAS_CPPBASE_DLL) || defined(BUILD_CPPBASE_DLL)
#include "debugFunctionInfoAccess_impl.hpp"
#endif // !defined(HAS_CPPBASE_DLL) || defined(BUILD_CPPBASE_DLL)

#endif
