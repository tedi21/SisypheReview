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
_CppAttributeAccess<EncodingT>* _CppAttributeAccess<EncodingT>::m_instance = NULL;

template<class EncodingT>
_CppAttributeAccess<EncodingT>* 
_CppAttributeAccess<EncodingT>::getInstance()  
{
	if (m_instance == NULL) {
		m_instance = new _CppAttributeAccess<EncodingT>();
	}
	return m_instance;
}

template<class EncodingT>
_CppAttributeAccess<EncodingT>::_CppAttributeAccess()
: m_transactionOwner(false) 
{
	m_logger = &Category::getInstance(LOGNAME);
	m_logger->debugStream() << "constructor CppAttributeAccess " << m_transactionOwner;
}

template<class EncodingT>
_CppAttributeAccess<EncodingT>::~_CppAttributeAccess()
{
	cancelSelection();
	m_logger = NULL;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppAttribute<EncodingT> > >
_CppAttributeAccess<EncodingT>::getManyCppAttributes(typename EncodingT::string_t const&  filter) const 
{
	boost::shared_ptr< _CppAttribute<EncodingT> > value;
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _CppAttribute<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("attrType"));
	columns.push_back(UCS("name"));
	columns.push_back(UCS("accessSpecifier"));
	columns.push_back(UCS("isStatic"));
	columns.push_back(UCS("isConst"));
	columns.push_back(UCS("isConstexpr"));
	columns.push_back(UCS("constValue"));
	columns.push_back(UCS("lineNumber"));
	columns.push_back(UCS("startBlock"));
	columns.push_back(UCS("lengthBlock"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,UCS("cppAttribute")), filter) );
	while( statement.executeStep() ) {
		long long identifier;
		typename EncodingT::string_t attrType;
		typename EncodingT::string_t name;
		typename EncodingT::string_t accessSpecifier;
		long long isStatic;
		long long isConst;
		long long isConstexpr;
		typename EncodingT::string_t constValue;
		long long lineNumber;
		long long startBlock;
		long long lengthBlock;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, attrType ) &&
			statement.getText( 2, name ) &&
			statement.getText( 3, accessSpecifier ) &&
			statement.getInt64( 4, isStatic ) &&
			statement.getInt64( 5, isConst ) &&
			statement.getInt64( 6, isConstexpr ) &&
			statement.getText( 7, constValue ) &&
			statement.getInt64( 8, lineNumber ) &&
			statement.getInt64( 9, startBlock ) &&
			statement.getInt64( 10, lengthBlock )) {
			value.reset(new _CppAttribute<EncodingT>(
				identifier,
				attrType,
				name,
				accessSpecifier,
				isStatic,
				isConst,
				isConstexpr,
				constValue,
				lineNumber,
				startBlock,
				lengthBlock));
			tab.push_back(value);
		}
	}
	return tab;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppAttribute<EncodingT> > >
_CppAttributeAccess<EncodingT>::getAllCppAttributes() const 
{
	return getManyCppAttributes(EncodingT::EMPTY);
}

