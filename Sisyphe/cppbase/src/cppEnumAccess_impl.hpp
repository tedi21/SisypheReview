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
_CppEnumAccess<EncodingT>* _CppEnumAccess<EncodingT>::m_instance = NULL;

template<class EncodingT>
_CppEnumAccess<EncodingT>* 
_CppEnumAccess<EncodingT>::getInstance()  
{
	if (m_instance == NULL) {
		m_instance = new _CppEnumAccess<EncodingT>();
	}
	return m_instance;
}

template<class EncodingT>
_CppEnumAccess<EncodingT>::_CppEnumAccess()
: m_transactionOwner(false) 
{
	m_logger = &Category::getInstance(LOGNAME);
	m_logger->debugStream() << "constructor CppEnumAccess " << m_transactionOwner;
}

template<class EncodingT>
_CppEnumAccess<EncodingT>::~_CppEnumAccess()
{
	cancelSelection();
	m_logger = NULL;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppEnum<EncodingT> > >
_CppEnumAccess<EncodingT>::getManyCppEnums(typename EncodingT::string_t const&  filter) const 
{
	boost::shared_ptr< _CppEnum<EncodingT> > value;
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _CppEnum<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("name"));
	columns.push_back(UCS("accessSpecifier"));
	columns.push_back(UCS("lineNumber"));
	columns.push_back(UCS("startBlock"));
	columns.push_back(UCS("lengthBlock"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,UCS("cppEnum")), filter) );
	while( statement.executeStep() ) {
		long long identifier;
		typename EncodingT::string_t name;
		typename EncodingT::string_t accessSpecifier;
		long long lineNumber;
		long long startBlock;
		long long lengthBlock;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, name ) &&
			statement.getText( 2, accessSpecifier ) &&
			statement.getInt64( 3, lineNumber ) &&
			statement.getInt64( 4, startBlock ) &&
			statement.getInt64( 5, lengthBlock )) {
			value.reset(new _CppEnum<EncodingT>(
				identifier,
				name,
				accessSpecifier,
				lineNumber,
				startBlock,
				lengthBlock));
			tab.push_back(value);
		}
	}
	return tab;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppEnum<EncodingT> > >
_CppEnumAccess<EncodingT>::getAllCppEnums() const 
{
	return getManyCppEnums(EncodingT::EMPTY);
}

