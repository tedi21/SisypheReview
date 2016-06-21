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
_CppEnumConstantAccess<EncodingT>* _CppEnumConstantAccess<EncodingT>::m_instance = NULL;

template<class EncodingT>
_CppEnumConstantAccess<EncodingT>* 
_CppEnumConstantAccess<EncodingT>::getInstance()  
{
	if (m_instance == NULL) {
		m_instance = new _CppEnumConstantAccess<EncodingT>();
	}
	return m_instance;
}

template<class EncodingT>
_CppEnumConstantAccess<EncodingT>::_CppEnumConstantAccess()
: m_transactionOwner(false) 
{
	m_logger = &Category::getInstance(LOGNAME);
	m_logger->debugStream() << "constructor CppEnumConstantAccess " << m_transactionOwner;
}

template<class EncodingT>
_CppEnumConstantAccess<EncodingT>::~_CppEnumConstantAccess()
{
	cancelSelection();
	m_logger = NULL;
}

template<class EncodingT>
std::vector< shared_ptr< _CppEnumConstant<EncodingT> > >
_CppEnumConstantAccess<EncodingT>::getManyCppEnumConstants(typename EncodingT::string_t const&  filter) const 
{
	shared_ptr< _CppEnumConstant<EncodingT> > value;
	_DataStatement<EncodingT> statement;
	std::vector< shared_ptr< _CppEnumConstant<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(C("identifier"));
	columns.push_back(C("name"));
	columns.push_back(C("defaultValue"));
	columns.push_back(C("startBlock"));
	columns.push_back(C("lengthBlock"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,C("cppEnumConstant")), filter) );
	while( statement.executeStep() ) {
		int identifier;
		typename EncodingT::string_t name;
		int defaultValue;
		int startBlock;
		int lengthBlock;
		if (statement.getInt( 0, identifier ) &&
			statement.getText( 1, name ) &&
			statement.getInt( 2, defaultValue ) &&
			statement.getInt( 3, startBlock ) &&
			statement.getInt( 4, lengthBlock )) {
			value.reset(new _CppEnumConstant<EncodingT>(
				identifier,
				name,
				defaultValue,
				startBlock,
				lengthBlock));
			tab.push_back(value);
		}
	}
	return tab;
}

template<class EncodingT>
std::vector< shared_ptr< _CppEnumConstant<EncodingT> > >
_CppEnumConstantAccess<EncodingT>::getAllCppEnumConstants() const 
{
	return getManyCppEnumConstants(EncodingT::EMPTY);
}

template<class EncodingT>
shared_ptr< _CppEnumConstant<EncodingT> >
_CppEnumConstantAccess<EncodingT>::getOneCppEnumConstant(int identifier) const 
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< shared_ptr< _CppEnumConstant<EncodingT> > > result = getManyCppEnumConstants(C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
std::vector< shared_ptr< _CppEnumConstant<EncodingT> > >
_CppEnumConstantAccess<EncodingT>::selectManyCppEnumConstants(typename EncodingT::string_t const&  filter, bool nowait, bool addition)  
{
	_DataStatement<EncodingT> statement;
	std::vector< shared_ptr< _CppEnumConstant<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(C("identifier"));
	columns.push_back(C("name"));
	columns.push_back(C("defaultValue"));
	columns.push_back(C("startBlock"));
	columns.push_back(C("lengthBlock"));
	if (!addition || !connection->isTransactionInProgress()) {
		cancelSelection();
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
	}
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,C("cppEnumConstant")), filter, nowait) );
	while( statement.executeStep() ) {
		int identifier;
		typename EncodingT::string_t name;
		int defaultValue;
		int startBlock;
		int lengthBlock;
		if (statement.getInt( 0, identifier ) &&
			statement.getText( 1, name ) &&
			statement.getInt( 2, defaultValue ) &&
			statement.getInt( 3, startBlock ) &&
			statement.getInt( 4, lengthBlock )) {
			tab.push_back(shared_ptr< _CppEnumConstant<EncodingT> >(new _CppEnumConstant<EncodingT>(
				identifier,
				name,
				defaultValue,
				startBlock,
				lengthBlock)));
		}
	}
	m_backup.insert(m_backup.end(), tab.begin(), tab.end());
	return copy_ptr(tab);
}

