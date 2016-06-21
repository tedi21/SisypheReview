
#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(data_access)

// Constructor
template <class EncodingT>
_DataDoubleParameter<EncodingT>::_DataDoubleParameter(double value)
{
	m_value = value;
    m_logger = &Category::getInstance(LOGNAME);
    m_logger->debugStream() << "creation DataDoubleParameter";
}

// Complete Statement
template <class EncodingT>
bool 
_DataDoubleParameter<EncodingT>::complete(_DataStatement<EncodingT>& statement, int index) const
{
	return statement.setDouble(index, m_value);
}

NAMESPACE_END

#undef C
#undef A

