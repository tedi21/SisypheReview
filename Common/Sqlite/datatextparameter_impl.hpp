
#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(data_access)

// Constructor
template <class EncodingT>
_DataTextParameter<EncodingT>::_DataTextParameter(const typename EncodingT::string_t& value)
{
	m_value = value;
    m_logger = &Category::getInstance(LOGNAME);
    m_logger->debugStream() << "creation DataTextParameter";
}

// Complete Statement
template <class EncodingT>
bool 
_DataTextParameter<EncodingT>::complete(_DataStatement<EncodingT>& statement, int index) const
{
	return statement.setText(index, m_value);
}

NAMESPACE_END

#undef C
#undef A

