#include "dataconnection.hpp"
#include "dataparameters.hpp"
#include "datastatement.hpp"
#include "NullPointerException.hpp"
#include "NoSqlRowException.hpp"
#include "UnIdentifiedObjectException.hpp"
#include "InvalidQueryException.hpp"
#include "UnSelectedObjectException.hpp"
#include <algorithm> 
#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(data_access)

using namespace boost;
using namespace entity;

template<class EncodingT>
_CppFileTypeAccess<EncodingT>* _CppFileTypeAccess<EncodingT>::m_instance = NULL;

template<class EncodingT>
_CppFileTypeAccess<EncodingT>* 
_CppFileTypeAccess<EncodingT>::getInstance()  
{
	if (m_instance == NULL) {
		m_instance = new _CppFileTypeAccess<EncodingT>();
	}
	return m_instance;
}

template<class EncodingT>
_CppFileTypeAccess<EncodingT>::_CppFileTypeAccess()
: m_transactionOwner(false) 
{
	m_logger = &Category::getInstance(LOGNAME);
	m_logger->debugStream() << "constructor CppFileTypeAccess " << m_transactionOwner;
}

template<class EncodingT>
_CppFileTypeAccess<EncodingT>::~_CppFileTypeAccess()
{
	cancelSelection();
	m_logger = NULL;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppFileType<EncodingT> > >
_CppFileTypeAccess<EncodingT>::getManyCppFileTypes(typename EncodingT::string_t const&  filter) const 
{
	boost::shared_ptr< _CppFileType<EncodingT> > value;
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _CppFileType<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("string"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,UCS("cppFileType")), filter) );
	while( statement.executeStep() ) {
		long long identifier;
		typename EncodingT::string_t string;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, string )) {
			value.reset(new _CppFileType<EncodingT>(
				identifier,
				string));
			tab.push_back(value);
		}
	}
	return tab;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppFileType<EncodingT> > >
_CppFileTypeAccess<EncodingT>::getAllCppFileTypes() const 
{
	return getManyCppFileTypes(EncodingT::EMPTY);
}

template<class EncodingT>
boost::shared_ptr< _CppFileType<EncodingT> >
_CppFileTypeAccess<EncodingT>::getOneCppFileType(long long identifier) const 
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _CppFileType<EncodingT> > > result = getManyCppFileTypes(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppFileType<EncodingT> > >
_CppFileTypeAccess<EncodingT>::selectManyCppFileTypes(typename EncodingT::string_t const&  filter, bool nowait, bool addition)  
{
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _CppFileType<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("string"));
	if (!addition || !connection->isTransactionInProgress()) {
		cancelSelection();
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
	}
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,UCS("cppFileType")), filter, nowait) );
	while( statement.executeStep() ) {
		long long identifier;
		typename EncodingT::string_t string;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, string )) {
			tab.push_back(boost::shared_ptr< _CppFileType<EncodingT> >(new _CppFileType<EncodingT>(
				identifier,
				string)));
		}
	}
	if (tab.empty()) {
		if (connection->isTransactionInProgress() && m_transactionOwner) {
			connection->rollback();
			m_transactionOwner = false;
			m_transactionSignal(OPERATION_ACCESS_ROLLBACK);
		}
	}
	else {
		m_backup.insert(m_backup.end(), tab.begin(), tab.end());
	}
	return copy_ptr(tab);
}

template<class EncodingT>
boost::shared_ptr< _CppFileType<EncodingT> >
_CppFileTypeAccess<EncodingT>::selectOneCppFileType(long long identifier, bool nowait, bool addition)  
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _CppFileType<EncodingT> > > result = selectManyCppFileTypes(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait, addition);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
bool
_CppFileTypeAccess<EncodingT>::isSelectedCppFileType(boost::shared_ptr< _CppFileType<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	typename _CppFileType<EncodingT>::CppFileTypeIDEquality cppFileTypeIdEquality(*o);
	return (!m_backup.empty() && (std::find_if(m_backup.begin(), m_backup.end(), cppFileTypeIdEquality)!=m_backup.end()));
}

