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
_TextNoticeAccess<EncodingT>* _TextNoticeAccess<EncodingT>::m_instance = NULL;

template<class EncodingT>
_TextNoticeAccess<EncodingT>* 
_TextNoticeAccess<EncodingT>::getInstance()  
{
	if (m_instance == NULL) {
		m_instance = new _TextNoticeAccess<EncodingT>();
	}
	return m_instance;
}

template<class EncodingT>
_TextNoticeAccess<EncodingT>::_TextNoticeAccess()
: m_transactionOwner(false) 
{
	m_logger = &Category::getInstance(LOGNAME);
	m_logger->debugStream() << "constructor TextNoticeAccess " << m_transactionOwner;
}

template<class EncodingT>
_TextNoticeAccess<EncodingT>::~_TextNoticeAccess()
{
	cancelSelection();
	m_logger = NULL;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _TextNotice<EncodingT> > >
_TextNoticeAccess<EncodingT>::getManyTextNotices(typename EncodingT::string_t const&  filter) const 
{
	boost::shared_ptr< _TextNotice<EncodingT> > value;
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _TextNotice<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(C("rowid"));
	columns.push_back(C("description"));
	columns.push_back(C("category"));
	columns.push_back(C("lineNumber"));
	columns.push_back(C("startBlock"));
	columns.push_back(C("lengthBlock"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,C("textNotice")), filter) );
	while( statement.executeStep() ) {
		long long rowid;
		typename EncodingT::string_t description;
		typename EncodingT::string_t category;
		int lineNumber;
		int startBlock;
		int lengthBlock;
		if (statement.getInt64( 0, rowid ) &&
			statement.getText( 1, description ) &&
			statement.getText( 2, category ) &&
			statement.getInt( 3, lineNumber ) &&
			statement.getInt( 4, startBlock ) &&
			statement.getInt( 5, lengthBlock )) {
			value.reset(new _TextNotice<EncodingT>(
				rowid,
				description,
				category,
				lineNumber,
				startBlock,
				lengthBlock));
			tab.push_back(value);
		}
	}
	return tab;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _TextNotice<EncodingT> > >
_TextNoticeAccess<EncodingT>::getAllTextNotices() const 
{
	return getManyTextNotices(EncodingT::EMPTY);
}

template<class EncodingT>
boost::shared_ptr< _TextNotice<EncodingT> >
_TextNoticeAccess<EncodingT>::getOneTextNotice(long long rowid) const 
{
	if ( rowid==-1 ) {
		m_logger->errorStream() << "Rowid : Identifier is null.";
		throw UnIdentifiedObjectException("Rowid : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _TextNotice<EncodingT> > > result = getManyTextNotices(C("rowid = ") /*+ C("\'") */+ C(ToString::parse(rowid))/* + C("\'")*/);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
std::vector< boost::shared_ptr< _TextNotice<EncodingT> > >
_TextNoticeAccess<EncodingT>::selectManyTextNotices(typename EncodingT::string_t const&  filter, bool nowait, bool addition)  
{
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _TextNotice<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(C("rowid"));
	columns.push_back(C("description"));
	columns.push_back(C("category"));
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
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,C("textNotice")), filter, nowait) );
	while( statement.executeStep() ) {
		long long rowid;
		typename EncodingT::string_t description;
		typename EncodingT::string_t category;
		int lineNumber;
		int startBlock;
		int lengthBlock;
		if (statement.getInt64( 0, rowid ) &&
			statement.getText( 1, description ) &&
			statement.getText( 2, category ) &&
			statement.getInt( 3, lineNumber ) &&
			statement.getInt( 4, startBlock ) &&
			statement.getInt( 5, lengthBlock )) {
			tab.push_back(boost::shared_ptr< _TextNotice<EncodingT> >(new _TextNotice<EncodingT>(
				rowid,
				description,
				category,
				lineNumber,
				startBlock,
				lengthBlock)));
		}
	}
	m_backup.insert(m_backup.end(), tab.begin(), tab.end());
	return copy_ptr(tab);
}

template<class EncodingT>
boost::shared_ptr< _TextNotice<EncodingT> >
_TextNoticeAccess<EncodingT>::selectOneTextNotice(long long rowid, bool nowait, bool addition)  
{
	if ( rowid==-1 ) {
		m_logger->errorStream() << "Rowid : Identifier is null.";
		throw UnIdentifiedObjectException("Rowid : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _TextNotice<EncodingT> > > result = selectManyTextNotices(C("rowid = ") /*+ C("\'") */+ C(ToString::parse(rowid))/* + C("\'")*/, nowait, addition);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
bool
_TextNoticeAccess<EncodingT>::isSelectedTextNotice(boost::shared_ptr< _TextNotice<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getRowid()==-1 ) {
		m_logger->errorStream() << "Rowid : Identifier is null.";
		throw UnIdentifiedObjectException("Rowid : Identifier is null.");
	}
	typename _TextNotice<EncodingT>::TextNoticeIDEquality textNoticeIdEquality(*o);
	return (!m_backup.empty() && (std::find_if(m_backup.begin(), m_backup.end(), textNoticeIdEquality)!=m_backup.end()));
}

template<class EncodingT>
void
_TextNoticeAccess<EncodingT>::cancelSelection()  
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
_TextNoticeAccess<EncodingT>::fillTextFile(boost::shared_ptr< _TextNotice<EncodingT> > o)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getRowid()==-1 ) {
		m_logger->errorStream() << "Rowid : Identifier is null.";
		throw UnIdentifiedObjectException("Rowid : Identifier is null.");
	}
	_DataStatement<EncodingT> statement;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	_TextFileAccess<EncodingT>* textFileAccess = _TextFileAccess<EncodingT>::getInstance();
	if (!textFileAccess) {
		m_logger->errorStream() << "TextFileAccess class is not initialized.";
		throw NullPointerException("TextFileAccess class is not initialized.");
	}
	int id;
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,C("idText")), std::vector<typename EncodingT::string_t>(1,C("textNotice")), C("rowid = ") /*+ C("\'") */+ C(ToString::parse(o->getRowid()))/* + C("\'")*/) );
	if( statement.executeStep() && statement.getInt( 0, id ) && id != 0 ) {
		typename _TextNotice<EncodingT>::TextNoticeIDEquality textNoticeIdEquality(o->getRowid());
		boost::shared_ptr< _TextFile<EncodingT> > val = textFileAccess->getOneTextFile(id);
		typename std::vector< boost::shared_ptr<_TextNotice<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), textNoticeIdEquality);
		if (save != m_backup.end()) {
			(*save)->setTextFile(val);
		}
		o->setTextFile(val);
	}
	else {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
}

