#include "Numeric.hpp"

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > NumericConstant<EncodingT>::interpret(Context<EncodingT>&)
    {
        return boost::shared_ptr< Base<EncodingT> >(new Numeric<EncodingT>(m_data));
    }

    template <class EncodingT>
    bool NumericConstant<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)
    {
        std::variant<long long,double> data;
        long long lldata = 0LL;
        double ddata = 0.0;
        typename EncodingT::string_t numeric = eat_space<EncodingT>(buf);
        bool success = false;
        if (Convert<long long>::try_parse(numeric, lldata))
        {
            data = lldata;
            success = true;
        }
        else if (Convert<double>::try_parse(numeric, ddata))
        {
            data = ddata;
            success = true;
        }
        else
        {
            // success = false;
        }
        if (success)
        {
            value.reset(new NumericConstant<EncodingT>(data));
        }
        return success;
    }

NAMESPACE_END

