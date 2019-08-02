#include "BadSqlQueryException.hpp"
#include "dbstring.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(data_access)

template <class EncodingT>
std::map<typename EncodingT::string_t,sqlite3*>
_DataConnection<EncodingT>::connection_handles;

template <class EncodingT>
std::map<typename EncodingT::string_t,_DataConnection<EncodingT>*>
_DataConnection<EncodingT>::m_instances;

// constructor
template <class EncodingT>
_DataConnection<EncodingT>::_DataConnection(sqlite3* handle)
{
    m_logger = &Category::getInstance(LOGNAME);
    m_logger->debugStream() << "creation DataConnection";
    connection_handle = handle;
    transaction_inProgress = false;
}

template <class EncodingT>
bool 
_DataConnection<EncodingT>::openConnection(typename EncodingT::string_t const& host,
                                           int port,
                                           typename EncodingT::string_t const& db,
                                           typename EncodingT::string_t const& user,
                                           typename EncodingT::string_t const& passwd)
{
    bool success = false;
    typename std::map<typename EncodingT::string_t,sqlite3*>::const_iterator i = connection_handles.find(db);
    if (i == connection_handles.end()) {
        //open connection
        //m_logger->debugStream() << "open db connection";
        sqlite3* connection_handle = NULL;
        success = (sqlite3_open(A(db).c_str(), &connection_handle) == SQLITE_OK);
        connection_handles.insert(std::make_pair(db,connection_handle));
    }
    return success;
}

template <class EncodingT>
void 
_DataConnection<EncodingT>::closeConnection(typename EncodingT::string_t const& db)
{
    bool clear = true;
    typename std::map<typename EncodingT::string_t,sqlite3*>::const_iterator i = connection_handles.begin();
    if (!db.empty()) {
      i = connection_handles.find(db);
    }
    while ((i != connection_handles.end()) && clear) {
        //close connection
        sqlite3_close(i->second);
        i = connection_handles.erase(i);
        //m_logger->debugStream() << "db connection closed";
        clear = db.empty();
    }
}

template <class EncodingT>
_DataConnection<EncodingT>* 
_DataConnection<EncodingT>::getInstance(typename EncodingT::string_t const& db)
{
    typename EncodingT::string_t dbName = db;
    if (db.empty() && !connection_handles.empty()) {
      dbName = connection_handles.begin()->first;
    }
    //check connection and create DataConnection
    typename std::map<typename EncodingT::string_t,sqlite3*>::const_iterator i = connection_handles.find(dbName);
    if (i != connection_handles.end()) {
      sqlite3* handle = i->second;
      if (handle) {
          _DataConnection<EncodingT>* instance = NULL;
          typename std::map<typename EncodingT::string_t,_DataConnection<EncodingT>*>::const_iterator j = m_instances.find(dbName);
          if (j != m_instances.end()) {
              instance = j->second;
          }
          else {
              instance = new _DataConnection<EncodingT>(handle);
              m_instances.insert(std::make_pair(dbName, instance));
          }
          return instance;
      }
    }
    return NULL;
}

template <class EncodingT>
_DataStatement<EncodingT>&
_DataConnection<EncodingT>::prepareStatement(typename ucs::string_t const& query)
{
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(connection_handle, enc::encode<ucs,dbs>(query).c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        m_logger->fatalStream() << "bad query : " << sqlite3_errmsg(connection_handle);
        throw BadSqlQueryException(sqlite3_errmsg(connection_handle));
    }
    _DataStatement<EncodingT> obj(stmt);
    current_statement.swap(obj);
    return current_statement;
}

template <class EncodingT>
_DataStatement<EncodingT>&
_DataConnection<EncodingT>::prepareStatement(typename ansi::string_t const& query)
{
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(connection_handle, query.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        m_logger->fatalStream() << "bad query : " << sqlite3_errmsg(connection_handle);
        throw BadSqlQueryException(sqlite3_errmsg(connection_handle));
    }
    _DataStatement<EncodingT> obj(stmt);
    current_statement.swap(obj);
    return current_statement;
}

