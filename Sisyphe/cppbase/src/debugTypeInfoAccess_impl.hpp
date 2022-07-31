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
_DebugTypeInfoAccess<EncodingT>* _DebugTypeInfoAccess<EncodingT>::m_instance = NULL;

template<class EncodingT>
_DebugTypeInfoAccess<EncodingT>* 
_DebugTypeInfoAccess<EncodingT>::getInstance()  
{
	if (m_instance == NULL) {
		m_instance = new _DebugTypeInfoAccess<EncodingT>();
	}
	return m_instance;
}

template<class EncodingT>
_DebugTypeInfoAccess<EncodingT>::_DebugTypeInfoAccess()
: m_transactionOwner(false) 
{
	m_logger = &Category::getInstance(LOGNAME);
	m_logger->debugStream() << "constructor DebugTypeInfoAccess " << m_transactionOwner;
}

template<class EncodingT>
_DebugTypeInfoAccess<EncodingT>::~_DebugTypeInfoAccess()
{
	cancelSelection();
	m_logger = NULL;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _DebugTypeInfo<EncodingT> > >
_DebugTypeInfoAccess<EncodingT>::getManyDebugTypeInfos(typename EncodingT::string_t const&  filter) const 
{
	boost::shared_ptr< _DebugTypeInfo<EncodingT> > value;
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _DebugTypeInfo<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("isChar"));
	columns.push_back(UCS("isString"));
	columns.push_back(UCS("isBool"));
	columns.push_back(UCS("isFloat"));
	columns.push_back(UCS("isSigned"));
	columns.push_back(UCS("isWide"));
	columns.push_back(UCS("isPointer"));
	columns.push_back(UCS("isReference"));
	columns.push_back(UCS("isArray"));
	columns.push_back(UCS("isConst"));
	columns.push_back(UCS("isVolatile"));
	columns.push_back(UCS("isStruct"));
	columns.push_back(UCS("isClass"));
	columns.push_back(UCS("isUnion"));
	columns.push_back(UCS("isInterface"));
	columns.push_back(UCS("isEnum"));
	columns.push_back(UCS("isFunction"));
	columns.push_back(UCS("baseName"));
	columns.push_back(UCS("name"));
	columns.push_back(UCS("sizeOf"));
	columns.push_back(UCS("typeId"));
	columns.push_back(UCS("arrayDim"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,UCS("debugTypeInfo")), filter) );
	while( statement.executeStep() ) {
		long long identifier;
		long long isChar;
		long long isString;
		long long isBool;
		long long isFloat;
		long long isSigned;
		long long isWide;
		long long isPointer;
		long long isReference;
		long long isArray;
		long long isConst;
		long long isVolatile;
		long long isStruct;
		long long isClass;
		long long isUnion;
		long long isInterface;
		long long isEnum;
		long long isFunction;
		typename EncodingT::string_t baseName;
		typename EncodingT::string_t name;
		long long sizeOf;
		long long typeId;
		long long arrayDim;
		if (statement.getInt64( 0, identifier ) &&
			statement.getInt64( 1, isChar ) &&
			statement.getInt64( 2, isString ) &&
			statement.getInt64( 3, isBool ) &&
			statement.getInt64( 4, isFloat ) &&
			statement.getInt64( 5, isSigned ) &&
			statement.getInt64( 6, isWide ) &&
			statement.getInt64( 7, isPointer ) &&
			statement.getInt64( 8, isReference ) &&
			statement.getInt64( 9, isArray ) &&
			statement.getInt64( 10, isConst ) &&
			statement.getInt64( 11, isVolatile ) &&
			statement.getInt64( 12, isStruct ) &&
			statement.getInt64( 13, isClass ) &&
			statement.getInt64( 14, isUnion ) &&
			statement.getInt64( 15, isInterface ) &&
			statement.getInt64( 16, isEnum ) &&
			statement.getInt64( 17, isFunction ) &&
			statement.getText( 18, baseName ) &&
			statement.getText( 19, name ) &&
			statement.getInt64( 20, sizeOf ) &&
			statement.getInt64( 21, typeId ) &&
			statement.getInt64( 22, arrayDim )) {
			value.reset(new _DebugTypeInfo<EncodingT>(
				identifier,
				isChar,
				isString,
				isBool,
				isFloat,
				isSigned,
				isWide,
				isPointer,
				isReference,
				isArray,
				isConst,
				isVolatile,
				isStruct,
				isClass,
				isUnion,
				isInterface,
				isEnum,
				isFunction,
				baseName,
				name,
				sizeOf,
				typeId,
				arrayDim));
			tab.push_back(value);
		}
	}
	return tab;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _DebugTypeInfo<EncodingT> > >
_DebugTypeInfoAccess<EncodingT>::getAllDebugTypeInfos() const 
{
	return getManyDebugTypeInfos(EncodingT::EMPTY);
}

