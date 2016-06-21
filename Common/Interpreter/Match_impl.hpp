#include "Array.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    Match<EncodingT>::Match()
    {}

    template <class EncodingT>
    Match<EncodingT>::Match(typename Match::match_t const& value, size_t start)
    {
        setValue(value, start);
    }

    template <class EncodingT>
    Match<EncodingT>::~Match()
    {}

    template <class EncodingT>
    typename Match<EncodingT>::match_t const& Match<EncodingT>::getValue() const
    {
        return m_value;
    }
	
    template <class EncodingT>
    void Match<EncodingT>::setValue(typename Match<EncodingT>::match_t const& value, size_t start)
    {
        m_value = value;
        m_start = start;
    }

    template <class EncodingT>
    typename EncodingT::string_t Match<EncodingT>::toString() const
    {
        return m_value[0];
    }

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > Match<EncodingT>::clone() const
    {
        return shared_ptr< Base<EncodingT> >(new Match<EncodingT>(m_value, m_start));
    }

    template <class EncodingT>
    typename EncodingT::string_t Match<EncodingT>::getClassName() const
    {
        return C("Match");
    }

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > Match<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
    {
        shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
        
        ParameterArray args, ret;
        if (check_parameters_array(params, args))
        {
            if (tryInvoke(this, C("Match"), method, args, ret))
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
    shared_ptr< Base<EncodingT> > Match<EncodingT>::getString() const
    {
        return shared_ptr< Base<EncodingT> >(new String<EncodingT>(m_value[0]));
    }

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > Match<EncodingT>::getSubStrings() const
    {
        shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
        for (size_t i=0; i < m_value.size(); i++)
        {
            arr->addValue(shared_ptr< Base<EncodingT> >(new String<EncodingT>(m_value[i])));
        }
        return arr;
    }

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > Match<EncodingT>::getStringPos() const
    {
        return shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_start + m_value.position()));
    }

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > Match<EncodingT>::getSubStringsPos() const
    {
        shared_ptr< Array<EncodingT> > arr(new Array<EncodingT>());
        for (size_t i=0; i < m_value.size(); i++)
        {
            arr->addValue(shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_start + m_value.position(i))));
        }
        return arr;
    }

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > Match<EncodingT>::getPrefix() const
    {
        return shared_ptr< Base<EncodingT> >(new String<EncodingT>(m_value.prefix()));
    }

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > Match<EncodingT>::getSuffix() const
    {
        return shared_ptr< Base<EncodingT> >(new String<EncodingT>(m_value.suffix()));
    }

NAMESPACE_END

#undef C
#undef A
