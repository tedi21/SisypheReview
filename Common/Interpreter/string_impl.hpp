#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>
#include "Array.hpp"
#include "Match.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    String<EncodingT>::String()
    {
        m_value = EncodingT::EMPTY;
    }

    template <class EncodingT>
    String<EncodingT>::String(typename EncodingT::string_t const& value)
    {
        m_value = value;
    }

    template <class EncodingT>
    String<EncodingT>::String(typename EncodingT::char_t const& value)
    {
        m_value = typename EncodingT::string_t(value);
    }

    template <class EncodingT>
    String<EncodingT>::String(boost::shared_ptr< Base<EncodingT> > const& value)
    {
        typename EncodingT::string_t str;
        double size;
        if (check_numeric(value, size))
        {
            m_value.reserve((size_t) size);
        }
        else if (check_string<EncodingT>(value, str))
        {
            m_value = str;
        }
    }

    template <class EncodingT>
    String<EncodingT>::~String()
    {}

    template <class EncodingT>
    typename EncodingT::string_t const& String<EncodingT>::getValue() const
    {
        return m_value;
    }
	
    template <class EncodingT>
    void String<EncodingT>::setValue(typename EncodingT::string_t const& value)
    {
        m_value = value;
    }

    template <class EncodingT>
    typename EncodingT::string_t String<EncodingT>::toString() const
    {
        return m_value;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::clone() const
    {
        return boost::shared_ptr< Base<EncodingT> >(new String<EncodingT>(m_value));
    }

    template <class EncodingT>
    typename EncodingT::string_t String<EncodingT>::getClassName() const
    {
        return C("String");
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
    {
        boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
        
        ParameterArray args, ret;
        if (check_parameters_array(params, args))
        {
            if (tryInvoke(this, C("String"), method, args, ret))
            {
                find_parameter(ret, FACTORY_RETURN_PARAMETER, obj);
                for (size_t i = 0; i < params.size(); ++i)
                {
                    find_parameter(ret, i, params[i]);
                }
            }
            else
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << "Unexpected call in String, no method \"" << A(method) << "\" exists.";
            }
        }
        return obj;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::concat(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new String<EncodingT>);
        typename EncodingT::string_t str;     
        if (check_string<EncodingT>(val, str))
        {
            res.reset(new String<EncodingT>(toString() + str));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::inferior(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>);
        typename EncodingT::string_t str;
        if (check_string<EncodingT>(val, str))
        {
            res.reset(new Bool<EncodingT>(m_value < str));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::inferiorOrEqual(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>);
        typename EncodingT::string_t str;
        if (check_string<EncodingT>(val, str))
        {
            res.reset(new Bool<EncodingT>(m_value <= str));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::superior(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>);
        typename EncodingT::string_t str;
        if (check_string<EncodingT>(val, str))
        {
            res.reset(new Bool<EncodingT>(m_value > str));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::superiorOrEqual(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>);
        typename EncodingT::string_t str;
        if (check_string<EncodingT>(val, str))
        {
            res.reset(new Bool<EncodingT>(m_value >= str));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::equals(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>);
        typename EncodingT::string_t str;     
        if (check_string<EncodingT>(val, str))
        {
            res.reset(new Bool<EncodingT>(boost::equals(toString(), str)));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::iequals(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>);
        typename EncodingT::string_t str;
        if (check_string<EncodingT>(val, str))
        {
            res.reset(new Bool<EncodingT>(boost::iequals(toString(), str)));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::size() const
    {
        return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(toString().size()));
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::notEquals(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>);
        typename EncodingT::string_t str;     
        if (check_string<EncodingT>(val, str))
        {
            res.reset(new Bool<EncodingT>(!boost::equals(toString(), str)));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::notIEquals(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>);
        typename EncodingT::string_t str;
        if (check_string<EncodingT>(val, str))
        {
            res.reset(new Bool<EncodingT>(!boost::iequals(toString(), str)));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::match(boost::shared_ptr< Base<EncodingT> > const& regex, boost::shared_ptr< Base<EncodingT> >& matches) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>(false));
        typename EncodingT::string_t nativeRegex;
        if (check_string<EncodingT>(regex, nativeRegex))
        {
            try
            {
                typedef boost::basic_regex<typename EncodingT::char_t>   regex_t;
                regex_t regexPattern(nativeRegex);
                typename Match<EncodingT>::match_t what;
                const typename EncodingT::string_t& str = m_value;
                bool match = boost::regex_match(str, what, regexPattern);
                res.reset(new Bool<EncodingT>(match));

                if (!what.empty())
                {
                    boost::shared_ptr< Match<EncodingT> > matchesObj = dynamic_pointer_cast< Match<EncodingT> >(matches);
                    if (matchesObj)
                    {
                        matchesObj->setValue(what);
                    }
                    else
                    {
                        Category * logger = &Category::getInstance(LOGNAME);
                        logger->errorStream() << "Match expected, got " << A(matches->getClassName());
                    }
                }
            }
            catch (boost::regex_error& re)
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << re.what();
            }
            catch (std::exception& ex)
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << ex.what();
            }
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::split(boost::shared_ptr< Base<EncodingT> > const& regex) const
    {
        boost::shared_ptr< Array<EncodingT> > res(new Array<EncodingT>());
        typename EncodingT::string_t nativeRegex;
        if (check_string<EncodingT>(regex, nativeRegex))
        {
            try
            {
                typedef boost::basic_regex<typename EncodingT::char_t>   regex_t;
                regex_t regexPattern(nativeRegex);
                std::vector<std::wstring> substring;
                boost::algorithm::split_regex(substring, toString(), regexPattern);

                if (!substring.empty())
                {
                    for (size_t i=0; i < substring.size(); i++)
                    {
                        res->addValue(boost::shared_ptr< Base<EncodingT> >(new String<EncodingT>(substring[i])));
                    }
                }
            }
            catch (boost::regex_error& re)
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << re.what();
            }
            catch (std::exception& ex)
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << ex.what();
            }
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::search(
            boost::shared_ptr< Base<EncodingT> > const& start, boost::shared_ptr< Base<EncodingT> > const& end,
            boost::shared_ptr< Base<EncodingT> > const& regex, boost::shared_ptr< Base<EncodingT> >& matches, boost::shared_ptr< Base<EncodingT> >& next) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new Bool<EncodingT>(false));
        next = end->clone();
        typename EncodingT::string_t nativeRegex;
        double nativeStart, nativeEnd;
        if (check_string<EncodingT>(regex, nativeRegex)  &&
            check_numeric(start, nativeStart) &&
            check_numeric(end, nativeEnd))
        {
            try
            {
                typedef boost::basic_regex<typename EncodingT::char_t>   regex_t;
                regex_t regexPattern(nativeRegex);
                typename Match<EncodingT>::match_t what;
                const typename EncodingT::string_t& str = m_value;
                bool match = boost::regex_search(str.begin()+nativeStart, str.begin()+nativeEnd, what, regexPattern);
                res.reset(new Bool<EncodingT>(match));

                if (match && !what.empty())
                {
                    boost::shared_ptr< Match<EncodingT> > matchesObj = dynamic_pointer_cast< Match<EncodingT> >(matches);
                    if (matchesObj)
                    {
                        matchesObj->setValue(what, nativeStart);
                    }
                    else
                    {
                        Category * logger = &Category::getInstance(LOGNAME);
                        logger->errorStream() << "Match expected, got " << A(matches->getClassName());
                    }

                    boost::shared_ptr< Numeric<EncodingT> > nextObj = dynamic_pointer_cast< Numeric<EncodingT> >(next);
                    if (nextObj)
                    {
                        nextObj->setValue(what[0].second - str.begin());
                    }
                    else
                    {
                        Category * logger = &Category::getInstance(LOGNAME);
                        logger->errorStream() << "Numeric expected, got " << A(next->getClassName());
                    }
                }
            }
            catch (boost::regex_error& re)
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << re.what();
            }
            catch (std::exception& ex)
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << ex.what();
            }
        }
        return res;
    }

    template <class EncodingT>
    void String<EncodingT>::append(boost::shared_ptr< Base<EncodingT> > const& val)
    {
        typename EncodingT::string_t str;
        if (check_string<EncodingT>(val, str))
        {
            m_value.append(str);
        }
    }

    template <class EncodingT>
    void String<EncodingT>::insert(boost::shared_ptr< Base<EncodingT> > const& pos, boost::shared_ptr< Base<EncodingT> > const& val)
    {
        typename EncodingT::string_t nativeStr;
        double nativePos;
        if (   check_numeric(pos, nativePos)
            && check_string<EncodingT>(val, nativeStr))
        {
            m_value.insert(nativePos, nativeStr);
        }
    }

    template <class EncodingT>
    void String<EncodingT>::remove(boost::shared_ptr< Base<EncodingT> > const& pos, boost::shared_ptr< Base<EncodingT> > const& len)
    {
        double nativePos, nativeLen;
        if (   check_numeric(pos, nativePos)
            && check_numeric(len, nativeLen))
        {
            m_value.erase(nativePos, nativeLen);
        }
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::substring(boost::shared_ptr< Base<EncodingT> > const& pos, boost::shared_ptr< Base<EncodingT> > const& len) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new String<EncodingT>());
        double nativePos, nativeLen;
        if (   check_numeric(pos, nativePos)
            && check_numeric(len, nativeLen))
        {
            res.reset(new String<EncodingT>(toString().substr(nativePos, nativeLen)));
        }
        return res;
    }

    template <class EncodingT2, class EncodingT>
    bool check_string(boost::shared_ptr< Base<EncodingT> > const& val, typename EncodingT2::string_t& n)
    {
        n = encode<EncodingT,EncodingT2>(val->toString());
        return true;
    }

    template <class EncodingT2, class EncodingT>
    bool check_char(boost::shared_ptr< Base<EncodingT> > const& val, typename EncodingT2::char_t& n)
    {
        typename EncodingT::string_t tmp = val->toString();
        if (tmp.size() > 0)
        {
            n = (typename EncodingT2::char_t) tmp[0];
        }
        return tmp.size() > 0;
    }

    template <class EncodingT2, class EncodingT>
    bool reset_string(boost::shared_ptr< Base<EncodingT> >& val, typename EncodingT2::string_t const& n)
    {
        boost::shared_ptr< String<EncodingT> > value  = dynamic_pointer_cast< String<EncodingT> >(val);
        if (value)
        {
            value->setValue(encode<EncodingT2,EncodingT>(n));
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "String expected, got " << A(val->getClassName());
        }
        return (value != NULL);
    }

NAMESPACE_END

#undef C
#undef A
