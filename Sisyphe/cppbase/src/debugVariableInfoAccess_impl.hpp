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
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("category"));
	columns.push_back(UCS("name"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,UCS("debugVariableInfo")), filter) );
	while( statement.executeStep() ) {
		long long identifier;
		typename EncodingT::string_t category;
		typename EncodingT::string_t name;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, category ) &&
			statement.getText( 2, name )) {
			value.reset(new _DebugVariableInfo<EncodingT>(
				identifier,
				category,
				name));
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
_DebugVariableInfoAccess<EncodingT>::getOneDebugVariableInfo(long long identifier) const 
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _DebugVariableInfo<EncodingT> > > result = getManyDebugVariableInfos(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/);
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
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("category"));
	columns.push_back(UCS("name"));
	if (!addition || !connection->isTransactionInProgress()) {
		cancelSelection();
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
	}
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,UCS("debugVariableInfo")), filter, nowait) );
	while( statement.executeStep() ) {
		long long identifier;
		typename EncodingT::string_t category;
		typename EncodingT::string_t name;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, category ) &&
			statement.getText( 2, name )) {
			tab.push_back(boost::shared_ptr< _DebugVariableInfo<EncodingT> >(new _DebugVariableInfo<EncodingT>(
				identifier,
				category,
				name)));
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
boost::shared_ptr< _DebugVariableInfo<EncodingT> >
_DebugVariableInfoAccess<EncodingT>::selectOneDebugVariableInfo(long long identifier, bool nowait, bool addition)  
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _DebugVariableInfo<EncodingT> > > result = selectManyDebugVariableInfos(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait, addition);
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
_DebugVariableInfoAccess<EncodingT>::fillDebugTypeInfo(boost::shared_ptr< _DebugVariableInfo<EncodingT> > o)  
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
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,UCS("idDebugType")), std::vector<typename EncodingT::string_t>(1,UCS("debugVariableInfo")), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
	if( statement.executeStep() && statement.getInt64( 0, id ) && id != 0 ) {
		typename _DebugVariableInfo<EncodingT>::DebugVariableInfoIDEquality debugVariableInfoIdEquality(o->getIdentifier());
		boost::shared_ptr< _DebugTypeInfo<EncodingT> > val = debugTypeInfoAccess->getOneDebugTypeInfo(id);
		typename std::list< boost::shared_ptr<_DebugVariableInfo<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), debugVariableInfoIdEquality);
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
	long long id;
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,UCS("idDebugFunction")), std::vector<typename EncodingT::string_t>(1,UCS("debugVariableInfo")), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
	if( statement.executeStep() && statement.getInt64( 0, id ) && id != 0 ) {
		typename _DebugVariableInfo<EncodingT>::DebugVariableInfoIDEquality debugVariableInfoIdEquality(o->getIdentifier());
		boost::shared_ptr< _DebugFunctionInfo<EncodingT> > val = debugFunctionInfoAccess->getOneDebugFunctionInfo(id);
		typename std::list< boost::shared_ptr<_DebugVariableInfo<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), debugVariableInfoIdEquality);
		if (save != m_backup.end()) {
			(*save)->setDebugFunctionInfo(val);
		}
		o->setDebugFunctionInfo(val);
	}
	else {
		m_logger->debugStream() << "identifier not found.";
	}
}

