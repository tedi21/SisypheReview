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
_CppClassAccess<EncodingT>* _CppClassAccess<EncodingT>::m_instance = NULL;

template<class EncodingT>
_CppClassAccess<EncodingT>* 
_CppClassAccess<EncodingT>::getInstance()  
{
	if (m_instance == NULL) {
		m_instance = new _CppClassAccess<EncodingT>();
	}
	return m_instance;
}

template<class EncodingT>
_CppClassAccess<EncodingT>::_CppClassAccess()
: m_transactionOwner(false) 
{
	m_logger = &Category::getInstance(LOGNAME);
	m_logger->debugStream() << "constructor CppClassAccess " << m_transactionOwner;
}

template<class EncodingT>
_CppClassAccess<EncodingT>::~_CppClassAccess()
{
	cancelSelection();
	m_logger = NULL;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppClass<EncodingT> > >
_CppClassAccess<EncodingT>::getManyCppClasss(typename EncodingT::string_t const&  filter) const 
{
	boost::shared_ptr< _CppClass<EncodingT> > value;
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _CppClass<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(C("identifier"));
	columns.push_back(C("name"));
	columns.push_back(C("fullName"));
	columns.push_back(C("accessSpecifier"));
	columns.push_back(C("isStruct"));
	columns.push_back(C("isInterface"));
	columns.push_back(C("isAbstract"));
	columns.push_back(C("isTemplate"));
	columns.push_back(C("linesCount"));
	columns.push_back(C("lineNumber"));
	columns.push_back(C("startBlock"));
	columns.push_back(C("lengthBlock"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,C("cppClass")), filter) );
	while( statement.executeStep() ) {
		long long identifier;
		typename EncodingT::string_t name;
		typename EncodingT::string_t fullName;
		typename EncodingT::string_t accessSpecifier;
		long long isStruct;
		long long isInterface;
		long long isAbstract;
		long long isTemplate;
		long long linesCount;
		long long lineNumber;
		long long startBlock;
		long long lengthBlock;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, name ) &&
			statement.getText( 2, fullName ) &&
			statement.getText( 3, accessSpecifier ) &&
			statement.getInt64( 4, isStruct ) &&
			statement.getInt64( 5, isInterface ) &&
			statement.getInt64( 6, isAbstract ) &&
			statement.getInt64( 7, isTemplate ) &&
			statement.getInt64( 8, linesCount ) &&
			statement.getInt64( 9, lineNumber ) &&
			statement.getInt64( 10, startBlock ) &&
			statement.getInt64( 11, lengthBlock )) {
			value.reset(new _CppClass<EncodingT>(
				identifier,
				name,
				fullName,
				accessSpecifier,
				isStruct,
				isInterface,
				isAbstract,
				isTemplate,
				linesCount,
				lineNumber,
				startBlock,
				lengthBlock));
			tab.push_back(value);
		}
	}
	return tab;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppClass<EncodingT> > >
_CppClassAccess<EncodingT>::getAllCppClasss() const 
{
	return getManyCppClasss(EncodingT::EMPTY);
}

