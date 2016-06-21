#include "ProgramInterpreter.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > SystemInstruction<EncodingT>::interpret(Context<EncodingT> & c)
    {
        shared_ptr< Base<EncodingT> > expr = m_instruction->interpret(c);
        shared_ptr< String<EncodingT> > res(new String<EncodingT>(expr->toString()));

        ::system(A(res->getValue()).c_str());

        return res;
    }

    template <class EncodingT>
    bool SystemInstruction<EncodingT>::parse(typename EncodingT::string_t const& buf, shared_ptr< Term<EncodingT> > & value)
    {
        typename EncodingT::string_t expr;
        shared_ptr< Term<EncodingT> > expr_value;
        bool success = prefix<EncodingT>(buf, C("system"), expr) &&
                       Bracket<EncodingT>::parse(expr, expr_value);
        if (success)
        {
            value.reset(new SystemInstruction<EncodingT>(expr_value));
        }
        return success;
    }

NAMESPACE_END

#undef C
#undef A