template<class EncodingT>
void
_DebugVariableInfoAccess<EncodingT>::fillAllDebugValueInfos(boost::shared_ptr< _DebugVariableInfo<EncodingT> > o, bool nowait)  
{
	fillManyDebugValueInfos(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_DebugVariableInfoAccess<EncodingT>::fillOneDebugValueInfo(boost::shared_ptr< _DebugVariableInfo<EncodingT> > o, long long identifier, bool nowait)  
{
	fillManyDebugValueInfos(o, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait);
}

template<class EncodingT>
void
_DebugVariableInfoAccess<EncodingT>::fillManyDebugValueInfos(boost::shared_ptr< _DebugVariableInfo<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
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
	typename EncodingT::string_t debugValueInfoFilter = UCS("idDebugVariable = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		debugValueInfoFilter += UCS(" AND ") + filter;
	}
	typename _DebugVariableInfo<EncodingT>::DebugVariableInfoIDEquality debugVariableInfoIdEquality(o->getIdentifier());
	typename std::list< boost::shared_ptr< _DebugVariableInfo<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), debugVariableInfoIdEquality);
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
	_DebugValueInfoAccess<EncodingT>* debugValueInfoAccess = _DebugValueInfoAccess<EncodingT>::getInstance();
	if (!debugValueInfoAccess) {
		m_logger->errorStream() << "DebugValueInfoAccess class is not initialized.";
		throw NullPointerException("DebugValueInfoAccess class is not initialized.");
	}
	typename _DebugVariableInfo<EncodingT>::DebugVariableInfoIDEquality debugVariableInfoIdEquality(*o);
	typename std::list< boost::shared_ptr< _DebugVariableInfo<EncodingT> > >::const_iterator save = std::find_if(m_backup.begin(), m_backup.end(), debugVariableInfoIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getCategory() != o->getCategory());
	bUpdate = bUpdate || ((*save)->getName() != o->getName());
	bUpdate = bUpdate || (!(*save)->isNullDebugTypeInfo() && !o->isNullDebugTypeInfo() && !typename _DebugTypeInfo<EncodingT>::DebugTypeInfoIDEquality(*(*save)->getDebugTypeInfo())(o->getDebugTypeInfo()))
		|| ((*save)->isNullDebugTypeInfo() && !o->isNullDebugTypeInfo()) 
		|| (!(*save)->isNullDebugTypeInfo() && o->isNullDebugTypeInfo());
	bUpdate = bUpdate || (!(*save)->isNullDebugFunctionInfo() && !o->isNullDebugFunctionInfo() && !typename _DebugFunctionInfo<EncodingT>::DebugFunctionInfoIDEquality(*(*save)->getDebugFunctionInfo())(o->getDebugFunctionInfo()))
		|| ((*save)->isNullDebugFunctionInfo() && !o->isNullDebugFunctionInfo()) 
		|| (!(*save)->isNullDebugFunctionInfo() && o->isNullDebugFunctionInfo());
	typename _DebugVariableInfo<EncodingT>::DebugValueInfoIterator debugValueInfo;
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
	_DebugValueInfoAccess<EncodingT>* debugValueInfoAccess = _DebugValueInfoAccess<EncodingT>::getInstance();
	if (!debugValueInfoAccess) {
		m_logger->errorStream() << "DebugValueInfoAccess class is not initialized.";
		throw NullPointerException("DebugValueInfoAccess class is not initialized.");
	}
	typename _DebugVariableInfo<EncodingT>::DebugVariableInfoIDEquality debugVariableInfoIdEquality(*o);
	typename std::list< boost::shared_ptr< _DebugVariableInfo<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), debugVariableInfoIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	try {
		if ( (*save)->getCategory() != o->getCategory() ) {
			values.addText( o->getCategory() );
			fields.push_back( UCS("category") );
		}
		if ( (*save)->getName() != o->getName() ) {
			values.addText( o->getName() );
			fields.push_back( UCS("name") );
		}
		if ( !o->isNullDebugTypeInfo() && typename _DebugTypeInfo<EncodingT>::DebugTypeInfoIDEquality(-1)(o->getDebugTypeInfo()) ) {
			m_logger->errorStream() << "idDebugType : Identifier is null.";
			throw InvalidQueryException("idDebugType : Identifier is null.");
		}
		else if ( !o->isNullDebugTypeInfo() && !typename _DebugTypeInfo<EncodingT>::DebugTypeInfoIDEquality(*(o->getDebugTypeInfo()))((*save)->getDebugTypeInfo()) ) {
			values.addInt64( o->getDebugTypeInfo()->getIdentifier() );
			fields.push_back( UCS("idDebugType") );
		}
		else if ( o->isNullDebugTypeInfo() && !(*save)->isNullDebugTypeInfo() ) {
			m_logger->errorStream() << "idDebugType : null reference is forbidden.";
			throw InvalidQueryException("idDebugType : null reference is forbidden.");
		}
		if ( !o->isNullDebugFunctionInfo() && typename _DebugFunctionInfo<EncodingT>::DebugFunctionInfoIDEquality(-1)(o->getDebugFunctionInfo()) ) {
			m_logger->errorStream() << "idDebugFunction : Identifier is null.";
			throw InvalidQueryException("idDebugFunction : Identifier is null.");
		}
		else if ( !o->isNullDebugFunctionInfo() && !typename _DebugFunctionInfo<EncodingT>::DebugFunctionInfoIDEquality(*(o->getDebugFunctionInfo()))((*save)->getDebugFunctionInfo()) ) {
			values.addInt64( o->getDebugFunctionInfo()->getIdentifier() );
			fields.push_back( UCS("idDebugFunction") );
		}
		else if ( o->isNullDebugFunctionInfo() && !(*save)->isNullDebugFunctionInfo() ) {
			values.addNull();
			fields.push_back( UCS("idDebugFunction") );
		}
		std::vector< boost::shared_ptr< _DebugValueInfo<EncodingT> > > listOfDebugValueInfoToAdd;
		std::vector< boost::shared_ptr< _DebugValueInfo<EncodingT> > > listOfDebugValueInfoToUpdate;
		typename _DebugVariableInfo<EncodingT>::DebugValueInfoIterator debugValueInfo;
		for ( debugValueInfo=o->getDebugValueInfosBeginning(); debugValueInfo!=o->getDebugValueInfosEnd(); ++debugValueInfo ) {
			if (!(*debugValueInfo)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*debugValueInfo)->setDebugVariableInfo(o);
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
			statement.swap( connection->update(UCS("debugVariableInfo"), fields, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, UCS("debugVariableInfo"), o);
		}
		for ( debugValueInfo=listOfDebugValueInfoToAdd.begin(); debugValueInfo!=listOfDebugValueInfoToAdd.end() ; ++debugValueInfo ) {
			debugValueInfoAccess->insertDebugValueInfo(*debugValueInfo);
		}
		for ( debugValueInfo=listOfDebugValueInfoToUpdate.begin(); debugValueInfo!=listOfDebugValueInfoToUpdate.end() ; ++debugValueInfo ) {
			debugValueInfoAccess->updateDebugValueInfo(*debugValueInfo);
		}
		for ( debugValueInfo=listOfDebugValueInfoToRemove.begin(); debugValueInfo!=listOfDebugValueInfoToRemove.end() ; ++debugValueInfo ) {
			debugValueInfoAccess->deleteDebugValueInfo(*debugValueInfo);
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
		int id = connection->selectMaxID(UCS("identifier"), UCS("debugVariableInfo"))+1;
		values.addInt( id );
		fields.push_back( UCS("identifier") );
		values.addText( o->getCategory() );
		fields.push_back( UCS("category") );
		values.addText( o->getName() );
		fields.push_back( UCS("name") );
		if ( !o->isNullDebugTypeInfo() && typename _DebugTypeInfo<EncodingT>::DebugTypeInfoIDEquality(-1)(o->getDebugTypeInfo()) ) {
			m_logger->errorStream() << "idDebugType : Identifier is null.";
			throw InvalidQueryException("idDebugType : Identifier is null.");
		}
		else if ( !o->isNullDebugTypeInfo() ) {
			values.addInt64( o->getDebugTypeInfo()->getIdentifier() );
			fields.push_back( UCS("idDebugType") );
		}
		else {
			m_logger->errorStream() << "idDebugType : null reference is forbidden.";
			throw InvalidQueryException("idDebugType : null reference is forbidden.");
		}
		if ( !o->isNullDebugFunctionInfo() && typename _DebugFunctionInfo<EncodingT>::DebugFunctionInfoIDEquality(-1)(o->getDebugFunctionInfo()) ) {
			m_logger->errorStream() << "idDebugFunction : Identifier is null.";
			throw InvalidQueryException("idDebugFunction : Identifier is null.");
		}
		else if ( !o->isNullDebugFunctionInfo() ) {
			values.addInt64( o->getDebugFunctionInfo()->getIdentifier() );
			fields.push_back( UCS("idDebugFunction") );
		}
		else {
			values.addNull();
			fields.push_back( UCS("idDebugFunction") );
		}
		statement.swap( connection->insert(UCS("debugVariableInfo"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		o->setIdentifier(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, UCS("debugVariableInfo"), o);
		typename _DebugVariableInfo<EncodingT>::DebugValueInfoIterator debugValueInfo;
		for ( debugValueInfo=o->getDebugValueInfosBeginning(); debugValueInfo!=o->getDebugValueInfosEnd(); ++debugValueInfo ) {
			(*debugValueInfo)->setDebugVariableInfo(o);
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
	_DebugValueInfoAccess<EncodingT>* debugValueInfoAccess = _DebugValueInfoAccess<EncodingT>::getInstance();
	if (!debugValueInfoAccess) {
		m_logger->errorStream() << "DebugValueInfoAccess class is not initialized.";
		throw NullPointerException("DebugValueInfoAccess class is not initialized.");
	}
	typename _DebugVariableInfo<EncodingT>::DebugVariableInfoIDEquality DebugVariableInfoIdEquality(*o);
	typename std::list< boost::shared_ptr< _DebugVariableInfo<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), DebugVariableInfoIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before deletion.";
		throw UnSelectedObjectException("You must select object before deletion.");
	}
	try {
		typename _DebugVariableInfo<EncodingT>::DebugValueInfoIterator debugValueInfo;
		fillAllDebugValueInfos(o);
		for ( debugValueInfo=o->getDebugValueInfosBeginning(); debugValueInfo!=o->getDebugValueInfosEnd(); ++debugValueInfo ) {
			debugValueInfoAccess->deleteDebugValueInfo(*debugValueInfo);
		}
		statement.swap( connection->deleteFrom(UCS("debugVariableInfo"), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, UCS("debugVariableInfo"), o);
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