template<class EncodingT>
boost::shared_ptr< _CppClass<EncodingT> >
_CppClassAccess<EncodingT>::getOneCppClass(long long identifier) const 
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _CppClass<EncodingT> > > result = getManyCppClasss(C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppClass<EncodingT> > >
_CppClassAccess<EncodingT>::selectManyCppClasss(typename EncodingT::string_t const&  filter, bool nowait, bool addition)  
{
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _CppClass<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(C("identifier"));
	columns.push_back(C("name"));
	columns.push_back(C("fullName"));
	columns.push_back(C("accessSpecifier"));
	columns.push_back(C("isStruct"));
	columns.push_back(C("isInterface"));
	columns.push_back(C("isAbstract"));
	columns.push_back(C("isTemplate"));
	columns.push_back(C("linesCount"));
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
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,C("cppClass")), filter, nowait) );
	while( statement.executeStep() ) {
		long long identifier;
		typename EncodingT::string_t name;
		typename EncodingT::string_t fullName;
		typename EncodingT::string_t accessSpecifier;
		long long isStruct;
		long long isInterface;
		long long isAbstract;
		long long isTemplate;
		long long linesCount;
		long long lineNumber;
		long long startBlock;
		long long lengthBlock;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, name ) &&
			statement.getText( 2, fullName ) &&
			statement.getText( 3, accessSpecifier ) &&
			statement.getInt64( 4, isStruct ) &&
			statement.getInt64( 5, isInterface ) &&
			statement.getInt64( 6, isAbstract ) &&
			statement.getInt64( 7, isTemplate ) &&
			statement.getInt64( 8, linesCount ) &&
			statement.getInt64( 9, lineNumber ) &&
			statement.getInt64( 10, startBlock ) &&
			statement.getInt64( 11, lengthBlock )) {
			tab.push_back(boost::shared_ptr< _CppClass<EncodingT> >(new _CppClass<EncodingT>(
				identifier,
				name,
				fullName,
				accessSpecifier,
				isStruct,
				isInterface,
				isAbstract,
				isTemplate,
				linesCount,
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
boost::shared_ptr< _CppClass<EncodingT> >
_CppClassAccess<EncodingT>::selectOneCppClass(long long identifier, bool nowait, bool addition)  
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _CppClass<EncodingT> > > result = selectManyCppClasss(C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait, addition);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
bool
_CppClassAccess<EncodingT>::isSelectedCppClass(boost::shared_ptr< _CppClass<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	typename _CppClass<EncodingT>::CppClassIDEquality cppClassIdEquality(*o);
	return (!m_backup.empty() && (std::find_if(m_backup.begin(), m_backup.end(), cppClassIdEquality)!=m_backup.end()));
}

template<class EncodingT>
void
_CppClassAccess<EncodingT>::cancelSelection()  
{
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	_CppInheritanceAccess<EncodingT>* cppInheritanceAccess = _CppInheritanceAccess<EncodingT>::getInstance();
	if (!cppInheritanceAccess) {
		m_logger->errorStream() << "CppInheritanceAccess class is not initialized.";
		throw NullPointerException("CppInheritanceAccess class is not initialized.");
	}
	_CppFunctionAccess<EncodingT>* cppFunctionAccess = _CppFunctionAccess<EncodingT>::getInstance();
	if (!cppFunctionAccess) {
		m_logger->errorStream() << "CppFunctionAccess class is not initialized.";
		throw NullPointerException("CppFunctionAccess class is not initialized.");
	}
	_CppClassAccess<EncodingT>* internClasseAccess = _CppClassAccess<EncodingT>::getInstance();
	if (!internClasseAccess) {
		m_logger->errorStream() << "CppClassAccess class is not initialized.";
		throw NullPointerException("CppClassAccess class is not initialized.");
	}
	_CppAttributeAccess<EncodingT>* cppAttributeAccess = _CppAttributeAccess<EncodingT>::getInstance();
	if (!cppAttributeAccess) {
		m_logger->errorStream() << "CppAttributeAccess class is not initialized.";
		throw NullPointerException("CppAttributeAccess class is not initialized.");
	}
	_CppEnumAccess<EncodingT>* cppEnumAccess = _CppEnumAccess<EncodingT>::getInstance();
	if (!cppEnumAccess) {
		m_logger->errorStream() << "CppEnumAccess class is not initialized.";
		throw NullPointerException("CppEnumAccess class is not initialized.");
	}
	if (!m_backup.empty()) {
		if (connection->isTransactionInProgress() && m_transactionOwner) {
			connection->rollback();
			m_transactionOwner = false;
			m_transactionSignal(OPERATION_ACCESS_ROLLBACK);
		}
		m_backup.clear();
		cppInheritanceAccess->cancelSelection();
		cppFunctionAccess->cancelSelection();
		internClasseAccess->cancelSelection();
		cppAttributeAccess->cancelSelection();
		cppEnumAccess->cancelSelection();
	}
}

template<class EncodingT>
void
_CppClassAccess<EncodingT>::fillEncapsulationClass(boost::shared_ptr< _CppClass<EncodingT> > o)  
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
	_CppClassAccess<EncodingT>* encapsulationClassAccess = _CppClassAccess<EncodingT>::getInstance();
	if (!encapsulationClassAccess) {
		m_logger->errorStream() << "CppClassAccess class is not initialized.";
		throw NullPointerException("CppClassAccess class is not initialized.");
	}
	long long id;
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,C("idEncapsulationClass")), std::vector<typename EncodingT::string_t>(1,C("cppClass")), C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
	if( statement.executeStep() && statement.getInt64( 0, id ) && id != 0 ) {
		typename _CppClass<EncodingT>::CppClassIDEquality cppClassIdEquality(o->getIdentifier());
		boost::shared_ptr< _CppClass<EncodingT> > val = encapsulationClassAccess->getOneCppClass(id);
		typename std::list< boost::shared_ptr<_CppClass<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppClassIdEquality);
		if (save != m_backup.end()) {
			(*save)->setEncapsulationClass(val);
		}
		o->setEncapsulationClass(val);
	}
	else {
		m_logger->debugStream() << "identifier not found.";
	}
}

template<class EncodingT>
void
_CppClassAccess<EncodingT>::fillCppFile(boost::shared_ptr< _CppClass<EncodingT> > o)  
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
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,C("idFile")), std::vector<typename EncodingT::string_t>(1,C("cppClass")), C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
	if( statement.executeStep() && statement.getInt64( 0, id ) && id != 0 ) {
		typename _CppClass<EncodingT>::CppClassIDEquality cppClassIdEquality(o->getIdentifier());
		boost::shared_ptr< _CppFile<EncodingT> > val = cppFileAccess->getOneCppFile(id);
		typename std::list< boost::shared_ptr<_CppClass<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppClassIdEquality);
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
_CppClassAccess<EncodingT>::fillAllCppInheritances(boost::shared_ptr< _CppClass<EncodingT> > o, bool nowait)  
{
	fillManyCppInheritances(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_CppClassAccess<EncodingT>::fillOneCppInheritance(boost::shared_ptr< _CppClass<EncodingT> > o, long long identifier, bool nowait)  
{
	fillManyCppInheritances(o, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait);
}

template<class EncodingT>
void
_CppClassAccess<EncodingT>::fillManyCppInheritances(boost::shared_ptr< _CppClass<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_CppInheritanceAccess<EncodingT>* cppInheritanceAccess = _CppInheritanceAccess<EncodingT>::getInstance();
	if (!cppInheritanceAccess) {
		m_logger->errorStream() << "CppInheritanceAccess class is not initialized.";
		throw NullPointerException("CppInheritanceAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _CppInheritance<EncodingT> > > tab;
	typename EncodingT::string_t cppInheritanceFilter = C("idDerived = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		cppInheritanceFilter += C(" AND ") + filter;
	}
	typename _CppClass<EncodingT>::CppClassIDEquality cppClassIdEquality(o->getIdentifier());
	typename std::list< boost::shared_ptr< _CppClass<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppClassIdEquality);
	if (save != m_backup.end())
	{
		tab = cppInheritanceAccess->selectManyCppInheritances(cppInheritanceFilter, nowait, true);
		(*save)->clearCppInheritances();
		(*save)->insertCppInheritance((*save)->getCppInheritancesEnd(), tab.begin(), tab.end());
	}
	else
	{
		tab = cppInheritanceAccess->getManyCppInheritances(cppInheritanceFilter);
	}
	o->clearCppInheritances();
	o->insertCppInheritance(o->getCppInheritancesEnd(), tab.begin(), tab.end());
}

template<class EncodingT>
void
_CppClassAccess<EncodingT>::fillAllCppFunctions(boost::shared_ptr< _CppClass<EncodingT> > o, bool nowait)  
{
	fillManyCppFunctions(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_CppClassAccess<EncodingT>::fillOneCppFunction(boost::shared_ptr< _CppClass<EncodingT> > o, long long identifier, bool nowait)  
{
	fillManyCppFunctions(o, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait);
}

template<class EncodingT>
void
_CppClassAccess<EncodingT>::fillManyCppFunctions(boost::shared_ptr< _CppClass<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_CppFunctionAccess<EncodingT>* cppFunctionAccess = _CppFunctionAccess<EncodingT>::getInstance();
	if (!cppFunctionAccess) {
		m_logger->errorStream() << "CppFunctionAccess class is not initialized.";
		throw NullPointerException("CppFunctionAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _CppFunction<EncodingT> > > tab;
	typename EncodingT::string_t cppFunctionFilter = C("idClass = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		cppFunctionFilter += C(" AND ") + filter;
	}
	typename _CppClass<EncodingT>::CppClassIDEquality cppClassIdEquality(o->getIdentifier());
	typename std::list< boost::shared_ptr< _CppClass<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppClassIdEquality);
	if (save != m_backup.end())
	{
		tab = cppFunctionAccess->selectManyCppFunctions(cppFunctionFilter, nowait, true);
		(*save)->clearCppFunctions();
		(*save)->insertCppFunction((*save)->getCppFunctionsEnd(), tab.begin(), tab.end());
	}
	else
	{
		tab = cppFunctionAccess->getManyCppFunctions(cppFunctionFilter);
	}
	o->clearCppFunctions();
	o->insertCppFunction(o->getCppFunctionsEnd(), tab.begin(), tab.end());
}

template<class EncodingT>
void
_CppClassAccess<EncodingT>::fillAllInternClasses(boost::shared_ptr< _CppClass<EncodingT> > o, bool nowait)  
{
	fillManyInternClasses(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_CppClassAccess<EncodingT>::fillOneInternClasse(boost::shared_ptr< _CppClass<EncodingT> > o, long long identifier, bool nowait)  
{
	fillManyInternClasses(o, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait);
}

template<class EncodingT>
void
_CppClassAccess<EncodingT>::fillManyInternClasses(boost::shared_ptr< _CppClass<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_CppClassAccess<EncodingT>* internClasseAccess = _CppClassAccess<EncodingT>::getInstance();
	if (!internClasseAccess) {
		m_logger->errorStream() << "CppClassAccess class is not initialized.";
		throw NullPointerException("CppClassAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _CppClass<EncodingT> > > tab;
	typename EncodingT::string_t cppClassFilter = C("idEncapsulationClass = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		cppClassFilter += C(" AND ") + filter;
	}
	typename _CppClass<EncodingT>::CppClassIDEquality cppClassIdEquality(o->getIdentifier());
	typename std::list< boost::shared_ptr< _CppClass<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppClassIdEquality);
	if (save != m_backup.end())
	{
		tab = internClasseAccess->selectManyCppClasss(cppClassFilter, nowait, true);
		(*save)->clearInternClasses();
		(*save)->insertInternClasse((*save)->getInternClassesEnd(), tab.begin(), tab.end());
	}
	else
	{
		tab = internClasseAccess->getManyCppClasss(cppClassFilter);
	}
	o->clearInternClasses();
	o->insertInternClasse(o->getInternClassesEnd(), tab.begin(), tab.end());
}

template<class EncodingT>
void
_CppClassAccess<EncodingT>::fillAllCppAttributes(boost::shared_ptr< _CppClass<EncodingT> > o, bool nowait)  
{
	fillManyCppAttributes(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_CppClassAccess<EncodingT>::fillOneCppAttribute(boost::shared_ptr< _CppClass<EncodingT> > o, long long identifier, bool nowait)  
{
	fillManyCppAttributes(o, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait);
}

template<class EncodingT>
void
_CppClassAccess<EncodingT>::fillManyCppAttributes(boost::shared_ptr< _CppClass<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_CppAttributeAccess<EncodingT>* cppAttributeAccess = _CppAttributeAccess<EncodingT>::getInstance();
	if (!cppAttributeAccess) {
		m_logger->errorStream() << "CppAttributeAccess class is not initialized.";
		throw NullPointerException("CppAttributeAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _CppAttribute<EncodingT> > > tab;
	typename EncodingT::string_t cppAttributeFilter = C("idClass = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		cppAttributeFilter += C(" AND ") + filter;
	}
	typename _CppClass<EncodingT>::CppClassIDEquality cppClassIdEquality(o->getIdentifier());
	typename std::list< boost::shared_ptr< _CppClass<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppClassIdEquality);
	if (save != m_backup.end())
	{
		tab = cppAttributeAccess->selectManyCppAttributes(cppAttributeFilter, nowait, true);
		(*save)->clearCppAttributes();
		(*save)->insertCppAttribute((*save)->getCppAttributesEnd(), tab.begin(), tab.end());
	}
	else
	{
		tab = cppAttributeAccess->getManyCppAttributes(cppAttributeFilter);
	}
	o->clearCppAttributes();
	o->insertCppAttribute(o->getCppAttributesEnd(), tab.begin(), tab.end());
}

template<class EncodingT>
void
_CppClassAccess<EncodingT>::fillAllCppEnums(boost::shared_ptr< _CppClass<EncodingT> > o, bool nowait)  
{
	fillManyCppEnums(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_CppClassAccess<EncodingT>::fillOneCppEnum(boost::shared_ptr< _CppClass<EncodingT> > o, long long identifier, bool nowait)  
{
	fillManyCppEnums(o, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait);
}

template<class EncodingT>
void
_CppClassAccess<EncodingT>::fillManyCppEnums(boost::shared_ptr< _CppClass<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_CppEnumAccess<EncodingT>* cppEnumAccess = _CppEnumAccess<EncodingT>::getInstance();
	if (!cppEnumAccess) {
		m_logger->errorStream() << "CppEnumAccess class is not initialized.";
		throw NullPointerException("CppEnumAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _CppEnum<EncodingT> > > tab;
	typename EncodingT::string_t cppEnumFilter = C("idClass = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		cppEnumFilter += C(" AND ") + filter;
	}
	typename _CppClass<EncodingT>::CppClassIDEquality cppClassIdEquality(o->getIdentifier());
	typename std::list< boost::shared_ptr< _CppClass<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppClassIdEquality);
	if (save != m_backup.end())
	{
		tab = cppEnumAccess->selectManyCppEnums(cppEnumFilter, nowait, true);
		(*save)->clearCppEnums();
		(*save)->insertCppEnum((*save)->getCppEnumsEnd(), tab.begin(), tab.end());
	}
	else
	{
		tab = cppEnumAccess->getManyCppEnums(cppEnumFilter);
	}
	o->clearCppEnums();
	o->insertCppEnum(o->getCppEnumsEnd(), tab.begin(), tab.end());
}

template<class EncodingT>
bool
_CppClassAccess<EncodingT>::isModifiedCppClass(boost::shared_ptr< _CppClass<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_CppInheritanceAccess<EncodingT>* cppInheritanceAccess = _CppInheritanceAccess<EncodingT>::getInstance();
	if (!cppInheritanceAccess) {
		m_logger->errorStream() << "CppInheritanceAccess class is not initialized.";
		throw NullPointerException("CppInheritanceAccess class is not initialized.");
	}
	_CppFunctionAccess<EncodingT>* cppFunctionAccess = _CppFunctionAccess<EncodingT>::getInstance();
	if (!cppFunctionAccess) {
		m_logger->errorStream() << "CppFunctionAccess class is not initialized.";
		throw NullPointerException("CppFunctionAccess class is not initialized.");
	}
	_CppClassAccess<EncodingT>* internClasseAccess = _CppClassAccess<EncodingT>::getInstance();
	if (!internClasseAccess) {
		m_logger->errorStream() << "CppClassAccess class is not initialized.";
		throw NullPointerException("CppClassAccess class is not initialized.");
	}
	_CppAttributeAccess<EncodingT>* cppAttributeAccess = _CppAttributeAccess<EncodingT>::getInstance();
	if (!cppAttributeAccess) {
		m_logger->errorStream() << "CppAttributeAccess class is not initialized.";
		throw NullPointerException("CppAttributeAccess class is not initialized.");
	}
	_CppEnumAccess<EncodingT>* cppEnumAccess = _CppEnumAccess<EncodingT>::getInstance();
	if (!cppEnumAccess) {
		m_logger->errorStream() << "CppEnumAccess class is not initialized.";
		throw NullPointerException("CppEnumAccess class is not initialized.");
	}
	typename _CppClass<EncodingT>::CppClassIDEquality cppClassIdEquality(*o);
	typename std::list< boost::shared_ptr< _CppClass<EncodingT> > >::const_iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppClassIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getName() != o->getName());
	bUpdate = bUpdate || ((*save)->getFullName() != o->getFullName());
	bUpdate = bUpdate || ((*save)->getAccessSpecifier() != o->getAccessSpecifier());
	bUpdate = bUpdate || ((*save)->getIsStruct() != o->getIsStruct());
	bUpdate = bUpdate || ((*save)->getIsInterface() != o->getIsInterface());
	bUpdate = bUpdate || ((*save)->getIsAbstract() != o->getIsAbstract());
	bUpdate = bUpdate || ((*save)->getIsTemplate() != o->getIsTemplate());
	bUpdate = bUpdate || ((*save)->getLinesCount() != o->getLinesCount());
	bUpdate = bUpdate || ((*save)->getLineNumber() != o->getLineNumber());
	bUpdate = bUpdate || ((*save)->getStartBlock() != o->getStartBlock());
	bUpdate = bUpdate || ((*save)->getLengthBlock() != o->getLengthBlock());
	bUpdate = bUpdate || (!(*save)->isNullEncapsulationClass() && !o->isNullEncapsulationClass() && !typename _CppClass<EncodingT>::CppClassIDEquality(*(*save)->getEncapsulationClass())(o->getEncapsulationClass()))
		|| ((*save)->isNullEncapsulationClass() && !o->isNullEncapsulationClass()) 
		|| (!(*save)->isNullEncapsulationClass() && o->isNullEncapsulationClass());
	bUpdate = bUpdate || (!(*save)->isNullCppFile() && !o->isNullCppFile() && !typename _CppFile<EncodingT>::CppFileIDEquality(*(*save)->getCppFile())(o->getCppFile()))
		|| ((*save)->isNullCppFile() && !o->isNullCppFile()) 
		|| (!(*save)->isNullCppFile() && o->isNullCppFile());
	typename _CppClass<EncodingT>::CppInheritanceIterator cppInheritance;
	for ( cppInheritance=o->getCppInheritancesBeginning(); cppInheritance!=o->getCppInheritancesEnd(); ++cppInheritance ) {
		if (!(*cppInheritance)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppInheritance<EncodingT>::CppInheritanceIDEquality cppInheritanceIdEquality(*(*cppInheritance));
		bUpdate = bUpdate || (std::find_if((*save)->getCppInheritancesBeginning(), (*save)->getCppInheritancesEnd(), cppInheritanceIdEquality) == (*save)->getCppInheritancesEnd())
			|| (cppInheritanceAccess->isModifiedCppInheritance(*cppInheritance));
	}
	for ( cppInheritance=(*save)->getCppInheritancesBeginning(); cppInheritance<(*save)->getCppInheritancesEnd(); ++cppInheritance ) {
		if (!(*cppInheritance)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppInheritance<EncodingT>::CppInheritanceIDEquality cppInheritanceIdEquality(*(*cppInheritance));
		bUpdate = bUpdate || (std::find_if(o->getCppInheritancesBeginning(), o->getCppInheritancesEnd(), cppInheritanceIdEquality) == o->getCppInheritancesEnd());
	}
	typename _CppClass<EncodingT>::CppFunctionIterator cppFunction;
	for ( cppFunction=o->getCppFunctionsBeginning(); cppFunction!=o->getCppFunctionsEnd(); ++cppFunction ) {
		if (!(*cppFunction)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppFunction<EncodingT>::CppFunctionIDEquality cppFunctionIdEquality(*(*cppFunction));
		bUpdate = bUpdate || (std::find_if((*save)->getCppFunctionsBeginning(), (*save)->getCppFunctionsEnd(), cppFunctionIdEquality) == (*save)->getCppFunctionsEnd())
			|| (cppFunctionAccess->isModifiedCppFunction(*cppFunction));
	}
	for ( cppFunction=(*save)->getCppFunctionsBeginning(); cppFunction<(*save)->getCppFunctionsEnd(); ++cppFunction ) {
		if (!(*cppFunction)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppFunction<EncodingT>::CppFunctionIDEquality cppFunctionIdEquality(*(*cppFunction));
		bUpdate = bUpdate || (std::find_if(o->getCppFunctionsBeginning(), o->getCppFunctionsEnd(), cppFunctionIdEquality) == o->getCppFunctionsEnd());
	}
	typename _CppClass<EncodingT>::InternClasseIterator internClasse;
	for ( internClasse=o->getInternClassesBeginning(); internClasse!=o->getInternClassesEnd(); ++internClasse ) {
		if (!(*internClasse)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppClass<EncodingT>::CppClassIDEquality internClasseIdEquality(*(*internClasse));
		bUpdate = bUpdate || (std::find_if((*save)->getInternClassesBeginning(), (*save)->getInternClassesEnd(), internClasseIdEquality) == (*save)->getInternClassesEnd())
			|| (internClasseAccess->isModifiedCppClass(*internClasse));
	}
	for ( internClasse=(*save)->getInternClassesBeginning(); internClasse<(*save)->getInternClassesEnd(); ++internClasse ) {
		if (!(*internClasse)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppClass<EncodingT>::CppClassIDEquality internClasseIdEquality(*(*internClasse));
		bUpdate = bUpdate || (std::find_if(o->getInternClassesBeginning(), o->getInternClassesEnd(), internClasseIdEquality) == o->getInternClassesEnd());
	}
	typename _CppClass<EncodingT>::CppAttributeIterator cppAttribute;
	for ( cppAttribute=o->getCppAttributesBeginning(); cppAttribute!=o->getCppAttributesEnd(); ++cppAttribute ) {
		if (!(*cppAttribute)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppAttribute<EncodingT>::CppAttributeIDEquality cppAttributeIdEquality(*(*cppAttribute));
		bUpdate = bUpdate || (std::find_if((*save)->getCppAttributesBeginning(), (*save)->getCppAttributesEnd(), cppAttributeIdEquality) == (*save)->getCppAttributesEnd())
			|| (cppAttributeAccess->isModifiedCppAttribute(*cppAttribute));
	}
	for ( cppAttribute=(*save)->getCppAttributesBeginning(); cppAttribute<(*save)->getCppAttributesEnd(); ++cppAttribute ) {
		if (!(*cppAttribute)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppAttribute<EncodingT>::CppAttributeIDEquality cppAttributeIdEquality(*(*cppAttribute));
		bUpdate = bUpdate || (std::find_if(o->getCppAttributesBeginning(), o->getCppAttributesEnd(), cppAttributeIdEquality) == o->getCppAttributesEnd());
	}
	typename _CppClass<EncodingT>::CppEnumIterator cppEnum;
	for ( cppEnum=o->getCppEnumsBeginning(); cppEnum!=o->getCppEnumsEnd(); ++cppEnum ) {
		if (!(*cppEnum)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppEnum<EncodingT>::CppEnumIDEquality cppEnumIdEquality(*(*cppEnum));
		bUpdate = bUpdate || (std::find_if((*save)->getCppEnumsBeginning(), (*save)->getCppEnumsEnd(), cppEnumIdEquality) == (*save)->getCppEnumsEnd())
			|| (cppEnumAccess->isModifiedCppEnum(*cppEnum));
	}
	for ( cppEnum=(*save)->getCppEnumsBeginning(); cppEnum<(*save)->getCppEnumsEnd(); ++cppEnum ) {
		if (!(*cppEnum)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppEnum<EncodingT>::CppEnumIDEquality cppEnumIdEquality(*(*cppEnum));
		bUpdate = bUpdate || (std::find_if(o->getCppEnumsBeginning(), o->getCppEnumsEnd(), cppEnumIdEquality) == o->getCppEnumsEnd());
	}
	return bUpdate;
}

template<class EncodingT>
void
_CppClassAccess<EncodingT>::updateCppClass(boost::shared_ptr< _CppClass<EncodingT> > o)  
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
	_CppInheritanceAccess<EncodingT>* cppInheritanceAccess = _CppInheritanceAccess<EncodingT>::getInstance();
	if (!cppInheritanceAccess) {
		m_logger->errorStream() << "CppInheritanceAccess class is not initialized.";
		throw NullPointerException("CppInheritanceAccess class is not initialized.");
	}
	_CppFunctionAccess<EncodingT>* cppFunctionAccess = _CppFunctionAccess<EncodingT>::getInstance();
	if (!cppFunctionAccess) {
		m_logger->errorStream() << "CppFunctionAccess class is not initialized.";
		throw NullPointerException("CppFunctionAccess class is not initialized.");
	}
	_CppClassAccess<EncodingT>* internClasseAccess = _CppClassAccess<EncodingT>::getInstance();
	if (!internClasseAccess) {
		m_logger->errorStream() << "CppClassAccess class is not initialized.";
		throw NullPointerException("CppClassAccess class is not initialized.");
	}
	_CppAttributeAccess<EncodingT>* cppAttributeAccess = _CppAttributeAccess<EncodingT>::getInstance();
	if (!cppAttributeAccess) {
		m_logger->errorStream() << "CppAttributeAccess class is not initialized.";
		throw NullPointerException("CppAttributeAccess class is not initialized.");
	}
	_CppEnumAccess<EncodingT>* cppEnumAccess = _CppEnumAccess<EncodingT>::getInstance();
	if (!cppEnumAccess) {
		m_logger->errorStream() << "CppEnumAccess class is not initialized.";
		throw NullPointerException("CppEnumAccess class is not initialized.");
	}
	typename _CppClass<EncodingT>::CppClassIDEquality cppClassIdEquality(*o);
	typename std::list< boost::shared_ptr< _CppClass<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppClassIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	try {
		if ( (*save)->getName() != o->getName() ) {
			values.addText( o->getName() );
			fields.push_back( C("name") );
		}
		if ( (*save)->getFullName() != o->getFullName() ) {
			values.addText( o->getFullName() );
			fields.push_back( C("fullName") );
		}
		if ( (*save)->getAccessSpecifier() != o->getAccessSpecifier() ) {
			values.addText( o->getAccessSpecifier() );
			fields.push_back( C("accessSpecifier") );
		}
		if ( (*save)->getIsStruct() != o->getIsStruct() ) {
			values.addInt64( o->getIsStruct() );
			fields.push_back( C("isStruct") );
		}
		if ( (*save)->getIsInterface() != o->getIsInterface() ) {
			values.addInt64( o->getIsInterface() );
			fields.push_back( C("isInterface") );
		}
		if ( (*save)->getIsAbstract() != o->getIsAbstract() ) {
			values.addInt64( o->getIsAbstract() );
			fields.push_back( C("isAbstract") );
		}
		if ( (*save)->getIsTemplate() != o->getIsTemplate() ) {
			values.addInt64( o->getIsTemplate() );
			fields.push_back( C("isTemplate") );
		}
		if ( (*save)->getLinesCount() != o->getLinesCount() ) {
			values.addInt64( o->getLinesCount() );
			fields.push_back( C("linesCount") );
		}
		if ( (*save)->getLineNumber() != o->getLineNumber() ) {
			values.addInt64( o->getLineNumber() );
			fields.push_back( C("lineNumber") );
		}
		if ( (*save)->getStartBlock() != o->getStartBlock() ) {
			values.addInt64( o->getStartBlock() );
			fields.push_back( C("startBlock") );
		}
		if ( (*save)->getLengthBlock() != o->getLengthBlock() ) {
			values.addInt64( o->getLengthBlock() );
			fields.push_back( C("lengthBlock") );
		}
		if ( !o->isNullEncapsulationClass() && typename _CppClass<EncodingT>::CppClassIDEquality(-1)(o->getEncapsulationClass()) ) {
			m_logger->errorStream() << "idEncapsulationClass : Identifier is null.";
			throw InvalidQueryException("idEncapsulationClass : Identifier is null.");
		}
		else if ( !o->isNullEncapsulationClass() && !typename _CppClass<EncodingT>::CppClassIDEquality(*(o->getEncapsulationClass()))((*save)->getEncapsulationClass()) ) {
			values.addInt64( o->getEncapsulationClass()->getIdentifier() );
			fields.push_back( C("idEncapsulationClass") );
		}
		else if ( o->isNullEncapsulationClass() && !(*save)->isNullEncapsulationClass() ) {
			values.addNull();
			fields.push_back( C("idEncapsulationClass") );
		}
		if ( !o->isNullCppFile() && typename _CppFile<EncodingT>::CppFileIDEquality(-1)(o->getCppFile()) ) {
			m_logger->errorStream() << "idFile : Identifier is null.";
			throw InvalidQueryException("idFile : Identifier is null.");
		}
		else if ( !o->isNullCppFile() && !typename _CppFile<EncodingT>::CppFileIDEquality(*(o->getCppFile()))((*save)->getCppFile()) ) {
			values.addInt64( o->getCppFile()->getIdentifier() );
			fields.push_back( C("idFile") );
		}
		else if ( o->isNullCppFile() && !(*save)->isNullCppFile() ) {
			m_logger->errorStream() << "idFile : null reference is forbidden.";
			throw InvalidQueryException("idFile : null reference is forbidden.");
		}
		std::vector< boost::shared_ptr< _CppInheritance<EncodingT> > > listOfCppInheritanceToAdd;
		std::vector< boost::shared_ptr< _CppInheritance<EncodingT> > > listOfCppInheritanceToUpdate;
		typename _CppClass<EncodingT>::CppInheritanceIterator cppInheritance;
		for ( cppInheritance=o->getCppInheritancesBeginning(); cppInheritance!=o->getCppInheritancesEnd(); ++cppInheritance ) {
			if (!(*cppInheritance)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*cppInheritance)->setDerived(o);
			typename _CppInheritance<EncodingT>::CppInheritanceIDEquality cppInheritanceIdEquality(*(*cppInheritance));
			if ( std::find_if((*save)->getCppInheritancesBeginning(), (*save)->getCppInheritancesEnd(), cppInheritanceIdEquality) == (*save)->getCppInheritancesEnd()) {
				listOfCppInheritanceToAdd.push_back(*cppInheritance);
			}
			else {
				if (cppInheritanceAccess->isModifiedCppInheritance(*cppInheritance))
					listOfCppInheritanceToUpdate.push_back(*cppInheritance);
			}
		}
		std::vector< boost::shared_ptr< _CppInheritance<EncodingT> > > listOfCppInheritanceToRemove;
		for ( cppInheritance=(*save)->getCppInheritancesBeginning(); cppInheritance<(*save)->getCppInheritancesEnd(); ++cppInheritance ) {
			if (!(*cppInheritance)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			typename _CppInheritance<EncodingT>::CppInheritanceIDEquality cppInheritanceIdEquality(*(*cppInheritance));
			if ( std::find_if(o->getCppInheritancesBeginning(), o->getCppInheritancesEnd(), cppInheritanceIdEquality) == o->getCppInheritancesEnd()) {
				listOfCppInheritanceToRemove.push_back(*cppInheritance);
			}
		}
		std::vector< boost::shared_ptr< _CppFunction<EncodingT> > > listOfCppFunctionToAdd;
		std::vector< boost::shared_ptr< _CppFunction<EncodingT> > > listOfCppFunctionToUpdate;
		typename _CppClass<EncodingT>::CppFunctionIterator cppFunction;
		for ( cppFunction=o->getCppFunctionsBeginning(); cppFunction!=o->getCppFunctionsEnd(); ++cppFunction ) {
			if (!(*cppFunction)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*cppFunction)->setCppClass(o);
			typename _CppFunction<EncodingT>::CppFunctionIDEquality cppFunctionIdEquality(*(*cppFunction));
			if ( std::find_if((*save)->getCppFunctionsBeginning(), (*save)->getCppFunctionsEnd(), cppFunctionIdEquality) == (*save)->getCppFunctionsEnd()) {
				listOfCppFunctionToAdd.push_back(*cppFunction);
			}
			else {
				if (cppFunctionAccess->isModifiedCppFunction(*cppFunction))
					listOfCppFunctionToUpdate.push_back(*cppFunction);
			}
		}
		std::vector< boost::shared_ptr< _CppFunction<EncodingT> > > listOfCppFunctionToRemove;
		for ( cppFunction=(*save)->getCppFunctionsBeginning(); cppFunction<(*save)->getCppFunctionsEnd(); ++cppFunction ) {
			if (!(*cppFunction)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			typename _CppFunction<EncodingT>::CppFunctionIDEquality cppFunctionIdEquality(*(*cppFunction));
			if ( std::find_if(o->getCppFunctionsBeginning(), o->getCppFunctionsEnd(), cppFunctionIdEquality) == o->getCppFunctionsEnd()) {
				listOfCppFunctionToRemove.push_back(*cppFunction);
			}
		}
		std::vector< boost::shared_ptr< _CppClass<EncodingT> > > listOfInternClasseToAdd;
		std::vector< boost::shared_ptr< _CppClass<EncodingT> > > listOfInternClasseToUpdate;
		typename _CppClass<EncodingT>::InternClasseIterator internClasse;
		for ( internClasse=o->getInternClassesBeginning(); internClasse!=o->getInternClassesEnd(); ++internClasse ) {
			if (!(*internClasse)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*internClasse)->setEncapsulationClass(o);
			typename _CppClass<EncodingT>::CppClassIDEquality internClasseIdEquality(*(*internClasse));
			if ( std::find_if((*save)->getInternClassesBeginning(), (*save)->getInternClassesEnd(), internClasseIdEquality) == (*save)->getInternClassesEnd()) {
				listOfInternClasseToAdd.push_back(*internClasse);
			}
			else {
				if (internClasseAccess->isModifiedCppClass(*internClasse))
					listOfInternClasseToUpdate.push_back(*internClasse);
			}
		}
		std::vector< boost::shared_ptr< _CppClass<EncodingT> > > listOfInternClasseToRemove;
		for ( internClasse=(*save)->getInternClassesBeginning(); internClasse<(*save)->getInternClassesEnd(); ++internClasse ) {
			if (!(*internClasse)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			typename _CppClass<EncodingT>::CppClassIDEquality internClasseIdEquality(*(*internClasse));
			if ( std::find_if(o->getInternClassesBeginning(), o->getInternClassesEnd(), internClasseIdEquality) == o->getInternClassesEnd()) {
				listOfInternClasseToRemove.push_back(*internClasse);
			}
		}
		std::vector< boost::shared_ptr< _CppAttribute<EncodingT> > > listOfCppAttributeToAdd;
		std::vector< boost::shared_ptr< _CppAttribute<EncodingT> > > listOfCppAttributeToUpdate;
		typename _CppClass<EncodingT>::CppAttributeIterator cppAttribute;
		for ( cppAttribute=o->getCppAttributesBeginning(); cppAttribute!=o->getCppAttributesEnd(); ++cppAttribute ) {
			if (!(*cppAttribute)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*cppAttribute)->setCppClass(o);
			typename _CppAttribute<EncodingT>::CppAttributeIDEquality cppAttributeIdEquality(*(*cppAttribute));
			if ( std::find_if((*save)->getCppAttributesBeginning(), (*save)->getCppAttributesEnd(), cppAttributeIdEquality) == (*save)->getCppAttributesEnd()) {
				listOfCppAttributeToAdd.push_back(*cppAttribute);
			}
			else {
				if (cppAttributeAccess->isModifiedCppAttribute(*cppAttribute))
					listOfCppAttributeToUpdate.push_back(*cppAttribute);
			}
		}
		std::vector< boost::shared_ptr< _CppAttribute<EncodingT> > > listOfCppAttributeToRemove;
		for ( cppAttribute=(*save)->getCppAttributesBeginning(); cppAttribute<(*save)->getCppAttributesEnd(); ++cppAttribute ) {
			if (!(*cppAttribute)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			typename _CppAttribute<EncodingT>::CppAttributeIDEquality cppAttributeIdEquality(*(*cppAttribute));
			if ( std::find_if(o->getCppAttributesBeginning(), o->getCppAttributesEnd(), cppAttributeIdEquality) == o->getCppAttributesEnd()) {
				listOfCppAttributeToRemove.push_back(*cppAttribute);
			}
		}
		std::vector< boost::shared_ptr< _CppEnum<EncodingT> > > listOfCppEnumToAdd;
		std::vector< boost::shared_ptr< _CppEnum<EncodingT> > > listOfCppEnumToUpdate;
		typename _CppClass<EncodingT>::CppEnumIterator cppEnum;
		for ( cppEnum=o->getCppEnumsBeginning(); cppEnum!=o->getCppEnumsEnd(); ++cppEnum ) {
			if (!(*cppEnum)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*cppEnum)->setCppClass(o);
			typename _CppEnum<EncodingT>::CppEnumIDEquality cppEnumIdEquality(*(*cppEnum));
			if ( std::find_if((*save)->getCppEnumsBeginning(), (*save)->getCppEnumsEnd(), cppEnumIdEquality) == (*save)->getCppEnumsEnd()) {
				listOfCppEnumToAdd.push_back(*cppEnum);
			}
			else {
				if (cppEnumAccess->isModifiedCppEnum(*cppEnum))
					listOfCppEnumToUpdate.push_back(*cppEnum);
			}
		}
		std::vector< boost::shared_ptr< _CppEnum<EncodingT> > > listOfCppEnumToRemove;
		for ( cppEnum=(*save)->getCppEnumsBeginning(); cppEnum<(*save)->getCppEnumsEnd(); ++cppEnum ) {
			if (!(*cppEnum)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			typename _CppEnum<EncodingT>::CppEnumIDEquality cppEnumIdEquality(*(*cppEnum));
			if ( std::find_if(o->getCppEnumsBeginning(), o->getCppEnumsEnd(), cppEnumIdEquality) == o->getCppEnumsEnd()) {
				listOfCppEnumToRemove.push_back(*cppEnum);
			}
		}
		if (!fields.empty()) {
			statement.swap( connection->update(C("cppClass"), fields, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, C("cppClass"), o);
		}
		for ( cppInheritance=listOfCppInheritanceToAdd.begin(); cppInheritance!=listOfCppInheritanceToAdd.end() ; ++cppInheritance ) {
			cppInheritanceAccess->insertCppInheritance(*cppInheritance);
		}
		for ( cppInheritance=listOfCppInheritanceToUpdate.begin(); cppInheritance!=listOfCppInheritanceToUpdate.end() ; ++cppInheritance ) {
			cppInheritanceAccess->updateCppInheritance(*cppInheritance);
		}
		for ( cppInheritance=listOfCppInheritanceToRemove.begin(); cppInheritance!=listOfCppInheritanceToRemove.end() ; ++cppInheritance ) {
			cppInheritanceAccess->deleteCppInheritance(*cppInheritance);
		}
		for ( cppFunction=listOfCppFunctionToAdd.begin(); cppFunction!=listOfCppFunctionToAdd.end() ; ++cppFunction ) {
			cppFunctionAccess->insertCppFunction(*cppFunction);
		}
		for ( cppFunction=listOfCppFunctionToUpdate.begin(); cppFunction!=listOfCppFunctionToUpdate.end() ; ++cppFunction ) {
			cppFunctionAccess->updateCppFunction(*cppFunction);
		}
		for ( cppFunction=listOfCppFunctionToRemove.begin(); cppFunction!=listOfCppFunctionToRemove.end() ; ++cppFunction ) {
			cppFunctionAccess->fillCppClass(*cppFunction);
			(*cppFunction)->eraseCppClass();
			cppFunctionAccess->updateCppFunction(*cppFunction);
		}
		for ( internClasse=listOfInternClasseToAdd.begin(); internClasse!=listOfInternClasseToAdd.end() ; ++internClasse ) {
			internClasseAccess->insertCppClass(*internClasse);
		}
		for ( internClasse=listOfInternClasseToUpdate.begin(); internClasse!=listOfInternClasseToUpdate.end() ; ++internClasse ) {
			internClasseAccess->updateCppClass(*internClasse);
		}
		for ( internClasse=listOfInternClasseToRemove.begin(); internClasse!=listOfInternClasseToRemove.end() ; ++internClasse ) {
			internClasseAccess->fillEncapsulationClass(*internClasse);
			(*internClasse)->eraseEncapsulationClass();
			internClasseAccess->updateCppClass(*internClasse);
		}
		for ( cppAttribute=listOfCppAttributeToAdd.begin(); cppAttribute!=listOfCppAttributeToAdd.end() ; ++cppAttribute ) {
			cppAttributeAccess->insertCppAttribute(*cppAttribute);
		}
		for ( cppAttribute=listOfCppAttributeToUpdate.begin(); cppAttribute!=listOfCppAttributeToUpdate.end() ; ++cppAttribute ) {
			cppAttributeAccess->updateCppAttribute(*cppAttribute);
		}
		for ( cppAttribute=listOfCppAttributeToRemove.begin(); cppAttribute!=listOfCppAttributeToRemove.end() ; ++cppAttribute ) {
			cppAttributeAccess->deleteCppAttribute(*cppAttribute);
		}
		for ( cppEnum=listOfCppEnumToAdd.begin(); cppEnum!=listOfCppEnumToAdd.end() ; ++cppEnum ) {
			cppEnumAccess->insertCppEnum(*cppEnum);
		}
		for ( cppEnum=listOfCppEnumToUpdate.begin(); cppEnum!=listOfCppEnumToUpdate.end() ; ++cppEnum ) {
			cppEnumAccess->updateCppEnum(*cppEnum);
		}
		for ( cppEnum=listOfCppEnumToRemove.begin(); cppEnum!=listOfCppEnumToRemove.end() ; ++cppEnum ) {
			cppEnumAccess->fillCppClass(*cppEnum);
			(*cppEnum)->eraseCppClass();
			cppEnumAccess->updateCppEnum(*cppEnum);
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
_CppClassAccess<EncodingT>::insertCppClass(boost::shared_ptr< _CppClass<EncodingT> > o)  
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
	_CppInheritanceAccess<EncodingT>* cppInheritanceAccess = _CppInheritanceAccess<EncodingT>::getInstance();
	if (!cppInheritanceAccess) {
		m_logger->errorStream() << "CppInheritanceAccess class is not initialized.";
		throw NullPointerException("CppInheritanceAccess class is not initialized.");
	}
	_CppFunctionAccess<EncodingT>* cppFunctionAccess = _CppFunctionAccess<EncodingT>::getInstance();
	if (!cppFunctionAccess) {
		m_logger->errorStream() << "CppFunctionAccess class is not initialized.";
		throw NullPointerException("CppFunctionAccess class is not initialized.");
	}
	_CppClassAccess<EncodingT>* internClasseAccess = _CppClassAccess<EncodingT>::getInstance();
	if (!internClasseAccess) {
		m_logger->errorStream() << "CppClassAccess class is not initialized.";
		throw NullPointerException("CppClassAccess class is not initialized.");
	}
	_CppAttributeAccess<EncodingT>* cppAttributeAccess = _CppAttributeAccess<EncodingT>::getInstance();
	if (!cppAttributeAccess) {
		m_logger->errorStream() << "CppAttributeAccess class is not initialized.";
		throw NullPointerException("CppAttributeAccess class is not initialized.");
	}
	_CppEnumAccess<EncodingT>* cppEnumAccess = _CppEnumAccess<EncodingT>::getInstance();
	if (!cppEnumAccess) {
		m_logger->errorStream() << "CppEnumAccess class is not initialized.";
		throw NullPointerException("CppEnumAccess class is not initialized.");
	}
	try {
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
		if ( !o->isNullEncapsulationClass() && typename _CppClass<EncodingT>::CppClassIDEquality(-1)(o->getEncapsulationClass()) ) {
			m_logger->errorStream() << "idEncapsulationClass : Identifier is null.";
			throw InvalidQueryException("idEncapsulationClass : Identifier is null.");
		}
		else if ( !o->isNullEncapsulationClass() ) {
			values.addInt64( o->getEncapsulationClass()->getIdentifier() );
			fields.push_back( C("idEncapsulationClass") );
		}
		else {
			values.addNull();
			fields.push_back( C("idEncapsulationClass") );
		}
		int id = connection->selectMaxID(C("identifier"), C("cppClass"))+1;
		values.addInt( id );
		fields.push_back( C("identifier") );
		values.addText( o->getName() );
		fields.push_back( C("name") );
		values.addText( o->getFullName() );
		fields.push_back( C("fullName") );
		values.addText( o->getAccessSpecifier() );
		fields.push_back( C("accessSpecifier") );
		values.addInt64( o->getIsStruct() );
		fields.push_back( C("isStruct") );
		values.addInt64( o->getIsInterface() );
		fields.push_back( C("isInterface") );
		values.addInt64( o->getIsAbstract() );
		fields.push_back( C("isAbstract") );
		values.addInt64( o->getIsTemplate() );
		fields.push_back( C("isTemplate") );
		values.addInt64( o->getLinesCount() );
		fields.push_back( C("linesCount") );
		if ( !o->isNullCppFile() && typename _CppFile<EncodingT>::CppFileIDEquality(-1)(o->getCppFile()) ) {
			m_logger->errorStream() << "idFile : Identifier is null.";
			throw InvalidQueryException("idFile : Identifier is null.");
		}
		else if ( !o->isNullCppFile() ) {
			values.addInt64( o->getCppFile()->getIdentifier() );
			fields.push_back( C("idFile") );
		}
		else {
			m_logger->errorStream() << "idFile : null reference is forbidden.";
			throw InvalidQueryException("idFile : null reference is forbidden.");
		}
		values.addInt64( o->getLineNumber() );
		fields.push_back( C("lineNumber") );
		values.addInt64( o->getStartBlock() );
		fields.push_back( C("startBlock") );
		values.addInt64( o->getLengthBlock() );
		fields.push_back( C("lengthBlock") );
		statement.swap( connection->insert(C("cppClass"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		o->setIdentifier(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, C("cppClass"), o);
		typename _CppClass<EncodingT>::CppInheritanceIterator cppInheritance;
		for ( cppInheritance=o->getCppInheritancesBeginning(); cppInheritance!=o->getCppInheritancesEnd(); ++cppInheritance ) {
			(*cppInheritance)->setDerived(o);
			cppInheritanceAccess->insertCppInheritance(*cppInheritance);
		}
		typename _CppClass<EncodingT>::CppFunctionIterator cppFunction;
		for ( cppFunction=o->getCppFunctionsBeginning(); cppFunction!=o->getCppFunctionsEnd(); ++cppFunction ) {
			(*cppFunction)->setCppClass(o);
			cppFunctionAccess->insertCppFunction(*cppFunction);
		}
		typename _CppClass<EncodingT>::InternClasseIterator internClasse;
		for ( internClasse=o->getInternClassesBeginning(); internClasse!=o->getInternClassesEnd(); ++internClasse ) {
			(*internClasse)->setEncapsulationClass(o);
			internClasseAccess->insertCppClass(*internClasse);
		}
		typename _CppClass<EncodingT>::CppAttributeIterator cppAttribute;
		for ( cppAttribute=o->getCppAttributesBeginning(); cppAttribute!=o->getCppAttributesEnd(); ++cppAttribute ) {
			(*cppAttribute)->setCppClass(o);
			cppAttributeAccess->insertCppAttribute(*cppAttribute);
		}
		typename _CppClass<EncodingT>::CppEnumIterator cppEnum;
		for ( cppEnum=o->getCppEnumsBeginning(); cppEnum!=o->getCppEnumsEnd(); ++cppEnum ) {
			(*cppEnum)->setCppClass(o);
			cppEnumAccess->insertCppEnum(*cppEnum);
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
_CppClassAccess<EncodingT>::deleteCppClass(boost::shared_ptr< _CppClass<EncodingT> > o)  
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
	_CppInheritanceAccess<EncodingT>* cppInheritanceAccess = _CppInheritanceAccess<EncodingT>::getInstance();
	if (!cppInheritanceAccess) {
		m_logger->errorStream() << "CppInheritanceAccess class is not initialized.";
		throw NullPointerException("CppInheritanceAccess class is not initialized.");
	}
	_CppFunctionAccess<EncodingT>* cppFunctionAccess = _CppFunctionAccess<EncodingT>::getInstance();
	if (!cppFunctionAccess) {
		m_logger->errorStream() << "CppFunctionAccess class is not initialized.";
		throw NullPointerException("CppFunctionAccess class is not initialized.");
	}
	_CppClassAccess<EncodingT>* internClasseAccess = _CppClassAccess<EncodingT>::getInstance();
	if (!internClasseAccess) {
		m_logger->errorStream() << "CppClassAccess class is not initialized.";
		throw NullPointerException("CppClassAccess class is not initialized.");
	}
	_CppAttributeAccess<EncodingT>* cppAttributeAccess = _CppAttributeAccess<EncodingT>::getInstance();
	if (!cppAttributeAccess) {
		m_logger->errorStream() << "CppAttributeAccess class is not initialized.";
		throw NullPointerException("CppAttributeAccess class is not initialized.");
	}
	_CppEnumAccess<EncodingT>* cppEnumAccess = _CppEnumAccess<EncodingT>::getInstance();
	if (!cppEnumAccess) {
		m_logger->errorStream() << "CppEnumAccess class is not initialized.";
		throw NullPointerException("CppEnumAccess class is not initialized.");
	}
	typename _CppClass<EncodingT>::CppClassIDEquality CppClassIdEquality(*o);
	typename std::list< boost::shared_ptr< _CppClass<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), CppClassIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before deletion.";
		throw UnSelectedObjectException("You must select object before deletion.");
	}
	try {
		typename _CppClass<EncodingT>::CppInheritanceIterator cppInheritance;
		fillAllCppInheritances(o);
		for ( cppInheritance=o->getCppInheritancesBeginning(); cppInheritance!=o->getCppInheritancesEnd(); ++cppInheritance ) {
			cppInheritanceAccess->deleteCppInheritance(*cppInheritance);
		}
		typename _CppClass<EncodingT>::CppFunctionIterator cppFunction;
		fillAllCppFunctions(o);
		for ( cppFunction=o->getCppFunctionsBeginning(); cppFunction!=o->getCppFunctionsEnd(); ++cppFunction ) {
			cppFunctionAccess->fillCppClass(*cppFunction);
			(*cppFunction)->eraseCppClass();
			cppFunctionAccess->updateCppFunction(*cppFunction);
		}
		typename _CppClass<EncodingT>::InternClasseIterator internClasse;
		fillAllInternClasses(o);
		for ( internClasse=o->getInternClassesBeginning(); internClasse!=o->getInternClassesEnd(); ++internClasse ) {
			internClasseAccess->fillEncapsulationClass(*internClasse);
			(*internClasse)->eraseEncapsulationClass();
			internClasseAccess->updateCppClass(*internClasse);
		}
		typename _CppClass<EncodingT>::CppAttributeIterator cppAttribute;
		fillAllCppAttributes(o);
		for ( cppAttribute=o->getCppAttributesBeginning(); cppAttribute!=o->getCppAttributesEnd(); ++cppAttribute ) {
			cppAttributeAccess->deleteCppAttribute(*cppAttribute);
		}
		typename _CppClass<EncodingT>::CppEnumIterator cppEnum;
		fillAllCppEnums(o);
		for ( cppEnum=o->getCppEnumsBeginning(); cppEnum!=o->getCppEnumsEnd(); ++cppEnum ) {
			cppEnumAccess->fillCppClass(*cppEnum);
			(*cppEnum)->eraseCppClass();
			cppEnumAccess->updateCppEnum(*cppEnum);
		}
		statement.swap( connection->deleteFrom(C("cppClass"), C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, C("cppClass"), o);
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
typename _CppClassAccess<EncodingT>::connection_t
_CppClassAccess<EncodingT>::addInsertSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_insertSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppClassAccess<EncodingT>::connection_t
_CppClassAccess<EncodingT>::addUpdateSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_updateSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppClassAccess<EncodingT>::connection_t
_CppClassAccess<EncodingT>::addDeleteSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_deleteSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppClassAccess<EncodingT>::connection_t
_CppClassAccess<EncodingT>::addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber)  
{
	return m_transactionSignal.connect(subscriber);
}

template<class EncodingT>
void
_CppClassAccess<EncodingT>::removeInsertSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppClassAccess<EncodingT>::removeUpdateSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppClassAccess<EncodingT>::removeDeleteSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppClassAccess<EncodingT>::removeTransactionSignal(connection_t connection)  
{
	connection.disconnect();
}


NAMESPACE_END

#undef C
#undef A

