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
_DebugFunctionInfoAccess<EncodingT>* _DebugFunctionInfoAccess<EncodingT>::m_instance = NULL;

template<class EncodingT>
_DebugFunctionInfoAccess<EncodingT>* 
_DebugFunctionInfoAccess<EncodingT>::getInstance()  
{
	if (m_instance == NULL) {
		m_instance = new _DebugFunctionInfoAccess<EncodingT>();
	}
	return m_instance;
}

template<class EncodingT>
_DebugFunctionInfoAccess<EncodingT>::_DebugFunctionInfoAccess()
: m_transactionOwner(false) 
{
	m_logger = &Category::getInstance(LOGNAME);
	m_logger->debugStream() << "constructor DebugFunctionInfoAccess " << m_transactionOwner;
}

template<class EncodingT>
_DebugFunctionInfoAccess<EncodingT>::~_DebugFunctionInfoAccess()
{
	cancelSelection();
	m_logger = NULL;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _DebugFunctionInfo<EncodingT> > >
_DebugFunctionInfoAccess<EncodingT>::getManyDebugFunctionInfos(typename EncodingT::string_t const&  filter) const 
{
	boost::shared_ptr< _DebugFunctionInfo<EncodingT> > value;
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _DebugFunctionInfo<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("name"));
	columns.push_back(UCS("firstLineNumber"));
	columns.push_back(UCS("lastLineNumber"));
	columns.push_back(UCS("address"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,UCS("debugFunctionInfo")), filter) );
	while( statement.executeStep() ) {
		long long identifier;
		typename EncodingT::string_t name;
		long long firstLineNumber;
		long long lastLineNumber;
		long long address;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, name ) &&
			statement.getInt64( 2, firstLineNumber ) &&
			statement.getInt64( 3, lastLineNumber ) &&
			statement.getInt64( 4, address )) {
			value.reset(new _DebugFunctionInfo<EncodingT>(
				identifier,
				name,
				firstLineNumber,
				lastLineNumber,
				address));
			tab.push_back(value);
		}
	}
	return tab;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _DebugFunctionInfo<EncodingT> > >
_DebugFunctionInfoAccess<EncodingT>::getAllDebugFunctionInfos() const 
{
	return getManyDebugFunctionInfos(EncodingT::EMPTY);
}

template<class EncodingT>
boost::shared_ptr< _DebugFunctionInfo<EncodingT> >
_DebugFunctionInfoAccess<EncodingT>::getOneDebugFunctionInfo(long long identifier) const 
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _DebugFunctionInfo<EncodingT> > > result = getManyDebugFunctionInfos(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
std::vector< boost::shared_ptr< _DebugFunctionInfo<EncodingT> > >
_DebugFunctionInfoAccess<EncodingT>::selectManyDebugFunctionInfos(typename EncodingT::string_t const&  filter, bool nowait, bool addition)  
{
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _DebugFunctionInfo<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("name"));
	columns.push_back(UCS("firstLineNumber"));
	columns.push_back(UCS("lastLineNumber"));
	columns.push_back(UCS("address"));
	if (!addition || !connection->isTransactionInProgress()) {
		cancelSelection();
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
	}
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,UCS("debugFunctionInfo")), filter, nowait) );
	while( statement.executeStep() ) {
		long long identifier;
		typename EncodingT::string_t name;
		long long firstLineNumber;
		long long lastLineNumber;
		long long address;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, name ) &&
			statement.getInt64( 2, firstLineNumber ) &&
			statement.getInt64( 3, lastLineNumber ) &&
			statement.getInt64( 4, address )) {
			tab.push_back(boost::shared_ptr< _DebugFunctionInfo<EncodingT> >(new _DebugFunctionInfo<EncodingT>(
				identifier,
				name,
				firstLineNumber,
				lastLineNumber,
				address)));
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
boost::shared_ptr< _DebugFunctionInfo<EncodingT> >
_DebugFunctionInfoAccess<EncodingT>::selectOneDebugFunctionInfo(long long identifier, bool nowait, bool addition)  
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _DebugFunctionInfo<EncodingT> > > result = selectManyDebugFunctionInfos(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait, addition);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
bool
_DebugFunctionInfoAccess<EncodingT>::isSelectedDebugFunctionInfo(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > o) const 
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
_DebugFunctionInfoAccess<EncodingT>::cancelSelection()  
{
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	_DebugVariableInfoAccess<EncodingT>* debugVariableInfoAccess = _DebugVariableInfoAccess<EncodingT>::getInstance();
	if (!debugVariableInfoAccess) {
		m_logger->errorStream() << "DebugVariableInfoAccess class is not initialized.";
		throw NullPointerException("DebugVariableInfoAccess class is not initialized.");
	}
	if (!m_backup.empty()) {
		if (connection->isTransactionInProgress() && m_transactionOwner) {
			connection->rollback();
			m_transactionOwner = false;
			m_transactionSignal(OPERATION_ACCESS_ROLLBACK);
		}
		m_backup.clear();
		debugVariableInfoAccess->cancelSelection();
	}
}

template<class EncodingT>
void
_DebugFunctionInfoAccess<EncodingT>::fillDebugTypeInfo(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > o)  
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
	_DebugTypeInfoAccess<EncodingT>* debugTypeInfoAccess = _DebugTypeInfoAccess<EncodingT>::getInstance();
	if (!debugTypeInfoAccess) {
		m_logger->errorStream() << "DebugTypeInfoAccess class is not initialized.";
		throw NullPointerException("DebugTypeInfoAccess class is not initialized.");
	}
	long long id;
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,UCS("idReturnType")), std::vector<typename EncodingT::string_t>(1,UCS("debugFunctionInfo")), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
	if( statement.executeStep() && statement.getInt64( 0, id ) && id != 0 ) {
		boost::shared_ptr< _DebugTypeInfo<EncodingT> > val = debugTypeInfoAccess->getOneDebugTypeInfo(id);
		typename backup_t::iterator save = m_backup.find(o);
		if (save != m_backup.end()) {
			(*save)->setDebugTypeInfo(val);
		}
		o->setDebugTypeInfo(val);
	}
	else {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
}

