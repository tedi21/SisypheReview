/* 
 * cppFileAccess.hpp
 *
 *
 * @date 10-05-2020
 * @author Teddy DIDE
 * @version 1.00
 * cppBase generated by gensources.
 */

#ifndef _CPPFILE_ACCESS_HPP_
#define _CPPFILE_ACCESS_HPP_

#include <boost/scoped_ptr.hpp>
#include <memory>
#include <boost/signals2.hpp>
#include <boost/any.hpp>
#include "cppBaseExport.hpp"
#include "cppFile.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(data_access)

using namespace entity; 

/// Represents an access class for CppFile object.
/// This class is used to manage CppFile entity in database.
template <class EncodingT>
class CPPBASE_API  _CppFileAccess {
private :
	std::list< boost::shared_ptr< _CppFile<EncodingT> > > m_backup;
	// Is a transaction in progress before queries ?
	bool m_transactionOwner;
	static _CppFileAccess<EncodingT>* m_instance; 

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
	/** Creates a new element CppFileAccess.
	*/
	_CppFileAccess();
	/** Releases the CppFileAccess object.
	*/
	~_CppFileAccess();
	Category*	m_logger;

protected :
public :
	/** Returns CppFileAccess object.
	@return Instance of CppFileAccess.
	*/
	 static _CppFileAccess<EncodingT>* getInstance();
	/** Returns CppFile objects from database.
	@param filter Condition allowing to filter data.
	@return List of CppFile objects.
	*/
	 std::vector< boost::shared_ptr< _CppFile<EncodingT> > > getManyCppFiles(typename EncodingT::string_t const&  filter) const;
	/** Returns all CppFile objects from database.
	@return List of CppFile objects.
	*/
	 std::vector< boost::shared_ptr< _CppFile<EncodingT> > > getAllCppFiles() const;
	/** Returns CppFile object from database.
	@param identifier 
	@return The CppFile object.
	*/
	 boost::shared_ptr< _CppFile<EncodingT> > getOneCppFile(long long identifier) const;
	/** Returns CppFile objects from database. Data are locked for update.
	@param filter Condition allowing to filter data.
	@param nowait Asynchonous call.
	@return List of CppFile objects.
	*/
	 std::vector< boost::shared_ptr< _CppFile<EncodingT> > > selectManyCppFiles(typename EncodingT::string_t const&  filter, bool nowait = false, bool addition = false);
	/** Returns CppFile object from database. Data are locked for update.
	@param identifier 
	@param nowait Asynchonous call.
	@return The CppFile object.
	*/
	 boost::shared_ptr< _CppFile<EncodingT> > selectOneCppFile(long long identifier, bool nowait = false, bool addition = false);
	/** Returns whether the data <i>CppFile</i> are selected.
	@param o The CppFile object.
	@return True if the data <i>CppFile</i> are selected.
	*/
	 bool isSelectedCppFile(boost::shared_ptr< _CppFile<EncodingT> > o) const;
	/** Cancel the selection. The CppFile object cannot be updated or deleted from database.
	*/
	 void cancelSelection();
	/** Fills textFile data from database.
	@param o The CppFile object.
	*/
	 void fillTextFile(boost::shared_ptr< _CppFile<EncodingT> > o);
	/** Fills cppFileType data from database.
	@param o The CppFile object.
	*/
	 void fillCppFileType(boost::shared_ptr< _CppFile<EncodingT> > o);
	/** Fills cppDeclarationFunction data from database.
	@param o The CppFile object.
	@param nowait Asynchronous call.
	*/
	 void fillAllCppDeclarationFunctions(boost::shared_ptr< _CppFile<EncodingT> > o, bool nowait = false);
	/** Fills cppDeclarationFunction data from database.
	@param o The CppFile object.
	@param identifier 
	@param nowait Asynchronous call.
	*/
	 void fillOneCppDeclarationFunction(boost::shared_ptr< _CppFile<EncodingT> > o, long long identifier, bool nowait = false);
	/** Fills cppDeclarationFunction data from database.
	@param o The CppFile object.
	@param filter Condition allowing to filter data.
	@param nowait Asynchonous call.
	*/
	 void fillManyCppDeclarationFunctions(boost::shared_ptr< _CppFile<EncodingT> > o, typename EncodingT::string_t const&  filter, bool nowait = false);
	/** Fills cppDefinitionFunction data from database.
	@param o The CppFile object.
	@param nowait Asynchronous call.
	*/
	 void fillAllCppDefinitionFunctions(boost::shared_ptr< _CppFile<EncodingT> > o, bool nowait = false);
	/** Fills cppDefinitionFunction data from database.
	@param o The CppFile object.
	@param identifier 
	@param nowait Asynchronous call.
	*/
	 void fillOneCppDefinitionFunction(boost::shared_ptr< _CppFile<EncodingT> > o, long long identifier, bool nowait = false);
	/** Fills cppDefinitionFunction data from database.
	@param o The CppFile object.
	@param filter Condition allowing to filter data.
	@param nowait Asynchonous call.
	*/
	 void fillManyCppDefinitionFunctions(boost::shared_ptr< _CppFile<EncodingT> > o, typename EncodingT::string_t const&  filter, bool nowait = false);
	/** Fills cppClass data from database.
	@param o The CppFile object.
	@param nowait Asynchronous call.
	*/
	 void fillAllCppClasss(boost::shared_ptr< _CppFile<EncodingT> > o, bool nowait = false);
	/** Fills cppClass data from database.
	@param o The CppFile object.
	@param identifier 
	@param nowait Asynchronous call.
	*/
	 void fillOneCppClass(boost::shared_ptr< _CppFile<EncodingT> > o, long long identifier, bool nowait = false);
	/** Fills cppClass data from database.
	@param o The CppFile object.
	@param filter Condition allowing to filter data.
	@param nowait Asynchonous call.
	*/
	 void fillManyCppClasss(boost::shared_ptr< _CppFile<EncodingT> > o, typename EncodingT::string_t const&  filter, bool nowait = false);
	/** Fills cppInclude data from database.
	@param o The CppFile object.
	@param nowait Asynchronous call.
	*/
	 void fillAllCppIncludes(boost::shared_ptr< _CppFile<EncodingT> > o, bool nowait = false);
	/** Fills cppInclude data from database.
	@param o The CppFile object.
	@param identifier 
	@param nowait Asynchronous call.
	*/
	 void fillOneCppInclude(boost::shared_ptr< _CppFile<EncodingT> > o, long long identifier, bool nowait = false);
	/** Fills cppInclude data from database.
	@param o The CppFile object.
	@param filter Condition allowing to filter data.
	@param nowait Asynchonous call.
	*/
	 void fillManyCppIncludes(boost::shared_ptr< _CppFile<EncodingT> > o, typename EncodingT::string_t const&  filter, bool nowait = false);
	/** Fills cppVariable data from database.
	@param o The CppFile object.
	@param nowait Asynchronous call.
	*/
	 void fillAllCppVariables(boost::shared_ptr< _CppFile<EncodingT> > o, bool nowait = false);
	/** Fills cppVariable data from database.
	@param o The CppFile object.
	@param identifier 
	@param nowait Asynchronous call.
	*/
	 void fillOneCppVariable(boost::shared_ptr< _CppFile<EncodingT> > o, long long identifier, bool nowait = false);
	/** Fills cppVariable data from database.
	@param o The CppFile object.
	@param filter Condition allowing to filter data.
	@param nowait Asynchonous call.
	*/
	 void fillManyCppVariables(boost::shared_ptr< _CppFile<EncodingT> > o, typename EncodingT::string_t const&  filter, bool nowait = false);
	/** Fills cppEnum data from database.
	@param o The CppFile object.
	@param nowait Asynchronous call.
	*/
	 void fillAllCppEnums(boost::shared_ptr< _CppFile<EncodingT> > o, bool nowait = false);
	/** Fills cppEnum data from database.
	@param o The CppFile object.
	@param identifier 
	@param nowait Asynchronous call.
	*/
	 void fillOneCppEnum(boost::shared_ptr< _CppFile<EncodingT> > o, long long identifier, bool nowait = false);
	/** Fills cppEnum data from database.
	@param o The CppFile object.
	@param filter Condition allowing to filter data.
	@param nowait Asynchonous call.
	*/
	 void fillManyCppEnums(boost::shared_ptr< _CppFile<EncodingT> > o, typename EncodingT::string_t const&  filter, bool nowait = false);
	/** Fills cMacro data from database.
	@param o The CppFile object.
	@param nowait Asynchronous call.
	*/
	 void fillAllCMacros(boost::shared_ptr< _CppFile<EncodingT> > o, bool nowait = false);
	/** Fills cMacro data from database.
	@param o The CppFile object.
	@param identifier 
	@param nowait Asynchronous call.
	*/
	 void fillOneCMacro(boost::shared_ptr< _CppFile<EncodingT> > o, long long identifier, bool nowait = false);
	/** Fills cMacro data from database.
	@param o The CppFile object.
	@param filter Condition allowing to filter data.
	@param nowait Asynchonous call.
	*/
	 void fillManyCMacros(boost::shared_ptr< _CppFile<EncodingT> > o, typename EncodingT::string_t const&  filter, bool nowait = false);
	/** Fills cppNotice data from database.
	@param o The CppFile object.
	@param nowait Asynchronous call.
	*/
	 void fillAllCppNotices(boost::shared_ptr< _CppFile<EncodingT> > o, bool nowait = false);
	/** Fills cppNotice data from database.
	@param o The CppFile object.
	@param identifier 
	@param nowait Asynchronous call.
	*/
	 void fillOneCppNotice(boost::shared_ptr< _CppFile<EncodingT> > o, long long identifier, bool nowait = false);
	/** Fills cppNotice data from database.
	@param o The CppFile object.
	@param filter Condition allowing to filter data.
	@param nowait Asynchonous call.
	*/
	 void fillManyCppNotices(boost::shared_ptr< _CppFile<EncodingT> > o, typename EncodingT::string_t const&  filter, bool nowait = false);
	/** Returns whether CppFile data are altered from database.
	@param o The CppFile object.
	@return True if data CppFile have been altered.
	*/
	 bool isModifiedCppFile(boost::shared_ptr< _CppFile<EncodingT> > o) const;
	/** Updates CppFile data to database.
	@param o The CppFile object.
	*/
	 void updateCppFile(boost::shared_ptr< _CppFile<EncodingT> > o);
	/** Inserts CppFile data to database.
	@param o The CppFile object.
	*/
	 void insertCppFile(boost::shared_ptr< _CppFile<EncodingT> > o);
	/** Deletes CppFile data to database.
	@param o The CppFile object.
	*/
	 void deleteCppFile(boost::shared_ptr< _CppFile<EncodingT> > o);
	/** Add signal for CppFile insertion.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addInsertSignal(typename signal_t::slot_function_type subscriber);
	/** Add signal for CppFile update.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addUpdateSignal(typename signal_t::slot_function_type subscriber);
	/** Add signal for CppFile deletion.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addDeleteSignal(typename signal_t::slot_function_type subscriber);
	/** Add signal for CppFile transaction result.
	@param subscriber The observer
	@return The connection
	*/
	 connection_t addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber);
	/** Remove signal for CppFile insertion.
	@param connection The connection
	*/
	 void removeInsertSignal(connection_t connection);
	/** Remove signal for CppFile update.
	@param connection The connection
	*/
	 void removeUpdateSignal(connection_t connection);
	/** Remove signal for CppFile deletion.
	@param connection The connection
	*/
	 void removeDeleteSignal(connection_t connection);
	/** Remove signal for CppFile transaction result.
	@param connection The connection
	*/
	 void removeTransactionSignal(connection_t connection);
};

typedef _CppFileAccess<ucs> UniCppFileAccess;
typedef _CppFileAccess<ansi> CppFileAccess;

NAMESPACE_END

#undef C
#undef A

#if !defined(HAS_CPPBASE_DLL) || defined(BUILD_CPPBASE_DLL)
#include "cppFileAccess_impl.hpp"
#endif // !defined(HAS_CPPBASE_DLL) || defined(BUILD_CPPBASE_DLL)

#endif
