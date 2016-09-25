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
_CppIncludeAccess<EncodingT>* _CppIncludeAccess<EncodingT>::m_instance = NULL;

template<class EncodingT>
_CppIncludeAccess<EncodingT>* 
_CppIncludeAccess<EncodingT>::getInstance()  
{
	if (m_instance == NULL) {
		m_instance = new _CppIncludeAccess<EncodingT>();
	}
	return m_instance;
}

template<class EncodingT>
_CppIncludeAccess<EncodingT>::_CppIncludeAccess()
: m_transactionOwner(false) 
{
	m_logger = &Category::getInstance(LOGNAME);
	m_logger->debugStream() << "constructor CppIncludeAccess " << m_transactionOwner;
}

template<class EncodingT>
_CppIncludeAccess<EncodingT>::~_CppIncludeAccess()
{
	cancelSelection();
	m_logger = NULL;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppInclude<EncodingT> > >
_CppIncludeAccess<EncodingT>::getManyCppIncludes(typename EncodingT::string_t const&  filter) const 
{
	boost::shared_ptr< _CppInclude<EncodingT> > value;
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _CppInclude<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(C("identifier"));
	columns.push_back(C("fileName"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,C("cppInclude")), filter) );
	while( statement.executeStep() ) {
		int identifier;
		typename EncodingT::string_t fileName;
		if (statement.getInt( 0, identifier ) &&
			statement.getText( 1, fileName )) {
			value.reset(new _CppInclude<EncodingT>(
				identifier,
				fileName));
			tab.push_back(value);
		}
	}
	return tab;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppInclude<EncodingT> > >
_CppIncludeAccess<EncodingT>::getAllCppIncludes() const 
{
	return getManyCppIncludes(EncodingT::EMPTY);
}

template<class EncodingT>
boost::shared_ptr< _CppInclude<EncodingT> >
_CppIncludeAccess<EncodingT>::getOneCppInclude(int identifier) const 
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _CppInclude<EncodingT> > > result = getManyCppIncludes(C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppInclude<EncodingT> > >
_CppIncludeAccess<EncodingT>::selectManyCppIncludes(typename EncodingT::string_t const&  filter, bool nowait, bool addition)  
{
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _CppInclude<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(C("identifier"));
	columns.push_back(C("fileName"));
	if (!addition || !connection->isTransactionInProgress()) {
		cancelSelection();
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
	}
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,C("cppInclude")), filter, nowait) );
	while( statement.executeStep() ) {
		int identifier;
		typename EncodingT::string_t fileName;
		if (statement.getInt( 0, identifier ) &&
			statement.getText( 1, fileName )) {
			tab.push_back(boost::shared_ptr< _CppInclude<EncodingT> >(new _CppInclude<EncodingT>(
				identifier,
				fileName)));
		}
	}
	m_backup.insert(m_backup.end(), tab.begin(), tab.end());
	return copy_ptr(tab);
}

template<class EncodingT>
boost::shared_ptr< _CppInclude<EncodingT> >
_CppIncludeAccess<EncodingT>::selectOneCppInclude(int identifier, bool nowait, bool addition)  
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _CppInclude<EncodingT> > > result = selectManyCppIncludes(C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait, addition);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
bool
_CppIncludeAccess<EncodingT>::isSelectedCppInclude(boost::shared_ptr< _CppInclude<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	typename _CppInclude<EncodingT>::CppIncludeIDEquality cppIncludeIdEquality(*o);
	return (!m_backup.empty() && (std::find_if(m_backup.begin(), m_backup.end(), cppIncludeIdEquality)!=m_backup.end()));
}