template<class EncodingT>
void
_DebugFunctionInfoAccess<EncodingT>::fillDebugFileInfo(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > o)  
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
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,UCS("idDebugFile")), std::vector<typename EncodingT::string_t>(1,UCS("debugFunctionInfo")), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
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
_DebugFunctionInfoAccess<EncodingT>::fillAllDebugVariableInfos(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > o, bool nowait)  
{
	fillManyDebugVariableInfos(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_DebugFunctionInfoAccess<EncodingT>::fillOneDebugVariableInfo(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > o, long long identifier, bool nowait)  
{
	fillManyDebugVariableInfos(o, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait);
}

template<class EncodingT>
void
_DebugFunctionInfoAccess<EncodingT>::fillManyDebugVariableInfos(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_DebugVariableInfoAccess<EncodingT>* debugVariableInfoAccess = _DebugVariableInfoAccess<EncodingT>::getInstance();
	if (!debugVariableInfoAccess) {
		m_logger->errorStream() << "DebugVariableInfoAccess class is not initialized.";
		throw NullPointerException("DebugVariableInfoAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _DebugVariableInfo<EncodingT> > > tab;
	typename EncodingT::string_t debugVariableInfoFilter = UCS("idDebugFunction = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		debugVariableInfoFilter += UCS(" AND ") + filter;
	}
	typename backup_t::iterator save = m_backup.find(o);
	if (save != m_backup.end())
	{
		tab = debugVariableInfoAccess->selectManyDebugVariableInfos(debugVariableInfoFilter, nowait, true);
		(*save)->clearDebugVariableInfos();
		(*save)->insertDebugVariableInfo((*save)->getDebugVariableInfosEnd(), tab.begin(), tab.end());
	}
	else
	{
		tab = debugVariableInfoAccess->getManyDebugVariableInfos(debugVariableInfoFilter);
	}
	o->clearDebugVariableInfos();
	o->insertDebugVariableInfo(o->getDebugVariableInfosEnd(), tab.begin(), tab.end());
}

template<class EncodingT>
bool
_DebugFunctionInfoAccess<EncodingT>::isModifiedDebugFunctionInfo(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_DebugVariableInfoAccess<EncodingT>* debugVariableInfoAccess = _DebugVariableInfoAccess<EncodingT>::getInstance();
	if (!debugVariableInfoAccess) {
		m_logger->errorStream() << "DebugVariableInfoAccess class is not initialized.";
		throw NullPointerException("DebugVariableInfoAccess class is not initialized.");
	}
	typename backup_t::const_iterator save = m_backup.find(o);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getName() != o->getName());
	bUpdate = bUpdate || ((*save)->getFirstLineNumber() != o->getFirstLineNumber());
	bUpdate = bUpdate || ((*save)->getLastLineNumber() != o->getLastLineNumber());
	bUpdate = bUpdate || ((*save)->getAddress() != o->getAddress());
	bUpdate = bUpdate || (!(*save)->isNullDebugTypeInfo() && !o->isNullDebugTypeInfo() && !typename _DebugTypeInfo<EncodingT>::DebugTypeInfoIDEquality(*(*save)->getDebugTypeInfo())(o->getDebugTypeInfo()))
		|| ((*save)->isNullDebugTypeInfo() && !o->isNullDebugTypeInfo()) 
		|| (!(*save)->isNullDebugTypeInfo() && o->isNullDebugTypeInfo());
	bUpdate = bUpdate || (!(*save)->isNullDebugFileInfo() && !o->isNullDebugFileInfo() && !typename _DebugFileInfo<EncodingT>::DebugFileInfoIDEquality(*(*save)->getDebugFileInfo())(o->getDebugFileInfo()))
		|| ((*save)->isNullDebugFileInfo() && !o->isNullDebugFileInfo()) 
		|| (!(*save)->isNullDebugFileInfo() && o->isNullDebugFileInfo());
	typename _DebugFunctionInfo<EncodingT>::DebugVariableInfoIterator debugVariableInfo;
	for ( debugVariableInfo=o->getDebugVariableInfosBeginning(); debugVariableInfo!=o->getDebugVariableInfosEnd(); ++debugVariableInfo ) {
		if (!(*debugVariableInfo)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _DebugVariableInfo<EncodingT>::DebugVariableInfoIDEquality debugVariableInfoIdEquality(*(*debugVariableInfo));
		bUpdate = bUpdate || (std::find_if((*save)->getDebugVariableInfosBeginning(), (*save)->getDebugVariableInfosEnd(), debugVariableInfoIdEquality) == (*save)->getDebugVariableInfosEnd())
			|| (debugVariableInfoAccess->isModifiedDebugVariableInfo(*debugVariableInfo));
	}
	for ( debugVariableInfo=(*save)->getDebugVariableInfosBeginning(); debugVariableInfo<(*save)->getDebugVariableInfosEnd(); ++debugVariableInfo ) {
		if (!(*debugVariableInfo)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _DebugVariableInfo<EncodingT>::DebugVariableInfoIDEquality debugVariableInfoIdEquality(*(*debugVariableInfo));
		bUpdate = bUpdate || (std::find_if(o->getDebugVariableInfosBeginning(), o->getDebugVariableInfosEnd(), debugVariableInfoIdEquality) == o->getDebugVariableInfosEnd());
	}
	return bUpdate;
}

template<class EncodingT>
void
_DebugFunctionInfoAccess<EncodingT>::updateDebugFunctionInfo(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > o)  
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
	_DebugVariableInfoAccess<EncodingT>* debugVariableInfoAccess = _DebugVariableInfoAccess<EncodingT>::getInstance();
	if (!debugVariableInfoAccess) {
		m_logger->errorStream() << "DebugVariableInfoAccess class is not initialized.";
		throw NullPointerException("DebugVariableInfoAccess class is not initialized.");
	}
	typename backup_t::iterator save = m_backup.find(o);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	try {
		if ( (*save)->getName() != o->getName() ) {
			values.addText( o->getName() );
			fields.push_back( UCS("name") );
		}
		if ( (*save)->getFirstLineNumber() != o->getFirstLineNumber() ) {
			values.addInt64( o->getFirstLineNumber() );
			fields.push_back( UCS("firstLineNumber") );
		}
		if ( (*save)->getLastLineNumber() != o->getLastLineNumber() ) {
			values.addInt64( o->getLastLineNumber() );
			fields.push_back( UCS("lastLineNumber") );
		}
		if ( (*save)->getAddress() != o->getAddress() ) {
			values.addInt64( o->getAddress() );
			fields.push_back( UCS("address") );
		}
		if ( !o->isNullDebugTypeInfo() && typename _DebugTypeInfo<EncodingT>::DebugTypeInfoIDEquality(-1)(o->getDebugTypeInfo()) ) {
			m_logger->errorStream() << "idReturnType : Identifier is null.";
			throw InvalidQueryException("idReturnType : Identifier is null.");
		}
		else if ( !o->isNullDebugTypeInfo() && !typename _DebugTypeInfo<EncodingT>::DebugTypeInfoIDEquality(*(o->getDebugTypeInfo()))((*save)->getDebugTypeInfo()) ) {
			values.addInt64( o->getDebugTypeInfo()->getIdentifier() );
			fields.push_back( UCS("idReturnType") );
		}
		else if ( o->isNullDebugTypeInfo() && !(*save)->isNullDebugTypeInfo() ) {
			m_logger->errorStream() << "idReturnType : null reference is forbidden.";
			throw InvalidQueryException("idReturnType : null reference is forbidden.");
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
		std::vector< boost::shared_ptr< _DebugVariableInfo<EncodingT> > > listOfDebugVariableInfoToAdd;
		std::vector< boost::shared_ptr< _DebugVariableInfo<EncodingT> > > listOfDebugVariableInfoToUpdate;
		typename _DebugFunctionInfo<EncodingT>::DebugVariableInfoIterator debugVariableInfo;
		for ( debugVariableInfo=o->getDebugVariableInfosBeginning(); debugVariableInfo!=o->getDebugVariableInfosEnd(); ++debugVariableInfo ) {
			if (!(*debugVariableInfo)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*debugVariableInfo)->setDebugFunctionInfo(o);
			typename _DebugVariableInfo<EncodingT>::DebugVariableInfoIDEquality debugVariableInfoIdEquality(*(*debugVariableInfo));
			if ( std::find_if((*save)->getDebugVariableInfosBeginning(), (*save)->getDebugVariableInfosEnd(), debugVariableInfoIdEquality) == (*save)->getDebugVariableInfosEnd()) {
				listOfDebugVariableInfoToAdd.push_back(*debugVariableInfo);
			}
			else {
				if (debugVariableInfoAccess->isModifiedDebugVariableInfo(*debugVariableInfo))
					listOfDebugVariableInfoToUpdate.push_back(*debugVariableInfo);
			}
		}
		std::vector< boost::shared_ptr< _DebugVariableInfo<EncodingT> > > listOfDebugVariableInfoToRemove;
		for ( debugVariableInfo=(*save)->getDebugVariableInfosBeginning(); debugVariableInfo<(*save)->getDebugVariableInfosEnd(); ++debugVariableInfo ) {
			if (!(*debugVariableInfo)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			typename _DebugVariableInfo<EncodingT>::DebugVariableInfoIDEquality debugVariableInfoIdEquality(*(*debugVariableInfo));
			if ( std::find_if(o->getDebugVariableInfosBeginning(), o->getDebugVariableInfosEnd(), debugVariableInfoIdEquality) == o->getDebugVariableInfosEnd()) {
				listOfDebugVariableInfoToRemove.push_back(*debugVariableInfo);
			}
		}
		if (!fields.empty()) {
			statement.swap( connection->update(UCS("debugFunctionInfo"), fields, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, UCS("debugFunctionInfo"), o);
		}
		for ( debugVariableInfo=listOfDebugVariableInfoToAdd.begin(); debugVariableInfo!=listOfDebugVariableInfoToAdd.end() ; ++debugVariableInfo ) {
			debugVariableInfoAccess->insertDebugVariableInfo(*debugVariableInfo);
		}
		for ( debugVariableInfo=listOfDebugVariableInfoToUpdate.begin(); debugVariableInfo!=listOfDebugVariableInfoToUpdate.end() ; ++debugVariableInfo ) {
			debugVariableInfoAccess->updateDebugVariableInfo(*debugVariableInfo);
		}
		for ( debugVariableInfo=listOfDebugVariableInfoToRemove.begin(); debugVariableInfo!=listOfDebugVariableInfoToRemove.end() ; ++debugVariableInfo ) {
			debugVariableInfoAccess->fillDebugFunctionInfo(*debugVariableInfo);
			(*debugVariableInfo)->eraseDebugFunctionInfo();
			debugVariableInfoAccess->updateDebugVariableInfo(*debugVariableInfo);
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
_DebugFunctionInfoAccess<EncodingT>::insertDebugFunctionInfo(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > o)  
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
	_DebugVariableInfoAccess<EncodingT>* debugVariableInfoAccess = _DebugVariableInfoAccess<EncodingT>::getInstance();
	if (!debugVariableInfoAccess) {
		m_logger->errorStream() << "DebugVariableInfoAccess class is not initialized.";
		throw NullPointerException("DebugVariableInfoAccess class is not initialized.");
	}
	try {
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
		int id = connection->selectMaxID(UCS("identifier"), UCS("debugFunctionInfo"))+1;
		values.addInt( id );
		fields.push_back( UCS("identifier") );
		values.addText( o->getName() );
		fields.push_back( UCS("name") );
		values.addInt64( o->getFirstLineNumber() );
		fields.push_back( UCS("firstLineNumber") );
		values.addInt64( o->getLastLineNumber() );
		fields.push_back( UCS("lastLineNumber") );
		values.addInt64( o->getAddress() );
		fields.push_back( UCS("address") );
		if ( !o->isNullDebugTypeInfo() && typename _DebugTypeInfo<EncodingT>::DebugTypeInfoIDEquality(-1)(o->getDebugTypeInfo()) ) {
			m_logger->errorStream() << "idReturnType : Identifier is null.";
			throw InvalidQueryException("idReturnType : Identifier is null.");
		}
		else if ( !o->isNullDebugTypeInfo() ) {
			values.addInt64( o->getDebugTypeInfo()->getIdentifier() );
			fields.push_back( UCS("idReturnType") );
		}
		else {
			m_logger->errorStream() << "idReturnType : null reference is forbidden.";
			throw InvalidQueryException("idReturnType : null reference is forbidden.");
		}
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
		statement.swap( connection->insert(UCS("debugFunctionInfo"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		o->setIdentifier(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, UCS("debugFunctionInfo"), o);
		typename _DebugFunctionInfo<EncodingT>::DebugVariableInfoIterator debugVariableInfo;
		for ( debugVariableInfo=o->getDebugVariableInfosBeginning(); debugVariableInfo!=o->getDebugVariableInfosEnd(); ++debugVariableInfo ) {
			(*debugVariableInfo)->setDebugFunctionInfo(o);
			debugVariableInfoAccess->insertDebugVariableInfo(*debugVariableInfo);
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
_DebugFunctionInfoAccess<EncodingT>::deleteDebugFunctionInfo(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > o)  
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
	_DebugVariableInfoAccess<EncodingT>* debugVariableInfoAccess = _DebugVariableInfoAccess<EncodingT>::getInstance();
	if (!debugVariableInfoAccess) {
		m_logger->errorStream() << "DebugVariableInfoAccess class is not initialized.";
		throw NullPointerException("DebugVariableInfoAccess class is not initialized.");
	}
	typename backup_t::iterator save = m_backup.find(o);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before deletion.";
		throw UnSelectedObjectException("You must select object before deletion.");
	}
	try {
		typename _DebugFunctionInfo<EncodingT>::DebugVariableInfoIterator debugVariableInfo;
		fillAllDebugVariableInfos(o);
		for ( debugVariableInfo=o->getDebugVariableInfosBeginning(); debugVariableInfo!=o->getDebugVariableInfosEnd(); ++debugVariableInfo ) {
			debugVariableInfoAccess->fillDebugFunctionInfo(*debugVariableInfo);
			(*debugVariableInfo)->eraseDebugFunctionInfo();
			debugVariableInfoAccess->updateDebugVariableInfo(*debugVariableInfo);
		}
		statement.swap( connection->deleteFrom(UCS("debugFunctionInfo"), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, UCS("debugFunctionInfo"), o);
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
typename _DebugFunctionInfoAccess<EncodingT>::connection_t
_DebugFunctionInfoAccess<EncodingT>::addInsertSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_insertSignal.connect(subscriber);
}

template<class EncodingT>
typename _DebugFunctionInfoAccess<EncodingT>::connection_t
_DebugFunctionInfoAccess<EncodingT>::addUpdateSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_updateSignal.connect(subscriber);
}

template<class EncodingT>
typename _DebugFunctionInfoAccess<EncodingT>::connection_t
_DebugFunctionInfoAccess<EncodingT>::addDeleteSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_deleteSignal.connect(subscriber);
}

template<class EncodingT>
typename _DebugFunctionInfoAccess<EncodingT>::connection_t
_DebugFunctionInfoAccess<EncodingT>::addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber)  
{
	return m_transactionSignal.connect(subscriber);
}

template<class EncodingT>
void
_DebugFunctionInfoAccess<EncodingT>::removeInsertSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_DebugFunctionInfoAccess<EncodingT>::removeUpdateSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_DebugFunctionInfoAccess<EncodingT>::removeDeleteSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_DebugFunctionInfoAccess<EncodingT>::removeTransactionSignal(connection_t connection)  
{
	connection.disconnect();
}


NAMESPACE_END

#undef C
#undef A