template <class EncodingT>
typename EncodingT::string_t 
_DataConnection<EncodingT>::formatSelect(std::vector<typename EncodingT::string_t> const& columns,
                                         std::vector<typename EncodingT::string_t> const& tables,
                                         typename EncodingT::string_t const& filter, bool forUpdate, bool noWait) const
{
    //Create SQL query
    typename EncodingT::string_t query = UCS("SELECT ");
    if (columns.size() == 0) {
        m_logger->fatalStream() << "bad query : no columns defined in SELECT query";
        throw BadSqlQueryException("no columns defined in SELECT query");
    }
    query += columns[0];
    for (size_t i=1; i<columns.size(); i++) query += UCS(", ") + columns[i];
    query += UCS(" FROM ");
    if (tables.size() == 0) {
        m_logger->fatalStream() << "bad query : no tables defined in SELECT query";
        throw BadSqlQueryException("no tables defined in SELECT query");
    }
    query += tables[0];
    for (size_t i=1; i<tables.size(); i++) query += UCS(", ") + tables[i];
    if (filter != EncodingT::EMPTY) {
        query += UCS(" WHERE ") + filter;
    }
    if (forUpdate) query += UCS(" FOR UPDATE ");
    if (noWait) query += UCS(" NOWAIT ");
    query += UCS(";");
    m_logger->debugStream() << "query : " << A(query);
    return query;
}

template <class EncodingT>
_DataStatement<EncodingT>&
_DataConnection<EncodingT>::select(std::vector<typename EncodingT::string_t> const& columns,
           std::vector<typename EncodingT::string_t> const& tables,
           typename EncodingT::string_t const& filter)
{
    return prepareStatement(formatSelect(columns, tables, filter, false, false));
}

template <class EncodingT>
_DataStatement<EncodingT>&
_DataConnection<EncodingT>::selectForUpdate(std::vector<typename EncodingT::string_t> const& columns,
                                            std::vector<typename EncodingT::string_t> const& tables,
                                            typename EncodingT::string_t const& filter, bool nowait)
{
    // This method locks data until the end of the transaction.
    // If NoWait is set, SelectForUpdate returns immediately with an error.
    // Else SelectForUpdate waits the end of the other process.
    // -- For Update not supported by sqlite
    // -- Locks must be performed by Process Synchronization mechanism
    return prepareStatement(formatSelect(columns, tables, filter, false, nowait));
}

template <class EncodingT>
typename EncodingT::string_t 
_DataConnection<EncodingT>::formatInsert(typename EncodingT::string_t const& table,
                                         std::vector<typename EncodingT::string_t> const& columns) const
{
    //Create SQL query
    typename EncodingT::string_t query = UCS("INSERT INTO ");
    if (table == EncodingT::EMPTY) {
        m_logger->fatalStream() << "bad query : no table defined in INSERT query";
        throw BadSqlQueryException("no table defined in INSERT query");
    }
    query += table;
    query += UCS(" ( ");
    if (columns.size() == 0) {
        m_logger->fatalStream() << "bad query : no columns defined in INSERT query";
        throw BadSqlQueryException("no columns defined in INSERT query");
    }
    query += columns[0];
    for (size_t i=1; i<columns.size(); i++) query += UCS(", ") + columns[i];
    query += UCS(" ) VALUES ( ?");
    for (size_t i=1; i<columns.size(); i++) query += UCS(", ?");
    query += UCS(" );");
    m_logger->debugStream() << "query : " << A(query);
    return query;
}

template <class EncodingT>
_DataStatement<EncodingT>&
_DataConnection<EncodingT>::insert(typename EncodingT::string_t const& table,
                                   std::vector<typename EncodingT::string_t> const& columns)
{
    return prepareStatement(formatInsert(table, columns));
}

template <class EncodingT>
typename EncodingT::string_t 
_DataConnection<EncodingT>::formatDeleteFrom(typename EncodingT::string_t const& table,
											 typename EncodingT::string_t const& filter) const
{
    //Create SQL query
    typename EncodingT::string_t query = UCS("DELETE FROM ");
    if (table == EncodingT::EMPTY) {
        m_logger->fatalStream() << "bad query : no table defined in DELETE query";
        throw BadSqlQueryException("no table defined in DELETE query");
    }
    else query += table;
    if (filter != EncodingT::EMPTY) {
        query += UCS(" WHERE ") + filter;
    }
    query += UCS(";");
    m_logger->debugStream() << "query : " << A(query);
    return query;
}

template <class EncodingT>
_DataStatement<EncodingT>&
_DataConnection<EncodingT>::deleteFrom(typename EncodingT::string_t const& table,
                                       typename EncodingT::string_t const& filter)
{
    return prepareStatement(formatDeleteFrom(table, filter));
}

