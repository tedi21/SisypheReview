
#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(data_access)

// Constructor
template <class EncodingT>
_DataNullParameter<EncodingT>::_DataNullParameter()
{
    m_logger = &Category::getInstance(LOGNAME);
    m_logger->debugStream() << "creation DataNullParameter";
}

// Complete Statement
template <class EncodingT>
bool 
_DataNullParameter<EncodingT>::complete(_DataStatement<EncodingT>& statement, int index) const
{
	return statement.setNull(index);
}

NAMESPACE_END

#undef C
#undef A

