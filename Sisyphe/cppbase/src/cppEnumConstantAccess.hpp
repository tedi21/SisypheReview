/* 
 * cppEnumConstantAccess.hpp
 *
 *
 * @date 28-08-2016
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPENUMCONSTANT_ACCESS_HPP_
#define _CPPENUMCONSTANT_ACCESS_HPP_

#include <boost/scoped_ptr.hpp>
#include <memory>
#include <boost/signals2.hpp>
#include <boost/any.hpp>
#include "cppBaseExport.hpp"
#include "cppEnumConstant.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(data_access)

using namespace entity; 

/// Represents an access class for CppEnumConstant object.
/// This class is used to manage CppEnumConstant entity in database.
template <class EncodingT>
class CPPBASE_API  _CppEnumConstantAccess {
private :
	std::vector< boost::shared_ptr< _CppEnumConstant<EncodingT> > > m_backup;
	// Is a transaction in progress before queries ?
	bool m_transactionOwner;
	static _CppEnumConstantAccess<EncodingT>* m_instance; 

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
	/** Creates a new element CppEnumConstantAccess.
	*/
	_CppEnumConstantAccess();
	/** Releases the CppEnumConstantAccess object.
	*/
	~_CppEnumConstantAccess();
	Category*	m_logger;

protected :
public :
	/** Returns CppEnumConstantAccess object.
	@return Instance of CppEnumConstantAccess.
	*/
	 static _CppEnumConstantAccess<EncodingT>* getInstance();
	/** Returns CppEnumConstant objects from database.
	@param filter Condition allowing to filter data.
	@return List of CppEnumConstant objects.
	*/
	 std::vector< boost::shared_ptr< _CppEnumConstant<EncodingT> > > getManyCppEnumConstants(typename EncodingT::string_t const&  filter) const;
	/** Returns all CppEnumConstant objects from database.
	@return List of CppEnumConstant objects.
	*/
	 std::vector< boost::shared_ptr< _CppEnumConstant<EncodingT> > > getAllCppEnumConstants() const;
	/** Returns CppEnumConstant object from database.
	@param identifier 
	@return The CppEnumConstant object.
	*/
	 boost::shared_ptr< _CppEnumConstant<EncodingT> > getOneCppEnumConstant(int identifier) const;
	/** Returns CppEnumConstant objects from database. Data are locked for update.
	@param filter Condition allowing to filter data.
	@param nowait Asynchonous call.
	@return List of CppEnumConstant objects.
	*/
	 std::vector< boost::shared_ptr< _CppEnumConstant<EncodingT> > > selectManyCppEnumConstants(typename EncodingT::string_t const&  filter, bool nowait = false, bool addition = false);
	/** Returns CppEnumConstant object from database. Data are locked for update.
	@param identifier 
	@param nowait Asynchonous call.
	@return The CppEnumConstant object.
	*/
	 boost::shared_ptr< _CppEnumConstant<EncodingT> > selectOneCppEnumConstant(int identifier, bool nowait = false, bool addition = false);
	/** Returns whether the data <i>CppEnumConstant</i> are selected.
	@param o The CppEnumConstant object.
	@return True if the data <i>CppEnumConstant</i> are selected.
	*/
	 bool isSelectedCppEnumConstant(boost::shared_ptr< _CppEnumConstant<EncodingT> > o) const;
	/** Cancel the selection. The CppEnumConstant object cannot be updated or deleted from database.
	*/
	 void cancelSelection();
	/** Fills cppEnum data from database.
	@param o The CppEnumConstant object.
	*/
	 void fillCppEnum(boost::shared_ptr< _CppEnumConstant<EncodingT> > o);
	/** Returns whether CppEnumConstant data are altered from database.
	@param o The CppEnumConstant object.
	@return True if data CppEnumConstant have been altered.
	*/
	 bool isModifiedCppEnumConstant(boost::shared_ptr< _CppEnumConstant<EncodingT> > o) const;
	/** Updates CppEnumConstant data to database.
	@param o The CppEnumConstant object.
	*/
	 void updateCppEnumConstant(boost::shared_ptr< _CppEnumConstant<EncodingT> > o);
	/** Inserts CppEnumConstant data to database.
	@param o The CppEnumConstant object.
	*/
	 void insertCppEnumConstant(boost::shared_ptr< _CppEnumConstant<EncodingT> > o);
	/** Deletes CppEnumConstant data to database.
	@param o The CppEnumConstant object.
	*/
	 void deleteCppEnumConstant(boost::shared_ptr< _CppEnumConstant<EncodingT> > o);
	/** Add signal for CppEnumConstant insertion.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addInsertSignal(typename signal_t::slot_function_type subscriber);
	/** Add signal for CppEnumConstant update.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addUpdateSignal(typename signal_t::slot_function_type subscriber);
	/** Add signal for CppEnumConstant deletion.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addDeleteSignal(typename signal_t::slot_function_type subscriber);
	/** Add signal for CppEnumConstant transaction result.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber);
	/** Remove signal for CppEnumConstant insertion.
	@param connection The connection
	*/
	 void removeInsertSignal(connection_t connection);
	/** Remove signal for CppEnumConstant update.
	@param connection The connection
	*/
	 void removeUpdateSignal(connection_t connection);
	/** Remove signal for CppEnumConstant deletion.
	@param connection The connection
	*/
	 void removeDeleteSignal(connection_t connection);
	/** Remove signal for CppEnumConstant transaction result.
	@param connection The connection
	*/
	 void removeTransactionSignal(connection_t connection);
};

typedef _CppEnumConstantAccess<ucs> UniCppEnumConstantAccess;
typedef _CppEnumConstantAccess<ansi> CppEnumConstantAccess;

NAMESPACE_END

#undef C
#undef A

#if !defined(HAS_CPPBASE_DLL) || defined(BUILD_CPPBASE_DLL)
#include "cppEnumConstantAccess_impl.hpp"
#endif // !defined(HAS_CPPBASE_DLL) || defined(BUILD_CPPBASE_DLL)

#endif
