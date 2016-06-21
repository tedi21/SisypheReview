
#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(data_access)

// Constructor
template <class EncodingT>
_DataBlobParameter<EncodingT>::_DataBlobParameter(const bc::vector<unsigned char>& value)
{
	m_value = value;
    m_logger = &Category::getInstance(LOGNAME);
    m_logger->debugStream() << "creation DataBlobParameter";
}

// Complete Statement
template <class EncodingT>
bool 
_DataBlobParameter<EncodingT>::complete(_DataStatement<EncodingT>& statement, int index) const
{
	return statement.setBlob(index, m_value);
}

NAMESPACE_END

#undef C
#undef A