template<class EncodingT>
boost::shared_ptr< _CppEnum<EncodingT> >
_CppEnumAccess<EncodingT>::getOneCppEnum(long long identifier) const 
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _CppEnum<EncodingT> > > result = getManyCppEnums(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppEnum<EncodingT> > >
_CppEnumAccess<EncodingT>::selectManyCppEnums(typename EncodingT::string_t const&  filter, bool nowait, bool addition)  
{
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _CppEnum<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("name"));
	columns.push_back(UCS("accessSpecifier"));
	columns.push_back(UCS("lineNumber"));
	columns.push_back(UCS("startBlock"));
	columns.push_back(UCS("lengthBlock"));
	if (!addition || !connection->isTransactionInProgress()) {
		cancelSelection();
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
	}
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,UCS("cppEnum")), filter, nowait) );
	while( statement.executeStep() ) {
		long long identifier;
		typename EncodingT::string_t name;
		typename EncodingT::string_t accessSpecifier;
		long long lineNumber;
		long long startBlock;
		long long lengthBlock;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, name ) &&
			statement.getText( 2, accessSpecifier ) &&
			statement.getInt64( 3, lineNumber ) &&
			statement.getInt64( 4, startBlock ) &&
			statement.getInt64( 5, lengthBlock )) {
			tab.push_back(boost::shared_ptr< _CppEnum<EncodingT> >(new _CppEnum<EncodingT>(
				identifier,
				name,
				accessSpecifier,
				lineNumber,
				startBlock,
				lengthBlock)));
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
boost::shared_ptr< _CppEnum<EncodingT> >
_CppEnumAccess<EncodingT>::selectOneCppEnum(long long identifier, bool nowait, bool addition)  
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _CppEnum<EncodingT> > > result = selectManyCppEnums(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait, addition);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
bool
_CppEnumAccess<EncodingT>::isSelectedCppEnum(boost::shared_ptr< _CppEnum<EncodingT> > o) const 
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
_CppEnumAccess<EncodingT>::cancelSelection()  
{
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	_CppEnumConstantAccess<EncodingT>* cppEnumConstantAccess = _CppEnumConstantAccess<EncodingT>::getInstance();
	if (!cppEnumConstantAccess) {
		m_logger->errorStream() << "CppEnumConstantAccess class is not initialized.";
		throw NullPointerException("CppEnumConstantAccess class is not initialized.");
	}
	if (!m_backup.empty()) {
		if (connection->isTransactionInProgress() && m_transactionOwner) {
			connection->rollback();
			m_transactionOwner = false;
			m_transactionSignal(OPERATION_ACCESS_ROLLBACK);
		}
		m_backup.clear();
		cppEnumConstantAccess->cancelSelection();
	}
}

template<class EncodingT>
void
_CppEnumAccess<EncodingT>::fillCppFile(boost::shared_ptr< _CppEnum<EncodingT> > o)  
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
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,UCS("idFile")), std::vector<typename EncodingT::string_t>(1,UCS("cppEnum")), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
	if( statement.executeStep() && statement.getInt64( 0, id ) && id != 0 ) {
		boost::shared_ptr< _CppFile<EncodingT> > val = cppFileAccess->getOneCppFile(id);
		typename backup_t::iterator save = m_backup.find(o);
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
void
_CppEnumAccess<EncodingT>::fillCppClass(boost::shared_ptr< _CppEnum<EncodingT> > o)  
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
	_CppClassAccess<EncodingT>* cppClassAccess = _CppClassAccess<EncodingT>::getInstance();
	if (!cppClassAccess) {
		m_logger->errorStream() << "CppClassAccess class is not initialized.";
		throw NullPointerException("CppClassAccess class is not initialized.");
	}
	long long id;
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,UCS("idClass")), std::vector<typename EncodingT::string_t>(1,UCS("cppEnum")), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
	if( statement.executeStep() && statement.getInt64( 0, id ) && id != 0 ) {
		boost::shared_ptr< _CppClass<EncodingT> > val = cppClassAccess->getOneCppClass(id);
		typename backup_t::iterator save = m_backup.find(o);
		if (save != m_backup.end()) {
			(*save)->setCppClass(val);
		}
		o->setCppClass(val);
	}
	else {
		m_logger->debugStream() << "identifier not found.";
	}
}

