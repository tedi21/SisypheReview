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
std::vector< boost::shared_ptr< _CppVariable<EncodingT> > >
_CppVariableAccess<EncodingT>::getManyCppVariables(typename EncodingT::string_t const&  filter) const 
{
	boost::shared_ptr< _CppVariable<EncodingT> > value;
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _CppVariable<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("varType"));
	columns.push_back(UCS("name"));
	columns.push_back(UCS("isStatic"));
	columns.push_back(UCS("isConst"));
	columns.push_back(UCS("isConstexpr"));
	columns.push_back(UCS("lineNumber"));
	columns.push_back(UCS("startBlock"));
	columns.push_back(UCS("lengthBlock"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,UCS("cppVariable")), filter) );
	while( statement.executeStep() ) {
		long long identifier;
		typename EncodingT::string_t varType;
		typename EncodingT::string_t name;
		long long isStatic;
		long long isConst;
		long long isConstexpr;
		long long lineNumber;
		long long startBlock;
		long long lengthBlock;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, varType ) &&
			statement.getText( 2, name ) &&
			statement.getInt64( 3, isStatic ) &&
			statement.getInt64( 4, isConst ) &&
			statement.getInt64( 5, isConstexpr ) &&
			statement.getInt64( 6, lineNumber ) &&
			statement.getInt64( 7, startBlock ) &&
			statement.getInt64( 8, lengthBlock )) {
			value.reset(new _CppVariable<EncodingT>(
				identifier,
				varType,
				name,
				isStatic,
				isConst,
				isConstexpr,
				lineNumber,
				startBlock,
				lengthBlock));
			tab.push_back(value);
		}
	}
	return tab;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppVariable<EncodingT> > >
_CppVariableAccess<EncodingT>::getAllCppVariables() const 
{
	return getManyCppVariables(EncodingT::EMPTY);
}

template<class EncodingT>
boost::shared_ptr< _CppVariable<EncodingT> >
_CppVariableAccess<EncodingT>::getOneCppVariable(long long identifier) const 
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _CppVariable<EncodingT> > > result = getManyCppVariables(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppVariable<EncodingT> > >
_CppVariableAccess<EncodingT>::selectManyCppVariables(typename EncodingT::string_t const&  filter, bool nowait, bool addition)  
{
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _CppVariable<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("varType"));
	columns.push_back(UCS("name"));
	columns.push_back(UCS("isStatic"));
	columns.push_back(UCS("isConst"));
	columns.push_back(UCS("isConstexpr"));
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
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,UCS("cppVariable")), filter, nowait) );
	while( statement.executeStep() ) {
		long long identifier;
		typename EncodingT::string_t varType;
		typename EncodingT::string_t name;
		long long isStatic;
		long long isConst;
		long long isConstexpr;
		long long lineNumber;
		long long startBlock;
		long long lengthBlock;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, varType ) &&
			statement.getText( 2, name ) &&
			statement.getInt64( 3, isStatic ) &&
			statement.getInt64( 4, isConst ) &&
			statement.getInt64( 5, isConstexpr ) &&
			statement.getInt64( 6, lineNumber ) &&
			statement.getInt64( 7, startBlock ) &&
			statement.getInt64( 8, lengthBlock )) {
			tab.push_back(boost::shared_ptr< _CppVariable<EncodingT> >(new _CppVariable<EncodingT>(
				identifier,
				varType,
				name,
				isStatic,
				isConst,
				isConstexpr,
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
		m_backup.insert(tab.begin(), tab.end());
	}
	return copy_ptr(tab);
}

template<class EncodingT>
boost::shared_ptr< _CppVariable<EncodingT> >
_CppVariableAccess<EncodingT>::selectOneCppVariable(long long identifier, bool nowait, bool addition)  
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _CppVariable<EncodingT> > > result = selectManyCppVariables(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait, addition);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
bool
_CppVariableAccess<EncodingT>::isSelectedCppVariable(boost::shared_ptr< _CppVariable<EncodingT> > o) const 
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
_CppVariableAccess<EncodingT>::fillCppFunction(boost::shared_ptr< _CppVariable<EncodingT> > o)  
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
	long long id;
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,UCS("idFunction")), std::vector<typename EncodingT::string_t>(1,UCS("cppVariable")), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
	if( statement.executeStep() && statement.getInt64( 0, id ) && id != 0 ) {
		boost::shared_ptr< _CppFunction<EncodingT> > val = cppFunctionAccess->getOneCppFunction(id);
		typename backup_t::iterator save = m_backup.find(o);
		if (save != m_backup.end()) {
			(*save)->setCppFunction(val);
		}
		o->setCppFunction(val);
	}
	else {
		m_logger->debugStream() << "identifier not found.";
	}
}

