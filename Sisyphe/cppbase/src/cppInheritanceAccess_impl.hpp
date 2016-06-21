#include "DataConnection.hpp"
#include "DataParameters.hpp"
#include "DataStatement.hpp"
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
_CppInheritanceAccess<EncodingT>* _CppInheritanceAccess<EncodingT>::m_instance = NULL;

template<class EncodingT>
_CppInheritanceAccess<EncodingT>* 
_CppInheritanceAccess<EncodingT>::getInstance()  
{
	if (m_instance == NULL) {
		m_instance = new _CppInheritanceAccess<EncodingT>();
	}
	return m_instance;
}

template<class EncodingT>
_CppInheritanceAccess<EncodingT>::_CppInheritanceAccess()
: m_transactionOwner(false) 
{
	m_logger = &Category::getInstance(LOGNAME);
	m_logger->debugStream() << "constructor CppInheritanceAccess " << m_transactionOwner;
}

template<class EncodingT>
_CppInheritanceAccess<EncodingT>::~_CppInheritanceAccess()
{
	cancelSelection();
	m_logger = NULL;
}

template<class EncodingT>
std::vector< shared_ptr< _CppInheritance<EncodingT> > >
_CppInheritanceAccess<EncodingT>::getManyCppInheritances(typename EncodingT::string_t const&  filter) const 
{
	shared_ptr< _CppInheritance<EncodingT> > value;
	_DataStatement<EncodingT> statement;
	std::vector< shared_ptr< _CppInheritance<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(C("identifier"));
	columns.push_back(C("baseClassName"));
	columns.push_back(C("baseAccess"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,C("cppInheritance")), filter) );
	while( statement.executeStep() ) {
		int identifier;
		typename EncodingT::string_t baseClassName;
		typename EncodingT::string_t baseAccess;
		if (statement.getInt( 0, identifier ) &&
			statement.getText( 1, baseClassName ) &&
			statement.getText( 2, baseAccess )) {
			value.reset(new _CppInheritance<EncodingT>(
				identifier,
				baseClassName,
				baseAccess));
			tab.push_back(value);
		}
	}
	return tab;
}

template<class EncodingT>
std::vector< shared_ptr< _CppInheritance<EncodingT> > >
_CppInheritanceAccess<EncodingT>::getAllCppInheritances() const 
{
	return getManyCppInheritances(EncodingT::EMPTY);
}

template<class EncodingT>
shared_ptr< _CppInheritance<EncodingT> >
_CppInheritanceAccess<EncodingT>::getOneCppInheritance(int identifier) const 
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< shared_ptr< _CppInheritance<EncodingT> > > result = getManyCppInheritances(C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
std::vector< shared_ptr< _CppInheritance<EncodingT> > >
_CppInheritanceAccess<EncodingT>::selectManyCppInheritances(typename EncodingT::string_t const&  filter, bool nowait, bool addition)  
{
	_DataStatement<EncodingT> statement;
	std::vector< shared_ptr< _CppInheritance<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(C("identifier"));
	columns.push_back(C("baseClassName"));
	columns.push_back(C("baseAccess"));
	if (!addition || !connection->isTransactionInProgress()) {
		cancelSelection();
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
	}
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,C("cppInheritance")), filter, nowait) );
	while( statement.executeStep() ) {
		int identifier;
		typename EncodingT::string_t baseClassName;
		typename EncodingT::string_t baseAccess;
		if (statement.getInt( 0, identifier ) &&
			statement.getText( 1, baseClassName ) &&
			statement.getText( 2, baseAccess )) {
			tab.push_back(shared_ptr< _CppInheritance<EncodingT> >(new _CppInheritance<EncodingT>(
				identifier,
				baseClassName,
				baseAccess)));
		}
	}
	m_backup.insert(m_backup.end(), tab.begin(), tab.end());
	return copy_ptr(tab);
}

template<class EncodingT>
shared_ptr< _CppInheritance<EncodingT> >
_CppInheritanceAccess<EncodingT>::selectOneCppInheritance(int identifier, bool nowait, bool addition)  
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< shared_ptr< _CppInheritance<EncodingT> > > result = selectManyCppInheritances(C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait, addition);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
bool
_CppInheritanceAccess<EncodingT>::isSelectedCppInheritance(shared_ptr< _CppInheritance<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	typename _CppInheritance<EncodingT>::CppInheritanceIDEquality cppInheritanceIdEquality(*o);
	return (!m_backup.empty() && (std::find_if(m_backup.begin(), m_backup.end(), cppInheritanceIdEquality)!=m_backup.end()));
}

template<class EncodingT>
void
_CppInheritanceAccess<EncodingT>::cancelSelection()  
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
_CppInheritanceAccess<EncodingT>::fillDerived(shared_ptr< _CppInheritance<EncodingT> > o)  
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
	_CppClassAccess<EncodingT>* derivedAccess = _CppClassAccess<EncodingT>::getInstance();
	if (!derivedAccess) {
		m_logger->errorStream() << "CppClassAccess class is not initialized.";
		throw NullPointerException("CppClassAccess class is not initialized.");
	}
	int id;
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,C("idDerived")), std::vector<typename EncodingT::string_t>(1,C("cppInheritance")), C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
	if( statement.executeStep() && statement.getInt( 0, id ) && id != 0 ) {
		typename _CppInheritance<EncodingT>::CppInheritanceIDEquality cppInheritanceIdEquality(o->getIdentifier());
		shared_ptr< _CppClass<EncodingT> > val = derivedAccess->getOneCppClass(id);
		typename std::vector< shared_ptr<_CppInheritance<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppInheritanceIdEquality);
		if (save != m_backup.end()) {
			(*save)->setDerived(val);
		}
		o->setDerived(val);
	}
	else {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
}

