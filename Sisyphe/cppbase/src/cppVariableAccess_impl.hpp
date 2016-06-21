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
_CppVariableAccess<EncodingT>* _CppVariableAccess<EncodingT>::m_instance = NULL;

template<class EncodingT>
_CppVariableAccess<EncodingT>* 
_CppVariableAccess<EncodingT>::getInstance()  
{
	if (m_instance == NULL) {
		m_instance = new _CppVariableAccess<EncodingT>();
	}
	return m_instance;
}

template<class EncodingT>
_CppVariableAccess<EncodingT>::_CppVariableAccess()
: m_transactionOwner(false) 
{
	m_logger = &Category::getInstance(LOGNAME);
	m_logger->debugStream() << "constructor CppVariableAccess " << m_transactionOwner;
}

template<class EncodingT>
_CppVariableAccess<EncodingT>::~_CppVariableAccess()
{
	cancelSelection();
	m_logger = NULL;
}

template<class EncodingT>
std::vector< shared_ptr< _CppVariable<EncodingT> > >
_CppVariableAccess<EncodingT>::getManyCppVariables(typename EncodingT::string_t const&  filter) const 
{
	shared_ptr< _CppVariable<EncodingT> > value;
	_DataStatement<EncodingT> statement;
	std::vector< shared_ptr< _CppVariable<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(C("identifier"));
	columns.push_back(C("varType"));
	columns.push_back(C("name"));
	columns.push_back(C("isStatic"));
	columns.push_back(C("isConst"));
	columns.push_back(C("lineNumber"));
	columns.push_back(C("startBlock"));
	columns.push_back(C("lengthBlock"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,C("cppVariable")), filter) );
	while( statement.executeStep() ) {
		int identifier;
		typename EncodingT::string_t varType;
		typename EncodingT::string_t name;
		int isStatic;
		int isConst;
		int lineNumber;
		int startBlock;
		int lengthBlock;
		if (statement.getInt( 0, identifier ) &&
			statement.getText( 1, varType ) &&
			statement.getText( 2, name ) &&
			statement.getInt( 3, isStatic ) &&
			statement.getInt( 4, isConst ) &&
			statement.getInt( 5, lineNumber ) &&
			statement.getInt( 6, startBlock ) &&
			statement.getInt( 7, lengthBlock )) {
			value.reset(new _CppVariable<EncodingT>(
				identifier,
				varType,
				name,
				isStatic,
				isConst,
				lineNumber,
				startBlock,
				lengthBlock));
			tab.push_back(value);
		}
	}
	return tab;
}

template<class EncodingT>
std::vector< shared_ptr< _CppVariable<EncodingT> > >
_CppVariableAccess<EncodingT>::getAllCppVariables() const 
{
	return getManyCppVariables(EncodingT::EMPTY);
}

template<class EncodingT>
shared_ptr< _CppVariable<EncodingT> >
_CppVariableAccess<EncodingT>::getOneCppVariable(int identifier) const 
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< shared_ptr< _CppVariable<EncodingT> > > result = getManyCppVariables(C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
std::vector< shared_ptr< _CppVariable<EncodingT> > >
_CppVariableAccess<EncodingT>::selectManyCppVariables(typename EncodingT::string_t const&  filter, bool nowait, bool addition)  
{
	_DataStatement<EncodingT> statement;
	std::vector< shared_ptr< _CppVariable<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(C("identifier"));
	columns.push_back(C("varType"));
	columns.push_back(C("name"));
	columns.push_back(C("isStatic"));
	columns.push_back(C("isConst"));
	columns.push_back(C("lineNumber"));
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
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,C("cppVariable")), filter, nowait) );
	while( statement.executeStep() ) {
		int identifier;
		typename EncodingT::string_t varType;
		typename EncodingT::string_t name;
		int isStatic;
		int isConst;
		int lineNumber;
		int startBlock;
		int lengthBlock;
		if (statement.getInt( 0, identifier ) &&
			statement.getText( 1, varType ) &&
			statement.getText( 2, name ) &&
			statement.getInt( 3, isStatic ) &&
			statement.getInt( 4, isConst ) &&
			statement.getInt( 5, lineNumber ) &&
			statement.getInt( 6, startBlock ) &&
			statement.getInt( 7, lengthBlock )) {
			tab.push_back(shared_ptr< _CppVariable<EncodingT> >(new _CppVariable<EncodingT>(
				identifier,
				varType,
				name,
				isStatic,
				isConst,
				lineNumber,
				startBlock,
				lengthBlock)));
		}
	}
	m_backup.insert(m_backup.end(), tab.begin(), tab.end());
	return copy_ptr(tab);
}

