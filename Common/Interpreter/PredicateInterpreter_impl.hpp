#include "Predicate.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    shared_ptr< Base<EncodingT> > PredicateOperator<EncodingT>::interpret(Context<EncodingT> & c)
    {
        return shared_ptr< Base<EncodingT> >(new Predicate<EncodingT>(c, m_name));
    }

    template <class EncodingT>
    bool PredicateOperator<EncodingT>::parse(typename EncodingT::string_t const& buf, shared_ptr< Term<EncodingT> > & value)
    {
        typename EncodingT::string_t expr = eat_space<EncodingT>(buf);
        bool success = prefix<EncodingT>(expr, C("function:"), expr, false) &&
                       is_identifier<EncodingT>(expr);
        if (success)
        {
            value.reset(new PredicateOperator<EncodingT>(expr));
        } 
        return success;  
    }

NAMESPACE_END

#undef C
#undef A
