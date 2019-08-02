#define A(str) encode<EncodingT,ansi>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    Regex<EncodingT>::Regex()
    {}

    template <class EncodingT>
    Regex<EncodingT>::Regex(typename Regex::regex_t const& val)
    {
        value(val);
    }

    template <class EncodingT>
    Regex<EncodingT>::Regex(boost::shared_ptr< Base<EncodingT> > const& value)
    {
        typename EncodingT::string_t str;
        if (check_string<EncodingT>(value, str))
        {
            m_value = str;
        }
    }

    template <class EncodingT>
    typename Regex<EncodingT>::regex_t const& Regex<EncodingT>::value() const
    {
        return m_value;
    }
	
    template <class EncodingT>
    void Regex<EncodingT>::value(typename Regex<EncodingT>::regex_t const& value)
    {
        m_value = value;
    }

    template <class EncodingT>
    typename EncodingT::string_t Regex<EncodingT>::toString() const
    {
        return m_value.str();
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Regex<EncodingT>::clone() const
    {
        return boost::shared_ptr< Base<EncodingT> >(new Regex<EncodingT>(m_value));
    }

    template <class EncodingT>
    typename EncodingT::string_t Regex<EncodingT>::getClassName() const
    {
        return UCS("Regex");
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Regex<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< boost::shared_ptr< Base<EncodingT> > >& params)
    {
        boost::shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
        
        ParameterArray args, ret;
        if (check_parameters_array(params, args))
        {
            if (tryInvoke(this, UCS("Regex"), method, args, ret) ||
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
                logger->errorStream() << "Unexpected call in Regex, no method \"" << A(method) << "\" exists.";
            }
        }
        return obj;
    }

    template <class EncodingT>
    void Regex<EncodingT>::setICase(boost::shared_ptr< Base<EncodingT> > const& val)
    {
      bool enable = false;
      if (check_bool(val, enable))
      {
        typename regex_t::flag_type flags = m_value.flags();
        if (enable)
        {
          flags |= boost::regex_constants::icase;
        }
        else
        {
          flags &= ~boost::regex_constants::icase;
        }
        m_value.assign(m_value.str(), flags);
      }
    }

    template <class EncodingT>
    void Regex<EncodingT>::setNoSubs(boost::shared_ptr< Base<EncodingT> > const& val)
    {
      bool enable = false;
      if (check_bool(val, enable))
      {
        typename regex_t::flag_type flags = m_value.flags();
        if (enable)
        {
          flags |= boost::regex_constants::nosubs;
        }
        else
        {
          flags &= ~boost::regex_constants::nosubs;
        }
        m_value.assign(m_value.str(), flags);
      }
    }
    
    template <class EncodingT>
    void Regex<EncodingT>::setCollate(boost::shared_ptr< Base<EncodingT> > const& val)
    {
      bool enable = false;
      if (check_bool(val, enable))
      {
        typename regex_t::flag_type flags = m_value.flags();
        if (enable)
        {
          flags |= boost::regex_constants::collate;
        }
        else
        {
          flags &= ~boost::regex_constants::collate;
        }
        m_value.assign(m_value.str(), flags);
      }
    }
    
    template <class EncodingT>
    void Regex<EncodingT>::setOptimize(boost::shared_ptr< Base<EncodingT> > const& val)
    {
      bool enable = false;
      if (check_bool(val, enable))
      {
        typename regex_t::flag_type flags = m_value.flags();
        if (enable)
        {
          flags |= boost::regex_constants::optimize;
        }
        else
        {
          flags &= ~boost::regex_constants::optimize;
        }
        m_value.assign(m_value.str(), flags);
      }
    }
    
    template <class EncodingT>
    bool check_regex(boost::shared_ptr< Base<EncodingT> > const& val, boost::basic_regex<typename EncodingT::char_t>& r)
    {
        boost::shared_ptr< Regex<EncodingT> > value  = dynamic_pointer_cast< Regex<EncodingT> >(val);
        if (value)
        {
          r = value->value();
        }
        else
        {
          r = val->toString();
        }
        return true;
    }

    template <class EncodingT>
    bool reset_regex(boost::shared_ptr< Base<EncodingT> > const& val, boost::basic_regex<typename EncodingT::char_t>& r)
    {
        boost::shared_ptr< Regex<EncodingT> > value  = dynamic_pointer_cast< Regex<EncodingT> >(val);
        if (value)
        {
            value->value(r);
        }
        else
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "Regex expected, got " << A(val->getClassName());
        }
        return value;
    }
    
NAMESPACE_END

#undef A
