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
	columns.push_back(C("identifier"));
	columns.push_back(C("name"));
	columns.push_back(C("accessSpecifier"));
	columns.push_back(C("returnType"));
	columns.push_back(C("isConst"));
	columns.push_back(C("isVirtual"));
	columns.push_back(C("isVirtualPure"));
	columns.push_back(C("isStatic"));
	columns.push_back(C("isOperator"));
	columns.push_back(C("isDestructor"));
	columns.push_back(C("isConstructor"));
	columns.push_back(C("isVariadic"));
	columns.push_back(C("signature"));
	columns.push_back(C("startDecBlock"));
	columns.push_back(C("lengthDecBlock"));
	columns.push_back(C("decLineNumber"));
	columns.push_back(C("linesCount"));
	columns.push_back(C("complexity"));
	columns.push_back(C("defLineNumber"));
	columns.push_back(C("startDefBlock"));
	columns.push_back(C("lengthDefBlock"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,C("cppFunction")), filter) );
	while( statement.executeStep() ) {
		int identifier;
		typename EncodingT::string_t name;
		typename EncodingT::string_t accessSpecifier;
		typename EncodingT::string_t returnType;
		int isConst;
		int isVirtual;
		int isVirtualPure;
		int isStatic;
		int isOperator;
		int isDestructor;
		int isConstructor;
		int isVariadic;
		typename EncodingT::string_t signature;
		int startDecBlock;
		int lengthDecBlock;
		int decLineNumber;
		int linesCount;
		int complexity;
		int defLineNumber;
		int startDefBlock;
		int lengthDefBlock;
		if (statement.getInt( 0, identifier ) &&
			statement.getText( 1, name ) &&
			statement.getText( 2, accessSpecifier ) &&
			statement.getText( 3, returnType ) &&
			statement.getInt( 4, isConst ) &&
			statement.getInt( 5, isVirtual ) &&
			statement.getInt( 6, isVirtualPure ) &&
			statement.getInt( 7, isStatic ) &&
			statement.getInt( 8, isOperator ) &&
			statement.getInt( 9, isDestructor ) &&
			statement.getInt( 10, isConstructor ) &&
			statement.getInt( 11, isVariadic ) &&
			statement.getText( 12, signature ) &&
			statement.getInt( 13, startDecBlock ) &&
			statement.getInt( 14, lengthDecBlock ) &&
			statement.getInt( 15, decLineNumber ) &&
			statement.getInt( 16, linesCount ) &&
			statement.getInt( 17, complexity ) &&
			statement.getInt( 18, defLineNumber ) &&
			statement.getInt( 19, startDefBlock ) &&
			statement.getInt( 20, lengthDefBlock )) {
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
				signature,
				startDecBlock,
				lengthDecBlock,
				decLineNumber,
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
_CppFunctionAccess<EncodingT>::getOneCppFunction(int identifier) const 
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _CppFunction<EncodingT> > > result = getManyCppFunctions(C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/);
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
	columns.push_back(C("identifier"));
	columns.push_back(C("name"));
	columns.push_back(C("accessSpecifier"));
	columns.push_back(C("returnType"));
	columns.push_back(C("isConst"));
	columns.push_back(C("isVirtual"));
	columns.push_back(C("isVirtualPure"));
	columns.push_back(C("isStatic"));
	columns.push_back(C("isOperator"));
	columns.push_back(C("isDestructor"));
	columns.push_back(C("isConstructor"));
	columns.push_back(C("isVariadic"));
	columns.push_back(C("signature"));
	columns.push_back(C("startDecBlock"));
	columns.push_back(C("lengthDecBlock"));
	columns.push_back(C("decLineNumber"));
	columns.push_back(C("linesCount"));
	columns.push_back(C("complexity"));
	columns.push_back(C("defLineNumber"));
	columns.push_back(C("startDefBlock"));
	columns.push_back(C("lengthDefBlock"));
	if (!addition || !connection->isTransactionInProgress()) {
		cancelSelection();
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
	}
	statement.swap( connection->selectForUpdate(columns, std::vector<typename EncodingT::string_t>(1,C("cppFunction")), filter, nowait) );
	while( statement.executeStep() ) {
		int identifier;
		typename EncodingT::string_t name;
		typename EncodingT::string_t accessSpecifier;
		typename EncodingT::string_t returnType;
		int isConst;
		int isVirtual;
		int isVirtualPure;
		int isStatic;
		int isOperator;
		int isDestructor;
		int isConstructor;
		int isVariadic;
		typename EncodingT::string_t signature;
		int startDecBlock;
		int lengthDecBlock;
		int decLineNumber;
		int linesCount;
		int complexity;
		int defLineNumber;
		int startDefBlock;
		int lengthDefBlock;
		if (statement.getInt( 0, identifier ) &&
			statement.getText( 1, name ) &&
			statement.getText( 2, accessSpecifier ) &&
			statement.getText( 3, returnType ) &&
			statement.getInt( 4, isConst ) &&
			statement.getInt( 5, isVirtual ) &&
			statement.getInt( 6, isVirtualPure ) &&
			statement.getInt( 7, isStatic ) &&
			statement.getInt( 8, isOperator ) &&
			statement.getInt( 9, isDestructor ) &&
			statement.getInt( 10, isConstructor ) &&
			statement.getInt( 11, isVariadic ) &&
			statement.getText( 12, signature ) &&
			statement.getInt( 13, startDecBlock ) &&
			statement.getInt( 14, lengthDecBlock ) &&
			statement.getInt( 15, decLineNumber ) &&
			statement.getInt( 16, linesCount ) &&
			statement.getInt( 17, complexity ) &&
			statement.getInt( 18, defLineNumber ) &&
			statement.getInt( 19, startDefBlock ) &&
			statement.getInt( 20, lengthDefBlock )) {
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
				signature,
				startDecBlock,
				lengthDecBlock,
				decLineNumber,
				linesCount,
				complexity,
				defLineNumber,
				startDefBlock,
				lengthDefBlock)));
		}
	}
	m_backup.insert(m_backup.end(), tab.begin(), tab.end());
	return copy_ptr(tab);
}

