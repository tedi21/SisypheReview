#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/algorithm/string/replace.hpp>
#include "Array.hpp"
#include "Match.hpp"
#include "Regex.hpp"

#define A(str) encode<EncodingT,ansi>(str)

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
        m_value = typename EncodingT::string_t(1, value);
    }

    template <class EncodingT>
    String<EncodingT>::String(boost::shared_ptr< Base<EncodingT> > const& value)
    {
        typename EncodingT::string_t str;
        size_t size;
        if (check_numeric_i(value, size))
        {
            m_value.reserve(size);
        }
        else if (check_string<EncodingT>(value, str))
        {
            m_value = str;
        }
    }

    template <class EncodingT>
    typename EncodingT::string_t const& String<EncodingT>::value() const
    {
        return m_value;
    }
	
    template <class EncodingT>
    void String<EncodingT>::value(typename EncodingT::string_t const& value)
    {
        m_value = value;
    }
    
    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::valueAt(size_t i) const
    {
        return boost::make_shared< String<EncodingT> >(m_value[i]);
    }
    
    template <class EncodingT>
    size_t String<EncodingT>::length() const
    {
        return m_value.size();
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
        return UCS("String");
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
    {
        boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
        
        ParameterArray args, ret;
        if (check_parameters_array(params, args))
        {
            if (tryInvoke(this, UCS("String"), method, args, ret) ||
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
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << "Unexpected call in String, no method \"" << A(method) << "\" exists.";
            }
        }
        return obj;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::concat(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< String<EncodingT> > res(new String<EncodingT>);
        typename EncodingT::string_t str;     
        if (check_string<EncodingT>(val, str))
        {
            res->value(m_value + str);
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::inferior(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>);
        typename EncodingT::string_t str;
        if (check_string<EncodingT>(val, str))
        {
            res->value(m_value < str);
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::inferiorOrEqual(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>);
        typename EncodingT::string_t str;
        if (check_string<EncodingT>(val, str))
        {
            res->value(m_value <= str);
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::superior(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>);
        typename EncodingT::string_t str;
        if (check_string<EncodingT>(val, str))
        {
            res->value(m_value > str);
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::superiorOrEqual(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>);
        typename EncodingT::string_t str;
        if (check_string<EncodingT>(val, str))
        {
            res->value(m_value >= str);
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::equals(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>);
        typename EncodingT::string_t str;     
        if (check_string<EncodingT>(val, str))
        {
            res->value(boost::equals(m_value, str));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::iequals(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>);
        typename EncodingT::string_t str;
        if (check_string<EncodingT>(val, str))
        {
            res->value(boost::iequals(m_value, str));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::size() const
    {
        return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_value.size()));
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::notEquals(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>);
        typename EncodingT::string_t str;     
        if (check_string<EncodingT>(val, str))
        {
            res->value(!boost::equals(m_value, str));
        }
        return res;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::notIEquals(boost::shared_ptr< Base<EncodingT> > const& val) const
    {
        boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>);
        typename EncodingT::string_t str;
        if (check_string<EncodingT>(val, str))
        {
            res->value(!boost::iequals(m_value, str));
        }
        return res;
    }
    
    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::getValue(boost::shared_ptr< Base<EncodingT> > const& i) const
    {
        return this->substring(i, boost::shared_ptr< Numeric<EncodingT> >(new Numeric<EncodingT>(1)));
    }
    
    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::getList(boost::shared_ptr< Base<EncodingT> > const& i1, boost::shared_ptr< Base<EncodingT> > const& i2) const
    {
        boost::shared_ptr< Base<EncodingT> > res(new String<EncodingT>());
        boost::shared_ptr< Numeric<EncodingT> > ii2  = dynamic_pointer_cast< Numeric<EncodingT> >(i2);
        if (ii2)
        {
            res = this->substring(i1, boost::shared_ptr< Numeric<EncodingT> >(new Numeric<EncodingT>(1))->plus(ii2->minus(i1)));
        }
        return res;
    }
    
    
    template <class EncodingT>
    void String<EncodingT>::addValue(boost::shared_ptr< Base<EncodingT> > const& val)
    {
        this->append(val);
    }

    template <class EncodingT>
    void String<EncodingT>::insertValue(boost::shared_ptr< Base<EncodingT> > const& i, boost::shared_ptr< Base<EncodingT> > const& val)
    {
        this->insert(i, val);
    }
    
    template <class EncodingT>
    void String<EncodingT>::insertList(boost::shared_ptr< Base<EncodingT> > const& i1, boost::shared_ptr< Base<EncodingT> > const& i2, boost::shared_ptr< Base<EncodingT> > const& val)
    {
        boost::shared_ptr< String<EncodingT> > value  = dynamic_pointer_cast< String<EncodingT> >(val);
        boost::shared_ptr< Numeric<EncodingT> > ii2  = dynamic_pointer_cast< Numeric<EncodingT> >(i2);
        if (value && ii2)
        {
            this->insert(i1, value->substring(boost::shared_ptr< Numeric<EncodingT> >(new Numeric<EncodingT>(0)), boost::shared_ptr< Numeric<EncodingT> >(new Numeric<EncodingT>(1))->plus(ii2->minus(i1))));
        }
    }

    template <class EncodingT>
    void String<EncodingT>::removeValue(boost::shared_ptr< Base<EncodingT> > const& i)
    {
        this->remove(i, boost::shared_ptr< Numeric<EncodingT> >(new Numeric<EncodingT>(1)));
    }
    
    template <class EncodingT>
    void String<EncodingT>::removeList(boost::shared_ptr< Base<EncodingT> > const& i1, boost::shared_ptr< Base<EncodingT> > const& i2)
    {
        boost::shared_ptr< Numeric<EncodingT> > ii2  = dynamic_pointer_cast< Numeric<EncodingT> >(i2);
        if (ii2)
        {
            this->remove(i1, boost::shared_ptr< Numeric<EncodingT> >(new Numeric<EncodingT>(1))->plus(ii2->minus(i1)));
        }
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::match(boost::shared_ptr< Base<EncodingT> > const& regex, boost::shared_ptr< Base<EncodingT> >& matches) const
    {
        boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>(false));
        typedef boost::basic_regex<typename EncodingT::char_t>   regex_t;
        regex_t regexPattern;
        if (check_regex<EncodingT>(regex, regexPattern))
        {
            try
            {
                typename Match<EncodingT>::match_t what;
                const typename EncodingT::string_t& str = m_value;
                bool match = boost::regex_match(str, what, regexPattern);
                res->value(match);

                if (!what.empty())
                {
                    boost::shared_ptr< Match<EncodingT> > matchesObj = dynamic_pointer_cast< Match<EncodingT> >(matches);
                    if (matchesObj)
                    {
                        matchesObj->value(what);
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
        typedef boost::basic_regex<typename EncodingT::char_t>   regex_t;
        regex_t regexPattern;
        if (check_regex<EncodingT>(regex, regexPattern))
        {
            try
            {
                std::vector<typename EncodingT::string_t> substring;
                const typename EncodingT::string_t& str = m_value;
                boost::algorithm::split_regex(substring, str, regexPattern);

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
        boost::shared_ptr< Bool<EncodingT> > res(new Bool<EncodingT>(false));
        next = end->clone();
        typedef boost::basic_regex<typename EncodingT::char_t>   regex_t;
        regex_t regexPattern;
        size_t nativeStart, nativeEnd;
        if (check_regex<EncodingT>(regex, regexPattern) &&
            check_numeric_i(start, nativeStart) &&
            check_numeric_i(end, nativeEnd) &&
            nativeStart < m_value.size() &&
            nativeStart < nativeEnd &&
            nativeEnd <= m_value.size())
        {
            try
            {
                typename Match<EncodingT>::match_t what;
                const typename EncodingT::string_t& str = m_value;
                bool match = boost::regex_search(str.begin()+nativeStart, str.begin()+nativeEnd, what, regexPattern);
                res->value(match);

                if (match && !what.empty())
                {
                    boost::shared_ptr< Match<EncodingT> > matchesObj = dynamic_pointer_cast< Match<EncodingT> >(matches);
                    if (matchesObj)
                    {
                        matchesObj->value(what, nativeStart);
                    }
                    else
                    {
                        Category * logger = &Category::getInstance(LOGNAME);
                        logger->errorStream() << "Match expected, got " << A(matches->getClassName());
                    }

                    boost::shared_ptr< Numeric<EncodingT> > nextObj = dynamic_pointer_cast< Numeric<EncodingT> >(next);
                    if (nextObj)
                    {
                        nextObj->LLvalue(what[0].second - str.begin());
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
    void String<EncodingT>::replaceAll(boost::shared_ptr< Base<EncodingT> > const& search, boost::shared_ptr< Base<EncodingT> > const& replace)
    {
        typename EncodingT::string_t nativeSearch, nativeReplace;
        if (check_string<EncodingT>(search, nativeSearch) &&
            check_string<EncodingT>(replace, nativeReplace))
        {
            try
            {
                typename EncodingT::string_t& str = m_value;
                boost::algorithm::replace_all(str, nativeSearch, nativeReplace);
            }
            catch (std::exception& ex)
            {
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << ex.what();
            }
        }
    }
    
    template <class EncodingT>
    void String<EncodingT>::replaceRegex(boost::shared_ptr< Base<EncodingT> > const& start, boost::shared_ptr< Base<EncodingT> > const& end,
                                         boost::shared_ptr< Base<EncodingT> > const& regex, boost::shared_ptr< Base<EncodingT> > const& replace)
    {
        typedef boost::basic_regex<typename EncodingT::char_t>   regex_t;
        regex_t regexPattern;
        size_t nativeStart, nativeEnd;
        typename EncodingT::string_t nativeReplace;
        if (check_regex<EncodingT>(regex, regexPattern) &&
            check_numeric_i(start, nativeStart) &&
            check_numeric_i(end, nativeEnd) &&
            check_string<EncodingT>(replace, nativeReplace) &&
            nativeStart < m_value.size() &&
            nativeStart < nativeEnd &&
            nativeEnd <= m_value.size())
        {
            try
            {
                const typename EncodingT::string_t& str = m_value;
                std::basic_ostringstream<typename EncodingT::char_t> stream(std::ios::out | std::ios::binary);
                stream << str.substr(0, nativeStart);
                std::ostream_iterator<typename EncodingT::char_t, typename EncodingT::char_t> oi(stream);
                boost::regex_replace(oi, str.begin()+nativeStart, str.begin()+nativeEnd, regexPattern, nativeReplace);
                stream << str.substr(nativeEnd);
                m_value = stream.str();
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
        size_t nativePos;
        if (   check_numeric_i(pos, nativePos)
            && check_string<EncodingT>(val, nativeStr)
            && nativePos <= m_value.size())
        {
            m_value.insert(nativePos, nativeStr);
        }
    }

    template <class EncodingT>
    void String<EncodingT>::remove(boost::shared_ptr< Base<EncodingT> > const& pos, boost::shared_ptr< Base<EncodingT> > const& len)
    {
        size_t nativePos, nativeLen;
        if (   check_numeric_i(pos, nativePos)
            && check_numeric_i(len, nativeLen)
            && nativePos < m_value.size())
        {
            m_value.erase(nativePos, nativeLen);
        }
    }
    
    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::substring(boost::shared_ptr< Base<EncodingT> > const& pos, boost::shared_ptr< Base<EncodingT> > const& len) const
    {
        boost::shared_ptr< String<EncodingT> > res(new String<EncodingT>());
        size_t nativePos, nativeLen;
        if (   check_numeric_i(pos, nativePos)
            && check_numeric_i(len, nativeLen)
            && nativePos < m_value.size())
        {
            res->value(m_value.substr(nativePos, nativeLen));
        }
        return res;
    }
    
    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > String<EncodingT>::hash() const
    {
        std::hash<typename EncodingT::string_t> hash_fn;
        size_t h = hash_fn(m_value);
        return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(h));
    }
    
    template <class EncodingT>
    void String<EncodingT>::trim()
    {
        boost::trim(m_value);
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
        const typename EncodingT::string_t& tmp = val->toString();
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
            value->value(encode<EncodingT2,EncodingT>(n));
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "String expected, got " << A(val->getClassName());
        }
        return (value != NULL);
    }

NAMESPACE_END

#undef A