template<class EncodingT>
bool
_TextNoticeAccess<EncodingT>::isModifiedTextNotice(boost::shared_ptr< _TextNotice<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getRowid()==-1 ) {
		m_logger->errorStream() << "Rowid : Identifier is null.";
		throw UnIdentifiedObjectException("Rowid : Identifier is null.");
	}
	typename _TextNotice<EncodingT>::TextNoticeIDEquality textNoticeIdEquality(*o);
	typename std::vector< boost::shared_ptr< _TextNotice<EncodingT> > >::const_iterator save = std::find_if(m_backup.begin(), m_backup.end(), textNoticeIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getDescription() != o->getDescription());
	bUpdate = bUpdate || ((*save)->getCategory() != o->getCategory());
	bUpdate = bUpdate || ((*save)->getLineNumber() != o->getLineNumber());
	bUpdate = bUpdate || ((*save)->getStartBlock() != o->getStartBlock());
	bUpdate = bUpdate || ((*save)->getLengthBlock() != o->getLengthBlock());
	bUpdate = bUpdate || (!(*save)->isNullTextFile() && !o->isNullTextFile() && !typename _TextFile<EncodingT>::TextFileIDEquality(*(*save)->getTextFile())(o->getTextFile()))
		|| ((*save)->isNullTextFile() && !o->isNullTextFile()) 
		|| (!(*save)->isNullTextFile() && o->isNullTextFile());
	return bUpdate;
}

