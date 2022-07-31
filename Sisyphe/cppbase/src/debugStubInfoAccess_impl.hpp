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
_DebugStubInfoAccess<EncodingT>* _DebugStubInfoAccess<EncodingT>::m_instance = NULL;

template<class EncodingT>
_DebugStubInfoAccess<EncodingT>* 
_DebugStubInfoAccess<EncodingT>::getInstance()  
{
	if (m_instance == NULL) {
		m_instance = new _DebugStubInfoAccess<EncodingT>();
	}
	return m_instance;
}

template<class EncodingT>
_DebugStubInfoAccess<EncodingT>::_DebugStubInfoAccess()
: m_transactionOwner(false) 
{
	m_logger = &Category::getInstance(LOGNAME);
	m_logger->debugStream() << "constructor DebugStubInfoAccess " << m_transactionOwner;
}

template<class EncodingT>
_DebugStubInfoAccess<EncodingT>::~_DebugStubInfoAccess()
{
	cancelSelection();
	m_logger = NULL;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _DebugStubInfo<EncodingT> > >
_DebugStubInfoAccess<EncodingT>::getManyDebugStubInfos(typename EncodingT::string_t const&  filter) const 
{
	boost::shared_ptr< _DebugStubInfo<EncodingT> > value;
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _DebugStubInfo<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("lineNumber"));
	columns.push_back(UCS("isLineSkipped"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,UCS("debugStubInfo")), filter) );
	while( statement.executeStep() ) {
		long long identifier;
		long long lineNumber;
		long long isLineSkipped;
		if (statement.getInt64( 0, identifier ) &&
			statement.getInt64( 1, lineNumber ) &&
			statement.getInt64( 2, isLineSkipped )) {
			value.reset(new _DebugStubInfo<EncodingT>(
				identifier,
				lineNumber,
				isLineSkipped));
			tab.push_back(value);
		}
	}
	return tab;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _DebugStubInfo<EncodingT> > >
_DebugStubInfoAccess<EncodingT>::getAllDebugStubInfos() const 
{
	return getManyDebugStubInfos(EncodingT::EMPTY);
}

