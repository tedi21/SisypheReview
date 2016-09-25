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
	_TextFileAccess<EncodingT>* textFileAccess = _TextFileAccess<EncodingT>::getInstance();
	if (!textFileAccess) {
		m_logger->errorStream() << "TextFileAccess class is not initialized.";
		throw NullPointerException("TextFileAccess class is not initialized.");
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(C("idText"));
	columns.push_back(C("path"));
	columns.push_back(C("name"));
	columns.push_back(C("linesCount"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,C("cppFile")), filter) );
	while( statement.executeStep() ) {
		int textFile;
		typename EncodingT::string_t path;
		typename EncodingT::string_t name;
		int linesCount;
		if (statement.getInt( 0, textFile ) &&
			statement.getText( 1, path ) &&
			statement.getText( 2, name ) &&
			statement.getInt( 3, linesCount )) {
			value.reset(new _CppFile<EncodingT>(
				textFileAccess->getOneTextFile(textFile),
				path,
				name,
				linesCount));
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
_CppFileAccess<EncodingT>::getOneCppFile(boost::shared_ptr< _TextFile<EncodingT> > textFile) const 
{
	if ( textFile == NULL || typename _TextFile<EncodingT>::TextFileIDEquality(-1)(textFile) ) {
		m_logger->errorStream() << "TextFile : Identifier is null.";
		throw UnIdentifiedObjectException("TextFile : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _CppFile<EncodingT> > > result = getManyCppFiles(C("idText = ") /*+ C("\'") */+ C(ToString::parse(textFile->getRowid()))/* + C("\'")*/);
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
	_TextFileAccess<EncodingT>* textFileAccess = _TextFileAccess<EncodingT>::getInstance();
	if (!textFileAccess) {
		m_logger->errorStream() << "TextFileAccess class is not initialized.";
		throw NullPointerException("TextFileAccess class is not initialized.");
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(C("idText"));
	columns.push_back(C("path"));
	columns.push_back(C("name"));
	columns.push_back(C("linesCount"));
	if (!addition || !connection->isTransactionInProgress()) {
		cancelSelection();
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
	}
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,C("cppFile")), filter, nowait) );
	while( statement.executeStep() ) {
		int textFile;
		typename EncodingT::string_t path;
		typename EncodingT::string_t name;
		int linesCount;
		if (statement.getInt( 0, textFile ) &&
			statement.getText( 1, path ) &&
			statement.getText( 2, name ) &&
			statement.getInt( 3, linesCount )) {
			tab.push_back(boost::shared_ptr< _CppFile<EncodingT> >(new _CppFile<EncodingT>(
				textFileAccess->selectOneTextFile(textFile, false, true),
				path,
				name,
				linesCount)));
		}
	}
	m_backup.insert(m_backup.end(), tab.begin(), tab.end());
	return copy_ptr(tab);
}

template<class EncodingT>
boost::shared_ptr< _CppFile<EncodingT> >
_CppFileAccess<EncodingT>::selectOneCppFile(boost::shared_ptr< _TextFile<EncodingT> > textFile, bool nowait, bool addition)  
{
	if ( textFile == NULL || typename _TextFile<EncodingT>::TextFileIDEquality(-1)(textFile) ) {
		m_logger->errorStream() << "TextFile : Identifier is null.";
		throw UnIdentifiedObjectException("TextFile : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _CppFile<EncodingT> > > result = selectManyCppFiles(C("idText = ") /*+ C("\'") */+ C(ToString::parse(textFile->getRowid()))/* + C("\'")*/, nowait, addition);
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
	if ( o->getTextFile() == NULL || typename _TextFile<EncodingT>::TextFileIDEquality(-1)(o->getTextFile()) ) {
		m_logger->errorStream() << "TextFile : Identifier is null.";
		throw UnIdentifiedObjectException("TextFile : Identifier is null.");
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
	_TextFileAccess<EncodingT>* textFileAccess = _TextFileAccess<EncodingT>::getInstance();
	if (!textFileAccess) {
		m_logger->errorStream() << "TextFileAccess class is not initialized.";
		throw NullPointerException("TextFileAccess class is not initialized.");
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
	_CppIncludeAccess<EncodingT>* cppIncludeAccess = _CppIncludeAccess<EncodingT>::getInstance();
	if (!cppIncludeAccess) {
		m_logger->errorStream() << "CppIncludeAccess class is not initialized.";
		throw NullPointerException("CppIncludeAccess class is not initialized.");
	}
	_CppClassAccess<EncodingT>* cppClassAccess = _CppClassAccess<EncodingT>::getInstance();
	if (!cppClassAccess) {
		m_logger->errorStream() << "CppClassAccess class is not initialized.";
		throw NullPointerException("CppClassAccess class is not initialized.");
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
	_DebugFileInfoAccess<EncodingT>* debugFileInfoAccess = _DebugFileInfoAccess<EncodingT>::getInstance();
	if (!debugFileInfoAccess) {
		m_logger->errorStream() << "DebugFileInfoAccess class is not initialized.";
		throw NullPointerException("DebugFileInfoAccess class is not initialized.");
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
		cppIncludeAccess->cancelSelection();
		cppClassAccess->cancelSelection();
		cppEnumAccess->cancelSelection();
		cMacroAccess->cancelSelection();
		debugFileInfoAccess->cancelSelection();
		textFileAccess->cancelSelection();
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
	if ( o->getTextFile() == NULL || typename _TextFile<EncodingT>::TextFileIDEquality(-1)(o->getTextFile()) ) {
		m_logger->errorStream() << "TextFile : Identifier is null.";
		throw UnIdentifiedObjectException("TextFile : Identifier is null.");
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
	int id;
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,C("idType")), std::vector<typename EncodingT::string_t>(1,C("cppFile")), C("idText = ") /*+ C("\'") */+ C(ToString::parse(o->getTextFile()->getRowid()))/* + C("\'")*/) );
	if( statement.executeStep() && statement.getInt( 0, id ) && id != 0 ) {
		typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(o->getTextFile());
		boost::shared_ptr< _CppFileType<EncodingT> > val = cppFileTypeAccess->getOneCppFileType(id);
		typename std::vector< boost::shared_ptr<_CppFile<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFileIdEquality);
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
_CppFileAccess<EncodingT>::fillOneCppDeclarationFunction(boost::shared_ptr< _CppFile<EncodingT> > o, int identifier, bool nowait)  
{
	fillManyCppDeclarationFunctions(o, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillManyCppDeclarationFunctions(boost::shared_ptr< _CppFile<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getTextFile() == NULL || typename _TextFile<EncodingT>::TextFileIDEquality(-1)(o->getTextFile()) ) {
		m_logger->errorStream() << "TextFile : Identifier is null.";
		throw UnIdentifiedObjectException("TextFile : Identifier is null.");
	}
	_CppFunctionAccess<EncodingT>* cppDeclarationFunctionAccess = _CppFunctionAccess<EncodingT>::getInstance();
	if (!cppDeclarationFunctionAccess) {
		m_logger->errorStream() << "CppFunctionAccess class is not initialized.";
		throw NullPointerException("CppFunctionAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _CppFunction<EncodingT> > > tab;
	typename EncodingT::string_t cppFunctionFilter = C("idDecFile = ") + C(ToString::parse(o->getTextFile()->getRowid()));
	if (!filter.empty()) {
		cppFunctionFilter += C(" AND ") + filter;
	}
	typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(o->getTextFile());
	typename std::vector< boost::shared_ptr< _CppFile<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFileIdEquality);
	if (save != m_backup.end())
	{
		tab = cppDeclarationFunctionAccess->selectManyCppFunctions(cppFunctionFilter, nowait);
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
_CppFileAccess<EncodingT>::fillOneCppDefinitionFunction(boost::shared_ptr< _CppFile<EncodingT> > o, int identifier, bool nowait)  
{
	fillManyCppDefinitionFunctions(o, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillManyCppDefinitionFunctions(boost::shared_ptr< _CppFile<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getTextFile() == NULL || typename _TextFile<EncodingT>::TextFileIDEquality(-1)(o->getTextFile()) ) {
		m_logger->errorStream() << "TextFile : Identifier is null.";
		throw UnIdentifiedObjectException("TextFile : Identifier is null.");
	}
	_CppFunctionAccess<EncodingT>* cppDefinitionFunctionAccess = _CppFunctionAccess<EncodingT>::getInstance();
	if (!cppDefinitionFunctionAccess) {
		m_logger->errorStream() << "CppFunctionAccess class is not initialized.";
		throw NullPointerException("CppFunctionAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _CppFunction<EncodingT> > > tab;
	typename EncodingT::string_t cppFunctionFilter = C("idDefFile = ") + C(ToString::parse(o->getTextFile()->getRowid()));
	if (!filter.empty()) {
		cppFunctionFilter += C(" AND ") + filter;
	}
	typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(o->getTextFile());
	typename std::vector< boost::shared_ptr< _CppFile<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFileIdEquality);
	if (save != m_backup.end())
	{
		tab = cppDefinitionFunctionAccess->selectManyCppFunctions(cppFunctionFilter, nowait);
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
_CppFileAccess<EncodingT>::fillAllCppIncludes(boost::shared_ptr< _CppFile<EncodingT> > o, bool nowait)  
{
	fillManyCppIncludes(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillOneCppInclude(boost::shared_ptr< _CppFile<EncodingT> > o, int identifier, bool nowait)  
{
	fillManyCppIncludes(o, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillManyCppIncludes(boost::shared_ptr< _CppFile<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getTextFile() == NULL || typename _TextFile<EncodingT>::TextFileIDEquality(-1)(o->getTextFile()) ) {
		m_logger->errorStream() << "TextFile : Identifier is null.";
		throw UnIdentifiedObjectException("TextFile : Identifier is null.");
	}
	_CppIncludeAccess<EncodingT>* cppIncludeAccess = _CppIncludeAccess<EncodingT>::getInstance();
	if (!cppIncludeAccess) {
		m_logger->errorStream() << "CppIncludeAccess class is not initialized.";
		throw NullPointerException("CppIncludeAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _CppInclude<EncodingT> > > tab;
	typename EncodingT::string_t cppIncludeFilter = C("idFile = ") + C(ToString::parse(o->getTextFile()->getRowid()));
	if (!filter.empty()) {
		cppIncludeFilter += C(" AND ") + filter;
	}
	typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(o->getTextFile());
	typename std::vector< boost::shared_ptr< _CppFile<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFileIdEquality);
	if (save != m_backup.end())
	{
		tab = cppIncludeAccess->selectManyCppIncludes(cppIncludeFilter, nowait);
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
_CppFileAccess<EncodingT>::fillAllCppClasss(boost::shared_ptr< _CppFile<EncodingT> > o, bool nowait)  
{
	fillManyCppClasss(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillOneCppClass(boost::shared_ptr< _CppFile<EncodingT> > o, int identifier, bool nowait)  
{
	fillManyCppClasss(o, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillManyCppClasss(boost::shared_ptr< _CppFile<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getTextFile() == NULL || typename _TextFile<EncodingT>::TextFileIDEquality(-1)(o->getTextFile()) ) {
		m_logger->errorStream() << "TextFile : Identifier is null.";
		throw UnIdentifiedObjectException("TextFile : Identifier is null.");
	}
	_CppClassAccess<EncodingT>* cppClassAccess = _CppClassAccess<EncodingT>::getInstance();
	if (!cppClassAccess) {
		m_logger->errorStream() << "CppClassAccess class is not initialized.";
		throw NullPointerException("CppClassAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _CppClass<EncodingT> > > tab;
	typename EncodingT::string_t cppClassFilter = C("idFile = ") + C(ToString::parse(o->getTextFile()->getRowid()));
	if (!filter.empty()) {
		cppClassFilter += C(" AND ") + filter;
	}
	typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(o->getTextFile());
	typename std::vector< boost::shared_ptr< _CppFile<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFileIdEquality);
	if (save != m_backup.end())
	{
		tab = cppClassAccess->selectManyCppClasss(cppClassFilter, nowait);
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
_CppFileAccess<EncodingT>::fillAllCppEnums(boost::shared_ptr< _CppFile<EncodingT> > o, bool nowait)  
{
	fillManyCppEnums(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillOneCppEnum(boost::shared_ptr< _CppFile<EncodingT> > o, int identifier, bool nowait)  
{
	fillManyCppEnums(o, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillManyCppEnums(boost::shared_ptr< _CppFile<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getTextFile() == NULL || typename _TextFile<EncodingT>::TextFileIDEquality(-1)(o->getTextFile()) ) {
		m_logger->errorStream() << "TextFile : Identifier is null.";
		throw UnIdentifiedObjectException("TextFile : Identifier is null.");
	}
	_CppEnumAccess<EncodingT>* cppEnumAccess = _CppEnumAccess<EncodingT>::getInstance();
	if (!cppEnumAccess) {
		m_logger->errorStream() << "CppEnumAccess class is not initialized.";
		throw NullPointerException("CppEnumAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _CppEnum<EncodingT> > > tab;
	typename EncodingT::string_t cppEnumFilter = C("idFile = ") + C(ToString::parse(o->getTextFile()->getRowid()));
	if (!filter.empty()) {
		cppEnumFilter += C(" AND ") + filter;
	}
	typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(o->getTextFile());
	typename std::vector< boost::shared_ptr< _CppFile<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFileIdEquality);
	if (save != m_backup.end())
	{
		tab = cppEnumAccess->selectManyCppEnums(cppEnumFilter, nowait);
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
_CppFileAccess<EncodingT>::fillOneCMacro(boost::shared_ptr< _CppFile<EncodingT> > o, int identifier, bool nowait)  
{
	fillManyCMacros(o, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillManyCMacros(boost::shared_ptr< _CppFile<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getTextFile() == NULL || typename _TextFile<EncodingT>::TextFileIDEquality(-1)(o->getTextFile()) ) {
		m_logger->errorStream() << "TextFile : Identifier is null.";
		throw UnIdentifiedObjectException("TextFile : Identifier is null.");
	}
	_CMacroAccess<EncodingT>* cMacroAccess = _CMacroAccess<EncodingT>::getInstance();
	if (!cMacroAccess) {
		m_logger->errorStream() << "CMacroAccess class is not initialized.";
		throw NullPointerException("CMacroAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _CMacro<EncodingT> > > tab;
	typename EncodingT::string_t cMacroFilter = C("idFile = ") + C(ToString::parse(o->getTextFile()->getRowid()));
	if (!filter.empty()) {
		cMacroFilter += C(" AND ") + filter;
	}
	typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(o->getTextFile());
	typename std::vector< boost::shared_ptr< _CppFile<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFileIdEquality);
	if (save != m_backup.end())
	{
		tab = cMacroAccess->selectManyCMacros(cMacroFilter, nowait);
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
_CppFileAccess<EncodingT>::fillAllDebugFileInfos(boost::shared_ptr< _CppFile<EncodingT> > o, bool nowait)  
{
	fillManyDebugFileInfos(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillOneDebugFileInfo(boost::shared_ptr< _CppFile<EncodingT> > o, int identifier, bool nowait)  
{
	fillManyDebugFileInfos(o, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait);
}

template<class EncodingT>
void
_CppFileAccess<EncodingT>::fillManyDebugFileInfos(boost::shared_ptr< _CppFile<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getTextFile() == NULL || typename _TextFile<EncodingT>::TextFileIDEquality(-1)(o->getTextFile()) ) {
		m_logger->errorStream() << "TextFile : Identifier is null.";
		throw UnIdentifiedObjectException("TextFile : Identifier is null.");
	}
	_DebugFileInfoAccess<EncodingT>* debugFileInfoAccess = _DebugFileInfoAccess<EncodingT>::getInstance();
	if (!debugFileInfoAccess) {
		m_logger->errorStream() << "DebugFileInfoAccess class is not initialized.";
		throw NullPointerException("DebugFileInfoAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _DebugFileInfo<EncodingT> > > tab;
	typename EncodingT::string_t debugFileInfoFilter = C("idFile = ") + C(ToString::parse(o->getTextFile()->getRowid()));
	if (!filter.empty()) {
		debugFileInfoFilter += C(" AND ") + filter;
	}
	typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(o->getTextFile());
	typename std::vector< boost::shared_ptr< _CppFile<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFileIdEquality);
	if (save != m_backup.end())
	{
		tab = debugFileInfoAccess->selectManyDebugFileInfos(debugFileInfoFilter, nowait);
		(*save)->clearDebugFileInfos();
		(*save)->insertDebugFileInfo((*save)->getDebugFileInfosEnd(), tab.begin(), tab.end());
	}
	else
	{
		tab = debugFileInfoAccess->getManyDebugFileInfos(debugFileInfoFilter);
	}
	o->clearDebugFileInfos();
	o->insertDebugFileInfo(o->getDebugFileInfosEnd(), tab.begin(), tab.end());
}

template<class EncodingT>
bool
_CppFileAccess<EncodingT>::isModifiedCppFile(boost::shared_ptr< _CppFile<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getTextFile() == NULL || typename _TextFile<EncodingT>::TextFileIDEquality(-1)(o->getTextFile()) ) {
		m_logger->errorStream() << "TextFile : Identifier is null.";
		throw UnIdentifiedObjectException("TextFile : Identifier is null.");
	}
	_TextFileAccess<EncodingT>* textFileAccess = _TextFileAccess<EncodingT>::getInstance();
	if (!textFileAccess) {
		m_logger->errorStream() << "TextFileAccess class is not initialized.";
		throw NullPointerException("TextFileAccess class is not initialized.");
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
	_CppIncludeAccess<EncodingT>* cppIncludeAccess = _CppIncludeAccess<EncodingT>::getInstance();
	if (!cppIncludeAccess) {
		m_logger->errorStream() << "CppIncludeAccess class is not initialized.";
		throw NullPointerException("CppIncludeAccess class is not initialized.");
	}
	_CppClassAccess<EncodingT>* cppClassAccess = _CppClassAccess<EncodingT>::getInstance();
	if (!cppClassAccess) {
		m_logger->errorStream() << "CppClassAccess class is not initialized.";
		throw NullPointerException("CppClassAccess class is not initialized.");
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
	_DebugFileInfoAccess<EncodingT>* debugFileInfoAccess = _DebugFileInfoAccess<EncodingT>::getInstance();
	if (!debugFileInfoAccess) {
		m_logger->errorStream() << "DebugFileInfoAccess class is not initialized.";
		throw NullPointerException("DebugFileInfoAccess class is not initialized.");
	}
	typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(*o);
	typename std::vector< boost::shared_ptr< _CppFile<EncodingT> > >::const_iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFileIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getPath() != o->getPath());
	bUpdate = bUpdate || ((*save)->getName() != o->getName());
	bUpdate = bUpdate || ((*save)->getLinesCount() != o->getLinesCount());
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
	typename _CppFile<EncodingT>::DebugFileInfoIterator debugFileInfo;
	for ( debugFileInfo=o->getDebugFileInfosBeginning(); debugFileInfo!=o->getDebugFileInfosEnd(); ++debugFileInfo ) {
		if (!(*debugFileInfo)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _DebugFileInfo<EncodingT>::DebugFileInfoIDEquality debugFileInfoIdEquality(*(*debugFileInfo));
		bUpdate = bUpdate || (std::find_if((*save)->getDebugFileInfosBeginning(), (*save)->getDebugFileInfosEnd(), debugFileInfoIdEquality) == (*save)->getDebugFileInfosEnd())
			|| (debugFileInfoAccess->isModifiedDebugFileInfo(*debugFileInfo));
	}
	for ( debugFileInfo=(*save)->getDebugFileInfosBeginning(); debugFileInfo<(*save)->getDebugFileInfosEnd(); ++debugFileInfo ) {
		if (!(*debugFileInfo)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _DebugFileInfo<EncodingT>::DebugFileInfoIDEquality debugFileInfoIdEquality(*(*debugFileInfo));
		bUpdate = bUpdate || (std::find_if(o->getDebugFileInfosBeginning(), o->getDebugFileInfosEnd(), debugFileInfoIdEquality) == o->getDebugFileInfosEnd());
	}
	bUpdate = bUpdate || textFileAccess->isModifiedTextFile(o->getTextFile());
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
	if ( o->getTextFile() == NULL || typename _TextFile<EncodingT>::TextFileIDEquality(-1)(o->getTextFile()) ) {
		m_logger->errorStream() << "TextFile : Identifier is null.";
		throw UnIdentifiedObjectException("TextFile : Identifier is null.");
	}
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
	_CppIncludeAccess<EncodingT>* cppIncludeAccess = _CppIncludeAccess<EncodingT>::getInstance();
	if (!cppIncludeAccess) {
		m_logger->errorStream() << "CppIncludeAccess class is not initialized.";
		throw NullPointerException("CppIncludeAccess class is not initialized.");
	}
	_CppClassAccess<EncodingT>* cppClassAccess = _CppClassAccess<EncodingT>::getInstance();
	if (!cppClassAccess) {
		m_logger->errorStream() << "CppClassAccess class is not initialized.";
		throw NullPointerException("CppClassAccess class is not initialized.");
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
	_DebugFileInfoAccess<EncodingT>* debugFileInfoAccess = _DebugFileInfoAccess<EncodingT>::getInstance();
	if (!debugFileInfoAccess) {
		m_logger->errorStream() << "DebugFileInfoAccess class is not initialized.";
		throw NullPointerException("DebugFileInfoAccess class is not initialized.");
	}
	typename _CppFile<EncodingT>::CppFileIDEquality cppFileIdEquality(*o);
	typename std::vector< boost::shared_ptr< _CppFile<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFileIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	try {
		if ( (*save)->getPath() != o->getPath() ) {
			values.addText( o->getPath() );
			fields.push_back( C("path") );
		}
		if ( (*save)->getName() != o->getName() ) {
			values.addText( o->getName() );
			fields.push_back( C("name") );
		}
		if ( (*save)->getLinesCount() != o->getLinesCount() ) {
			values.addInt( o->getLinesCount() );
			fields.push_back( C("linesCount") );
		}
		if ( !o->isNullCppFileType() && typename _CppFileType<EncodingT>::CppFileTypeIDEquality(-1)(o->getCppFileType()) ) {
			m_logger->errorStream() << "idType : Identifier is null.";
			throw InvalidQueryException("idType : Identifier is null.");
		}
		else if ( !o->isNullCppFileType() && !typename _CppFileType<EncodingT>::CppFileTypeIDEquality(*(o->getCppFileType()))((*save)->getCppFileType()) ) {
			values.addInt( o->getCppFileType()->getIdentifier() );
			fields.push_back( C("idType") );
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
		std::vector< boost::shared_ptr< _DebugFileInfo<EncodingT> > > listOfDebugFileInfoToAdd;
		std::vector< boost::shared_ptr< _DebugFileInfo<EncodingT> > > listOfDebugFileInfoToUpdate;
		typename _CppFile<EncodingT>::DebugFileInfoIterator debugFileInfo;
		for ( debugFileInfo=o->getDebugFileInfosBeginning(); debugFileInfo!=o->getDebugFileInfosEnd(); ++debugFileInfo ) {
			if (!(*debugFileInfo)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*debugFileInfo)->setCppFile(o);
			typename _DebugFileInfo<EncodingT>::DebugFileInfoIDEquality debugFileInfoIdEquality(*(*debugFileInfo));
			if ( std::find_if((*save)->getDebugFileInfosBeginning(), (*save)->getDebugFileInfosEnd(), debugFileInfoIdEquality) == (*save)->getDebugFileInfosEnd()) {
				listOfDebugFileInfoToAdd.push_back(*debugFileInfo);
			}
			else {
				if (debugFileInfoAccess->isModifiedDebugFileInfo(*debugFileInfo))
					listOfDebugFileInfoToUpdate.push_back(*debugFileInfo);
			}
		}
		std::vector< boost::shared_ptr< _DebugFileInfo<EncodingT> > > listOfDebugFileInfoToRemove;
		for ( debugFileInfo=(*save)->getDebugFileInfosBeginning(); debugFileInfo<(*save)->getDebugFileInfosEnd(); ++debugFileInfo ) {
			if (!(*debugFileInfo)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			typename _DebugFileInfo<EncodingT>::DebugFileInfoIDEquality debugFileInfoIdEquality(*(*debugFileInfo));
			if ( std::find_if(o->getDebugFileInfosBeginning(), o->getDebugFileInfosEnd(), debugFileInfoIdEquality) == o->getDebugFileInfosEnd()) {
				listOfDebugFileInfoToRemove.push_back(*debugFileInfo);
			}
		}
		if (!fields.empty()) {
			statement.swap( connection->update(C("cppFile"), fields, C("idText = ") /*+ C("\'") */+ C(ToString::parse(o->getTextFile()->getRowid()))/* + C("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, C("cppFile"), o);
		}
		for ( cppDeclarationFunction=listOfCppDeclarationFunctionToAdd.begin(); cppDeclarationFunction!=listOfCppDeclarationFunctionToAdd.end() ; ++cppDeclarationFunction ) {
			cppDeclarationFunctionAccess->insertCppFunction(*cppDeclarationFunction);
		}
		for ( cppDeclarationFunction=listOfCppDeclarationFunctionToUpdate.begin(); cppDeclarationFunction!=listOfCppDeclarationFunctionToUpdate.end() ; ++cppDeclarationFunction ) {
			cppDeclarationFunctionAccess->updateCppFunction(*cppDeclarationFunction);
		}
		for ( cppDeclarationFunction=listOfCppDeclarationFunctionToRemove.begin(); cppDeclarationFunction!=listOfCppDeclarationFunctionToRemove.end() ; ++cppDeclarationFunction ) {
			cppDeclarationFunctionAccess->deleteCppFunction(*cppDeclarationFunction);
		}
		for ( cppDefinitionFunction=listOfCppDefinitionFunctionToAdd.begin(); cppDefinitionFunction!=listOfCppDefinitionFunctionToAdd.end() ; ++cppDefinitionFunction ) {
			cppDefinitionFunctionAccess->insertCppFunction(*cppDefinitionFunction);
		}
		for ( cppDefinitionFunction=listOfCppDefinitionFunctionToUpdate.begin(); cppDefinitionFunction!=listOfCppDefinitionFunctionToUpdate.end() ; ++cppDefinitionFunction ) {
			cppDefinitionFunctionAccess->updateCppFunction(*cppDefinitionFunction);
		}
		for ( cppDefinitionFunction=listOfCppDefinitionFunctionToRemove.begin(); cppDefinitionFunction!=listOfCppDefinitionFunctionToRemove.end() ; ++cppDefinitionFunction ) {
			cppDefinitionFunctionAccess->deleteCppFunction(*cppDefinitionFunction);
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
		for ( cppClass=listOfCppClassToAdd.begin(); cppClass!=listOfCppClassToAdd.end() ; ++cppClass ) {
			cppClassAccess->insertCppClass(*cppClass);
		}
		for ( cppClass=listOfCppClassToUpdate.begin(); cppClass!=listOfCppClassToUpdate.end() ; ++cppClass ) {
			cppClassAccess->updateCppClass(*cppClass);
		}
		for ( cppClass=listOfCppClassToRemove.begin(); cppClass!=listOfCppClassToRemove.end() ; ++cppClass ) {
			cppClassAccess->deleteCppClass(*cppClass);
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
		for ( debugFileInfo=listOfDebugFileInfoToAdd.begin(); debugFileInfo!=listOfDebugFileInfoToAdd.end() ; ++debugFileInfo ) {
			debugFileInfoAccess->insertDebugFileInfo(*debugFileInfo);
		}
		for ( debugFileInfo=listOfDebugFileInfoToUpdate.begin(); debugFileInfo!=listOfDebugFileInfoToUpdate.end() ; ++debugFileInfo ) {
			debugFileInfoAccess->updateDebugFileInfo(*debugFileInfo);
		}
		for ( debugFileInfo=listOfDebugFileInfoToRemove.begin(); debugFileInfo!=listOfDebugFileInfoToRemove.end() ; ++debugFileInfo ) {
			debugFileInfoAccess->deleteDebugFileInfo(*debugFileInfo);
		}
		if (textFileAccess->isModifiedTextFile(o->getTextFile())) {
			textFileAccess->updateTextFile(o->getTextFile());
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
	_TextFileAccess<EncodingT>* textFileAccess = _TextFileAccess<EncodingT>::getInstance();
	if (!textFileAccess) {
		m_logger->errorStream() << "TextFileAccess class is not initialized.";
		throw NullPointerException("TextFileAccess class is not initialized.");
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
	_CppIncludeAccess<EncodingT>* cppIncludeAccess = _CppIncludeAccess<EncodingT>::getInstance();
	if (!cppIncludeAccess) {
		m_logger->errorStream() << "CppIncludeAccess class is not initialized.";
		throw NullPointerException("CppIncludeAccess class is not initialized.");
	}
	_CppClassAccess<EncodingT>* cppClassAccess = _CppClassAccess<EncodingT>::getInstance();
	if (!cppClassAccess) {
		m_logger->errorStream() << "CppClassAccess class is not initialized.";
		throw NullPointerException("CppClassAccess class is not initialized.");
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
	_DebugFileInfoAccess<EncodingT>* debugFileInfoAccess = _DebugFileInfoAccess<EncodingT>::getInstance();
	if (!debugFileInfoAccess) {
		m_logger->errorStream() << "DebugFileInfoAccess class is not initialized.";
		throw NullPointerException("DebugFileInfoAccess class is not initialized.");
	}
	try {
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
		if ( !o->isNullTextFile() && typename _TextFile<EncodingT>::TextFileIDEquality(-1)(o->getTextFile())) {
			textFileAccess->insertTextFile(o->getTextFile());
		}
		if ( !o->isNullTextFile() ) {
			values.addInt( o->getTextFile()->getRowid() );
			fields.push_back( C("idText") );
		}
		else {
			m_logger->errorStream() << "idText : null reference is forbidden.";
			throw InvalidQueryException("idText : null reference is forbidden.");
		}
		values.addText( o->getPath() );
		fields.push_back( C("path") );
		values.addText( o->getName() );
		fields.push_back( C("name") );
		if ( !o->isNullCppFileType() && typename _CppFileType<EncodingT>::CppFileTypeIDEquality(-1)(o->getCppFileType()) ) {
			m_logger->errorStream() << "idType : Identifier is null.";
			throw InvalidQueryException("idType : Identifier is null.");
		}
		else if ( !o->isNullCppFileType() ) {
			values.addInt( o->getCppFileType()->getIdentifier() );
			fields.push_back( C("idType") );
		}
		else {
			m_logger->errorStream() << "idType : null reference is forbidden.";
			throw InvalidQueryException("idType : null reference is forbidden.");
		}
		values.addInt( o->getLinesCount() );
		fields.push_back( C("linesCount") );
		statement.swap( connection->insert(C("cppFile"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_insertSignal(OPERATION_ACCESS_INSERT, C("cppFile"), o);
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
		typename _CppFile<EncodingT>::CppIncludeIterator cppInclude;
		for ( cppInclude=o->getCppIncludesBeginning(); cppInclude!=o->getCppIncludesEnd(); ++cppInclude ) {
			(*cppInclude)->setCppFile(o);
			cppIncludeAccess->insertCppInclude(*cppInclude);
		}
		typename _CppFile<EncodingT>::CppClassIterator cppClass;
		for ( cppClass=o->getCppClasssBeginning(); cppClass!=o->getCppClasssEnd(); ++cppClass ) {
			(*cppClass)->setCppFile(o);
			cppClassAccess->insertCppClass(*cppClass);
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
		typename _CppFile<EncodingT>::DebugFileInfoIterator debugFileInfo;
		for ( debugFileInfo=o->getDebugFileInfosBeginning(); debugFileInfo!=o->getDebugFileInfosEnd(); ++debugFileInfo ) {
			(*debugFileInfo)->setCppFile(o);
			debugFileInfoAccess->insertDebugFileInfo(*debugFileInfo);
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
_CppFileAccess<EncodingT>::deleteCppFile(boost::shared_ptr< _CppFile<EncodingT> > o, bool deleteid)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	_DataStatement<EncodingT> statement;
	if ( o->getTextFile() == NULL || typename _TextFile<EncodingT>::TextFileIDEquality(-1)(o->getTextFile()) ) {
		m_logger->errorStream() << "TextFile : Identifier is null.";
		throw UnIdentifiedObjectException("TextFile : Identifier is null.");
	}
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
	_CppIncludeAccess<EncodingT>* cppIncludeAccess = _CppIncludeAccess<EncodingT>::getInstance();
	if (!cppIncludeAccess) {
		m_logger->errorStream() << "CppIncludeAccess class is not initialized.";
		throw NullPointerException("CppIncludeAccess class is not initialized.");
	}
	_CppClassAccess<EncodingT>* cppClassAccess = _CppClassAccess<EncodingT>::getInstance();
	if (!cppClassAccess) {
		m_logger->errorStream() << "CppClassAccess class is not initialized.";
		throw NullPointerException("CppClassAccess class is not initialized.");
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
	_DebugFileInfoAccess<EncodingT>* debugFileInfoAccess = _DebugFileInfoAccess<EncodingT>::getInstance();
	if (!debugFileInfoAccess) {
		m_logger->errorStream() << "DebugFileInfoAccess class is not initialized.";
		throw NullPointerException("DebugFileInfoAccess class is not initialized.");
	}
	typename _CppFile<EncodingT>::CppFileIDEquality CppFileIdEquality(*o);
	typename std::vector< boost::shared_ptr< _CppFile<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), CppFileIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before deletion.";
		throw UnSelectedObjectException("You must select object before deletion.");
	}
	try {
		typename _CppFile<EncodingT>::CppDeclarationFunctionIterator cppDeclarationFunction;
		fillAllCppDeclarationFunctions(o);
		for ( cppDeclarationFunction=o->getCppDeclarationFunctionsBeginning(); cppDeclarationFunction!=o->getCppDeclarationFunctionsEnd(); ++cppDeclarationFunction ) {
			cppDeclarationFunctionAccess->deleteCppFunction(*cppDeclarationFunction);
		}
		typename _CppFile<EncodingT>::CppDefinitionFunctionIterator cppDefinitionFunction;
		fillAllCppDefinitionFunctions(o);
		for ( cppDefinitionFunction=o->getCppDefinitionFunctionsBeginning(); cppDefinitionFunction!=o->getCppDefinitionFunctionsEnd(); ++cppDefinitionFunction ) {
			cppDefinitionFunctionAccess->deleteCppFunction(*cppDefinitionFunction);
		}
		typename _CppFile<EncodingT>::CppIncludeIterator cppInclude;
		fillAllCppIncludes(o);
		for ( cppInclude=o->getCppIncludesBeginning(); cppInclude!=o->getCppIncludesEnd(); ++cppInclude ) {
			cppIncludeAccess->deleteCppInclude(*cppInclude);
		}
		typename _CppFile<EncodingT>::CppClassIterator cppClass;
		fillAllCppClasss(o);
		for ( cppClass=o->getCppClasssBeginning(); cppClass!=o->getCppClasssEnd(); ++cppClass ) {
			cppClassAccess->deleteCppClass(*cppClass);
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
		typename _CppFile<EncodingT>::DebugFileInfoIterator debugFileInfo;
		fillAllDebugFileInfos(o);
		for ( debugFileInfo=o->getDebugFileInfosBeginning(); debugFileInfo!=o->getDebugFileInfosEnd(); ++debugFileInfo ) {
			debugFileInfoAccess->deleteDebugFileInfo(*debugFileInfo);
		}
		statement.swap( connection->deleteFrom(C("cppFile"), C("idText = ") /*+ C("\'") */+ C(ToString::parse(o->getTextFile()->getRowid()))/* + C("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, C("cppFile"), o);
		if (deleteid) {
			textFileAccess->deleteTextFile(o->getTextFile());
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

