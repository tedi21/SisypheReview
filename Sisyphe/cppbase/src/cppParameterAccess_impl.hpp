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
_CppParameterAccess<EncodingT>* _CppParameterAccess<EncodingT>::m_instance = NULL;

template<class EncodingT>
_CppParameterAccess<EncodingT>* 
_CppParameterAccess<EncodingT>::getInstance()  
{
	if (m_instance == NULL) {
		m_instance = new _CppParameterAccess<EncodingT>();
	}
	return m_instance;
}

template<class EncodingT>
_CppParameterAccess<EncodingT>::_CppParameterAccess()
: m_transactionOwner(false) 
{
	m_logger = &Category::getInstance(LOGNAME);
	m_logger->debugStream() << "constructor CppParameterAccess " << m_transactionOwner;
}

template<class EncodingT>
_CppParameterAccess<EncodingT>::~_CppParameterAccess()
{
	cancelSelection();
	m_logger = NULL;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppParameter<EncodingT> > >
_CppParameterAccess<EncodingT>::getManyCppParameters(typename EncodingT::string_t const&  filter) const 
{
	boost::shared_ptr< _CppParameter<EncodingT> > value;
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _CppParameter<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(C("identifier"));
	columns.push_back(C("paramOrder"));
	columns.push_back(C("paramType"));
	columns.push_back(C("isConst"));
	columns.push_back(C("defaultValue"));
	columns.push_back(C("decName"));
	columns.push_back(C("decLineNumber"));
	columns.push_back(C("startDecBlock"));
	columns.push_back(C("lengthDecBlock"));
	columns.push_back(C("defName"));
	columns.push_back(C("defLineNumber"));
	columns.push_back(C("startDefBlock"));
	columns.push_back(C("lengthDefBlock"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,C("cppParameter")), filter) );
	while( statement.executeStep() ) {
		long long identifier;
		long long paramOrder;
		typename EncodingT::string_t paramType;
		long long isConst;
		typename EncodingT::string_t defaultValue;
		typename EncodingT::string_t decName;
		long long decLineNumber;
		long long startDecBlock;
		long long lengthDecBlock;
		typename EncodingT::string_t defName;
		long long defLineNumber;
		long long startDefBlock;
		long long lengthDefBlock;
		if (statement.getInt64( 0, identifier ) &&
			statement.getInt64( 1, paramOrder ) &&
			statement.getText( 2, paramType ) &&
			statement.getInt64( 3, isConst ) &&
			statement.getText( 4, defaultValue ) &&
			statement.getText( 5, decName ) &&
			statement.getInt64( 6, decLineNumber ) &&
			statement.getInt64( 7, startDecBlock ) &&
			statement.getInt64( 8, lengthDecBlock ) &&
			statement.getText( 9, defName ) &&
			statement.getInt64( 10, defLineNumber ) &&
			statement.getInt64( 11, startDefBlock ) &&
			statement.getInt64( 12, lengthDefBlock )) {
			value.reset(new _CppParameter<EncodingT>(
				identifier,
				paramOrder,
				paramType,
				isConst,
				defaultValue,
				decName,
				decLineNumber,
				startDecBlock,
				lengthDecBlock,
				defName,
				defLineNumber,
				startDefBlock,
				lengthDefBlock));
			tab.push_back(value);
		}
	}
	return tab;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppParameter<EncodingT> > >
_CppParameterAccess<EncodingT>::getAllCppParameters() const 
{
	return getManyCppParameters(EncodingT::EMPTY);
}

template<class EncodingT>
boost::shared_ptr< _CppParameter<EncodingT> >
_CppParameterAccess<EncodingT>::getOneCppParameter(long long identifier) const 
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _CppParameter<EncodingT> > > result = getManyCppParameters(C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppParameter<EncodingT> > >
_CppParameterAccess<EncodingT>::selectManyCppParameters(typename EncodingT::string_t const&  filter, bool nowait, bool addition)  
{
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _CppParameter<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(C("identifier"));
	columns.push_back(C("paramOrder"));
	columns.push_back(C("paramType"));
	columns.push_back(C("isConst"));
	columns.push_back(C("defaultValue"));
	columns.push_back(C("decName"));
	columns.push_back(C("decLineNumber"));
	columns.push_back(C("startDecBlock"));
	columns.push_back(C("lengthDecBlock"));
	columns.push_back(C("defName"));
	columns.push_back(C("defLineNumber"));
	columns.push_back(C("startDefBlock"));
	columns.push_back(C("lengthDefBlock"));
	if (!addition || !connection->isTransactionInProgress()) {
		cancelSelection();
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
	}
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,C("cppParameter")), filter, nowait) );
	while( statement.executeStep() ) {
		long long identifier;
		long long paramOrder;
		typename EncodingT::string_t paramType;
		long long isConst;
		typename EncodingT::string_t defaultValue;
		typename EncodingT::string_t decName;
		long long decLineNumber;
		long long startDecBlock;
		long long lengthDecBlock;
		typename EncodingT::string_t defName;
		long long defLineNumber;
		long long startDefBlock;
		long long lengthDefBlock;
		if (statement.getInt64( 0, identifier ) &&
			statement.getInt64( 1, paramOrder ) &&
			statement.getText( 2, paramType ) &&
			statement.getInt64( 3, isConst ) &&
			statement.getText( 4, defaultValue ) &&
			statement.getText( 5, decName ) &&
			statement.getInt64( 6, decLineNumber ) &&
			statement.getInt64( 7, startDecBlock ) &&
			statement.getInt64( 8, lengthDecBlock ) &&
			statement.getText( 9, defName ) &&
			statement.getInt64( 10, defLineNumber ) &&
			statement.getInt64( 11, startDefBlock ) &&
			statement.getInt64( 12, lengthDefBlock )) {
			tab.push_back(boost::shared_ptr< _CppParameter<EncodingT> >(new _CppParameter<EncodingT>(
				identifier,
				paramOrder,
				paramType,
				isConst,
				defaultValue,
				decName,
				decLineNumber,
				startDecBlock,
				lengthDecBlock,
				defName,
				defLineNumber,
				startDefBlock,
				lengthDefBlock)));
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
boost::shared_ptr< _CppParameter<EncodingT> >
_CppParameterAccess<EncodingT>::selectOneCppParameter(long long identifier, bool nowait, bool addition)  
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _CppParameter<EncodingT> > > result = selectManyCppParameters(C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait, addition);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
bool
_CppParameterAccess<EncodingT>::isSelectedCppParameter(boost::shared_ptr< _CppParameter<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	typename _CppParameter<EncodingT>::CppParameterIDEquality cppParameterIdEquality(*o);
	return (!m_backup.empty() && (std::find_if(m_backup.begin(), m_backup.end(), cppParameterIdEquality)!=m_backup.end()));
}

template<class EncodingT>
void
_CppParameterAccess<EncodingT>::cancelSelection()  
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
_CppParameterAccess<EncodingT>::fillCppFunction(boost::shared_ptr< _CppParameter<EncodingT> > o)  
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
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,C("idFunction")), std::vector<typename EncodingT::string_t>(1,C("cppParameter")), C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
	if( statement.executeStep() && statement.getInt64( 0, id ) && id != 0 ) {
		typename _CppParameter<EncodingT>::CppParameterIDEquality cppParameterIdEquality(o->getIdentifier());
		boost::shared_ptr< _CppFunction<EncodingT> > val = cppFunctionAccess->getOneCppFunction(id);
		typename std::list< boost::shared_ptr<_CppParameter<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppParameterIdEquality);
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
_CppParameterAccess<EncodingT>::isModifiedCppParameter(boost::shared_ptr< _CppParameter<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	typename _CppParameter<EncodingT>::CppParameterIDEquality cppParameterIdEquality(*o);
	typename std::list< boost::shared_ptr< _CppParameter<EncodingT> > >::const_iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppParameterIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getParamOrder() != o->getParamOrder());
	bUpdate = bUpdate || ((*save)->getParamType() != o->getParamType());
	bUpdate = bUpdate || ((*save)->getIsConst() != o->getIsConst());
	bUpdate = bUpdate || ((*save)->getDefaultValue() != o->getDefaultValue());
	bUpdate = bUpdate || ((*save)->getDecName() != o->getDecName());
	bUpdate = bUpdate || ((*save)->getDecLineNumber() != o->getDecLineNumber());
	bUpdate = bUpdate || ((*save)->getStartDecBlock() != o->getStartDecBlock());
	bUpdate = bUpdate || ((*save)->getLengthDecBlock() != o->getLengthDecBlock());
	bUpdate = bUpdate || ((*save)->getDefName() != o->getDefName());
	bUpdate = bUpdate || ((*save)->getDefLineNumber() != o->getDefLineNumber());
	bUpdate = bUpdate || ((*save)->getStartDefBlock() != o->getStartDefBlock());
	bUpdate = bUpdate || ((*save)->getLengthDefBlock() != o->getLengthDefBlock());
	bUpdate = bUpdate || (!(*save)->isNullCppFunction() && !o->isNullCppFunction() && !typename _CppFunction<EncodingT>::CppFunctionIDEquality(*(*save)->getCppFunction())(o->getCppFunction()))
		|| ((*save)->isNullCppFunction() && !o->isNullCppFunction()) 
		|| (!(*save)->isNullCppFunction() && o->isNullCppFunction());
	return bUpdate;
}