template<class EncodingT>
boost::shared_ptr< _DebugTypeInfo<EncodingT> >
_DebugTypeInfoAccess<EncodingT>::getOneDebugTypeInfo(long long identifier) const 
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _DebugTypeInfo<EncodingT> > > result = getManyDebugTypeInfos(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
std::vector< boost::shared_ptr< _DebugTypeInfo<EncodingT> > >
_DebugTypeInfoAccess<EncodingT>::selectManyDebugTypeInfos(typename EncodingT::string_t const&  filter, bool nowait, bool addition)  
{
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _DebugTypeInfo<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("isChar"));
	columns.push_back(UCS("isString"));
	columns.push_back(UCS("isBool"));
	columns.push_back(UCS("isFloat"));
	columns.push_back(UCS("isSigned"));
	columns.push_back(UCS("isWide"));
	columns.push_back(UCS("isPointer"));
	columns.push_back(UCS("isReference"));
	columns.push_back(UCS("isArray"));
	columns.push_back(UCS("isConst"));
	columns.push_back(UCS("isVolatile"));
	columns.push_back(UCS("isStruct"));
	columns.push_back(UCS("isClass"));
	columns.push_back(UCS("isUnion"));
	columns.push_back(UCS("isInterface"));
	columns.push_back(UCS("isEnum"));
	columns.push_back(UCS("isFunction"));
	columns.push_back(UCS("baseName"));
	columns.push_back(UCS("name"));
	columns.push_back(UCS("sizeOf"));
	columns.push_back(UCS("typeId"));
	columns.push_back(UCS("arrayDim"));
	if (!addition || !connection->isTransactionInProgress()) {
		cancelSelection();
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
	}
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,UCS("debugTypeInfo")), filter, nowait) );
	while( statement.executeStep() ) {
		long long identifier;
		long long isChar;
		long long isString;
		long long isBool;
		long long isFloat;
		long long isSigned;
		long long isWide;
		long long isPointer;
		long long isReference;
		long long isArray;
		long long isConst;
		long long isVolatile;
		long long isStruct;
		long long isClass;
		long long isUnion;
		long long isInterface;
		long long isEnum;
		long long isFunction;
		typename EncodingT::string_t baseName;
		typename EncodingT::string_t name;
		long long sizeOf;
		long long typeId;
		long long arrayDim;
		if (statement.getInt64( 0, identifier ) &&
			statement.getInt64( 1, isChar ) &&
			statement.getInt64( 2, isString ) &&
			statement.getInt64( 3, isBool ) &&
			statement.getInt64( 4, isFloat ) &&
			statement.getInt64( 5, isSigned ) &&
			statement.getInt64( 6, isWide ) &&
			statement.getInt64( 7, isPointer ) &&
			statement.getInt64( 8, isReference ) &&
			statement.getInt64( 9, isArray ) &&
			statement.getInt64( 10, isConst ) &&
			statement.getInt64( 11, isVolatile ) &&
			statement.getInt64( 12, isStruct ) &&
			statement.getInt64( 13, isClass ) &&
			statement.getInt64( 14, isUnion ) &&
			statement.getInt64( 15, isInterface ) &&
			statement.getInt64( 16, isEnum ) &&
			statement.getInt64( 17, isFunction ) &&
			statement.getText( 18, baseName ) &&
			statement.getText( 19, name ) &&
			statement.getInt64( 20, sizeOf ) &&
			statement.getInt64( 21, typeId ) &&
			statement.getInt64( 22, arrayDim )) {
			tab.push_back(boost::shared_ptr< _DebugTypeInfo<EncodingT> >(new _DebugTypeInfo<EncodingT>(
				identifier,
				isChar,
				isString,
				isBool,
				isFloat,
				isSigned,
				isWide,
				isPointer,
				isReference,
				isArray,
				isConst,
				isVolatile,
				isStruct,
				isClass,
				isUnion,
				isInterface,
				isEnum,
				isFunction,
				baseName,
				name,
				sizeOf,
				typeId,
				arrayDim)));
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
boost::shared_ptr< _DebugTypeInfo<EncodingT> >
_DebugTypeInfoAccess<EncodingT>::selectOneDebugTypeInfo(long long identifier, bool nowait, bool addition)  
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _DebugTypeInfo<EncodingT> > > result = selectManyDebugTypeInfos(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait, addition);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
bool
_DebugTypeInfoAccess<EncodingT>::isSelectedDebugTypeInfo(boost::shared_ptr< _DebugTypeInfo<EncodingT> > o) const 
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
_DebugTypeInfoAccess<EncodingT>::cancelSelection()  
{
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	_DebugTypeInfoAccess<EncodingT>* richTypeAccess = _DebugTypeInfoAccess<EncodingT>::getInstance();
	if (!richTypeAccess) {
		m_logger->errorStream() << "DebugTypeInfoAccess class is not initialized.";
		throw NullPointerException("DebugTypeInfoAccess class is not initialized.");
	}
	_DebugFunctionInfoAccess<EncodingT>* debugFunctionInfoAccess = _DebugFunctionInfoAccess<EncodingT>::getInstance();
	if (!debugFunctionInfoAccess) {
		m_logger->errorStream() << "DebugFunctionInfoAccess class is not initialized.";
		throw NullPointerException("DebugFunctionInfoAccess class is not initialized.");
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
		richTypeAccess->cancelSelection();
		debugFunctionInfoAccess->cancelSelection();
		debugVariableInfoAccess->cancelSelection();
	}
}

template<class EncodingT>
void
_DebugTypeInfoAccess<EncodingT>::fillPrimitiveType(boost::shared_ptr< _DebugTypeInfo<EncodingT> > o)  
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
	_DebugTypeInfoAccess<EncodingT>* primitiveTypeAccess = _DebugTypeInfoAccess<EncodingT>::getInstance();
	if (!primitiveTypeAccess) {
		m_logger->errorStream() << "DebugTypeInfoAccess class is not initialized.";
		throw NullPointerException("DebugTypeInfoAccess class is not initialized.");
	}
	long long id;
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,UCS("idPrimitiveType")), std::vector<typename EncodingT::string_t>(1,UCS("debugTypeInfo")), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
	if( statement.executeStep() && statement.getInt64( 0, id ) && id != 0 ) {
		boost::shared_ptr< _DebugTypeInfo<EncodingT> > val = primitiveTypeAccess->getOneDebugTypeInfo(id);
		typename backup_t::iterator save = m_backup.find(o);
		if (save != m_backup.end()) {
			(*save)->setPrimitiveType(val);
		}
		o->setPrimitiveType(val);
	}
	else {
		m_logger->debugStream() << "identifier not found.";
	}
}