template <class EncodingT>
typename EncodingT::string_t 
_DataConnection<EncodingT>::formatUpdate(typename EncodingT::string_t const& table,
                                         std::vector<typename EncodingT::string_t> const& columns,
                                         typename EncodingT::string_t const& filter) const
{
    //Create SQL query
    typename EncodingT::string_t query = UCS("UPDATE ");
    if (table == EncodingT::EMPTY) {
        m_logger->fatalStream() << "bad query : no table defined in UPDATE query";
        throw BadSqlQueryException("no table defined in UPDATE query");
    }
    else query += table;
    query += UCS(" SET ");
    if (columns.size() == 0) {
        m_logger->fatalStream() << "bad query : no columns defined in UPDATE query";
        throw BadSqlQueryException("no columns defined in UPDATE query");
    }
    else query += columns[0] + UCS("=?");
    for (size_t i=1; i<columns.size(); i++) query += UCS(", ") + columns[i] + UCS("=?");
    if (filter != EncodingT::EMPTY) {
        query += UCS(" WHERE ") + filter;
    }
    query += UCS(";");
    m_logger->debugStream() << "query : " << A(query);
    return query;
}

template <class EncodingT>
_DataStatement<EncodingT>&
_DataConnection<EncodingT>::update(typename EncodingT::string_t const& table,
                                   std::vector<typename EncodingT::string_t> const& columns,
                                   typename EncodingT::string_t const& filter)
{
    return prepareStatement(formatUpdate(table, columns, filter));
}

template <class EncodingT>
int 
_DataConnection<EncodingT>::getLastInsertID() const
{
    return (int) sqlite3_last_insert_rowid(connection_handle);
}

template <class EncodingT>
int 
_DataConnection<EncodingT>::selectMaxID(typename EncodingT::string_t const& id,
                                        typename EncodingT::string_t const& table) const
{
    int result = 0;
    sqlite3_stmt *statement;
    int res;
    // This method returns the max Id and locks the table with SELECT FOR UPDATE. 
    // -- For Update not supported by sqlite
    // -- Locks must be performed by Process Synchronization mechanism
    string query = string("SELECT max(") + A(id) + ") FROM "+ A(table) + ";";
    m_logger->debugStream() << "query : " << query;
    if (sqlite3_prepare_v2(connection_handle,query.c_str(),-1,&statement,NULL) != SQLITE_OK){
        m_logger->fatalStream() << "bad query : " << sqlite3_errmsg(connection_handle);
        throw BadSqlQueryException(sqlite3_errmsg(connection_handle));
    }
    size_t num_fields = sqlite3_column_count(statement); 
    while ((res=sqlite3_step(statement)) == SQLITE_ROW) {
        if (num_fields) result = sqlite3_column_int(statement,0);
    }
    sqlite3_finalize(statement);    
    return result;
}

template <class EncodingT>
bool 
_DataConnection<EncodingT>::commit()
{
    static const char * commit = "COMMIT;";
    string query = commit;
    m_logger->debugStream() << "query : " << query;
    sqlite3_exec(connection_handle,query.c_str(),NULL,NULL,NULL);
    transaction_inProgress = false;
    return true;
}

template <class EncodingT>
bool 
_DataConnection<EncodingT>::rollback()
{
    static const char * rollback = "ROLLBACK;";
    string query = rollback;
    m_logger->debugStream() << "query : " << query;
    sqlite3_exec(connection_handle,query.c_str(),NULL,NULL,NULL);
    transaction_inProgress = false;
    return true;
}

template <class EncodingT>
bool 
_DataConnection<EncodingT>::startTransaction()
{
    static const char * start_transaction = "BEGIN TRANSACTION;";
    string query = start_transaction;
    m_logger->debugStream() << "query : " << query;
    sqlite3_exec(connection_handle,query.c_str(),NULL,NULL,NULL);
    transaction_inProgress = true;
    return true;
}

template <class EncodingT>
bool 
_DataConnection<EncodingT>::isTransactionInProgress() const
{
    return transaction_inProgress;
}

template <class EncodingT>
void
_DataConnection<EncodingT>::setPragma(typename EncodingT::string_t const& pragma)
{
    static const char * pragma_statement = "PRAGMA ";
    string query = pragma_statement;
    query += A(pragma);
    m_logger->debugStream() << "query : " << query;
    sqlite3_exec(connection_handle,query.c_str(),NULL,NULL,NULL);
}

NAMESPACE_END

#undef C
#undef A