template<class EncodingT>
void
_CppParameterAccess<EncodingT>::updateCppParameter(boost::shared_ptr< _CppParameter<EncodingT> > o)  
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
	typename _CppParameter<EncodingT>::CppParameterIDEquality cppParameterIdEquality(*o);
	typename std::list< boost::shared_ptr< _CppParameter<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppParameterIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	try {
		if ( (*save)->getParamOrder() != o->getParamOrder() ) {
			values.addInt64( o->getParamOrder() );
			fields.push_back( C("paramOrder") );
		}
		if ( (*save)->getParamType() != o->getParamType() ) {
			values.addText( o->getParamType() );
			fields.push_back( C("paramType") );
		}
		if ( (*save)->getIsConst() != o->getIsConst() ) {
			values.addInt64( o->getIsConst() );
			fields.push_back( C("isConst") );
		}
		if ( (*save)->getDefaultValue() != o->getDefaultValue() ) {
			values.addText( o->getDefaultValue() );
			fields.push_back( C("defaultValue") );
		}
		if ( (*save)->getDecName() != o->getDecName() ) {
			values.addText( o->getDecName() );
			fields.push_back( C("decName") );
		}
		if ( (*save)->getDecLineNumber() != o->getDecLineNumber() ) {
			values.addInt64( o->getDecLineNumber() );
			fields.push_back( C("decLineNumber") );
		}
		if ( (*save)->getStartDecBlock() != o->getStartDecBlock() ) {
			values.addInt64( o->getStartDecBlock() );
			fields.push_back( C("startDecBlock") );
		}
		if ( (*save)->getLengthDecBlock() != o->getLengthDecBlock() ) {
			values.addInt64( o->getLengthDecBlock() );
			fields.push_back( C("lengthDecBlock") );
		}
		if ( (*save)->getDefName() != o->getDefName() ) {
			values.addText( o->getDefName() );
			fields.push_back( C("defName") );
		}
		if ( (*save)->getDefLineNumber() != o->getDefLineNumber() ) {
			values.addInt64( o->getDefLineNumber() );
			fields.push_back( C("defLineNumber") );
		}
		if ( (*save)->getStartDefBlock() != o->getStartDefBlock() ) {
			values.addInt64( o->getStartDefBlock() );
			fields.push_back( C("startDefBlock") );
		}
		if ( (*save)->getLengthDefBlock() != o->getLengthDefBlock() ) {
			values.addInt64( o->getLengthDefBlock() );
			fields.push_back( C("lengthDefBlock") );
		}
		if ( !o->isNullCppFunction() && typename _CppFunction<EncodingT>::CppFunctionIDEquality(-1)(o->getCppFunction()) ) {
			m_logger->errorStream() << "idFunction : Identifier is null.";
			throw InvalidQueryException("idFunction : Identifier is null.");
		}
		else if ( !o->isNullCppFunction() && !typename _CppFunction<EncodingT>::CppFunctionIDEquality(*(o->getCppFunction()))((*save)->getCppFunction()) ) {
			values.addInt64( o->getCppFunction()->getIdentifier() );
			fields.push_back( C("idFunction") );
		}
		else if ( o->isNullCppFunction() && !(*save)->isNullCppFunction() ) {
			m_logger->errorStream() << "idFunction : null reference is forbidden.";
			throw InvalidQueryException("idFunction : null reference is forbidden.");
		}
		if (!fields.empty()) {
			statement.swap( connection->update(C("cppParameter"), fields, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, C("cppParameter"), o);
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
_CppParameterAccess<EncodingT>::insertCppParameter(boost::shared_ptr< _CppParameter<EncodingT> > o)  
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
		int id = connection->selectMaxID(C("identifier"), C("cppParameter"))+1;
		values.addInt( id );
		fields.push_back( C("identifier") );
		values.addInt64( o->getParamOrder() );
		fields.push_back( C("paramOrder") );
		values.addText( o->getParamType() );
		fields.push_back( C("paramType") );
		values.addInt64( o->getIsConst() );
		fields.push_back( C("isConst") );
		values.addText( o->getDefaultValue() );
		fields.push_back( C("defaultValue") );
		if ( !o->isNullCppFunction() && typename _CppFunction<EncodingT>::CppFunctionIDEquality(-1)(o->getCppFunction()) ) {
			m_logger->errorStream() << "idFunction : Identifier is null.";
			throw InvalidQueryException("idFunction : Identifier is null.");
		}
		else if ( !o->isNullCppFunction() ) {
			values.addInt64( o->getCppFunction()->getIdentifier() );
			fields.push_back( C("idFunction") );
		}
		else {
			m_logger->errorStream() << "idFunction : null reference is forbidden.";
			throw InvalidQueryException("idFunction : null reference is forbidden.");
		}
		values.addText( o->getDecName() );
		fields.push_back( C("decName") );
		values.addInt64( o->getDecLineNumber() );
		fields.push_back( C("decLineNumber") );
		values.addInt64( o->getStartDecBlock() );
		fields.push_back( C("startDecBlock") );
		values.addInt64( o->getLengthDecBlock() );
		fields.push_back( C("lengthDecBlock") );
		values.addText( o->getDefName() );
		fields.push_back( C("defName") );
		values.addInt64( o->getDefLineNumber() );
		fields.push_back( C("defLineNumber") );
		values.addInt64( o->getStartDefBlock() );
		fields.push_back( C("startDefBlock") );
		values.addInt64( o->getLengthDefBlock() );
		fields.push_back( C("lengthDefBlock") );
		statement.swap( connection->insert(C("cppParameter"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		o->setIdentifier(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, C("cppParameter"), o);
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
_CppParameterAccess<EncodingT>::deleteCppParameter(boost::shared_ptr< _CppParameter<EncodingT> > o)  
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
	typename _CppParameter<EncodingT>::CppParameterIDEquality CppParameterIdEquality(*o);
	typename std::list< boost::shared_ptr< _CppParameter<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), CppParameterIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before deletion.";
		throw UnSelectedObjectException("You must select object before deletion.");
	}
	try {
		statement.swap( connection->deleteFrom(C("cppParameter"), C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, C("cppParameter"), o);
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
typename _CppParameterAccess<EncodingT>::connection_t
_CppParameterAccess<EncodingT>::addInsertSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_insertSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppParameterAccess<EncodingT>::connection_t
_CppParameterAccess<EncodingT>::addUpdateSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_updateSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppParameterAccess<EncodingT>::connection_t
_CppParameterAccess<EncodingT>::addDeleteSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_deleteSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppParameterAccess<EncodingT>::connection_t
_CppParameterAccess<EncodingT>::addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber)  
{
	return m_transactionSignal.connect(subscriber);
}

template<class EncodingT>
void
_CppParameterAccess<EncodingT>::removeInsertSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppParameterAccess<EncodingT>::removeUpdateSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppParameterAccess<EncodingT>::removeDeleteSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppParameterAccess<EncodingT>::removeTransactionSignal(connection_t connection)  
{
	connection.disconnect();
}


NAMESPACE_END

#undef C
#undef A

