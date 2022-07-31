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
_CppFunctionAccess<EncodingT>* _CppFunctionAccess<EncodingT>::m_instance = NULL;

template<class EncodingT>
_CppFunctionAccess<EncodingT>* 
_CppFunctionAccess<EncodingT>::getInstance()  
{
	if (m_instance == NULL) {
		m_instance = new _CppFunctionAccess<EncodingT>();
	}
	return m_instance;
}

template<class EncodingT>
_CppFunctionAccess<EncodingT>::_CppFunctionAccess()
: m_transactionOwner(false) 
{
	m_logger = &Category::getInstance(LOGNAME);
	m_logger->debugStream() << "constructor CppFunctionAccess " << m_transactionOwner;
}

template<class EncodingT>
_CppFunctionAccess<EncodingT>::~_CppFunctionAccess()
{
	cancelSelection();
	m_logger = NULL;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppFunction<EncodingT> > >
_CppFunctionAccess<EncodingT>::getManyCppFunctions(typename EncodingT::string_t const&  filter) const 
{
	boost::shared_ptr< _CppFunction<EncodingT> > value;
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _CppFunction<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("name"));
	columns.push_back(UCS("accessSpecifier"));
	columns.push_back(UCS("returnType"));
	columns.push_back(UCS("isConst"));
	columns.push_back(UCS("isVirtual"));
	columns.push_back(UCS("isVirtualPure"));
	columns.push_back(UCS("isStatic"));
	columns.push_back(UCS("isOperator"));
	columns.push_back(UCS("isDestructor"));
	columns.push_back(UCS("isConstructor"));
	columns.push_back(UCS("isVariadic"));
	columns.push_back(UCS("isTemplate"));
	columns.push_back(UCS("isInline"));
	columns.push_back(UCS("isConstexpr"));
	columns.push_back(UCS("isOverride"));
	columns.push_back(UCS("isFinal"));
	columns.push_back(UCS("isNoexcept"));
	columns.push_back(UCS("signature"));
	columns.push_back(UCS("decLineNumber"));
	columns.push_back(UCS("startDecBlock"));
	columns.push_back(UCS("lengthDecBlock"));
	columns.push_back(UCS("linesCount"));
	columns.push_back(UCS("complexity"));
	columns.push_back(UCS("defLineNumber"));
	columns.push_back(UCS("startDefBlock"));
	columns.push_back(UCS("lengthDefBlock"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,UCS("cppFunction")), filter) );
	while( statement.executeStep() ) {
		long long identifier;
		typename EncodingT::string_t name;
		typename EncodingT::string_t accessSpecifier;
		typename EncodingT::string_t returnType;
		long long isConst;
		long long isVirtual;
		long long isVirtualPure;
		long long isStatic;
		long long isOperator;
		long long isDestructor;
		long long isConstructor;
		long long isVariadic;
		long long isTemplate;
		long long isInline;
		long long isConstexpr;
		long long isOverride;
		long long isFinal;
		long long isNoexcept;
		typename EncodingT::string_t signature;
		long long decLineNumber;
		long long startDecBlock;
		long long lengthDecBlock;
		long long linesCount;
		long long complexity;
		long long defLineNumber;
		long long startDefBlock;
		long long lengthDefBlock;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, name ) &&
			statement.getText( 2, accessSpecifier ) &&
			statement.getText( 3, returnType ) &&
			statement.getInt64( 4, isConst ) &&
			statement.getInt64( 5, isVirtual ) &&
			statement.getInt64( 6, isVirtualPure ) &&
			statement.getInt64( 7, isStatic ) &&
			statement.getInt64( 8, isOperator ) &&
			statement.getInt64( 9, isDestructor ) &&
			statement.getInt64( 10, isConstructor ) &&
			statement.getInt64( 11, isVariadic ) &&
			statement.getInt64( 12, isTemplate ) &&
			statement.getInt64( 13, isInline ) &&
			statement.getInt64( 14, isConstexpr ) &&
			statement.getInt64( 15, isOverride ) &&
			statement.getInt64( 16, isFinal ) &&
			statement.getInt64( 17, isNoexcept ) &&
			statement.getText( 18, signature ) &&
			statement.getInt64( 19, decLineNumber ) &&
			statement.getInt64( 20, startDecBlock ) &&
			statement.getInt64( 21, lengthDecBlock ) &&
			statement.getInt64( 22, linesCount ) &&
			statement.getInt64( 23, complexity ) &&
			statement.getInt64( 24, defLineNumber ) &&
			statement.getInt64( 25, startDefBlock ) &&
			statement.getInt64( 26, lengthDefBlock )) {
			value.reset(new _CppFunction<EncodingT>(
				identifier,
				name,
				accessSpecifier,
				returnType,
				isConst,
				isVirtual,
				isVirtualPure,
				isStatic,
				isOperator,
				isDestructor,
				isConstructor,
				isVariadic,
				isTemplate,
				isInline,
				isConstexpr,
				isOverride,
				isFinal,
				isNoexcept,
				signature,
				decLineNumber,
				startDecBlock,
				lengthDecBlock,
				linesCount,
				complexity,
				defLineNumber,
				startDefBlock,
				lengthDefBlock));
			tab.push_back(value);
		}
	}
	return tab;
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppFunction<EncodingT> > >
_CppFunctionAccess<EncodingT>::getAllCppFunctions() const 
{
	return getManyCppFunctions(EncodingT::EMPTY);
}

