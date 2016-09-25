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
_DebugFileInfoAccess<EncodingT>* _DebugFileInfoAccess<EncodingT>::m_instance = NULL;

template<class EncodingT>
_DebugFileInfoAccess<EncodingT>* 
_DebugFileInfoAccess<EncodingT>::getInstance()  
{
	if (m_instance == NULL) {
		m_instance = new _DebugFileInfoAccess<EncodingT>();
	}
	return m_instance;
}

template<class EncodingT>
_DebugFileInfoAccess<EncodingT>::_DebugFileInfoAccess()
: m_transactionOwner(false) 
{
	m_logger = &Category::getInstance(LOGNAME);
	m_logger->debugStream() << "constructor DebugFileInfoAccess " << m_transactionOwner;
}

template<class EncodingT>
_DebugFileInfoAccess<EncodingT>::~_DebugFileInfoAccess()
{
	cancelSelection();
	m_logger = NULL;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _DebugFileInfo<EncodingT> > >
_DebugFileInfoAccess<EncodingT>::getManyDebugFileInfos(typename EncodingT::string_t const&  filter) const 
{
	boost::shared_ptr< _DebugFileInfo<EncodingT> > value;
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _DebugFileInfo<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(C("identifier"));
	columns.push_back(C("compilandPath"));
	columns.push_back(C("checksum"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,C("debugFileInfo")), filter) );
	while( statement.executeStep() ) {
		int identifier;
		typename EncodingT::string_t compilandPath;
		boost::container::vector<unsigned char> checksum;
		if (statement.getInt( 0, identifier ) &&
			statement.getText( 1, compilandPath ) &&
			statement.getBlob( 2, checksum )) {
			value.reset(new _DebugFileInfo<EncodingT>(
				identifier,
				compilandPath,
				checksum));
			tab.push_back(value);
		}
	}
	return tab;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _DebugFileInfo<EncodingT> > >
_DebugFileInfoAccess<EncodingT>::getAllDebugFileInfos() const 
{
	return getManyDebugFileInfos(EncodingT::EMPTY);
}

template<class EncodingT>
boost::shared_ptr< _DebugFileInfo<EncodingT> >
_DebugFileInfoAccess<EncodingT>::getOneDebugFileInfo(int identifier) const 
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _DebugFileInfo<EncodingT> > > result = getManyDebugFileInfos(C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
std::vector< boost::shared_ptr< _DebugFileInfo<EncodingT> > >
_DebugFileInfoAccess<EncodingT>::selectManyDebugFileInfos(typename EncodingT::string_t const&  filter, bool nowait, bool addition)  
{
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _DebugFileInfo<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(C("identifier"));
	columns.push_back(C("compilandPath"));
	columns.push_back(C("checksum"));
	if (!addition || !connection->isTransactionInProgress()) {
		cancelSelection();
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
	}
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,C("debugFileInfo")), filter, nowait) );
	while( statement.executeStep() ) {
		int identifier;
		typename EncodingT::string_t compilandPath;
		boost::container::vector<unsigned char> checksum;
		if (statement.getInt( 0, identifier ) &&
			statement.getText( 1, compilandPath ) &&
			statement.getBlob( 2, checksum )) {
			tab.push_back(boost::shared_ptr< _DebugFileInfo<EncodingT> >(new _DebugFileInfo<EncodingT>(
				identifier,
				compilandPath,
				checksum)));
		}
	}
	m_backup.insert(m_backup.end(), tab.begin(), tab.end());
	return copy_ptr(tab);
}

template<class EncodingT>
boost::shared_ptr< _DebugFileInfo<EncodingT> >
_DebugFileInfoAccess<EncodingT>::selectOneDebugFileInfo(int identifier, bool nowait, bool addition)  
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _DebugFileInfo<EncodingT> > > result = selectManyDebugFileInfos(C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait, addition);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
bool
_DebugFileInfoAccess<EncodingT>::isSelectedDebugFileInfo(boost::shared_ptr< _DebugFileInfo<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	typename _DebugFileInfo<EncodingT>::DebugFileInfoIDEquality debugFileInfoIdEquality(*o);
	return (!m_backup.empty() && (std::find_if(m_backup.begin(), m_backup.end(), debugFileInfoIdEquality)!=m_backup.end()));
}