template<class EncodingT>
boost::shared_ptr< _CppFunction<EncodingT> >
_CppFunctionAccess<EncodingT>::selectOneCppFunction(int identifier, bool nowait, bool addition)  
{
	if ( identifier==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	std::vector< boost::shared_ptr< _CppFunction<EncodingT> > > result = selectManyCppFunctions(C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait, addition);
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
	typename _CppFunction<EncodingT>::CppFunctionIDEquality cppFunctionIdEquality(*o);
	return (!m_backup.empty() && (std::find_if(m_backup.begin(), m_backup.end(), cppFunctionIdEquality)!=m_backup.end()));
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
	_DebugFunctionInfoAccess<EncodingT>* debugFunctionInfoAccess = _DebugFunctionInfoAccess<EncodingT>::getInstance();
	if (!debugFunctionInfoAccess) {
		m_logger->errorStream() << "DebugFunctionInfoAccess class is not initialized.";
		throw NullPointerException("DebugFunctionInfoAccess class is not initialized.");
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
		debugFunctionInfoAccess->cancelSelection();
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
	_TextFileAccess<EncodingT>* textFileAccess = _TextFileAccess<EncodingT>::getInstance();
	if (!textFileAccess) {
		m_logger->errorStream() << "TextFileAccess class is not initialized.";
		throw NullPointerException("TextFileAccess class is not initialized.");
	}
	int id;
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,C("idDecFile")), std::vector<typename EncodingT::string_t>(1,C("cppFunction")), C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
	if( statement.executeStep() && statement.getInt( 0, id ) && id != 0 ) {
		typename _CppFunction<EncodingT>::CppFunctionIDEquality cppFunctionIdEquality(o->getIdentifier());
		boost::shared_ptr< _CppFile<EncodingT> > val = cppDeclarationFileAccess->getOneCppFile(textFileAccess->getOneTextFile(id));
		typename std::vector< boost::shared_ptr<_CppFunction<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFunctionIdEquality);
		if (save != m_backup.end()) {
			(*save)->setCppDeclarationFile(val);
		}
		o->setCppDeclarationFile(val);
	}
	else {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
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
	_TextFileAccess<EncodingT>* textFileAccess = _TextFileAccess<EncodingT>::getInstance();
	if (!textFileAccess) {
		m_logger->errorStream() << "TextFileAccess class is not initialized.";
		throw NullPointerException("TextFileAccess class is not initialized.");
	}
	int id;
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,C("idDefFile")), std::vector<typename EncodingT::string_t>(1,C("cppFunction")), C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
	if( statement.executeStep() && statement.getInt( 0, id ) && id != 0 ) {
		typename _CppFunction<EncodingT>::CppFunctionIDEquality cppFunctionIdEquality(o->getIdentifier());
		boost::shared_ptr< _CppFile<EncodingT> > val = cppDefinitionFileAccess->getOneCppFile(textFileAccess->getOneTextFile(id));
		typename std::vector< boost::shared_ptr<_CppFunction<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFunctionIdEquality);
		if (save != m_backup.end()) {
			(*save)->setCppDefinitionFile(val);
		}
		o->setCppDefinitionFile(val);
	}
	else {
		m_logger->errorStream() << "identifier not found.";
		throw NoSqlRowException("identifier not found.");
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
	int id;
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,C("idClass")), std::vector<typename EncodingT::string_t>(1,C("cppFunction")), C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
	if( statement.executeStep() && statement.getInt( 0, id ) && id != 0 ) {
		typename _CppFunction<EncodingT>::CppFunctionIDEquality cppFunctionIdEquality(o->getIdentifier());
		boost::shared_ptr< _CppClass<EncodingT> > val = cppClassAccess->getOneCppClass(id);
		typename std::vector< boost::shared_ptr<_CppFunction<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFunctionIdEquality);
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
_CppFunctionAccess<EncodingT>::fillOneCppParameter(boost::shared_ptr< _CppFunction<EncodingT> > o, int identifier, bool nowait)  
{
	fillManyCppParameters(o, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait);
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
	typename EncodingT::string_t cppParameterFilter = C("idFunction = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		cppParameterFilter += C(" AND ") + filter;
	}
	typename _CppFunction<EncodingT>::CppFunctionIDEquality cppFunctionIdEquality(o->getIdentifier());
	typename std::vector< boost::shared_ptr< _CppFunction<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFunctionIdEquality);
	if (save != m_backup.end())
	{
		tab = cppParameterAccess->selectManyCppParameters(cppParameterFilter, nowait);
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
_CppFunctionAccess<EncodingT>::fillOneCppVariable(boost::shared_ptr< _CppFunction<EncodingT> > o, int identifier, bool nowait)  
{
	fillManyCppVariables(o, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait);
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
	typename EncodingT::string_t cppVariableFilter = C("idFunction = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		cppVariableFilter += C(" AND ") + filter;
	}
	typename _CppFunction<EncodingT>::CppFunctionIDEquality cppFunctionIdEquality(o->getIdentifier());
	typename std::vector< boost::shared_ptr< _CppFunction<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFunctionIdEquality);
	if (save != m_backup.end())
	{
		tab = cppVariableAccess->selectManyCppVariables(cppVariableFilter, nowait);
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
_CppFunctionAccess<EncodingT>::fillAllDebugFunctionInfos(boost::shared_ptr< _CppFunction<EncodingT> > o, bool nowait)  
{
	fillManyDebugFunctionInfos(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_CppFunctionAccess<EncodingT>::fillOneDebugFunctionInfo(boost::shared_ptr< _CppFunction<EncodingT> > o, int identifier, bool nowait)  
{
	fillManyDebugFunctionInfos(o, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait);
}

template<class EncodingT>
void
_CppFunctionAccess<EncodingT>::fillManyDebugFunctionInfos(boost::shared_ptr< _CppFunction<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
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
	typename EncodingT::string_t debugFunctionInfoFilter = C("idFunction = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		debugFunctionInfoFilter += C(" AND ") + filter;
	}
	typename _CppFunction<EncodingT>::CppFunctionIDEquality cppFunctionIdEquality(o->getIdentifier());
	typename std::vector< boost::shared_ptr< _CppFunction<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFunctionIdEquality);
	if (save != m_backup.end())
	{
		tab = debugFunctionInfoAccess->selectManyDebugFunctionInfos(debugFunctionInfoFilter, nowait);
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
	_DebugFunctionInfoAccess<EncodingT>* debugFunctionInfoAccess = _DebugFunctionInfoAccess<EncodingT>::getInstance();
	if (!debugFunctionInfoAccess) {
		m_logger->errorStream() << "DebugFunctionInfoAccess class is not initialized.";
		throw NullPointerException("DebugFunctionInfoAccess class is not initialized.");
	}
	typename _CppFunction<EncodingT>::CppFunctionIDEquality cppFunctionIdEquality(*o);
	typename std::vector< boost::shared_ptr< _CppFunction<EncodingT> > >::const_iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFunctionIdEquality);
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
	bUpdate = bUpdate || ((*save)->getSignature() != o->getSignature());
	bUpdate = bUpdate || ((*save)->getStartDecBlock() != o->getStartDecBlock());
	bUpdate = bUpdate || ((*save)->getLengthDecBlock() != o->getLengthDecBlock());
	bUpdate = bUpdate || ((*save)->getDecLineNumber() != o->getDecLineNumber());
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
	typename _CppFunction<EncodingT>::DebugFunctionInfoIterator debugFunctionInfo;
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
	_DebugFunctionInfoAccess<EncodingT>* debugFunctionInfoAccess = _DebugFunctionInfoAccess<EncodingT>::getInstance();
	if (!debugFunctionInfoAccess) {
		m_logger->errorStream() << "DebugFunctionInfoAccess class is not initialized.";
		throw NullPointerException("DebugFunctionInfoAccess class is not initialized.");
	}
	typename _CppFunction<EncodingT>::CppFunctionIDEquality cppFunctionIdEquality(*o);
	typename std::vector< boost::shared_ptr< _CppFunction<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), cppFunctionIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	try {
		if ( (*save)->getName() != o->getName() ) {
			values.addText( o->getName() );
			fields.push_back( C("name") );
		}
		if ( (*save)->getAccessSpecifier() != o->getAccessSpecifier() ) {
			values.addText( o->getAccessSpecifier() );
			fields.push_back( C("accessSpecifier") );
		}
		if ( (*save)->getReturnType() != o->getReturnType() ) {
			values.addText( o->getReturnType() );
			fields.push_back( C("returnType") );
		}
		if ( (*save)->getIsConst() != o->getIsConst() ) {
			values.addInt( o->getIsConst() );
			fields.push_back( C("isConst") );
		}
		if ( (*save)->getIsVirtual() != o->getIsVirtual() ) {
			values.addInt( o->getIsVirtual() );
			fields.push_back( C("isVirtual") );
		}
		if ( (*save)->getIsVirtualPure() != o->getIsVirtualPure() ) {
			values.addInt( o->getIsVirtualPure() );
			fields.push_back( C("isVirtualPure") );
		}
		if ( (*save)->getIsStatic() != o->getIsStatic() ) {
			values.addInt( o->getIsStatic() );
			fields.push_back( C("isStatic") );
		}
		if ( (*save)->getIsOperator() != o->getIsOperator() ) {
			values.addInt( o->getIsOperator() );
			fields.push_back( C("isOperator") );
		}
		if ( (*save)->getIsDestructor() != o->getIsDestructor() ) {
			values.addInt( o->getIsDestructor() );
			fields.push_back( C("isDestructor") );
		}
		if ( (*save)->getIsConstructor() != o->getIsConstructor() ) {
			values.addInt( o->getIsConstructor() );
			fields.push_back( C("isConstructor") );
		}
		if ( (*save)->getIsVariadic() != o->getIsVariadic() ) {
			values.addInt( o->getIsVariadic() );
			fields.push_back( C("isVariadic") );
		}
		if ( (*save)->getSignature() != o->getSignature() ) {
			values.addText( o->getSignature() );
			fields.push_back( C("signature") );
		}
		if ( (*save)->getStartDecBlock() != o->getStartDecBlock() ) {
			values.addInt( o->getStartDecBlock() );
			fields.push_back( C("startDecBlock") );
		}
		if ( (*save)->getLengthDecBlock() != o->getLengthDecBlock() ) {
			values.addInt( o->getLengthDecBlock() );
			fields.push_back( C("lengthDecBlock") );
		}
		if ( (*save)->getDecLineNumber() != o->getDecLineNumber() ) {
			values.addInt( o->getDecLineNumber() );
			fields.push_back( C("decLineNumber") );
		}
		if ( (*save)->getLinesCount() != o->getLinesCount() ) {
			values.addInt( o->getLinesCount() );
			fields.push_back( C("linesCount") );
		}
		if ( (*save)->getComplexity() != o->getComplexity() ) {
			values.addInt( o->getComplexity() );
			fields.push_back( C("complexity") );
		}
		if ( (*save)->getDefLineNumber() != o->getDefLineNumber() ) {
			values.addInt( o->getDefLineNumber() );
			fields.push_back( C("defLineNumber") );
		}
		if ( (*save)->getStartDefBlock() != o->getStartDefBlock() ) {
			values.addInt( o->getStartDefBlock() );
			fields.push_back( C("startDefBlock") );
		}
		if ( (*save)->getLengthDefBlock() != o->getLengthDefBlock() ) {
			values.addInt( o->getLengthDefBlock() );
			fields.push_back( C("lengthDefBlock") );
		}
		if ( !o->isNullCppDeclarationFile() && !o->getCppDeclarationFile()->isNullTextFile() && typename _TextFile<EncodingT>::TextFileIDEquality(-1)(o->getCppDeclarationFile()->getTextFile()) ) {
			m_logger->errorStream() << "idDecFile : Identifier is null.";
			throw InvalidQueryException("idDecFile : Identifier is null.");
		}
		else if ( !o->isNullCppDeclarationFile() && !o->getCppDeclarationFile()->isNullTextFile() && !typename _CppFile<EncodingT>::CppFileIDEquality(*(o->getCppDeclarationFile()))((*save)->getCppDeclarationFile()) ) {
			values.addInt( o->getCppDeclarationFile()->getTextFile()->getRowid() );
			fields.push_back( C("idDecFile") );
		}
		else if ( o->isNullCppDeclarationFile() && !(*save)->isNullCppDeclarationFile() ) {
			m_logger->errorStream() << "idDecFile : null reference is forbidden.";
			throw InvalidQueryException("idDecFile : null reference is forbidden.");
		}
		if ( !o->isNullCppDefinitionFile() && !o->getCppDefinitionFile()->isNullTextFile() && typename _TextFile<EncodingT>::TextFileIDEquality(-1)(o->getCppDefinitionFile()->getTextFile()) ) {
			m_logger->errorStream() << "idDefFile : Identifier is null.";
			throw InvalidQueryException("idDefFile : Identifier is null.");
		}
		else if ( !o->isNullCppDefinitionFile() && !o->getCppDefinitionFile()->isNullTextFile() && !typename _CppFile<EncodingT>::CppFileIDEquality(*(o->getCppDefinitionFile()))((*save)->getCppDefinitionFile()) ) {
			values.addInt( o->getCppDefinitionFile()->getTextFile()->getRowid() );
			fields.push_back( C("idDefFile") );
		}
		else if ( o->isNullCppDefinitionFile() && !(*save)->isNullCppDefinitionFile() ) {
			m_logger->errorStream() << "idDefFile : null reference is forbidden.";
			throw InvalidQueryException("idDefFile : null reference is forbidden.");
		}
		if ( !o->isNullCppClass() && typename _CppClass<EncodingT>::CppClassIDEquality(-1)(o->getCppClass()) ) {
			m_logger->errorStream() << "idClass : Identifier is null.";
			throw InvalidQueryException("idClass : Identifier is null.");
		}
		else if ( !o->isNullCppClass() && !typename _CppClass<EncodingT>::CppClassIDEquality(*(o->getCppClass()))((*save)->getCppClass()) ) {
			values.addInt( o->getCppClass()->getIdentifier() );
			fields.push_back( C("idClass") );
		}
		else if ( o->isNullCppClass() && !(*save)->isNullCppClass() ) {
			values.addText( C("NULL") );
			fields.push_back( C("idClass") );
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
		std::vector< boost::shared_ptr< _DebugFunctionInfo<EncodingT> > > listOfDebugFunctionInfoToAdd;
		std::vector< boost::shared_ptr< _DebugFunctionInfo<EncodingT> > > listOfDebugFunctionInfoToUpdate;
		typename _CppFunction<EncodingT>::DebugFunctionInfoIterator debugFunctionInfo;
		for ( debugFunctionInfo=o->getDebugFunctionInfosBeginning(); debugFunctionInfo!=o->getDebugFunctionInfosEnd(); ++debugFunctionInfo ) {
			if (!(*debugFunctionInfo)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*debugFunctionInfo)->setCppFunction(o);
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
		if (!fields.empty()) {
			statement.swap( connection->update(C("cppFunction"), fields, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, C("cppFunction"), o);
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
			cppVariableAccess->deleteCppVariable(*cppVariable);
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
	_DebugFunctionInfoAccess<EncodingT>* debugFunctionInfoAccess = _DebugFunctionInfoAccess<EncodingT>::getInstance();
	if (!debugFunctionInfoAccess) {
		m_logger->errorStream() << "DebugFunctionInfoAccess class is not initialized.";
		throw NullPointerException("DebugFunctionInfoAccess class is not initialized.");
	}
	try {
		m_transactionOwner = !connection->isTransactionInProgress();
		if (m_transactionOwner) {
			connection->startTransaction();
			m_transactionSignal(OPERATION_ACCESS_START);
		}
		if ( !o->isNullCppDeclarationFile() && !o->getCppDeclarationFile()->isNullTextFile() && typename _TextFile<EncodingT>::TextFileIDEquality(-1)(o->getCppDeclarationFile()->getTextFile()) ) {
			m_logger->errorStream() << "idDecFile : Identifier is null.";
			throw InvalidQueryException("idDecFile : Identifier is null.");
		}
		else if ( !o->isNullCppDeclarationFile() && !o->getCppDeclarationFile()->isNullTextFile() ) {
			values.addInt( o->getCppDeclarationFile()->getTextFile()->getRowid() );
			fields.push_back( C("idDecFile") );
		}
		else {
			m_logger->errorStream() << "idDecFile : null reference is forbidden.";
			throw InvalidQueryException("idDecFile : null reference is forbidden.");
		}
		if ( !o->isNullCppDefinitionFile() && !o->getCppDefinitionFile()->isNullTextFile() && typename _TextFile<EncodingT>::TextFileIDEquality(-1)(o->getCppDefinitionFile()->getTextFile()) ) {
			m_logger->errorStream() << "idDefFile : Identifier is null.";
			throw InvalidQueryException("idDefFile : Identifier is null.");
		}
		else if ( !o->isNullCppDefinitionFile() && !o->getCppDefinitionFile()->isNullTextFile() ) {
			values.addInt( o->getCppDefinitionFile()->getTextFile()->getRowid() );
			fields.push_back( C("idDefFile") );
		}
		else {
			m_logger->errorStream() << "idDefFile : null reference is forbidden.";
			throw InvalidQueryException("idDefFile : null reference is forbidden.");
		}
		int id = connection->selectMaxID(C("identifier"), C("cppFunction"))+1;
		values.addInt( id );
		fields.push_back( C("identifier") );
		values.addText( o->getName() );
		fields.push_back( C("name") );
		if ( !o->isNullCppClass() && typename _CppClass<EncodingT>::CppClassIDEquality(-1)(o->getCppClass()) ) {
			m_logger->errorStream() << "idClass : Identifier is null.";
			throw InvalidQueryException("idClass : Identifier is null.");
		}
		else if ( !o->isNullCppClass() ) {
			values.addInt( o->getCppClass()->getIdentifier() );
			fields.push_back( C("idClass") );
		}
		else {
			values.addText( C("NULL") );
			fields.push_back( C("idClass") );
		}
		values.addText( o->getAccessSpecifier() );
		fields.push_back( C("accessSpecifier") );
		values.addText( o->getReturnType() );
		fields.push_back( C("returnType") );
		values.addInt( o->getIsConst() );
		fields.push_back( C("isConst") );
		values.addInt( o->getIsVirtual() );
		fields.push_back( C("isVirtual") );
		values.addInt( o->getIsVirtualPure() );
		fields.push_back( C("isVirtualPure") );
		values.addInt( o->getIsStatic() );
		fields.push_back( C("isStatic") );
		values.addInt( o->getIsOperator() );
		fields.push_back( C("isOperator") );
		values.addInt( o->getIsDestructor() );
		fields.push_back( C("isDestructor") );
		values.addInt( o->getIsConstructor() );
		fields.push_back( C("isConstructor") );
		values.addInt( o->getIsVariadic() );
		fields.push_back( C("isVariadic") );
		values.addText( o->getSignature() );
		fields.push_back( C("signature") );
		values.addInt( o->getStartDecBlock() );
		fields.push_back( C("startDecBlock") );
		values.addInt( o->getLengthDecBlock() );
		fields.push_back( C("lengthDecBlock") );
		values.addInt( o->getDecLineNumber() );
		fields.push_back( C("decLineNumber") );
		values.addInt( o->getLinesCount() );
		fields.push_back( C("linesCount") );
		values.addInt( o->getComplexity() );
		fields.push_back( C("complexity") );
		values.addInt( o->getDefLineNumber() );
		fields.push_back( C("defLineNumber") );
		values.addInt( o->getStartDefBlock() );
		fields.push_back( C("startDefBlock") );
		values.addInt( o->getLengthDefBlock() );
		fields.push_back( C("lengthDefBlock") );
		statement.swap( connection->insert(C("cppFunction"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		o->setIdentifier(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, C("cppFunction"), o);
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
		typename _CppFunction<EncodingT>::DebugFunctionInfoIterator debugFunctionInfo;
		for ( debugFunctionInfo=o->getDebugFunctionInfosBeginning(); debugFunctionInfo!=o->getDebugFunctionInfosEnd(); ++debugFunctionInfo ) {
			(*debugFunctionInfo)->setCppFunction(o);
			debugFunctionInfoAccess->insertDebugFunctionInfo(*debugFunctionInfo);
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
	_DebugFunctionInfoAccess<EncodingT>* debugFunctionInfoAccess = _DebugFunctionInfoAccess<EncodingT>::getInstance();
	if (!debugFunctionInfoAccess) {
		m_logger->errorStream() << "DebugFunctionInfoAccess class is not initialized.";
		throw NullPointerException("DebugFunctionInfoAccess class is not initialized.");
	}
	typename _CppFunction<EncodingT>::CppFunctionIDEquality CppFunctionIdEquality(*o);
	typename std::vector< boost::shared_ptr< _CppFunction<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), CppFunctionIdEquality);
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
			cppVariableAccess->deleteCppVariable(*cppVariable);
		}
		typename _CppFunction<EncodingT>::DebugFunctionInfoIterator debugFunctionInfo;
		fillAllDebugFunctionInfos(o);
		for ( debugFunctionInfo=o->getDebugFunctionInfosBeginning(); debugFunctionInfo!=o->getDebugFunctionInfosEnd(); ++debugFunctionInfo ) {
			debugFunctionInfoAccess->deleteDebugFunctionInfo(*debugFunctionInfo);
		}
		statement.swap( connection->deleteFrom(C("cppFunction"), C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
		if ( !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		m_deleteSignal(OPERATION_ACCESS_DELETE, C("cppFunction"), o);
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