template<class EncodingT>
boost::shared_ptr< _CppFunction<EncodingT> >
_CppFunctionAccess<EncodingT>::getOneCppFunction(long long identifier) const 
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _CppFunction<EncodingT> > > result = getManyCppFunctions(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
std::vector< boost::shared_ptr< _CppFunction<EncodingT> > >
_CppFunctionAccess<EncodingT>::selectManyCppFunctions(typename EncodingT::string_t const&  filter, bool nowait, bool addition)  
{
	_DataStatement<EncodingT> statement;
	std::vector< boost::shared_ptr< _CppFunction<EncodingT> > > tab;
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	std::vector<typename EncodingT::string_t> columns;                   
	columns.push_back(UCS("identifier"));
	columns.push_back(UCS("name"));
	columns.push_back(UCS("accessSpecifier"));
	columns.push_back(UCS("returnType"));
	columns.push_back(UCS("isConst"));
	columns.push_back(UCS("isVirtual"));
	columns.push_back(UCS("isVirtualPure"));
	columns.push_back(UCS("isStatic"));
	columns.push_back(UCS("isOperator"));
	columns.push_back(UCS("isDestructor"));
	columns.push_back(UCS("isConstructor"));
	columns.push_back(UCS("isVariadic"));
	columns.push_back(UCS("isTemplate"));
	columns.push_back(UCS("isInline"));
	columns.push_back(UCS("isConstexpr"));
	columns.push_back(UCS("isOverride"));
	columns.push_back(UCS("isFinal"));
	columns.push_back(UCS("isNoexcept"));
	columns.push_back(UCS("signature"));
	columns.push_back(UCS("decLineNumber"));
	columns.push_back(UCS("startDecBlock"));
	columns.push_back(UCS("lengthDecBlock"));
	columns.push_back(UCS("linesCount"));
	columns.push_back(UCS("complexity"));
	columns.push_back(UCS("defLineNumber"));
	columns.push_back(UCS("startDefBlock"));
	columns.push_back(UCS("lengthDefBlock"));
	if (!addition || !connection->isTransactionInProgress()) {
		cancelSelection();
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
	}
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,UCS("cppFunction")), filter, nowait) );
	while( statement.executeStep() ) {
		long long identifier;
		typename EncodingT::string_t name;
		typename EncodingT::string_t accessSpecifier;
		typename EncodingT::string_t returnType;
		long long isConst;
		long long isVirtual;
		long long isVirtualPure;
		long long isStatic;
		long long isOperator;
		long long isDestructor;
		long long isConstructor;
		long long isVariadic;
		long long isTemplate;
		long long isInline;
		long long isConstexpr;
		long long isOverride;
		long long isFinal;
		long long isNoexcept;
		typename EncodingT::string_t signature;
		long long decLineNumber;
		long long startDecBlock;
		long long lengthDecBlock;
		long long linesCount;
		long long complexity;
		long long defLineNumber;
		long long startDefBlock;
		long long lengthDefBlock;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, name ) &&
			statement.getText( 2, accessSpecifier ) &&
			statement.getText( 3, returnType ) &&
			statement.getInt64( 4, isConst ) &&
			statement.getInt64( 5, isVirtual ) &&
			statement.getInt64( 6, isVirtualPure ) &&
			statement.getInt64( 7, isStatic ) &&
			statement.getInt64( 8, isOperator ) &&
			statement.getInt64( 9, isDestructor ) &&
			statement.getInt64( 10, isConstructor ) &&
			statement.getInt64( 11, isVariadic ) &&
			statement.getInt64( 12, isTemplate ) &&
			statement.getInt64( 13, isInline ) &&
			statement.getInt64( 14, isConstexpr ) &&
			statement.getInt64( 15, isOverride ) &&
			statement.getInt64( 16, isFinal ) &&
			statement.getInt64( 17, isNoexcept ) &&
			statement.getText( 18, signature ) &&
			statement.getInt64( 19, decLineNumber ) &&
			statement.getInt64( 20, startDecBlock ) &&
			statement.getInt64( 21, lengthDecBlock ) &&
			statement.getInt64( 22, linesCount ) &&
			statement.getInt64( 23, complexity ) &&
			statement.getInt64( 24, defLineNumber ) &&
			statement.getInt64( 25, startDefBlock ) &&
			statement.getInt64( 26, lengthDefBlock )) {
			tab.push_back(boost::shared_ptr< _CppFunction<EncodingT> >(new _CppFunction<EncodingT>(
				identifier,
				name,
				accessSpecifier,
				returnType,
				isConst,
				isVirtual,
				isVirtualPure,
				isStatic,
				isOperator,
				isDestructor,
				isConstructor,
				isVariadic,
				isTemplate,
				isInline,
				isConstexpr,
				isOverride,
				isFinal,
				isNoexcept,
				signature,
				decLineNumber,
				startDecBlock,
				lengthDecBlock,
				linesCount,
				complexity,
				defLineNumber,
				startDefBlock,
				lengthDefBlock)));
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
boost::shared_ptr< _CppFunction<EncodingT> >
_CppFunctionAccess<EncodingT>::selectOneCppFunction(long long identifier, bool nowait, bool addition)  
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _CppFunction<EncodingT> > > result = selectManyCppFunctions(UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait, addition);
	if (result.size()==0) {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
	}
	return result.back();
}