template<class EncodingT>
boost::shared_ptr< _CppAttribute<EncodingT> >
_CppAttributeAccess<EncodingT>::getOneCppAttribute(long long identifier) const 
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _CppAttribute<EncodingT> > > result = getManyCppAttributes(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppAttribute<EncodingT> > >
_CppAttributeAccess<EncodingT>::selectManyCppAttributes(typename EncodingT::string_t const&  filter, bool nowait, bool addition)  
{
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _CppAttribute<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("attrType"));
	columns.push_back(UCS("name"));
	columns.push_back(UCS("accessSpecifier"));
	columns.push_back(UCS("isStatic"));
	columns.push_back(UCS("isConst"));
	columns.push_back(UCS("isConstexpr"));
	columns.push_back(UCS("constValue"));
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
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,UCS("cppAttribute")), filter, nowait) );
	while( statement.executeStep() ) {
		long long identifier;
		typename EncodingT::string_t attrType;
		typename EncodingT::string_t name;
		typename EncodingT::string_t accessSpecifier;
		long long isStatic;
		long long isConst;
		long long isConstexpr;
		typename EncodingT::string_t constValue;
		long long lineNumber;
		long long startBlock;
		long long lengthBlock;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, attrType ) &&
			statement.getText( 2, name ) &&
			statement.getText( 3, accessSpecifier ) &&
			statement.getInt64( 4, isStatic ) &&
			statement.getInt64( 5, isConst ) &&
			statement.getInt64( 6, isConstexpr ) &&
			statement.getText( 7, constValue ) &&
			statement.getInt64( 8, lineNumber ) &&
			statement.getInt64( 9, startBlock ) &&
			statement.getInt64( 10, lengthBlock )) {
			tab.push_back(boost::shared_ptr< _CppAttribute<EncodingT> >(new _CppAttribute<EncodingT>(
				identifier,
				attrType,
				name,
				accessSpecifier,
				isStatic,
				isConst,
				isConstexpr,
				constValue,
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
		m_backup.insert(m_backup.end(), tab.begin(), tab.end());
	}
	return copy_ptr(tab);
}

template<class EncodingT>
boost::shared_ptr< _CppAttribute<EncodingT> >
_CppAttributeAccess<EncodingT>::selectOneCppAttribute(long long identifier, bool nowait, bool addition)  
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _CppAttribute<EncodingT> > > result = selectManyCppAttributes(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait, addition);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
bool
_CppAttributeAccess<EncodingT>::isSelectedCppAttribute(boost::shared_ptr< _CppAttribute<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	typename _CppAttribute<EncodingT>::CppAttributeIDEquality cppAttributeIdEquality(*o);
	return (!m_backup.empty() && (std::find_if(m_backup.begin(), m_backup.end(), cppAttributeIdEquality)!=m_backup.end()));
}

template<class EncodingT>
void
_CppAttributeAccess<EncodingT>::cancelSelection()  
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
_CppAttributeAccess<EncodingT>::fillCppClass(boost::shared_ptr< _CppAttribute<EncodingT> > o)  
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
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,UCS("idClass")), std::vector<typename EncodingT::string_t>(1,UCS("cppAttribute")), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
	if( statement.executeStep() && statement.getInt64( 0, id ) && id != 0 ) {
		typename _CppAttribute<EncodingT>::CppAttributeIDEquality cppAttributeIdEquality(o->getIdentifier());
		boost::shared_ptr< _CppClass<EncodingT> > val = cppClassAccess->getOneCppClass(id);
		typename std::list< boost::shared_ptr<_CppAttribute<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppAttributeIdEquality);
		if (save != m_backup.end()) {
			(*save)->setCppClass(val);
		}
		o->setCppClass(val);
	}
	else {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
}

template<class EncodingT>
bool
_CppAttributeAccess<EncodingT>::isModifiedCppAttribute(boost::shared_ptr< _CppAttribute<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	typename _CppAttribute<EncodingT>::CppAttributeIDEquality cppAttributeIdEquality(*o);
	typename std::list< boost::shared_ptr< _CppAttribute<EncodingT> > >::const_iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppAttributeIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getAttrType() != o->getAttrType());
	bUpdate = bUpdate || ((*save)->getName() != o->getName());
	bUpdate = bUpdate || ((*save)->getAccessSpecifier() != o->getAccessSpecifier());
	bUpdate = bUpdate || ((*save)->getIsStatic() != o->getIsStatic());
	bUpdate = bUpdate || ((*save)->getIsConst() != o->getIsConst());
	bUpdate = bUpdate || ((*save)->getIsConstexpr() != o->getIsConstexpr());
	bUpdate = bUpdate || ((*save)->getConstValue() != o->getConstValue());
	bUpdate = bUpdate || ((*save)->getLineNumber() != o->getLineNumber());
	bUpdate = bUpdate || ((*save)->getStartBlock() != o->getStartBlock());
	bUpdate = bUpdate || ((*save)->getLengthBlock() != o->getLengthBlock());
	bUpdate = bUpdate || (!(*save)->isNullCppClass() && !o->isNullCppClass() && !typename _CppClass<EncodingT>::CppClassIDEquality(*(*save)->getCppClass())(o->getCppClass()))
		|| ((*save)->isNullCppClass() && !o->isNullCppClass()) 
		|| (!(*save)->isNullCppClass() && o->isNullCppClass());
	return bUpdate;
}

