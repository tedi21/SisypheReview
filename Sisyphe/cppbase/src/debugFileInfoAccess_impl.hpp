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
	columns.push_back(C("name"));
	columns.push_back(C("compilandPath"));
	columns.push_back(C("checksum"));
	statement.swap( connection->select(columns, std::vector<typename EncodingT::string_t>(1,C("debugFileInfo")), filter) );
	while( statement.executeStep() ) {
		long long identifier;
		typename EncodingT::string_t name;
		typename EncodingT::string_t compilandPath;
		boost::container::vector<unsigned char> checksum;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, name ) &&
			statement.getText( 2, compilandPath ) &&
			statement.getBlob( 3, checksum )) {
			value.reset(new _DebugFileInfo<EncodingT>(
				identifier,
				name,
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
_DebugFileInfoAccess<EncodingT>::getOneDebugFileInfo(long long identifier) const 
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
	columns.push_back(C("name"));
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
		long long identifier;
		typename EncodingT::string_t name;
		typename EncodingT::string_t compilandPath;
		boost::container::vector<unsigned char> checksum;
		if (statement.getInt64( 0, identifier ) &&
			statement.getText( 1, name ) &&
			statement.getText( 2, compilandPath ) &&
			statement.getBlob( 3, checksum )) {
			tab.push_back(boost::shared_ptr< _DebugFileInfo<EncodingT> >(new _DebugFileInfo<EncodingT>(
				identifier,
				name,
				compilandPath,
				checksum)));
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
boost::shared_ptr< _DebugFileInfo<EncodingT> >
_DebugFileInfoAccess<EncodingT>::selectOneDebugFileInfo(long long identifier, bool nowait, bool addition)  
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
	_DebugFunctionInfoAccess<EncodingT>* debugFunctionInfoAccess = _DebugFunctionInfoAccess<EncodingT>::getInstance();
	if (!debugFunctionInfoAccess) {
		m_logger->errorStream() << "DebugFunctionInfoAccess class is not initialized.";
		throw NullPointerException("DebugFunctionInfoAccess class is not initialized.");
	}
	_DebugStubInfoAccess<EncodingT>* debugStubInfoAccess = _DebugStubInfoAccess<EncodingT>::getInstance();
	if (!debugStubInfoAccess) {
		m_logger->errorStream() << "DebugStubInfoAccess class is not initialized.";
		throw NullPointerException("DebugStubInfoAccess class is not initialized.");
	}
	if (!m_backup.empty()) {
		if (connection->isTransactionInProgress() && m_transactionOwner) {
			connection->rollback();
			m_transactionOwner = false;
			m_transactionSignal(OPERATION_ACCESS_ROLLBACK);
		}
		m_backup.clear();
		debugFunctionInfoAccess->cancelSelection();
		debugStubInfoAccess->cancelSelection();
	}
}

template<class EncodingT>
void
_DebugFileInfoAccess<EncodingT>::fillTextFile(boost::shared_ptr< _DebugFileInfo<EncodingT> > o)  
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
	statement.swap( connection->select(std::vector<typename EncodingT::string_t>(1,C("idText")), std::vector<typename EncodingT::string_t>(1,C("debugFileInfo")), C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
	if( statement.executeStep() && statement.getInt64( 0, id ) && id != 0 ) {
		typename _DebugFileInfo<EncodingT>::DebugFileInfoIDEquality debugFileInfoIdEquality(o->getIdentifier());
		boost::shared_ptr< _TextFile<EncodingT> > val = textFileAccess->getOneTextFile(id);
		typename std::list< boost::shared_ptr<_DebugFileInfo<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), debugFileInfoIdEquality);
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
_DebugFileInfoAccess<EncodingT>::fillAllDebugFunctionInfos(boost::shared_ptr< _DebugFileInfo<EncodingT> > o, bool nowait)  
{
	fillManyDebugFunctionInfos(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_DebugFileInfoAccess<EncodingT>::fillOneDebugFunctionInfo(boost::shared_ptr< _DebugFileInfo<EncodingT> > o, long long identifier, bool nowait)  
{
	fillManyDebugFunctionInfos(o, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait);
}

template<class EncodingT>
void
_DebugFileInfoAccess<EncodingT>::fillManyDebugFunctionInfos(boost::shared_ptr< _DebugFileInfo<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
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
	typename EncodingT::string_t debugFunctionInfoFilter = C("idDebugFile = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		debugFunctionInfoFilter += C(" AND ") + filter;
	}
	typename _DebugFileInfo<EncodingT>::DebugFileInfoIDEquality debugFileInfoIdEquality(o->getIdentifier());
	typename std::list< boost::shared_ptr< _DebugFileInfo<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), debugFileInfoIdEquality);
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
_DebugFileInfoAccess<EncodingT>::fillAllDebugStubInfos(boost::shared_ptr< _DebugFileInfo<EncodingT> > o, bool nowait)  
{
	fillManyDebugStubInfos(o, EncodingT::EMPTY, nowait);
}

template<class EncodingT>
void
_DebugFileInfoAccess<EncodingT>::fillOneDebugStubInfo(boost::shared_ptr< _DebugFileInfo<EncodingT> > o, long long identifier, bool nowait)  
{
	fillManyDebugStubInfos(o, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(identifier))/* + C("\'")*/, nowait);
}

template<class EncodingT>
void
_DebugFileInfoAccess<EncodingT>::fillManyDebugStubInfos(boost::shared_ptr< _DebugFileInfo<EncodingT> > o, typename EncodingT::string_t const& filter, bool nowait)  
{
	if (!o) {
		m_logger->errorStream() << "Parameter is null.";
		throw NullPointerException("Parameter is null.");
	}
	if ( o->getIdentifier()==-1 ) {
		m_logger->errorStream() << "Identifier : Identifier is null.";
		throw UnIdentifiedObjectException("Identifier : Identifier is null.");
	}
	_DebugStubInfoAccess<EncodingT>* debugStubInfoAccess = _DebugStubInfoAccess<EncodingT>::getInstance();
	if (!debugStubInfoAccess) {
		m_logger->errorStream() << "DebugStubInfoAccess class is not initialized.";
		throw NullPointerException("DebugStubInfoAccess class is not initialized.");
	}
	std::vector< boost::shared_ptr< _DebugStubInfo<EncodingT> > > tab;
	typename EncodingT::string_t debugStubInfoFilter = C("idDebugFile = ") + C(ToString::parse(o->getIdentifier()));
	if (!filter.empty()) {
		debugStubInfoFilter += C(" AND ") + filter;
	}
	typename _DebugFileInfo<EncodingT>::DebugFileInfoIDEquality debugFileInfoIdEquality(o->getIdentifier());
	typename std::list< boost::shared_ptr< _DebugFileInfo<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), debugFileInfoIdEquality);
	if (save != m_backup.end())
	{
		tab = debugStubInfoAccess->selectManyDebugStubInfos(debugStubInfoFilter, nowait, true);
		(*save)->clearDebugStubInfos();
		(*save)->insertDebugStubInfo((*save)->getDebugStubInfosEnd(), tab.begin(), tab.end());
	}
	else
	{
		tab = debugStubInfoAccess->getManyDebugStubInfos(debugStubInfoFilter);
	}
	o->clearDebugStubInfos();
	o->insertDebugStubInfo(o->getDebugStubInfosEnd(), tab.begin(), tab.end());
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
	_DebugFunctionInfoAccess<EncodingT>* debugFunctionInfoAccess = _DebugFunctionInfoAccess<EncodingT>::getInstance();
	if (!debugFunctionInfoAccess) {
		m_logger->errorStream() << "DebugFunctionInfoAccess class is not initialized.";
		throw NullPointerException("DebugFunctionInfoAccess class is not initialized.");
	}
	_DebugStubInfoAccess<EncodingT>* debugStubInfoAccess = _DebugStubInfoAccess<EncodingT>::getInstance();
	if (!debugStubInfoAccess) {
		m_logger->errorStream() << "DebugStubInfoAccess class is not initialized.";
		throw NullPointerException("DebugStubInfoAccess class is not initialized.");
	}
	typename _DebugFileInfo<EncodingT>::DebugFileInfoIDEquality debugFileInfoIdEquality(*o);
	typename std::list< boost::shared_ptr< _DebugFileInfo<EncodingT> > >::const_iterator save = std::find_if(m_backup.begin(), m_backup.end(), debugFileInfoIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	bool bUpdate = false;
	bUpdate = bUpdate || ((*save)->getName() != o->getName());
	bUpdate = bUpdate || ((*save)->getCompilandPath() != o->getCompilandPath());
	bUpdate = bUpdate || ((*save)->getChecksum() != o->getChecksum());
	bUpdate = bUpdate || (!(*save)->isNullTextFile() && !o->isNullTextFile() && !typename _TextFile<EncodingT>::TextFileIDEquality(*(*save)->getTextFile())(o->getTextFile()))
		|| ((*save)->isNullTextFile() && !o->isNullTextFile()) 
		|| (!(*save)->isNullTextFile() && o->isNullTextFile());
	typename _DebugFileInfo<EncodingT>::DebugFunctionInfoIterator debugFunctionInfo;
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
	typename _DebugFileInfo<EncodingT>::DebugStubInfoIterator debugStubInfo;
	for ( debugStubInfo=o->getDebugStubInfosBeginning(); debugStubInfo!=o->getDebugStubInfosEnd(); ++debugStubInfo ) {
		if (!(*debugStubInfo)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _DebugStubInfo<EncodingT>::DebugStubInfoIDEquality debugStubInfoIdEquality(*(*debugStubInfo));
		bUpdate = bUpdate || (std::find_if((*save)->getDebugStubInfosBeginning(), (*save)->getDebugStubInfosEnd(), debugStubInfoIdEquality) == (*save)->getDebugStubInfosEnd())
			|| (debugStubInfoAccess->isModifiedDebugStubInfo(*debugStubInfo));
	}
	for ( debugStubInfo=(*save)->getDebugStubInfosBeginning(); debugStubInfo<(*save)->getDebugStubInfosEnd(); ++debugStubInfo ) {
		if (!(*debugStubInfo)) {
			m_logger->errorStream() << "Aggregate is null.";
			throw NullPointerException("Aggregate is null.");
		}
		typename _DebugStubInfo<EncodingT>::DebugStubInfoIDEquality debugStubInfoIdEquality(*(*debugStubInfo));
		bUpdate = bUpdate || (std::find_if(o->getDebugStubInfosBeginning(), o->getDebugStubInfosEnd(), debugStubInfoIdEquality) == o->getDebugStubInfosEnd());
	}
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
	_DebugFunctionInfoAccess<EncodingT>* debugFunctionInfoAccess = _DebugFunctionInfoAccess<EncodingT>::getInstance();
	if (!debugFunctionInfoAccess) {
		m_logger->errorStream() << "DebugFunctionInfoAccess class is not initialized.";
		throw NullPointerException("DebugFunctionInfoAccess class is not initialized.");
	}
	_DebugStubInfoAccess<EncodingT>* debugStubInfoAccess = _DebugStubInfoAccess<EncodingT>::getInstance();
	if (!debugStubInfoAccess) {
		m_logger->errorStream() << "DebugStubInfoAccess class is not initialized.";
		throw NullPointerException("DebugStubInfoAccess class is not initialized.");
	}
	typename _DebugFileInfo<EncodingT>::DebugFileInfoIDEquality debugFileInfoIdEquality(*o);
	typename std::list< boost::shared_ptr< _DebugFileInfo<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), debugFileInfoIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before update.";
		throw UnSelectedObjectException("You must select object before update.");
	}
	try {
		if ( (*save)->getName() != o->getName() ) {
			values.addText( o->getName() );
			fields.push_back( C("name") );
		}
		if ( (*save)->getCompilandPath() != o->getCompilandPath() ) {
			values.addText( o->getCompilandPath() );
			fields.push_back( C("compilandPath") );
		}
		if ( (*save)->getChecksum() != o->getChecksum() ) {
			values.addBlob( o->getChecksum() );
			fields.push_back( C("checksum") );
		}
		if ( !o->isNullTextFile() && typename _TextFile<EncodingT>::TextFileIDEquality(-1)(o->getTextFile()) ) {
			m_logger->errorStream() << "idText : Identifier is null.";
			throw InvalidQueryException("idText : Identifier is null.");
		}
		else if ( !o->isNullTextFile() && !typename _TextFile<EncodingT>::TextFileIDEquality(*(o->getTextFile()))((*save)->getTextFile()) ) {
			values.addInt64( o->getTextFile()->getRowid() );
			fields.push_back( C("idText") );
		}
		else if ( o->isNullTextFile() && !(*save)->isNullTextFile() ) {
			m_logger->errorStream() << "idText : null reference is forbidden.";
			throw InvalidQueryException("idText : null reference is forbidden.");
		}
		std::vector< boost::shared_ptr< _DebugFunctionInfo<EncodingT> > > listOfDebugFunctionInfoToAdd;
		std::vector< boost::shared_ptr< _DebugFunctionInfo<EncodingT> > > listOfDebugFunctionInfoToUpdate;
		typename _DebugFileInfo<EncodingT>::DebugFunctionInfoIterator debugFunctionInfo;
		for ( debugFunctionInfo=o->getDebugFunctionInfosBeginning(); debugFunctionInfo!=o->getDebugFunctionInfosEnd(); ++debugFunctionInfo ) {
			if (!(*debugFunctionInfo)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*debugFunctionInfo)->setDebugFileInfo(o);
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
		std::vector< boost::shared_ptr< _DebugStubInfo<EncodingT> > > listOfDebugStubInfoToAdd;
		std::vector< boost::shared_ptr< _DebugStubInfo<EncodingT> > > listOfDebugStubInfoToUpdate;
		typename _DebugFileInfo<EncodingT>::DebugStubInfoIterator debugStubInfo;
		for ( debugStubInfo=o->getDebugStubInfosBeginning(); debugStubInfo!=o->getDebugStubInfosEnd(); ++debugStubInfo ) {
			if (!(*debugStubInfo)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			(*debugStubInfo)->setDebugFileInfo(o);
			typename _DebugStubInfo<EncodingT>::DebugStubInfoIDEquality debugStubInfoIdEquality(*(*debugStubInfo));
			if ( std::find_if((*save)->getDebugStubInfosBeginning(), (*save)->getDebugStubInfosEnd(), debugStubInfoIdEquality) == (*save)->getDebugStubInfosEnd()) {
				listOfDebugStubInfoToAdd.push_back(*debugStubInfo);
			}
			else {
				if (debugStubInfoAccess->isModifiedDebugStubInfo(*debugStubInfo))
					listOfDebugStubInfoToUpdate.push_back(*debugStubInfo);
			}
		}
		std::vector< boost::shared_ptr< _DebugStubInfo<EncodingT> > > listOfDebugStubInfoToRemove;
		for ( debugStubInfo=(*save)->getDebugStubInfosBeginning(); debugStubInfo<(*save)->getDebugStubInfosEnd(); ++debugStubInfo ) {
			if (!(*debugStubInfo)) {
				m_logger->errorStream() << "Aggregate is null.";
				throw NullPointerException("Aggregate is null.");
			}
			typename _DebugStubInfo<EncodingT>::DebugStubInfoIDEquality debugStubInfoIdEquality(*(*debugStubInfo));
			if ( std::find_if(o->getDebugStubInfosBeginning(), o->getDebugStubInfosEnd(), debugStubInfoIdEquality) == o->getDebugStubInfosEnd()) {
				listOfDebugStubInfoToRemove.push_back(*debugStubInfo);
			}
		}
		if (!fields.empty()) {
			statement.swap( connection->update(C("debugFileInfo"), fields, C("identifier = ") /*+ C("\'") */+ C(ToString::parse(o->getIdentifier()))/* + C("\'")*/) );
			if ( !values.fill(statement) || !statement.executeQuery() ) {
				m_logger->fatalStream() << "invalid query.";
				throw InvalidQueryException("invalid query.");
			}
			m_updateSignal(OPERATION_ACCESS_UPDATE, C("debugFileInfo"), o);
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
		for ( debugStubInfo=listOfDebugStubInfoToAdd.begin(); debugStubInfo!=listOfDebugStubInfoToAdd.end() ; ++debugStubInfo ) {
			debugStubInfoAccess->insertDebugStubInfo(*debugStubInfo);
		}
		for ( debugStubInfo=listOfDebugStubInfoToUpdate.begin(); debugStubInfo!=listOfDebugStubInfoToUpdate.end() ; ++debugStubInfo ) {
			debugStubInfoAccess->updateDebugStubInfo(*debugStubInfo);
		}
		for ( debugStubInfo=listOfDebugStubInfoToRemove.begin(); debugStubInfo!=listOfDebugStubInfoToRemove.end() ; ++debugStubInfo ) {
			debugStubInfoAccess->deleteDebugStubInfo(*debugStubInfo);
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
	_DebugFunctionInfoAccess<EncodingT>* debugFunctionInfoAccess = _DebugFunctionInfoAccess<EncodingT>::getInstance();
	if (!debugFunctionInfoAccess) {
		m_logger->errorStream() << "DebugFunctionInfoAccess class is not initialized.";
		throw NullPointerException("DebugFunctionInfoAccess class is not initialized.");
	}
	_DebugStubInfoAccess<EncodingT>* debugStubInfoAccess = _DebugStubInfoAccess<EncodingT>::getInstance();
	if (!debugStubInfoAccess) {
		m_logger->errorStream() << "DebugStubInfoAccess class is not initialized.";
		throw NullPointerException("DebugStubInfoAccess class is not initialized.");
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
		if ( !o->isNullTextFile() && typename _TextFile<EncodingT>::TextFileIDEquality(-1)(o->getTextFile()) ) {
			m_logger->errorStream() << "idText : Identifier is null.";
			throw InvalidQueryException("idText : Identifier is null.");
		}
		else if ( !o->isNullTextFile() ) {
			values.addInt64( o->getTextFile()->getRowid() );
			fields.push_back( C("idText") );
		}
		else {
			m_logger->errorStream() << "idText : null reference is forbidden.";
			throw InvalidQueryException("idText : null reference is forbidden.");
		}
		values.addText( o->getName() );
		fields.push_back( C("name") );
		values.addText( o->getCompilandPath() );
		fields.push_back( C("compilandPath") );
		values.addBlob( o->getChecksum() );
		fields.push_back( C("checksum") );
		statement.swap( connection->insert(C("debugFileInfo"), fields) );
		if ( !values.fill(statement) || !statement.executeQuery() ) {
			m_logger->fatalStream() << "invalid query.";
			throw InvalidQueryException("invalid query.");
		}
		o->setIdentifier(id);
		m_insertSignal(OPERATION_ACCESS_INSERT, C("debugFileInfo"), o);
		typename _DebugFileInfo<EncodingT>::DebugFunctionInfoIterator debugFunctionInfo;
		for ( debugFunctionInfo=o->getDebugFunctionInfosBeginning(); debugFunctionInfo!=o->getDebugFunctionInfosEnd(); ++debugFunctionInfo ) {
			(*debugFunctionInfo)->setDebugFileInfo(o);
			debugFunctionInfoAccess->insertDebugFunctionInfo(*debugFunctionInfo);
		}
		typename _DebugFileInfo<EncodingT>::DebugStubInfoIterator debugStubInfo;
		for ( debugStubInfo=o->getDebugStubInfosBeginning(); debugStubInfo!=o->getDebugStubInfosEnd(); ++debugStubInfo ) {
			(*debugStubInfo)->setDebugFileInfo(o);
			debugStubInfoAccess->insertDebugStubInfo(*debugStubInfo);
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
	_DebugFunctionInfoAccess<EncodingT>* debugFunctionInfoAccess = _DebugFunctionInfoAccess<EncodingT>::getInstance();
	if (!debugFunctionInfoAccess) {
		m_logger->errorStream() << "DebugFunctionInfoAccess class is not initialized.";
		throw NullPointerException("DebugFunctionInfoAccess class is not initialized.");
	}
	_DebugStubInfoAccess<EncodingT>* debugStubInfoAccess = _DebugStubInfoAccess<EncodingT>::getInstance();
	if (!debugStubInfoAccess) {
		m_logger->errorStream() << "DebugStubInfoAccess class is not initialized.";
		throw NullPointerException("DebugStubInfoAccess class is not initialized.");
	}
	typename _DebugFileInfo<EncodingT>::DebugFileInfoIDEquality DebugFileInfoIdEquality(*o);
	typename std::list< boost::shared_ptr< _DebugFileInfo<EncodingT> > >::iterator save = std::find_if(m_backup.begin(), m_backup.end(), DebugFileInfoIdEquality);
	if (save == m_backup.end()) {
		m_logger->errorStream() << "You must select object before deletion.";
		throw UnSelectedObjectException("You must select object before deletion.");
	}
	try {
		typename _DebugFileInfo<EncodingT>::DebugFunctionInfoIterator debugFunctionInfo;
		fillAllDebugFunctionInfos(o);
		for ( debugFunctionInfo=o->getDebugFunctionInfosBeginning(); debugFunctionInfo!=o->getDebugFunctionInfosEnd(); ++debugFunctionInfo ) {
			debugFunctionInfoAccess->deleteDebugFunctionInfo(*debugFunctionInfo);
		}
		typename _DebugFileInfo<EncodingT>::DebugStubInfoIterator debugStubInfo;
		fillAllDebugStubInfos(o);
		for ( debugStubInfo=o->getDebugStubInfosBeginning(); debugStubInfo!=o->getDebugStubInfosEnd(); ++debugStubInfo ) {
			debugStubInfoAccess->deleteDebugStubInfo(*debugStubInfo);
		}
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