template<class EncodingT>
bool
_CppFunctionAccess<EncodingT>::isSelectedCppFunction(boost::shared_ptr< _CppFunction<EncodingT> > o) const 
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
_CppFunctionAccess<EncodingT>::cancelSelection()  
{
	_DataConnection<EncodingT>* connection = _DataConnection<EncodingT>::getInstance();
	if (!connection) {
		m_logger->errorStream() << "DB connection is not initialized.";    
		throw NullPointerException("DB connection is not initialized.");   
	}
	_CppParameterAccess<EncodingT>* cppParameterAccess = _CppParameterAccess<EncodingT>::getInstance();
	if (!cppParameterAccess) {
		m_logger->errorStream() << "CppParameterAccess class is not initialized.";
		throw NullPointerException("CppParameterAccess class is not initialized.");
	}
	_CppVariableAccess<EncodingT>* cppVariableAccess = _CppVariableAccess<EncodingT>::getInstance();
	if (!cppVariableAccess) {
		m_logger->errorStream() << "CppVariableAccess class is not initialized.";
		throw NullPointerException("CppVariableAccess class is not initialized.");
	}
	if (!m_backup.empty()) {
		if (connection->isTransactionInProgress() && m_transactionOwner) {
			connection->rollback();
			m_transactionOwner = false;
			m_transactionSignal(OPERATION_ACCESS_ROLLBACK);
		}
		m_backup.clear();
		cppParameterAccess->cancelSelection();
		cppVariableAccess->cancelSelection();
	}
}

template<class EncodingT>
void
_CppFunctionAccess<EncodingT>::fillCppDeclarationFile(boost::shared_ptr< _CppFunction<EncodingT> > o)  
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
	_CppFileAccess<EncodingT>* cppDeclarationFileAccess = _CppFileAccess<EncodingT>::getInstance();
	if (!cppDeclarationFileAccess) {
		m_logger->errorStream() << "CppFileAccess class is not initialized.";
		throw NullPointerException("CppFileAccess class is not initialized.");
	}
	long long id;
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,UCS("idDecFile")), std::vector<typename EncodingT::string_t>(1,UCS("cppFunction")), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
	if( statement.executeStep() && statement.getInt64( 0, id ) && id != 0 ) {
		boost::shared_ptr< _CppFile<EncodingT> > val = cppDeclarationFileAccess->getOneCppFile(id);
		typename backup_t::iterator save = m_backup.find(o);
		if (save != m_backup.end()) {
			(*save)->setCppDeclarationFile(val);
		}
		o->setCppDeclarationFile(val);
	}
	else {
		m_logger->debugStream() << "identifier not found.";
	}
}

template<class EncodingT>
void
_CppFunctionAccess<EncodingT>::fillCppDefinitionFile(boost::shared_ptr< _CppFunction<EncodingT> > o)  
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
	_CppFileAccess<EncodingT>* cppDefinitionFileAccess = _CppFileAccess<EncodingT>::getInstance();
	if (!cppDefinitionFileAccess) {
		m_logger->errorStream() << "CppFileAccess class is not initialized.";
		throw NullPointerException("CppFileAccess class is not initialized.");
	}
	long long id;
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,UCS("idDefFile")), std::vector<typename EncodingT::string_t>(1,UCS("cppFunction")), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
	if( statement.executeStep() && statement.getInt64( 0, id ) && id != 0 ) {
		boost::shared_ptr< _CppFile<EncodingT> > val = cppDefinitionFileAccess->getOneCppFile(id);
		typename backup_t::iterator save = m_backup.find(o);
		if (save != m_backup.end()) {
			(*save)->setCppDefinitionFile(val);
		}
		o->setCppDefinitionFile(val);
	}
	else {
		m_logger->debugStream() << "identifier not found.";
	}
}