template<class EncodingT>
void
_CppVariableAccess<EncodingT>::fillCppFile(boost::shared_ptr< _CppVariable<EncodingT> > o)  
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
	_CppFileAccess<EncodingT>* cppFileAccess = _CppFileAccess<EncodingT>::getInstance();
	if (!cppFileAccess) {
		m_logger->errorStream() << "CppFileAccess class is not initialized.";
		throw NullPointerException("CppFileAccess class is not initialized.");
	}
	long long id;
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,UCS("idFile")), std::vector<typename EncodingT::string_t>(1,UCS("cppVariable")), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
	if( statement.executeStep() && statement.getInt64( 0, id ) && id != 0 ) {
		boost::shared_ptr< _CppFile<EncodingT> > val = cppFileAccess->getOneCppFile(id);
		typename backup_t::iterator save = m_backup.find(o);
		if (save != m_backup.end()) {
			(*save)->setCppFile(val);
		}
		o->setCppFile(val);
	}
	else {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
}

template<class EncodingT>
bool
_CppVariableAccess<EncodingT>::isModifiedCppVariable(boost::shared_ptr< _CppVariable<EncodingT> > o) const 
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
	bUpdate = bUpdate || ((*save)->getVarType() != o->getVarType());
	bUpdate = bUpdate || ((*save)->getName() != o->getName());
	bUpdate = bUpdate || ((*save)->getIsStatic() != o->getIsStatic());
	bUpdate = bUpdate || ((*save)->getIsConst() != o->getIsConst());
	bUpdate = bUpdate || ((*save)->getIsConstexpr() != o->getIsConstexpr());
	bUpdate = bUpdate || ((*save)->getLineNumber() != o->getLineNumber());
	bUpdate = bUpdate || ((*save)->getStartBlock() != o->getStartBlock());
	bUpdate = bUpdate || ((*save)->getLengthBlock() != o->getLengthBlock());
	bUpdate = bUpdate || (!(*save)->isNullCppFunction() && !o->isNullCppFunction() && !typename _CppFunction<EncodingT>::CppFunctionIDEquality(*(*save)->getCppFunction())(o->getCppFunction()))
		|| ((*save)->isNullCppFunction() && !o->isNullCppFunction()) 
		|| (!(*save)->isNullCppFunction() && o->isNullCppFunction());
	bUpdate = bUpdate || (!(*save)->isNullCppFile() && !o->isNullCppFile() && !typename _CppFile<EncodingT>::CppFileIDEquality(*(*save)->getCppFile())(o->getCppFile()))
		|| ((*save)->isNullCppFile() && !o->isNullCppFile()) 
		|| (!(*save)->isNullCppFile() && o->isNullCppFile());
	return bUpdate;
}

