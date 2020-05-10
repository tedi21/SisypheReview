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
_DebugValueInfoAccess<EncodingT>* _DebugValueInfoAccess<EncodingT>::m_instance = NULL;

template<class EncodingT>
_DebugValueInfoAccess<EncodingT>* 
_DebugValueInfoAccess<EncodingT>::getInstance()  
{
	if (m_instance == NULL) {
		m_instance = new _DebugValueInfoAccess<EncodingT>();
	}
	return m_instance;
}

template<class EncodingT>
_DebugValueInfoAccess<EncodingT>::_DebugValueInfoAccess()
: m_transactionOwner(false) 
{
	m_logger = &Category::getInstance(LOGNAME);
	m_logger->debugStream() << "constructor DebugValueInfoAccess " << m_transactionOwner;
}

template<class EncodingT>
_DebugValueInfoAccess<EncodingT>::~_DebugValueInfoAccess()
{
	cancelSelection();
	m_logger = NULL;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _DebugValueInfo<EncodingT> > >
_DebugValueInfoAccess<EncodingT>::getManyDebugValueInfos(typename EncodingT::string_t const&  filter) const 
{
	boost::shared_ptr< _DebugValueInfo<EncodingT> > value;
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _DebugValueInfo<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("textValue"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,UCS("debugValueInfo")), filter) );
	while( statement.executeStep() ) {
		long long identifier;
		typename EncodingT::string_t textValue;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, textValue )) {
			value.reset(new _DebugValueInfo<EncodingT>(
				identifier,
				textValue));
			tab.push_back(value);
		}
	}
	return tab;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _DebugValueInfo<EncodingT> > >
_DebugValueInfoAccess<EncodingT>::getAllDebugValueInfos() const 
{
	return getManyDebugValueInfos(EncodingT::EMPTY);
}

template<class EncodingT>
boost::shared_ptr< _DebugValueInfo<EncodingT> >
_DebugValueInfoAccess<EncodingT>::getOneDebugValueInfo(long long identifier) const 
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _DebugValueInfo<EncodingT> > > result = getManyDebugValueInfos(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
std::vector< boost::shared_ptr< _DebugValueInfo<EncodingT> > >
_DebugValueInfoAccess<EncodingT>::selectManyDebugValueInfos(typename EncodingT::string_t const&  filter, bool nowait, bool addition)  
{
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _DebugValueInfo<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("textValue"));
	if (!addition || !connection->isTransactionInProgress()) {
		cancelSelection();
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
	}
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,UCS("debugValueInfo")), filter, nowait) );
	while( statement.executeStep() ) {
		long long identifier;
		typename EncodingT::string_t textValue;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, textValue )) {
			tab.push_back(boost::shared_ptr< _DebugValueInfo<EncodingT> >(new _DebugValueInfo<EncodingT>(
				identifier,
				textValue)));
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
boost::shared_ptr< _DebugValueInfo<EncodingT> >
_DebugValueInfoAccess<EncodingT>::selectOneDebugValueInfo(long long identifier, bool nowait, bool addition)  
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _DebugValueInfo<EncodingT> > > result = selectManyDebugValueInfos(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait, addition);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
bool
_DebugValueInfoAccess<EncodingT>::isSelectedDebugValueInfo(boost::shared_ptr< _DebugValueInfo<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	typename _DebugValueInfo<EncodingT>::DebugValueInfoIDEquality debugValueInfoIdEquality(*o);
	return (!m_backup.empty() && (std::find_if(m_backup.begin(), m_backup.end(), debugValueInfoIdEquality)!=m_backup.end()));
}

template<class EncodingT>
void
_DebugValueInfoAccess<EncodingT>::cancelSelection()  
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
void
_DebugValueInfoAccess<EncodingT>::fillDebugVariableInfo(boost::shared_ptr< _DebugValueInfo<EncodingT> > o)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_DataStatement<EncodingT> statement;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	_DebugVariableInfoAccess<EncodingT>* debugVariableInfoAccess = _DebugVariableInfoAccess<EncodingT>::getInstance();
	if (!debugVariableInfoAccess) {
		m_logger->errorStream() << "DebugVariableInfoAccess class is not initialized.";
		throw NullPointerException("DebugVariableInfoAccess class is not initialized.");
	}
	long long id;
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,UCS("idDebugVariable")), std::vector<typename EncodingT::string_t>(1,UCS("debugValueInfo")), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
	if( statement.executeStep() && statement.getInt64( 0, id ) && id != 0 ) {
		typename _DebugValueInfo<EncodingT>::DebugValueInfoIDEquality debugValueInfoIdEquality(o->getIdentifier());
		boost::shared_ptr< _DebugVariableInfo<EncodingT> > val = debugVariableInfoAccess->getOneDebugVariableInfo(id);
		typename std::list< boost::shared_ptr<_DebugValueInfo<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), debugValueInfoIdEquality);
		if (save != m_backup.end()) {
			(*save)->setDebugVariableInfo(val);
		}
		o->setDebugVariableInfo(val);
	}
	else {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
}