template<class EncodingT>
void
_CppFunctionAccess<EncodingT>::fillCppClass(boost::shared_ptr< _CppFunction<EncodingT> > o)  
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
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,UCS("idClass")), std::vector<typename EncodingT::string_t>(1,UCS("cppFunction")), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
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
_CppFunctionAccess<EncodingT>::fillAllCppParameters(boost::shared_ptr< _CppFunction<EncodingT> > o, bool nowait)  
{
	fillManyCppParameters(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_CppFunctionAccess<EncodingT>::fillOneCppParameter(boost::shared_ptr< _CppFunction<EncodingT> > o, long long identifier, bool nowait)  
{
	fillManyCppParameters(o, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait);
}

template<class EncodingT>
void
_CppFunctionAccess<EncodingT>::fillManyCppParameters(boost::shared_ptr< _CppFunction<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_CppParameterAccess<EncodingT>* cppParameterAccess = _CppParameterAccess<EncodingT>::getInstance();
	if (!cppParameterAccess) {
		m_logger->errorStream() << "CppParameterAccess class is not initialized.";
		throw NullPointerException("CppParameterAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _CppParameter<EncodingT> > > tab;
	typename EncodingT::string_t cppParameterFilter = UCS("idFunction = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		cppParameterFilter += UCS(" AND ") + filter;
	}
	typename backup_t::iterator save = m_backup.find(o);
	if (save != m_backup.end())
	{
		tab = cppParameterAccess->selectManyCppParameters(cppParameterFilter, nowait, true);
		(*save)->clearCppParameters();
		(*save)->insertCppParameter((*save)->getCppParametersEnd(), tab.begin(), tab.end());
	}
	else
	{
		tab = cppParameterAccess->getManyCppParameters(cppParameterFilter);
	}
	o->clearCppParameters();
	o->insertCppParameter(o->getCppParametersEnd(), tab.begin(), tab.end());
}

template<class EncodingT>
void
_CppFunctionAccess<EncodingT>::fillAllCppVariables(boost::shared_ptr< _CppFunction<EncodingT> > o, bool nowait)  
{
	fillManyCppVariables(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_CppFunctionAccess<EncodingT>::fillOneCppVariable(boost::shared_ptr< _CppFunction<EncodingT> > o, long long identifier, bool nowait)  
{
	fillManyCppVariables(o, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(identifier))/* + UCS("\'")*/, nowait);
}

template<class EncodingT>
void
_CppFunctionAccess<EncodingT>::fillManyCppVariables(boost::shared_ptr< _CppFunction<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
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
	typename EncodingT::string_t cppVariableFilter = UCS("idFunction = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		cppVariableFilter += UCS(" AND ") + filter;
	}
	typename backup_t::iterator save = m_backup.find(o);
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
bool
_CppFunctionAccess<EncodingT>::isModifiedCppFunction(boost::shared_ptr< _CppFunction<EncodingT> > o) const 
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_CppParameterAccess<EncodingT>* cppParameterAccess = _CppParameterAccess<EncodingT>::getInstance();
	if (!cppParameterAccess) {
		m_logger->errorStream() << "CppParameterAccess class is not initialized.";
		throw NullPointerException("CppParameterAccess class is not initialized.");
	}
	_CppVariableAccess<EncodingT>* cppVariableAccess = _CppVariableAccess<EncodingT>::getInstance();
	if (!cppVariableAccess) {
		m_logger->errorStream() << "CppVariableAccess class is not initialized.";
		throw NullPointerException("CppVariableAccess class is not initialized.");
	}
	typename backup_t::const_iterator save = m_backup.find(o);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getName() != o->getName());
	bUpdate = bUpdate || ((*save)->getAccessSpecifier() != o->getAccessSpecifier());
	bUpdate = bUpdate || ((*save)->getReturnType() != o->getReturnType());
	bUpdate = bUpdate || ((*save)->getIsConst() != o->getIsConst());
	bUpdate = bUpdate || ((*save)->getIsVirtual() != o->getIsVirtual());
	bUpdate = bUpdate || ((*save)->getIsVirtualPure() != o->getIsVirtualPure());
	bUpdate = bUpdate || ((*save)->getIsStatic() != o->getIsStatic());
	bUpdate = bUpdate || ((*save)->getIsOperator() != o->getIsOperator());
	bUpdate = bUpdate || ((*save)->getIsDestructor() != o->getIsDestructor());
	bUpdate = bUpdate || ((*save)->getIsConstructor() != o->getIsConstructor());
	bUpdate = bUpdate || ((*save)->getIsVariadic() != o->getIsVariadic());
	bUpdate = bUpdate || ((*save)->getIsTemplate() != o->getIsTemplate());
	bUpdate = bUpdate || ((*save)->getIsInline() != o->getIsInline());
	bUpdate = bUpdate || ((*save)->getIsConstexpr() != o->getIsConstexpr());
	bUpdate = bUpdate || ((*save)->getIsOverride() != o->getIsOverride());
	bUpdate = bUpdate || ((*save)->getIsFinal() != o->getIsFinal());
	bUpdate = bUpdate || ((*save)->getIsNoexcept() != o->getIsNoexcept());
	bUpdate = bUpdate || ((*save)->getSignature() != o->getSignature());
	bUpdate = bUpdate || ((*save)->getDecLineNumber() != o->getDecLineNumber());
	bUpdate = bUpdate || ((*save)->getStartDecBlock() != o->getStartDecBlock());
	bUpdate = bUpdate || ((*save)->getLengthDecBlock() != o->getLengthDecBlock());
	bUpdate = bUpdate || ((*save)->getLinesCount() != o->getLinesCount());
	bUpdate = bUpdate || ((*save)->getComplexity() != o->getComplexity());
	bUpdate = bUpdate || ((*save)->getDefLineNumber() != o->getDefLineNumber());
	bUpdate = bUpdate || ((*save)->getStartDefBlock() != o->getStartDefBlock());
	bUpdate = bUpdate || ((*save)->getLengthDefBlock() != o->getLengthDefBlock());
	bUpdate = bUpdate || (!(*save)->isNullCppDeclarationFile() && !o->isNullCppDeclarationFile() && !typename _CppFile<EncodingT>::CppFileIDEquality(*(*save)->getCppDeclarationFile())(o->getCppDeclarationFile()))
		|| ((*save)->isNullCppDeclarationFile() && !o->isNullCppDeclarationFile()) 
		|| (!(*save)->isNullCppDeclarationFile() && o->isNullCppDeclarationFile());
	bUpdate = bUpdate || (!(*save)->isNullCppDefinitionFile() && !o->isNullCppDefinitionFile() && !typename _CppFile<EncodingT>::CppFileIDEquality(*(*save)->getCppDefinitionFile())(o->getCppDefinitionFile()))
		|| ((*save)->isNullCppDefinitionFile() && !o->isNullCppDefinitionFile()) 
		|| (!(*save)->isNullCppDefinitionFile() && o->isNullCppDefinitionFile());
	bUpdate = bUpdate || (!(*save)->isNullCppClass() && !o->isNullCppClass() && !typename _CppClass<EncodingT>::CppClassIDEquality(*(*save)->getCppClass())(o->getCppClass()))
		|| ((*save)->isNullCppClass() && !o->isNullCppClass()) 
		|| (!(*save)->isNullCppClass() && o->isNullCppClass());
	typename _CppFunction<EncodingT>::CppParameterIterator cppParameter;
	for ( cppParameter=o->getCppParametersBeginning(); cppParameter!=o->getCppParametersEnd(); ++cppParameter ) {
		if (!(*cppParameter)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppParameter<EncodingT>::CppParameterIDEquality cppParameterIdEquality(*(*cppParameter));
		bUpdate = bUpdate || (std::find_if((*save)->getCppParametersBeginning(), (*save)->getCppParametersEnd(), cppParameterIdEquality) == (*save)->getCppParametersEnd())
			|| (cppParameterAccess->isModifiedCppParameter(*cppParameter));
	}
	for ( cppParameter=(*save)->getCppParametersBeginning(); cppParameter<(*save)->getCppParametersEnd(); ++cppParameter ) {
		if (!(*cppParameter)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _CppParameter<EncodingT>::CppParameterIDEquality cppParameterIdEquality(*(*cppParameter));
		bUpdate = bUpdate || (std::find_if(o->getCppParametersBeginning(), o->getCppParametersEnd(), cppParameterIdEquality) == o->getCppParametersEnd());
	}
	typename _CppFunction<EncodingT>::CppVariableIterator cppVariable;
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
	return bUpdate;
}

template<class EncodingT>
void
_CppFunctionAccess<EncodingT>::updateCppFunction(boost::shared_ptr< _CppFunction<EncodingT> > o)  
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
	_CppParameterAccess<EncodingT>* cppParameterAccess = _CppParameterAccess<EncodingT>::getInstance();
	if (!cppParameterAccess) {
		m_logger->errorStream() << "CppParameterAccess class is not initialized.";
		throw NullPointerException("CppParameterAccess class is not initialized.");
	}
	_CppVariableAccess<EncodingT>* cppVariableAccess = _CppVariableAccess<EncodingT>::getInstance();
	if (!cppVariableAccess) {
		m_logger->errorStream() << "CppVariableAccess class is not initialized.";
		throw NullPointerException("CppVariableAccess class is not initialized.");
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
		if ( (*save)->getReturnType() != o->getReturnType() ) {
			values.addText( o->getReturnType() );
			fields.push_back( UCS("returnType") );
		}
		if ( (*save)->getIsConst() != o->getIsConst() ) {
			values.addInt64( o->getIsConst() );
			fields.push_back( UCS("isConst") );
		}
		if ( (*save)->getIsVirtual() != o->getIsVirtual() ) {
			values.addInt64( o->getIsVirtual() );
			fields.push_back( UCS("isVirtual") );
		}
		if ( (*save)->getIsVirtualPure() != o->getIsVirtualPure() ) {
			values.addInt64( o->getIsVirtualPure() );
			fields.push_back( UCS("isVirtualPure") );
		}
		if ( (*save)->getIsStatic() != o->getIsStatic() ) {
			values.addInt64( o->getIsStatic() );
			fields.push_back( UCS("isStatic") );
		}
		if ( (*save)->getIsOperator() != o->getIsOperator() ) {
			values.addInt64( o->getIsOperator() );
			fields.push_back( UCS("isOperator") );
		}
		if ( (*save)->getIsDestructor() != o->getIsDestructor() ) {
			values.addInt64( o->getIsDestructor() );
			fields.push_back( UCS("isDestructor") );
		}
		if ( (*save)->getIsConstructor() != o->getIsConstructor() ) {
			values.addInt64( o->getIsConstructor() );
			fields.push_back( UCS("isConstructor") );
		}
		if ( (*save)->getIsVariadic() != o->getIsVariadic() ) {
			values.addInt64( o->getIsVariadic() );
			fields.push_back( UCS("isVariadic") );
		}
		if ( (*save)->getIsTemplate() != o->getIsTemplate() ) {
			values.addInt64( o->getIsTemplate() );
			fields.push_back( UCS("isTemplate") );
		}
		if ( (*save)->getIsInline() != o->getIsInline() ) {
			values.addInt64( o->getIsInline() );
			fields.push_back( UCS("isInline") );
		}
		if ( (*save)->getIsConstexpr() != o->getIsConstexpr() ) {
			values.addInt64( o->getIsConstexpr() );
			fields.push_back( UCS("isConstexpr") );
		}
		if ( (*save)->getIsOverride() != o->getIsOverride() ) {
			values.addInt64( o->getIsOverride() );
			fields.push_back( UCS("isOverride") );
		}
		if ( (*save)->getIsFinal() != o->getIsFinal() ) {
			values.addInt64( o->getIsFinal() );
			fields.push_back( UCS("isFinal") );
		}
		if ( (*save)->getIsNoexcept() != o->getIsNoexcept() ) {
			values.addInt64( o->getIsNoexcept() );
			fields.push_back( UCS("isNoexcept") );
		}
		if ( (*save)->getSignature() != o->getSignature() ) {
			values.addText( o->getSignature() );
			fields.push_back( UCS("signature") );
		}
		if ( (*save)->getDecLineNumber() != o->getDecLineNumber() ) {
			values.addInt64( o->getDecLineNumber() );
			fields.push_back( UCS("decLineNumber") );
		}
		if ( (*save)->getStartDecBlock() != o->getStartDecBlock() ) {
			values.addInt64( o->getStartDecBlock() );
			fields.push_back( UCS("startDecBlock") );
		}
		if ( (*save)->getLengthDecBlock() != o->getLengthDecBlock() ) {
			values.addInt64( o->getLengthDecBlock() );
			fields.push_back( UCS("lengthDecBlock") );
		}
		if ( (*save)->getLinesCount() != o->getLinesCount() ) {
			values.addInt64( o->getLinesCount() );
			fields.push_back( UCS("linesCount") );
		}
		if ( (*save)->getComplexity() != o->getComplexity() ) {
			values.addInt64( o->getComplexity() );
			fields.push_back( UCS("complexity") );
		}
		if ( (*save)->getDefLineNumber() != o->getDefLineNumber() ) {
			values.addInt64( o->getDefLineNumber() );
			fields.push_back( UCS("defLineNumber") );
		}
		if ( (*save)->getStartDefBlock() != o->getStartDefBlock() ) {
			values.addInt64( o->getStartDefBlock() );
			fields.push_back( UCS("startDefBlock") );
		}
		if ( (*save)->getLengthDefBlock() != o->getLengthDefBlock() ) {
			values.addInt64( o->getLengthDefBlock() );
			fields.push_back( UCS("lengthDefBlock") );
		}
		if ( !o->isNullCppDeclarationFile() && typename _CppFile<EncodingT>::CppFileIDEquality(-1)(o->getCppDeclarationFile()) ) {
			m_logger->errorStream() << "idDecFile : Identifier is null.";
			throw InvalidQueryException("idDecFile : Identifier is null.");
		}
		else if ( !o->isNullCppDeclarationFile() && !typename _CppFile<EncodingT>::CppFileIDEquality(*(o->getCppDeclarationFile()))((*save)->getCppDeclarationFile()) ) {
			values.addInt64( o->getCppDeclarationFile()->getIdentifier() );
			fields.push_back( UCS("idDecFile") );
		}
		else if ( o->isNullCppDeclarationFile() && !(*save)->isNullCppDeclarationFile() ) {
			values.addNull();
			fields.push_back( UCS("idDecFile") );
		}
		if ( !o->isNullCppDefinitionFile() && typename _CppFile<EncodingT>::CppFileIDEquality(-1)(o->getCppDefinitionFile()) ) {
			m_logger->errorStream() << "idDefFile : Identifier is null.";
			throw InvalidQueryException("idDefFile : Identifier is null.");
		}
		else if ( !o->isNullCppDefinitionFile() && !typename _CppFile<EncodingT>::CppFileIDEquality(*(o->getCppDefinitionFile()))((*save)->getCppDefinitionFile()) ) {
			values.addInt64( o->getCppDefinitionFile()->getIdentifier() );
			fields.push_back( UCS("idDefFile") );
		}
		else if ( o->isNullCppDefinitionFile() && !(*save)->isNullCppDefinitionFile() ) {
			values.addNull();
			fields.push_back( UCS("idDefFile") );
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
		std::vector< boost::shared_ptr< _CppParameter<EncodingT> > > listOfCppParameterToAdd;
		std::vector< boost::shared_ptr< _CppParameter<EncodingT> > > listOfCppParameterToUpdate;
		typename _CppFunction<EncodingT>::CppParameterIterator cppParameter;
		for ( cppParameter=o->getCppParametersBeginning(); cppParameter!=o->getCppParametersEnd(); ++cppParameter ) {
			if (!(*cppParameter)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*cppParameter)->setCppFunction(o);
			typename _CppParameter<EncodingT>::CppParameterIDEquality cppParameterIdEquality(*(*cppParameter));
			if ( std::find_if((*save)->getCppParametersBeginning(), (*save)->getCppParametersEnd(), cppParameterIdEquality) == (*save)->getCppParametersEnd()) {
				listOfCppParameterToAdd.push_back(*cppParameter);
			}
			else {
				if (cppParameterAccess->isModifiedCppParameter(*cppParameter))
					listOfCppParameterToUpdate.push_back(*cppParameter);
			}
		}
		std::vector< boost::shared_ptr< _CppParameter<EncodingT> > > listOfCppParameterToRemove;
		for ( cppParameter=(*save)->getCppParametersBeginning(); cppParameter<(*save)->getCppParametersEnd(); ++cppParameter ) {
			if (!(*cppParameter)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			typename _CppParameter<EncodingT>::CppParameterIDEquality cppParameterIdEquality(*(*cppParameter));
			if ( std::find_if(o->getCppParametersBeginning(), o->getCppParametersEnd(), cppParameterIdEquality) == o->getCppParametersEnd()) {
				listOfCppParameterToRemove.push_back(*cppParameter);
			}
		}
		std::vector< boost::shared_ptr< _CppVariable<EncodingT> > > listOfCppVariableToAdd;
		std::vector< boost::shared_ptr< _CppVariable<EncodingT> > > listOfCppVariableToUpdate;
		typename _CppFunction<EncodingT>::CppVariableIterator cppVariable;
		for ( cppVariable=o->getCppVariablesBeginning(); cppVariable!=o->getCppVariablesEnd(); ++cppVariable ) {
			if (!(*cppVariable)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*cppVariable)->setCppFunction(o);
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
		if (!fields.empty()) {
			statement.swap( connection->update(UCS("cppFunction"), fields, UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, UCS("cppFunction"), o);
		}
		for ( cppParameter=listOfCppParameterToAdd.begin(); cppParameter!=listOfCppParameterToAdd.end() ; ++cppParameter ) {
			cppParameterAccess->insertCppParameter(*cppParameter);
		}
		for ( cppParameter=listOfCppParameterToUpdate.begin(); cppParameter!=listOfCppParameterToUpdate.end() ; ++cppParameter ) {
			cppParameterAccess->updateCppParameter(*cppParameter);
		}
		for ( cppParameter=listOfCppParameterToRemove.begin(); cppParameter!=listOfCppParameterToRemove.end() ; ++cppParameter ) {
			cppParameterAccess->deleteCppParameter(*cppParameter);
		}
		for ( cppVariable=listOfCppVariableToAdd.begin(); cppVariable!=listOfCppVariableToAdd.end() ; ++cppVariable ) {
			cppVariableAccess->insertCppVariable(*cppVariable);
		}
		for ( cppVariable=listOfCppVariableToUpdate.begin(); cppVariable!=listOfCppVariableToUpdate.end() ; ++cppVariable ) {
			cppVariableAccess->updateCppVariable(*cppVariable);
		}
		for ( cppVariable=listOfCppVariableToRemove.begin(); cppVariable!=listOfCppVariableToRemove.end() ; ++cppVariable ) {
			cppVariableAccess->fillCppFunction(*cppVariable);
			(*cppVariable)->eraseCppFunction();
			cppVariableAccess->updateCppVariable(*cppVariable);
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
_CppFunctionAccess<EncodingT>::insertCppFunction(boost::shared_ptr< _CppFunction<EncodingT> > o)  
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
	_CppParameterAccess<EncodingT>* cppParameterAccess = _CppParameterAccess<EncodingT>::getInstance();
	if (!cppParameterAccess) {
		m_logger->errorStream() << "CppParameterAccess class is not initialized.";
		throw NullPointerException("CppParameterAccess class is not initialized.");
	}
	_CppVariableAccess<EncodingT>* cppVariableAccess = _CppVariableAccess<EncodingT>::getInstance();
	if (!cppVariableAccess) {
		m_logger->errorStream() << "CppVariableAccess class is not initialized.";
		throw NullPointerException("CppVariableAccess class is not initialized.");
	}
	try {
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
		if ( !o->isNullCppDeclarationFile() && typename _CppFile<EncodingT>::CppFileIDEquality(-1)(o->getCppDeclarationFile()) ) {
			m_logger->errorStream() << "idDecFile : Identifier is null.";
			throw InvalidQueryException("idDecFile : Identifier is null.");
		}
		else if ( !o->isNullCppDeclarationFile() ) {
			values.addInt64( o->getCppDeclarationFile()->getIdentifier() );
			fields.push_back( UCS("idDecFile") );
		}
		else {
			values.addNull();
			fields.push_back( UCS("idDecFile") );
		}
		if ( !o->isNullCppDefinitionFile() && typename _CppFile<EncodingT>::CppFileIDEquality(-1)(o->getCppDefinitionFile()) ) {
			m_logger->errorStream() << "idDefFile : Identifier is null.";
			throw InvalidQueryException("idDefFile : Identifier is null.");
		}
		else if ( !o->isNullCppDefinitionFile() ) {
			values.addInt64( o->getCppDefinitionFile()->getIdentifier() );
			fields.push_back( UCS("idDefFile") );
		}
		else {
			values.addNull();
			fields.push_back( UCS("idDefFile") );
		}
		int id = connection->selectMaxID(UCS("identifier"), UCS("cppFunction"))+1;
		values.addInt( id );
		fields.push_back( UCS("identifier") );
		values.addText( o->getName() );
		fields.push_back( UCS("name") );
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
		values.addText( o->getReturnType() );
		fields.push_back( UCS("returnType") );
		values.addInt64( o->getIsConst() );
		fields.push_back( UCS("isConst") );
		values.addInt64( o->getIsVirtual() );
		fields.push_back( UCS("isVirtual") );
		values.addInt64( o->getIsVirtualPure() );
		fields.push_back( UCS("isVirtualPure") );
		values.addInt64( o->getIsStatic() );
		fields.push_back( UCS("isStatic") );
		values.addInt64( o->getIsOperator() );
		fields.push_back( UCS("isOperator") );
		values.addInt64( o->getIsDestructor() );
		fields.push_back( UCS("isDestructor") );
		values.addInt64( o->getIsConstructor() );
		fields.push_back( UCS("isConstructor") );
		values.addInt64( o->getIsVariadic() );
		fields.push_back( UCS("isVariadic") );
		values.addInt64( o->getIsTemplate() );
		fields.push_back( UCS("isTemplate") );
		values.addInt64( o->getIsInline() );
		fields.push_back( UCS("isInline") );
		values.addInt64( o->getIsConstexpr() );
		fields.push_back( UCS("isConstexpr") );
		values.addInt64( o->getIsOverride() );
		fields.push_back( UCS("isOverride") );
		values.addInt64( o->getIsFinal() );
		fields.push_back( UCS("isFinal") );
		values.addInt64( o->getIsNoexcept() );
		fields.push_back( UCS("isNoexcept") );
		values.addText( o->getSignature() );
		fields.push_back( UCS("signature") );
		values.addInt64( o->getDecLineNumber() );
		fields.push_back( UCS("decLineNumber") );
		values.addInt64( o->getStartDecBlock() );
		fields.push_back( UCS("startDecBlock") );
		values.addInt64( o->getLengthDecBlock() );
		fields.push_back( UCS("lengthDecBlock") );
		values.addInt64( o->getLinesCount() );
		fields.push_back( UCS("linesCount") );
		values.addInt64( o->getComplexity() );
		fields.push_back( UCS("complexity") );
		values.addInt64( o->getDefLineNumber() );
		fields.push_back( UCS("defLineNumber") );
		values.addInt64( o->getStartDefBlock() );
		fields.push_back( UCS("startDefBlock") );
		values.addInt64( o->getLengthDefBlock() );
		fields.push_back( UCS("lengthDefBlock") );
		statement.swap( connection->insert(UCS("cppFunction"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		o->setIdentifier(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, UCS("cppFunction"), o);
		typename _CppFunction<EncodingT>::CppParameterIterator cppParameter;
		for ( cppParameter=o->getCppParametersBeginning(); cppParameter!=o->getCppParametersEnd(); ++cppParameter ) {
			(*cppParameter)->setCppFunction(o);
			cppParameterAccess->insertCppParameter(*cppParameter);
		}
		typename _CppFunction<EncodingT>::CppVariableIterator cppVariable;
		for ( cppVariable=o->getCppVariablesBeginning(); cppVariable!=o->getCppVariablesEnd(); ++cppVariable ) {
			(*cppVariable)->setCppFunction(o);
			cppVariableAccess->insertCppVariable(*cppVariable);
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
_CppFunctionAccess<EncodingT>::deleteCppFunction(boost::shared_ptr< _CppFunction<EncodingT> > o)  
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
	_CppParameterAccess<EncodingT>* cppParameterAccess = _CppParameterAccess<EncodingT>::getInstance();
	if (!cppParameterAccess) {
		m_logger->errorStream() << "CppParameterAccess class is not initialized.";
		throw NullPointerException("CppParameterAccess class is not initialized.");
	}
	_CppVariableAccess<EncodingT>* cppVariableAccess = _CppVariableAccess<EncodingT>::getInstance();
	if (!cppVariableAccess) {
		m_logger->errorStream() << "CppVariableAccess class is not initialized.";
		throw NullPointerException("CppVariableAccess class is not initialized.");
	}
	typename backup_t::iterator save = m_backup.find(o);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before deletion.";
		throw UnSelectedObjectException("You must select object before deletion.");
	}
	try {
		typename _CppFunction<EncodingT>::CppParameterIterator cppParameter;
		fillAllCppParameters(o);
		for ( cppParameter=o->getCppParametersBeginning(); cppParameter!=o->getCppParametersEnd(); ++cppParameter ) {
			cppParameterAccess->deleteCppParameter(*cppParameter);
		}
		typename _CppFunction<EncodingT>::CppVariableIterator cppVariable;
		fillAllCppVariables(o);
		for ( cppVariable=o->getCppVariablesBeginning(); cppVariable!=o->getCppVariablesEnd(); ++cppVariable ) {
			cppVariableAccess->fillCppFunction(*cppVariable);
			(*cppVariable)->eraseCppFunction();
			cppVariableAccess->updateCppVariable(*cppVariable);
		}
		statement.swap( connection->deleteFrom(UCS("cppFunction"), UCS("identifier = ") /*+ UCS("\'") */+ C(ToString::parse(o->getIdentifier()))/* + UCS("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, UCS("cppFunction"), o);
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
typename _CppFunctionAccess<EncodingT>::connection_t
_CppFunctionAccess<EncodingT>::addInsertSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_insertSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppFunctionAccess<EncodingT>::connection_t
_CppFunctionAccess<EncodingT>::addUpdateSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_updateSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppFunctionAccess<EncodingT>::connection_t
_CppFunctionAccess<EncodingT>::addDeleteSignal(typename signal_t::slot_function_type subscriber)  
{
	return m_deleteSignal.connect(subscriber);
}

template<class EncodingT>
typename _CppFunctionAccess<EncodingT>::connection_t
_CppFunctionAccess<EncodingT>::addTransactionSignal(typename signal_transaction_t::slot_function_type subscriber)  
{
	return m_transactionSignal.connect(subscriber);
}

template<class EncodingT>
void
_CppFunctionAccess<EncodingT>::removeInsertSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppFunctionAccess<EncodingT>::removeUpdateSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppFunctionAccess<EncodingT>::removeDeleteSignal(connection_t connection)  
{
	connection.disconnect();
}

template<class EncodingT>
void
_CppFunctionAccess<EncodingT>::removeTransactionSignal(connection_t connection)  
{
	connection.disconnect();
}


NAMESPACE_END

#undef C
#undef A