template<class EncodingT>
void
_CppVariableAccess<EncodingT>::updateCppVariable(boost::shared_ptr< _CppVariable<EncodingT> > o)  
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
		if ( (*save)->getVarType() != o->getVarType() ) {
			values.addText( o->getVarType() );
			fields.push_back( UCS("varType") );
		}
		if ( (*save)->getName() != o->getName() ) {
			values.addText( o->getName() );
			fields.push_back( UCS("name") );
		}
		if ( (*save)->getIsStatic() != o->getIsStatic() ) {
			values.addInt64( o->getIsStatic() );
			fields.push_back( UCS("isStatic") );
		}
		if ( (*save)->getIsConst() != o->getIsConst() ) {
			values.addInt64( o->getIsConst() );
			fields.push_back( UCS("isConst") );
		}
		if ( (*save)->getIsConstexpr() != o->getIsConstexpr() ) {
			values.addInt64( o->getIsConstexpr() );
			fields.push_back( UCS("isConstexpr") );
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
		if ( !o->isNullCppFunction() && typename _CppFunction<EncodingT>::CppFunctionIDEquality(-1)(o->getCppFunction()) ) {
			m_logger->errorStream() << "idFunction : Identifier is null.";
			throw InvalidQueryException("idFunction : Identifier is null.");
		}
		else if ( !o->isNullCppFunction() && !typename _CppFunction<EncodingT>::CppFunctionIDEquality(*(o->getCppFunction()))((*save)->getCppFunction()) ) {
			values.addInt64( o->getCppFunction()->getIdentifier() );
			fields.push_back( UCS("idFunction") );
		}
		else if ( o->isNullCppFunction() && !(*save)->isNullCppFunction() ) {
			values.addNull();
			fields.push_back( UCS("idFunction") );
		}
		if ( !o->isNullCppFile() && typename _CppFile<EncodingT>::CppFileIDEquality(-1)(o->getCppFile()) ) {
			m_logger->errorStream() << "idFile : Identifier is null.";
			throw InvalidQueryException("idFile : Identifier is null.");
		}
		else if ( !o->isNullCppFile() && !typename _CppFile<EncodingT>::CppFileIDEquality(*(o->getCppFile()))((*save)->getCppFile()) ) {
			values.addInt64( o->getCppFile()->getIdentifier() );
			fields.push_back( UCS("idFile") );
		}
		else if ( o->isNullCppFile() && !(*save)->isNullCppFile() ) {
			m_logger->errorStream() << "idFile : null reference is forbidden.";
			throw InvalidQueryException("idFile : null reference is forbidden.");
		}
		if (!fields.empty()) {
			statement.swap( connection->update(UCS("cppVariable"), fields, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, UCS("cppVariable"), o);
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
_CppVariableAccess<EncodingT>::insertCppVariable(boost::shared_ptr< _CppVariable<EncodingT> > o)  
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
		int id = connection->selectMaxID(UCS("identifier"), UCS("cppVariable"))+1;
		values.addInt( id );
		fields.push_back( UCS("identifier") );
		values.addText( o->getVarType() );
		fields.push_back( UCS("varType") );
		values.addText( o->getName() );
		fields.push_back( UCS("name") );
		values.addInt64( o->getIsStatic() );
		fields.push_back( UCS("isStatic") );
		values.addInt64( o->getIsConst() );
		fields.push_back( UCS("isConst") );
		values.addInt64( o->getIsConstexpr() );
		fields.push_back( UCS("isConstexpr") );
		if ( !o->isNullCppFunction() && typename _CppFunction<EncodingT>::CppFunctionIDEquality(-1)(o->getCppFunction()) ) {
			m_logger->errorStream() << "idFunction : Identifier is null.";
			throw InvalidQueryException("idFunction : Identifier is null.");
		}
		else if ( !o->isNullCppFunction() ) {
			values.addInt64( o->getCppFunction()->getIdentifier() );
			fields.push_back( UCS("idFunction") );
		}
		else {
			values.addNull();
			fields.push_back( UCS("idFunction") );
		}
		values.addInt64( o->getLineNumber() );
		fields.push_back( UCS("lineNumber") );
		values.addInt64( o->getStartBlock() );
		fields.push_back( UCS("startBlock") );
		values.addInt64( o->getLengthBlock() );
		fields.push_back( UCS("lengthBlock") );
		if ( !o->isNullCppFile() && typename _CppFile<EncodingT>::CppFileIDEquality(-1)(o->getCppFile()) ) {
			m_logger->errorStream() << "idFile : Identifier is null.";
			throw InvalidQueryException("idFile : Identifier is null.");
		}
		else if ( !o->isNullCppFile() ) {
			values.addInt64( o->getCppFile()->getIdentifier() );
			fields.push_back( UCS("idFile") );
		}
		else {
			m_logger->errorStream() << "idFile : null reference is forbidden.";
			throw InvalidQueryException("idFile : null reference is forbidden.");
		}
		statement.swap( connection->insert(UCS("cppVariable"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		o->setIdentifier(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, UCS("cppVariable"), o);
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
_CppVariableAccess<EncodingT>::deleteCppVariable(boost::shared_ptr< _CppVariable<EncodingT> > o)  
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
		statement.swap( connection->deleteFrom(UCS("cppVariable"), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, UCS("cppVariable"), o);
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