template<class EncodingT>
shared_ptr< _CppVariable<EncodingT> >
_CppVariableAccess<EncodingT>::selectOneCppVariable(int identifier, bool nowait, bool addition)  
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< shared_ptr< _CppVariable<EncodingT> > > result = selectManyCppVariables(C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait, addition);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
bool
_CppVariableAccess<EncodingT>::isSelectedCppVariable(shared_ptr< _CppVariable<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	typename _CppVariable<EncodingT>::CppVariableIDEquality cppVariableIdEquality(*o);
	return (!m_backup.empty() && (std::find_if(m_backup.begin(), m_backup.end(), cppVariableIdEquality)!=m_backup.end()));
}

template<class EncodingT>
void
_CppVariableAccess<EncodingT>::cancelSelection()  
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
_CppVariableAccess<EncodingT>::fillCppFunction(shared_ptr< _CppVariable<EncodingT> > o)  
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
	_CppFunctionAccess<EncodingT>* cppFunctionAccess = _CppFunctionAccess<EncodingT>::getInstance();
	if (!cppFunctionAccess) {
		m_logger->errorStream() << "CppFunctionAccess class is not initialized.";
		throw NullPointerException("CppFunctionAccess class is not initialized.");
	}
	int id;
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,C("idFunction")), std::vector<typename EncodingT::string_t>(1,C("cppVariable")), C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
	if( statement.executeStep() && statement.getInt( 0, id ) && id != 0 ) {
		typename _CppVariable<EncodingT>::CppVariableIDEquality cppVariableIdEquality(o->getIdentifier());
		shared_ptr< _CppFunction<EncodingT> > val = cppFunctionAccess->getOneCppFunction(id);
		typename std::vector< shared_ptr<_CppVariable<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppVariableIdEquality);
		if (save != m_backup.end()) {
			(*save)->setCppFunction(val);
		}
		o->setCppFunction(val);
	}
	else {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
}

template<class EncodingT>
bool
_CppVariableAccess<EncodingT>::isModifiedCppVariable(shared_ptr< _CppVariable<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	typename _CppVariable<EncodingT>::CppVariableIDEquality cppVariableIdEquality(*o);
	typename std::vector< shared_ptr< _CppVariable<EncodingT> > >::const_iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppVariableIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getVarType() != o->getVarType());
	bUpdate = bUpdate || ((*save)->getName() != o->getName());
	bUpdate = bUpdate || ((*save)->getIsStatic() != o->getIsStatic());
	bUpdate = bUpdate || ((*save)->getIsConst() != o->getIsConst());
	bUpdate = bUpdate || ((*save)->getLineNumber() != o->getLineNumber());
	bUpdate = bUpdate || ((*save)->getStartBlock() != o->getStartBlock());
	bUpdate = bUpdate || ((*save)->getLengthBlock() != o->getLengthBlock());
	bUpdate = bUpdate || (!(*save)->isNullCppFunction() && !o->isNullCppFunction() && !typename _CppFunction<EncodingT>::CppFunctionIDEquality(*(*save)->getCppFunction())(o->getCppFunction()))
		|| ((*save)->isNullCppFunction() && !o->isNullCppFunction()) 
		|| (!(*save)->isNullCppFunction() && o->isNullCppFunction());
	return bUpdate;
}

