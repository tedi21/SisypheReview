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
_DebugVariableInfoAccess<EncodingT>* _DebugVariableInfoAccess<EncodingT>::m_instance = NULL;

template<class EncodingT>
_DebugVariableInfoAccess<EncodingT>* 
_DebugVariableInfoAccess<EncodingT>::getInstance()  
{
	if (m_instance == NULL) {
		m_instance = new _DebugVariableInfoAccess<EncodingT>();
	}
	return m_instance;
}

template<class EncodingT>
_DebugVariableInfoAccess<EncodingT>::_DebugVariableInfoAccess()
: m_transactionOwner(false) 
{
	m_logger = &Category::getInstance(LOGNAME);
	m_logger->debugStream() << "constructor DebugVariableInfoAccess " << m_transactionOwner;
}

template<class EncodingT>
_DebugVariableInfoAccess<EncodingT>::~_DebugVariableInfoAccess()
{
	cancelSelection();
	m_logger = NULL;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _DebugVariableInfo<EncodingT> > >
_DebugVariableInfoAccess<EncodingT>::getManyDebugVariableInfos(typename EncodingT::string_t const&  filter) const 
{
	boost::shared_ptr< _DebugVariableInfo<EncodingT> > value;
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _DebugVariableInfo<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(C("identifier"));
	columns.push_back(C("category"));
	columns.push_back(C("debugType"));
	columns.push_back(C("name"));
	columns.push_back(C("textValue"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,C("debugVariableInfo")), filter) );
	while( statement.executeStep() ) {
		int identifier;
		typename EncodingT::string_t category;
		typename EncodingT::string_t debugType;
		typename EncodingT::string_t name;
		typename EncodingT::string_t textValue;
		if (statement.getInt( 0, identifier ) &&
			statement.getText( 1, category ) &&
			statement.getText( 2, debugType ) &&
			statement.getText( 3, name ) &&
			statement.getText( 4, textValue )) {
			value.reset(new _DebugVariableInfo<EncodingT>(
				identifier,
				category,
				debugType,
				name,
				textValue));
			tab.push_back(value);
		}
	}
	return tab;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _DebugVariableInfo<EncodingT> > >
_DebugVariableInfoAccess<EncodingT>::getAllDebugVariableInfos() const 
{
	return getManyDebugVariableInfos(EncodingT::EMPTY);
}

template<class EncodingT>
boost::shared_ptr< _DebugVariableInfo<EncodingT> >
_DebugVariableInfoAccess<EncodingT>::getOneDebugVariableInfo(int identifier) const 
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _DebugVariableInfo<EncodingT> > > result = getManyDebugVariableInfos(C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
std::vector< boost::shared_ptr< _DebugVariableInfo<EncodingT> > >
_DebugVariableInfoAccess<EncodingT>::selectManyDebugVariableInfos(typename EncodingT::string_t const&  filter, bool nowait, bool addition)  
{
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _DebugVariableInfo<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(C("identifier"));
	columns.push_back(C("category"));
	columns.push_back(C("debugType"));
	columns.push_back(C("name"));
	columns.push_back(C("textValue"));
	if (!addition || !connection->isTransactionInProgress()) {
		cancelSelection();
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
	}
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,C("debugVariableInfo")), filter, nowait) );
	while( statement.executeStep() ) {
		int identifier;
		typename EncodingT::string_t category;
		typename EncodingT::string_t debugType;
		typename EncodingT::string_t name;
		typename EncodingT::string_t textValue;
		if (statement.getInt( 0, identifier ) &&
			statement.getText( 1, category ) &&
			statement.getText( 2, debugType ) &&
			statement.getText( 3, name ) &&
			statement.getText( 4, textValue )) {
			tab.push_back(boost::shared_ptr< _DebugVariableInfo<EncodingT> >(new _DebugVariableInfo<EncodingT>(
				identifier,
				category,
				debugType,
				name,
				textValue)));
		}
	}
	m_backup.insert(m_backup.end(), tab.begin(), tab.end());
	return copy_ptr(tab);
}

