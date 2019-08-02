#include "Bool.hpp"

NAMESPACE_BEGIN(interp)

    template <class EncodingT>
    boost::shared_ptr< Base<EncodingT> > BoolConstant<EncodingT>::interpret(Context<EncodingT> &)
    {
        return boost::shared_ptr< Base<EncodingT> >(new Bool<EncodingT>(m_data));
    }

    template <class EncodingT>
    bool BoolConstant<EncodingT>::parse(typename EncodingT::string_t const& buf, boost::shared_ptr< Term<EncodingT> > & value)
    {  
        typename EncodingT::string_t str = eat_space<EncodingT>(buf);
        bool success = (str==UCS("true") || str==UCS("false"));
        if (success)
        {
            value.reset(new BoolConstant<EncodingT>((str==UCS("true"))?true:false));
        }
        return success; 
    }

NAMESPACE_END