template<class EncodingT>
void
_CppFileTypeAccess<EncodingT>::cancelSelection()  
{
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	_CppFileAccess<EncodingT>* cppFileAccess = _CppFileAccess<EncodingT>::getInstance();
	if (!cppFileAccess) {
		m_logger->errorStream() << "CppFileAccess class is not initialized.";
		throw NullPointerException("CppFileAccess class is not initialized.");
	}
	if (!m_backup.empty()) {
		if (connection->isTransactionInProgress() && m_transactionOwner) {
			connection->rollback();
			m_transactionOwner = false;
			m_transactionSignal(OPERATION_ACCESS_ROLLBACK);
		}
		m_backup.clear();
		cppFileAccess->cancelSelection();
	}
}

template<class EncodingT>
void
_CppFileTypeAccess<EncodingT>::fillAllCppFiles(boost::shared_ptr< _CppFileType<EncodingT> > o, bool nowait)  
{
	fillManyCppFiles(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_CppFileTypeAccess<EncodingT>::fillOneCppFile(boost::shared_ptr< _CppFileType<EncodingT> > o, long long identifier, bool nowait)  
{
	fillManyCppFiles(o, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait);
}

template<class EncodingT>
void
_CppFileTypeAccess<EncodingT>::fillManyCppFiles(boost::shared_ptr< _CppFileType<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_CppFileAccess<EncodingT>* cppFileAccess = _CppFileAccess<EncodingT>::getInstance();
	if (!cppFileAccess) {
		m_logger->errorStream() << "CppFileAccess class is not initialized.";
		throw NullPointerException("CppFileAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _CppFile<EncodingT> > > tab;
	typename EncodingT::string_t cppFileFilter = UCS("idType = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		cppFileFilter += UCS(" AND ") + filter;
	}
	typename _CppFileType<EncodingT>::CppFileTypeIDEquality cppFileTypeIdEquality(o->getIdentifier());
	typename std::list< boost::shared_ptr< _CppFileType<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFileTypeIdEquality);
	if (save != m_backup.end())
	{
		tab = cppFileAccess->selectManyCppFiles(cppFileFilter, nowait, true);
		(*save)->clearCppFiles();
		(*save)->insertCppFile((*save)->getCppFilesEnd(), tab.begin(), tab.end());
	}
	else
	{
		tab = cppFileAccess->getManyCppFiles(cppFileFilter);
	}
	o->clearCppFiles();
	o->insertCppFile(o->getCppFilesEnd(), tab.begin(), tab.end());
}

template<class EncodingT>
bool
_CppFileTypeAccess<EncodingT>::isModifiedCppFileType(boost::shared_ptr< _CppFileType<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_CppFileAccess<EncodingT>* cppFileAccess = _CppFileAccess<EncodingT>::getInstance();
	if (!cppFileAccess) {
		m_logger->errorStream() << "CppFileAccess class is not initialized.";
		throw NullPointerException("CppFileAccess class is not initialized.");
	}
	typename _CppFileType<EncodingT>::CppFileTypeIDEquality cppFileTypeIdEquality(*o);
	typename std::list< boost::shared_ptr< _CppFileType<EncodingT> > >::const_iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFileTypeIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getString() != o->getString());
	typename _CppFileType<EncodingT>::CppFileIterator cppFile;
	for ( cppFile=o->getCppFilesBeginning(); cppFile!=o->getCppFilesEnd(); ++cppFile ) {
		if (!(*cppFile)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(*(*cppFile));
		bUpdate = bUpdate || (std::find_if((*save)->getCppFilesBeginning(), (*save)->getCppFilesEnd(), cppFileIdEquality) == (*save)->getCppFilesEnd())
			|| (cppFileAccess->isModifiedCppFile(*cppFile));
	}
	for ( cppFile=(*save)->getCppFilesBeginning(); cppFile<(*save)->getCppFilesEnd(); ++cppFile ) {
		if (!(*cppFile)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(*(*cppFile));
		bUpdate = bUpdate || (std::find_if(o->getCppFilesBeginning(), o->getCppFilesEnd(), cppFileIdEquality) == o->getCppFilesEnd());
	}
	return bUpdate;
}

template<class EncodingT>
void
_CppFileTypeAccess<EncodingT>::updateCppFileType(boost::shared_ptr< _CppFileType<EncodingT> > o)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	_DataParameters<EncodingT> values;
	_DataStatement<EncodingT> statement;
	std::vector<typename EncodingT::string_t> fields;
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	_CppFileAccess<EncodingT>* cppFileAccess = _CppFileAccess<EncodingT>::getInstance();
	if (!cppFileAccess) {
		m_logger->errorStream() << "CppFileAccess class is not initialized.";
		throw NullPointerException("CppFileAccess class is not initialized.");
	}
	typename _CppFileType<EncodingT>::CppFileTypeIDEquality cppFileTypeIdEquality(*o);
	typename std::list< boost::shared_ptr< _CppFileType<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFileTypeIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	try {
		if ( (*save)->getString() != o->getString() ) {
			values.addText( o->getString() );
			fields.push_back( UCS("string") );
		}
		std::vector< boost::shared_ptr< _CppFile<EncodingT> > > listOfCppFileToAdd;
		std::vector< boost::shared_ptr< _CppFile<EncodingT> > > listOfCppFileToUpdate;
		typename _CppFileType<EncodingT>::CppFileIterator cppFile;
		for ( cppFile=o->getCppFilesBeginning(); cppFile!=o->getCppFilesEnd(); ++cppFile ) {
			if (!(*cppFile)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*cppFile)->setCppFileType(o);
			typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(*(*cppFile));
			if ( std::find_if((*save)->getCppFilesBeginning(), (*save)->getCppFilesEnd(), cppFileIdEquality) == (*save)->getCppFilesEnd()) {
				listOfCppFileToAdd.push_back(*cppFile);
			}
			else {
				if (cppFileAccess->isModifiedCppFile(*cppFile))
					listOfCppFileToUpdate.push_back(*cppFile);
			}
		}
		std::vector< boost::shared_ptr< _CppFile<EncodingT> > > listOfCppFileToRemove;
		for ( cppFile=(*save)->getCppFilesBeginning(); cppFile<(*save)->getCppFilesEnd(); ++cppFile ) {
			if (!(*cppFile)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(*(*cppFile));
			if ( std::find_if(o->getCppFilesBeginning(), o->getCppFilesEnd(), cppFileIdEquality) == o->getCppFilesEnd()) {
				listOfCppFileToRemove.push_back(*cppFile);
			}
		}
		if (!fields.empty()) {
			statement.swap( connection->update(UCS("cppFileType"), fields, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, UCS("cppFileType"), o);
		}
		for ( cppFile=listOfCppFileToAdd.begin(); cppFile!=listOfCppFileToAdd.end() ; ++cppFile ) {
			cppFileAccess->insertCppFile(*cppFile);
		}
		for ( cppFile=listOfCppFileToUpdate.begin(); cppFile!=listOfCppFileToUpdate.end() ; ++cppFile ) {
			cppFileAccess->updateCppFile(*cppFile);
		}
		for ( cppFile=listOfCppFileToRemove.begin(); cppFile!=listOfCppFileToRemove.end() ; ++cppFile ) {
			cppFileAccess->deleteCppFile(*cppFile);
		}
		if (connection->isTransactionInProgress() && m_transactionOwner) {
			connection->commit();
			m_transactionOwner = false;
			m_transactionSignal(OPERATION_ACCESS_COMMIT);
		}
		m_backup.erase(save);
	} catch (...) {
		if (m_transactionOwner) {
			cancelSelection();
		}
		throw;
	}
}

template<class EncodingT>
void
_CppFileTypeAccess<EncodingT>::insertCppFileType(boost::shared_ptr< _CppFileType<EncodingT> > o)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	_DataParameters<EncodingT> values;
	_DataStatement<EncodingT> statement;
	std::vector<typename EncodingT::string_t> fields;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	_CppFileAccess<EncodingT>* cppFileAccess = _CppFileAccess<EncodingT>::getInstance();
	if (!cppFileAccess) {
		m_logger->errorStream() << "CppFileAccess class is not initialized.";
		throw NullPointerException("CppFileAccess class is not initialized.");
	}
	try {
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
		int id = connection->selectMaxID(UCS("identifier"), UCS("cppFileType"))+1;
		values.addInt( id );
		fields.push_back( UCS("identifier") );
		values.addText( o->getString() );
		fields.push_back( UCS("string") );
		statement.swap( connection->insert(UCS("cppFileType"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		o->setIdentifier(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, UCS("cppFileType"), o);
		typename _CppFileType<EncodingT>::CppFileIterator cppFile;
		for ( cppFile=o->getCppFilesBeginning(); cppFile!=o->getCppFilesEnd(); ++cppFile ) {
			(*cppFile)->setCppFileType(o);
			cppFileAccess->insertCppFile(*cppFile);
		}
		if (connection->isTransactionInProgress() && m_transactionOwner) {
			connection->commit();
			m_transactionOwner = false;
			m_transactionSignal(OPERATION_ACCESS_COMMIT);
		}
	} catch (...) {
		if (connection->isTransactionInProgress() && m_transactionOwner) {
			connection->rollback();
			m_transactionOwner = false;
			m_transactionSignal(OPERATION_ACCESS_ROLLBACK);
		}
		throw;
	}
}

template<class EncodingT>
void
_CppFileTypeAccess<EncodingT>::deleteCppFileType(boost::shared_ptr< _CppFileType<EncodingT> > o)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	_DataStatement<EncodingT> statement;
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	_CppFileAccess<EncodingT>* cppFileAccess = _CppFileAccess<EncodingT>::getInstance();
	if (!cppFileAccess) {
		m_logger->errorStream() << "CppFileAccess class is not initialized.";
		throw NullPointerException("CppFileAccess class is not initialized.");
	}
	typename _CppFileType<EncodingT>::CppFileTypeIDEquality CppFileTypeIdEquality(*o);
	typename std::list< boost::shared_ptr< _CppFileType<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), CppFileTypeIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before deletion.";
		throw UnSelectedObjectException("You must select object before deletion.");
	}
	try {
		typename _CppFileType<EncodingT>::CppFileIterator cppFile;
		fillAllCppFiles(o);
		for ( cppFile=o->getCppFilesBeginning(); cppFile!=o->getCppFilesEnd(); ++cppFile ) {
			cppFileAccess->deleteCppFile(*cppFile);
		}
		statement.swap( connection->deleteFrom(UCS("cppFileType"), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, UCS("cppFileType"), o);
		if (connection->isTransactionInProgress() && m_transactionOwner) {
			connection->commit();
			m_transactionOwner = false;
			m_transactionSignal(OPERATION_ACCESS_COMMIT);
		}
		m_backup.erase(save);
		o->setIdentifier(-1);
	} catch (...) {
		if (m_transactionOwner) {
			cancelSelection();
		}
		throw;
	}
}

template<class EncodingT>
typename _CppFileTypeAccess<EncodingT>::connection_t
_CppFileTypeAccess<EncodingT>::addInsertSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_insertSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppFileTypeAccess<EncodingT>::connection_t
_CppFileTypeAccess<EncodingT>::addUpdateSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_updateSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppFileTypeAccess<EncodingT>::connection_t
_CppFileTypeAccess<EncodingT>::addDeleteSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_deleteSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppFileTypeAccess<EncodingT>::connection_t
_CppFileTypeAccess<EncodingT>::addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber)  
{
	return m_transactionSignal.connect(subscriber);
}

template<class EncodingT>
void
_CppFileTypeAccess<EncodingT>::removeInsertSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppFileTypeAccess<EncodingT>::removeUpdateSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppFileTypeAccess<EncodingT>::removeDeleteSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppFileTypeAccess<EncodingT>::removeTransactionSignal(connection_t connection)  
{
	connection.disconnect();
}


NAMESPACE_END

#undef C
#undef A