template<class EncodingT>
void
_DebugTypeInfoAccess<EncodingT>::fillAllRichTypes(boost::shared_ptr< _DebugTypeInfo<EncodingT> > o, bool nowait)  
{
	fillManyRichTypes(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_DebugTypeInfoAccess<EncodingT>::fillOneRichType(boost::shared_ptr< _DebugTypeInfo<EncodingT> > o, long long identifier, bool nowait)  
{
	fillManyRichTypes(o, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait);
}

template<class EncodingT>
void
_DebugTypeInfoAccess<EncodingT>::fillManyRichTypes(boost::shared_ptr< _DebugTypeInfo<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_DebugTypeInfoAccess<EncodingT>* richTypeAccess = _DebugTypeInfoAccess<EncodingT>::getInstance();
	if (!richTypeAccess) {
		m_logger->errorStream() << "DebugTypeInfoAccess class is not initialized.";
		throw NullPointerException("DebugTypeInfoAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _DebugTypeInfo<EncodingT> > > tab;
	typename EncodingT::string_t debugTypeInfoFilter = UCS("idPrimitiveType = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		debugTypeInfoFilter += UCS(" AND ") + filter;
	}
	typename backup_t::iterator save = m_backup.find(o);
	if (save != m_backup.end())
	{
		tab = richTypeAccess->selectManyDebugTypeInfos(debugTypeInfoFilter, nowait, true);
		(*save)->clearRichTypes();
		(*save)->insertRichType((*save)->getRichTypesEnd(), tab.begin(), tab.end());
	}
	else
	{
		tab = richTypeAccess->getManyDebugTypeInfos(debugTypeInfoFilter);
	}
	o->clearRichTypes();
	o->insertRichType(o->getRichTypesEnd(), tab.begin(), tab.end());
}

template<class EncodingT>
void
_DebugTypeInfoAccess<EncodingT>::fillAllDebugFunctionInfos(boost::shared_ptr< _DebugTypeInfo<EncodingT> > o, bool nowait)  
{
	fillManyDebugFunctionInfos(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_DebugTypeInfoAccess<EncodingT>::fillOneDebugFunctionInfo(boost::shared_ptr< _DebugTypeInfo<EncodingT> > o, long long identifier, bool nowait)  
{
	fillManyDebugFunctionInfos(o, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait);
}

template<class EncodingT>
void
_DebugTypeInfoAccess<EncodingT>::fillManyDebugFunctionInfos(boost::shared_ptr< _DebugTypeInfo<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_DebugFunctionInfoAccess<EncodingT>* debugFunctionInfoAccess = _DebugFunctionInfoAccess<EncodingT>::getInstance();
	if (!debugFunctionInfoAccess) {
		m_logger->errorStream() << "DebugFunctionInfoAccess class is not initialized.";
		throw NullPointerException("DebugFunctionInfoAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _DebugFunctionInfo<EncodingT> > > tab;
	typename EncodingT::string_t debugFunctionInfoFilter = UCS("idReturnType = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		debugFunctionInfoFilter += UCS(" AND ") + filter;
	}
	typename backup_t::iterator save = m_backup.find(o);
	if (save != m_backup.end())
	{
		tab = debugFunctionInfoAccess->selectManyDebugFunctionInfos(debugFunctionInfoFilter, nowait, true);
		(*save)->clearDebugFunctionInfos();
		(*save)->insertDebugFunctionInfo((*save)->getDebugFunctionInfosEnd(), tab.begin(), tab.end());
	}
	else
	{
		tab = debugFunctionInfoAccess->getManyDebugFunctionInfos(debugFunctionInfoFilter);
	}
	o->clearDebugFunctionInfos();
	o->insertDebugFunctionInfo(o->getDebugFunctionInfosEnd(), tab.begin(), tab.end());
}

template<class EncodingT>
void
_DebugTypeInfoAccess<EncodingT>::fillAllDebugVariableInfos(boost::shared_ptr< _DebugTypeInfo<EncodingT> > o, bool nowait)  
{
	fillManyDebugVariableInfos(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_DebugTypeInfoAccess<EncodingT>::fillOneDebugVariableInfo(boost::shared_ptr< _DebugTypeInfo<EncodingT> > o, long long identifier, bool nowait)  
{
	fillManyDebugVariableInfos(o, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait);
}

template<class EncodingT>
void
_DebugTypeInfoAccess<EncodingT>::fillManyDebugVariableInfos(boost::shared_ptr< _DebugTypeInfo<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
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
	typename EncodingT::string_t debugVariableInfoFilter = UCS("idDebugType = ") + C(ToString::parse(o->getIdentifier()));
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
_DebugTypeInfoAccess<EncodingT>::isModifiedDebugTypeInfo(boost::shared_ptr< _DebugTypeInfo<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_DebugTypeInfoAccess<EncodingT>* richTypeAccess = _DebugTypeInfoAccess<EncodingT>::getInstance();
	if (!richTypeAccess) {
		m_logger->errorStream() << "DebugTypeInfoAccess class is not initialized.";
		throw NullPointerException("DebugTypeInfoAccess class is not initialized.");
	}
	_DebugFunctionInfoAccess<EncodingT>* debugFunctionInfoAccess = _DebugFunctionInfoAccess<EncodingT>::getInstance();
	if (!debugFunctionInfoAccess) {
		m_logger->errorStream() << "DebugFunctionInfoAccess class is not initialized.";
		throw NullPointerException("DebugFunctionInfoAccess class is not initialized.");
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
	bUpdate = bUpdate || ((*save)->getIsChar() != o->getIsChar());
	bUpdate = bUpdate || ((*save)->getIsString() != o->getIsString());
	bUpdate = bUpdate || ((*save)->getIsBool() != o->getIsBool());
	bUpdate = bUpdate || ((*save)->getIsFloat() != o->getIsFloat());
	bUpdate = bUpdate || ((*save)->getIsSigned() != o->getIsSigned());
	bUpdate = bUpdate || ((*save)->getIsWide() != o->getIsWide());
	bUpdate = bUpdate || ((*save)->getIsPointer() != o->getIsPointer());
	bUpdate = bUpdate || ((*save)->getIsReference() != o->getIsReference());
	bUpdate = bUpdate || ((*save)->getIsArray() != o->getIsArray());
	bUpdate = bUpdate || ((*save)->getIsConst() != o->getIsConst());
	bUpdate = bUpdate || ((*save)->getIsVolatile() != o->getIsVolatile());
	bUpdate = bUpdate || ((*save)->getIsStruct() != o->getIsStruct());
	bUpdate = bUpdate || ((*save)->getIsClass() != o->getIsClass());
	bUpdate = bUpdate || ((*save)->getIsUnion() != o->getIsUnion());
	bUpdate = bUpdate || ((*save)->getIsInterface() != o->getIsInterface());
	bUpdate = bUpdate || ((*save)->getIsEnum() != o->getIsEnum());
	bUpdate = bUpdate || ((*save)->getIsFunction() != o->getIsFunction());
	bUpdate = bUpdate || ((*save)->getBaseName() != o->getBaseName());
	bUpdate = bUpdate || ((*save)->getName() != o->getName());
	bUpdate = bUpdate || ((*save)->getSizeOf() != o->getSizeOf());
	bUpdate = bUpdate || ((*save)->getTypeId() != o->getTypeId());
	bUpdate = bUpdate || ((*save)->getArrayDim() != o->getArrayDim());
	bUpdate = bUpdate || (!(*save)->isNullPrimitiveType() && !o->isNullPrimitiveType() && !typename _DebugTypeInfo<EncodingT>::DebugTypeInfoIDEquality(*(*save)->getPrimitiveType())(o->getPrimitiveType()))
		|| ((*save)->isNullPrimitiveType() && !o->isNullPrimitiveType()) 
		|| (!(*save)->isNullPrimitiveType() && o->isNullPrimitiveType());
	typename _DebugTypeInfo<EncodingT>::RichTypeIterator richType;
	for ( richType=o->getRichTypesBeginning(); richType!=o->getRichTypesEnd(); ++richType ) {
		if (!(*richType)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _DebugTypeInfo<EncodingT>::DebugTypeInfoIDEquality richTypeIdEquality(*(*richType));
		bUpdate = bUpdate || (std::find_if((*save)->getRichTypesBeginning(), (*save)->getRichTypesEnd(), richTypeIdEquality) == (*save)->getRichTypesEnd())
			|| (richTypeAccess->isModifiedDebugTypeInfo(*richType));
	}
	for ( richType=(*save)->getRichTypesBeginning(); richType<(*save)->getRichTypesEnd(); ++richType ) {
		if (!(*richType)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _DebugTypeInfo<EncodingT>::DebugTypeInfoIDEquality richTypeIdEquality(*(*richType));
		bUpdate = bUpdate || (std::find_if(o->getRichTypesBeginning(), o->getRichTypesEnd(), richTypeIdEquality) == o->getRichTypesEnd());
	}
	typename _DebugTypeInfo<EncodingT>::DebugFunctionInfoIterator debugFunctionInfo;
	for ( debugFunctionInfo=o->getDebugFunctionInfosBeginning(); debugFunctionInfo!=o->getDebugFunctionInfosEnd(); ++debugFunctionInfo ) {
		if (!(*debugFunctionInfo)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _DebugFunctionInfo<EncodingT>::DebugFunctionInfoIDEquality debugFunctionInfoIdEquality(*(*debugFunctionInfo));
		bUpdate = bUpdate || (std::find_if((*save)->getDebugFunctionInfosBeginning(), (*save)->getDebugFunctionInfosEnd(), debugFunctionInfoIdEquality) == (*save)->getDebugFunctionInfosEnd())
			|| (debugFunctionInfoAccess->isModifiedDebugFunctionInfo(*debugFunctionInfo));
	}
	for ( debugFunctionInfo=(*save)->getDebugFunctionInfosBeginning(); debugFunctionInfo<(*save)->getDebugFunctionInfosEnd(); ++debugFunctionInfo ) {
		if (!(*debugFunctionInfo)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _DebugFunctionInfo<EncodingT>::DebugFunctionInfoIDEquality debugFunctionInfoIdEquality(*(*debugFunctionInfo));
		bUpdate = bUpdate || (std::find_if(o->getDebugFunctionInfosBeginning(), o->getDebugFunctionInfosEnd(), debugFunctionInfoIdEquality) == o->getDebugFunctionInfosEnd());
	}
	typename _DebugTypeInfo<EncodingT>::DebugVariableInfoIterator debugVariableInfo;
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
_DebugTypeInfoAccess<EncodingT>::updateDebugTypeInfo(boost::shared_ptr< _DebugTypeInfo<EncodingT> > o)  
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
	_DebugTypeInfoAccess<EncodingT>* richTypeAccess = _DebugTypeInfoAccess<EncodingT>::getInstance();
	if (!richTypeAccess) {
		m_logger->errorStream() << "DebugTypeInfoAccess class is not initialized.";
		throw NullPointerException("DebugTypeInfoAccess class is not initialized.");
	}
	_DebugFunctionInfoAccess<EncodingT>* debugFunctionInfoAccess = _DebugFunctionInfoAccess<EncodingT>::getInstance();
	if (!debugFunctionInfoAccess) {
		m_logger->errorStream() << "DebugFunctionInfoAccess class is not initialized.";
		throw NullPointerException("DebugFunctionInfoAccess class is not initialized.");
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
		if ( (*save)->getIsChar() != o->getIsChar() ) {
			values.addInt64( o->getIsChar() );
			fields.push_back( UCS("isChar") );
		}
		if ( (*save)->getIsString() != o->getIsString() ) {
			values.addInt64( o->getIsString() );
			fields.push_back( UCS("isString") );
		}
		if ( (*save)->getIsBool() != o->getIsBool() ) {
			values.addInt64( o->getIsBool() );
			fields.push_back( UCS("isBool") );
		}
		if ( (*save)->getIsFloat() != o->getIsFloat() ) {
			values.addInt64( o->getIsFloat() );
			fields.push_back( UCS("isFloat") );
		}
		if ( (*save)->getIsSigned() != o->getIsSigned() ) {
			values.addInt64( o->getIsSigned() );
			fields.push_back( UCS("isSigned") );
		}
		if ( (*save)->getIsWide() != o->getIsWide() ) {
			values.addInt64( o->getIsWide() );
			fields.push_back( UCS("isWide") );
		}
		if ( (*save)->getIsPointer() != o->getIsPointer() ) {
			values.addInt64( o->getIsPointer() );
			fields.push_back( UCS("isPointer") );
		}
		if ( (*save)->getIsReference() != o->getIsReference() ) {
			values.addInt64( o->getIsReference() );
			fields.push_back( UCS("isReference") );
		}
		if ( (*save)->getIsArray() != o->getIsArray() ) {
			values.addInt64( o->getIsArray() );
			fields.push_back( UCS("isArray") );
		}
		if ( (*save)->getIsConst() != o->getIsConst() ) {
			values.addInt64( o->getIsConst() );
			fields.push_back( UCS("isConst") );
		}
		if ( (*save)->getIsVolatile() != o->getIsVolatile() ) {
			values.addInt64( o->getIsVolatile() );
			fields.push_back( UCS("isVolatile") );
		}
		if ( (*save)->getIsStruct() != o->getIsStruct() ) {
			values.addInt64( o->getIsStruct() );
			fields.push_back( UCS("isStruct") );
		}
		if ( (*save)->getIsClass() != o->getIsClass() ) {
			values.addInt64( o->getIsClass() );
			fields.push_back( UCS("isClass") );
		}
		if ( (*save)->getIsUnion() != o->getIsUnion() ) {
			values.addInt64( o->getIsUnion() );
			fields.push_back( UCS("isUnion") );
		}
		if ( (*save)->getIsInterface() != o->getIsInterface() ) {
			values.addInt64( o->getIsInterface() );
			fields.push_back( UCS("isInterface") );
		}
		if ( (*save)->getIsEnum() != o->getIsEnum() ) {
			values.addInt64( o->getIsEnum() );
			fields.push_back( UCS("isEnum") );
		}
		if ( (*save)->getIsFunction() != o->getIsFunction() ) {
			values.addInt64( o->getIsFunction() );
			fields.push_back( UCS("isFunction") );
		}
		if ( (*save)->getBaseName() != o->getBaseName() ) {
			values.addText( o->getBaseName() );
			fields.push_back( UCS("baseName") );
		}
		if ( (*save)->getName() != o->getName() ) {
			values.addText( o->getName() );
			fields.push_back( UCS("name") );
		}
		if ( (*save)->getSizeOf() != o->getSizeOf() ) {
			values.addInt64( o->getSizeOf() );
			fields.push_back( UCS("sizeOf") );
		}
		if ( (*save)->getTypeId() != o->getTypeId() ) {
			values.addInt64( o->getTypeId() );
			fields.push_back( UCS("typeId") );
		}
		if ( (*save)->getArrayDim() != o->getArrayDim() ) {
			values.addInt64( o->getArrayDim() );
			fields.push_back( UCS("arrayDim") );
		}
		if ( !o->isNullPrimitiveType() && typename _DebugTypeInfo<EncodingT>::DebugTypeInfoIDEquality(-1)(o->getPrimitiveType()) ) {
			m_logger->errorStream() << "idPrimitiveType : Identifier is null.";
			throw InvalidQueryException("idPrimitiveType : Identifier is null.");
		}
		else if ( !o->isNullPrimitiveType() && !typename _DebugTypeInfo<EncodingT>::DebugTypeInfoIDEquality(*(o->getPrimitiveType()))((*save)->getPrimitiveType()) ) {
			values.addInt64( o->getPrimitiveType()->getIdentifier() );
			fields.push_back( UCS("idPrimitiveType") );
		}
		else if ( o->isNullPrimitiveType() && !(*save)->isNullPrimitiveType() ) {
			values.addNull();
			fields.push_back( UCS("idPrimitiveType") );
		}
		std::vector< boost::shared_ptr< _DebugTypeInfo<EncodingT> > > listOfRichTypeToAdd;
		std::vector< boost::shared_ptr< _DebugTypeInfo<EncodingT> > > listOfRichTypeToUpdate;
		typename _DebugTypeInfo<EncodingT>::RichTypeIterator richType;
		for ( richType=o->getRichTypesBeginning(); richType!=o->getRichTypesEnd(); ++richType ) {
			if (!(*richType)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*richType)->setPrimitiveType(o);
			typename _DebugTypeInfo<EncodingT>::DebugTypeInfoIDEquality richTypeIdEquality(*(*richType));
			if ( std::find_if((*save)->getRichTypesBeginning(), (*save)->getRichTypesEnd(), richTypeIdEquality) == (*save)->getRichTypesEnd()) {
				listOfRichTypeToAdd.push_back(*richType);
			}
			else {
				if (richTypeAccess->isModifiedDebugTypeInfo(*richType))
					listOfRichTypeToUpdate.push_back(*richType);
			}
		}
		std::vector< boost::shared_ptr< _DebugTypeInfo<EncodingT> > > listOfRichTypeToRemove;
		for ( richType=(*save)->getRichTypesBeginning(); richType<(*save)->getRichTypesEnd(); ++richType ) {
			if (!(*richType)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			typename _DebugTypeInfo<EncodingT>::DebugTypeInfoIDEquality richTypeIdEquality(*(*richType));
			if ( std::find_if(o->getRichTypesBeginning(), o->getRichTypesEnd(), richTypeIdEquality) == o->getRichTypesEnd()) {
				listOfRichTypeToRemove.push_back(*richType);
			}
		}
		std::vector< boost::shared_ptr< _DebugFunctionInfo<EncodingT> > > listOfDebugFunctionInfoToAdd;
		std::vector< boost::shared_ptr< _DebugFunctionInfo<EncodingT> > > listOfDebugFunctionInfoToUpdate;
		typename _DebugTypeInfo<EncodingT>::DebugFunctionInfoIterator debugFunctionInfo;
		for ( debugFunctionInfo=o->getDebugFunctionInfosBeginning(); debugFunctionInfo!=o->getDebugFunctionInfosEnd(); ++debugFunctionInfo ) {
			if (!(*debugFunctionInfo)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*debugFunctionInfo)->setDebugTypeInfo(o);
			typename _DebugFunctionInfo<EncodingT>::DebugFunctionInfoIDEquality debugFunctionInfoIdEquality(*(*debugFunctionInfo));
			if ( std::find_if((*save)->getDebugFunctionInfosBeginning(), (*save)->getDebugFunctionInfosEnd(), debugFunctionInfoIdEquality) == (*save)->getDebugFunctionInfosEnd()) {
				listOfDebugFunctionInfoToAdd.push_back(*debugFunctionInfo);
			}
			else {
				if (debugFunctionInfoAccess->isModifiedDebugFunctionInfo(*debugFunctionInfo))
					listOfDebugFunctionInfoToUpdate.push_back(*debugFunctionInfo);
			}
		}
		std::vector< boost::shared_ptr< _DebugFunctionInfo<EncodingT> > > listOfDebugFunctionInfoToRemove;
		for ( debugFunctionInfo=(*save)->getDebugFunctionInfosBeginning(); debugFunctionInfo<(*save)->getDebugFunctionInfosEnd(); ++debugFunctionInfo ) {
			if (!(*debugFunctionInfo)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			typename _DebugFunctionInfo<EncodingT>::DebugFunctionInfoIDEquality debugFunctionInfoIdEquality(*(*debugFunctionInfo));
			if ( std::find_if(o->getDebugFunctionInfosBeginning(), o->getDebugFunctionInfosEnd(), debugFunctionInfoIdEquality) == o->getDebugFunctionInfosEnd()) {
				listOfDebugFunctionInfoToRemove.push_back(*debugFunctionInfo);
			}
		}
		std::vector< boost::shared_ptr< _DebugVariableInfo<EncodingT> > > listOfDebugVariableInfoToAdd;
		std::vector< boost::shared_ptr< _DebugVariableInfo<EncodingT> > > listOfDebugVariableInfoToUpdate;
		typename _DebugTypeInfo<EncodingT>::DebugVariableInfoIterator debugVariableInfo;
		for ( debugVariableInfo=o->getDebugVariableInfosBeginning(); debugVariableInfo!=o->getDebugVariableInfosEnd(); ++debugVariableInfo ) {
			if (!(*debugVariableInfo)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*debugVariableInfo)->setDebugTypeInfo(o);
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
			statement.swap( connection->update(UCS("debugTypeInfo"), fields, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, UCS("debugTypeInfo"), o);
		}
		for ( richType=listOfRichTypeToAdd.begin(); richType!=listOfRichTypeToAdd.end() ; ++richType ) {
			richTypeAccess->insertDebugTypeInfo(*richType);
		}
		for ( richType=listOfRichTypeToUpdate.begin(); richType!=listOfRichTypeToUpdate.end() ; ++richType ) {
			richTypeAccess->updateDebugTypeInfo(*richType);
		}
		for ( richType=listOfRichTypeToRemove.begin(); richType!=listOfRichTypeToRemove.end() ; ++richType ) {
			richTypeAccess->fillPrimitiveType(*richType);
			(*richType)->erasePrimitiveType();
			richTypeAccess->updateDebugTypeInfo(*richType);
		}
		for ( debugFunctionInfo=listOfDebugFunctionInfoToAdd.begin(); debugFunctionInfo!=listOfDebugFunctionInfoToAdd.end() ; ++debugFunctionInfo ) {
			debugFunctionInfoAccess->insertDebugFunctionInfo(*debugFunctionInfo);
		}
		for ( debugFunctionInfo=listOfDebugFunctionInfoToUpdate.begin(); debugFunctionInfo!=listOfDebugFunctionInfoToUpdate.end() ; ++debugFunctionInfo ) {
			debugFunctionInfoAccess->updateDebugFunctionInfo(*debugFunctionInfo);
		}
		for ( debugFunctionInfo=listOfDebugFunctionInfoToRemove.begin(); debugFunctionInfo!=listOfDebugFunctionInfoToRemove.end() ; ++debugFunctionInfo ) {
			debugFunctionInfoAccess->deleteDebugFunctionInfo(*debugFunctionInfo);
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
_DebugTypeInfoAccess<EncodingT>::insertDebugTypeInfo(boost::shared_ptr< _DebugTypeInfo<EncodingT> > o)  
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
	_DebugTypeInfoAccess<EncodingT>* richTypeAccess = _DebugTypeInfoAccess<EncodingT>::getInstance();
	if (!richTypeAccess) {
		m_logger->errorStream() << "DebugTypeInfoAccess class is not initialized.";
		throw NullPointerException("DebugTypeInfoAccess class is not initialized.");
	}
	_DebugFunctionInfoAccess<EncodingT>* debugFunctionInfoAccess = _DebugFunctionInfoAccess<EncodingT>::getInstance();
	if (!debugFunctionInfoAccess) {
		m_logger->errorStream() << "DebugFunctionInfoAccess class is not initialized.";
		throw NullPointerException("DebugFunctionInfoAccess class is not initialized.");
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
		if ( !o->isNullPrimitiveType() && typename _DebugTypeInfo<EncodingT>::DebugTypeInfoIDEquality(-1)(o->getPrimitiveType()) ) {
			m_logger->errorStream() << "idPrimitiveType : Identifier is null.";
			throw InvalidQueryException("idPrimitiveType : Identifier is null.");
		}
		else if ( !o->isNullPrimitiveType() ) {
			values.addInt64( o->getPrimitiveType()->getIdentifier() );
			fields.push_back( UCS("idPrimitiveType") );
		}
		else {
			values.addNull();
			fields.push_back( UCS("idPrimitiveType") );
		}
		int id = connection->selectMaxID(UCS("identifier"), UCS("debugTypeInfo"))+1;
		values.addInt( id );
		fields.push_back( UCS("identifier") );
		values.addInt64( o->getIsChar() );
		fields.push_back( UCS("isChar") );
		values.addInt64( o->getIsString() );
		fields.push_back( UCS("isString") );
		values.addInt64( o->getIsBool() );
		fields.push_back( UCS("isBool") );
		values.addInt64( o->getIsFloat() );
		fields.push_back( UCS("isFloat") );
		values.addInt64( o->getIsSigned() );
		fields.push_back( UCS("isSigned") );
		values.addInt64( o->getIsWide() );
		fields.push_back( UCS("isWide") );
		values.addInt64( o->getIsPointer() );
		fields.push_back( UCS("isPointer") );
		values.addInt64( o->getIsReference() );
		fields.push_back( UCS("isReference") );
		values.addInt64( o->getIsArray() );
		fields.push_back( UCS("isArray") );
		values.addInt64( o->getIsConst() );
		fields.push_back( UCS("isConst") );
		values.addInt64( o->getIsVolatile() );
		fields.push_back( UCS("isVolatile") );
		values.addInt64( o->getIsStruct() );
		fields.push_back( UCS("isStruct") );
		values.addInt64( o->getIsClass() );
		fields.push_back( UCS("isClass") );
		values.addInt64( o->getIsUnion() );
		fields.push_back( UCS("isUnion") );
		values.addInt64( o->getIsInterface() );
		fields.push_back( UCS("isInterface") );
		values.addInt64( o->getIsEnum() );
		fields.push_back( UCS("isEnum") );
		values.addInt64( o->getIsFunction() );
		fields.push_back( UCS("isFunction") );
		values.addText( o->getBaseName() );
		fields.push_back( UCS("baseName") );
		values.addText( o->getName() );
		fields.push_back( UCS("name") );
		values.addInt64( o->getSizeOf() );
		fields.push_back( UCS("sizeOf") );
		values.addInt64( o->getTypeId() );
		fields.push_back( UCS("typeId") );
		values.addInt64( o->getArrayDim() );
		fields.push_back( UCS("arrayDim") );
		statement.swap( connection->insert(UCS("debugTypeInfo"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		o->setIdentifier(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, UCS("debugTypeInfo"), o);
		typename _DebugTypeInfo<EncodingT>::RichTypeIterator richType;
		for ( richType=o->getRichTypesBeginning(); richType!=o->getRichTypesEnd(); ++richType ) {
			(*richType)->setPrimitiveType(o);
			richTypeAccess->insertDebugTypeInfo(*richType);
		}
		typename _DebugTypeInfo<EncodingT>::DebugFunctionInfoIterator debugFunctionInfo;
		for ( debugFunctionInfo=o->getDebugFunctionInfosBeginning(); debugFunctionInfo!=o->getDebugFunctionInfosEnd(); ++debugFunctionInfo ) {
			(*debugFunctionInfo)->setDebugTypeInfo(o);
			debugFunctionInfoAccess->insertDebugFunctionInfo(*debugFunctionInfo);
		}
		typename _DebugTypeInfo<EncodingT>::DebugVariableInfoIterator debugVariableInfo;
		for ( debugVariableInfo=o->getDebugVariableInfosBeginning(); debugVariableInfo!=o->getDebugVariableInfosEnd(); ++debugVariableInfo ) {
			(*debugVariableInfo)->setDebugTypeInfo(o);
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
_DebugTypeInfoAccess<EncodingT>::deleteDebugTypeInfo(boost::shared_ptr< _DebugTypeInfo<EncodingT> > o)  
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
	_DebugTypeInfoAccess<EncodingT>* richTypeAccess = _DebugTypeInfoAccess<EncodingT>::getInstance();
	if (!richTypeAccess) {
		m_logger->errorStream() << "DebugTypeInfoAccess class is not initialized.";
		throw NullPointerException("DebugTypeInfoAccess class is not initialized.");
	}
	_DebugFunctionInfoAccess<EncodingT>* debugFunctionInfoAccess = _DebugFunctionInfoAccess<EncodingT>::getInstance();
	if (!debugFunctionInfoAccess) {
		m_logger->errorStream() << "DebugFunctionInfoAccess class is not initialized.";
		throw NullPointerException("DebugFunctionInfoAccess class is not initialized.");
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
		typename _DebugTypeInfo<EncodingT>::RichTypeIterator richType;
		fillAllRichTypes(o);
		for ( richType=o->getRichTypesBeginning(); richType!=o->getRichTypesEnd(); ++richType ) {
			richTypeAccess->fillPrimitiveType(*richType);
			(*richType)->erasePrimitiveType();
			richTypeAccess->updateDebugTypeInfo(*richType);
		}
		typename _DebugTypeInfo<EncodingT>::DebugFunctionInfoIterator debugFunctionInfo;
		fillAllDebugFunctionInfos(o);
		for ( debugFunctionInfo=o->getDebugFunctionInfosBeginning(); debugFunctionInfo!=o->getDebugFunctionInfosEnd(); ++debugFunctionInfo ) {
			debugFunctionInfoAccess->deleteDebugFunctionInfo(*debugFunctionInfo);
		}
		typename _DebugTypeInfo<EncodingT>::DebugVariableInfoIterator debugVariableInfo;
		fillAllDebugVariableInfos(o);
		for ( debugVariableInfo=o->getDebugVariableInfosBeginning(); debugVariableInfo!=o->getDebugVariableInfosEnd(); ++debugVariableInfo ) {
			debugVariableInfoAccess->deleteDebugVariableInfo(*debugVariableInfo);
		}
		statement.swap( connection->deleteFrom(UCS("debugTypeInfo"), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, UCS("debugTypeInfo"), o);
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
typename _DebugTypeInfoAccess<EncodingT>::connection_t
_DebugTypeInfoAccess<EncodingT>::addInsertSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_insertSignal.connect(subscriber);
}

template<class EncodingT>
typename _DebugTypeInfoAccess<EncodingT>::connection_t
_DebugTypeInfoAccess<EncodingT>::addUpdateSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_updateSignal.connect(subscriber);
}

template<class EncodingT>
typename _DebugTypeInfoAccess<EncodingT>::connection_t
_DebugTypeInfoAccess<EncodingT>::addDeleteSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_deleteSignal.connect(subscriber);
}

template<class EncodingT>
typename _DebugTypeInfoAccess<EncodingT>::connection_t
_DebugTypeInfoAccess<EncodingT>::addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber)  
{
	return m_transactionSignal.connect(subscriber);
}

template<class EncodingT>
void
_DebugTypeInfoAccess<EncodingT>::removeInsertSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_DebugTypeInfoAccess<EncodingT>::removeUpdateSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_DebugTypeInfoAccess<EncodingT>::removeDeleteSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_DebugTypeInfoAccess<EncodingT>::removeTransactionSignal(connection_t connection)  
{
	connection.disconnect();
}


NAMESPACE_END

#undef C
#undef A