template<class EncodingT>
void
_DebugFileInfoAccess<EncodingT>::cancelSelection()  
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
_DebugFileInfoAccess<EncodingT>::fillCppFile(boost::shared_ptr< _DebugFileInfo<EncodingT> > o)  
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
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,C("idFile")), std::vector<typename EncodingT::string_t>(1,C("debugFileInfo")), C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
	if( statement.executeStep() && statement.getInt( 0, id ) && id != 0 ) {
		typename _DebugFileInfo<EncodingT>::DebugFileInfoIDEquality debugFileInfoIdEquality(o->getIdentifier());
		boost::shared_ptr< _CppFile<EncodingT> > val = cppFileAccess->getOneCppFile(textFileAccess->getOneTextFile(id));
		typename std::vector< boost::shared_ptr<_DebugFileInfo<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), debugFileInfoIdEquality);
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
_DebugFileInfoAccess<EncodingT>::isModifiedDebugFileInfo(boost::shared_ptr< _DebugFileInfo<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	typename _DebugFileInfo<EncodingT>::DebugFileInfoIDEquality debugFileInfoIdEquality(*o);
	typename std::vector< boost::shared_ptr< _DebugFileInfo<EncodingT> > >::const_iterator save = std::find_if(m_backup.begin(), m_backup.end(), debugFileInfoIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getCompilandPath() != o->getCompilandPath());
	bUpdate = bUpdate || ((*save)->getChecksum() != o->getChecksum());
	bUpdate = bUpdate || (!(*save)->isNullCppFile() && !o->isNullCppFile() && !typename _CppFile<EncodingT>::CppFileIDEquality(*(*save)->getCppFile())(o->getCppFile()))
		|| ((*save)->isNullCppFile() && !o->isNullCppFile()) 
		|| (!(*save)->isNullCppFile() && o->isNullCppFile());
	return bUpdate;
}

template<class EncodingT>
void
_DebugFileInfoAccess<EncodingT>::updateDebugFileInfo(boost::shared_ptr< _DebugFileInfo<EncodingT> > o)  
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
	typename _DebugFileInfo<EncodingT>::DebugFileInfoIDEquality debugFileInfoIdEquality(*o);
	typename std::vector< boost::shared_ptr< _DebugFileInfo<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), debugFileInfoIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	try {
		if ( (*save)->getCompilandPath() != o->getCompilandPath() ) {
			values.addText( o->getCompilandPath() );
			fields.push_back( C("compilandPath") );
		}
		if ( (*save)->getChecksum() != o->getChecksum() ) {
			values.addBlob( o->getChecksum() );
			fields.push_back( C("checksum") );
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
			statement.swap( connection->update(C("debugFileInfo"), fields, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, C("debugFileInfo"), o);
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
_DebugFileInfoAccess<EncodingT>::insertDebugFileInfo(boost::shared_ptr< _DebugFileInfo<EncodingT> > o)  
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
		int id = connection->selectMaxID(C("identifier"), C("debugFileInfo"))+1;
		values.addInt( id );
		fields.push_back( C("identifier") );
		values.addText( o->getCompilandPath() );
		fields.push_back( C("compilandPath") );
		values.addBlob( o->getChecksum() );
		fields.push_back( C("checksum") );
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
		statement.swap( connection->insert(C("debugFileInfo"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		o->setIdentifier(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, C("debugFileInfo"), o);
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
_DebugFileInfoAccess<EncodingT>::deleteDebugFileInfo(boost::shared_ptr< _DebugFileInfo<EncodingT> > o)  
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
	typename _DebugFileInfo<EncodingT>::DebugFileInfoIDEquality DebugFileInfoIdEquality(*o);
	typename std::vector< boost::shared_ptr< _DebugFileInfo<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), DebugFileInfoIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before deletion.";
		throw UnSelectedObjectException("You must select object before deletion.");
	}
	try {
		statement.swap( connection->deleteFrom(C("debugFileInfo"), C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, C("debugFileInfo"), o);
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
typename _DebugFileInfoAccess<EncodingT>::connection_t
_DebugFileInfoAccess<EncodingT>::addInsertSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_insertSignal.connect(subscriber);
}

template<class EncodingT>
typename _DebugFileInfoAccess<EncodingT>::connection_t
_DebugFileInfoAccess<EncodingT>::addUpdateSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_updateSignal.connect(subscriber);
}

template<class EncodingT>
typename _DebugFileInfoAccess<EncodingT>::connection_t
_DebugFileInfoAccess<EncodingT>::addDeleteSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_deleteSignal.connect(subscriber);
}

template<class EncodingT>
typename _DebugFileInfoAccess<EncodingT>::connection_t
_DebugFileInfoAccess<EncodingT>::addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber)  
{
	return m_transactionSignal.connect(subscriber);
}

template<class EncodingT>
void
_DebugFileInfoAccess<EncodingT>::removeInsertSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_DebugFileInfoAccess<EncodingT>::removeUpdateSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_DebugFileInfoAccess<EncodingT>::removeDeleteSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_DebugFileInfoAccess<EncodingT>::removeTransactionSignal(connection_t connection)  
{
	connection.disconnect();
}


NAMESPACE_END

#undef C
#undef A

