/*
 * JSONStructureFormatterInterpreter_impl.hpp
 *
 *
 * @date 20-10-2018
 * @author Teddy DIDE
 * @version 1.00
 */
#include "JSONStructureFormatterInterpreter.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
JSONStructureFormatterInterpreter<EncodingT>::JSONStructureFormatterInterpreter()
{
}

template <class EncodingT>
JSONStructureFormatterInterpreter<EncodingT>::JSONStructureFormatterInterpreter(const typename EncodingT::string_t& buffer)
: m_buffer(buffer)
{
}

template <class EncodingT>
typename EncodingT::string_t JSONStructureFormatterInterpreter<EncodingT>::toString() const
{
    return C("{") + m_buffer + C("}");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > JSONStructureFormatterInterpreter<EncodingT>::clone() const
{
    return boost::shared_ptr< Base<EncodingT> >(new JSONStructureFormatterInterpreter<EncodingT>(m_buffer));
}

template <class EncodingT>
typename EncodingT::string_t JSONStructureFormatterInterpreter<EncodingT>::getClassName() const
{
    return C("JSONStructureFormatter");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > JSONStructureFormatterInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
    ParameterArray args, ret;
    if (check_parameters_array(params, args))
	{
        if (tryInvoke(this, C("JSONStructureFormatter"), method, args, ret) ||
			tryInvoke(this, C("Base"), method, args, ret))
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
            logger->errorStream() << "Unexpected call in JSONStructureFormatter, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > JSONStructureFormatterInterpreter<EncodingT>::getText() const
{
    return boost::make_shared< String<EncodingT> >(toString());
}

template <class EncodingT>
void JSONStructureFormatterInterpreter<EncodingT>::append(const boost::shared_ptr< Base<EncodingT> >& name, const boost::shared_ptr< Base<EncodingT> >& val)
{
    boost::shared_ptr< String<EncodingT> > str = dynamic_pointer_cast< String<EncodingT> >(name);
    if (str != nullptr)
    {
        const typename EncodingT::string_t nativeText = JSONConverterInterpreter<EncodingT>::toNativeText(val);
        if (!m_buffer.empty())
        {
            m_buffer += C(",");
        }
        m_buffer += C("\"") + str->value() + C("\":") + nativeText;
    }
    else
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "String expected, got " << A(name->getClassName());
    }
}

template <class EncodingT>
void JSONStructureFormatterInterpreter<EncodingT>::appendAsText(const boost::shared_ptr< Base<EncodingT> >& name, const boost::shared_ptr< Base<EncodingT> >& val)
{
    boost::shared_ptr< String<EncodingT> > str = dynamic_pointer_cast< String<EncodingT> >(name);
    boost::shared_ptr< String<EncodingT> > text = dynamic_pointer_cast< String<EncodingT> >(val);
    if (str != nullptr && text != nullptr)
    {
        const typename EncodingT::string_t nativeText = text->value();
        if (!m_buffer.empty())
        {
            m_buffer += C(",");
        }
        m_buffer += C("\"") + str->value() + C("\":") + nativeText;
    }
    else
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "String, String expected, got " << A(name->getClassName()) << ", " << A(val->getClassName());
    }
}

template <class EncodingT>
void JSONStructureFormatterInterpreter<EncodingT>::clear()
{
    m_buffer.clear();
}

NAMESPACE_END

#undef A
#undef C