template<class EncodingT>
void
_CppEnumAccess<EncodingT>::fillAllCppEnumConstants(boost::shared_ptr< _CppEnum<EncodingT> > o, bool nowait)  
{
	fillManyCppEnumConstants(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_CppEnumAccess<EncodingT>::fillOneCppEnumConstant(boost::shared_ptr< _CppEnum<EncodingT> > o, long long identifier, bool nowait)  
{
	fillManyCppEnumConstants(o, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait);
}

template<class EncodingT>
void
_CppEnumAccess<EncodingT>::fillManyCppEnumConstants(boost::shared_ptr< _CppEnum<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_CppEnumConstantAccess<EncodingT>* cppEnumConstantAccess = _CppEnumConstantAccess<EncodingT>::getInstance();
	if (!cppEnumConstantAccess) {
		m_logger->errorStream() << "CppEnumConstantAccess class is not initialized.";
		throw NullPointerException("CppEnumConstantAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _CppEnumConstant<EncodingT> > > tab;
	typename EncodingT::string_t cppEnumConstantFilter = UCS("idEnum = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		cppEnumConstantFilter += UCS(" AND ") + filter;
	}
	typename backup_t::iterator save = m_backup.find(o);
	if (save != m_backup.end())
	{
		tab = cppEnumConstantAccess->selectManyCppEnumConstants(cppEnumConstantFilter, nowait, true);
		(*save)->clearCppEnumConstants();
		(*save)->insertCppEnumConstant((*save)->getCppEnumConstantsEnd(), tab.begin(), tab.end());
	}
	else
	{
		tab = cppEnumConstantAccess->getManyCppEnumConstants(cppEnumConstantFilter);
	}
	o->clearCppEnumConstants();
	o->insertCppEnumConstant(o->getCppEnumConstantsEnd(), tab.begin(), tab.end());
}

template<class EncodingT>
bool
_CppEnumAccess<EncodingT>::isModifiedCppEnum(boost::shared_ptr< _CppEnum<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_CppEnumConstantAccess<EncodingT>* cppEnumConstantAccess = _CppEnumConstantAccess<EncodingT>::getInstance();
	if (!cppEnumConstantAccess) {
		m_logger->errorStream() << "CppEnumConstantAccess class is not initialized.";
		throw NullPointerException("CppEnumConstantAccess class is not initialized.");
	}
	typename backup_t::const_iterator save = m_backup.find(o);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getName() != o->getName());
	bUpdate = bUpdate || ((*save)->getAccessSpecifier() != o->getAccessSpecifier());
	bUpdate = bUpdate || ((*save)->getLineNumber() != o->getLineNumber());
	bUpdate = bUpdate || ((*save)->getStartBlock() != o->getStartBlock());
	bUpdate = bUpdate || ((*save)->getLengthBlock() != o->getLengthBlock());
	bUpdate = bUpdate || (!(*save)->isNullCppFile() && !o->isNullCppFile() && !typename _CppFile<EncodingT>::CppFileIDEquality(*(*save)->getCppFile())(o->getCppFile()))
		|| ((*save)->isNullCppFile() && !o->isNullCppFile()) 
		|| (!(*save)->isNullCppFile() && o->isNullCppFile());
	bUpdate = bUpdate || (!(*save)->isNullCppClass() && !o->isNullCppClass() && !typename _CppClass<EncodingT>::CppClassIDEquality(*(*save)->getCppClass())(o->getCppClass()))
		|| ((*save)->isNullCppClass() && !o->isNullCppClass()) 
		|| (!(*save)->isNullCppClass() && o->isNullCppClass());
	typename _CppEnum<EncodingT>::CppEnumConstantIterator cppEnumConstant;
	for ( cppEnumConstant=o->getCppEnumConstantsBeginning(); cppEnumConstant!=o->getCppEnumConstantsEnd(); ++cppEnumConstant ) {
		if (!(*cppEnumConstant)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppEnumConstant<EncodingT>::CppEnumConstantIDEquality cppEnumConstantIdEquality(*(*cppEnumConstant));
		bUpdate = bUpdate || (std::find_if((*save)->getCppEnumConstantsBeginning(), (*save)->getCppEnumConstantsEnd(), cppEnumConstantIdEquality) == (*save)->getCppEnumConstantsEnd())
			|| (cppEnumConstantAccess->isModifiedCppEnumConstant(*cppEnumConstant));
	}
	for ( cppEnumConstant=(*save)->getCppEnumConstantsBeginning(); cppEnumConstant<(*save)->getCppEnumConstantsEnd(); ++cppEnumConstant ) {
		if (!(*cppEnumConstant)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppEnumConstant<EncodingT>::CppEnumConstantIDEquality cppEnumConstantIdEquality(*(*cppEnumConstant));
		bUpdate = bUpdate || (std::find_if(o->getCppEnumConstantsBeginning(), o->getCppEnumConstantsEnd(), cppEnumConstantIdEquality) == o->getCppEnumConstantsEnd());
	}
	return bUpdate;
}

template<class EncodingT>
void
_CppEnumAccess<EncodingT>::updateCppEnum(boost::shared_ptr< _CppEnum<EncodingT> > o)  
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
	_CppEnumConstantAccess<EncodingT>* cppEnumConstantAccess = _CppEnumConstantAccess<EncodingT>::getInstance();
	if (!cppEnumConstantAccess) {
		m_logger->errorStream() << "CppEnumConstantAccess class is not initialized.";
		throw NullPointerException("CppEnumConstantAccess class is not initialized.");
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
		if ( (*save)->getAccessSpecifier() != o->getAccessSpecifier() ) {
			values.addText( o->getAccessSpecifier() );
			fields.push_back( UCS("accessSpecifier") );
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
		if ( !o->isNullCppClass() && typename _CppClass<EncodingT>::CppClassIDEquality(-1)(o->getCppClass()) ) {
			m_logger->errorStream() << "idClass : Identifier is null.";
			throw InvalidQueryException("idClass : Identifier is null.");
		}
		else if ( !o->isNullCppClass() && !typename _CppClass<EncodingT>::CppClassIDEquality(*(o->getCppClass()))((*save)->getCppClass()) ) {
			values.addInt64( o->getCppClass()->getIdentifier() );
			fields.push_back( UCS("idClass") );
		}
		else if ( o->isNullCppClass() && !(*save)->isNullCppClass() ) {
			values.addNull();
			fields.push_back( UCS("idClass") );
		}
		std::vector< boost::shared_ptr< _CppEnumConstant<EncodingT> > > listOfCppEnumConstantToAdd;
		std::vector< boost::shared_ptr< _CppEnumConstant<EncodingT> > > listOfCppEnumConstantToUpdate;
		typename _CppEnum<EncodingT>::CppEnumConstantIterator cppEnumConstant;
		for ( cppEnumConstant=o->getCppEnumConstantsBeginning(); cppEnumConstant!=o->getCppEnumConstantsEnd(); ++cppEnumConstant ) {
			if (!(*cppEnumConstant)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*cppEnumConstant)->setCppEnum(o);
			typename _CppEnumConstant<EncodingT>::CppEnumConstantIDEquality cppEnumConstantIdEquality(*(*cppEnumConstant));
			if ( std::find_if((*save)->getCppEnumConstantsBeginning(), (*save)->getCppEnumConstantsEnd(), cppEnumConstantIdEquality) == (*save)->getCppEnumConstantsEnd()) {
				listOfCppEnumConstantToAdd.push_back(*cppEnumConstant);
			}
			else {
				if (cppEnumConstantAccess->isModifiedCppEnumConstant(*cppEnumConstant))
					listOfCppEnumConstantToUpdate.push_back(*cppEnumConstant);
			}
		}
		std::vector< boost::shared_ptr< _CppEnumConstant<EncodingT> > > listOfCppEnumConstantToRemove;
		for ( cppEnumConstant=(*save)->getCppEnumConstantsBeginning(); cppEnumConstant<(*save)->getCppEnumConstantsEnd(); ++cppEnumConstant ) {
			if (!(*cppEnumConstant)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			typename _CppEnumConstant<EncodingT>::CppEnumConstantIDEquality cppEnumConstantIdEquality(*(*cppEnumConstant));
			if ( std::find_if(o->getCppEnumConstantsBeginning(), o->getCppEnumConstantsEnd(), cppEnumConstantIdEquality) == o->getCppEnumConstantsEnd()) {
				listOfCppEnumConstantToRemove.push_back(*cppEnumConstant);
			}
		}
		if (!fields.empty()) {
			statement.swap( connection->update(UCS("cppEnum"), fields, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, UCS("cppEnum"), o);
		}
		for ( cppEnumConstant=listOfCppEnumConstantToAdd.begin(); cppEnumConstant!=listOfCppEnumConstantToAdd.end() ; ++cppEnumConstant ) {
			cppEnumConstantAccess->insertCppEnumConstant(*cppEnumConstant);
		}
		for ( cppEnumConstant=listOfCppEnumConstantToUpdate.begin(); cppEnumConstant!=listOfCppEnumConstantToUpdate.end() ; ++cppEnumConstant ) {
			cppEnumConstantAccess->updateCppEnumConstant(*cppEnumConstant);
		}
		for ( cppEnumConstant=listOfCppEnumConstantToRemove.begin(); cppEnumConstant!=listOfCppEnumConstantToRemove.end() ; ++cppEnumConstant ) {
			cppEnumConstantAccess->deleteCppEnumConstant(*cppEnumConstant);
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
_CppEnumAccess<EncodingT>::insertCppEnum(boost::shared_ptr< _CppEnum<EncodingT> > o)  
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
	_CppEnumConstantAccess<EncodingT>* cppEnumConstantAccess = _CppEnumConstantAccess<EncodingT>::getInstance();
	if (!cppEnumConstantAccess) {
		m_logger->errorStream() << "CppEnumConstantAccess class is not initialized.";
		throw NullPointerException("CppEnumConstantAccess class is not initialized.");
	}
	try {
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
		int id = connection->selectMaxID(UCS("identifier"), UCS("cppEnum"))+1;
		values.addInt( id );
		fields.push_back( UCS("identifier") );
		values.addText( o->getName() );
		fields.push_back( UCS("name") );
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
		if ( !o->isNullCppClass() && typename _CppClass<EncodingT>::CppClassIDEquality(-1)(o->getCppClass()) ) {
			m_logger->errorStream() << "idClass : Identifier is null.";
			throw InvalidQueryException("idClass : Identifier is null.");
		}
		else if ( !o->isNullCppClass() ) {
			values.addInt64( o->getCppClass()->getIdentifier() );
			fields.push_back( UCS("idClass") );
		}
		else {
			values.addNull();
			fields.push_back( UCS("idClass") );
		}
		values.addText( o->getAccessSpecifier() );
		fields.push_back( UCS("accessSpecifier") );
		values.addInt64( o->getLineNumber() );
		fields.push_back( UCS("lineNumber") );
		values.addInt64( o->getStartBlock() );
		fields.push_back( UCS("startBlock") );
		values.addInt64( o->getLengthBlock() );
		fields.push_back( UCS("lengthBlock") );
		statement.swap( connection->insert(UCS("cppEnum"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		o->setIdentifier(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, UCS("cppEnum"), o);
		typename _CppEnum<EncodingT>::CppEnumConstantIterator cppEnumConstant;
		for ( cppEnumConstant=o->getCppEnumConstantsBeginning(); cppEnumConstant!=o->getCppEnumConstantsEnd(); ++cppEnumConstant ) {
			(*cppEnumConstant)->setCppEnum(o);
			cppEnumConstantAccess->insertCppEnumConstant(*cppEnumConstant);
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
_CppEnumAccess<EncodingT>::deleteCppEnum(boost::shared_ptr< _CppEnum<EncodingT> > o)  
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
	_CppEnumConstantAccess<EncodingT>* cppEnumConstantAccess = _CppEnumConstantAccess<EncodingT>::getInstance();
	if (!cppEnumConstantAccess) {
		m_logger->errorStream() << "CppEnumConstantAccess class is not initialized.";
		throw NullPointerException("CppEnumConstantAccess class is not initialized.");
	}
	typename backup_t::iterator save = m_backup.find(o);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before deletion.";
		throw UnSelectedObjectException("You must select object before deletion.");
	}
	try {
		typename _CppEnum<EncodingT>::CppEnumConstantIterator cppEnumConstant;
		fillAllCppEnumConstants(o);
		for ( cppEnumConstant=o->getCppEnumConstantsBeginning(); cppEnumConstant!=o->getCppEnumConstantsEnd(); ++cppEnumConstant ) {
			cppEnumConstantAccess->deleteCppEnumConstant(*cppEnumConstant);
		}
		statement.swap( connection->deleteFrom(UCS("cppEnum"), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, UCS("cppEnum"), o);
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
typename _CppEnumAccess<EncodingT>::connection_t
_CppEnumAccess<EncodingT>::addInsertSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_insertSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppEnumAccess<EncodingT>::connection_t
_CppEnumAccess<EncodingT>::addUpdateSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_updateSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppEnumAccess<EncodingT>::connection_t
_CppEnumAccess<EncodingT>::addDeleteSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_deleteSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppEnumAccess<EncodingT>::connection_t
_CppEnumAccess<EncodingT>::addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber)  
{
	return m_transactionSignal.connect(subscriber);
}

template<class EncodingT>
void
_CppEnumAccess<EncodingT>::removeInsertSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppEnumAccess<EncodingT>::removeUpdateSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppEnumAccess<EncodingT>::removeDeleteSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppEnumAccess<EncodingT>::removeTransactionSignal(connection_t connection)  
{
	connection.disconnect();
}


NAMESPACE_END

#undef C
#undef A