template<class EncodingT>
void
_CppIncludeAccess<EncodingT>::cancelSelection()  
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
_CppIncludeAccess<EncodingT>::fillCppFile(boost::shared_ptr< _CppInclude<EncodingT> > o)  
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
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,C("idFile")), std::vector<typename EncodingT::string_t>(1,C("cppInclude")), C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
	if( statement.executeStep() && statement.getInt( 0, id ) && id != 0 ) {
		typename _CppInclude<EncodingT>::CppIncludeIDEquality cppIncludeIdEquality(o->getIdentifier());
		boost::shared_ptr< _CppFile<EncodingT> > val = cppFileAccess->getOneCppFile(textFileAccess->getOneTextFile(id));
		typename std::vector< boost::shared_ptr<_CppInclude<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppIncludeIdEquality);
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
_CppIncludeAccess<EncodingT>::isModifiedCppInclude(boost::shared_ptr< _CppInclude<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	typename _CppInclude<EncodingT>::CppIncludeIDEquality cppIncludeIdEquality(*o);
	typename std::vector< boost::shared_ptr< _CppInclude<EncodingT> > >::const_iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppIncludeIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getFileName() != o->getFileName());
	bUpdate = bUpdate || (!(*save)->isNullCppFile() && !o->isNullCppFile() && !typename _CppFile<EncodingT>::CppFileIDEquality(*(*save)->getCppFile())(o->getCppFile()))
		|| ((*save)->isNullCppFile() && !o->isNullCppFile()) 
		|| (!(*save)->isNullCppFile() && o->isNullCppFile());
	return bUpdate;
}

template<class EncodingT>
void
_CppIncludeAccess<EncodingT>::updateCppInclude(boost::shared_ptr< _CppInclude<EncodingT> > o)  
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
	typename _CppInclude<EncodingT>::CppIncludeIDEquality cppIncludeIdEquality(*o);
	typename std::vector< boost::shared_ptr< _CppInclude<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppIncludeIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	try {
		if ( (*save)->getFileName() != o->getFileName() ) {
			values.addText( o->getFileName() );
			fields.push_back( C("fileName") );
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
		if (!fields.empty()) {
			statement.swap( connection->update(C("cppInclude"), fields, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, C("cppInclude"), o);
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
_CppIncludeAccess<EncodingT>::insertCppInclude(boost::shared_ptr< _CppInclude<EncodingT> > o)  
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
		int id = connection->selectMaxID(C("identifier"), C("cppInclude"))+1;
		values.addInt( id );
		fields.push_back( C("identifier") );
		values.addText( o->getFileName() );
		fields.push_back( C("fileName") );
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
		statement.swap( connection->insert(C("cppInclude"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		o->setIdentifier(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, C("cppInclude"), o);
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
_CppIncludeAccess<EncodingT>::deleteCppInclude(boost::shared_ptr< _CppInclude<EncodingT> > o)  
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
	typename _CppInclude<EncodingT>::CppIncludeIDEquality CppIncludeIdEquality(*o);
	typename std::vector< boost::shared_ptr< _CppInclude<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), CppIncludeIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before deletion.";
		throw UnSelectedObjectException("You must select object before deletion.");
	}
	try {
		statement.swap( connection->deleteFrom(C("cppInclude"), C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, C("cppInclude"), o);
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
typename _CppIncludeAccess<EncodingT>::connection_t
_CppIncludeAccess<EncodingT>::addInsertSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_insertSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppIncludeAccess<EncodingT>::connection_t
_CppIncludeAccess<EncodingT>::addUpdateSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_updateSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppIncludeAccess<EncodingT>::connection_t
_CppIncludeAccess<EncodingT>::addDeleteSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_deleteSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppIncludeAccess<EncodingT>::connection_t
_CppIncludeAccess<EncodingT>::addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber)  
{
	return m_transactionSignal.connect(subscriber);
}

template<class EncodingT>
void
_CppIncludeAccess<EncodingT>::removeInsertSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppIncludeAccess<EncodingT>::removeUpdateSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppIncludeAccess<EncodingT>::removeDeleteSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppIncludeAccess<EncodingT>::removeTransactionSignal(connection_t connection)  
{
	connection.disconnect();
}


NAMESPACE_END

#undef C
#undef A

