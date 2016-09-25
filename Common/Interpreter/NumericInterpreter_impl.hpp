#include "Numeric.hpp"

#define A(str) encode<EncodingT,ansi>(str)
#define C(str) encode<ansi,EncodingT>(str)

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > NumericConstant<EncodingT>::interpret(Context<EncodingT>&)
    {
        return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_data));
    }

    template <class EncodingT>
    bool NumericConstant<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)
    {
        double data    = 0;
        typename EncodingT::string_t numeric = eat_space<EncodingT>(buf);
        bool success = Convert<double>::try_parse(A(numeric), data);
        if (success)
        {
            value.reset(new NumericConstant<EncodingT>(data));
        }
        return success;
    }

NAMESPACE_END

#undef C
#undef A
