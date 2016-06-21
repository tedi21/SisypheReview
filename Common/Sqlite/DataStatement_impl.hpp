#include "BadSqlQueryException.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(data_access)

// Private constructor
template <class EncodingT>
_DataStatement<EncodingT>::_DataStatement(sqlite3_stmt* statement)
{
	m_statement = statement;
    m_logger = &Category::getInstance(LOGNAME);
    m_logger->debugStream() << "creation DataStatement";
}

// Release statement
template <class EncodingT>
void 
_DataStatement<EncodingT>::release()
{
	if (m_statement) {
		sqlite3_finalize(m_statement);
		m_statement = NULL;
	}
}

// Constructor
template <class EncodingT>
_DataStatement<EncodingT>::_DataStatement()
{
	m_statement = NULL;
    m_logger = &Category::getInstance(LOGNAME);
    m_logger->debugStream() << "creation DataStatement";
}

// Destructor
template <class EncodingT>
_DataStatement<EncodingT>::~_DataStatement()
{
	release();
}

// Swap
template <class EncodingT>
void 
_DataStatement<EncodingT>::swap(_DataStatement& statement)
{
	sqlite3_stmt* tmp = statement.m_statement;
	statement.m_statement = m_statement;
	m_statement = tmp;
}

// Execute Query
template <class EncodingT>
bool 
_DataStatement<EncodingT>::executeStep()
{
	if (!m_statement)
	{
        m_logger->fatalStream() << "bad statement : prepared statement not initialized";
        throw BadSqlQueryException("bad statement : prepared statement not initialized");
	}
	return sqlite3_step(m_statement) == SQLITE_ROW;
}

template <class EncodingT>
bool 
_DataStatement<EncodingT>::executeQuery()
{
	if (!m_statement)
	{
        m_logger->fatalStream() << "bad statement : prepared statement not initialized";
        throw BadSqlQueryException("bad statement : prepared statement not initialized");
	}
    return sqlite3_step(m_statement) == SQLITE_DONE;
}

// Set Values
template <class EncodingT>
bool 
_DataStatement<EncodingT>::setBlob		(int index, const bc::vector<unsigned char>& value)
{
	if (!m_statement)
	{
        m_logger->fatalStream() << "bad statement : prepared statement not initialized";
        throw BadSqlQueryException("bad statement : prepared statement not initialized");
	}
	return sqlite3_bind_blob(m_statement, index, value.data(), value.size()*sizeof(unsigned char), SQLITE_TRANSIENT) == SQLITE_OK;
}

template <class EncodingT>
bool 
_DataStatement<EncodingT>::setDouble	(int index, double value)
{
	if (!m_statement)
	{
        m_logger->fatalStream() << "bad statement : prepared statement not initialized";
        throw BadSqlQueryException("bad statement : prepared statement not initialized");
	}
	return sqlite3_bind_double(m_statement, index, value) == SQLITE_OK;
}

template <class EncodingT>
bool 
_DataStatement<EncodingT>::setInt		(int index, int value)
{
	if (!m_statement)
	{
        m_logger->fatalStream() << "bad statement : prepared statement not initialized";
        throw BadSqlQueryException("bad statement : prepared statement not initialized");
	}
	return sqlite3_bind_int(m_statement, index, value) == SQLITE_OK;
}

template <class EncodingT>
bool 
_DataStatement<EncodingT>::setInt64		(int index, long long value)
{
	if (!m_statement)
	{
        m_logger->fatalStream() << "bad statement : prepared statement not initialized";
        throw BadSqlQueryException("bad statement : prepared statement not initialized");
	}
	return sqlite3_bind_int64(m_statement, index, value) == SQLITE_OK;
}

template <class EncodingT>
bool 
_DataStatement<EncodingT>::setText		(int index, const typename ucs::string_t& value)
{
	if (!m_statement)
	{
        m_logger->fatalStream() << "bad statement : prepared statement not initialized";
        throw BadSqlQueryException("bad statement : prepared statement not initialized");
	}
	return sqlite3_bind_text16(m_statement, index, value.c_str(), -1, SQLITE_TRANSIENT) == SQLITE_OK;
}

template <class EncodingT>
bool 
_DataStatement<EncodingT>::setText		(int index, const typename ansi::string_t& value)
{
	if (!m_statement)
	{
        m_logger->fatalStream() << "bad statement : prepared statement not initialized";
        throw BadSqlQueryException("bad statement : prepared statement not initialized");
	}
	return sqlite3_bind_text(m_statement, index, value.c_str(), -1, SQLITE_TRANSIENT) == SQLITE_OK;
}

// Get Value
template <class EncodingT>
bool 
_DataStatement<EncodingT>::getBlob		(int column, bc::vector<unsigned char>& value) const
{
	if (!m_statement)
	{
        m_logger->fatalStream() << "bad statement : prepared statement not initialized";
        throw BadSqlQueryException("bad statement : prepared statement not initialized");
	}
	const unsigned char* ptr = (const unsigned char*) sqlite3_column_blob(m_statement, column);
	size_t n = sqlite3_column_bytes(m_statement, column);
	value.assign(ptr, ptr+n);
	return true;
}

template <class EncodingT>
bool 
_DataStatement<EncodingT>::getDouble	(int column, double& value) const
{
	if (!m_statement)
	{
        m_logger->fatalStream() << "bad statement : prepared statement not initialized";
        throw BadSqlQueryException("bad statement : prepared statement not initialized");
	}
	value = sqlite3_column_double(m_statement, column);
	return true;
}

template <class EncodingT>
bool 
_DataStatement<EncodingT>::getInt		(int column, int& value) const
{
	if (!m_statement)
	{
        m_logger->fatalStream() << "bad statement : prepared statement not initialized";
        throw BadSqlQueryException("bad statement : prepared statement not initialized");
	}
	value = sqlite3_column_int(m_statement, column);
	return true;
}

template <class EncodingT>
bool 
_DataStatement<EncodingT>::getInt64		(int column, long long& value) const
{
	if (!m_statement)
	{
        m_logger->fatalStream() << "bad statement : prepared statement not initialized";
        throw BadSqlQueryException("bad statement : prepared statement not initialized");
	}
	value = sqlite3_column_int64(m_statement, column);
	return true;
}

template <class EncodingT>
bool 
_DataStatement<EncodingT>::getText		(int column, typename ucs::string_t& value) const
{
	if (!m_statement)
	{
        m_logger->fatalStream() << "bad statement : prepared statement not initialized";
        throw BadSqlQueryException("bad statement : prepared statement not initialized");
	}
	value = (const wchar_t*) sqlite3_column_text16(m_statement, column);
	return true;
}

template <class EncodingT>
bool 
_DataStatement<EncodingT>::getText		(int column, typename ansi::string_t& value) const
{
	if (!m_statement)
	{
        m_logger->fatalStream() << "bad statement : prepared statement not initialized";
        throw BadSqlQueryException("bad statement : prepared statement not initialized");
	}
	value = (const char*) sqlite3_column_text(m_statement, column);
	return true;
}

NAMESPACE_END

#undef C
#undef A