template<class EncodingT>
boost::shared_ptr< _DebugStubInfo<EncodingT> >
_DebugStubInfoAccess<EncodingT>::getOneDebugStubInfo(long long identifier) const 
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _DebugStubInfo<EncodingT> > > result = getManyDebugStubInfos(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
std::vector< boost::shared_ptr< _DebugStubInfo<EncodingT> > >
_DebugStubInfoAccess<EncodingT>::selectManyDebugStubInfos(typename EncodingT::string_t const&  filter, bool nowait, bool addition)  
{
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _DebugStubInfo<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("lineNumber"));
	columns.push_back(UCS("isLineSkipped"));
	if (!addition || !connection->isTransactionInProgress()) {
		cancelSelection();
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
	}
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,UCS("debugStubInfo")), filter, nowait) );
	while( statement.executeStep() ) {
		long long identifier;
		long long lineNumber;
		long long isLineSkipped;
		if (statement.getInt64( 0, identifier ) &&
			statement.getInt64( 1, lineNumber ) &&
			statement.getInt64( 2, isLineSkipped )) {
			tab.push_back(boost::shared_ptr< _DebugStubInfo<EncodingT> >(new _DebugStubInfo<EncodingT>(
				identifier,
				lineNumber,
				isLineSkipped)));
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
boost::shared_ptr< _DebugStubInfo<EncodingT> >
_DebugStubInfoAccess<EncodingT>::selectOneDebugStubInfo(long long identifier, bool nowait, bool addition)  
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _DebugStubInfo<EncodingT> > > result = selectManyDebugStubInfos(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait, addition);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
bool
_DebugStubInfoAccess<EncodingT>::isSelectedDebugStubInfo(boost::shared_ptr< _DebugStubInfo<EncodingT> > o) const 
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
_DebugStubInfoAccess<EncodingT>::cancelSelection()  
{
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	_DebugValueInfoAccess<EncodingT>* debugValueInfoAccess = _DebugValueInfoAccess<EncodingT>::getInstance();
	if (!debugValueInfoAccess) {
		m_logger->errorStream() << "DebugValueInfoAccess class is not initialized.";
		throw NullPointerException("DebugValueInfoAccess class is not initialized.");
	}
	if (!m_backup.empty()) {
		if (connection->isTransactionInProgress() && m_transactionOwner) {
			connection->rollback();
			m_transactionOwner = false;
			m_transactionSignal(OPERATION_ACCESS_ROLLBACK);
		}
		m_backup.clear();
		debugValueInfoAccess->cancelSelection();
	}
}

template<class EncodingT>
void
_DebugStubInfoAccess<EncodingT>::fillDebugFileInfo(boost::shared_ptr< _DebugStubInfo<EncodingT> > o)  
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
	_DebugFileInfoAccess<EncodingT>* debugFileInfoAccess = _DebugFileInfoAccess<EncodingT>::getInstance();
	if (!debugFileInfoAccess) {
		m_logger->errorStream() << "DebugFileInfoAccess class is not initialized.";
		throw NullPointerException("DebugFileInfoAccess class is not initialized.");
	}
	long long id;
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,UCS("idDebugFile")), std::vector<typename EncodingT::string_t>(1,UCS("debugStubInfo")), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
	if( statement.executeStep() && statement.getInt64( 0, id ) && id != 0 ) {
		boost::shared_ptr< _DebugFileInfo<EncodingT> > val = debugFileInfoAccess->getOneDebugFileInfo(id);
		typename backup_t::iterator save = m_backup.find(o);
		if (save != m_backup.end()) {
			(*save)->setDebugFileInfo(val);
		}
		o->setDebugFileInfo(val);
	}
	else {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
}

template<class EncodingT>
void
_DebugStubInfoAccess<EncodingT>::fillAllDebugValueInfos(boost::shared_ptr< _DebugStubInfo<EncodingT> > o, bool nowait)  
{
	fillManyDebugValueInfos(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_DebugStubInfoAccess<EncodingT>::fillOneDebugValueInfo(boost::shared_ptr< _DebugStubInfo<EncodingT> > o, long long identifier, bool nowait)  
{
	fillManyDebugValueInfos(o, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait);
}

template<class EncodingT>
void
_DebugStubInfoAccess<EncodingT>::fillManyDebugValueInfos(boost::shared_ptr< _DebugStubInfo<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_DebugValueInfoAccess<EncodingT>* debugValueInfoAccess = _DebugValueInfoAccess<EncodingT>::getInstance();
	if (!debugValueInfoAccess) {
		m_logger->errorStream() << "DebugValueInfoAccess class is not initialized.";
		throw NullPointerException("DebugValueInfoAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _DebugValueInfo<EncodingT> > > tab;
	typename EncodingT::string_t debugValueInfoFilter = UCS("idDebugStub = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		debugValueInfoFilter += UCS(" AND ") + filter;
	}
	typename backup_t::iterator save = m_backup.find(o);
	if (save != m_backup.end())
	{
		tab = debugValueInfoAccess->selectManyDebugValueInfos(debugValueInfoFilter, nowait, true);
		(*save)->clearDebugValueInfos();
		(*save)->insertDebugValueInfo((*save)->getDebugValueInfosEnd(), tab.begin(), tab.end());
	}
	else
	{
		tab = debugValueInfoAccess->getManyDebugValueInfos(debugValueInfoFilter);
	}
	o->clearDebugValueInfos();
	o->insertDebugValueInfo(o->getDebugValueInfosEnd(), tab.begin(), tab.end());
}

template<class EncodingT>
bool
_DebugStubInfoAccess<EncodingT>::isModifiedDebugStubInfo(boost::shared_ptr< _DebugStubInfo<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_DebugValueInfoAccess<EncodingT>* debugValueInfoAccess = _DebugValueInfoAccess<EncodingT>::getInstance();
	if (!debugValueInfoAccess) {
		m_logger->errorStream() << "DebugValueInfoAccess class is not initialized.";
		throw NullPointerException("DebugValueInfoAccess class is not initialized.");
	}
	typename backup_t::const_iterator save = m_backup.find(o);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getLineNumber() != o->getLineNumber());
	bUpdate = bUpdate || ((*save)->getIsLineSkipped() != o->getIsLineSkipped());
	bUpdate = bUpdate || (!(*save)->isNullDebugFileInfo() && !o->isNullDebugFileInfo() && !typename _DebugFileInfo<EncodingT>::DebugFileInfoIDEquality(*(*save)->getDebugFileInfo())(o->getDebugFileInfo()))
		|| ((*save)->isNullDebugFileInfo() && !o->isNullDebugFileInfo()) 
		|| (!(*save)->isNullDebugFileInfo() && o->isNullDebugFileInfo());
	typename _DebugStubInfo<EncodingT>::DebugValueInfoIterator debugValueInfo;
	for ( debugValueInfo=o->getDebugValueInfosBeginning(); debugValueInfo!=o->getDebugValueInfosEnd(); ++debugValueInfo ) {
		if (!(*debugValueInfo)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _DebugValueInfo<EncodingT>::DebugValueInfoIDEquality debugValueInfoIdEquality(*(*debugValueInfo));
		bUpdate = bUpdate || (std::find_if((*save)->getDebugValueInfosBeginning(), (*save)->getDebugValueInfosEnd(), debugValueInfoIdEquality) == (*save)->getDebugValueInfosEnd())
			|| (debugValueInfoAccess->isModifiedDebugValueInfo(*debugValueInfo));
	}
	for ( debugValueInfo=(*save)->getDebugValueInfosBeginning(); debugValueInfo<(*save)->getDebugValueInfosEnd(); ++debugValueInfo ) {
		if (!(*debugValueInfo)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _DebugValueInfo<EncodingT>::DebugValueInfoIDEquality debugValueInfoIdEquality(*(*debugValueInfo));
		bUpdate = bUpdate || (std::find_if(o->getDebugValueInfosBeginning(), o->getDebugValueInfosEnd(), debugValueInfoIdEquality) == o->getDebugValueInfosEnd());
	}
	return bUpdate;
}

template<class EncodingT>
void
_DebugStubInfoAccess<EncodingT>::updateDebugStubInfo(boost::shared_ptr< _DebugStubInfo<EncodingT> > o)  
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
	_DebugValueInfoAccess<EncodingT>* debugValueInfoAccess = _DebugValueInfoAccess<EncodingT>::getInstance();
	if (!debugValueInfoAccess) {
		m_logger->errorStream() << "DebugValueInfoAccess class is not initialized.";
		throw NullPointerException("DebugValueInfoAccess class is not initialized.");
	}
	typename backup_t::iterator save = m_backup.find(o);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	try {
		if ( (*save)->getLineNumber() != o->getLineNumber() ) {
			values.addInt64( o->getLineNumber() );
			fields.push_back( UCS("lineNumber") );
		}
		if ( (*save)->getIsLineSkipped() != o->getIsLineSkipped() ) {
			values.addInt64( o->getIsLineSkipped() );
			fields.push_back( UCS("isLineSkipped") );
		}
		if ( !o->isNullDebugFileInfo() && typename _DebugFileInfo<EncodingT>::DebugFileInfoIDEquality(-1)(o->getDebugFileInfo()) ) {
			m_logger->errorStream() << "idDebugFile : Identifier is null.";
			throw InvalidQueryException("idDebugFile : Identifier is null.");
		}
		else if ( !o->isNullDebugFileInfo() && !typename _DebugFileInfo<EncodingT>::DebugFileInfoIDEquality(*(o->getDebugFileInfo()))((*save)->getDebugFileInfo()) ) {
			values.addInt64( o->getDebugFileInfo()->getIdentifier() );
			fields.push_back( UCS("idDebugFile") );
		}
		else if ( o->isNullDebugFileInfo() && !(*save)->isNullDebugFileInfo() ) {
			m_logger->errorStream() << "idDebugFile : null reference is forbidden.";
			throw InvalidQueryException("idDebugFile : null reference is forbidden.");
		}
		std::vector< boost::shared_ptr< _DebugValueInfo<EncodingT> > > listOfDebugValueInfoToAdd;
		std::vector< boost::shared_ptr< _DebugValueInfo<EncodingT> > > listOfDebugValueInfoToUpdate;
		typename _DebugStubInfo<EncodingT>::DebugValueInfoIterator debugValueInfo;
		for ( debugValueInfo=o->getDebugValueInfosBeginning(); debugValueInfo!=o->getDebugValueInfosEnd(); ++debugValueInfo ) {
			if (!(*debugValueInfo)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*debugValueInfo)->setDebugStubInfo(o);
			typename _DebugValueInfo<EncodingT>::DebugValueInfoIDEquality debugValueInfoIdEquality(*(*debugValueInfo));
			if ( std::find_if((*save)->getDebugValueInfosBeginning(), (*save)->getDebugValueInfosEnd(), debugValueInfoIdEquality) == (*save)->getDebugValueInfosEnd()) {
				listOfDebugValueInfoToAdd.push_back(*debugValueInfo);
			}
			else {
				if (debugValueInfoAccess->isModifiedDebugValueInfo(*debugValueInfo))
					listOfDebugValueInfoToUpdate.push_back(*debugValueInfo);
			}
		}
		std::vector< boost::shared_ptr< _DebugValueInfo<EncodingT> > > listOfDebugValueInfoToRemove;
		for ( debugValueInfo=(*save)->getDebugValueInfosBeginning(); debugValueInfo<(*save)->getDebugValueInfosEnd(); ++debugValueInfo ) {
			if (!(*debugValueInfo)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			typename _DebugValueInfo<EncodingT>::DebugValueInfoIDEquality debugValueInfoIdEquality(*(*debugValueInfo));
			if ( std::find_if(o->getDebugValueInfosBeginning(), o->getDebugValueInfosEnd(), debugValueInfoIdEquality) == o->getDebugValueInfosEnd()) {
				listOfDebugValueInfoToRemove.push_back(*debugValueInfo);
			}
		}
		if (!fields.empty()) {
			statement.swap( connection->update(UCS("debugStubInfo"), fields, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, UCS("debugStubInfo"), o);
		}
		for ( debugValueInfo=listOfDebugValueInfoToAdd.begin(); debugValueInfo!=listOfDebugValueInfoToAdd.end() ; ++debugValueInfo ) {
			debugValueInfoAccess->insertDebugValueInfo(*debugValueInfo);
		}
		for ( debugValueInfo=listOfDebugValueInfoToUpdate.begin(); debugValueInfo!=listOfDebugValueInfoToUpdate.end() ; ++debugValueInfo ) {
			debugValueInfoAccess->updateDebugValueInfo(*debugValueInfo);
		}
		for ( debugValueInfo=listOfDebugValueInfoToRemove.begin(); debugValueInfo!=listOfDebugValueInfoToRemove.end() ; ++debugValueInfo ) {
			debugValueInfoAccess->fillDebugStubInfo(*debugValueInfo);
			(*debugValueInfo)->eraseDebugStubInfo();
			debugValueInfoAccess->updateDebugValueInfo(*debugValueInfo);
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
_DebugStubInfoAccess<EncodingT>::insertDebugStubInfo(boost::shared_ptr< _DebugStubInfo<EncodingT> > o)  
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
	_DebugValueInfoAccess<EncodingT>* debugValueInfoAccess = _DebugValueInfoAccess<EncodingT>::getInstance();
	if (!debugValueInfoAccess) {
		m_logger->errorStream() << "DebugValueInfoAccess class is not initialized.";
		throw NullPointerException("DebugValueInfoAccess class is not initialized.");
	}
	try {
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
		int id = connection->selectMaxID(UCS("identifier"), UCS("debugStubInfo"))+1;
		values.addInt( id );
		fields.push_back( UCS("identifier") );
		values.addInt64( o->getLineNumber() );
		fields.push_back( UCS("lineNumber") );
		values.addInt64( o->getIsLineSkipped() );
		fields.push_back( UCS("isLineSkipped") );
		if ( !o->isNullDebugFileInfo() && typename _DebugFileInfo<EncodingT>::DebugFileInfoIDEquality(-1)(o->getDebugFileInfo()) ) {
			m_logger->errorStream() << "idDebugFile : Identifier is null.";
			throw InvalidQueryException("idDebugFile : Identifier is null.");
		}
		else if ( !o->isNullDebugFileInfo() ) {
			values.addInt64( o->getDebugFileInfo()->getIdentifier() );
			fields.push_back( UCS("idDebugFile") );
		}
		else {
			m_logger->errorStream() << "idDebugFile : null reference is forbidden.";
			throw InvalidQueryException("idDebugFile : null reference is forbidden.");
		}
		statement.swap( connection->insert(UCS("debugStubInfo"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		o->setIdentifier(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, UCS("debugStubInfo"), o);
		typename _DebugStubInfo<EncodingT>::DebugValueInfoIterator debugValueInfo;
		for ( debugValueInfo=o->getDebugValueInfosBeginning(); debugValueInfo!=o->getDebugValueInfosEnd(); ++debugValueInfo ) {
			(*debugValueInfo)->setDebugStubInfo(o);
			debugValueInfoAccess->insertDebugValueInfo(*debugValueInfo);
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
_DebugStubInfoAccess<EncodingT>::deleteDebugStubInfo(boost::shared_ptr< _DebugStubInfo<EncodingT> > o)  
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
	_DebugValueInfoAccess<EncodingT>* debugValueInfoAccess = _DebugValueInfoAccess<EncodingT>::getInstance();
	if (!debugValueInfoAccess) {
		m_logger->errorStream() << "DebugValueInfoAccess class is not initialized.";
		throw NullPointerException("DebugValueInfoAccess class is not initialized.");
	}
	typename backup_t::iterator save = m_backup.find(o);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before deletion.";
		throw UnSelectedObjectException("You must select object before deletion.");
	}
	try {
		typename _DebugStubInfo<EncodingT>::DebugValueInfoIterator debugValueInfo;
		fillAllDebugValueInfos(o);
		for ( debugValueInfo=o->getDebugValueInfosBeginning(); debugValueInfo!=o->getDebugValueInfosEnd(); ++debugValueInfo ) {
			debugValueInfoAccess->fillDebugStubInfo(*debugValueInfo);
			(*debugValueInfo)->eraseDebugStubInfo();
			debugValueInfoAccess->updateDebugValueInfo(*debugValueInfo);
		}
		statement.swap( connection->deleteFrom(UCS("debugStubInfo"), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, UCS("debugStubInfo"), o);
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
typename _DebugStubInfoAccess<EncodingT>::connection_t
_DebugStubInfoAccess<EncodingT>::addInsertSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_insertSignal.connect(subscriber);
}

template<class EncodingT>
typename _DebugStubInfoAccess<EncodingT>::connection_t
_DebugStubInfoAccess<EncodingT>::addUpdateSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_updateSignal.connect(subscriber);
}

template<class EncodingT>
typename _DebugStubInfoAccess<EncodingT>::connection_t
_DebugStubInfoAccess<EncodingT>::addDeleteSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_deleteSignal.connect(subscriber);
}

template<class EncodingT>
typename _DebugStubInfoAccess<EncodingT>::connection_t
_DebugStubInfoAccess<EncodingT>::addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber)  
{
	return m_transactionSignal.connect(subscriber);
}

template<class EncodingT>
void
_DebugStubInfoAccess<EncodingT>::removeInsertSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_DebugStubInfoAccess<EncodingT>::removeUpdateSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_DebugStubInfoAccess<EncodingT>::removeDeleteSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_DebugStubInfoAccess<EncodingT>::removeTransactionSignal(connection_t connection)  
{
	connection.disconnect();
}


NAMESPACE_END

#undef C
#undef A

