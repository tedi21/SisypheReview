#include "Predicate.hpp"

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > PredicateOperator<EncodingT>::interpret(Context<EncodingT> & c)
    {
        return boost::shared_ptr< Base<EncodingT> >(new Predicate<EncodingT>(c, m_name));
    }

    template <class EncodingT>
    bool PredicateOperator<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)
    {
        typename EncodingT::string_t expr = eat_space<EncodingT>(buf);
        bool success = prefix<EncodingT>(expr, UCS("function:"), expr, false) &&
                       is_identifier<EncodingT>(expr);
        if (success)
        {
            value.reset(new PredicateOperator<EncodingT>(expr));
        } 
        return success;  
    }

NAMESPACE_END

