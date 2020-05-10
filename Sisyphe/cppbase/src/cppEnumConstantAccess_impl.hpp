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
std::vector< boost::shared_ptr< _CppEnumConstant<EncodingT> > >
_CppEnumConstantAccess<EncodingT>::getManyCppEnumConstants(typename EncodingT::string_t const&  filter) const 
{
	boost::shared_ptr< _CppEnumConstant<EncodingT> > value;
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _CppEnumConstant<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("name"));
	columns.push_back(UCS("defaultValue"));
	columns.push_back(UCS("lineNumber"));
	columns.push_back(UCS("startBlock"));
	columns.push_back(UCS("lengthBlock"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,UCS("cppEnumConstant")), filter) );
	while( statement.executeStep() ) {
		long long identifier;
		typename EncodingT::string_t name;
		long long defaultValue;
		long long lineNumber;
		long long startBlock;
		long long lengthBlock;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, name ) &&
			statement.getInt64( 2, defaultValue ) &&
			statement.getInt64( 3, lineNumber ) &&
			statement.getInt64( 4, startBlock ) &&
			statement.getInt64( 5, lengthBlock )) {
			value.reset(new _CppEnumConstant<EncodingT>(
				identifier,
				name,
				defaultValue,
				lineNumber,
				startBlock,
				lengthBlock));
			tab.push_back(value);
		}
	}
	return tab;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppEnumConstant<EncodingT> > >
_CppEnumConstantAccess<EncodingT>::getAllCppEnumConstants() const 
{
	return getManyCppEnumConstants(EncodingT::EMPTY);
}

template<class EncodingT>
boost::shared_ptr< _CppEnumConstant<EncodingT> >
_CppEnumConstantAccess<EncodingT>::getOneCppEnumConstant(long long identifier) const 
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _CppEnumConstant<EncodingT> > > result = getManyCppEnumConstants(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppEnumConstant<EncodingT> > >
_CppEnumConstantAccess<EncodingT>::selectManyCppEnumConstants(typename EncodingT::string_t const&  filter, bool nowait, bool addition)  
{
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _CppEnumConstant<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("name"));
	columns.push_back(UCS("defaultValue"));
	columns.push_back(UCS("lineNumber"));
	columns.push_back(UCS("startBlock"));
	columns.push_back(UCS("lengthBlock"));
	if (!addition || !connection->isTransactionInProgress()) {
		cancelSelection();
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
	}
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,UCS("cppEnumConstant")), filter, nowait) );
	while( statement.executeStep() ) {
		long long identifier;
		typename EncodingT::string_t name;
		long long defaultValue;
		long long lineNumber;
		long long startBlock;
		long long lengthBlock;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, name ) &&
			statement.getInt64( 2, defaultValue ) &&
			statement.getInt64( 3, lineNumber ) &&
			statement.getInt64( 4, startBlock ) &&
			statement.getInt64( 5, lengthBlock )) {
			tab.push_back(boost::shared_ptr< _CppEnumConstant<EncodingT> >(new _CppEnumConstant<EncodingT>(
				identifier,
				name,
				defaultValue,
				lineNumber,
				startBlock,
				lengthBlock)));
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
boost::shared_ptr< _CppEnumConstant<EncodingT> >
_CppEnumConstantAccess<EncodingT>::selectOneCppEnumConstant(long long identifier, bool nowait, bool addition)  
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _CppEnumConstant<EncodingT> > > result = selectManyCppEnumConstants(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait, addition);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
bool
_CppEnumConstantAccess<EncodingT>::isSelectedCppEnumConstant(boost::shared_ptr< _CppEnumConstant<EncodingT> > o) const 
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
_CppEnumConstantAccess<EncodingT>::fillCppEnum(boost::shared_ptr< _CppEnumConstant<EncodingT> > o)  
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
	long long id;
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,UCS("idEnum")), std::vector<typename EncodingT::string_t>(1,UCS("cppEnumConstant")), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
	if( statement.executeStep() && statement.getInt64( 0, id ) && id != 0 ) {
		typename _CppEnumConstant<EncodingT>::CppEnumConstantIDEquality cppEnumConstantIdEquality(o->getIdentifier());
		boost::shared_ptr< _CppEnum<EncodingT> > val = cppEnumAccess->getOneCppEnum(id);
		typename std::list< boost::shared_ptr<_CppEnumConstant<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppEnumConstantIdEquality);
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
_CppEnumConstantAccess<EncodingT>::isModifiedCppEnumConstant(boost::shared_ptr< _CppEnumConstant<EncodingT> > o) const 
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
	typename std::list< boost::shared_ptr< _CppEnumConstant<EncodingT> > >::const_iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppEnumConstantIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getName() != o->getName());
	bUpdate = bUpdate || ((*save)->getDefaultValue() != o->getDefaultValue());
	bUpdate = bUpdate || ((*save)->getLineNumber() != o->getLineNumber());
	bUpdate = bUpdate || ((*save)->getStartBlock() != o->getStartBlock());
	bUpdate = bUpdate || ((*save)->getLengthBlock() != o->getLengthBlock());
	bUpdate = bUpdate || (!(*save)->isNullCppEnum() && !o->isNullCppEnum() && !typename _CppEnum<EncodingT>::CppEnumIDEquality(*(*save)->getCppEnum())(o->getCppEnum()))
		|| ((*save)->isNullCppEnum() && !o->isNullCppEnum()) 
		|| (!(*save)->isNullCppEnum() && o->isNullCppEnum());
	return bUpdate;
}

