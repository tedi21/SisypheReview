#include "ProgramInterpreter.hpp"

#define A(str) encode<EncodingT,ansi>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > SystemInstruction<EncodingT>::interpret(Context<EncodingT> & c)
    {
        boost::shared_ptr< Base<EncodingT> > expr = m_instruction->interpret(c);
        boost::shared_ptr< String<EncodingT> > res(new String<EncodingT>(expr->toString()));

        ::system(A(res->value()).c_str());

        return res;
    }

    template <class EncodingT>
    bool SystemInstruction<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)
    {
        typename EncodingT::string_t expr;
        boost::shared_ptr< Term<EncodingT> > expr_value;
        bool success = prefix<EncodingT>(buf, UCS("system"), expr) &&
                       Bracket<EncodingT>::parse(expr, expr_value);
        if (success)
        {
            value.reset(new SystemInstruction<EncodingT>(expr_value));
        }
        return success;
    }

NAMESPACE_END

#undef A
