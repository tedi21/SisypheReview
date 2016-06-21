
#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > DeleteOperator<EncodingT>::interpret(Context<EncodingT> & c)
    {
        return shared_ptr< Base<EncodingT> >(new Null<EncodingT>());
    }

    template <class EncodingT>
    bool DeleteOperator<EncodingT>::parse(typename EncodingT::string_t const& buf, shared_ptr< Term<EncodingT> > & value)
    {
        typename EncodingT::string_t str = eat_space<EncodingT>(buf);
        bool success = (str==C("null"));
        if (success)
        {
            value.reset(new DeleteOperator<EncodingT>());
        }
        return success;
    }

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > NewOperator<EncodingT>::interpret(Context<EncodingT> & c)
    {
        shared_ptr< Base<EncodingT> > object(new Base<EncodingT>());
        ParameterArray parameters;
        for (size_t i = 0; i<m_params.size(); ++i)
        {
            parameters.push_back(Parameter(i, m_params[i]->interpret(c)));
        }
        try
        {
            object.reset(FACTORY_MANAGER::getInstance()
                ->create(m_type + Convert<typename EncodingT::string_t>::parse(parameters.size()),
                         parameters));
        }
        catch (std::exception)
        {
            Category * logger = &Category::getInstance(LOGNAME);
            logger->errorStream() << "Unknown type name '" << A(m_type) << "' with " << parameters.size() << " parameters.";
        }

        return object;
    }

    template <class EncodingT>
    bool NewOperator<EncodingT>::parse(typename EncodingT::string_t const& buf, shared_ptr< Term<EncodingT> > & value)
    {
        typename EncodingT::string_t str;
        bool success = false;
        if (prefix<EncodingT>(buf, C("new"), str, true))
        {
            vector< shared_ptr< Term<EncodingT> > > params_values;
            typename EncodingT::string_t::const_iterator i = find_symbol<EncodingT>(str.begin(), str.end(), C("("));
            typename EncodingT::string_t type = eat_space<EncodingT>(typename EncodingT::string_t(
                                                (typename EncodingT::string_t::const_iterator) str.begin(), i));
            typename EncodingT::string_t parameters(i, (typename EncodingT::string_t::const_iterator) str.end());

            success = is_identifier<EncodingT>(type) &&
                      embrace<EncodingT>(parameters, C("("), C(")"), str);

            if (!str.empty())
            {
                vector<typename EncodingT::string_t> params;
                size_t j = 0;
                tuple_op<EncodingT>(str, C(","), params);
                while (success && j<params.size())
                {
                    shared_ptr< Term<EncodingT> > expr_value;
                    success = Instruction<EncodingT>::parse(params[j], expr_value);
                    params_values.push_back(expr_value);
                    ++j;
                }
            }

            if (success)
            {
                value.reset(new NewOperator<EncodingT>(type, params_values));
            }
        }
        return success;
    }

NAMESPACE_END

#undef C
#undef A