template<class EncodingT>
boost::shared_ptr< _DebugVariableInfo<EncodingT> >
_DebugVariableInfoAccess<EncodingT>::selectOneDebugVariableInfo(int identifier, bool nowait, bool addition)  
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _DebugVariableInfo<EncodingT> > > result = selectManyDebugVariableInfos(C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait, addition);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
bool
_DebugVariableInfoAccess<EncodingT>::isSelectedDebugVariableInfo(boost::shared_ptr< _DebugVariableInfo<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	typename _DebugVariableInfo<EncodingT>::DebugVariableInfoIDEquality debugVariableInfoIdEquality(*o);
	return (!m_backup.empty() && (std::find_if(m_backup.begin(), m_backup.end(), debugVariableInfoIdEquality)!=m_backup.end()));
}

template<class EncodingT>
void
_DebugVariableInfoAccess<EncodingT>::cancelSelection()  
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
_DebugVariableInfoAccess<EncodingT>::fillDebugFunctionInfo(boost::shared_ptr< _DebugVariableInfo<EncodingT> > o)  
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
	_DebugFunctionInfoAccess<EncodingT>* debugFunctionInfoAccess = _DebugFunctionInfoAccess<EncodingT>::getInstance();
	if (!debugFunctionInfoAccess) {
		m_logger->errorStream() << "DebugFunctionInfoAccess class is not initialized.";
		throw NullPointerException("DebugFunctionInfoAccess class is not initialized.");
	}
	int id;
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,C("idDebugFunction")), std::vector<typename EncodingT::string_t>(1,C("debugVariableInfo")), C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
	if( statement.executeStep() && statement.getInt( 0, id ) && id != 0 ) {
		typename _DebugVariableInfo<EncodingT>::DebugVariableInfoIDEquality debugVariableInfoIdEquality(o->getIdentifier());
		boost::shared_ptr< _DebugFunctionInfo<EncodingT> > val = debugFunctionInfoAccess->getOneDebugFunctionInfo(id);
		typename std::vector< boost::shared_ptr<_DebugVariableInfo<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), debugVariableInfoIdEquality);
		if (save != m_backup.end()) {
			(*save)->setDebugFunctionInfo(val);
		}
		o->setDebugFunctionInfo(val);
	}
	else {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
}

template<class EncodingT>
bool
_DebugVariableInfoAccess<EncodingT>::isModifiedDebugVariableInfo(boost::shared_ptr< _DebugVariableInfo<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	typename _DebugVariableInfo<EncodingT>::DebugVariableInfoIDEquality debugVariableInfoIdEquality(*o);
	typename std::vector< boost::shared_ptr< _DebugVariableInfo<EncodingT> > >::const_iterator save = std::find_if(m_backup.begin(), m_backup.end(), debugVariableInfoIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getCategory() != o->getCategory());
	bUpdate = bUpdate || ((*save)->getDebugType() != o->getDebugType());
	bUpdate = bUpdate || ((*save)->getName() != o->getName());
	bUpdate = bUpdate || ((*save)->getTextValue() != o->getTextValue());
	bUpdate = bUpdate || (!(*save)->isNullDebugFunctionInfo() && !o->isNullDebugFunctionInfo() && !typename _DebugFunctionInfo<EncodingT>::DebugFunctionInfoIDEquality(*(*save)->getDebugFunctionInfo())(o->getDebugFunctionInfo()))
		|| ((*save)->isNullDebugFunctionInfo() && !o->isNullDebugFunctionInfo()) 
		|| (!(*save)->isNullDebugFunctionInfo() && o->isNullDebugFunctionInfo());
	return bUpdate;
}

