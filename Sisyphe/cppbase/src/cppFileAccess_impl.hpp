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
_CppFileAccess<EncodingT>* _CppFileAccess<EncodingT>::m_instance = NULL;

template<class EncodingT>
_CppFileAccess<EncodingT>* 
_CppFileAccess<EncodingT>::getInstance()  
{
	if (m_instance == NULL) {
		m_instance = new _CppFileAccess<EncodingT>();
	}
	return m_instance;
}

template<class EncodingT>
_CppFileAccess<EncodingT>::_CppFileAccess()
: m_transactionOwner(false) 
{
	m_logger = &Category::getInstance(LOGNAME);
	m_logger->debugStream() << "constructor CppFileAccess " << m_transactionOwner;
}

template<class EncodingT>
_CppFileAccess<EncodingT>::~_CppFileAccess()
{
	cancelSelection();
	m_logger = NULL;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppFile<EncodingT> > >
_CppFileAccess<EncodingT>::getManyCppFiles(typename EncodingT::string_t const&  filter) const 
{
	boost::shared_ptr< _CppFile<EncodingT> > value;
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _CppFile<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("path"));
	columns.push_back(UCS("name"));
	columns.push_back(UCS("linesCount"));
	columns.push_back(UCS("hash"));
	columns.push_back(UCS("analyzed"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,UCS("cppFile")), filter) );
	while( statement.executeStep() ) {
		long long identifier;
		typename EncodingT::string_t path;
		typename EncodingT::string_t name;
		long long linesCount;
		long long hash;
		long long analyzed;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, path ) &&
			statement.getText( 2, name ) &&
			statement.getInt64( 3, linesCount ) &&
			statement.getInt64( 4, hash ) &&
			statement.getInt64( 5, analyzed )) {
			value.reset(new _CppFile<EncodingT>(
				identifier,
				path,
				name,
				linesCount,
				hash,
				analyzed));
			tab.push_back(value);
		}
	}
	return tab;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppFile<EncodingT> > >
_CppFileAccess<EncodingT>::getAllCppFiles() const 
{
	return getManyCppFiles(EncodingT::EMPTY);
}

