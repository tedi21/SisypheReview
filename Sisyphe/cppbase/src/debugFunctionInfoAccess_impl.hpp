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
	columns.push_back(C("identifier"));
	columns.push_back(C("lineNumber"));
	columns.push_back(C("address"));
	columns.push_back(C("debugStart"));
	columns.push_back(C("debugEnd"));
	columns.push_back(C("debugReturnType"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,C("debugFunctionInfo")), filter) );
	while( statement.executeStep() ) {
		int identifier;
		int lineNumber;
		int address;
		int debugStart;
		int debugEnd;
		typename EncodingT::string_t debugReturnType;
		if (statement.getInt( 0, identifier ) &&
			statement.getInt( 1, lineNumber ) &&
			statement.getInt( 2, address ) &&
			statement.getInt( 3, debugStart ) &&
			statement.getInt( 4, debugEnd ) &&
			statement.getText( 5, debugReturnType )) {
			value.reset(new _DebugFunctionInfo<EncodingT>(
				identifier,
				lineNumber,
				address,
				debugStart,
				debugEnd,
				debugReturnType));
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
_DebugFunctionInfoAccess<EncodingT>::getOneDebugFunctionInfo(int identifier) const 
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _DebugFunctionInfo<EncodingT> > > result = getManyDebugFunctionInfos(C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/);
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
	columns.push_back(C("identifier"));
	columns.push_back(C("lineNumber"));
	columns.push_back(C("address"));
	columns.push_back(C("debugStart"));
	columns.push_back(C("debugEnd"));
	columns.push_back(C("debugReturnType"));
	if (!addition || !connection->isTransactionInProgress()) {
		cancelSelection();
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
	}
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,C("debugFunctionInfo")), filter, nowait) );
	while( statement.executeStep() ) {
		int identifier;
		int lineNumber;
		int address;
		int debugStart;
		int debugEnd;
		typename EncodingT::string_t debugReturnType;
		if (statement.getInt( 0, identifier ) &&
			statement.getInt( 1, lineNumber ) &&
			statement.getInt( 2, address ) &&
			statement.getInt( 3, debugStart ) &&
			statement.getInt( 4, debugEnd ) &&
			statement.getText( 5, debugReturnType )) {
			tab.push_back(boost::shared_ptr< _DebugFunctionInfo<EncodingT> >(new _DebugFunctionInfo<EncodingT>(
				identifier,
				lineNumber,
				address,
				debugStart,
				debugEnd,
				debugReturnType)));
		}
	}
	m_backup.insert(m_backup.end(), tab.begin(), tab.end());
	return copy_ptr(tab);
}