template<class EncodingT>
void
_CppVariableAccess<EncodingT>::updateCppVariable(shared_ptr< _CppVariable<EncodingT> > o)  
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
	typename _CppVariable<EncodingT>::CppVariableIDEquality cppVariableIdEquality(*o);
	typename std::vector< shared_ptr< _CppVariable<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppVariableIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	try {
		if ( (*save)->getVarType() != o->getVarType() ) {
			values.addText( o->getVarType() );
			fields.push_back( C("varType") );
		}
		if ( (*save)->getName() != o->getName() ) {
			values.addText( o->getName() );
			fields.push_back( C("name") );
		}
		if ( (*save)->getIsStatic() != o->getIsStatic() ) {
			values.addInt( o->getIsStatic() );
			fields.push_back( C("isStatic") );
		}
		if ( (*save)->getIsConst() != o->getIsConst() ) {
			values.addInt( o->getIsConst() );
			fields.push_back( C("isConst") );
		}
		if ( (*save)->getLineNumber() != o->getLineNumber() ) {
			values.addInt( o->getLineNumber() );
			fields.push_back( C("lineNumber") );
		}
		if ( (*save)->getStartBlock() != o->getStartBlock() ) {
			values.addInt( o->getStartBlock() );
			fields.push_back( C("startBlock") );
		}
		if ( (*save)->getLengthBlock() != o->getLengthBlock() ) {
			values.addInt( o->getLengthBlock() );
			fields.push_back( C("lengthBlock") );
		}
		if ( !o->isNullCppFunction() && typename _CppFunction<EncodingT>::CppFunctionIDEquality(-1)(o->getCppFunction()) ) {
			m_logger->errorStream() << "idFunction : Identifier is null.";
			throw InvalidQueryException("idFunction : Identifier is null.");
		}
		else if ( !o->isNullCppFunction() && !typename _CppFunction<EncodingT>::CppFunctionIDEquality(*(o->getCppFunction()))((*save)->getCppFunction()) ) {
			values.addInt( o->getCppFunction()->getIdentifier() );
			fields.push_back( C("idFunction") );
		}
		else if ( o->isNullCppFunction() && !(*save)->isNullCppFunction() ) {
			m_logger->errorStream() << "idFunction : null reference is forbidden.";
			throw InvalidQueryException("idFunction : null reference is forbidden.");
		}
		if (!fields.empty()) {
			statement.swap( connection->update(C("cppVariable"), fields, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, C("cppVariable"), o);
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
_CppVariableAccess<EncodingT>::insertCppVariable(shared_ptr< _CppVariable<EncodingT> > o)  
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
		int id = connection->selectMaxID(C("identifier"), C("cppVariable"))+1;
		values.addInt( id );
		fields.push_back( C("identifier") );
		values.addText( o->getVarType() );
		fields.push_back( C("varType") );
		values.addText( o->getName() );
		fields.push_back( C("name") );
		values.addInt( o->getIsStatic() );
		fields.push_back( C("isStatic") );
		values.addInt( o->getIsConst() );
		fields.push_back( C("isConst") );
		if ( !o->isNullCppFunction() && typename _CppFunction<EncodingT>::CppFunctionIDEquality(-1)(o->getCppFunction()) ) {
			m_logger->errorStream() << "idFunction : Identifier is null.";
			throw InvalidQueryException("idFunction : Identifier is null.");
		}
		else if ( !o->isNullCppFunction() ) {
			values.addInt( o->getCppFunction()->getIdentifier() );
			fields.push_back( C("idFunction") );
		}
		else {
			m_logger->errorStream() << "idFunction : null reference is forbidden.";
			throw InvalidQueryException("idFunction : null reference is forbidden.");
		}
		values.addInt( o->getLineNumber() );
		fields.push_back( C("lineNumber") );
		values.addInt( o->getStartBlock() );
		fields.push_back( C("startBlock") );
		values.addInt( o->getLengthBlock() );
		fields.push_back( C("lengthBlock") );
		statement.swap( connection->insert(C("cppVariable"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		o->setIdentifier(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, C("cppVariable"), o);
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
_CppVariableAccess<EncodingT>::deleteCppVariable(shared_ptr< _CppVariable<EncodingT> > o)  
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
	typename _CppVariable<EncodingT>::CppVariableIDEquality CppVariableIdEquality(*o);
	typename std::vector< shared_ptr< _CppVariable<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), CppVariableIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before deletion.";
		throw UnSelectedObjectException("You must select object before deletion.");
	}
	try {
		statement.swap( connection->deleteFrom(C("cppVariable"), C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, C("cppVariable"), o);
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
typename _CppVariableAccess<EncodingT>::connection_t
_CppVariableAccess<EncodingT>::addInsertSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_insertSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppVariableAccess<EncodingT>::connection_t
_CppVariableAccess<EncodingT>::addUpdateSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_updateSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppVariableAccess<EncodingT>::connection_t
_CppVariableAccess<EncodingT>::addDeleteSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_deleteSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppVariableAccess<EncodingT>::connection_t
_CppVariableAccess<EncodingT>::addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber)  
{
	return m_transactionSignal.connect(subscriber);
}

template<class EncodingT>
void
_CppVariableAccess<EncodingT>::removeInsertSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppVariableAccess<EncodingT>::removeUpdateSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppVariableAccess<EncodingT>::removeDeleteSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppVariableAccess<EncodingT>::removeTransactionSignal(connection_t connection)  
{
	connection.disconnect();
}


NAMESPACE_END

#undef C
#undef A

