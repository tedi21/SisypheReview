/*
 * JSONConverterInterpreter_impl.hpp
 *
 *
 * @date 20-10-2018
 * @author Teddy DIDE
 * @version 1.00
 */
#include <boost/algorithm/string/replace.hpp>
#include "String.hpp"
#include "Array.hpp"
#include "Structure.hpp"
#include "Numeric.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

template <class EncodingT>
typename EncodingT::string_t JSONConverterInterpreter<EncodingT>::escapeChar(const typename EncodingT::string_t& str)
{
    typename EncodingT::string_t res = str;
    boost::algorithm::replace_all(res, "\\", "\\\\");
    boost::algorithm::replace_all(res, "\"", "\\\"");
    boost::algorithm::replace_all(res, "\r", "\\r");
    boost::algorithm::replace_all(res, "\n", "\\n");
    boost::algorithm::replace_all(res, "\t", "\\t");
    return res;
}

template <class EncodingT>
typename EncodingT::string_t JSONConverterInterpreter<EncodingT>::unEscapeChar(const typename EncodingT::string_t& str)
{
    typename EncodingT::string_t res = str;
    boost::algorithm::replace_all(res, "\\\"", "\"");
    boost::algorithm::replace_all(res, "\\r", "\r");
    boost::algorithm::replace_all(res, "\\n", "\n");
    boost::algorithm::replace_all(res, "\\t", "\t");
    boost::algorithm::replace_all(res, "\\\\", "\\");
    return res;
}

template <class EncodingT>
typename EncodingT::string_t JSONConverterInterpreter<EncodingT>::shrinkText(const typename EncodingT::string_t& str)
{
    size_t i = 0, j = str.size() - 1;
    while (i <= j && (str[i] == ' ' || str[i] == '\t' || str[i] == '\r' || str[i] == '\n')) ++i;
    while (j > i && (str[j] == ' ' || str[j] == '\t' || str[j] == '\r' || str[j] == '\n')) --j;

    typename EncodingT::string_t res;
    if (i < j)
    {
        res = str.substr(i, (j + 1) - i);
    }
    return res;
}

template <class EncodingT>
size_t JSONConverterInterpreter<EncodingT>::findChar(const typename EncodingT::string_t& str, const typename EncodingT::char_t& ch, size_t start)
{
    bool inString = false;
    bool escaping = false;
    size_t inArray = 0U;
    size_t inStructure = 0U;
    size_t res = start;
    while ((res < str.size()) && (inString || (inArray > 0U) || (inStructure > 0U) || (str[res] != ch)))
    {
        inString = (inString != ((str[res] == '"') && !escaping));
        escaping = (str[res] == '\\') && !escaping;
        if (!inString && (str[res] == '['))
        {
          ++inArray;
        }
        else if (!inString && (str[res] == ']'))
        {
           --inArray;
        }
        else if (!inString && (str[res] == '{'))
        {
          ++inStructure;
        }
        else if (!inString && (str[res] == '}'))
        {
           --inStructure;
        }
        ++res;
    }
    return res;
}

