#include "ProgramInterpreter.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    typename EncodingT::string_t const& Function<EncodingT>::getName() const
    {
        return m_name;
    }

    template <class EncodingT>
    std::vector<typename EncodingT::string_t> const& Function<EncodingT>::getParams() const
    {
        return m_params;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > Function<EncodingT>::interpret(Context<EncodingT> & c)
    {
        return m_block->interpret(c);
    }

    template <class EncodingT>
    bool Function<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)
    {
        bool success =  false;
        const typename EncodingT::string_t expr = eat_space<EncodingT>(buf);
        typename EncodingT::string_t::const_iterator i = find_symbol<EncodingT>(expr.begin(), expr.end(), C("("));
        typename EncodingT::string_t::const_iterator j = find_symbol<EncodingT>(i, expr.end(), C(")"));
        if (j != expr.end())
        {
            ++j;
            typename EncodingT::string_t parameters(i, j);
            typename EncodingT::string_t name(expr.begin(), i), block(j, expr.end());
            name = eat_space<EncodingT>(name);
            block = eat_space<EncodingT>(block);
            boost::shared_ptr< Term<EncodingT> > block_value;
            std::vector<typename EncodingT::string_t> params;
            success =   prefix<EncodingT>(name, C("function"), name, true) &&
                        suffix<EncodingT>(block, C("endfunction"), block, true) &&
                        is_identifier<EncodingT>(name) &&
                        embrace<EncodingT>(parameters, C("("), C(")"), parameters) &&
                        Block<EncodingT>::parse(block, block_value);
            if (!parameters.empty())
            {
                size_t k = 0;
                tuple_op<EncodingT>(parameters, C(","), params);
                while (success && k<params.size())
                {
                    success = is_identifier<EncodingT>(params[k]);
                    ++k;
                }
            }
            if (success)
            {
                value.reset(new Function<EncodingT>(name, params, block_value));
            }
        }
        return success;
    }

    template <class EncodingT>
    typename Function<EncodingT>::char_iterator
    Function<EncodingT>::look_for(typename Function<EncodingT>::char_iterator start, typename Function<EncodingT>::char_iterator end)
    {
        typename EncodingT::string_t::const_iterator i = start, j;
        if ( end-start > 20 &&
             equal_symbol<EncodingT>(start, start+8, C("function")) &&
            (j = find_symbol<EncodingT>(start+8, end, C("endfunction")))!=end)
        {
            i = j + 11;
        }
        return i;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > FunctionCall<EncodingT>::interpret(Context<EncodingT> & c)
    {
        boost::shared_ptr< Base<EncodingT> > val(new Base<EncodingT>());
        boost::shared_ptr< Function<EncodingT> > fct = dynamic_pointer_cast< Function<EncodingT> >(c.getFunction(m_name));
        if (fct)
        {
            Context<EncodingT> new_context(c);
            new_context.clear();
            std::vector<typename EncodingT::string_t> paramsName = fct->getParams();
            std::vector< boost::shared_ptr< Base<EncodingT> > > in;
            for (size_t i = 0; i<m_params.size() && i<paramsName.size(); ++i)
            {
                in.push_back(m_params[i]->interpret(c));
                new_context.add(paramsName[i], in[i]);
            }
            val = fct->interpret(new_context);
            for (size_t i = 0; i<m_params.size() && i<paramsName.size(); ++i)
            {
                boost::shared_ptr< Address<EncodingT> > ref = dynamic_pointer_cast< Address<EncodingT> >(m_params[i]);
                if (ref)
                {
                    boost::shared_ptr< Base<EncodingT> > out = new_context.getObject(paramsName[i]);
                    if (out != in[i])
                    {
                        ref->allocate(out, c);
                    }
                }
            }
        }
        return val;
    }

    template <class EncodingT>
    bool FunctionCall<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)
    {
        typename EncodingT::string_t name;
        vector< boost::shared_ptr< Term<EncodingT> > > params_values;
        typename EncodingT::string_t::const_iterator i = find_symbol<EncodingT>(buf.begin(), buf.end(), C("("));
        typename EncodingT::string_t parameters(i, buf.end());
        name = eat_space<EncodingT>(typename EncodingT::string_t(buf.begin(), i));

        bool success =  is_identifier<EncodingT>(name) &&
                        embrace<EncodingT>(parameters, C("("), C(")"), parameters);
        if (!parameters.empty())
        {
            vector<typename EncodingT::string_t> params;
            size_t j = 0;
            ignore_literal_comment<EncodingT> predicat;
            tuple_op_if<EncodingT>(parameters, C(","), params, predicat);
            while (success && j<params.size())
            {
                boost::shared_ptr< Address<EncodingT> > ref_value;
                boost::shared_ptr< Term<EncodingT> >    expr_value;
                success = Assignable<EncodingT>::parse(params[j], ref_value) ||
                          Instruction<EncodingT>::parse(params[j], expr_value);
                if (ref_value)
                {
                    params_values.push_back(ref_value);
                }
                else if (expr_value)
                {
                    params_values.push_back(expr_value);
                }
                ++j;
            }
        }

        if (success)
        {
            value.reset(new FunctionCall<EncodingT>(name, params_values));
        }
        return success;
    }

NAMESPACE_END

#undef C
#undef A
