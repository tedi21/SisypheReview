#include "String.hpp"

#define A(str) encode<EncodingT,ansi>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > StringConstant<EncodingT>::interpret(Context<EncodingT>&)
    {
        return boost::shared_ptr< Base<EncodingT> >(new String<EncodingT>(m_data));
    }

    template <class EncodingT>
    bool StringConstant<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)
    {
        typename EncodingT::string_t expr = eat_space<EncodingT>(buf);
        bool specialCrLf = (expr==UCS("CrLf"));
        bool specialCr = (expr==UCS("Cr"));
        bool specialLf = (expr==UCS("Lf"));
        bool specialDoubleQuotes = (expr==UCS("DblQuotes"));
        bool specialTab = (expr==UCS("Tab"));
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
                expr = UCS("\r\n");
            }
            else if (specialCr)
            {
                expr = UCS("\r");
            }
            else if (specialLf)
            {
                expr = UCS("\n");
            }
            else if (specialTab)
            {
                expr = UCS("\t");
            }
            else if (specialDoubleQuotes)
            {
                expr = UCS("\"");
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

#undef A
