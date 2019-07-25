
#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(data_access)

// Constructor
template <class EncodingT>
_DataInt64Parameter<EncodingT>::_DataInt64Parameter(long long value)
{
    m_value = value;
    m_logger = &Category::getInstance(LOGNAME);
    m_logger->debugStream() << "creation DataInt64Parameter";
}

// Complete Statement
template <class EncodingT>
bool 
_DataInt64Parameter<EncodingT>::complete(_DataStatement<EncodingT>& statement, int index) const
{
	return statement.setInt64(index, m_value);
}

NAMESPACE_END

#undef C
#undef A