template<class EncodingT>
void
_TextNoticeAccess<EncodingT>::updateTextNotice(boost::shared_ptr< _TextNotice<EncodingT> > o)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	_DataParameters<EncodingT> values;
	_DataStatement<EncodingT> statement;
	std::vector<typename EncodingT::string_t> fields;
	if ( o->getRowid()==-1 ) {
		m_logger->errorStream() << "Rowid : Identifier is null.";
		throw UnIdentifiedObjectException("Rowid : Identifier is null.");
	}
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	typename _TextNotice<EncodingT>::TextNoticeIDEquality textNoticeIdEquality(*o);
	typename std::vector< boost::shared_ptr< _TextNotice<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), textNoticeIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	try {
		if ( (*save)->getDescription() != o->getDescription() ) {
			values.addText( o->getDescription() );
			fields.push_back( C("description") );
		}
		if ( (*save)->getCategory() != o->getCategory() ) {
			values.addText( o->getCategory() );
			fields.push_back( C("category") );
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
		if ( !o->isNullTextFile() && typename _TextFile<EncodingT>::TextFileIDEquality(-1)(o->getTextFile()) ) {
			m_logger->errorStream() << "idText : Identifier is null.";
			throw InvalidQueryException("idText : Identifier is null.");
		}
		else if ( !o->isNullTextFile() && !typename _TextFile<EncodingT>::TextFileIDEquality(*(o->getTextFile()))((*save)->getTextFile()) ) {
			values.addInt( o->getTextFile()->getRowid() );
			fields.push_back( C("idText") );
		}
		else if ( o->isNullTextFile() && !(*save)->isNullTextFile() ) {
			m_logger->errorStream() << "idText : null reference is forbidden.";
			throw InvalidQueryException("idText : null reference is forbidden.");
		}
		if (!fields.empty()) {
			statement.swap( connection->update(C("textNotice"), fields, C("rowid = ") /*+ C("\'") */+ C(ToString::parse(o->getRowid()))/* + C("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, C("textNotice"), o);
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
_TextNoticeAccess<EncodingT>::insertTextNotice(boost::shared_ptr< _TextNotice<EncodingT> > o)  
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
		values.addText( o->getDescription() );
		fields.push_back( C("description") );
		values.addText( o->getCategory() );
		fields.push_back( C("category") );
		values.addInt( o->getLineNumber() );
		fields.push_back( C("lineNumber") );
		if ( !o->isNullTextFile() && typename _TextFile<EncodingT>::TextFileIDEquality(-1)(o->getTextFile()) ) {
			m_logger->errorStream() << "idText : Identifier is null.";
			throw InvalidQueryException("idText : Identifier is null.");
		}
		else if ( !o->isNullTextFile() ) {
			values.addInt( o->getTextFile()->getRowid() );
			fields.push_back( C("idText") );
		}
		else {
			m_logger->errorStream() << "idText : null reference is forbidden.";
			throw InvalidQueryException("idText : null reference is forbidden.");
		}
		values.addInt( o->getStartBlock() );
		fields.push_back( C("startBlock") );
		values.addInt( o->getLengthBlock() );
		fields.push_back( C("lengthBlock") );
		statement.swap( connection->insert(C("textNotice"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		int id = connection->getLastInsertID();
		o->setRowid(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, C("textNotice"), o);
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
_TextNoticeAccess<EncodingT>::deleteTextNotice(boost::shared_ptr< _TextNotice<EncodingT> > o)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	_DataStatement<EncodingT> statement;
	if ( o->getRowid()==-1 ) {
		m_logger->errorStream() << "Rowid : Identifier is null.";
		throw UnIdentifiedObjectException("Rowid : Identifier is null.");
	}
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	typename _TextNotice<EncodingT>::TextNoticeIDEquality TextNoticeIdEquality(*o);
	typename std::vector< boost::shared_ptr< _TextNotice<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), TextNoticeIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before deletion.";
		throw UnSelectedObjectException("You must select object before deletion.");
	}
	try {
		statement.swap( connection->deleteFrom(C("textNotice"), C("rowid = ") /*+ C("\'") */+ C(ToString::parse(o->getRowid()))/* + C("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, C("textNotice"), o);
		if (connection->isTransactionInProgress() && m_transactionOwner) {
			connection->commit();
			m_transactionOwner = false;
			m_transactionSignal(OPERATION_ACCESS_COMMIT);
		}
		m_backup.erase(save);
		o->setRowid(-1);
	} catch (...) {
		if (m_transactionOwner) {
			cancelSelection();
		}
		throw;
	}
}

template<class EncodingT>
typename _TextNoticeAccess<EncodingT>::connection_t
_TextNoticeAccess<EncodingT>::addInsertSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_insertSignal.connect(subscriber);
}

template<class EncodingT>
typename _TextNoticeAccess<EncodingT>::connection_t
_TextNoticeAccess<EncodingT>::addUpdateSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_updateSignal.connect(subscriber);
}

template<class EncodingT>
typename _TextNoticeAccess<EncodingT>::connection_t
_TextNoticeAccess<EncodingT>::addDeleteSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_deleteSignal.connect(subscriber);
}

template<class EncodingT>
typename _TextNoticeAccess<EncodingT>::connection_t
_TextNoticeAccess<EncodingT>::addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber)  
{
	return m_transactionSignal.connect(subscriber);
}

template<class EncodingT>
void
_TextNoticeAccess<EncodingT>::removeInsertSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_TextNoticeAccess<EncodingT>::removeUpdateSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_TextNoticeAccess<EncodingT>::removeDeleteSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_TextNoticeAccess<EncodingT>::removeTransactionSignal(connection_t connection)  
{
	connection.disconnect();
}


NAMESPACE_END

#undef C
#undef A