template<class EncodingT>
void
_DebugValueInfoAccess<EncodingT>::fillDebugStubInfo(boost::shared_ptr< _DebugValueInfo<EncodingT> > o)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_DataStatement<EncodingT> statement;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	_DebugStubInfoAccess<EncodingT>* debugStubInfoAccess = _DebugStubInfoAccess<EncodingT>::getInstance();
	if (!debugStubInfoAccess) {
		m_logger->errorStream() << "DebugStubInfoAccess class is not initialized.";
		throw NullPointerException("DebugStubInfoAccess class is not initialized.");
	}
	long long id;
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,UCS("idDebugStub")), std::vector<typename EncodingT::string_t>(1,UCS("debugValueInfo")), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
	if( statement.executeStep() && statement.getInt64( 0, id ) && id != 0 ) {
		typename _DebugValueInfo<EncodingT>::DebugValueInfoIDEquality debugValueInfoIdEquality(o->getIdentifier());
		boost::shared_ptr< _DebugStubInfo<EncodingT> > val = debugStubInfoAccess->getOneDebugStubInfo(id);
		typename std::list< boost::shared_ptr<_DebugValueInfo<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), debugValueInfoIdEquality);
		if (save != m_backup.end()) {
			(*save)->setDebugStubInfo(val);
		}
		o->setDebugStubInfo(val);
	}
	else {
		m_logger->debugStream() << "identifier not found.";
	}
}

template<class EncodingT>
bool
_DebugValueInfoAccess<EncodingT>::isModifiedDebugValueInfo(boost::shared_ptr< _DebugValueInfo<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	typename _DebugValueInfo<EncodingT>::DebugValueInfoIDEquality debugValueInfoIdEquality(*o);
	typename std::list< boost::shared_ptr< _DebugValueInfo<EncodingT> > >::const_iterator save = std::find_if(m_backup.begin(), m_backup.end(), debugValueInfoIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getTextValue() != o->getTextValue());
	bUpdate = bUpdate || (!(*save)->isNullDebugVariableInfo() && !o->isNullDebugVariableInfo() && !typename _DebugVariableInfo<EncodingT>::DebugVariableInfoIDEquality(*(*save)->getDebugVariableInfo())(o->getDebugVariableInfo()))
		|| ((*save)->isNullDebugVariableInfo() && !o->isNullDebugVariableInfo()) 
		|| (!(*save)->isNullDebugVariableInfo() && o->isNullDebugVariableInfo());
	bUpdate = bUpdate || (!(*save)->isNullDebugStubInfo() && !o->isNullDebugStubInfo() && !typename _DebugStubInfo<EncodingT>::DebugStubInfoIDEquality(*(*save)->getDebugStubInfo())(o->getDebugStubInfo()))
		|| ((*save)->isNullDebugStubInfo() && !o->isNullDebugStubInfo()) 
		|| (!(*save)->isNullDebugStubInfo() && o->isNullDebugStubInfo());
	return bUpdate;
}

