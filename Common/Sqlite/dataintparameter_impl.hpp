
#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(data_access)

// Constructor
template <class EncodingT>
_DataIntParameter<EncodingT>::_DataIntParameter(int value)
{
	m_value = value;
    m_logger = &Category::getInstance(LOGNAME);
    m_logger->debugStream() << "creation DataIntParameter";
}

// Complete Statement
template <class EncodingT>
bool 
_DataIntParameter<EncodingT>::complete(_DataStatement<EncodingT>& statement, int index) const
{
	return statement.setInt(index, m_value);
}

NAMESPACE_END

#undef C
#undef A