template<class EncodingT>
boost::shared_ptr< _DebugFunctionInfo<EncodingT> >
_DebugFunctionInfoAccess<EncodingT>::selectOneDebugFunctionInfo(int identifier, bool nowait, bool addition)  
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _DebugFunctionInfo<EncodingT> > > result = selectManyDebugFunctionInfos(C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait, addition);
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
	typename _DebugFunctionInfo<EncodingT>::DebugFunctionInfoIDEquality debugFunctionInfoIdEquality(*o);
	return (!m_backup.empty() && (std::find_if(m_backup.begin(), m_backup.end(), debugFunctionInfoIdEquality)!=m_backup.end()));
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
_DebugFunctionInfoAccess<EncodingT>::fillCppFunction(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > o)  
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
	int id;
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,C("idFunction")), std::vector<typename EncodingT::string_t>(1,C("debugFunctionInfo")), C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
	if( statement.executeStep() && statement.getInt( 0, id ) && id != 0 ) {
		typename _DebugFunctionInfo<EncodingT>::DebugFunctionInfoIDEquality debugFunctionInfoIdEquality(o->getIdentifier());
		boost::shared_ptr< _CppFunction<EncodingT> > val = cppFunctionAccess->getOneCppFunction(id);
		typename std::vector< boost::shared_ptr<_DebugFunctionInfo<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), debugFunctionInfoIdEquality);
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
void
_DebugFunctionInfoAccess<EncodingT>::fillAllDebugVariableInfos(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > o, bool nowait)  
{
	fillManyDebugVariableInfos(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_DebugFunctionInfoAccess<EncodingT>::fillOneDebugVariableInfo(boost::shared_ptr< _DebugFunctionInfo<EncodingT> > o, int identifier, bool nowait)  
{
	fillManyDebugVariableInfos(o, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait);
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
	typename EncodingT::string_t debugVariableInfoFilter = C("idDebugFunction = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		debugVariableInfoFilter += C(" AND ") + filter;
	}
	typename _DebugFunctionInfo<EncodingT>::DebugFunctionInfoIDEquality debugFunctionInfoIdEquality(o->getIdentifier());
	typename std::vector< boost::shared_ptr< _DebugFunctionInfo<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), debugFunctionInfoIdEquality);
	if (save != m_backup.end())
	{
		tab = debugVariableInfoAccess->selectManyDebugVariableInfos(debugVariableInfoFilter, nowait);
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
	typename _DebugFunctionInfo<EncodingT>::DebugFunctionInfoIDEquality debugFunctionInfoIdEquality(*o);
	typename std::vector< boost::shared_ptr< _DebugFunctionInfo<EncodingT> > >::const_iterator save = std::find_if(m_backup.begin(), m_backup.end(), debugFunctionInfoIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getLineNumber() != o->getLineNumber());
	bUpdate = bUpdate || ((*save)->getAddress() != o->getAddress());
	bUpdate = bUpdate || ((*save)->getDebugStart() != o->getDebugStart());
	bUpdate = bUpdate || ((*save)->getDebugEnd() != o->getDebugEnd());
	bUpdate = bUpdate || ((*save)->getDebugReturnType() != o->getDebugReturnType());
	bUpdate = bUpdate || (!(*save)->isNullCppFunction() && !o->isNullCppFunction() && !typename _CppFunction<EncodingT>::CppFunctionIDEquality(*(*save)->getCppFunction())(o->getCppFunction()))
		|| ((*save)->isNullCppFunction() && !o->isNullCppFunction()) 
		|| (!(*save)->isNullCppFunction() && o->isNullCppFunction());
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
	typename _DebugFunctionInfo<EncodingT>::DebugFunctionInfoIDEquality debugFunctionInfoIdEquality(*o);
	typename std::vector< boost::shared_ptr< _DebugFunctionInfo<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), debugFunctionInfoIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	try {
		if ( (*save)->getLineNumber() != o->getLineNumber() ) {
			values.addInt( o->getLineNumber() );
			fields.push_back( C("lineNumber") );
		}
		if ( (*save)->getAddress() != o->getAddress() ) {
			values.addInt( o->getAddress() );
			fields.push_back( C("address") );
		}
		if ( (*save)->getDebugStart() != o->getDebugStart() ) {
			values.addInt( o->getDebugStart() );
			fields.push_back( C("debugStart") );
		}
		if ( (*save)->getDebugEnd() != o->getDebugEnd() ) {
			values.addInt( o->getDebugEnd() );
			fields.push_back( C("debugEnd") );
		}
		if ( (*save)->getDebugReturnType() != o->getDebugReturnType() ) {
			values.addText( o->getDebugReturnType() );
			fields.push_back( C("debugReturnType") );
		}
		if ( !o->isNullCppFunction() && typename _CppFunction<EncodingT>::CppFunctionIDEquality(-1)(o->getCppFunction()) ) {
			m_logger->errorStream() << "idFunction : Identifier is null.";
			throw InvalidQueryException("idFunction : Identifier is null.");
		}
		else if ( !o->isNullCppFunction() && !typename _CppFunction<EncodingT>::CppFunctionIDEquality(*(o->getCppFunction()))((*save)->getCppFunction()) ) {
			values.addInt( o->getCppFunction()->getIdentifier() );
			fields.push_back( C("idFunction") );
		}
		else if ( o->isNullCppFunction() && !(*save)->isNullCppFunction() ) {
			m_logger->errorStream() << "idFunction : null reference is forbidden.";
			throw InvalidQueryException("idFunction : null reference is forbidden.");
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
			statement.swap( connection->update(C("debugFunctionInfo"), fields, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, C("debugFunctionInfo"), o);
		}
		for ( debugVariableInfo=listOfDebugVariableInfoToAdd.begin(); debugVariableInfo!=listOfDebugVariableInfoToAdd.end() ; ++debugVariableInfo ) {
			debugVariableInfoAccess->insertDebugVariableInfo(*debugVariableInfo);
		}
		for ( debugVariableInfo=listOfDebugVariableInfoToUpdate.begin(); debugVariableInfo!=listOfDebugVariableInfoToUpdate.end() ; ++debugVariableInfo ) {
			debugVariableInfoAccess->updateDebugVariableInfo(*debugVariableInfo);
		}
		for ( debugVariableInfo=listOfDebugVariableInfoToRemove.begin(); debugVariableInfo!=listOfDebugVariableInfoToRemove.end() ; ++debugVariableInfo ) {
			debugVariableInfoAccess->deleteDebugVariableInfo(*debugVariableInfo);
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
		int id = connection->selectMaxID(C("identifier"), C("debugFunctionInfo"))+1;
		values.addInt( id );
		fields.push_back( C("identifier") );
		values.addInt( o->getLineNumber() );
		fields.push_back( C("lineNumber") );
		values.addInt( o->getAddress() );
		fields.push_back( C("address") );
		values.addInt( o->getDebugStart() );
		fields.push_back( C("debugStart") );
		values.addInt( o->getDebugEnd() );
		fields.push_back( C("debugEnd") );
		values.addText( o->getDebugReturnType() );
		fields.push_back( C("debugReturnType") );
		if ( !o->isNullCppFunction() && typename _CppFunction<EncodingT>::CppFunctionIDEquality(-1)(o->getCppFunction()) ) {
			m_logger->errorStream() << "idFunction : Identifier is null.";
			throw InvalidQueryException("idFunction : Identifier is null.");
		}
		else if ( !o->isNullCppFunction() ) {
			values.addInt( o->getCppFunction()->getIdentifier() );
			fields.push_back( C("idFunction") );
		}
		else {
			m_logger->errorStream() << "idFunction : null reference is forbidden.";
			throw InvalidQueryException("idFunction : null reference is forbidden.");
		}
		statement.swap( connection->insert(C("debugFunctionInfo"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		o->setIdentifier(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, C("debugFunctionInfo"), o);
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
	typename _DebugFunctionInfo<EncodingT>::DebugFunctionInfoIDEquality DebugFunctionInfoIdEquality(*o);
	typename std::vector< boost::shared_ptr< _DebugFunctionInfo<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), DebugFunctionInfoIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before deletion.";
		throw UnSelectedObjectException("You must select object before deletion.");
	}
	try {
		typename _DebugFunctionInfo<EncodingT>::DebugVariableInfoIterator debugVariableInfo;
		fillAllDebugVariableInfos(o);
		for ( debugVariableInfo=o->getDebugVariableInfosBeginning(); debugVariableInfo!=o->getDebugVariableInfosEnd(); ++debugVariableInfo ) {
			debugVariableInfoAccess->deleteDebugVariableInfo(*debugVariableInfo);
		}
		statement.swap( connection->deleteFrom(C("debugFunctionInfo"), C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, C("debugFunctionInfo"), o);
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

