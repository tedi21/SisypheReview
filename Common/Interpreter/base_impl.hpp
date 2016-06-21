
#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    typename EncodingT::string_t Base<EncodingT>::toString() const
    {
        return typename EncodingT::string_t();
    }

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > Base<EncodingT>::clone() const
    {
        return shared_ptr< Base<EncodingT> >(new Base<EncodingT>());
    }

    template <class EncodingT>
    typename EncodingT::string_t Base<EncodingT>::getClassName() const
    {
        return C("Base");
    }

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > Base<EncodingT>::invoke(const typename EncodingT::string_t& method)
    {
        std::vector< shared_ptr< Base<EncodingT> > > params;
        return invoke(method, params);
    }

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > Base<EncodingT>::invoke(const typename EncodingT::string_t& method, std::vector< shared_ptr< Base<EncodingT> > >& params)
    {
        shared_ptr< Base<EncodingT> > obj(new Base<EncodingT>());
        
        ParameterArray args, ret;
        if (check_parameters_array(params, args))
        {
            if (tryInvoke(this, C("Base"), method, args, ret))
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
                logger->errorStream() << "Unexpected call in Base, no method \"" << A(method) << "\" exists.";
            }
        }
        return obj;
    }

    template <class EncodingT>
    bool check_parameters_array(const std::vector< shared_ptr< Base<EncodingT> > >& params, ParameterArray& out)
    { 
        for (size_t i=0; i<params.size(); ++i)
        {
            out.push_back(Parameter(i, params[i]));
        }

        return true;
    }

    template <class EncodingT>
    bool tryInvoke( Base<EncodingT>* object,
                    const typename EncodingT::string_t& className,
                    const typename EncodingT::string_t& method, 
                    const ParameterArray& params,
                    ParameterArray& out)
    {
        bool success = false;
        try
        {
            out = FACTORY_MANAGER::getInstance()
                ->invoke(className + C("::") + method + Convert<typename EncodingT::string_t>::parse(params.size()),
                         object, 
                         params);
            success = true;
        }
        catch (std::exception)
        {}
        return success;
    }

NAMESPACE_END

#undef C
#undef A
