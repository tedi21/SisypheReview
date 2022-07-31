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
_DebugErrorInfoAccess<EncodingT>* _DebugErrorInfoAccess<EncodingT>::m_instance = NULL;

template<class EncodingT>
_DebugErrorInfoAccess<EncodingT>* 
_DebugErrorInfoAccess<EncodingT>::getInstance()  
{
	if (m_instance == NULL) {
		m_instance = new _DebugErrorInfoAccess<EncodingT>();
	}
	return m_instance;
}

template<class EncodingT>
_DebugErrorInfoAccess<EncodingT>::_DebugErrorInfoAccess()
: m_transactionOwner(false) 
{
	m_logger = &Category::getInstance(LOGNAME);
	m_logger->debugStream() << "constructor DebugErrorInfoAccess " << m_transactionOwner;
}

template<class EncodingT>
_DebugErrorInfoAccess<EncodingT>::~_DebugErrorInfoAccess()
{
	cancelSelection();
	m_logger = NULL;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _DebugErrorInfo<EncodingT> > >
_DebugErrorInfoAccess<EncodingT>::getManyDebugErrorInfos(typename EncodingT::string_t const&  filter) const 
{
	boost::shared_ptr< _DebugErrorInfo<EncodingT> > value;
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _DebugErrorInfo<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("callStack"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,UCS("debugErrorInfo")), filter) );
	while( statement.executeStep() ) {
		long long identifier;
		typename EncodingT::string_t callStack;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, callStack )) {
			value.reset(new _DebugErrorInfo<EncodingT>(
				identifier,
				callStack));
			tab.push_back(value);
		}
	}
	return tab;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _DebugErrorInfo<EncodingT> > >
_DebugErrorInfoAccess<EncodingT>::getAllDebugErrorInfos() const 
{
	return getManyDebugErrorInfos(EncodingT::EMPTY);
}

template<class EncodingT>
boost::shared_ptr< _DebugErrorInfo<EncodingT> >
_DebugErrorInfoAccess<EncodingT>::getOneDebugErrorInfo(long long identifier) const 
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _DebugErrorInfo<EncodingT> > > result = getManyDebugErrorInfos(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
std::vector< boost::shared_ptr< _DebugErrorInfo<EncodingT> > >
_DebugErrorInfoAccess<EncodingT>::selectManyDebugErrorInfos(typename EncodingT::string_t const&  filter, bool nowait, bool addition)  
{
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _DebugErrorInfo<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("callStack"));
	if (!addition || !connection->isTransactionInProgress()) {
		cancelSelection();
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
	}
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,UCS("debugErrorInfo")), filter, nowait) );
	while( statement.executeStep() ) {
		long long identifier;
		typename EncodingT::string_t callStack;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, callStack )) {
			tab.push_back(boost::shared_ptr< _DebugErrorInfo<EncodingT> >(new _DebugErrorInfo<EncodingT>(
				identifier,
				callStack)));
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
		m_backup.insert(tab.begin(), tab.end());
	}
	return copy_ptr(tab);
}

template<class EncodingT>
boost::shared_ptr< _DebugErrorInfo<EncodingT> >
_DebugErrorInfoAccess<EncodingT>::selectOneDebugErrorInfo(long long identifier, bool nowait, bool addition)  
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _DebugErrorInfo<EncodingT> > > result = selectManyDebugErrorInfos(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait, addition);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
bool
_DebugErrorInfoAccess<EncodingT>::isSelectedDebugErrorInfo(boost::shared_ptr< _DebugErrorInfo<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	return (!m_backup.empty() && (m_backup.find(o) != m_backup.end()));
}

template<class EncodingT>
void
_DebugErrorInfoAccess<EncodingT>::cancelSelection()  
{
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	if (!m_backup.empty()) {
		if (connection->isTransactionInProgress() && m_transactionOwner) {
			connection->rollback();
			m_transactionOwner = false;
			m_transactionSignal(OPERATION_ACCESS_ROLLBACK);
		}
		m_backup.clear();
	}
}