template<class EncodingT>
void
_CppAttributeAccess<EncodingT>::updateCppAttribute(boost::shared_ptr< _CppAttribute<EncodingT> > o)  
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
	typename _CppAttribute<EncodingT>::CppAttributeIDEquality cppAttributeIdEquality(*o);
	typename std::list< boost::shared_ptr< _CppAttribute<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppAttributeIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	try {
		if ( (*save)->getAttrType() != o->getAttrType() ) {
			values.addText( o->getAttrType() );
			fields.push_back( UCS("attrType") );
		}
		if ( (*save)->getName() != o->getName() ) {
			values.addText( o->getName() );
			fields.push_back( UCS("name") );
		}
		if ( (*save)->getAccessSpecifier() != o->getAccessSpecifier() ) {
			values.addText( o->getAccessSpecifier() );
			fields.push_back( UCS("accessSpecifier") );
		}
		if ( (*save)->getIsStatic() != o->getIsStatic() ) {
			values.addInt64( o->getIsStatic() );
			fields.push_back( UCS("isStatic") );
		}
		if ( (*save)->getIsConst() != o->getIsConst() ) {
			values.addInt64( o->getIsConst() );
			fields.push_back( UCS("isConst") );
		}
		if ( (*save)->getIsConstexpr() != o->getIsConstexpr() ) {
			values.addInt64( o->getIsConstexpr() );
			fields.push_back( UCS("isConstexpr") );
		}
		if ( (*save)->getConstValue() != o->getConstValue() ) {
			values.addText( o->getConstValue() );
			fields.push_back( UCS("constValue") );
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
		if ( !o->isNullCppClass() && typename _CppClass<EncodingT>::CppClassIDEquality(-1)(o->getCppClass()) ) {
			m_logger->errorStream() << "idClass : Identifier is null.";
			throw InvalidQueryException("idClass : Identifier is null.");
		}
		else if ( !o->isNullCppClass() && !typename _CppClass<EncodingT>::CppClassIDEquality(*(o->getCppClass()))((*save)->getCppClass()) ) {
			values.addInt64( o->getCppClass()->getIdentifier() );
			fields.push_back( UCS("idClass") );
		}
		else if ( o->isNullCppClass() && !(*save)->isNullCppClass() ) {
			m_logger->errorStream() << "idClass : null reference is forbidden.";
			throw InvalidQueryException("idClass : null reference is forbidden.");
		}
		if (!fields.empty()) {
			statement.swap( connection->update(UCS("cppAttribute"), fields, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, UCS("cppAttribute"), o);
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
_CppAttributeAccess<EncodingT>::insertCppAttribute(boost::shared_ptr< _CppAttribute<EncodingT> > o)  
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
		int id = connection->selectMaxID(UCS("identifier"), UCS("cppAttribute"))+1;
		values.addInt( id );
		fields.push_back( UCS("identifier") );
		values.addText( o->getAttrType() );
		fields.push_back( UCS("attrType") );
		values.addText( o->getName() );
		fields.push_back( UCS("name") );
		values.addText( o->getAccessSpecifier() );
		fields.push_back( UCS("accessSpecifier") );
		values.addInt64( o->getIsStatic() );
		fields.push_back( UCS("isStatic") );
		values.addInt64( o->getIsConst() );
		fields.push_back( UCS("isConst") );
		values.addInt64( o->getIsConstexpr() );
		fields.push_back( UCS("isConstexpr") );
		values.addText( o->getConstValue() );
		fields.push_back( UCS("constValue") );
		if ( !o->isNullCppClass() && typename _CppClass<EncodingT>::CppClassIDEquality(-1)(o->getCppClass()) ) {
			m_logger->errorStream() << "idClass : Identifier is null.";
			throw InvalidQueryException("idClass : Identifier is null.");
		}
		else if ( !o->isNullCppClass() ) {
			values.addInt64( o->getCppClass()->getIdentifier() );
			fields.push_back( UCS("idClass") );
		}
		else {
			m_logger->errorStream() << "idClass : null reference is forbidden.";
			throw InvalidQueryException("idClass : null reference is forbidden.");
		}
		values.addInt64( o->getLineNumber() );
		fields.push_back( UCS("lineNumber") );
		values.addInt64( o->getStartBlock() );
		fields.push_back( UCS("startBlock") );
		values.addInt64( o->getLengthBlock() );
		fields.push_back( UCS("lengthBlock") );
		statement.swap( connection->insert(UCS("cppAttribute"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		o->setIdentifier(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, UCS("cppAttribute"), o);
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
_CppAttributeAccess<EncodingT>::deleteCppAttribute(boost::shared_ptr< _CppAttribute<EncodingT> > o)  
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
	typename _CppAttribute<EncodingT>::CppAttributeIDEquality CppAttributeIdEquality(*o);
	typename std::list< boost::shared_ptr< _CppAttribute<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), CppAttributeIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before deletion.";
		throw UnSelectedObjectException("You must select object before deletion.");
	}
	try {
		statement.swap( connection->deleteFrom(UCS("cppAttribute"), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, UCS("cppAttribute"), o);
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
typename _CppAttributeAccess<EncodingT>::connection_t
_CppAttributeAccess<EncodingT>::addInsertSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_insertSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppAttributeAccess<EncodingT>::connection_t
_CppAttributeAccess<EncodingT>::addUpdateSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_updateSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppAttributeAccess<EncodingT>::connection_t
_CppAttributeAccess<EncodingT>::addDeleteSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_deleteSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppAttributeAccess<EncodingT>::connection_t
_CppAttributeAccess<EncodingT>::addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber)  
{
	return m_transactionSignal.connect(subscriber);
}

template<class EncodingT>
void
_CppAttributeAccess<EncodingT>::removeInsertSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppAttributeAccess<EncodingT>::removeUpdateSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppAttributeAccess<EncodingT>::removeDeleteSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppAttributeAccess<EncodingT>::removeTransactionSignal(connection_t connection)  
{
	connection.disconnect();
}


NAMESPACE_END

#undef C
#undef A

