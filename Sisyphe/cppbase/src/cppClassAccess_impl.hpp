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
	columns.push_back(C("isStruct"));
	columns.push_back(C("isInterface"));
	columns.push_back(C("isAbstract"));
	columns.push_back(C("linesCount"));
	columns.push_back(C("lineNumber"));
	columns.push_back(C("startBlock"));
	columns.push_back(C("lengthBlock"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,C("cppClass")), filter) );
	while( statement.executeStep() ) {
		int identifier;
		typename EncodingT::string_t name;
		int isStruct;
		int isInterface;
		int isAbstract;
		int linesCount;
		int lineNumber;
		int startBlock;
		int lengthBlock;
		if (statement.getInt( 0, identifier ) &&
			statement.getText( 1, name ) &&
			statement.getInt( 2, isStruct ) &&
			statement.getInt( 3, isInterface ) &&
			statement.getInt( 4, isAbstract ) &&
			statement.getInt( 5, linesCount ) &&
			statement.getInt( 6, lineNumber ) &&
			statement.getInt( 7, startBlock ) &&
			statement.getInt( 8, lengthBlock )) {
			value.reset(new _CppClass<EncodingT>(
				identifier,
				name,
				isStruct,
				isInterface,
				isAbstract,
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
_CppClassAccess<EncodingT>::getOneCppClass(int identifier) const 
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
	columns.push_back(C("isStruct"));
	columns.push_back(C("isInterface"));
	columns.push_back(C("isAbstract"));
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
		int identifier;
		typename EncodingT::string_t name;
		int isStruct;
		int isInterface;
		int isAbstract;
		int linesCount;
		int lineNumber;
		int startBlock;
		int lengthBlock;
		if (statement.getInt( 0, identifier ) &&
			statement.getText( 1, name ) &&
			statement.getInt( 2, isStruct ) &&
			statement.getInt( 3, isInterface ) &&
			statement.getInt( 4, isAbstract ) &&
			statement.getInt( 5, linesCount ) &&
			statement.getInt( 6, lineNumber ) &&
			statement.getInt( 7, startBlock ) &&
			statement.getInt( 8, lengthBlock )) {
			tab.push_back(boost::shared_ptr< _CppClass<EncodingT> >(new _CppClass<EncodingT>(
				identifier,
				name,
				isStruct,
				isInterface,
				isAbstract,
				linesCount,
				lineNumber,
				startBlock,
				lengthBlock)));
		}
	}
	m_backup.insert(m_backup.end(), tab.begin(), tab.end());
	return copy_ptr(tab);
}

template<class EncodingT>
boost::shared_ptr< _CppClass<EncodingT> >
_CppClassAccess<EncodingT>::selectOneCppClass(int identifier, bool nowait, bool addition)  
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
	_CppAttributeAccess<EncodingT>* cppAttributeAccess = _CppAttributeAccess<EncodingT>::getInstance();
	if (!cppAttributeAccess) {
		m_logger->errorStream() << "CppAttributeAccess class is not initialized.";
		throw NullPointerException("CppAttributeAccess class is not initialized.");
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
		cppAttributeAccess->cancelSelection();
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
	_TextFileAccess<EncodingT>* textFileAccess = _TextFileAccess<EncodingT>::getInstance();
	if (!textFileAccess) {
		m_logger->errorStream() << "TextFileAccess class is not initialized.";
		throw NullPointerException("TextFileAccess class is not initialized.");
	}
	int id;
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,C("idFile")), std::vector<typename EncodingT::string_t>(1,C("cppClass")), C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
	if( statement.executeStep() && statement.getInt( 0, id ) && id != 0 ) {
		typename _CppClass<EncodingT>::CppClassIDEquality cppClassIdEquality(o->getIdentifier());
		boost::shared_ptr< _CppFile<EncodingT> > val = cppFileAccess->getOneCppFile(textFileAccess->getOneTextFile(id));
		typename std::vector< boost::shared_ptr<_CppClass<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppClassIdEquality);
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
_CppClassAccess<EncodingT>::fillOneCppInheritance(boost::shared_ptr< _CppClass<EncodingT> > o, int identifier, bool nowait)  
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
	typename std::vector< boost::shared_ptr< _CppClass<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppClassIdEquality);
	if (save != m_backup.end())
	{
		tab = cppInheritanceAccess->selectManyCppInheritances(cppInheritanceFilter, nowait);
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
_CppClassAccess<EncodingT>::fillOneCppFunction(boost::shared_ptr< _CppClass<EncodingT> > o, int identifier, bool nowait)  
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
	typename std::vector< boost::shared_ptr< _CppClass<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppClassIdEquality);
	if (save != m_backup.end())
	{
		tab = cppFunctionAccess->selectManyCppFunctions(cppFunctionFilter, nowait);
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
_CppClassAccess<EncodingT>::fillAllCppAttributes(boost::shared_ptr< _CppClass<EncodingT> > o, bool nowait)  
{
	fillManyCppAttributes(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_CppClassAccess<EncodingT>::fillOneCppAttribute(boost::shared_ptr< _CppClass<EncodingT> > o, int identifier, bool nowait)  
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
	typename std::vector< boost::shared_ptr< _CppClass<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppClassIdEquality);
	if (save != m_backup.end())
	{
		tab = cppAttributeAccess->selectManyCppAttributes(cppAttributeFilter, nowait);
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
	_CppAttributeAccess<EncodingT>* cppAttributeAccess = _CppAttributeAccess<EncodingT>::getInstance();
	if (!cppAttributeAccess) {
		m_logger->errorStream() << "CppAttributeAccess class is not initialized.";
		throw NullPointerException("CppAttributeAccess class is not initialized.");
	}
	typename _CppClass<EncodingT>::CppClassIDEquality cppClassIdEquality(*o);
	typename std::vector< boost::shared_ptr< _CppClass<EncodingT> > >::const_iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppClassIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getName() != o->getName());
	bUpdate = bUpdate || ((*save)->getIsStruct() != o->getIsStruct());
	bUpdate = bUpdate || ((*save)->getIsInterface() != o->getIsInterface());
	bUpdate = bUpdate || ((*save)->getIsAbstract() != o->getIsAbstract());
	bUpdate = bUpdate || ((*save)->getLinesCount() != o->getLinesCount());
	bUpdate = bUpdate || ((*save)->getLineNumber() != o->getLineNumber());
	bUpdate = bUpdate || ((*save)->getStartBlock() != o->getStartBlock());
	bUpdate = bUpdate || ((*save)->getLengthBlock() != o->getLengthBlock());
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
	_CppAttributeAccess<EncodingT>* cppAttributeAccess = _CppAttributeAccess<EncodingT>::getInstance();
	if (!cppAttributeAccess) {
		m_logger->errorStream() << "CppAttributeAccess class is not initialized.";
		throw NullPointerException("CppAttributeAccess class is not initialized.");
	}
	typename _CppClass<EncodingT>::CppClassIDEquality cppClassIdEquality(*o);
	typename std::vector< boost::shared_ptr< _CppClass<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppClassIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	try {
		if ( (*save)->getName() != o->getName() ) {
			values.addText( o->getName() );
			fields.push_back( C("name") );
		}
		if ( (*save)->getIsStruct() != o->getIsStruct() ) {
			values.addInt( o->getIsStruct() );
			fields.push_back( C("isStruct") );
		}
		if ( (*save)->getIsInterface() != o->getIsInterface() ) {
			values.addInt( o->getIsInterface() );
			fields.push_back( C("isInterface") );
		}
		if ( (*save)->getIsAbstract() != o->getIsAbstract() ) {
			values.addInt( o->getIsAbstract() );
			fields.push_back( C("isAbstract") );
		}
		if ( (*save)->getLinesCount() != o->getLinesCount() ) {
			values.addInt( o->getLinesCount() );
			fields.push_back( C("linesCount") );
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
		for ( cppAttribute=listOfCppAttributeToAdd.begin(); cppAttribute!=listOfCppAttributeToAdd.end() ; ++cppAttribute ) {
			cppAttributeAccess->insertCppAttribute(*cppAttribute);
		}
		for ( cppAttribute=listOfCppAttributeToUpdate.begin(); cppAttribute!=listOfCppAttributeToUpdate.end() ; ++cppAttribute ) {
			cppAttributeAccess->updateCppAttribute(*cppAttribute);
		}
		for ( cppAttribute=listOfCppAttributeToRemove.begin(); cppAttribute!=listOfCppAttributeToRemove.end() ; ++cppAttribute ) {
			cppAttributeAccess->deleteCppAttribute(*cppAttribute);
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
	_CppAttributeAccess<EncodingT>* cppAttributeAccess = _CppAttributeAccess<EncodingT>::getInstance();
	if (!cppAttributeAccess) {
		m_logger->errorStream() << "CppAttributeAccess class is not initialized.";
		throw NullPointerException("CppAttributeAccess class is not initialized.");
	}
	try {
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
		int id = connection->selectMaxID(C("identifier"), C("cppClass"))+1;
		values.addInt( id );
		fields.push_back( C("identifier") );
		values.addText( o->getName() );
		fields.push_back( C("name") );
		values.addInt( o->getIsStruct() );
		fields.push_back( C("isStruct") );
		values.addInt( o->getIsInterface() );
		fields.push_back( C("isInterface") );
		values.addInt( o->getIsAbstract() );
		fields.push_back( C("isAbstract") );
		values.addInt( o->getLinesCount() );
		fields.push_back( C("linesCount") );
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
		typename _CppClass<EncodingT>::CppAttributeIterator cppAttribute;
		for ( cppAttribute=o->getCppAttributesBeginning(); cppAttribute!=o->getCppAttributesEnd(); ++cppAttribute ) {
			(*cppAttribute)->setCppClass(o);
			cppAttributeAccess->insertCppAttribute(*cppAttribute);
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
	_CppAttributeAccess<EncodingT>* cppAttributeAccess = _CppAttributeAccess<EncodingT>::getInstance();
	if (!cppAttributeAccess) {
		m_logger->errorStream() << "CppAttributeAccess class is not initialized.";
		throw NullPointerException("CppAttributeAccess class is not initialized.");
	}
	typename _CppClass<EncodingT>::CppClassIDEquality CppClassIdEquality(*o);
	typename std::vector< boost::shared_ptr< _CppClass<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), CppClassIdEquality);
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
		typename _CppClass<EncodingT>::CppAttributeIterator cppAttribute;
		fillAllCppAttributes(o);
		for ( cppAttribute=o->getCppAttributesBeginning(); cppAttribute!=o->getCppAttributesEnd(); ++cppAttribute ) {
			cppAttributeAccess->deleteCppAttribute(*cppAttribute);
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