template<class EncodingT>
shared_ptr< _CppEnumConstant<EncodingT> >
_CppEnumConstantAccess<EncodingT>::selectOneCppEnumConstant(int identifier, bool nowait, bool addition)  
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< shared_ptr< _CppEnumConstant<EncodingT> > > result = selectManyCppEnumConstants(C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait, addition);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
bool
_CppEnumConstantAccess<EncodingT>::isSelectedCppEnumConstant(shared_ptr< _CppEnumConstant<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	typename _CppEnumConstant<EncodingT>::CppEnumConstantIDEquality cppEnumConstantIdEquality(*o);
	return (!m_backup.empty() && (std::find_if(m_backup.begin(), m_backup.end(), cppEnumConstantIdEquality)!=m_backup.end()));
}

template<class EncodingT>
void
_CppEnumConstantAccess<EncodingT>::cancelSelection()  
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
_CppEnumConstantAccess<EncodingT>::fillCppEnum(shared_ptr< _CppEnumConstant<EncodingT> > o)  
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
	_CppEnumAccess<EncodingT>* cppEnumAccess = _CppEnumAccess<EncodingT>::getInstance();
	if (!cppEnumAccess) {
		m_logger->errorStream() << "CppEnumAccess class is not initialized.";
		throw NullPointerException("CppEnumAccess class is not initialized.");
	}
	int id;
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,C("idEnum")), std::vector<typename EncodingT::string_t>(1,C("cppEnumConstant")), C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
	if( statement.executeStep() && statement.getInt( 0, id ) && id != 0 ) {
		typename _CppEnumConstant<EncodingT>::CppEnumConstantIDEquality cppEnumConstantIdEquality(o->getIdentifier());
		shared_ptr< _CppEnum<EncodingT> > val = cppEnumAccess->getOneCppEnum(id);
		typename std::vector< shared_ptr<_CppEnumConstant<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppEnumConstantIdEquality);
		if (save != m_backup.end()) {
			(*save)->setCppEnum(val);
		}
		o->setCppEnum(val);
	}
	else {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
}

template<class EncodingT>
bool
_CppEnumConstantAccess<EncodingT>::isModifiedCppEnumConstant(shared_ptr< _CppEnumConstant<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	typename _CppEnumConstant<EncodingT>::CppEnumConstantIDEquality cppEnumConstantIdEquality(*o);
	typename std::vector< shared_ptr< _CppEnumConstant<EncodingT> > >::const_iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppEnumConstantIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getName() != o->getName());
	bUpdate = bUpdate || ((*save)->getDefaultValue() != o->getDefaultValue());
	bUpdate = bUpdate || ((*save)->getStartBlock() != o->getStartBlock());
	bUpdate = bUpdate || ((*save)->getLengthBlock() != o->getLengthBlock());
	bUpdate = bUpdate || (!(*save)->isNullCppEnum() && !o->isNullCppEnum() && !typename _CppEnum<EncodingT>::CppEnumIDEquality(*(*save)->getCppEnum())(o->getCppEnum()))
		|| ((*save)->isNullCppEnum() && !o->isNullCppEnum()) 
		|| (!(*save)->isNullCppEnum() && o->isNullCppEnum());
	return bUpdate;
}

