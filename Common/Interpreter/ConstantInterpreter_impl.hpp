#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > ConstantAssignment<EncodingT>::interpret(Context<EncodingT> & c)
    {
        boost::shared_ptr< Base<EncodingT> > value = m_instruction->interpret(c);
        c.define(m_name, value);
        return value;
    }

    template <class EncodingT>
    bool ConstantAssignment<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)
    {
        typename EncodingT::string_t left, right;
        boost::shared_ptr< Term<EncodingT> > right_value;
        bool success = binary_op<EncodingT>(buf, C("="), left, right)     &&
                       prefix<EncodingT>(left, C("constant"), left, true) &&
                       is_identifier<EncodingT>(left)                     &&
                       Instruction<EncodingT>::parse(right, right_value);
        if (success)
        {
            value.reset(new ConstantAssignment<EncodingT>(left, right_value));
        }
        return success;
    }

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > ConstantOperator<EncodingT>::interpret(Context<EncodingT> & c)
    {
        return c.getConstant(m_name);
    }

    template <class EncodingT>
    bool ConstantOperator<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)
    {
        typename EncodingT::string_t expr = eat_space<EncodingT>(buf);
        bool success = prefix<EncodingT>(expr, C("constant:"), expr, false) &&
                       is_identifier<EncodingT>(expr);
        if (success)
        {
            value.reset(new ConstantOperator<EncodingT>(expr));
        } 
        return success;  
    }

NAMESPACE_END

#undef C
#undef A
