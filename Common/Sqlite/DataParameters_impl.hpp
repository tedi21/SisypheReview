#include "datablobparameter.hpp"
#include "datadoubleparameter.hpp"
#include "dataintparameter.hpp"
#include "dataint64parameter.hpp"
#include "datatextparameter.hpp"
#include "datanullparameter.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(data_access)

// Constructor
template <class EncodingT>
_DataParameters<EncodingT>::_DataParameters()
{
    m_logger = &Category::getInstance(LOGNAME);
    m_logger->debugStream() << "creation DataParameters";
}

// Fill Statement
template <class EncodingT>
bool 
_DataParameters<EncodingT>::fill(_DataStatement<EncodingT>& statement) const
{
	bool success = statement.reset();
	parameters_const_iterator itParameter;
	for (itParameter = m_parameters.begin(); itParameter != m_parameters.end() && success; ++itParameter)
	{
		success = itParameter->complete(statement, itParameter-m_parameters.begin()+1);
	}
	return success;
}

// Add Value
template <class EncodingT>
void 
_DataParameters<EncodingT>::addBlob		(const bc::vector<unsigned char>& value)
{
	m_parameters.push_back(new _DataBlobParameter<EncodingT>(value));
}

template <class EncodingT>
void 
_DataParameters<EncodingT>::addDouble	(double value)
{
	m_parameters.push_back(new _DataDoubleParameter<EncodingT>(value));
}

template <class EncodingT>
void 
_DataParameters<EncodingT>::addInt		(int value)
{
	m_parameters.push_back(new _DataIntParameter<EncodingT>(value));
}


template <class EncodingT>
void 
_DataParameters<EncodingT>::addInt64	(long long value)
{
	m_parameters.push_back(new _DataInt64Parameter<EncodingT>(value));
}

template <class EncodingT>
void 
_DataParameters<EncodingT>::addText		(const typename EncodingT::string_t& value)
{
	m_parameters.push_back(new _DataTextParameter<EncodingT>(value));
}

template <class EncodingT>
void 
_DataParameters<EncodingT>::addNull		()
{
	m_parameters.push_back(new _DataNullParameter<EncodingT>());
}

NAMESPACE_END

#undef C
#undef A