template <class EncodingT>
typename EncodingT::string_t JSONConverterInterpreter<EncodingT>::toNativeText(const boost::shared_ptr< Base<EncodingT> >& object)
{
    typename EncodingT::string_t result;
    boost::shared_ptr< Numeric<EncodingT> > num;
    boost::shared_ptr< String<EncodingT> > str;
    boost::shared_ptr< Array<EncodingT> > arr;
    boost::shared_ptr< Structure<EncodingT> > st;
    if ((num  = dynamic_pointer_cast< Numeric<EncodingT> >(object)) != nullptr)
    {
        result = num->toString();
    }
    else if ((str  = dynamic_pointer_cast< String<EncodingT> >(object)) != nullptr)
    {
        result = UCS("\"") + escapeChar(str->value()) + UCS("\"");
    }
    else if ((arr  = dynamic_pointer_cast< Array<EncodingT> >(object)) != nullptr)
    {
        size_t lg = arr->length();
        result = UCS("[");
        for (size_t i = 0; i < lg; ++i)
        {
            result += toNativeText(arr->valueAt(i));
            if (i != lg-1)
            {
                result += UCS(",");
            }
        }
        result += UCS("]");
    }
    else if ((st  = dynamic_pointer_cast< Structure<EncodingT> >(object)) != nullptr)
    {
        size_t lg = st->getFieldsCount();
        result = UCS("{");
        for (size_t i = 0; i < lg; ++i)
        {
            auto pairIterator = st->getField(i);
            result += UCS("\"") + pairIterator->first + UCS("\":") + toNativeText(pairIterator->second);
            if (i != lg-1)
            {
                result += UCS(",");
            }
        }
        result += UCS("}");
    }
    else
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "Numeric, String, Array or Structure expected, got " << A(object->getClassName());
    }
    return result;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > JSONConverterInterpreter<EncodingT>::fromNativeText(const typename EncodingT::string_t& nativeText)
{
    boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
    long long llvalue;
    double dvalue;
    if ((nativeText.size() >= 2U) && (nativeText.front() == '{') && (nativeText.back() == '}'))
    {
        Structure<EncodingT>* st = new Structure<EncodingT>();
        typename EncodingT::string_t content = shrinkText(nativeText.substr(1U, nativeText.size() - 2U));
        if (!content.empty())
        {
            size_t parsed = 0U;
            while (parsed < content.size())
            {
                size_t i = findChar(content, ':', parsed);
                if (i < content.size())
                {
                    size_t j = findChar(content, ',', i);
                    typename EncodingT::string_t fieldstr = shrinkText(content.substr(parsed, i - parsed));
                    if (fieldstr.size() >= 2U)
                    {
                        typename EncodingT::string_t fieldName = fieldstr.substr(1U, fieldstr.size() - 2U);
                        boost::shared_ptr< Base<EncodingT> > fieldValue = fromNativeText(content.substr(i + 1U, j - (i + 1U)));
                        st->insertField(fieldName, fieldValue);
                    }
                    else
                    {
                        parsed = i;
                        Category * logger = &Category::getInstance(LOGNAME);
                        logger->errorStream() << "Unrecognized JSON text : " << A(fieldstr);
                    }
                    if (j < content.size())
                    {
                        parsed = j + 1U;
                    }
                    else
                    {
                        parsed = j;
                    }
                }
                else
                {
                    parsed = i;
                    Category * logger = &Category::getInstance(LOGNAME);
                    logger->errorStream() << "Unrecognized JSON text : " << A(content);
                }
            }
        }
        obj.reset(st);
    }
    else if ((nativeText.size() >= 2U) && (nativeText.front() == '[') && (nativeText.back() == ']'))
    {
        Array<EncodingT>* arr = new Array<EncodingT>();
        typename EncodingT::string_t content = shrinkText(nativeText.substr(1U, nativeText.size()-2U));
        if (!content.empty())
        {
            size_t parsed = 0U;
            while (parsed < content.size())
            {
                size_t i = findChar(content, ',', parsed);
                boost::shared_ptr< Base<EncodingT> > fieldValue = fromNativeText(content.substr(parsed, i - parsed));
                arr->addValue(fieldValue);
                if (i < content.size())
                {
                    parsed = i + 1U;
                }
                else
                {
                    parsed = i;
                }
            }
        }
        obj.reset(arr);
    }
    else if ((nativeText.size() >= 2U) && (nativeText.front() == '"') && (nativeText.back() == '"'))
    {
        obj.reset(new String<EncodingT>(unEscapeChar(nativeText.substr(1U, nativeText.size()-2U))));
    }
    else if (Convert<long long>::try_parse(nativeText, llvalue))
    {
        obj.reset(new Numeric<EncodingT>(llvalue));
    }
    else if (Convert<double>::try_parse(nativeText, dvalue))
    {
        obj.reset(new Numeric<EncodingT>(dvalue));
    }
    else
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "Unrecognized JSON text : " << A(nativeText);
    }
    return obj;
}


template <class EncodingT>
JSONConverterInterpreter<EncodingT>::JSONConverterInterpreter()
{
}

template <class EncodingT>
typename EncodingT::string_t JSONConverterInterpreter<EncodingT>::toString() const
{
	return EncodingT::EMPTY;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > JSONConverterInterpreter<EncodingT>::clone() const
{
    return boost::shared_ptr< Base<EncodingT> >(new JSONConverterInterpreter<EncodingT>());
}

template <class EncodingT>
typename EncodingT::string_t JSONConverterInterpreter<EncodingT>::getClassName() const
{
    return UCS("JSONConverter");
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > JSONConverterInterpreter<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
{
	boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
	ParameterArray args, ret;
	if (check_parameters_array(params, args))
	{
        if (tryInvoke(this, UCS("JSONConverter"), method, args, ret) ||
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
            logger->errorStream() << "Unexpected call in JSONConverter, no method \"" << A(method) << "\" exists.";
		}
	}
	return obj;
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > JSONConverterInterpreter<EncodingT>::toText(const boost::shared_ptr< Base<EncodingT> >& object) const
{
    return boost::make_shared< String<EncodingT> >(toNativeText(object));
}

template <class EncodingT>
boost::shared_ptr< Base<EncodingT> > JSONConverterInterpreter<EncodingT>::fromText(const boost::shared_ptr< Base<EncodingT> >& text) const
{
    boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
    boost::shared_ptr< String<EncodingT> > str = dynamic_pointer_cast< String<EncodingT> >(text);
    if (str != nullptr)
    {
        typename EncodingT::string_t nativeText = shrinkText(str->value());
        obj = fromNativeText(nativeText);
    }
    else
    {
        Category * logger = &Category::getInstance(LOGNAME);
        logger->errorStream() << "String expected, got " << A(text->getClassName());
    }
    return obj;
}

NAMESPACE_END

#undef A
#undef C