template<class EncodingT>
void
_DebugVariableInfoAccess<EncodingT>::updateDebugVariableInfo(boost::shared_ptr< _DebugVariableInfo<EncodingT> > o)  
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
	typename _DebugVariableInfo<EncodingT>::DebugVariableInfoIDEquality debugVariableInfoIdEquality(*o);
	typename std::vector< boost::shared_ptr< _DebugVariableInfo<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), debugVariableInfoIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	try {
		if ( (*save)->getCategory() != o->getCategory() ) {
			values.addText( o->getCategory() );
			fields.push_back( C("category") );
		}
		if ( (*save)->getDebugType() != o->getDebugType() ) {
			values.addText( o->getDebugType() );
			fields.push_back( C("debugType") );
		}
		if ( (*save)->getName() != o->getName() ) {
			values.addText( o->getName() );
			fields.push_back( C("name") );
		}
		if ( (*save)->getTextValue() != o->getTextValue() ) {
			values.addText( o->getTextValue() );
			fields.push_back( C("textValue") );
		}
		if ( !o->isNullDebugFunctionInfo() && typename _DebugFunctionInfo<EncodingT>::DebugFunctionInfoIDEquality(-1)(o->getDebugFunctionInfo()) ) {
			m_logger->errorStream() << "idDebugFunction : Identifier is null.";
			throw InvalidQueryException("idDebugFunction : Identifier is null.");
		}
		else if ( !o->isNullDebugFunctionInfo() && !typename _DebugFunctionInfo<EncodingT>::DebugFunctionInfoIDEquality(*(o->getDebugFunctionInfo()))((*save)->getDebugFunctionInfo()) ) {
			values.addInt( o->getDebugFunctionInfo()->getIdentifier() );
			fields.push_back( C("idDebugFunction") );
		}
		else if ( o->isNullDebugFunctionInfo() && !(*save)->isNullDebugFunctionInfo() ) {
			m_logger->errorStream() << "idDebugFunction : null reference is forbidden.";
			throw InvalidQueryException("idDebugFunction : null reference is forbidden.");
		}
		if (!fields.empty()) {
			statement.swap( connection->update(C("debugVariableInfo"), fields, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, C("debugVariableInfo"), o);
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
_DebugVariableInfoAccess<EncodingT>::insertDebugVariableInfo(boost::shared_ptr< _DebugVariableInfo<EncodingT> > o)  
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
		int id = connection->selectMaxID(C("identifier"), C("debugVariableInfo"))+1;
		values.addInt( id );
		fields.push_back( C("identifier") );
		values.addText( o->getCategory() );
		fields.push_back( C("category") );
		values.addText( o->getDebugType() );
		fields.push_back( C("debugType") );
		values.addText( o->getName() );
		fields.push_back( C("name") );
		values.addText( o->getTextValue() );
		fields.push_back( C("textValue") );
		if ( !o->isNullDebugFunctionInfo() && typename _DebugFunctionInfo<EncodingT>::DebugFunctionInfoIDEquality(-1)(o->getDebugFunctionInfo()) ) {
			m_logger->errorStream() << "idDebugFunction : Identifier is null.";
			throw InvalidQueryException("idDebugFunction : Identifier is null.");
		}
		else if ( !o->isNullDebugFunctionInfo() ) {
			values.addInt( o->getDebugFunctionInfo()->getIdentifier() );
			fields.push_back( C("idDebugFunction") );
		}
		else {
			m_logger->errorStream() << "idDebugFunction : null reference is forbidden.";
			throw InvalidQueryException("idDebugFunction : null reference is forbidden.");
		}
		statement.swap( connection->insert(C("debugVariableInfo"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		o->setIdentifier(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, C("debugVariableInfo"), o);
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
_DebugVariableInfoAccess<EncodingT>::deleteDebugVariableInfo(boost::shared_ptr< _DebugVariableInfo<EncodingT> > o)  
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
	typename _DebugVariableInfo<EncodingT>::DebugVariableInfoIDEquality DebugVariableInfoIdEquality(*o);
	typename std::vector< boost::shared_ptr< _DebugVariableInfo<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), DebugVariableInfoIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before deletion.";
		throw UnSelectedObjectException("You must select object before deletion.");
	}
	try {
		statement.swap( connection->deleteFrom(C("debugVariableInfo"), C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, C("debugVariableInfo"), o);
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
typename _DebugVariableInfoAccess<EncodingT>::connection_t
_DebugVariableInfoAccess<EncodingT>::addInsertSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_insertSignal.connect(subscriber);
}

template<class EncodingT>
typename _DebugVariableInfoAccess<EncodingT>::connection_t
_DebugVariableInfoAccess<EncodingT>::addUpdateSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_updateSignal.connect(subscriber);
}

template<class EncodingT>
typename _DebugVariableInfoAccess<EncodingT>::connection_t
_DebugVariableInfoAccess<EncodingT>::addDeleteSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_deleteSignal.connect(subscriber);
}

template<class EncodingT>
typename _DebugVariableInfoAccess<EncodingT>::connection_t
_DebugVariableInfoAccess<EncodingT>::addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber)  
{
	return m_transactionSignal.connect(subscriber);
}

template<class EncodingT>
void
_DebugVariableInfoAccess<EncodingT>::removeInsertSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_DebugVariableInfoAccess<EncodingT>::removeUpdateSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_DebugVariableInfoAccess<EncodingT>::removeDeleteSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_DebugVariableInfoAccess<EncodingT>::removeTransactionSignal(connection_t connection)  
{
	connection.disconnect();
}


NAMESPACE_END

#undef C
#undef A