template<class EncodingT>
void
_CppEnumConstantAccess<EncodingT>::updateCppEnumConstant(shared_ptr< _CppEnumConstant<EncodingT> > o)  
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
	typename _CppEnumConstant<EncodingT>::CppEnumConstantIDEquality cppEnumConstantIdEquality(*o);
	typename std::vector< shared_ptr< _CppEnumConstant<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppEnumConstantIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	try {
		if ( (*save)->getName() != o->getName() ) {
			values.addText( o->getName() );
			fields.push_back( C("name") );
		}
		if ( (*save)->getDefaultValue() != o->getDefaultValue() ) {
			values.addInt( o->getDefaultValue() );
			fields.push_back( C("defaultValue") );
		}
		if ( (*save)->getStartBlock() != o->getStartBlock() ) {
			values.addInt( o->getStartBlock() );
			fields.push_back( C("startBlock") );
		}
		if ( (*save)->getLengthBlock() != o->getLengthBlock() ) {
			values.addInt( o->getLengthBlock() );
			fields.push_back( C("lengthBlock") );
		}
		if ( !o->isNullCppEnum() && typename _CppEnum<EncodingT>::CppEnumIDEquality(-1)(o->getCppEnum()) ) {
			m_logger->errorStream() << "idEnum : Identifier is null.";
			throw InvalidQueryException("idEnum : Identifier is null.");
		}
		else if ( !o->isNullCppEnum() && !typename _CppEnum<EncodingT>::CppEnumIDEquality(*(o->getCppEnum()))((*save)->getCppEnum()) ) {
			values.addInt( o->getCppEnum()->getIdentifier() );
			fields.push_back( C("idEnum") );
		}
		else if ( o->isNullCppEnum() && !(*save)->isNullCppEnum() ) {
			m_logger->errorStream() << "idEnum : null reference is forbidden.";
			throw InvalidQueryException("idEnum : null reference is forbidden.");
		}
		if (!fields.empty()) {
			statement.swap( connection->update(C("cppEnumConstant"), fields, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, C("cppEnumConstant"), o);
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
_CppEnumConstantAccess<EncodingT>::insertCppEnumConstant(shared_ptr< _CppEnumConstant<EncodingT> > o)  
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
		int id = connection->selectMaxID(C("identifier"), C("cppEnumConstant"))+1;
		values.addInt( id );
		fields.push_back( C("identifier") );
		values.addText( o->getName() );
		fields.push_back( C("name") );
		values.addInt( o->getDefaultValue() );
		fields.push_back( C("defaultValue") );
		if ( !o->isNullCppEnum() && typename _CppEnum<EncodingT>::CppEnumIDEquality(-1)(o->getCppEnum()) ) {
			m_logger->errorStream() << "idEnum : Identifier is null.";
			throw InvalidQueryException("idEnum : Identifier is null.");
		}
		else if ( !o->isNullCppEnum() ) {
			values.addInt( o->getCppEnum()->getIdentifier() );
			fields.push_back( C("idEnum") );
		}
		else {
			m_logger->errorStream() << "idEnum : null reference is forbidden.";
			throw InvalidQueryException("idEnum : null reference is forbidden.");
		}
		values.addInt( o->getStartBlock() );
		fields.push_back( C("startBlock") );
		values.addInt( o->getLengthBlock() );
		fields.push_back( C("lengthBlock") );
		statement.swap( connection->insert(C("cppEnumConstant"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		o->setIdentifier(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, C("cppEnumConstant"), o);
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
_CppEnumConstantAccess<EncodingT>::deleteCppEnumConstant(shared_ptr< _CppEnumConstant<EncodingT> > o)  
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
	typename _CppEnumConstant<EncodingT>::CppEnumConstantIDEquality CppEnumConstantIdEquality(*o);
	typename std::vector< shared_ptr< _CppEnumConstant<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), CppEnumConstantIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before deletion.";
		throw UnSelectedObjectException("You must select object before deletion.");
	}
	try {
		statement.swap( connection->deleteFrom(C("cppEnumConstant"), C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, C("cppEnumConstant"), o);
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
typename _CppEnumConstantAccess<EncodingT>::connection_t
_CppEnumConstantAccess<EncodingT>::addInsertSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_insertSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppEnumConstantAccess<EncodingT>::connection_t
_CppEnumConstantAccess<EncodingT>::addUpdateSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_updateSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppEnumConstantAccess<EncodingT>::connection_t
_CppEnumConstantAccess<EncodingT>::addDeleteSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_deleteSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppEnumConstantAccess<EncodingT>::connection_t
_CppEnumConstantAccess<EncodingT>::addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber)  
{
	return m_transactionSignal.connect(subscriber);
}

template<class EncodingT>
void
_CppEnumConstantAccess<EncodingT>::removeInsertSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppEnumConstantAccess<EncodingT>::removeUpdateSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppEnumConstantAccess<EncodingT>::removeDeleteSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppEnumConstantAccess<EncodingT>::removeTransactionSignal(connection_t connection)  
{
	connection.disconnect();
}


NAMESPACE_END

#undef C
#undef A

