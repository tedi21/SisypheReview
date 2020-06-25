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
_CppNoticeAccess<EncodingT>* _CppNoticeAccess<EncodingT>::m_instance = NULL;

template<class EncodingT>
_CppNoticeAccess<EncodingT>* 
_CppNoticeAccess<EncodingT>::getInstance()  
{
	if (m_instance == NULL) {
		m_instance = new _CppNoticeAccess<EncodingT>();
	}
	return m_instance;
}

template<class EncodingT>
_CppNoticeAccess<EncodingT>::_CppNoticeAccess()
: m_transactionOwner(false) 
{
	m_logger = &Category::getInstance(LOGNAME);
	m_logger->debugStream() << "constructor CppNoticeAccess " << m_transactionOwner;
}

template<class EncodingT>
_CppNoticeAccess<EncodingT>::~_CppNoticeAccess()
{
	cancelSelection();
	m_logger = NULL;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppNotice<EncodingT> > >
_CppNoticeAccess<EncodingT>::getManyCppNotices(typename EncodingT::string_t const&  filter) const 
{
	boost::shared_ptr< _CppNotice<EncodingT> > value;
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _CppNotice<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("description"));
	columns.push_back(UCS("category"));
	columns.push_back(UCS("ruleNumber"));
	columns.push_back(UCS("lineNumber"));
	columns.push_back(UCS("startBlock"));
	columns.push_back(UCS("lengthBlock"));
	columns.push_back(UCS("isNew"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,UCS("cppNotice")), filter) );
	while( statement.executeStep() ) {
		long long identifier;
		typename EncodingT::string_t description;
		typename EncodingT::string_t category;
		long long ruleNumber;
		long long lineNumber;
		long long startBlock;
		long long lengthBlock;
		long long isNew;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, description ) &&
			statement.getText( 2, category ) &&
			statement.getInt64( 3, ruleNumber ) &&
			statement.getInt64( 4, lineNumber ) &&
			statement.getInt64( 5, startBlock ) &&
			statement.getInt64( 6, lengthBlock ) &&
			statement.getInt64( 7, isNew )) {
			value.reset(new _CppNotice<EncodingT>(
				identifier,
				description,
				category,
				ruleNumber,
				lineNumber,
				startBlock,
				lengthBlock,
				isNew));
			tab.push_back(value);
		}
	}
	return tab;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppNotice<EncodingT> > >
_CppNoticeAccess<EncodingT>::getAllCppNotices() const 
{
	return getManyCppNotices(EncodingT::EMPTY);
}

template<class EncodingT>
boost::shared_ptr< _CppNotice<EncodingT> >
_CppNoticeAccess<EncodingT>::getOneCppNotice(long long identifier) const 
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _CppNotice<EncodingT> > > result = getManyCppNotices(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppNotice<EncodingT> > >
_CppNoticeAccess<EncodingT>::selectManyCppNotices(typename EncodingT::string_t const&  filter, bool nowait, bool addition)  
{
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _CppNotice<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("description"));
	columns.push_back(UCS("category"));
	columns.push_back(UCS("ruleNumber"));
	columns.push_back(UCS("lineNumber"));
	columns.push_back(UCS("startBlock"));
	columns.push_back(UCS("lengthBlock"));
	columns.push_back(UCS("isNew"));
	if (!addition || !connection->isTransactionInProgress()) {
		cancelSelection();
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
	}
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,UCS("cppNotice")), filter, nowait) );
	while( statement.executeStep() ) {
		long long identifier;
		typename EncodingT::string_t description;
		typename EncodingT::string_t category;
		long long ruleNumber;
		long long lineNumber;
		long long startBlock;
		long long lengthBlock;
		long long isNew;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, description ) &&
			statement.getText( 2, category ) &&
			statement.getInt64( 3, ruleNumber ) &&
			statement.getInt64( 4, lineNumber ) &&
			statement.getInt64( 5, startBlock ) &&
			statement.getInt64( 6, lengthBlock ) &&
			statement.getInt64( 7, isNew )) {
			tab.push_back(boost::shared_ptr< _CppNotice<EncodingT> >(new _CppNotice<EncodingT>(
				identifier,
				description,
				category,
				ruleNumber,
				lineNumber,
				startBlock,
				lengthBlock,
				isNew)));
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
boost::shared_ptr< _CppNotice<EncodingT> >
_CppNoticeAccess<EncodingT>::selectOneCppNotice(long long identifier, bool nowait, bool addition)  
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _CppNotice<EncodingT> > > result = selectManyCppNotices(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait, addition);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
bool
_CppNoticeAccess<EncodingT>::isSelectedCppNotice(boost::shared_ptr< _CppNotice<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	typename _CppNotice<EncodingT>::CppNoticeIDEquality cppNoticeIdEquality(*o);
	return (!m_backup.empty() && (std::find_if(m_backup.begin(), m_backup.end(), cppNoticeIdEquality)!=m_backup.end()));
}

template<class EncodingT>
void
_CppNoticeAccess<EncodingT>::cancelSelection()  
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
_CppNoticeAccess<EncodingT>::fillCppFile(boost::shared_ptr< _CppNotice<EncodingT> > o)  
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
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,UCS("idFile")), std::vector<typename EncodingT::string_t>(1,UCS("cppNotice")), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
	if( statement.executeStep() && statement.getInt64( 0, id ) && id != 0 ) {
		typename _CppNotice<EncodingT>::CppNoticeIDEquality cppNoticeIdEquality(o->getIdentifier());
		boost::shared_ptr< _CppFile<EncodingT> > val = cppFileAccess->getOneCppFile(id);
		typename std::list< boost::shared_ptr<_CppNotice<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppNoticeIdEquality);
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
_CppNoticeAccess<EncodingT>::isModifiedCppNotice(boost::shared_ptr< _CppNotice<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	typename _CppNotice<EncodingT>::CppNoticeIDEquality cppNoticeIdEquality(*o);
	typename std::list< boost::shared_ptr< _CppNotice<EncodingT> > >::const_iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppNoticeIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getDescription() != o->getDescription());
	bUpdate = bUpdate || ((*save)->getCategory() != o->getCategory());
	bUpdate = bUpdate || ((*save)->getRuleNumber() != o->getRuleNumber());
	bUpdate = bUpdate || ((*save)->getLineNumber() != o->getLineNumber());
	bUpdate = bUpdate || ((*save)->getStartBlock() != o->getStartBlock());
	bUpdate = bUpdate || ((*save)->getLengthBlock() != o->getLengthBlock());
	bUpdate = bUpdate || ((*save)->getIsNew() != o->getIsNew());
	bUpdate = bUpdate || (!(*save)->isNullCppFile() && !o->isNullCppFile() && !typename _CppFile<EncodingT>::CppFileIDEquality(*(*save)->getCppFile())(o->getCppFile()))
		|| ((*save)->isNullCppFile() && !o->isNullCppFile()) 
		|| (!(*save)->isNullCppFile() && o->isNullCppFile());
	return bUpdate;
}

