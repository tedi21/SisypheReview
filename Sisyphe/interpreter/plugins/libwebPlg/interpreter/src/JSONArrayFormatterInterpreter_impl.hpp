/*
 * JSONArrayFormatterInterpreter_impl.hpp
 *
 *
 * @date 20-10-2018
 * @author Teddy DIDE
 * @version 1.00
 */
#include "JSONArrayFormatterInterpreter.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
JSONArrayFormatterInterpreter<EncodingT>::JSONArrayFormatterInterpreter()
{
}

template <class EncodingT>
JSONArrayFormatterInterpreter<EncodingT>::JSONArrayFormatterInterpreter(const typename EncodingT::string_t& buffer)
: m_buffer(buffer)
{
}

template <class EncodingT>
typename EncodingT::string_t JSONArrayFormatterInterpreter<EncodingT>::toString() const
{
    return UCS("[") + m_buffer + UCS("]");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > JSONArrayFormatterInterpreter<EncodingT>::clone() const
{
    return boost::shared_ptr< Base<EncodingT> >(new JSONArrayFormatterInterpreter<EncodingT>(m_buffer));
}

template <class EncodingT>
typename EncodingT::string_t JSONArrayFormatterInterpreter<EncodingT>::getClassName() const
{
    return UCS("JSONArrayFormatter");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > JSONArrayFormatterInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
        if (tryInvoke(this, UCS("JSONArrayFormatter"), method, args, ret) ||
            tryInvoke(this, UCS("Base"), method, args, ret))
		{
			find_parameter(ret, FACTORY_RETURN_PARAMETER, obj);
			for (size_t i = 0; i < params.size(); ++i)
			{
				find_parameter(ret, i, params[i]);
			}
		}
		else
		{
			Category* logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "Unexpected call in JSONArrayFormatter, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > JSONArrayFormatterInterpreter<EncodingT>::getText() const
{
    return boost::make_shared< String<EncodingT> >(toString());
}

template <class EncodingT>
void JSONArrayFormatterInterpreter<EncodingT>::append(const boost::shared_ptr< Base<EncodingT> >& val)
{
    const typename EncodingT::string_t nativeText = JSONConverterInterpreter<EncodingT>::toNativeText(val);
    if (!m_buffer.empty())
    {
        m_buffer += UCS(",");
    }
    m_buffer += nativeText;
}

template <class EncodingT>
void JSONArrayFormatterInterpreter<EncodingT>::appendAsText(const boost::shared_ptr< Base<EncodingT> >& val)
{
    boost::shared_ptr< String<EncodingT> > text = dynamic_pointer_cast< String<EncodingT> >(val);
    if (text != nullptr)
    {
        const typename EncodingT::string_t nativeText = text->value();
        if (!m_buffer.empty())
        {
            m_buffer += UCS(",");
        }
        m_buffer += nativeText;
    }
    else
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "String expected, got " << A(val->getClassName());
    }
}

template <class EncodingT>
void JSONArrayFormatterInterpreter<EncodingT>::clear()
{
    m_buffer.clear();
}

NAMESPACE_END

#undef A
#undef C
