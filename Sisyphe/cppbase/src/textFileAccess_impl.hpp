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
	columns.push_back(UCS("rowid"));
	columns.push_back(UCS("content"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,UCS("textFile")), filter) );
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
	std::vector< boost::shared_ptr< _TextFile<EncodingT> > > result = getManyTextFiles(UCS("rowid = ") /*+ UCS("\'") */+ C(ToString::parse(rowid))/* + UCS("\'")*/);
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
	columns.push_back(UCS("rowid"));
	columns.push_back(UCS("content"));
	if (!addition || !connection->isTransactionInProgress()) {
		cancelSelection();
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
	}
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,UCS("textFile")), filter, nowait) );
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
boost::shared_ptr< _TextFile<EncodingT> >
_TextFileAccess<EncodingT>::selectOneTextFile(long long rowid, bool nowait, bool addition)  
{
	if ( rowid==-1 ) {
		m_logger->errorStream() << "Rowid : Identifier is null.";
		throw UnIdentifiedObjectException("Rowid : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _TextFile<EncodingT> > > result = selectManyTextFiles(UCS("rowid = ") /*+ UCS("\'") */+ C(ToString::parse(rowid))/* + UCS("\'")*/, nowait, addition);
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
	return (!m_backup.empty() && (m_backup.find(o) != m_backup.end()));
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
	_CppFileAccess<EncodingT>* cppFileAccess = _CppFileAccess<EncodingT>::getInstance();
	if (!cppFileAccess) {
		m_logger->errorStream() << "CppFileAccess class is not initialized.";
		throw NullPointerException("CppFileAccess class is not initialized.");
	}
	_DebugFileInfoAccess<EncodingT>* debugFileInfoAccess = _DebugFileInfoAccess<EncodingT>::getInstance();
	if (!debugFileInfoAccess) {
		m_logger->errorStream() << "DebugFileInfoAccess class is not initialized.";
		throw NullPointerException("DebugFileInfoAccess class is not initialized.");
	}
	if (!m_backup.empty()) {
		if (connection->isTransactionInProgress() && m_transactionOwner) {
			connection->rollback();
			m_transactionOwner = false;
			m_transactionSignal(OPERATION_ACCESS_ROLLBACK);
		}
		m_backup.clear();
		cppFileAccess->cancelSelection();
		debugFileInfoAccess->cancelSelection();
	}
}

template<class EncodingT>
void
_TextFileAccess<EncodingT>::fillAllCppFiles(boost::shared_ptr< _TextFile<EncodingT> > o, bool nowait)  
{
	fillManyCppFiles(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_TextFileAccess<EncodingT>::fillOneCppFile(boost::shared_ptr< _TextFile<EncodingT> > o, long long identifier, bool nowait)  
{
	fillManyCppFiles(o, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait);
}

template<class EncodingT>
void
_TextFileAccess<EncodingT>::fillManyCppFiles(boost::shared_ptr< _TextFile<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getRowid()==-1 ) {
		m_logger->errorStream() << "Rowid : Identifier is null.";
		throw UnIdentifiedObjectException("Rowid : Identifier is null.");
	}
	_CppFileAccess<EncodingT>* cppFileAccess = _CppFileAccess<EncodingT>::getInstance();
	if (!cppFileAccess) {
		m_logger->errorStream() << "CppFileAccess class is not initialized.";
		throw NullPointerException("CppFileAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _CppFile<EncodingT> > > tab;
	typename EncodingT::string_t cppFileFilter = UCS("idText = ") + C(ToString::parse(o->getRowid()));
	if (!filter.empty()) {
		cppFileFilter += UCS(" AND ") + filter;
	}
	typename backup_t::iterator save = m_backup.find(o);
	if (save != m_backup.end())
	{
		tab = cppFileAccess->selectManyCppFiles(cppFileFilter, nowait, true);
		(*save)->clearCppFiles();
		(*save)->insertCppFile((*save)->getCppFilesEnd(), tab.begin(), tab.end());
	}
	else
	{
		tab = cppFileAccess->getManyCppFiles(cppFileFilter);
	}
	o->clearCppFiles();
	o->insertCppFile(o->getCppFilesEnd(), tab.begin(), tab.end());
}

template<class EncodingT>
void
_TextFileAccess<EncodingT>::fillAllDebugFileInfos(boost::shared_ptr< _TextFile<EncodingT> > o, bool nowait)  
{
	fillManyDebugFileInfos(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_TextFileAccess<EncodingT>::fillOneDebugFileInfo(boost::shared_ptr< _TextFile<EncodingT> > o, long long identifier, bool nowait)  
{
	fillManyDebugFileInfos(o, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait);
}

template<class EncodingT>
void
_TextFileAccess<EncodingT>::fillManyDebugFileInfos(boost::shared_ptr< _TextFile<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getRowid()==-1 ) {
		m_logger->errorStream() << "Rowid : Identifier is null.";
		throw UnIdentifiedObjectException("Rowid : Identifier is null.");
	}
	_DebugFileInfoAccess<EncodingT>* debugFileInfoAccess = _DebugFileInfoAccess<EncodingT>::getInstance();
	if (!debugFileInfoAccess) {
		m_logger->errorStream() << "DebugFileInfoAccess class is not initialized.";
		throw NullPointerException("DebugFileInfoAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _DebugFileInfo<EncodingT> > > tab;
	typename EncodingT::string_t debugFileInfoFilter = UCS("idText = ") + C(ToString::parse(o->getRowid()));
	if (!filter.empty()) {
		debugFileInfoFilter += UCS(" AND ") + filter;
	}
	typename backup_t::iterator save = m_backup.find(o);
	if (save != m_backup.end())
	{
		tab = debugFileInfoAccess->selectManyDebugFileInfos(debugFileInfoFilter, nowait, true);
		(*save)->clearDebugFileInfos();
		(*save)->insertDebugFileInfo((*save)->getDebugFileInfosEnd(), tab.begin(), tab.end());
	}
	else
	{
		tab = debugFileInfoAccess->getManyDebugFileInfos(debugFileInfoFilter);
	}
	o->clearDebugFileInfos();
	o->insertDebugFileInfo(o->getDebugFileInfosEnd(), tab.begin(), tab.end());
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
	_CppFileAccess<EncodingT>* cppFileAccess = _CppFileAccess<EncodingT>::getInstance();
	if (!cppFileAccess) {
		m_logger->errorStream() << "CppFileAccess class is not initialized.";
		throw NullPointerException("CppFileAccess class is not initialized.");
	}
	_DebugFileInfoAccess<EncodingT>* debugFileInfoAccess = _DebugFileInfoAccess<EncodingT>::getInstance();
	if (!debugFileInfoAccess) {
		m_logger->errorStream() << "DebugFileInfoAccess class is not initialized.";
		throw NullPointerException("DebugFileInfoAccess class is not initialized.");
	}
	typename backup_t::const_iterator save = m_backup.find(o);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getContent() != o->getContent());
	typename _TextFile<EncodingT>::CppFileIterator cppFile;
	for ( cppFile=o->getCppFilesBeginning(); cppFile!=o->getCppFilesEnd(); ++cppFile ) {
		if (!(*cppFile)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(*(*cppFile));
		bUpdate = bUpdate || (std::find_if((*save)->getCppFilesBeginning(), (*save)->getCppFilesEnd(), cppFileIdEquality) == (*save)->getCppFilesEnd())
			|| (cppFileAccess->isModifiedCppFile(*cppFile));
	}
	for ( cppFile=(*save)->getCppFilesBeginning(); cppFile<(*save)->getCppFilesEnd(); ++cppFile ) {
		if (!(*cppFile)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(*(*cppFile));
		bUpdate = bUpdate || (std::find_if(o->getCppFilesBeginning(), o->getCppFilesEnd(), cppFileIdEquality) == o->getCppFilesEnd());
	}
	typename _TextFile<EncodingT>::DebugFileInfoIterator debugFileInfo;
	for ( debugFileInfo=o->getDebugFileInfosBeginning(); debugFileInfo!=o->getDebugFileInfosEnd(); ++debugFileInfo ) {
		if (!(*debugFileInfo)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _DebugFileInfo<EncodingT>::DebugFileInfoIDEquality debugFileInfoIdEquality(*(*debugFileInfo));
		bUpdate = bUpdate || (std::find_if((*save)->getDebugFileInfosBeginning(), (*save)->getDebugFileInfosEnd(), debugFileInfoIdEquality) == (*save)->getDebugFileInfosEnd())
			|| (debugFileInfoAccess->isModifiedDebugFileInfo(*debugFileInfo));
	}
	for ( debugFileInfo=(*save)->getDebugFileInfosBeginning(); debugFileInfo<(*save)->getDebugFileInfosEnd(); ++debugFileInfo ) {
		if (!(*debugFileInfo)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _DebugFileInfo<EncodingT>::DebugFileInfoIDEquality debugFileInfoIdEquality(*(*debugFileInfo));
		bUpdate = bUpdate || (std::find_if(o->getDebugFileInfosBeginning(), o->getDebugFileInfosEnd(), debugFileInfoIdEquality) == o->getDebugFileInfosEnd());
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
	_CppFileAccess<EncodingT>* cppFileAccess = _CppFileAccess<EncodingT>::getInstance();
	if (!cppFileAccess) {
		m_logger->errorStream() << "CppFileAccess class is not initialized.";
		throw NullPointerException("CppFileAccess class is not initialized.");
	}
	_DebugFileInfoAccess<EncodingT>* debugFileInfoAccess = _DebugFileInfoAccess<EncodingT>::getInstance();
	if (!debugFileInfoAccess) {
		m_logger->errorStream() << "DebugFileInfoAccess class is not initialized.";
		throw NullPointerException("DebugFileInfoAccess class is not initialized.");
	}
	typename backup_t::iterator save = m_backup.find(o);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	try {
		if ( (*save)->getContent() != o->getContent() ) {
			values.addText( o->getContent() );
			fields.push_back( UCS("content") );
		}
		std::vector< boost::shared_ptr< _CppFile<EncodingT> > > listOfCppFileToAdd;
		std::vector< boost::shared_ptr< _CppFile<EncodingT> > > listOfCppFileToUpdate;
		typename _TextFile<EncodingT>::CppFileIterator cppFile;
		for ( cppFile=o->getCppFilesBeginning(); cppFile!=o->getCppFilesEnd(); ++cppFile ) {
			if (!(*cppFile)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*cppFile)->setTextFile(o);
			typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(*(*cppFile));
			if ( std::find_if((*save)->getCppFilesBeginning(), (*save)->getCppFilesEnd(), cppFileIdEquality) == (*save)->getCppFilesEnd()) {
				listOfCppFileToAdd.push_back(*cppFile);
			}
			else {
				if (cppFileAccess->isModifiedCppFile(*cppFile))
					listOfCppFileToUpdate.push_back(*cppFile);
			}
		}
		std::vector< boost::shared_ptr< _CppFile<EncodingT> > > listOfCppFileToRemove;
		for ( cppFile=(*save)->getCppFilesBeginning(); cppFile<(*save)->getCppFilesEnd(); ++cppFile ) {
			if (!(*cppFile)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(*(*cppFile));
			if ( std::find_if(o->getCppFilesBeginning(), o->getCppFilesEnd(), cppFileIdEquality) == o->getCppFilesEnd()) {
				listOfCppFileToRemove.push_back(*cppFile);
			}
		}
		std::vector< boost::shared_ptr< _DebugFileInfo<EncodingT> > > listOfDebugFileInfoToAdd;
		std::vector< boost::shared_ptr< _DebugFileInfo<EncodingT> > > listOfDebugFileInfoToUpdate;
		typename _TextFile<EncodingT>::DebugFileInfoIterator debugFileInfo;
		for ( debugFileInfo=o->getDebugFileInfosBeginning(); debugFileInfo!=o->getDebugFileInfosEnd(); ++debugFileInfo ) {
			if (!(*debugFileInfo)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*debugFileInfo)->setTextFile(o);
			typename _DebugFileInfo<EncodingT>::DebugFileInfoIDEquality debugFileInfoIdEquality(*(*debugFileInfo));
			if ( std::find_if((*save)->getDebugFileInfosBeginning(), (*save)->getDebugFileInfosEnd(), debugFileInfoIdEquality) == (*save)->getDebugFileInfosEnd()) {
				listOfDebugFileInfoToAdd.push_back(*debugFileInfo);
			}
			else {
				if (debugFileInfoAccess->isModifiedDebugFileInfo(*debugFileInfo))
					listOfDebugFileInfoToUpdate.push_back(*debugFileInfo);
			}
		}
		std::vector< boost::shared_ptr< _DebugFileInfo<EncodingT> > > listOfDebugFileInfoToRemove;
		for ( debugFileInfo=(*save)->getDebugFileInfosBeginning(); debugFileInfo<(*save)->getDebugFileInfosEnd(); ++debugFileInfo ) {
			if (!(*debugFileInfo)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			typename _DebugFileInfo<EncodingT>::DebugFileInfoIDEquality debugFileInfoIdEquality(*(*debugFileInfo));
			if ( std::find_if(o->getDebugFileInfosBeginning(), o->getDebugFileInfosEnd(), debugFileInfoIdEquality) == o->getDebugFileInfosEnd()) {
				listOfDebugFileInfoToRemove.push_back(*debugFileInfo);
			}
		}
		if (!fields.empty()) {
			statement.swap( connection->update(UCS("textFile"), fields, UCS("rowid = ") /*+ UCS("\'") */+ C(ToString::parse(o->getRowid()))/* + UCS("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, UCS("textFile"), o);
		}
		for ( cppFile=listOfCppFileToAdd.begin(); cppFile!=listOfCppFileToAdd.end() ; ++cppFile ) {
			cppFileAccess->insertCppFile(*cppFile);
		}
		for ( cppFile=listOfCppFileToUpdate.begin(); cppFile!=listOfCppFileToUpdate.end() ; ++cppFile ) {
			cppFileAccess->updateCppFile(*cppFile);
		}
		for ( cppFile=listOfCppFileToRemove.begin(); cppFile!=listOfCppFileToRemove.end() ; ++cppFile ) {
			cppFileAccess->deleteCppFile(*cppFile);
		}
		for ( debugFileInfo=listOfDebugFileInfoToAdd.begin(); debugFileInfo!=listOfDebugFileInfoToAdd.end() ; ++debugFileInfo ) {
			debugFileInfoAccess->insertDebugFileInfo(*debugFileInfo);
		}
		for ( debugFileInfo=listOfDebugFileInfoToUpdate.begin(); debugFileInfo!=listOfDebugFileInfoToUpdate.end() ; ++debugFileInfo ) {
			debugFileInfoAccess->updateDebugFileInfo(*debugFileInfo);
		}
		for ( debugFileInfo=listOfDebugFileInfoToRemove.begin(); debugFileInfo!=listOfDebugFileInfoToRemove.end() ; ++debugFileInfo ) {
			debugFileInfoAccess->deleteDebugFileInfo(*debugFileInfo);
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
	_CppFileAccess<EncodingT>* cppFileAccess = _CppFileAccess<EncodingT>::getInstance();
	if (!cppFileAccess) {
		m_logger->errorStream() << "CppFileAccess class is not initialized.";
		throw NullPointerException("CppFileAccess class is not initialized.");
	}
	_DebugFileInfoAccess<EncodingT>* debugFileInfoAccess = _DebugFileInfoAccess<EncodingT>::getInstance();
	if (!debugFileInfoAccess) {
		m_logger->errorStream() << "DebugFileInfoAccess class is not initialized.";
		throw NullPointerException("DebugFileInfoAccess class is not initialized.");
	}
	try {
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
		values.addText( o->getContent() );
		fields.push_back( UCS("content") );
		statement.swap( connection->insert(UCS("textFile"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		int id = connection->getLastInsertID();
		o->setRowid(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, UCS("textFile"), o);
		typename _TextFile<EncodingT>::CppFileIterator cppFile;
		for ( cppFile=o->getCppFilesBeginning(); cppFile!=o->getCppFilesEnd(); ++cppFile ) {
			(*cppFile)->setTextFile(o);
			cppFileAccess->insertCppFile(*cppFile);
		}
		typename _TextFile<EncodingT>::DebugFileInfoIterator debugFileInfo;
		for ( debugFileInfo=o->getDebugFileInfosBeginning(); debugFileInfo!=o->getDebugFileInfosEnd(); ++debugFileInfo ) {
			(*debugFileInfo)->setTextFile(o);
			debugFileInfoAccess->insertDebugFileInfo(*debugFileInfo);
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
	_CppFileAccess<EncodingT>* cppFileAccess = _CppFileAccess<EncodingT>::getInstance();
	if (!cppFileAccess) {
		m_logger->errorStream() << "CppFileAccess class is not initialized.";
		throw NullPointerException("CppFileAccess class is not initialized.");
	}
	_DebugFileInfoAccess<EncodingT>* debugFileInfoAccess = _DebugFileInfoAccess<EncodingT>::getInstance();
	if (!debugFileInfoAccess) {
		m_logger->errorStream() << "DebugFileInfoAccess class is not initialized.";
		throw NullPointerException("DebugFileInfoAccess class is not initialized.");
	}
	typename backup_t::iterator save = m_backup.find(o);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before deletion.";
		throw UnSelectedObjectException("You must select object before deletion.");
	}
	try {
		typename _TextFile<EncodingT>::CppFileIterator cppFile;
		fillAllCppFiles(o);
		for ( cppFile=o->getCppFilesBeginning(); cppFile!=o->getCppFilesEnd(); ++cppFile ) {
			cppFileAccess->deleteCppFile(*cppFile);
		}
		typename _TextFile<EncodingT>::DebugFileInfoIterator debugFileInfo;
		fillAllDebugFileInfos(o);
		for ( debugFileInfo=o->getDebugFileInfosBeginning(); debugFileInfo!=o->getDebugFileInfosEnd(); ++debugFileInfo ) {
			debugFileInfoAccess->deleteDebugFileInfo(*debugFileInfo);
		}
		statement.swap( connection->deleteFrom(UCS("textFile"), UCS("rowid = ") /*+ UCS("\'") */+ C(ToString::parse(o->getRowid()))/* + UCS("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, UCS("textFile"), o);
		if (connection->isTransactionInProgress() && m_transactionOwner) {
			connection->commit();
			m_transactionOwner = false;
			cancelSelection();
			m_transactionSignal(OPERATION_ACCESS_COMMIT);
		}
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