template<class EncodingT>
void
_DebugValueInfoAccess<EncodingT>::updateDebugValueInfo(boost::shared_ptr< _DebugValueInfo<EncodingT> > o)  
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
	typename _DebugValueInfo<EncodingT>::DebugValueInfoIDEquality debugValueInfoIdEquality(*o);
	typename std::list< boost::shared_ptr< _DebugValueInfo<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), debugValueInfoIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	try {
		if ( (*save)->getTextValue() != o->getTextValue() ) {
			values.addText( o->getTextValue() );
			fields.push_back( UCS("textValue") );
		}
		if ( !o->isNullDebugVariableInfo() && typename _DebugVariableInfo<EncodingT>::DebugVariableInfoIDEquality(-1)(o->getDebugVariableInfo()) ) {
			m_logger->errorStream() << "idDebugVariable : Identifier is null.";
			throw InvalidQueryException("idDebugVariable : Identifier is null.");
		}
		else if ( !o->isNullDebugVariableInfo() && !typename _DebugVariableInfo<EncodingT>::DebugVariableInfoIDEquality(*(o->getDebugVariableInfo()))((*save)->getDebugVariableInfo()) ) {
			values.addInt64( o->getDebugVariableInfo()->getIdentifier() );
			fields.push_back( UCS("idDebugVariable") );
		}
		else if ( o->isNullDebugVariableInfo() && !(*save)->isNullDebugVariableInfo() ) {
			m_logger->errorStream() << "idDebugVariable : null reference is forbidden.";
			throw InvalidQueryException("idDebugVariable : null reference is forbidden.");
		}
		if ( !o->isNullDebugStubInfo() && typename _DebugStubInfo<EncodingT>::DebugStubInfoIDEquality(-1)(o->getDebugStubInfo()) ) {
			m_logger->errorStream() << "idDebugStub : Identifier is null.";
			throw InvalidQueryException("idDebugStub : Identifier is null.");
		}
		else if ( !o->isNullDebugStubInfo() && !typename _DebugStubInfo<EncodingT>::DebugStubInfoIDEquality(*(o->getDebugStubInfo()))((*save)->getDebugStubInfo()) ) {
			values.addInt64( o->getDebugStubInfo()->getIdentifier() );
			fields.push_back( UCS("idDebugStub") );
		}
		else if ( o->isNullDebugStubInfo() && !(*save)->isNullDebugStubInfo() ) {
			values.addNull();
			fields.push_back( UCS("idDebugStub") );
		}
		if (!fields.empty()) {
			statement.swap( connection->update(UCS("debugValueInfo"), fields, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, UCS("debugValueInfo"), o);
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
_DebugValueInfoAccess<EncodingT>::insertDebugValueInfo(boost::shared_ptr< _DebugValueInfo<EncodingT> > o)  
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
		int id = connection->selectMaxID(UCS("identifier"), UCS("debugValueInfo"))+1;
		values.addInt( id );
		fields.push_back( UCS("identifier") );
		values.addText( o->getTextValue() );
		fields.push_back( UCS("textValue") );
		if ( !o->isNullDebugVariableInfo() && typename _DebugVariableInfo<EncodingT>::DebugVariableInfoIDEquality(-1)(o->getDebugVariableInfo()) ) {
			m_logger->errorStream() << "idDebugVariable : Identifier is null.";
			throw InvalidQueryException("idDebugVariable : Identifier is null.");
		}
		else if ( !o->isNullDebugVariableInfo() ) {
			values.addInt64( o->getDebugVariableInfo()->getIdentifier() );
			fields.push_back( UCS("idDebugVariable") );
		}
		else {
			m_logger->errorStream() << "idDebugVariable : null reference is forbidden.";
			throw InvalidQueryException("idDebugVariable : null reference is forbidden.");
		}
		if ( !o->isNullDebugStubInfo() && typename _DebugStubInfo<EncodingT>::DebugStubInfoIDEquality(-1)(o->getDebugStubInfo()) ) {
			m_logger->errorStream() << "idDebugStub : Identifier is null.";
			throw InvalidQueryException("idDebugStub : Identifier is null.");
		}
		else if ( !o->isNullDebugStubInfo() ) {
			values.addInt64( o->getDebugStubInfo()->getIdentifier() );
			fields.push_back( UCS("idDebugStub") );
		}
		else {
			values.addNull();
			fields.push_back( UCS("idDebugStub") );
		}
		statement.swap( connection->insert(UCS("debugValueInfo"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		o->setIdentifier(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, UCS("debugValueInfo"), o);
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
_DebugValueInfoAccess<EncodingT>::deleteDebugValueInfo(boost::shared_ptr< _DebugValueInfo<EncodingT> > o)  
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
	typename _DebugValueInfo<EncodingT>::DebugValueInfoIDEquality DebugValueInfoIdEquality(*o);
	typename std::list< boost::shared_ptr< _DebugValueInfo<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), DebugValueInfoIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before deletion.";
		throw UnSelectedObjectException("You must select object before deletion.");
	}
	try {
		statement.swap( connection->deleteFrom(UCS("debugValueInfo"), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, UCS("debugValueInfo"), o);
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
typename _DebugValueInfoAccess<EncodingT>::connection_t
_DebugValueInfoAccess<EncodingT>::addInsertSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_insertSignal.connect(subscriber);
}

template<class EncodingT>
typename _DebugValueInfoAccess<EncodingT>::connection_t
_DebugValueInfoAccess<EncodingT>::addUpdateSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_updateSignal.connect(subscriber);
}

template<class EncodingT>
typename _DebugValueInfoAccess<EncodingT>::connection_t
_DebugValueInfoAccess<EncodingT>::addDeleteSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_deleteSignal.connect(subscriber);
}

template<class EncodingT>
typename _DebugValueInfoAccess<EncodingT>::connection_t
_DebugValueInfoAccess<EncodingT>::addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber)  
{
	return m_transactionSignal.connect(subscriber);
}

template<class EncodingT>
void
_DebugValueInfoAccess<EncodingT>::removeInsertSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_DebugValueInfoAccess<EncodingT>::removeUpdateSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_DebugValueInfoAccess<EncodingT>::removeDeleteSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_DebugValueInfoAccess<EncodingT>::removeTransactionSignal(connection_t connection)  
{
	connection.disconnect();
}


NAMESPACE_END

#undef C
#undef A

