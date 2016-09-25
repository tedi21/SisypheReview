
#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    Date<EncodingT>::Date()
    {}

    template <class EncodingT>
    Date<EncodingT>::Date(const dates::date& d)
    : m_date(d)
    {}

    template <class EncodingT>
    Date<EncodingT>::Date(boost::shared_ptr< Base<EncodingT> > const& year, boost::shared_ptr< Base<EncodingT> > const& month, boost::shared_ptr< Base<EncodingT> > const& day)
    {
        double nativeYear, nativeMonth, nativeDay;
        if (check_numeric(year, nativeYear)   &&
            check_numeric(month, nativeMonth) &&
            check_numeric(day, nativeDay))
        {
            m_date = dates::date(nativeYear, nativeMonth, nativeDay);
        }
    }

    template <class EncodingT>
    Date<EncodingT>::~Date()
    {}

    template <class EncodingT>
    typename EncodingT::string_t Date<EncodingT>::toString() const
    {
        return C(dates::to_simple_string(m_date));
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Date<EncodingT>::clone() const
    {
        return boost::shared_ptr< Base<EncodingT> >(new Date<EncodingT>(m_date));
    }

    template <class EncodingT>
    typename EncodingT::string_t Date<EncodingT>::getClassName() const
    {
        return C("Date");
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Date<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
    {
        boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());

        ParameterArray args, ret;
        if (check_parameters_array(params, args))
        {
            if (tryInvoke(this, C("Date"), method, args, ret) ||
                tryInvoke(this, C("String"), method, args, ret))
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
                logger->errorStream() << "Unexpected call in Date, no method \"" << A(method) << "\" exists.";
            }
        }
        return obj;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Date<EncodingT>::getCurrentDate() const
    {
        return boost::shared_ptr< Base<EncodingT> >(new Date<EncodingT>(dates::day_clock::local_day()));
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Date<EncodingT>::getDay() const
    {
        return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_date.day()));
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Date<EncodingT>::getMonth() const
    {
        return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_date.month()));
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Date<EncodingT>::getYear() const
    {
        return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_date.year()));
    }

NAMESPACE_END

#undef C
#undef A
