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
_TextFileAccess<EncodingT>* _TextFileAccess<EncodingT>::m_instance = NULL;

template<class EncodingT>
_TextFileAccess<EncodingT>* 
_TextFileAccess<EncodingT>::getInstance()  
{
	if (m_instance == NULL) {
		m_instance = new _TextFileAccess<EncodingT>();
	}
	return m_instance;
}

template<class EncodingT>
_TextFileAccess<EncodingT>::_TextFileAccess()
: m_transactionOwner(false) 
{
	m_logger = &Category::getInstance(LOGNAME);
	m_logger->debugStream() << "constructor TextFileAccess " << m_transactionOwner;
}

template<class EncodingT>
_TextFileAccess<EncodingT>::~_TextFileAccess()
{
	cancelSelection();
	m_logger = NULL;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _TextFile<EncodingT> > >
_TextFileAccess<EncodingT>::getManyTextFiles(typename EncodingT::string_t const&  filter) const 
{
	boost::shared_ptr< _TextFile<EncodingT> > value;
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _TextFile<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(C("rowid"));
	columns.push_back(C("content"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,C("textFile")), filter) );
	while( statement.executeStep() ) {
		long long rowid;
		typename EncodingT::string_t content;
		if (statement.getInt64( 0, rowid ) &&
			statement.getText( 1, content )) {
			value.reset(new _TextFile<EncodingT>(
				rowid,
				content));
			tab.push_back(value);
		}
	}
	return tab;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _TextFile<EncodingT> > >
_TextFileAccess<EncodingT>::getAllTextFiles() const 
{
	return getManyTextFiles(EncodingT::EMPTY);
}

template<class EncodingT>
boost::shared_ptr< _TextFile<EncodingT> >
_TextFileAccess<EncodingT>::getOneTextFile(long long rowid) const 
{
	if ( rowid==-1 ) {
		m_logger->errorStream() << "Rowid : Identifier is null.";
		throw UnIdentifiedObjectException("Rowid : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _TextFile<EncodingT> > > result = getManyTextFiles(C("rowid = ") /*+ C("\'") */+ C(ToString::parse(rowid))/* + C("\'")*/);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
std::vector< boost::shared_ptr< _TextFile<EncodingT> > >
_TextFileAccess<EncodingT>::selectManyTextFiles(typename EncodingT::string_t const&  filter, bool nowait, bool addition)  
{
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _TextFile<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(C("rowid"));
	columns.push_back(C("content"));
	if (!addition || !connection->isTransactionInProgress()) {
		cancelSelection();
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
	}
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,C("textFile")), filter, nowait) );
	while( statement.executeStep() ) {
		long long rowid;
		typename EncodingT::string_t content;
		if (statement.getInt64( 0, rowid ) &&
			statement.getText( 1, content )) {
			tab.push_back(boost::shared_ptr< _TextFile<EncodingT> >(new _TextFile<EncodingT>(
				rowid,
				content)));
		}
	}
	m_backup.insert(m_backup.end(), tab.begin(), tab.end());
	return copy_ptr(tab);
}

template<class EncodingT>
boost::shared_ptr< _TextFile<EncodingT> >
_TextFileAccess<EncodingT>::selectOneTextFile(long long rowid, bool nowait, bool addition)  
{
	if ( rowid==-1 ) {
		m_logger->errorStream() << "Rowid : Identifier is null.";
		throw UnIdentifiedObjectException("Rowid : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _TextFile<EncodingT> > > result = selectManyTextFiles(C("rowid = ") /*+ C("\'") */+ C(ToString::parse(rowid))/* + C("\'")*/, nowait, addition);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
bool
_TextFileAccess<EncodingT>::isSelectedTextFile(boost::shared_ptr< _TextFile<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getRowid()==-1 ) {
		m_logger->errorStream() << "Rowid : Identifier is null.";
		throw UnIdentifiedObjectException("Rowid : Identifier is null.");
	}
	typename _TextFile<EncodingT>::TextFileIDEquality textFileIdEquality(*o);
	return (!m_backup.empty() && (std::find_if(m_backup.begin(), m_backup.end(), textFileIdEquality)!=m_backup.end()));
}

template<class EncodingT>
void
_TextFileAccess<EncodingT>::cancelSelection()  
{
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	_TextNoticeAccess<EncodingT>* textNoticeAccess = _TextNoticeAccess<EncodingT>::getInstance();
	if (!textNoticeAccess) {
		m_logger->errorStream() << "TextNoticeAccess class is not initialized.";
		throw NullPointerException("TextNoticeAccess class is not initialized.");
	}
	if (!m_backup.empty()) {
		if (connection->isTransactionInProgress() && m_transactionOwner) {
			connection->rollback();
			m_transactionOwner = false;
			m_transactionSignal(OPERATION_ACCESS_ROLLBACK);
		}
		m_backup.clear();
		textNoticeAccess->cancelSelection();
	}
}

template<class EncodingT>
void
_TextFileAccess<EncodingT>::fillAllTextNotices(boost::shared_ptr< _TextFile<EncodingT> > o, bool nowait)  
{
	fillManyTextNotices(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_TextFileAccess<EncodingT>::fillOneTextNotice(boost::shared_ptr< _TextFile<EncodingT> > o, long long rowid, bool nowait)  
{
	fillManyTextNotices(o, C("rowid = ") /*+ C("\'") */+ C(ToString::parse(rowid))/* + C("\'")*/, nowait);
}

template<class EncodingT>
void
_TextFileAccess<EncodingT>::fillManyTextNotices(boost::shared_ptr< _TextFile<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getRowid()==-1 ) {
		m_logger->errorStream() << "Rowid : Identifier is null.";
		throw UnIdentifiedObjectException("Rowid : Identifier is null.");
	}
	_TextNoticeAccess<EncodingT>* textNoticeAccess = _TextNoticeAccess<EncodingT>::getInstance();
	if (!textNoticeAccess) {
		m_logger->errorStream() << "TextNoticeAccess class is not initialized.";
		throw NullPointerException("TextNoticeAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _TextNotice<EncodingT> > > tab;
	typename EncodingT::string_t textNoticeFilter = C("idText = ") + C(ToString::parse(o->getRowid()));
	if (!filter.empty()) {
		textNoticeFilter += C(" AND ") + filter;
	}
	typename _TextFile<EncodingT>::TextFileIDEquality textFileIdEquality(o->getRowid());
	typename std::vector< boost::shared_ptr< _TextFile<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), textFileIdEquality);
	if (save != m_backup.end())
	{
		tab = textNoticeAccess->selectManyTextNotices(textNoticeFilter, nowait);
		(*save)->clearTextNotices();
		(*save)->insertTextNotice((*save)->getTextNoticesEnd(), tab.begin(), tab.end());
	}
	else
	{
		tab = textNoticeAccess->getManyTextNotices(textNoticeFilter);
	}
	o->clearTextNotices();
	o->insertTextNotice(o->getTextNoticesEnd(), tab.begin(), tab.end());
}

template<class EncodingT>
bool
_TextFileAccess<EncodingT>::isModifiedTextFile(boost::shared_ptr< _TextFile<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getRowid()==-1 ) {
		m_logger->errorStream() << "Rowid : Identifier is null.";
		throw UnIdentifiedObjectException("Rowid : Identifier is null.");
	}
	_TextNoticeAccess<EncodingT>* textNoticeAccess = _TextNoticeAccess<EncodingT>::getInstance();
	if (!textNoticeAccess) {
		m_logger->errorStream() << "TextNoticeAccess class is not initialized.";
		throw NullPointerException("TextNoticeAccess class is not initialized.");
	}
	typename _TextFile<EncodingT>::TextFileIDEquality textFileIdEquality(*o);
	typename std::vector< boost::shared_ptr< _TextFile<EncodingT> > >::const_iterator save = std::find_if(m_backup.begin(), m_backup.end(), textFileIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getContent() != o->getContent());
	typename _TextFile<EncodingT>::TextNoticeIterator textNotice;
	for ( textNotice=o->getTextNoticesBeginning(); textNotice!=o->getTextNoticesEnd(); ++textNotice ) {
		if (!(*textNotice)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _TextNotice<EncodingT>::TextNoticeIDEquality textNoticeIdEquality(*(*textNotice));
		bUpdate = bUpdate || (std::find_if((*save)->getTextNoticesBeginning(), (*save)->getTextNoticesEnd(), textNoticeIdEquality) == (*save)->getTextNoticesEnd())
			|| (textNoticeAccess->isModifiedTextNotice(*textNotice));
	}
	for ( textNotice=(*save)->getTextNoticesBeginning(); textNotice<(*save)->getTextNoticesEnd(); ++textNotice ) {
		if (!(*textNotice)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _TextNotice<EncodingT>::TextNoticeIDEquality textNoticeIdEquality(*(*textNotice));
		bUpdate = bUpdate || (std::find_if(o->getTextNoticesBeginning(), o->getTextNoticesEnd(), textNoticeIdEquality) == o->getTextNoticesEnd());
	}
	return bUpdate;
}

template<class EncodingT>
void
_TextFileAccess<EncodingT>::updateTextFile(boost::shared_ptr< _TextFile<EncodingT> > o)  
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
	_TextNoticeAccess<EncodingT>* textNoticeAccess = _TextNoticeAccess<EncodingT>::getInstance();
	if (!textNoticeAccess) {
		m_logger->errorStream() << "TextNoticeAccess class is not initialized.";
		throw NullPointerException("TextNoticeAccess class is not initialized.");
	}
	typename _TextFile<EncodingT>::TextFileIDEquality textFileIdEquality(*o);
	typename std::vector< boost::shared_ptr< _TextFile<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), textFileIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	try {
		if ( (*save)->getContent() != o->getContent() ) {
			values.addText( o->getContent() );
			fields.push_back( C("content") );
		}
		std::vector< boost::shared_ptr< _TextNotice<EncodingT> > > listOfTextNoticeToAdd;
		std::vector< boost::shared_ptr< _TextNotice<EncodingT> > > listOfTextNoticeToUpdate;
		typename _TextFile<EncodingT>::TextNoticeIterator textNotice;
		for ( textNotice=o->getTextNoticesBeginning(); textNotice!=o->getTextNoticesEnd(); ++textNotice ) {
			if (!(*textNotice)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*textNotice)->setTextFile(o);
			typename _TextNotice<EncodingT>::TextNoticeIDEquality textNoticeIdEquality(*(*textNotice));
			if ( std::find_if((*save)->getTextNoticesBeginning(), (*save)->getTextNoticesEnd(), textNoticeIdEquality) == (*save)->getTextNoticesEnd()) {
				listOfTextNoticeToAdd.push_back(*textNotice);
			}
			else {
				if (textNoticeAccess->isModifiedTextNotice(*textNotice))
					listOfTextNoticeToUpdate.push_back(*textNotice);
			}
		}
		std::vector< boost::shared_ptr< _TextNotice<EncodingT> > > listOfTextNoticeToRemove;
		for ( textNotice=(*save)->getTextNoticesBeginning(); textNotice<(*save)->getTextNoticesEnd(); ++textNotice ) {
			if (!(*textNotice)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			typename _TextNotice<EncodingT>::TextNoticeIDEquality textNoticeIdEquality(*(*textNotice));
			if ( std::find_if(o->getTextNoticesBeginning(), o->getTextNoticesEnd(), textNoticeIdEquality) == o->getTextNoticesEnd()) {
				listOfTextNoticeToRemove.push_back(*textNotice);
			}
		}
		if (!fields.empty()) {
			statement.swap( connection->update(C("textFile"), fields, C("rowid = ") /*+ C("\'") */+ C(ToString::parse(o->getRowid()))/* + C("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, C("textFile"), o);
		}
		for ( textNotice=listOfTextNoticeToAdd.begin(); textNotice!=listOfTextNoticeToAdd.end() ; ++textNotice ) {
			textNoticeAccess->insertTextNotice(*textNotice);
		}
		for ( textNotice=listOfTextNoticeToUpdate.begin(); textNotice!=listOfTextNoticeToUpdate.end() ; ++textNotice ) {
			textNoticeAccess->updateTextNotice(*textNotice);
		}
		for ( textNotice=listOfTextNoticeToRemove.begin(); textNotice!=listOfTextNoticeToRemove.end() ; ++textNotice ) {
			textNoticeAccess->deleteTextNotice(*textNotice);
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
_TextFileAccess<EncodingT>::insertTextFile(boost::shared_ptr< _TextFile<EncodingT> > o)  
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
	_TextNoticeAccess<EncodingT>* textNoticeAccess = _TextNoticeAccess<EncodingT>::getInstance();
	if (!textNoticeAccess) {
		m_logger->errorStream() << "TextNoticeAccess class is not initialized.";
		throw NullPointerException("TextNoticeAccess class is not initialized.");
	}
	try {
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
		values.addText( o->getContent() );
		fields.push_back( C("content") );
		statement.swap( connection->insert(C("textFile"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		int id = connection->getLastInsertID();
		o->setRowid(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, C("textFile"), o);
		typename _TextFile<EncodingT>::TextNoticeIterator textNotice;
		for ( textNotice=o->getTextNoticesBeginning(); textNotice!=o->getTextNoticesEnd(); ++textNotice ) {
			(*textNotice)->setTextFile(o);
			textNoticeAccess->insertTextNotice(*textNotice);
		}
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
_TextFileAccess<EncodingT>::deleteTextFile(boost::shared_ptr< _TextFile<EncodingT> > o)  
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
	_TextNoticeAccess<EncodingT>* textNoticeAccess = _TextNoticeAccess<EncodingT>::getInstance();
	if (!textNoticeAccess) {
		m_logger->errorStream() << "TextNoticeAccess class is not initialized.";
		throw NullPointerException("TextNoticeAccess class is not initialized.");
	}
	_CppFileAccess<EncodingT>* cppFileAccess = _CppFileAccess<EncodingT>::getInstance();
	if (!cppFileAccess) {
		m_logger->errorStream() << "CppFileAccess class is not initialized.";
		throw NullPointerException("CppFileAccess class is not initialized.");
	}
	typename _TextFile<EncodingT>::TextFileIDEquality TextFileIdEquality(*o);
	typename std::vector< boost::shared_ptr< _TextFile<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), TextFileIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before deletion.";
		throw UnSelectedObjectException("You must select object before deletion.");
	}
	try {
		typename _TextFile<EncodingT>::TextNoticeIterator textNotice;
		fillAllTextNotices(o);
		for ( textNotice=o->getTextNoticesBeginning(); textNotice!=o->getTextNoticesEnd(); ++textNotice ) {
			textNoticeAccess->deleteTextNotice(*textNotice);
		}
		statement.swap( connection->deleteFrom(C("textFile"), C("rowid = ") /*+ C("\'") */+ C(ToString::parse(o->getRowid()))/* + C("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, C("textFile"), o);
		if (connection->isTransactionInProgress() && m_transactionOwner) {
			cppFileAccess->deleteCppFile(cppFileAccess->selectOneCppFile(o), false);
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
typename _TextFileAccess<EncodingT>::connection_t
_TextFileAccess<EncodingT>::addInsertSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_insertSignal.connect(subscriber);
}

template<class EncodingT>
typename _TextFileAccess<EncodingT>::connection_t
_TextFileAccess<EncodingT>::addUpdateSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_updateSignal.connect(subscriber);
}

template<class EncodingT>
typename _TextFileAccess<EncodingT>::connection_t
_TextFileAccess<EncodingT>::addDeleteSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_deleteSignal.connect(subscriber);
}

template<class EncodingT>
typename _TextFileAccess<EncodingT>::connection_t
_TextFileAccess<EncodingT>::addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber)  
{
	return m_transactionSignal.connect(subscriber);
}

template<class EncodingT>
void
_TextFileAccess<EncodingT>::removeInsertSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_TextFileAccess<EncodingT>::removeUpdateSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_TextFileAccess<EncodingT>::removeDeleteSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_TextFileAccess<EncodingT>::removeTransactionSignal(connection_t connection)  
{
	connection.disconnect();
}


NAMESPACE_END

#undef C
#undef A