template<class EncodingT>
bool
_DebugErrorInfoAccess<EncodingT>::isModifiedDebugErrorInfo(boost::shared_ptr< _DebugErrorInfo<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	typename backup_t::const_iterator save = m_backup.find(o);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getCallStack() != o->getCallStack());
	return bUpdate;
}

template<class EncodingT>
void
_DebugErrorInfoAccess<EncodingT>::updateDebugErrorInfo(boost::shared_ptr< _DebugErrorInfo<EncodingT> > o)  
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
	typename backup_t::iterator save = m_backup.find(o);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	try {
		if ( (*save)->getCallStack() != o->getCallStack() ) {
			values.addText( o->getCallStack() );
			fields.push_back( UCS("callStack") );
		}
		if (!fields.empty()) {
			statement.swap( connection->update(UCS("debugErrorInfo"), fields, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, UCS("debugErrorInfo"), o);
		}
		if (connection->isTransactionInProgress() && m_transactionOwner) {
			connection->commit();
			m_transactionOwner = false;
			cancelSelection();
			m_transactionSignal(OPERATION_ACCESS_COMMIT);
		}
		} catch (...) {
		if (m_transactionOwner) {
			cancelSelection();
		}
		throw;
	}
}

template<class EncodingT>
void
_DebugErrorInfoAccess<EncodingT>::insertDebugErrorInfo(boost::shared_ptr< _DebugErrorInfo<EncodingT> > o)  
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
	try {
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
		int id = connection->selectMaxID(UCS("identifier"), UCS("debugErrorInfo"))+1;
		values.addInt( id );
		fields.push_back( UCS("identifier") );
		values.addText( o->getCallStack() );
		fields.push_back( UCS("callStack") );
		statement.swap( connection->insert(UCS("debugErrorInfo"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		o->setIdentifier(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, UCS("debugErrorInfo"), o);
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
_DebugErrorInfoAccess<EncodingT>::deleteDebugErrorInfo(boost::shared_ptr< _DebugErrorInfo<EncodingT> > o)  
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
	typename backup_t::iterator save = m_backup.find(o);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before deletion.";
		throw UnSelectedObjectException("You must select object before deletion.");
	}
	try {
		statement.swap( connection->deleteFrom(UCS("debugErrorInfo"), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, UCS("debugErrorInfo"), o);
		if (connection->isTransactionInProgress() && m_transactionOwner) {
			connection->commit();
			m_transactionOwner = false;
			cancelSelection();
			m_transactionSignal(OPERATION_ACCESS_COMMIT);
		}
			o->setIdentifier(-1);
	} catch (...) {
		if (m_transactionOwner) {
			cancelSelection();
		}
		throw;
	}
}

template<class EncodingT>
typename _DebugErrorInfoAccess<EncodingT>::connection_t
_DebugErrorInfoAccess<EncodingT>::addInsertSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_insertSignal.connect(subscriber);
}

template<class EncodingT>
typename _DebugErrorInfoAccess<EncodingT>::connection_t
_DebugErrorInfoAccess<EncodingT>::addUpdateSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_updateSignal.connect(subscriber);
}

template<class EncodingT>
typename _DebugErrorInfoAccess<EncodingT>::connection_t
_DebugErrorInfoAccess<EncodingT>::addDeleteSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_deleteSignal.connect(subscriber);
}

template<class EncodingT>
typename _DebugErrorInfoAccess<EncodingT>::connection_t
_DebugErrorInfoAccess<EncodingT>::addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber)  
{
	return m_transactionSignal.connect(subscriber);
}

template<class EncodingT>
void
_DebugErrorInfoAccess<EncodingT>::removeInsertSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_DebugErrorInfoAccess<EncodingT>::removeUpdateSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_DebugErrorInfoAccess<EncodingT>::removeDeleteSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_DebugErrorInfoAccess<EncodingT>::removeTransactionSignal(connection_t connection)  
{
	connection.disconnect();
}


NAMESPACE_END

#undef C
#undef A