template<class EncodingT>
boost::shared_ptr< _CppFile<EncodingT> >
_CppFileAccess<EncodingT>::getOneCppFile(long long identifier) const 
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _CppFile<EncodingT> > > result = getManyCppFiles(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppFile<EncodingT> > >
_CppFileAccess<EncodingT>::selectManyCppFiles(typename EncodingT::string_t const&  filter, bool nowait, bool addition)  
{
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _CppFile<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("path"));
	columns.push_back(UCS("name"));
	columns.push_back(UCS("linesCount"));
	columns.push_back(UCS("hash"));
	columns.push_back(UCS("analyzed"));
	if (!addition || !connection->isTransactionInProgress()) {
		cancelSelection();
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
	}
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,UCS("cppFile")), filter, nowait) );
	while( statement.executeStep() ) {
		long long identifier;
		typename EncodingT::string_t path;
		typename EncodingT::string_t name;
		long long linesCount;
		long long hash;
		long long analyzed;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, path ) &&
			statement.getText( 2, name ) &&
			statement.getInt64( 3, linesCount ) &&
			statement.getInt64( 4, hash ) &&
			statement.getInt64( 5, analyzed )) {
			tab.push_back(boost::shared_ptr< _CppFile<EncodingT> >(new _CppFile<EncodingT>(
				identifier,
				path,
				name,
				linesCount,
				hash,
				analyzed)));
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
boost::shared_ptr< _CppFile<EncodingT> >
_CppFileAccess<EncodingT>::selectOneCppFile(long long identifier, bool nowait, bool addition)  
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _CppFile<EncodingT> > > result = selectManyCppFiles(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait, addition);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
bool
_CppFileAccess<EncodingT>::isSelectedCppFile(boost::shared_ptr< _CppFile<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(*o);
	return (!m_backup.empty() && (std::find_if(m_backup.begin(), m_backup.end(), cppFileIdEquality)!=m_backup.end()));
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::cancelSelection()  
{
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	_CppFunctionAccess<EncodingT>* cppDeclarationFunctionAccess = _CppFunctionAccess<EncodingT>::getInstance();
	if (!cppDeclarationFunctionAccess) {
		m_logger->errorStream() << "CppFunctionAccess class is not initialized.";
		throw NullPointerException("CppFunctionAccess class is not initialized.");
	}
	_CppFunctionAccess<EncodingT>* cppDefinitionFunctionAccess = _CppFunctionAccess<EncodingT>::getInstance();
	if (!cppDefinitionFunctionAccess) {
		m_logger->errorStream() << "CppFunctionAccess class is not initialized.";
		throw NullPointerException("CppFunctionAccess class is not initialized.");
	}
	_CppClassAccess<EncodingT>* cppClassAccess = _CppClassAccess<EncodingT>::getInstance();
	if (!cppClassAccess) {
		m_logger->errorStream() << "CppClassAccess class is not initialized.";
		throw NullPointerException("CppClassAccess class is not initialized.");
	}
	_CppIncludeAccess<EncodingT>* cppIncludeAccess = _CppIncludeAccess<EncodingT>::getInstance();
	if (!cppIncludeAccess) {
		m_logger->errorStream() << "CppIncludeAccess class is not initialized.";
		throw NullPointerException("CppIncludeAccess class is not initialized.");
	}
	_CppVariableAccess<EncodingT>* cppVariableAccess = _CppVariableAccess<EncodingT>::getInstance();
	if (!cppVariableAccess) {
		m_logger->errorStream() << "CppVariableAccess class is not initialized.";
		throw NullPointerException("CppVariableAccess class is not initialized.");
	}
	_CppEnumAccess<EncodingT>* cppEnumAccess = _CppEnumAccess<EncodingT>::getInstance();
	if (!cppEnumAccess) {
		m_logger->errorStream() << "CppEnumAccess class is not initialized.";
		throw NullPointerException("CppEnumAccess class is not initialized.");
	}
	_CMacroAccess<EncodingT>* cMacroAccess = _CMacroAccess<EncodingT>::getInstance();
	if (!cMacroAccess) {
		m_logger->errorStream() << "CMacroAccess class is not initialized.";
		throw NullPointerException("CMacroAccess class is not initialized.");
	}
	_CppNoticeAccess<EncodingT>* cppNoticeAccess = _CppNoticeAccess<EncodingT>::getInstance();
	if (!cppNoticeAccess) {
		m_logger->errorStream() << "CppNoticeAccess class is not initialized.";
		throw NullPointerException("CppNoticeAccess class is not initialized.");
	}
	if (!m_backup.empty()) {
		if (connection->isTransactionInProgress() && m_transactionOwner) {
			connection->rollback();
			m_transactionOwner = false;
			m_transactionSignal(OPERATION_ACCESS_ROLLBACK);
		}
		m_backup.clear();
		cppDeclarationFunctionAccess->cancelSelection();
		cppDefinitionFunctionAccess->cancelSelection();
		cppClassAccess->cancelSelection();
		cppIncludeAccess->cancelSelection();
		cppVariableAccess->cancelSelection();
		cppEnumAccess->cancelSelection();
		cMacroAccess->cancelSelection();
		cppNoticeAccess->cancelSelection();
	}
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillTextFile(boost::shared_ptr< _CppFile<EncodingT> > o)  
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
	_TextFileAccess<EncodingT>* textFileAccess = _TextFileAccess<EncodingT>::getInstance();
	if (!textFileAccess) {
		m_logger->errorStream() << "TextFileAccess class is not initialized.";
		throw NullPointerException("TextFileAccess class is not initialized.");
	}
	long long id;
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,UCS("idText")), std::vector<typename EncodingT::string_t>(1,UCS("cppFile")), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
	if( statement.executeStep() && statement.getInt64( 0, id ) && id != 0 ) {
		typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(o->getIdentifier());
		boost::shared_ptr< _TextFile<EncodingT> > val = textFileAccess->getOneTextFile(id);
		typename std::list< boost::shared_ptr<_CppFile<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFileIdEquality);
		if (save != m_backup.end()) {
			(*save)->setTextFile(val);
		}
		o->setTextFile(val);
	}
	else {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillCppFileType(boost::shared_ptr< _CppFile<EncodingT> > o)  
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
	_CppFileTypeAccess<EncodingT>* cppFileTypeAccess = _CppFileTypeAccess<EncodingT>::getInstance();
	if (!cppFileTypeAccess) {
		m_logger->errorStream() << "CppFileTypeAccess class is not initialized.";
		throw NullPointerException("CppFileTypeAccess class is not initialized.");
	}
	long long id;
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,UCS("idType")), std::vector<typename EncodingT::string_t>(1,UCS("cppFile")), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
	if( statement.executeStep() && statement.getInt64( 0, id ) && id != 0 ) {
		typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(o->getIdentifier());
		boost::shared_ptr< _CppFileType<EncodingT> > val = cppFileTypeAccess->getOneCppFileType(id);
		typename std::list< boost::shared_ptr<_CppFile<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFileIdEquality);
		if (save != m_backup.end()) {
			(*save)->setCppFileType(val);
		}
		o->setCppFileType(val);
	}
	else {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillAllCppDeclarationFunctions(boost::shared_ptr< _CppFile<EncodingT> > o, bool nowait)  
{
	fillManyCppDeclarationFunctions(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillOneCppDeclarationFunction(boost::shared_ptr< _CppFile<EncodingT> > o, long long identifier, bool nowait)  
{
	fillManyCppDeclarationFunctions(o, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillManyCppDeclarationFunctions(boost::shared_ptr< _CppFile<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_CppFunctionAccess<EncodingT>* cppDeclarationFunctionAccess = _CppFunctionAccess<EncodingT>::getInstance();
	if (!cppDeclarationFunctionAccess) {
		m_logger->errorStream() << "CppFunctionAccess class is not initialized.";
		throw NullPointerException("CppFunctionAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _CppFunction<EncodingT> > > tab;
	typename EncodingT::string_t cppFunctionFilter = UCS("idDecFile = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		cppFunctionFilter += UCS(" AND ") + filter;
	}
	typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(o->getIdentifier());
	typename std::list< boost::shared_ptr< _CppFile<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFileIdEquality);
	if (save != m_backup.end())
	{
		tab = cppDeclarationFunctionAccess->selectManyCppFunctions(cppFunctionFilter, nowait, true);
		(*save)->clearCppDeclarationFunctions();
		(*save)->insertCppDeclarationFunction((*save)->getCppDeclarationFunctionsEnd(), tab.begin(), tab.end());
	}
	else
	{
		tab = cppDeclarationFunctionAccess->getManyCppFunctions(cppFunctionFilter);
	}
	o->clearCppDeclarationFunctions();
	o->insertCppDeclarationFunction(o->getCppDeclarationFunctionsEnd(), tab.begin(), tab.end());
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillAllCppDefinitionFunctions(boost::shared_ptr< _CppFile<EncodingT> > o, bool nowait)  
{
	fillManyCppDefinitionFunctions(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillOneCppDefinitionFunction(boost::shared_ptr< _CppFile<EncodingT> > o, long long identifier, bool nowait)  
{
	fillManyCppDefinitionFunctions(o, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillManyCppDefinitionFunctions(boost::shared_ptr< _CppFile<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_CppFunctionAccess<EncodingT>* cppDefinitionFunctionAccess = _CppFunctionAccess<EncodingT>::getInstance();
	if (!cppDefinitionFunctionAccess) {
		m_logger->errorStream() << "CppFunctionAccess class is not initialized.";
		throw NullPointerException("CppFunctionAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _CppFunction<EncodingT> > > tab;
	typename EncodingT::string_t cppFunctionFilter = UCS("idDefFile = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		cppFunctionFilter += UCS(" AND ") + filter;
	}
	typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(o->getIdentifier());
	typename std::list< boost::shared_ptr< _CppFile<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFileIdEquality);
	if (save != m_backup.end())
	{
		tab = cppDefinitionFunctionAccess->selectManyCppFunctions(cppFunctionFilter, nowait, true);
		(*save)->clearCppDefinitionFunctions();
		(*save)->insertCppDefinitionFunction((*save)->getCppDefinitionFunctionsEnd(), tab.begin(), tab.end());
	}
	else
	{
		tab = cppDefinitionFunctionAccess->getManyCppFunctions(cppFunctionFilter);
	}
	o->clearCppDefinitionFunctions();
	o->insertCppDefinitionFunction(o->getCppDefinitionFunctionsEnd(), tab.begin(), tab.end());
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillAllCppClasss(boost::shared_ptr< _CppFile<EncodingT> > o, bool nowait)  
{
	fillManyCppClasss(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillOneCppClass(boost::shared_ptr< _CppFile<EncodingT> > o, long long identifier, bool nowait)  
{
	fillManyCppClasss(o, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillManyCppClasss(boost::shared_ptr< _CppFile<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_CppClassAccess<EncodingT>* cppClassAccess = _CppClassAccess<EncodingT>::getInstance();
	if (!cppClassAccess) {
		m_logger->errorStream() << "CppClassAccess class is not initialized.";
		throw NullPointerException("CppClassAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _CppClass<EncodingT> > > tab;
	typename EncodingT::string_t cppClassFilter = UCS("idFile = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		cppClassFilter += UCS(" AND ") + filter;
	}
	typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(o->getIdentifier());
	typename std::list< boost::shared_ptr< _CppFile<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFileIdEquality);
	if (save != m_backup.end())
	{
		tab = cppClassAccess->selectManyCppClasss(cppClassFilter, nowait, true);
		(*save)->clearCppClasss();
		(*save)->insertCppClass((*save)->getCppClasssEnd(), tab.begin(), tab.end());
	}
	else
	{
		tab = cppClassAccess->getManyCppClasss(cppClassFilter);
	}
	o->clearCppClasss();
	o->insertCppClass(o->getCppClasssEnd(), tab.begin(), tab.end());
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillAllCppIncludes(boost::shared_ptr< _CppFile<EncodingT> > o, bool nowait)  
{
	fillManyCppIncludes(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillOneCppInclude(boost::shared_ptr< _CppFile<EncodingT> > o, long long identifier, bool nowait)  
{
	fillManyCppIncludes(o, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillManyCppIncludes(boost::shared_ptr< _CppFile<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_CppIncludeAccess<EncodingT>* cppIncludeAccess = _CppIncludeAccess<EncodingT>::getInstance();
	if (!cppIncludeAccess) {
		m_logger->errorStream() << "CppIncludeAccess class is not initialized.";
		throw NullPointerException("CppIncludeAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _CppInclude<EncodingT> > > tab;
	typename EncodingT::string_t cppIncludeFilter = UCS("idFile = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		cppIncludeFilter += UCS(" AND ") + filter;
	}
	typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(o->getIdentifier());
	typename std::list< boost::shared_ptr< _CppFile<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFileIdEquality);
	if (save != m_backup.end())
	{
		tab = cppIncludeAccess->selectManyCppIncludes(cppIncludeFilter, nowait, true);
		(*save)->clearCppIncludes();
		(*save)->insertCppInclude((*save)->getCppIncludesEnd(), tab.begin(), tab.end());
	}
	else
	{
		tab = cppIncludeAccess->getManyCppIncludes(cppIncludeFilter);
	}
	o->clearCppIncludes();
	o->insertCppInclude(o->getCppIncludesEnd(), tab.begin(), tab.end());
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillAllCppVariables(boost::shared_ptr< _CppFile<EncodingT> > o, bool nowait)  
{
	fillManyCppVariables(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillOneCppVariable(boost::shared_ptr< _CppFile<EncodingT> > o, long long identifier, bool nowait)  
{
	fillManyCppVariables(o, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillManyCppVariables(boost::shared_ptr< _CppFile<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_CppVariableAccess<EncodingT>* cppVariableAccess = _CppVariableAccess<EncodingT>::getInstance();
	if (!cppVariableAccess) {
		m_logger->errorStream() << "CppVariableAccess class is not initialized.";
		throw NullPointerException("CppVariableAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _CppVariable<EncodingT> > > tab;
	typename EncodingT::string_t cppVariableFilter = UCS("idFile = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		cppVariableFilter += UCS(" AND ") + filter;
	}
	typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(o->getIdentifier());
	typename std::list< boost::shared_ptr< _CppFile<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFileIdEquality);
	if (save != m_backup.end())
	{
		tab = cppVariableAccess->selectManyCppVariables(cppVariableFilter, nowait, true);
		(*save)->clearCppVariables();
		(*save)->insertCppVariable((*save)->getCppVariablesEnd(), tab.begin(), tab.end());
	}
	else
	{
		tab = cppVariableAccess->getManyCppVariables(cppVariableFilter);
	}
	o->clearCppVariables();
	o->insertCppVariable(o->getCppVariablesEnd(), tab.begin(), tab.end());
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillAllCppEnums(boost::shared_ptr< _CppFile<EncodingT> > o, bool nowait)  
{
	fillManyCppEnums(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillOneCppEnum(boost::shared_ptr< _CppFile<EncodingT> > o, long long identifier, bool nowait)  
{
	fillManyCppEnums(o, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillManyCppEnums(boost::shared_ptr< _CppFile<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
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
	typename EncodingT::string_t cppEnumFilter = UCS("idFile = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		cppEnumFilter += UCS(" AND ") + filter;
	}
	typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(o->getIdentifier());
	typename std::list< boost::shared_ptr< _CppFile<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFileIdEquality);
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
void
_CppFileAccess<EncodingT>::fillAllCMacros(boost::shared_ptr< _CppFile<EncodingT> > o, bool nowait)  
{
	fillManyCMacros(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillOneCMacro(boost::shared_ptr< _CppFile<EncodingT> > o, long long identifier, bool nowait)  
{
	fillManyCMacros(o, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillManyCMacros(boost::shared_ptr< _CppFile<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_CMacroAccess<EncodingT>* cMacroAccess = _CMacroAccess<EncodingT>::getInstance();
	if (!cMacroAccess) {
		m_logger->errorStream() << "CMacroAccess class is not initialized.";
		throw NullPointerException("CMacroAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _CMacro<EncodingT> > > tab;
	typename EncodingT::string_t cMacroFilter = UCS("idFile = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		cMacroFilter += UCS(" AND ") + filter;
	}
	typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(o->getIdentifier());
	typename std::list< boost::shared_ptr< _CppFile<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFileIdEquality);
	if (save != m_backup.end())
	{
		tab = cMacroAccess->selectManyCMacros(cMacroFilter, nowait, true);
		(*save)->clearCMacros();
		(*save)->insertCMacro((*save)->getCMacrosEnd(), tab.begin(), tab.end());
	}
	else
	{
		tab = cMacroAccess->getManyCMacros(cMacroFilter);
	}
	o->clearCMacros();
	o->insertCMacro(o->getCMacrosEnd(), tab.begin(), tab.end());
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillAllCppNotices(boost::shared_ptr< _CppFile<EncodingT> > o, bool nowait)  
{
	fillManyCppNotices(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillOneCppNotice(boost::shared_ptr< _CppFile<EncodingT> > o, long long identifier, bool nowait)  
{
	fillManyCppNotices(o, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillManyCppNotices(boost::shared_ptr< _CppFile<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_CppNoticeAccess<EncodingT>* cppNoticeAccess = _CppNoticeAccess<EncodingT>::getInstance();
	if (!cppNoticeAccess) {
		m_logger->errorStream() << "CppNoticeAccess class is not initialized.";
		throw NullPointerException("CppNoticeAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _CppNotice<EncodingT> > > tab;
	typename EncodingT::string_t cppNoticeFilter = UCS("idFile = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		cppNoticeFilter += UCS(" AND ") + filter;
	}
	typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(o->getIdentifier());
	typename std::list< boost::shared_ptr< _CppFile<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFileIdEquality);
	if (save != m_backup.end())
	{
		tab = cppNoticeAccess->selectManyCppNotices(cppNoticeFilter, nowait, true);
		(*save)->clearCppNotices();
		(*save)->insertCppNotice((*save)->getCppNoticesEnd(), tab.begin(), tab.end());
	}
	else
	{
		tab = cppNoticeAccess->getManyCppNotices(cppNoticeFilter);
	}
	o->clearCppNotices();
	o->insertCppNotice(o->getCppNoticesEnd(), tab.begin(), tab.end());
}

template<class EncodingT>
bool
_CppFileAccess<EncodingT>::isModifiedCppFile(boost::shared_ptr< _CppFile<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_CppFunctionAccess<EncodingT>* cppDeclarationFunctionAccess = _CppFunctionAccess<EncodingT>::getInstance();
	if (!cppDeclarationFunctionAccess) {
		m_logger->errorStream() << "CppFunctionAccess class is not initialized.";
		throw NullPointerException("CppFunctionAccess class is not initialized.");
	}
	_CppFunctionAccess<EncodingT>* cppDefinitionFunctionAccess = _CppFunctionAccess<EncodingT>::getInstance();
	if (!cppDefinitionFunctionAccess) {
		m_logger->errorStream() << "CppFunctionAccess class is not initialized.";
		throw NullPointerException("CppFunctionAccess class is not initialized.");
	}
	_CppClassAccess<EncodingT>* cppClassAccess = _CppClassAccess<EncodingT>::getInstance();
	if (!cppClassAccess) {
		m_logger->errorStream() << "CppClassAccess class is not initialized.";
		throw NullPointerException("CppClassAccess class is not initialized.");
	}
	_CppIncludeAccess<EncodingT>* cppIncludeAccess = _CppIncludeAccess<EncodingT>::getInstance();
	if (!cppIncludeAccess) {
		m_logger->errorStream() << "CppIncludeAccess class is not initialized.";
		throw NullPointerException("CppIncludeAccess class is not initialized.");
	}
	_CppVariableAccess<EncodingT>* cppVariableAccess = _CppVariableAccess<EncodingT>::getInstance();
	if (!cppVariableAccess) {
		m_logger->errorStream() << "CppVariableAccess class is not initialized.";
		throw NullPointerException("CppVariableAccess class is not initialized.");
	}
	_CppEnumAccess<EncodingT>* cppEnumAccess = _CppEnumAccess<EncodingT>::getInstance();
	if (!cppEnumAccess) {
		m_logger->errorStream() << "CppEnumAccess class is not initialized.";
		throw NullPointerException("CppEnumAccess class is not initialized.");
	}
	_CMacroAccess<EncodingT>* cMacroAccess = _CMacroAccess<EncodingT>::getInstance();
	if (!cMacroAccess) {
		m_logger->errorStream() << "CMacroAccess class is not initialized.";
		throw NullPointerException("CMacroAccess class is not initialized.");
	}
	_CppNoticeAccess<EncodingT>* cppNoticeAccess = _CppNoticeAccess<EncodingT>::getInstance();
	if (!cppNoticeAccess) {
		m_logger->errorStream() << "CppNoticeAccess class is not initialized.";
		throw NullPointerException("CppNoticeAccess class is not initialized.");
	}
	typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(*o);
	typename std::list< boost::shared_ptr< _CppFile<EncodingT> > >::const_iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFileIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getPath() != o->getPath());
	bUpdate = bUpdate || ((*save)->getName() != o->getName());
	bUpdate = bUpdate || ((*save)->getLinesCount() != o->getLinesCount());
	bUpdate = bUpdate || ((*save)->getHash() != o->getHash());
	bUpdate = bUpdate || ((*save)->getAnalyzed() != o->getAnalyzed());
	bUpdate = bUpdate || (!(*save)->isNullTextFile() && !o->isNullTextFile() && !typename _TextFile<EncodingT>::TextFileIDEquality(*(*save)->getTextFile())(o->getTextFile()))
		|| ((*save)->isNullTextFile() && !o->isNullTextFile()) 
		|| (!(*save)->isNullTextFile() && o->isNullTextFile());
	bUpdate = bUpdate || (!(*save)->isNullCppFileType() && !o->isNullCppFileType() && !typename _CppFileType<EncodingT>::CppFileTypeIDEquality(*(*save)->getCppFileType())(o->getCppFileType()))
		|| ((*save)->isNullCppFileType() && !o->isNullCppFileType()) 
		|| (!(*save)->isNullCppFileType() && o->isNullCppFileType());
	typename _CppFile<EncodingT>::CppDeclarationFunctionIterator cppDeclarationFunction;
	for ( cppDeclarationFunction=o->getCppDeclarationFunctionsBeginning(); cppDeclarationFunction!=o->getCppDeclarationFunctionsEnd(); ++cppDeclarationFunction ) {
		if (!(*cppDeclarationFunction)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppFunction<EncodingT>::CppFunctionIDEquality cppDeclarationFunctionIdEquality(*(*cppDeclarationFunction));
		bUpdate = bUpdate || (std::find_if((*save)->getCppDeclarationFunctionsBeginning(), (*save)->getCppDeclarationFunctionsEnd(), cppDeclarationFunctionIdEquality) == (*save)->getCppDeclarationFunctionsEnd())
			|| (cppDeclarationFunctionAccess->isModifiedCppFunction(*cppDeclarationFunction));
	}
	for ( cppDeclarationFunction=(*save)->getCppDeclarationFunctionsBeginning(); cppDeclarationFunction<(*save)->getCppDeclarationFunctionsEnd(); ++cppDeclarationFunction ) {
		if (!(*cppDeclarationFunction)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppFunction<EncodingT>::CppFunctionIDEquality cppDeclarationFunctionIdEquality(*(*cppDeclarationFunction));
		bUpdate = bUpdate || (std::find_if(o->getCppDeclarationFunctionsBeginning(), o->getCppDeclarationFunctionsEnd(), cppDeclarationFunctionIdEquality) == o->getCppDeclarationFunctionsEnd());
	}
	typename _CppFile<EncodingT>::CppDefinitionFunctionIterator cppDefinitionFunction;
	for ( cppDefinitionFunction=o->getCppDefinitionFunctionsBeginning(); cppDefinitionFunction!=o->getCppDefinitionFunctionsEnd(); ++cppDefinitionFunction ) {
		if (!(*cppDefinitionFunction)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppFunction<EncodingT>::CppFunctionIDEquality cppDefinitionFunctionIdEquality(*(*cppDefinitionFunction));
		bUpdate = bUpdate || (std::find_if((*save)->getCppDefinitionFunctionsBeginning(), (*save)->getCppDefinitionFunctionsEnd(), cppDefinitionFunctionIdEquality) == (*save)->getCppDefinitionFunctionsEnd())
			|| (cppDefinitionFunctionAccess->isModifiedCppFunction(*cppDefinitionFunction));
	}
	for ( cppDefinitionFunction=(*save)->getCppDefinitionFunctionsBeginning(); cppDefinitionFunction<(*save)->getCppDefinitionFunctionsEnd(); ++cppDefinitionFunction ) {
		if (!(*cppDefinitionFunction)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppFunction<EncodingT>::CppFunctionIDEquality cppDefinitionFunctionIdEquality(*(*cppDefinitionFunction));
		bUpdate = bUpdate || (std::find_if(o->getCppDefinitionFunctionsBeginning(), o->getCppDefinitionFunctionsEnd(), cppDefinitionFunctionIdEquality) == o->getCppDefinitionFunctionsEnd());
	}
	typename _CppFile<EncodingT>::CppClassIterator cppClass;
	for ( cppClass=o->getCppClasssBeginning(); cppClass!=o->getCppClasssEnd(); ++cppClass ) {
		if (!(*cppClass)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppClass<EncodingT>::CppClassIDEquality cppClassIdEquality(*(*cppClass));
		bUpdate = bUpdate || (std::find_if((*save)->getCppClasssBeginning(), (*save)->getCppClasssEnd(), cppClassIdEquality) == (*save)->getCppClasssEnd())
			|| (cppClassAccess->isModifiedCppClass(*cppClass));
	}
	for ( cppClass=(*save)->getCppClasssBeginning(); cppClass<(*save)->getCppClasssEnd(); ++cppClass ) {
		if (!(*cppClass)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppClass<EncodingT>::CppClassIDEquality cppClassIdEquality(*(*cppClass));
		bUpdate = bUpdate || (std::find_if(o->getCppClasssBeginning(), o->getCppClasssEnd(), cppClassIdEquality) == o->getCppClasssEnd());
	}
	typename _CppFile<EncodingT>::CppIncludeIterator cppInclude;
	for ( cppInclude=o->getCppIncludesBeginning(); cppInclude!=o->getCppIncludesEnd(); ++cppInclude ) {
		if (!(*cppInclude)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppInclude<EncodingT>::CppIncludeIDEquality cppIncludeIdEquality(*(*cppInclude));
		bUpdate = bUpdate || (std::find_if((*save)->getCppIncludesBeginning(), (*save)->getCppIncludesEnd(), cppIncludeIdEquality) == (*save)->getCppIncludesEnd())
			|| (cppIncludeAccess->isModifiedCppInclude(*cppInclude));
	}
	for ( cppInclude=(*save)->getCppIncludesBeginning(); cppInclude<(*save)->getCppIncludesEnd(); ++cppInclude ) {
		if (!(*cppInclude)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppInclude<EncodingT>::CppIncludeIDEquality cppIncludeIdEquality(*(*cppInclude));
		bUpdate = bUpdate || (std::find_if(o->getCppIncludesBeginning(), o->getCppIncludesEnd(), cppIncludeIdEquality) == o->getCppIncludesEnd());
	}
	typename _CppFile<EncodingT>::CppVariableIterator cppVariable;
	for ( cppVariable=o->getCppVariablesBeginning(); cppVariable!=o->getCppVariablesEnd(); ++cppVariable ) {
		if (!(*cppVariable)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppVariable<EncodingT>::CppVariableIDEquality cppVariableIdEquality(*(*cppVariable));
		bUpdate = bUpdate || (std::find_if((*save)->getCppVariablesBeginning(), (*save)->getCppVariablesEnd(), cppVariableIdEquality) == (*save)->getCppVariablesEnd())
			|| (cppVariableAccess->isModifiedCppVariable(*cppVariable));
	}
	for ( cppVariable=(*save)->getCppVariablesBeginning(); cppVariable<(*save)->getCppVariablesEnd(); ++cppVariable ) {
		if (!(*cppVariable)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppVariable<EncodingT>::CppVariableIDEquality cppVariableIdEquality(*(*cppVariable));
		bUpdate = bUpdate || (std::find_if(o->getCppVariablesBeginning(), o->getCppVariablesEnd(), cppVariableIdEquality) == o->getCppVariablesEnd());
	}
	typename _CppFile<EncodingT>::CppEnumIterator cppEnum;
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
	typename _CppFile<EncodingT>::CMacroIterator cMacro;
	for ( cMacro=o->getCMacrosBeginning(); cMacro!=o->getCMacrosEnd(); ++cMacro ) {
		if (!(*cMacro)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CMacro<EncodingT>::CMacroIDEquality cMacroIdEquality(*(*cMacro));
		bUpdate = bUpdate || (std::find_if((*save)->getCMacrosBeginning(), (*save)->getCMacrosEnd(), cMacroIdEquality) == (*save)->getCMacrosEnd())
			|| (cMacroAccess->isModifiedCMacro(*cMacro));
	}
	for ( cMacro=(*save)->getCMacrosBeginning(); cMacro<(*save)->getCMacrosEnd(); ++cMacro ) {
		if (!(*cMacro)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CMacro<EncodingT>::CMacroIDEquality cMacroIdEquality(*(*cMacro));
		bUpdate = bUpdate || (std::find_if(o->getCMacrosBeginning(), o->getCMacrosEnd(), cMacroIdEquality) == o->getCMacrosEnd());
	}
	typename _CppFile<EncodingT>::CppNoticeIterator cppNotice;
	for ( cppNotice=o->getCppNoticesBeginning(); cppNotice!=o->getCppNoticesEnd(); ++cppNotice ) {
		if (!(*cppNotice)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppNotice<EncodingT>::CppNoticeIDEquality cppNoticeIdEquality(*(*cppNotice));
		bUpdate = bUpdate || (std::find_if((*save)->getCppNoticesBeginning(), (*save)->getCppNoticesEnd(), cppNoticeIdEquality) == (*save)->getCppNoticesEnd())
			|| (cppNoticeAccess->isModifiedCppNotice(*cppNotice));
	}
	for ( cppNotice=(*save)->getCppNoticesBeginning(); cppNotice<(*save)->getCppNoticesEnd(); ++cppNotice ) {
		if (!(*cppNotice)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppNotice<EncodingT>::CppNoticeIDEquality cppNoticeIdEquality(*(*cppNotice));
		bUpdate = bUpdate || (std::find_if(o->getCppNoticesBeginning(), o->getCppNoticesEnd(), cppNoticeIdEquality) == o->getCppNoticesEnd());
	}
	return bUpdate;
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::updateCppFile(boost::shared_ptr< _CppFile<EncodingT> > o)  
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
	_CppFunctionAccess<EncodingT>* cppDeclarationFunctionAccess = _CppFunctionAccess<EncodingT>::getInstance();
	if (!cppDeclarationFunctionAccess) {
		m_logger->errorStream() << "CppFunctionAccess class is not initialized.";
		throw NullPointerException("CppFunctionAccess class is not initialized.");
	}
	_CppFunctionAccess<EncodingT>* cppDefinitionFunctionAccess = _CppFunctionAccess<EncodingT>::getInstance();
	if (!cppDefinitionFunctionAccess) {
		m_logger->errorStream() << "CppFunctionAccess class is not initialized.";
		throw NullPointerException("CppFunctionAccess class is not initialized.");
	}
	_CppClassAccess<EncodingT>* cppClassAccess = _CppClassAccess<EncodingT>::getInstance();
	if (!cppClassAccess) {
		m_logger->errorStream() << "CppClassAccess class is not initialized.";
		throw NullPointerException("CppClassAccess class is not initialized.");
	}
	_CppIncludeAccess<EncodingT>* cppIncludeAccess = _CppIncludeAccess<EncodingT>::getInstance();
	if (!cppIncludeAccess) {
		m_logger->errorStream() << "CppIncludeAccess class is not initialized.";
		throw NullPointerException("CppIncludeAccess class is not initialized.");
	}
	_CppVariableAccess<EncodingT>* cppVariableAccess = _CppVariableAccess<EncodingT>::getInstance();
	if (!cppVariableAccess) {
		m_logger->errorStream() << "CppVariableAccess class is not initialized.";
		throw NullPointerException("CppVariableAccess class is not initialized.");
	}
	_CppEnumAccess<EncodingT>* cppEnumAccess = _CppEnumAccess<EncodingT>::getInstance();
	if (!cppEnumAccess) {
		m_logger->errorStream() << "CppEnumAccess class is not initialized.";
		throw NullPointerException("CppEnumAccess class is not initialized.");
	}
	_CMacroAccess<EncodingT>* cMacroAccess = _CMacroAccess<EncodingT>::getInstance();
	if (!cMacroAccess) {
		m_logger->errorStream() << "CMacroAccess class is not initialized.";
		throw NullPointerException("CMacroAccess class is not initialized.");
	}
	_CppNoticeAccess<EncodingT>* cppNoticeAccess = _CppNoticeAccess<EncodingT>::getInstance();
	if (!cppNoticeAccess) {
		m_logger->errorStream() << "CppNoticeAccess class is not initialized.";
		throw NullPointerException("CppNoticeAccess class is not initialized.");
	}
	typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(*o);
	typename std::list< boost::shared_ptr< _CppFile<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFileIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	try {
		if ( (*save)->getPath() != o->getPath() ) {
			values.addText( o->getPath() );
			fields.push_back( UCS("path") );
		}
		if ( (*save)->getName() != o->getName() ) {
			values.addText( o->getName() );
			fields.push_back( UCS("name") );
		}
		if ( (*save)->getLinesCount() != o->getLinesCount() ) {
			values.addInt64( o->getLinesCount() );
			fields.push_back( UCS("linesCount") );
		}
		if ( (*save)->getHash() != o->getHash() ) {
			values.addInt64( o->getHash() );
			fields.push_back( UCS("hash") );
		}
		if ( (*save)->getAnalyzed() != o->getAnalyzed() ) {
			values.addInt64( o->getAnalyzed() );
			fields.push_back( UCS("analyzed") );
		}
		if ( !o->isNullTextFile() && typename _TextFile<EncodingT>::TextFileIDEquality(-1)(o->getTextFile()) ) {
			m_logger->errorStream() << "idText : Identifier is null.";
			throw InvalidQueryException("idText : Identifier is null.");
		}
		else if ( !o->isNullTextFile() && !typename _TextFile<EncodingT>::TextFileIDEquality(*(o->getTextFile()))((*save)->getTextFile()) ) {
			values.addInt64( o->getTextFile()->getRowid() );
			fields.push_back( UCS("idText") );
		}
		else if ( o->isNullTextFile() && !(*save)->isNullTextFile() ) {
			m_logger->errorStream() << "idText : null reference is forbidden.";
			throw InvalidQueryException("idText : null reference is forbidden.");
		}
		if ( !o->isNullCppFileType() && typename _CppFileType<EncodingT>::CppFileTypeIDEquality(-1)(o->getCppFileType()) ) {
			m_logger->errorStream() << "idType : Identifier is null.";
			throw InvalidQueryException("idType : Identifier is null.");
		}
		else if ( !o->isNullCppFileType() && !typename _CppFileType<EncodingT>::CppFileTypeIDEquality(*(o->getCppFileType()))((*save)->getCppFileType()) ) {
			values.addInt64( o->getCppFileType()->getIdentifier() );
			fields.push_back( UCS("idType") );
		}
		else if ( o->isNullCppFileType() && !(*save)->isNullCppFileType() ) {
			m_logger->errorStream() << "idType : null reference is forbidden.";
			throw InvalidQueryException("idType : null reference is forbidden.");
		}
		std::vector< boost::shared_ptr< _CppFunction<EncodingT> > > listOfCppDeclarationFunctionToAdd;
		std::vector< boost::shared_ptr< _CppFunction<EncodingT> > > listOfCppDeclarationFunctionToUpdate;
		typename _CppFile<EncodingT>::CppDeclarationFunctionIterator cppDeclarationFunction;
		for ( cppDeclarationFunction=o->getCppDeclarationFunctionsBeginning(); cppDeclarationFunction!=o->getCppDeclarationFunctionsEnd(); ++cppDeclarationFunction ) {
			if (!(*cppDeclarationFunction)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*cppDeclarationFunction)->setCppDeclarationFile(o);
			typename _CppFunction<EncodingT>::CppFunctionIDEquality cppDeclarationFunctionIdEquality(*(*cppDeclarationFunction));
			if ( std::find_if((*save)->getCppDeclarationFunctionsBeginning(), (*save)->getCppDeclarationFunctionsEnd(), cppDeclarationFunctionIdEquality) == (*save)->getCppDeclarationFunctionsEnd()) {
				listOfCppDeclarationFunctionToAdd.push_back(*cppDeclarationFunction);
			}
			else {
				if (cppDeclarationFunctionAccess->isModifiedCppFunction(*cppDeclarationFunction))
					listOfCppDeclarationFunctionToUpdate.push_back(*cppDeclarationFunction);
			}
		}
		std::vector< boost::shared_ptr< _CppFunction<EncodingT> > > listOfCppDeclarationFunctionToRemove;
		for ( cppDeclarationFunction=(*save)->getCppDeclarationFunctionsBeginning(); cppDeclarationFunction<(*save)->getCppDeclarationFunctionsEnd(); ++cppDeclarationFunction ) {
			if (!(*cppDeclarationFunction)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			typename _CppFunction<EncodingT>::CppFunctionIDEquality cppDeclarationFunctionIdEquality(*(*cppDeclarationFunction));
			if ( std::find_if(o->getCppDeclarationFunctionsBeginning(), o->getCppDeclarationFunctionsEnd(), cppDeclarationFunctionIdEquality) == o->getCppDeclarationFunctionsEnd()) {
				listOfCppDeclarationFunctionToRemove.push_back(*cppDeclarationFunction);
			}
		}
		std::vector< boost::shared_ptr< _CppFunction<EncodingT> > > listOfCppDefinitionFunctionToAdd;
		std::vector< boost::shared_ptr< _CppFunction<EncodingT> > > listOfCppDefinitionFunctionToUpdate;
		typename _CppFile<EncodingT>::CppDefinitionFunctionIterator cppDefinitionFunction;
		for ( cppDefinitionFunction=o->getCppDefinitionFunctionsBeginning(); cppDefinitionFunction!=o->getCppDefinitionFunctionsEnd(); ++cppDefinitionFunction ) {
			if (!(*cppDefinitionFunction)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*cppDefinitionFunction)->setCppDefinitionFile(o);
			typename _CppFunction<EncodingT>::CppFunctionIDEquality cppDefinitionFunctionIdEquality(*(*cppDefinitionFunction));
			if ( std::find_if((*save)->getCppDefinitionFunctionsBeginning(), (*save)->getCppDefinitionFunctionsEnd(), cppDefinitionFunctionIdEquality) == (*save)->getCppDefinitionFunctionsEnd()) {
				listOfCppDefinitionFunctionToAdd.push_back(*cppDefinitionFunction);
			}
			else {
				if (cppDefinitionFunctionAccess->isModifiedCppFunction(*cppDefinitionFunction))
					listOfCppDefinitionFunctionToUpdate.push_back(*cppDefinitionFunction);
			}
		}
		std::vector< boost::shared_ptr< _CppFunction<EncodingT> > > listOfCppDefinitionFunctionToRemove;
		for ( cppDefinitionFunction=(*save)->getCppDefinitionFunctionsBeginning(); cppDefinitionFunction<(*save)->getCppDefinitionFunctionsEnd(); ++cppDefinitionFunction ) {
			if (!(*cppDefinitionFunction)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			typename _CppFunction<EncodingT>::CppFunctionIDEquality cppDefinitionFunctionIdEquality(*(*cppDefinitionFunction));
			if ( std::find_if(o->getCppDefinitionFunctionsBeginning(), o->getCppDefinitionFunctionsEnd(), cppDefinitionFunctionIdEquality) == o->getCppDefinitionFunctionsEnd()) {
				listOfCppDefinitionFunctionToRemove.push_back(*cppDefinitionFunction);
			}
		}
		std::vector< boost::shared_ptr< _CppClass<EncodingT> > > listOfCppClassToAdd;
		std::vector< boost::shared_ptr< _CppClass<EncodingT> > > listOfCppClassToUpdate;
		typename _CppFile<EncodingT>::CppClassIterator cppClass;
		for ( cppClass=o->getCppClasssBeginning(); cppClass!=o->getCppClasssEnd(); ++cppClass ) {
			if (!(*cppClass)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*cppClass)->setCppFile(o);
			typename _CppClass<EncodingT>::CppClassIDEquality cppClassIdEquality(*(*cppClass));
			if ( std::find_if((*save)->getCppClasssBeginning(), (*save)->getCppClasssEnd(), cppClassIdEquality) == (*save)->getCppClasssEnd()) {
				listOfCppClassToAdd.push_back(*cppClass);
			}
			else {
				if (cppClassAccess->isModifiedCppClass(*cppClass))
					listOfCppClassToUpdate.push_back(*cppClass);
			}
		}
		std::vector< boost::shared_ptr< _CppClass<EncodingT> > > listOfCppClassToRemove;
		for ( cppClass=(*save)->getCppClasssBeginning(); cppClass<(*save)->getCppClasssEnd(); ++cppClass ) {
			if (!(*cppClass)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			typename _CppClass<EncodingT>::CppClassIDEquality cppClassIdEquality(*(*cppClass));
			if ( std::find_if(o->getCppClasssBeginning(), o->getCppClasssEnd(), cppClassIdEquality) == o->getCppClasssEnd()) {
				listOfCppClassToRemove.push_back(*cppClass);
			}
		}
		std::vector< boost::shared_ptr< _CppInclude<EncodingT> > > listOfCppIncludeToAdd;
		std::vector< boost::shared_ptr< _CppInclude<EncodingT> > > listOfCppIncludeToUpdate;
		typename _CppFile<EncodingT>::CppIncludeIterator cppInclude;
		for ( cppInclude=o->getCppIncludesBeginning(); cppInclude!=o->getCppIncludesEnd(); ++cppInclude ) {
			if (!(*cppInclude)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*cppInclude)->setCppFile(o);
			typename _CppInclude<EncodingT>::CppIncludeIDEquality cppIncludeIdEquality(*(*cppInclude));
			if ( std::find_if((*save)->getCppIncludesBeginning(), (*save)->getCppIncludesEnd(), cppIncludeIdEquality) == (*save)->getCppIncludesEnd()) {
				listOfCppIncludeToAdd.push_back(*cppInclude);
			}
			else {
				if (cppIncludeAccess->isModifiedCppInclude(*cppInclude))
					listOfCppIncludeToUpdate.push_back(*cppInclude);
			}
		}
		std::vector< boost::shared_ptr< _CppInclude<EncodingT> > > listOfCppIncludeToRemove;
		for ( cppInclude=(*save)->getCppIncludesBeginning(); cppInclude<(*save)->getCppIncludesEnd(); ++cppInclude ) {
			if (!(*cppInclude)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			typename _CppInclude<EncodingT>::CppIncludeIDEquality cppIncludeIdEquality(*(*cppInclude));
			if ( std::find_if(o->getCppIncludesBeginning(), o->getCppIncludesEnd(), cppIncludeIdEquality) == o->getCppIncludesEnd()) {
				listOfCppIncludeToRemove.push_back(*cppInclude);
			}
		}
		std::vector< boost::shared_ptr< _CppVariable<EncodingT> > > listOfCppVariableToAdd;
		std::vector< boost::shared_ptr< _CppVariable<EncodingT> > > listOfCppVariableToUpdate;
		typename _CppFile<EncodingT>::CppVariableIterator cppVariable;
		for ( cppVariable=o->getCppVariablesBeginning(); cppVariable!=o->getCppVariablesEnd(); ++cppVariable ) {
			if (!(*cppVariable)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*cppVariable)->setCppFile(o);
			typename _CppVariable<EncodingT>::CppVariableIDEquality cppVariableIdEquality(*(*cppVariable));
			if ( std::find_if((*save)->getCppVariablesBeginning(), (*save)->getCppVariablesEnd(), cppVariableIdEquality) == (*save)->getCppVariablesEnd()) {
				listOfCppVariableToAdd.push_back(*cppVariable);
			}
			else {
				if (cppVariableAccess->isModifiedCppVariable(*cppVariable))
					listOfCppVariableToUpdate.push_back(*cppVariable);
			}
		}
		std::vector< boost::shared_ptr< _CppVariable<EncodingT> > > listOfCppVariableToRemove;
		for ( cppVariable=(*save)->getCppVariablesBeginning(); cppVariable<(*save)->getCppVariablesEnd(); ++cppVariable ) {
			if (!(*cppVariable)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			typename _CppVariable<EncodingT>::CppVariableIDEquality cppVariableIdEquality(*(*cppVariable));
			if ( std::find_if(o->getCppVariablesBeginning(), o->getCppVariablesEnd(), cppVariableIdEquality) == o->getCppVariablesEnd()) {
				listOfCppVariableToRemove.push_back(*cppVariable);
			}
		}
		std::vector< boost::shared_ptr< _CppEnum<EncodingT> > > listOfCppEnumToAdd;
		std::vector< boost::shared_ptr< _CppEnum<EncodingT> > > listOfCppEnumToUpdate;
		typename _CppFile<EncodingT>::CppEnumIterator cppEnum;
		for ( cppEnum=o->getCppEnumsBeginning(); cppEnum!=o->getCppEnumsEnd(); ++cppEnum ) {
			if (!(*cppEnum)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*cppEnum)->setCppFile(o);
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
		std::vector< boost::shared_ptr< _CMacro<EncodingT> > > listOfCMacroToAdd;
		std::vector< boost::shared_ptr< _CMacro<EncodingT> > > listOfCMacroToUpdate;
		typename _CppFile<EncodingT>::CMacroIterator cMacro;
		for ( cMacro=o->getCMacrosBeginning(); cMacro!=o->getCMacrosEnd(); ++cMacro ) {
			if (!(*cMacro)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*cMacro)->setCppFile(o);
			typename _CMacro<EncodingT>::CMacroIDEquality cMacroIdEquality(*(*cMacro));
			if ( std::find_if((*save)->getCMacrosBeginning(), (*save)->getCMacrosEnd(), cMacroIdEquality) == (*save)->getCMacrosEnd()) {
				listOfCMacroToAdd.push_back(*cMacro);
			}
			else {
				if (cMacroAccess->isModifiedCMacro(*cMacro))
					listOfCMacroToUpdate.push_back(*cMacro);
			}
		}
		std::vector< boost::shared_ptr< _CMacro<EncodingT> > > listOfCMacroToRemove;
		for ( cMacro=(*save)->getCMacrosBeginning(); cMacro<(*save)->getCMacrosEnd(); ++cMacro ) {
			if (!(*cMacro)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			typename _CMacro<EncodingT>::CMacroIDEquality cMacroIdEquality(*(*cMacro));
			if ( std::find_if(o->getCMacrosBeginning(), o->getCMacrosEnd(), cMacroIdEquality) == o->getCMacrosEnd()) {
				listOfCMacroToRemove.push_back(*cMacro);
			}
		}
		std::vector< boost::shared_ptr< _CppNotice<EncodingT> > > listOfCppNoticeToAdd;
		std::vector< boost::shared_ptr< _CppNotice<EncodingT> > > listOfCppNoticeToUpdate;
		typename _CppFile<EncodingT>::CppNoticeIterator cppNotice;
		for ( cppNotice=o->getCppNoticesBeginning(); cppNotice!=o->getCppNoticesEnd(); ++cppNotice ) {
			if (!(*cppNotice)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*cppNotice)->setCppFile(o);
			typename _CppNotice<EncodingT>::CppNoticeIDEquality cppNoticeIdEquality(*(*cppNotice));
			if ( std::find_if((*save)->getCppNoticesBeginning(), (*save)->getCppNoticesEnd(), cppNoticeIdEquality) == (*save)->getCppNoticesEnd()) {
				listOfCppNoticeToAdd.push_back(*cppNotice);
			}
			else {
				if (cppNoticeAccess->isModifiedCppNotice(*cppNotice))
					listOfCppNoticeToUpdate.push_back(*cppNotice);
			}
		}
		std::vector< boost::shared_ptr< _CppNotice<EncodingT> > > listOfCppNoticeToRemove;
		for ( cppNotice=(*save)->getCppNoticesBeginning(); cppNotice<(*save)->getCppNoticesEnd(); ++cppNotice ) {
			if (!(*cppNotice)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			typename _CppNotice<EncodingT>::CppNoticeIDEquality cppNoticeIdEquality(*(*cppNotice));
			if ( std::find_if(o->getCppNoticesBeginning(), o->getCppNoticesEnd(), cppNoticeIdEquality) == o->getCppNoticesEnd()) {
				listOfCppNoticeToRemove.push_back(*cppNotice);
			}
		}
		if (!fields.empty()) {
			statement.swap( connection->update(UCS("cppFile"), fields, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, UCS("cppFile"), o);
		}
		for ( cppDeclarationFunction=listOfCppDeclarationFunctionToAdd.begin(); cppDeclarationFunction!=listOfCppDeclarationFunctionToAdd.end() ; ++cppDeclarationFunction ) {
			cppDeclarationFunctionAccess->insertCppFunction(*cppDeclarationFunction);
		}
		for ( cppDeclarationFunction=listOfCppDeclarationFunctionToUpdate.begin(); cppDeclarationFunction!=listOfCppDeclarationFunctionToUpdate.end() ; ++cppDeclarationFunction ) {
			cppDeclarationFunctionAccess->updateCppFunction(*cppDeclarationFunction);
		}
		for ( cppDeclarationFunction=listOfCppDeclarationFunctionToRemove.begin(); cppDeclarationFunction!=listOfCppDeclarationFunctionToRemove.end() ; ++cppDeclarationFunction ) {
			cppDeclarationFunctionAccess->fillCppDeclarationFile(*cppDeclarationFunction);
			(*cppDeclarationFunction)->eraseCppDeclarationFile();
			cppDeclarationFunctionAccess->updateCppFunction(*cppDeclarationFunction);
		}
		for ( cppDefinitionFunction=listOfCppDefinitionFunctionToAdd.begin(); cppDefinitionFunction!=listOfCppDefinitionFunctionToAdd.end() ; ++cppDefinitionFunction ) {
			cppDefinitionFunctionAccess->insertCppFunction(*cppDefinitionFunction);
		}
		for ( cppDefinitionFunction=listOfCppDefinitionFunctionToUpdate.begin(); cppDefinitionFunction!=listOfCppDefinitionFunctionToUpdate.end() ; ++cppDefinitionFunction ) {
			cppDefinitionFunctionAccess->updateCppFunction(*cppDefinitionFunction);
		}
		for ( cppDefinitionFunction=listOfCppDefinitionFunctionToRemove.begin(); cppDefinitionFunction!=listOfCppDefinitionFunctionToRemove.end() ; ++cppDefinitionFunction ) {
			cppDefinitionFunctionAccess->fillCppDefinitionFile(*cppDefinitionFunction);
			(*cppDefinitionFunction)->eraseCppDefinitionFile();
			cppDefinitionFunctionAccess->updateCppFunction(*cppDefinitionFunction);
		}
		for ( cppClass=listOfCppClassToAdd.begin(); cppClass!=listOfCppClassToAdd.end() ; ++cppClass ) {
			cppClassAccess->insertCppClass(*cppClass);
		}
		for ( cppClass=listOfCppClassToUpdate.begin(); cppClass!=listOfCppClassToUpdate.end() ; ++cppClass ) {
			cppClassAccess->updateCppClass(*cppClass);
		}
		for ( cppClass=listOfCppClassToRemove.begin(); cppClass!=listOfCppClassToRemove.end() ; ++cppClass ) {
			cppClassAccess->deleteCppClass(*cppClass);
		}
		for ( cppInclude=listOfCppIncludeToAdd.begin(); cppInclude!=listOfCppIncludeToAdd.end() ; ++cppInclude ) {
			cppIncludeAccess->insertCppInclude(*cppInclude);
		}
		for ( cppInclude=listOfCppIncludeToUpdate.begin(); cppInclude!=listOfCppIncludeToUpdate.end() ; ++cppInclude ) {
			cppIncludeAccess->updateCppInclude(*cppInclude);
		}
		for ( cppInclude=listOfCppIncludeToRemove.begin(); cppInclude!=listOfCppIncludeToRemove.end() ; ++cppInclude ) {
			cppIncludeAccess->deleteCppInclude(*cppInclude);
		}
		for ( cppVariable=listOfCppVariableToAdd.begin(); cppVariable!=listOfCppVariableToAdd.end() ; ++cppVariable ) {
			cppVariableAccess->insertCppVariable(*cppVariable);
		}
		for ( cppVariable=listOfCppVariableToUpdate.begin(); cppVariable!=listOfCppVariableToUpdate.end() ; ++cppVariable ) {
			cppVariableAccess->updateCppVariable(*cppVariable);
		}
		for ( cppVariable=listOfCppVariableToRemove.begin(); cppVariable!=listOfCppVariableToRemove.end() ; ++cppVariable ) {
			cppVariableAccess->deleteCppVariable(*cppVariable);
		}
		for ( cppEnum=listOfCppEnumToAdd.begin(); cppEnum!=listOfCppEnumToAdd.end() ; ++cppEnum ) {
			cppEnumAccess->insertCppEnum(*cppEnum);
		}
		for ( cppEnum=listOfCppEnumToUpdate.begin(); cppEnum!=listOfCppEnumToUpdate.end() ; ++cppEnum ) {
			cppEnumAccess->updateCppEnum(*cppEnum);
		}
		for ( cppEnum=listOfCppEnumToRemove.begin(); cppEnum!=listOfCppEnumToRemove.end() ; ++cppEnum ) {
			cppEnumAccess->deleteCppEnum(*cppEnum);
		}
		for ( cMacro=listOfCMacroToAdd.begin(); cMacro!=listOfCMacroToAdd.end() ; ++cMacro ) {
			cMacroAccess->insertCMacro(*cMacro);
		}
		for ( cMacro=listOfCMacroToUpdate.begin(); cMacro!=listOfCMacroToUpdate.end() ; ++cMacro ) {
			cMacroAccess->updateCMacro(*cMacro);
		}
		for ( cMacro=listOfCMacroToRemove.begin(); cMacro!=listOfCMacroToRemove.end() ; ++cMacro ) {
			cMacroAccess->deleteCMacro(*cMacro);
		}
		for ( cppNotice=listOfCppNoticeToAdd.begin(); cppNotice!=listOfCppNoticeToAdd.end() ; ++cppNotice ) {
			cppNoticeAccess->insertCppNotice(*cppNotice);
		}
		for ( cppNotice=listOfCppNoticeToUpdate.begin(); cppNotice!=listOfCppNoticeToUpdate.end() ; ++cppNotice ) {
			cppNoticeAccess->updateCppNotice(*cppNotice);
		}
		for ( cppNotice=listOfCppNoticeToRemove.begin(); cppNotice!=listOfCppNoticeToRemove.end() ; ++cppNotice ) {
			cppNoticeAccess->deleteCppNotice(*cppNotice);
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
_CppFileAccess<EncodingT>::insertCppFile(boost::shared_ptr< _CppFile<EncodingT> > o)  
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
	_CppFunctionAccess<EncodingT>* cppDeclarationFunctionAccess = _CppFunctionAccess<EncodingT>::getInstance();
	if (!cppDeclarationFunctionAccess) {
		m_logger->errorStream() << "CppFunctionAccess class is not initialized.";
		throw NullPointerException("CppFunctionAccess class is not initialized.");
	}
	_CppFunctionAccess<EncodingT>* cppDefinitionFunctionAccess = _CppFunctionAccess<EncodingT>::getInstance();
	if (!cppDefinitionFunctionAccess) {
		m_logger->errorStream() << "CppFunctionAccess class is not initialized.";
		throw NullPointerException("CppFunctionAccess class is not initialized.");
	}
	_CppClassAccess<EncodingT>* cppClassAccess = _CppClassAccess<EncodingT>::getInstance();
	if (!cppClassAccess) {
		m_logger->errorStream() << "CppClassAccess class is not initialized.";
		throw NullPointerException("CppClassAccess class is not initialized.");
	}
	_CppIncludeAccess<EncodingT>* cppIncludeAccess = _CppIncludeAccess<EncodingT>::getInstance();
	if (!cppIncludeAccess) {
		m_logger->errorStream() << "CppIncludeAccess class is not initialized.";
		throw NullPointerException("CppIncludeAccess class is not initialized.");
	}
	_CppVariableAccess<EncodingT>* cppVariableAccess = _CppVariableAccess<EncodingT>::getInstance();
	if (!cppVariableAccess) {
		m_logger->errorStream() << "CppVariableAccess class is not initialized.";
		throw NullPointerException("CppVariableAccess class is not initialized.");
	}
	_CppEnumAccess<EncodingT>* cppEnumAccess = _CppEnumAccess<EncodingT>::getInstance();
	if (!cppEnumAccess) {
		m_logger->errorStream() << "CppEnumAccess class is not initialized.";
		throw NullPointerException("CppEnumAccess class is not initialized.");
	}
	_CMacroAccess<EncodingT>* cMacroAccess = _CMacroAccess<EncodingT>::getInstance();
	if (!cMacroAccess) {
		m_logger->errorStream() << "CMacroAccess class is not initialized.";
		throw NullPointerException("CMacroAccess class is not initialized.");
	}
	_CppNoticeAccess<EncodingT>* cppNoticeAccess = _CppNoticeAccess<EncodingT>::getInstance();
	if (!cppNoticeAccess) {
		m_logger->errorStream() << "CppNoticeAccess class is not initialized.";
		throw NullPointerException("CppNoticeAccess class is not initialized.");
	}
	try {
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
		int id = connection->selectMaxID(UCS("identifier"), UCS("cppFile"))+1;
		values.addInt( id );
		fields.push_back( UCS("identifier") );
		if ( !o->isNullTextFile() && typename _TextFile<EncodingT>::TextFileIDEquality(-1)(o->getTextFile()) ) {
			m_logger->errorStream() << "idText : Identifier is null.";
			throw InvalidQueryException("idText : Identifier is null.");
		}
		else if ( !o->isNullTextFile() ) {
			values.addInt64( o->getTextFile()->getRowid() );
			fields.push_back( UCS("idText") );
		}
		else {
			m_logger->errorStream() << "idText : null reference is forbidden.";
			throw InvalidQueryException("idText : null reference is forbidden.");
		}
		values.addText( o->getPath() );
		fields.push_back( UCS("path") );
		values.addText( o->getName() );
		fields.push_back( UCS("name") );
		if ( !o->isNullCppFileType() && typename _CppFileType<EncodingT>::CppFileTypeIDEquality(-1)(o->getCppFileType()) ) {
			m_logger->errorStream() << "idType : Identifier is null.";
			throw InvalidQueryException("idType : Identifier is null.");
		}
		else if ( !o->isNullCppFileType() ) {
			values.addInt64( o->getCppFileType()->getIdentifier() );
			fields.push_back( UCS("idType") );
		}
		else {
			m_logger->errorStream() << "idType : null reference is forbidden.";
			throw InvalidQueryException("idType : null reference is forbidden.");
		}
		values.addInt64( o->getLinesCount() );
		fields.push_back( UCS("linesCount") );
		values.addInt64( o->getHash() );
		fields.push_back( UCS("hash") );
		values.addInt64( o->getAnalyzed() );
		fields.push_back( UCS("analyzed") );
		statement.swap( connection->insert(UCS("cppFile"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		o->setIdentifier(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, UCS("cppFile"), o);
		typename _CppFile<EncodingT>::CppDeclarationFunctionIterator cppDeclarationFunction;
		for ( cppDeclarationFunction=o->getCppDeclarationFunctionsBeginning(); cppDeclarationFunction!=o->getCppDeclarationFunctionsEnd(); ++cppDeclarationFunction ) {
			(*cppDeclarationFunction)->setCppDeclarationFile(o);
			cppDeclarationFunctionAccess->insertCppFunction(*cppDeclarationFunction);
		}
		typename _CppFile<EncodingT>::CppDefinitionFunctionIterator cppDefinitionFunction;
		for ( cppDefinitionFunction=o->getCppDefinitionFunctionsBeginning(); cppDefinitionFunction!=o->getCppDefinitionFunctionsEnd(); ++cppDefinitionFunction ) {
			(*cppDefinitionFunction)->setCppDefinitionFile(o);
			cppDefinitionFunctionAccess->insertCppFunction(*cppDefinitionFunction);
		}
		typename _CppFile<EncodingT>::CppClassIterator cppClass;
		for ( cppClass=o->getCppClasssBeginning(); cppClass!=o->getCppClasssEnd(); ++cppClass ) {
			(*cppClass)->setCppFile(o);
			cppClassAccess->insertCppClass(*cppClass);
		}
		typename _CppFile<EncodingT>::CppIncludeIterator cppInclude;
		for ( cppInclude=o->getCppIncludesBeginning(); cppInclude!=o->getCppIncludesEnd(); ++cppInclude ) {
			(*cppInclude)->setCppFile(o);
			cppIncludeAccess->insertCppInclude(*cppInclude);
		}
		typename _CppFile<EncodingT>::CppVariableIterator cppVariable;
		for ( cppVariable=o->getCppVariablesBeginning(); cppVariable!=o->getCppVariablesEnd(); ++cppVariable ) {
			(*cppVariable)->setCppFile(o);
			cppVariableAccess->insertCppVariable(*cppVariable);
		}
		typename _CppFile<EncodingT>::CppEnumIterator cppEnum;
		for ( cppEnum=o->getCppEnumsBeginning(); cppEnum!=o->getCppEnumsEnd(); ++cppEnum ) {
			(*cppEnum)->setCppFile(o);
			cppEnumAccess->insertCppEnum(*cppEnum);
		}
		typename _CppFile<EncodingT>::CMacroIterator cMacro;
		for ( cMacro=o->getCMacrosBeginning(); cMacro!=o->getCMacrosEnd(); ++cMacro ) {
			(*cMacro)->setCppFile(o);
			cMacroAccess->insertCMacro(*cMacro);
		}
		typename _CppFile<EncodingT>::CppNoticeIterator cppNotice;
		for ( cppNotice=o->getCppNoticesBeginning(); cppNotice!=o->getCppNoticesEnd(); ++cppNotice ) {
			(*cppNotice)->setCppFile(o);
			cppNoticeAccess->insertCppNotice(*cppNotice);
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
_CppFileAccess<EncodingT>::deleteCppFile(boost::shared_ptr< _CppFile<EncodingT> > o)  
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
	_CppFunctionAccess<EncodingT>* cppDeclarationFunctionAccess = _CppFunctionAccess<EncodingT>::getInstance();
	if (!cppDeclarationFunctionAccess) {
		m_logger->errorStream() << "CppFunctionAccess class is not initialized.";
		throw NullPointerException("CppFunctionAccess class is not initialized.");
	}
	_CppFunctionAccess<EncodingT>* cppDefinitionFunctionAccess = _CppFunctionAccess<EncodingT>::getInstance();
	if (!cppDefinitionFunctionAccess) {
		m_logger->errorStream() << "CppFunctionAccess class is not initialized.";
		throw NullPointerException("CppFunctionAccess class is not initialized.");
	}
	_CppClassAccess<EncodingT>* cppClassAccess = _CppClassAccess<EncodingT>::getInstance();
	if (!cppClassAccess) {
		m_logger->errorStream() << "CppClassAccess class is not initialized.";
		throw NullPointerException("CppClassAccess class is not initialized.");
	}
	_CppIncludeAccess<EncodingT>* cppIncludeAccess = _CppIncludeAccess<EncodingT>::getInstance();
	if (!cppIncludeAccess) {
		m_logger->errorStream() << "CppIncludeAccess class is not initialized.";
		throw NullPointerException("CppIncludeAccess class is not initialized.");
	}
	_CppVariableAccess<EncodingT>* cppVariableAccess = _CppVariableAccess<EncodingT>::getInstance();
	if (!cppVariableAccess) {
		m_logger->errorStream() << "CppVariableAccess class is not initialized.";
		throw NullPointerException("CppVariableAccess class is not initialized.");
	}
	_CppEnumAccess<EncodingT>* cppEnumAccess = _CppEnumAccess<EncodingT>::getInstance();
	if (!cppEnumAccess) {
		m_logger->errorStream() << "CppEnumAccess class is not initialized.";
		throw NullPointerException("CppEnumAccess class is not initialized.");
	}
	_CMacroAccess<EncodingT>* cMacroAccess = _CMacroAccess<EncodingT>::getInstance();
	if (!cMacroAccess) {
		m_logger->errorStream() << "CMacroAccess class is not initialized.";
		throw NullPointerException("CMacroAccess class is not initialized.");
	}
	_CppNoticeAccess<EncodingT>* cppNoticeAccess = _CppNoticeAccess<EncodingT>::getInstance();
	if (!cppNoticeAccess) {
		m_logger->errorStream() << "CppNoticeAccess class is not initialized.";
		throw NullPointerException("CppNoticeAccess class is not initialized.");
	}
	typename _CppFile<EncodingT>::CppFileIDEquality CppFileIdEquality(*o);
	typename std::list< boost::shared_ptr< _CppFile<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), CppFileIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before deletion.";
		throw UnSelectedObjectException("You must select object before deletion.");
	}
	try {
		typename _CppFile<EncodingT>::CppDeclarationFunctionIterator cppDeclarationFunction;
		fillAllCppDeclarationFunctions(o);
		for ( cppDeclarationFunction=o->getCppDeclarationFunctionsBeginning(); cppDeclarationFunction!=o->getCppDeclarationFunctionsEnd(); ++cppDeclarationFunction ) {
			cppDeclarationFunctionAccess->fillCppDeclarationFile(*cppDeclarationFunction);
			(*cppDeclarationFunction)->eraseCppDeclarationFile();
			cppDeclarationFunctionAccess->updateCppFunction(*cppDeclarationFunction);
		}
		typename _CppFile<EncodingT>::CppDefinitionFunctionIterator cppDefinitionFunction;
		fillAllCppDefinitionFunctions(o);
		for ( cppDefinitionFunction=o->getCppDefinitionFunctionsBeginning(); cppDefinitionFunction!=o->getCppDefinitionFunctionsEnd(); ++cppDefinitionFunction ) {
			cppDefinitionFunctionAccess->fillCppDefinitionFile(*cppDefinitionFunction);
			(*cppDefinitionFunction)->eraseCppDefinitionFile();
			cppDefinitionFunctionAccess->updateCppFunction(*cppDefinitionFunction);
		}
		typename _CppFile<EncodingT>::CppClassIterator cppClass;
		fillAllCppClasss(o);
		for ( cppClass=o->getCppClasssBeginning(); cppClass!=o->getCppClasssEnd(); ++cppClass ) {
			cppClassAccess->deleteCppClass(*cppClass);
		}
		typename _CppFile<EncodingT>::CppIncludeIterator cppInclude;
		fillAllCppIncludes(o);
		for ( cppInclude=o->getCppIncludesBeginning(); cppInclude!=o->getCppIncludesEnd(); ++cppInclude ) {
			cppIncludeAccess->deleteCppInclude(*cppInclude);
		}
		typename _CppFile<EncodingT>::CppVariableIterator cppVariable;
		fillAllCppVariables(o);
		for ( cppVariable=o->getCppVariablesBeginning(); cppVariable!=o->getCppVariablesEnd(); ++cppVariable ) {
			cppVariableAccess->deleteCppVariable(*cppVariable);
		}
		typename _CppFile<EncodingT>::CppEnumIterator cppEnum;
		fillAllCppEnums(o);
		for ( cppEnum=o->getCppEnumsBeginning(); cppEnum!=o->getCppEnumsEnd(); ++cppEnum ) {
			cppEnumAccess->deleteCppEnum(*cppEnum);
		}
		typename _CppFile<EncodingT>::CMacroIterator cMacro;
		fillAllCMacros(o);
		for ( cMacro=o->getCMacrosBeginning(); cMacro!=o->getCMacrosEnd(); ++cMacro ) {
			cMacroAccess->deleteCMacro(*cMacro);
		}
		typename _CppFile<EncodingT>::CppNoticeIterator cppNotice;
		fillAllCppNotices(o);
		for ( cppNotice=o->getCppNoticesBeginning(); cppNotice!=o->getCppNoticesEnd(); ++cppNotice ) {
			cppNoticeAccess->deleteCppNotice(*cppNotice);
		}
		statement.swap( connection->deleteFrom(UCS("cppFile"), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, UCS("cppFile"), o);
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
typename _CppFileAccess<EncodingT>::connection_t
_CppFileAccess<EncodingT>::addInsertSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_insertSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppFileAccess<EncodingT>::connection_t
_CppFileAccess<EncodingT>::addUpdateSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_updateSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppFileAccess<EncodingT>::connection_t
_CppFileAccess<EncodingT>::addDeleteSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_deleteSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppFileAccess<EncodingT>::connection_t
_CppFileAccess<EncodingT>::addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber)  
{
	return m_transactionSignal.connect(subscriber);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::removeInsertSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::removeUpdateSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::removeDeleteSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::removeTransactionSignal(connection_t connection)  
{
	connection.disconnect();
}


NAMESPACE_END

#undef C
#undef A