template<class EncodingT>
bool
_CppInheritanceAccess<EncodingT>::isModifiedCppInheritance(shared_ptr< _CppInheritance<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	typename _CppInheritance<EncodingT>::CppInheritanceIDEquality cppInheritanceIdEquality(*o);
	typename std::vector< shared_ptr< _CppInheritance<EncodingT> > >::const_iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppInheritanceIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getBaseClassName() != o->getBaseClassName());
	bUpdate = bUpdate || ((*save)->getBaseAccess() != o->getBaseAccess());
	bUpdate = bUpdate || (!(*save)->isNullDerived() && !o->isNullDerived() && !typename _CppClass<EncodingT>::CppClassIDEquality(*(*save)->getDerived())(o->getDerived()))
		|| ((*save)->isNullDerived() && !o->isNullDerived()) 
		|| (!(*save)->isNullDerived() && o->isNullDerived());
	return bUpdate;
}

template<class EncodingT>
void
_CppInheritanceAccess<EncodingT>::updateCppInheritance(shared_ptr< _CppInheritance<EncodingT> > o)  
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
	typename _CppInheritance<EncodingT>::CppInheritanceIDEquality cppInheritanceIdEquality(*o);
	typename std::vector< shared_ptr< _CppInheritance<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppInheritanceIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	try {
		if ( (*save)->getBaseClassName() != o->getBaseClassName() ) {
			values.addText( o->getBaseClassName() );
			fields.push_back( C("baseClassName") );
		}
		if ( (*save)->getBaseAccess() != o->getBaseAccess() ) {
			values.addText( o->getBaseAccess() );
			fields.push_back( C("baseAccess") );
		}
		if ( !o->isNullDerived() && typename _CppClass<EncodingT>::CppClassIDEquality(-1)(o->getDerived()) ) {
			m_logger->errorStream() << "idDerived : Identifier is null.";
			throw InvalidQueryException("idDerived : Identifier is null.");
		}
		else if ( !o->isNullDerived() && !typename _CppClass<EncodingT>::CppClassIDEquality(*(o->getDerived()))((*save)->getDerived()) ) {
			values.addInt( o->getDerived()->getIdentifier() );
			fields.push_back( C("idDerived") );
		}
		else if ( o->isNullDerived() && !(*save)->isNullDerived() ) {
			m_logger->errorStream() << "idDerived : null reference is forbidden.";
			throw InvalidQueryException("idDerived : null reference is forbidden.");
		}
		if (!fields.empty()) {
			statement.swap( connection->update(C("cppInheritance"), fields, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, C("cppInheritance"), o);
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
_CppInheritanceAccess<EncodingT>::insertCppInheritance(shared_ptr< _CppInheritance<EncodingT> > o)  
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
		if ( !o->isNullDerived() && typename _CppClass<EncodingT>::CppClassIDEquality(-1)(o->getDerived()) ) {
			m_logger->errorStream() << "idDerived : Identifier is null.";
			throw InvalidQueryException("idDerived : Identifier is null.");
		}
		else if ( !o->isNullDerived() ) {
			values.addInt( o->getDerived()->getIdentifier() );
			fields.push_back( C("idDerived") );
		}
		else {
			m_logger->errorStream() << "idDerived : null reference is forbidden.";
			throw InvalidQueryException("idDerived : null reference is forbidden.");
		}
		int id = connection->selectMaxID(C("identifier"), C("cppInheritance"))+1;
		values.addInt( id );
		fields.push_back( C("identifier") );
		values.addText( o->getBaseClassName() );
		fields.push_back( C("baseClassName") );
		values.addText( o->getBaseAccess() );
		fields.push_back( C("baseAccess") );
		statement.swap( connection->insert(C("cppInheritance"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		o->setIdentifier(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, C("cppInheritance"), o);
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
_CppInheritanceAccess<EncodingT>::deleteCppInheritance(shared_ptr< _CppInheritance<EncodingT> > o)  
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
	typename _CppInheritance<EncodingT>::CppInheritanceIDEquality CppInheritanceIdEquality(*o);
	typename std::vector< shared_ptr< _CppInheritance<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), CppInheritanceIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before deletion.";
		throw UnSelectedObjectException("You must select object before deletion.");
	}
	try {
		statement.swap( connection->deleteFrom(C("cppInheritance"), C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, C("cppInheritance"), o);
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
typename _CppInheritanceAccess<EncodingT>::connection_t
_CppInheritanceAccess<EncodingT>::addInsertSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_insertSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppInheritanceAccess<EncodingT>::connection_t
_CppInheritanceAccess<EncodingT>::addUpdateSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_updateSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppInheritanceAccess<EncodingT>::connection_t
_CppInheritanceAccess<EncodingT>::addDeleteSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_deleteSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppInheritanceAccess<EncodingT>::connection_t
_CppInheritanceAccess<EncodingT>::addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber)  
{
	return m_transactionSignal.connect(subscriber);
}

template<class EncodingT>
void
_CppInheritanceAccess<EncodingT>::removeInsertSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppInheritanceAccess<EncodingT>::removeUpdateSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppInheritanceAccess<EncodingT>::removeDeleteSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppInheritanceAccess<EncodingT>::removeTransactionSignal(connection_t connection)  
{
	connection.disconnect();
}


NAMESPACE_END

#undef C
#undef A