template<class EncodingT>
void
_CppEnumConstantAccess<EncodingT>::updateCppEnumConstant(boost::shared_ptr< _CppEnumConstant<EncodingT> > o)  
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
	typename std::list< boost::shared_ptr< _CppEnumConstant<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppEnumConstantIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	try {
		if ( (*save)->getName() != o->getName() ) {
			values.addText( o->getName() );
			fields.push_back( UCS("name") );
		}
		if ( (*save)->getDefaultValue() != o->getDefaultValue() ) {
			values.addInt64( o->getDefaultValue() );
			fields.push_back( UCS("defaultValue") );
		}
		if ( (*save)->getLineNumber() != o->getLineNumber() ) {
			values.addInt64( o->getLineNumber() );
			fields.push_back( UCS("lineNumber") );
		}
		if ( (*save)->getStartBlock() != o->getStartBlock() ) {
			values.addInt64( o->getStartBlock() );
			fields.push_back( UCS("startBlock") );
		}
		if ( (*save)->getLengthBlock() != o->getLengthBlock() ) {
			values.addInt64( o->getLengthBlock() );
			fields.push_back( UCS("lengthBlock") );
		}
		if ( !o->isNullCppEnum() && typename _CppEnum<EncodingT>::CppEnumIDEquality(-1)(o->getCppEnum()) ) {
			m_logger->errorStream() << "idEnum : Identifier is null.";
			throw InvalidQueryException("idEnum : Identifier is null.");
		}
		else if ( !o->isNullCppEnum() && !typename _CppEnum<EncodingT>::CppEnumIDEquality(*(o->getCppEnum()))((*save)->getCppEnum()) ) {
			values.addInt64( o->getCppEnum()->getIdentifier() );
			fields.push_back( UCS("idEnum") );
		}
		else if ( o->isNullCppEnum() && !(*save)->isNullCppEnum() ) {
			m_logger->errorStream() << "idEnum : null reference is forbidden.";
			throw InvalidQueryException("idEnum : null reference is forbidden.");
		}
		if (!fields.empty()) {
			statement.swap( connection->update(UCS("cppEnumConstant"), fields, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, UCS("cppEnumConstant"), o);
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
_CppEnumConstantAccess<EncodingT>::insertCppEnumConstant(boost::shared_ptr< _CppEnumConstant<EncodingT> > o)  
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
		int id = connection->selectMaxID(UCS("identifier"), UCS("cppEnumConstant"))+1;
		values.addInt( id );
		fields.push_back( UCS("identifier") );
		values.addText( o->getName() );
		fields.push_back( UCS("name") );
		values.addInt64( o->getDefaultValue() );
		fields.push_back( UCS("defaultValue") );
		if ( !o->isNullCppEnum() && typename _CppEnum<EncodingT>::CppEnumIDEquality(-1)(o->getCppEnum()) ) {
			m_logger->errorStream() << "idEnum : Identifier is null.";
			throw InvalidQueryException("idEnum : Identifier is null.");
		}
		else if ( !o->isNullCppEnum() ) {
			values.addInt64( o->getCppEnum()->getIdentifier() );
			fields.push_back( UCS("idEnum") );
		}
		else {
			m_logger->errorStream() << "idEnum : null reference is forbidden.";
			throw InvalidQueryException("idEnum : null reference is forbidden.");
		}
		values.addInt64( o->getLineNumber() );
		fields.push_back( UCS("lineNumber") );
		values.addInt64( o->getStartBlock() );
		fields.push_back( UCS("startBlock") );
		values.addInt64( o->getLengthBlock() );
		fields.push_back( UCS("lengthBlock") );
		statement.swap( connection->insert(UCS("cppEnumConstant"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		o->setIdentifier(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, UCS("cppEnumConstant"), o);
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
_CppEnumConstantAccess<EncodingT>::deleteCppEnumConstant(boost::shared_ptr< _CppEnumConstant<EncodingT> > o)  
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
	typename std::list< boost::shared_ptr< _CppEnumConstant<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), CppEnumConstantIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before deletion.";
		throw UnSelectedObjectException("You must select object before deletion.");
	}
	try {
		statement.swap( connection->deleteFrom(UCS("cppEnumConstant"), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, UCS("cppEnumConstant"), o);
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

