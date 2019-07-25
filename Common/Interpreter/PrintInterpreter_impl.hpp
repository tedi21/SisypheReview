#include "ProgramInterpreter.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > PrintInstruction<EncodingT>::interpret(Context<EncodingT> & c)
    {
        boost::shared_ptr< Base<EncodingT> > expr = m_instruction->interpret(c);
        boost::shared_ptr< String<EncodingT> > res(new String<EncodingT>(expr->toString()));

        cout << A(res->value()) << endl;

        return res;
    }

    template <class EncodingT>
    bool PrintInstruction<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)
    {
        typename EncodingT::string_t expr;
        boost::shared_ptr< Term<EncodingT> > expr_value;
        bool success = prefix<EncodingT>(buf, C("print"), expr) &&
                       Bracket<EncodingT>::parse(expr, expr_value);
        if (success)
        {
            value.reset(new PrintInstruction<EncodingT>(expr_value));
        }
        return success;
    }

NAMESPACE_END

#undef C
#undef A
