#include "Array.hpp"
#include "Numeric.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    Match<EncodingT>::Match()
    : m_start(0),
      m_string(nullptr),
      m_stringPos(nullptr),
      m_subStrings(nullptr),
      m_subStringsPos(nullptr),
      m_prefix(nullptr),
      m_suffix(nullptr)
    {}

    template <class EncodingT>
    Match<EncodingT>::Match(typename Match::match_t const& val, size_t start)
    : m_start(0),
      m_string(nullptr),
      m_stringPos(nullptr),
      m_subStrings(nullptr),
      m_subStringsPos(nullptr),
      m_prefix(nullptr),
      m_suffix(nullptr)
    {
        value(val, start);
    }

    template <class EncodingT>
    typename Match<EncodingT>::match_t const& Match<EncodingT>::value() const
    {
        return m_value;
    }
	
    template <class EncodingT>
    void Match<EncodingT>::value(typename Match<EncodingT>::match_t const& value, size_t start)
    {
        m_value = value;
        m_start = start;
        m_string.reset();
        m_stringPos.reset();
        m_subStrings.reset();
        m_subStringsPos.reset();
        m_prefix.reset();
        m_suffix.reset();
    }

    template <class EncodingT>
    typename EncodingT::string_t Match<EncodingT>::toString() const
    {
        typename EncodingT::string_t str;
        if (!m_value.empty())
        {
            str = m_value.str(0);
        }
        return str;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Match<EncodingT>::clone() const
    {
        return boost::shared_ptr< Base<EncodingT> >(new Match<EncodingT>(m_value, m_start));
    }

    template <class EncodingT>
    typename EncodingT::string_t Match<EncodingT>::getClassName() const
    {
        return C("Match");
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Match<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
    {
        boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
        
        ParameterArray args, ret;
        if (check_parameters_array(params, args))
        {
            if (tryInvoke(this, C("Match"), method, args, ret) ||
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
                Category * logger = &Category::getInstance(LOGNAME);
                logger->errorStream() << "Unexpected call in Match, no method \"" << A(method) << "\" exists.";
            }
        }
        return obj;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Match<EncodingT>::transformString() const
    {
        typename EncodingT::string_t str;
        if (!m_value.empty())
        {
            str = m_value.str(0);
        }
        return boost::shared_ptr< Base<EncodingT> >(new String<EncodingT>(str));
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Match<EncodingT>::transformSubStrings() const
    {
        boost::shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
        for (size_t i = 0; i < m_value.size(); i++)
        {
            arr->addValue(boost::shared_ptr< Base<EncodingT> >(new String<EncodingT>(m_value.str(i))));
        }
        return arr;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Match<EncodingT>::transformStringPos() const
    {
        size_t pos = 0;
        if (!m_value.empty())
        {
            pos = m_value.position();
        }
        return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_start + pos));
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Match<EncodingT>::transformSubStringsPos() const
    {
        boost::shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
        for (size_t i = 0; i < m_value.size(); i++)
        {
            arr->addValue(boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_start + m_value.position(i))));
        }
        return arr;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Match<EncodingT>::transformPrefix() const
    {
        typename EncodingT::string_t prefix;
        if (!m_value.empty())
        {
            prefix = m_value.prefix();
        }
        return boost::shared_ptr< Base<EncodingT> >(new String<EncodingT>(prefix));
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Match<EncodingT>::transformSuffix() const
    {
        typename EncodingT::string_t suffix;
        if (!m_value.empty())
        {
            suffix = m_value.suffix();
        }
        return boost::shared_ptr< Base<EncodingT> >(new String<EncodingT>(suffix));
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Match<EncodingT>::getString() const
    {
        if (!m_string)
        {
            m_string = transformString();
        }
        return m_string;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Match<EncodingT>::getSubStrings() const
    {
        if (!m_subStrings)
        {
            m_subStrings = transformSubStrings();
        }
        return m_subStrings;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Match<EncodingT>::getStringPos() const
    {
        if (!m_stringPos)
        {
            m_stringPos = transformStringPos();
        }
        return m_stringPos;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Match<EncodingT>::getSubStringsPos() const
    {
        if (!m_subStringsPos)
        {
            m_subStringsPos = transformSubStringsPos();
        }
        return m_subStringsPos;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Match<EncodingT>::getPrefix() const
    {
        if (!m_prefix)
        {
            m_prefix = transformPrefix();
        }
        return m_prefix;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Match<EncodingT>::getSuffix() const
    {
        if (!m_suffix)
        {
            m_suffix = transformSuffix();
        }
        return m_suffix;
    }

NAMESPACE_END

#undef C
#undef A
