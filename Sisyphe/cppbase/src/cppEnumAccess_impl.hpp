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
std::vector< shared_ptr< _CppEnum<EncodingT> > >
_CppEnumAccess<EncodingT>::getManyCppEnums(typename EncodingT::string_t const&  filter) const 
{
	shared_ptr< _CppEnum<EncodingT> > value;
	_DataStatement<EncodingT> statement;
	std::vector< shared_ptr< _CppEnum<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(C("identifier"));
	columns.push_back(C("name"));
	columns.push_back(C("lineNumber"));
	columns.push_back(C("startBlock"));
	columns.push_back(C("lengthBlock"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,C("cppEnum")), filter) );
	while( statement.executeStep() ) {
		int identifier;
		typename EncodingT::string_t name;
		int lineNumber;
		int startBlock;
		int lengthBlock;
		if (statement.getInt( 0, identifier ) &&
			statement.getText( 1, name ) &&
			statement.getInt( 2, lineNumber ) &&
			statement.getInt( 3, startBlock ) &&
			statement.getInt( 4, lengthBlock )) {
			value.reset(new _CppEnum<EncodingT>(
				identifier,
				name,
				lineNumber,
				startBlock,
				lengthBlock));
			tab.push_back(value);
		}
	}
	return tab;
}

template<class EncodingT>
std::vector< shared_ptr< _CppEnum<EncodingT> > >
_CppEnumAccess<EncodingT>::getAllCppEnums() const 
{
	return getManyCppEnums(EncodingT::EMPTY);
}

template<class EncodingT>
shared_ptr< _CppEnum<EncodingT> >
_CppEnumAccess<EncodingT>::getOneCppEnum(int identifier) const 
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< shared_ptr< _CppEnum<EncodingT> > > result = getManyCppEnums(C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
std::vector< shared_ptr< _CppEnum<EncodingT> > >
_CppEnumAccess<EncodingT>::selectManyCppEnums(typename EncodingT::string_t const&  filter, bool nowait, bool addition)  
{
	_DataStatement<EncodingT> statement;
	std::vector< shared_ptr< _CppEnum<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(C("identifier"));
	columns.push_back(C("name"));
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
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,C("cppEnum")), filter, nowait) );
	while( statement.executeStep() ) {
		int identifier;
		typename EncodingT::string_t name;
		int lineNumber;
		int startBlock;
		int lengthBlock;
		if (statement.getInt( 0, identifier ) &&
			statement.getText( 1, name ) &&
			statement.getInt( 2, lineNumber ) &&
			statement.getInt( 3, startBlock ) &&
			statement.getInt( 4, lengthBlock )) {
			tab.push_back(shared_ptr< _CppEnum<EncodingT> >(new _CppEnum<EncodingT>(
				identifier,
				name,
				lineNumber,
				startBlock,
				lengthBlock)));
		}
	}
	m_backup.insert(m_backup.end(), tab.begin(), tab.end());
	return copy_ptr(tab);
}

