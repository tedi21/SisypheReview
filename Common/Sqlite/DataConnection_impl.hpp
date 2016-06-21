#include "BadSqlQueryException.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(data_access)

template <class EncodingT>
sqlite3* 
_DataConnection<EncodingT>::connection_handle = NULL;

template <class EncodingT>
_DataConnection<EncodingT>* 
_DataConnection<EncodingT>::m_instance = NULL;

// constructor
template <class EncodingT>
_DataConnection<EncodingT>::_DataConnection()
{
    m_logger = &Category::getInstance(LOGNAME);
    m_logger->debugStream() << "creation DataConnection";
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
    //open connection
	//m_logger->debugStream() << "open db connection";
	return sqlite3_open(A(db).c_str(), &connection_handle) == SQLITE_OK;
}

template <class EncodingT>
void 
_DataConnection<EncodingT>::closeConnection()
{
    //close connection
    sqlite3_close(connection_handle);
	connection_handle = NULL;
    //m_logger->debugStream() << "db connection closed";
}

template <class EncodingT>
_DataConnection<EncodingT>* 
_DataConnection<EncodingT>::getInstance()
{
    //check connection and create DataConnection
    if (connection_handle) {
        if (!m_instance) {
            m_instance = new _DataConnection<EncodingT>();
		}
        return m_instance;
    }
    else return NULL;
}

template <class EncodingT>
_DataStatement<EncodingT>&
_DataConnection<EncodingT>::prepareStatement(typename ucs::string_t const& query)
{
    sqlite3_stmt* stmt;
    if (sqlite3_prepare16_v2(connection_handle, query.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
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
    typename EncodingT::string_t query = C("SELECT ");
    if (columns.size() == 0) {
        m_logger->fatalStream() << "bad query : no columns defined in SELECT query";
        throw BadSqlQueryException("no columns defined in SELECT query");
    }
    query += columns[0];
    for (size_t i=1; i<columns.size(); i++) query += C(", ") + columns[i];
    query += C(" FROM ");
    if (tables.size() == 0) {
        m_logger->fatalStream() << "bad query : no tables defined in SELECT query";
        throw BadSqlQueryException("no tables defined in SELECT query");
    }
    query += tables[0];
    for (size_t i=1; i<tables.size(); i++) query += C(", ") + tables[i];
    if (filter != EncodingT::EMPTY) {
        query += C(" WHERE ") + filter;
    }
    if (forUpdate) query += C(" FOR UPDATE ");
    if (noWait) query += C(" NOWAIT ");
    query += C(";");
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
    return prepareStatement(formatSelect(columns, tables, filter, false, nowait));
}

template <class EncodingT>
typename EncodingT::string_t 
_DataConnection<EncodingT>::formatInsert(typename EncodingT::string_t const& table,
                                         std::vector<typename EncodingT::string_t> const& columns) const
{
    //Create SQL query
    typename EncodingT::string_t query = C("INSERT INTO ");
    if (table == EncodingT::EMPTY) {
        m_logger->fatalStream() << "bad query : no table defined in INSERT query";
        throw BadSqlQueryException("no table defined in INSERT query");
    }
    query += table;
    query += C(" ( ");
    if (columns.size() == 0) {
        m_logger->fatalStream() << "bad query : no columns defined in INSERT query";
        throw BadSqlQueryException("no columns defined in INSERT query");
    }
    query += columns[0];
    for (size_t i=1; i<columns.size(); i++) query += C(", ") + columns[i];
    query += C(" ) VALUES ( ?");
    for (size_t i=1; i<columns.size(); i++) query += C(", ?");
    query += C(" );");
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
    typename EncodingT::string_t query = C("DELETE FROM ");
    if (table == EncodingT::EMPTY) {
        m_logger->fatalStream() << "bad query : no table defined in DELETE query";
        throw BadSqlQueryException("no table defined in DELETE query");
    }
    else query += table;
    if (filter != EncodingT::EMPTY) {
        query += C(" WHERE ") + filter;
    }
    query += C(";");
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
    typename EncodingT::string_t query = C("UPDATE ");
    if (table == EncodingT::EMPTY) {
        m_logger->fatalStream() << "bad query : no table defined in UPDATE query";
        throw BadSqlQueryException("no table defined in UPDATE query");
    }
    else query += table;
    query += C(" SET ");
    if (columns.size() == 0) {
        m_logger->fatalStream() << "bad query : no columns defined in UPDATE query";
        throw BadSqlQueryException("no columns defined in UPDATE query");
    }
    else query += columns[0] + C("=?");
    for (size_t i=1; i<columns.size(); i++) query += C(", ") + columns[i] + C("=?");
    if (filter != EncodingT::EMPTY) {
        query += C(" WHERE ") + filter;
    }
    query += C(";");
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