template<class EncodingT>
void
_CppNoticeAccess<EncodingT>::updateCppNotice(boost::shared_ptr< _CppNotice<EncodingT> > o)  
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
	typename _CppNotice<EncodingT>::CppNoticeIDEquality cppNoticeIdEquality(*o);
	typename std::list< boost::shared_ptr< _CppNotice<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppNoticeIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	try {
		if ( (*save)->getDescription() != o->getDescription() ) {
			values.addText( o->getDescription() );
			fields.push_back( UCS("description") );
		}
		if ( (*save)->getCategory() != o->getCategory() ) {
			values.addText( o->getCategory() );
			fields.push_back( UCS("category") );
		}
		if ( (*save)->getRuleNumber() != o->getRuleNumber() ) {
			values.addInt64( o->getRuleNumber() );
			fields.push_back( UCS("ruleNumber") );
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
		if ( (*save)->getIsNew() != o->getIsNew() ) {
			values.addInt64( o->getIsNew() );
			fields.push_back( UCS("isNew") );
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
			statement.swap( connection->update(UCS("cppNotice"), fields, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, UCS("cppNotice"), o);
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
_CppNoticeAccess<EncodingT>::insertCppNotice(boost::shared_ptr< _CppNotice<EncodingT> > o)  
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
		int id = connection->selectMaxID(UCS("identifier"), UCS("cppNotice"))+1;
		values.addInt( id );
		fields.push_back( UCS("identifier") );
		values.addText( o->getDescription() );
		fields.push_back( UCS("description") );
		values.addText( o->getCategory() );
		fields.push_back( UCS("category") );
		values.addInt64( o->getRuleNumber() );
		fields.push_back( UCS("ruleNumber") );
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
		values.addInt64( o->getLineNumber() );
		fields.push_back( UCS("lineNumber") );
		values.addInt64( o->getStartBlock() );
		fields.push_back( UCS("startBlock") );
		values.addInt64( o->getLengthBlock() );
		fields.push_back( UCS("lengthBlock") );
		values.addInt64( o->getIsNew() );
		fields.push_back( UCS("isNew") );
		statement.swap( connection->insert(UCS("cppNotice"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		o->setIdentifier(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, UCS("cppNotice"), o);
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
_CppNoticeAccess<EncodingT>::deleteCppNotice(boost::shared_ptr< _CppNotice<EncodingT> > o)  
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
	typename _CppNotice<EncodingT>::CppNoticeIDEquality CppNoticeIdEquality(*o);
	typename std::list< boost::shared_ptr< _CppNotice<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), CppNoticeIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before deletion.";
		throw UnSelectedObjectException("You must select object before deletion.");
	}
	try {
		statement.swap( connection->deleteFrom(UCS("cppNotice"), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, UCS("cppNotice"), o);
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
typename _CppNoticeAccess<EncodingT>::connection_t
_CppNoticeAccess<EncodingT>::addInsertSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_insertSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppNoticeAccess<EncodingT>::connection_t
_CppNoticeAccess<EncodingT>::addUpdateSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_updateSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppNoticeAccess<EncodingT>::connection_t
_CppNoticeAccess<EncodingT>::addDeleteSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_deleteSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppNoticeAccess<EncodingT>::connection_t
_CppNoticeAccess<EncodingT>::addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber)  
{
	return m_transactionSignal.connect(subscriber);
}

template<class EncodingT>
void
_CppNoticeAccess<EncodingT>::removeInsertSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppNoticeAccess<EncodingT>::removeUpdateSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppNoticeAccess<EncodingT>::removeDeleteSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppNoticeAccess<EncodingT>::removeTransactionSignal(connection_t connection)  
{
	connection.disconnect();
}


NAMESPACE_END

#undef C
#undef A

