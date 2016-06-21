#include "String.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > StringConstant<EncodingT>::interpret(Context<EncodingT>&)
    {
        return shared_ptr< Base<EncodingT> >(new String<EncodingT>(m_data));
    }

    template <class EncodingT>
    bool StringConstant<EncodingT>::parse(typename EncodingT::string_t const& buf, shared_ptr< Term<EncodingT> > & value)
    {
        typename EncodingT::string_t expr = eat_space<EncodingT>(buf);
        bool specialCrLf = (expr==C("CrLf"));
        bool specialCr = (expr==C("Cr"));
        bool specialLf = (expr==C("Lf"));
        bool specialDoubleQuotes = (expr==C("DblQuotes"));
        bool specialTab = (expr==C("Tab"));
        bool success =  expr.size()>1 &&
                        (specialCrLf         ||
                         specialCr           ||
                         specialLf           ||
                         specialTab          ||
                         specialDoubleQuotes ||
                        (expr[0] == (typename EncodingT::char_t)'\"' &&
                         expr[expr.size()-1] == (typename EncodingT::char_t)'\"'));
        if (success)
        {
            if (specialCrLf)
            {
                expr = C("\r\n");
            }
            else if (specialCr)
            {
                expr = C("\r");
            }
            else if (specialLf)
            {
                expr = C("\n");
            }
            else if (specialTab)
            {
                expr = C("\t");
            }
            else if (specialDoubleQuotes)
            {
                expr = C("\"");
            }
            else
            {
                expr = typename EncodingT::string_t(expr.begin()+1, expr.end()-1);
            }
            value.reset(new StringConstant<EncodingT>(expr));
        }
        return success;
    }

NAMESPACE_END

#undef C
#undef A