template<class EncodingT>
shared_ptr< _CppEnum<EncodingT> >
_CppEnumAccess<EncodingT>::selectOneCppEnum(int identifier, bool nowait, bool addition)  
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< shared_ptr< _CppEnum<EncodingT> > > result = selectManyCppEnums(C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait, addition);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
bool
_CppEnumAccess<EncodingT>::isSelectedCppEnum(shared_ptr< _CppEnum<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	typename _CppEnum<EncodingT>::CppEnumIDEquality cppEnumIdEquality(*o);
	return (!m_backup.empty() && (std::find_if(m_backup.begin(), m_backup.end(), cppEnumIdEquality)!=m_backup.end()));
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
_CppEnumAccess<EncodingT>::fillCppFile(shared_ptr< _CppEnum<EncodingT> > o)  
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
	_TextFileAccess<EncodingT>* textFileAccess = _TextFileAccess<EncodingT>::getInstance();
	if (!textFileAccess) {
		m_logger->errorStream() << "TextFileAccess class is not initialized.";
		throw NullPointerException("TextFileAccess class is not initialized.");
	}
	int id;
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,C("idFile")), std::vector<typename EncodingT::string_t>(1,C("cppEnum")), C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
	if( statement.executeStep() && statement.getInt( 0, id ) && id != 0 ) {
		typename _CppEnum<EncodingT>::CppEnumIDEquality cppEnumIdEquality(o->getIdentifier());
		shared_ptr< _CppFile<EncodingT> > val = cppFileAccess->getOneCppFile(textFileAccess->getOneTextFile(id));
		typename std::vector< shared_ptr<_CppEnum<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppEnumIdEquality);
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
_CppEnumAccess<EncodingT>::fillAllCppEnumConstants(shared_ptr< _CppEnum<EncodingT> > o, bool nowait)  
{
	fillManyCppEnumConstants(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_CppEnumAccess<EncodingT>::fillOneCppEnumConstant(shared_ptr< _CppEnum<EncodingT> > o, int identifier, bool nowait)  
{
	fillManyCppEnumConstants(o, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait);
}

template<class EncodingT>
void
_CppEnumAccess<EncodingT>::fillManyCppEnumConstants(shared_ptr< _CppEnum<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
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
	std::vector< shared_ptr< _CppEnumConstant<EncodingT> > > tab;
	typename EncodingT::string_t cppEnumConstantFilter = C("idEnum = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		cppEnumConstantFilter += C(" AND ") + filter;
	}
	typename _CppEnum<EncodingT>::CppEnumIDEquality cppEnumIdEquality(o->getIdentifier());
	typename std::vector< shared_ptr< _CppEnum<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppEnumIdEquality);
	if (save != m_backup.end())
	{
		tab = cppEnumConstantAccess->selectManyCppEnumConstants(cppEnumConstantFilter, nowait);
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
_CppEnumAccess<EncodingT>::isModifiedCppEnum(shared_ptr< _CppEnum<EncodingT> > o) const 
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
	typename _CppEnum<EncodingT>::CppEnumIDEquality cppEnumIdEquality(*o);
	typename std::vector< shared_ptr< _CppEnum<EncodingT> > >::const_iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppEnumIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getName() != o->getName());
	bUpdate = bUpdate || ((*save)->getLineNumber() != o->getLineNumber());
	bUpdate = bUpdate || ((*save)->getStartBlock() != o->getStartBlock());
	bUpdate = bUpdate || ((*save)->getLengthBlock() != o->getLengthBlock());
	bUpdate = bUpdate || (!(*save)->isNullCppFile() && !o->isNullCppFile() && !typename _CppFile<EncodingT>::CppFileIDEquality(*(*save)->getCppFile())(o->getCppFile()))
		|| ((*save)->isNullCppFile() && !o->isNullCppFile()) 
		|| (!(*save)->isNullCppFile() && o->isNullCppFile());
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
_CppEnumAccess<EncodingT>::updateCppEnum(shared_ptr< _CppEnum<EncodingT> > o)  
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
	typename _CppEnum<EncodingT>::CppEnumIDEquality cppEnumIdEquality(*o);
	typename std::vector< shared_ptr< _CppEnum<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppEnumIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	try {
		if ( (*save)->getName() != o->getName() ) {
			values.addText( o->getName() );
			fields.push_back( C("name") );
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
		if ( !o->isNullCppFile() && !o->getCppFile()->isNullTextFile() && typename _TextFile<EncodingT>::TextFileIDEquality(-1)(o->getCppFile()->getTextFile()) ) {
			m_logger->errorStream() << "idFile : Identifier is null.";
			throw InvalidQueryException("idFile : Identifier is null.");
		}
		else if ( !o->isNullCppFile() && !o->getCppFile()->isNullTextFile() && !typename _CppFile<EncodingT>::CppFileIDEquality(*(o->getCppFile()))((*save)->getCppFile()) ) {
			values.addInt( o->getCppFile()->getTextFile()->getRowid() );
			fields.push_back( C("idFile") );
		}
		else if ( o->isNullCppFile() && !(*save)->isNullCppFile() ) {
			m_logger->errorStream() << "idFile : null reference is forbidden.";
			throw InvalidQueryException("idFile : null reference is forbidden.");
		}
		std::vector< shared_ptr< _CppEnumConstant<EncodingT> > > listOfCppEnumConstantToAdd;
		std::vector< shared_ptr< _CppEnumConstant<EncodingT> > > listOfCppEnumConstantToUpdate;
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
		std::vector< shared_ptr< _CppEnumConstant<EncodingT> > > listOfCppEnumConstantToRemove;
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
			statement.swap( connection->update(C("cppEnum"), fields, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, C("cppEnum"), o);
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
_CppEnumAccess<EncodingT>::insertCppEnum(shared_ptr< _CppEnum<EncodingT> > o)  
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
		int id = connection->selectMaxID(C("identifier"), C("cppEnum"))+1;
		values.addInt( id );
		fields.push_back( C("identifier") );
		values.addText( o->getName() );
		fields.push_back( C("name") );
		if ( !o->isNullCppFile() && !o->getCppFile()->isNullTextFile() && typename _TextFile<EncodingT>::TextFileIDEquality(-1)(o->getCppFile()->getTextFile()) ) {
			m_logger->errorStream() << "idFile : Identifier is null.";
			throw InvalidQueryException("idFile : Identifier is null.");
		}
		else if ( !o->isNullCppFile() && !o->getCppFile()->isNullTextFile() ) {
			values.addInt( o->getCppFile()->getTextFile()->getRowid() );
			fields.push_back( C("idFile") );
		}
		else {
			m_logger->errorStream() << "idFile : null reference is forbidden.";
			throw InvalidQueryException("idFile : null reference is forbidden.");
		}
		values.addInt( o->getLineNumber() );
		fields.push_back( C("lineNumber") );
		values.addInt( o->getStartBlock() );
		fields.push_back( C("startBlock") );
		values.addInt( o->getLengthBlock() );
		fields.push_back( C("lengthBlock") );
		statement.swap( connection->insert(C("cppEnum"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		o->setIdentifier(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, C("cppEnum"), o);
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
_CppEnumAccess<EncodingT>::deleteCppEnum(shared_ptr< _CppEnum<EncodingT> > o)  
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
	typename _CppEnum<EncodingT>::CppEnumIDEquality CppEnumIdEquality(*o);
	typename std::vector< shared_ptr< _CppEnum<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), CppEnumIdEquality);
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
		statement.swap( connection->deleteFrom(C("cppEnum"), C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, C("cppEnum"), o);
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

